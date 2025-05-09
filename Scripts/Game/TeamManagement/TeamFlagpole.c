/*!
    TeamFlagpole entity - a purchasable respawn point for teams.
    This entity can be placed in the world and purchased by team leaders,
    allowing team members to respawn at its location.
*/
class TeamFlagpole : GenericEntity
{
    protected ref TeamRespawnComponent m_RespawnComponent;
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
        m_RespawnComponent = TeamRespawnComponent.Cast(FindComponent(TeamRespawnComponent));
        if (!m_RespawnComponent)
        {
            m_RespawnComponent = TeamRespawnComponent.Cast(AddComponent(TeamRespawnComponent));
        }
        
        // Get RplComponent
        m_RplComponent = RplComponent.Cast(FindComponent(RplComponent));
        
        // Setup interaction trigger
        if (GetGame().GetNetMode() == ENetMode.NM_Host || GetGame().IsMultiplayerHost())
        {
            // Register for RPC method to purchase flagpole
            if (m_RplComponent)
            {
                m_RplComponent.RegisterScriptRPC("RPC_PurchaseFlagpole", "RPC_PurchaseFlagpole", EScriptRPCFlags.kIsReliable);
            }
        }
    }
    
    //------------------------------------------------------------------------------------------------
    /*! 
        RPC handler for purchasing the flagpole
        \param ctx Context for the RPC call
    */
    private void RPC_PurchaseFlagpole(ScriptCallContext ctx)
    {
        // Read parameters from the RPC call
        int playerID;
        string customName;
        
        ctx.Read(playerID);
        ctx.Read(customName);
        
        // Validate the player and check if they are a team leader
        IEntity playerEntity = GetGame().GetWorld().FindEntityByID(playerID);
        if (!playerEntity)
            return;
            
        // Get the TeamManager
        TeamManager teamManager = TeamManager.GetInstance();
        if (!teamManager)
            return;
            
        // Check if the player is a team leader
        TeamMember playerMember = teamManager.GetTeamMemberByEntityID(playerID);
        if (!playerMember || !playerMember.IsLeader())
            return;
            
        // Check if player has enough resources to purchase the flagpole
        // This depends on the game's economy system, so there should be an additional check here.
        // For now, we assume the player has enough resources.
        
        // Assign the team to this respawn point
        if (m_RespawnComponent)
        {
            m_RespawnComponent.AssignTeam(playerMember.GetTeamID(), playerID, customName);
        }
        
        // Notify the player that purchase was successful
        // This could send a UI notification to the player
    }
    
    //------------------------------------------------------------------------------------------------
    /*! 
        Method for a player to purchase this flagpole
        \param playerID Entity ID of the player making the purchase
        \param customName Optional custom name for the respawn point
    */
    void PurchaseFlagpole(int playerID, string customName = "")
    {
        if (GetGame().GetNetMode() == ENetMode.NM_Client)
        {
            // Send RPC to server
            if (m_RplComponent)
            {
                ScriptRPC rpc = new ScriptRPC();
                rpc.Write(playerID);
                rpc.Write(customName);
                m_RplComponent.SendRPC("RPC_PurchaseFlagpole", rpc);
            }
        }
        else
        {
            // Direct call on the server
            IEntity playerEntity = GetGame().GetWorld().FindEntityByID(playerID);
            if (!playerEntity)
                return;
                
            // Get the TeamManager
            TeamManager teamManager = TeamManager.GetInstance();
            if (!teamManager)
                return;
                
            // Check if the player is a team leader
            TeamMember playerMember = teamManager.GetTeamMemberByEntityID(playerID);
            if (!playerMember || !playerMember.IsLeader())
                return;
                
            // Assign the team to this respawn point
            if (m_RespawnComponent)
            {
                m_RespawnComponent.AssignTeam(playerMember.GetTeamID(), playerID, customName);
            }
        }
    }
    
    //------------------------------------------------------------------------------------------------
    /*! 
        Check if this flagpole is owned by a team
        \return True if the flagpole is owned, false otherwise
    */
    bool IsOwned()
    {
        if (!m_RespawnComponent)
            return false;
            
        return m_RespawnComponent.GetTeamID() != -1;
    }
    
    //------------------------------------------------------------------------------------------------
    /*! 
        Get the respawn component attached to this flagpole
        \return The respawn component
    */
    TeamRespawnComponent GetRespawnComponent()
    {
        return m_RespawnComponent;
    }
}