/*!
    TeamFlagpole entity - a purchasable respawn point for teams.
    This entity can be placed in the world and purchased by team leaders,
    allowing team members to respawn at its location.
*/

// Import necessary classes from the engine
// Required includes for ARMA Reforger
class TeamFlagpole : GenericEntity
{
    protected int m_RespawnComponentID;
    protected RplComponent m_RplComponent;
    
    //------------------------------------------------------------------------------------------------
    void TeamFlagpole(IEntitySource src, IEntity parent)
    {
        SetFlags(EntityFlags.VISIBLE, true);
        SetEventMask(EntityEvent.INIT | EntityEvent.FRAME);
    }
    
    //------------------------------------------------------------------------------------------------
    override void EOnInit(IEntity owner)
    {
        super.EOnInit(owner);
        
        // Add respawn component
        TeamRespawnComponent respComp = TeamRespawnComponent.Cast(FindComponent(TeamRespawnComponent));
        if (!respComp)
        {
            respComp = TeamRespawnComponent.Cast(AddComponent(TeamRespawnComponent));
        }
        
        // Store the component ID instead of a direct reference
        if (respComp)
        {
            m_RespawnComponentID = respComp.GetComponentID();
        }
        
        // Get RplComponent
        m_RplComponent = RplComponent.Cast(FindComponent(RplComponent));
        
        // Setup interaction trigger
        if (GetGame().GetNetMode() == ENetMode.NM_Host || GetGame().IsMultiplayerHost())
        {
            // Register for RPC method to purchase flagpole
            if (m_RplComponent)
            {
                m_RplComponent.RegisterRPC("RPC_PurchaseFlagpole", "RPC_PurchaseFlagpole", EScriptRPCFlags.kIsReliable);
            }
        }
    }
    
    //------------------------------------------------------------------------------------------------
    /*! 
        RPC handler for purchasing the flagpole
        \param rpc The RPC object containing the call data
    */
    private void RPC_PurchaseFlagpole(ScriptCallContext ctx)
    {
        // Read parameters from the RPC call
        int playerID;
        string customName;
        
        ctx.Read(playerID);
        ctx.Read(customName);
        
        // Call the purchase method directly
        bool success = PurchaseFlagpole(playerID, customName);
        
        // Note: Notifications are handled in the PurchaseFlagpole method
    }
    
    //------------------------------------------------------------------------------------------------
    /*! 
        Method for a player to purchase this flagpole
        \param playerID Entity ID of the player making the purchase
        \param customName Optional custom name for the respawn point
        \return True if purchase was successful, false otherwise
    */
    bool PurchaseFlagpole(int playerID, string customName = "")
    {
        if (GetGame().GetNetMode() == ENetMode.NM_Client)
        {
            // Send RPC to server
            if (m_RplComponent)
            {
                ScriptCallContext rpc = new ScriptCallContext();
                rpc.Write(playerID);
                rpc.Write(customName);
                m_RplComponent.SendRPC("RPC_PurchaseFlagpole", rpc);
                return true; // Client doesn't know the result yet
            }
            return false;
        }
        else
        {
            // Direct call on the server
            IEntity playerEntity = GetGame().GetWorld().FindEntityByID(playerID);
            if (!playerEntity)
                return false;
                
            // Get the TeamManager
            TeamManager teamManager = TeamManager.GetInstance();
            if (!teamManager)
                return false;
                
            // Check if the player is a team leader
            TeamMember playerMember = teamManager.GetTeamMemberByEntityID(playerID);
            if (!playerMember || !playerMember.IsLeader())
                return false;
            
            int teamID = playerMember.GetTeamID();
            
            // Check if team already has maximum number of flagpoles
            if (teamManager.GetTeamFlagpoleCount(teamID) >= TeamManager.MAX_FLAGPOLES_PER_TEAM)
            {
                // Notify player
                PlayerController pc = PlayerController.Cast(playerEntity.GetController());
                if (pc)
                {
                    SCR_NotificationSystem.SendNotification(pc, "Your team already has the maximum number of respawn points.");
                }
                return false;
            }
            
            // Check if this location is valid (not too close to other flagpoles)
            if (!TeamRespawnComponent.CanPlaceFlagpoleAt(GetOrigin()))
            {
                // Notify player
                PlayerController pc = PlayerController.Cast(playerEntity.GetController());
                if (pc)
                {
                    SCR_NotificationSystem.SendNotification(pc, "Cannot place respawn point here. Too close to another respawn point.");
                }
                return false;
            }
                
            // Assign the team to this respawn point
            TeamRespawnComponent respComp = GetRespawnComponent();
            if (respComp)
            {
                respComp.AssignTeam(teamID, playerID, customName);
                
                // Register flagpole with the team manager
                teamManager.RegisterFlagpole(teamID, this);
                
                // Notify player
                PlayerController pc = PlayerController.Cast(playerEntity.GetController());
                if (pc)
                {
                    SCR_NotificationSystem.SendNotification(pc, "Team respawn point purchased successfully!");
                }
                
                return true;
            }
            
            return false;
        }
    }
    
    //------------------------------------------------------------------------------------------------
    /*! 
        Check if this flagpole is owned by a team
        \return True if the flagpole is owned, false otherwise
    */
    bool IsOwned()
    {
        TeamRespawnComponent respComp = GetRespawnComponent();
        if (!respComp)
            return false;
            
        return respComp.GetTeamID() != -1;
    }
    
    //------------------------------------------------------------------------------------------------
    /*! 
        Get the respawn component attached to this flagpole
        \return The respawn component
    */
    TeamRespawnComponent GetRespawnComponent()
    {
        return TeamRespawnComponent.Cast(FindComponentByID(m_RespawnComponentID));
    }
}