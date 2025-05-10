// Import necessary classes from the engine
#include "$scripts:Game/Network/Rpc/Rpc.c"
#include "$scripts:Game/Network/ScriptCallContext.c"

class TeamRespawnComponentClass: GenericComponentClass
{
}

//------------------------------------------------------------------------------------------------
/*!
    Component that handles team respawn mechanics.
    Attaches to flagpole entities to provide team respawn functionality.
*/
class TeamRespawnComponent : GenericComponent
{
    // Reference to the owning team
    protected int m_TeamID = -1;
    
    // Reference to the entity ID of the team leader who purchased this respawn point
    protected int m_LeaderEntityID = -1;
    
    // Display name for this respawn point
    protected string m_RespawnName = "Team Respawn Point";
    
    // Position of the respawn point
    protected vector m_Position;
    
    // Cost to purchase this respawn point - placeholder for now
    static const int PURCHASE_COST = 9999; // "notYetDefined" - will be set by server admin
    
    // Minimum distance between flagpoles in meters
    static const float MIN_FLAGPOLE_DISTANCE = 100.0;
    
    // Cooldown time in seconds between respawns at flagpole
    static const float RESPAWN_COOLDOWN_SECONDS = 300.0;
    
    // Map to track player respawn cooldowns (playerID -> last respawn time)
    protected ref map<int, float> m_PlayerRespawnTimes = new map<int, float>();
    
    //------------------------------------------------------------------------------------------------
    void TeamRespawnComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
    {
        m_Position = ent.GetOrigin();
    }
    
    //------------------------------------------------------------------------------------------------
    void OnPostInit(IEntity owner)
    {
        
        SetEventMask(owner, EntityEvent.INIT);
        
        // Register to server RPCs
        if (GetGame().GetNetMode() == ENetMode.NM_Host || GetGame().IsMultiplayerHost())
        {
            RplComponent rpl = RplComponent.Cast(owner.FindComponent(RplComponent));
            if (rpl)
            {
                // Register for RPC method to handle respawn requests
                rpl.RegisterScriptRPC("RPC_RequestRespawn", "RPC_RequestRespawn", EScriptRPCFlags.kIsReliable);
                
                // Register for RPC method to assign team ownership
                rpl.RegisterScriptRPC("RPC_AssignTeam", "RPC_AssignTeam", EScriptRPCFlags.kIsReliable);
            }
        }
    }
    
    //------------------------------------------------------------------------------------------------
    override bool RplSave(ScriptBitWriter writer)
    {
        writer.WriteInt(m_TeamID);
        writer.WriteInt(m_LeaderEntityID);
        writer.WriteString(m_RespawnName);
        return true;
    }

    //------------------------------------------------------------------------------------------------
    override bool RplLoad(ScriptBitReader reader)
    {
        reader.ReadInt(m_TeamID);
        reader.ReadInt(m_LeaderEntityID);
        reader.ReadString(m_RespawnName);
        return true;
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        Assign a team ownership to this respawn point
        \param teamID The ID of the team that owns this respawn point
        \param leaderEntityID The entity ID of the team leader
        \param name Optional custom name for this respawn point
    */
    void AssignTeam(int teamID, int leaderEntityID, string name = "")
    {
        m_TeamID = teamID;
        m_LeaderEntityID = leaderEntityID;
        
        if (name != "")
            m_RespawnName = name;
        
        // Notify all clients about the team assignment
        RplComponent rpl = RplComponent.Cast(GetOwner().FindComponent(RplComponent));
        if (rpl)
        {
            ScriptCallContext rpc = new ScriptCallContext();
            rpc.Write(teamID);
            rpc.Write(leaderEntityID);
            rpc.Write(m_RespawnName);
            rpl.SendRPC("RPC_AssignTeam", rpc);
        }
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        RPC handler for assigning team ownership
        \param rpc The RPC object containing the call data
    */
    private void RPC_AssignTeam(ScriptCallContext ctx)
    {
        int teamID;
        int leaderEntityID;
        string name;
        
        ctx.Read(teamID);
        ctx.Read(leaderEntityID);
        ctx.Read(name);
        
        m_TeamID = teamID;
        m_LeaderEntityID = leaderEntityID;
        m_RespawnName = name;
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        Check if a player can use this respawn point
        \param playerID The entity ID of the player
        \return True if the player can use this respawn point, false otherwise
    */
    bool CanPlayerUseRespawn(int playerID)
    {
        if (m_TeamID == -1)
            return false;
            
        // Get the TeamManager
        TeamManager teamManager = TeamManager.GetInstance();
        if (!teamManager)
            return false;
            
        // Check if the player is in the same team
        TeamMember playerMember = teamManager.GetTeamMemberByEntityID(playerID);
        if (!playerMember)
            return false;
            
        return playerMember.GetTeamID() == m_TeamID;
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        Check if a player is on cooldown for respawning
        \param playerID The entity ID of the player
        \param remainingTime Output parameter to store the remaining cooldown time
        \return True if player is on cooldown, false otherwise
    */
    bool IsPlayerOnCooldown(int playerID, out float remainingTime)
    {
        remainingTime = 0;
        
        // If player has never respawned, they're not on cooldown
        if (!m_PlayerRespawnTimes.Contains(playerID))
            return false;
            
        // Get the last respawn time for this player
        float lastRespawnTime = m_PlayerRespawnTimes.Get(playerID);
        float currentTime = GetGame().GetWorld().GetWorldTime();
        float timeSinceLastRespawn = currentTime - lastRespawnTime;
        
        // If enough time has passed, player is not on cooldown
        if (timeSinceLastRespawn >= RESPAWN_COOLDOWN_SECONDS)
            return false;
            
        // Player is on cooldown, calculate remaining time
        remainingTime = RESPAWN_COOLDOWN_SECONDS - timeSinceLastRespawn;
        return true;
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        Handle a respawn request from a player
        \param playerID The entity ID of the player requesting respawn
        \return True if the request was successful, false otherwise
    */
    bool HandleRespawnRequest(int playerID)
    {
        if (!CanPlayerUseRespawn(playerID))
            return false;
            
        // Get the player entity
        IEntity player = GetGame().GetWorld().FindEntityByID(playerID);
        if (!player)
            return false;
            
        // Check if player is on cooldown
        float remainingCooldown;
        if (IsPlayerOnCooldown(playerID, remainingCooldown))
        {
            // Notify player they are on cooldown
            PlayerController pc = PlayerController.Cast(player.GetController());
            if (pc)
            {
                int minutes = Math.Floor(remainingCooldown / 60);
                int seconds = Math.Floor(remainingCooldown) % 60;
                string secondsStr;
                if (seconds < 10)
                    secondsStr = "0" + seconds.ToString();
                else
                    secondsStr = seconds.ToString();
                string cooldownText = minutes.ToString() + ":" + secondsStr;
                SCR_NotificationSystem.SendNotification(pc, "You must wait " + cooldownText + " before respawning again.");
            }
            return false;
        }
            
        // Teleport to the respawn position with a slight offset to prevent players spawning on top of each other
        float randomOffsetX = Math.RandomFloat(-2, 2);
        float randomOffsetZ = Math.RandomFloat(-2, 2);
        vector respawnPos = m_Position + Vector(randomOffsetX, 0, randomOffsetZ);
        
        // Set player position
        player.SetOrigin(respawnPos);
        
        // Update the player's last respawn time
        float currentTime = GetGame().GetWorld().GetWorldTime();
        m_PlayerRespawnTimes.Set(playerID, currentTime);
        
        // Notify player of successful respawn and cooldown
        PlayerController pc = PlayerController.Cast(player.GetController());
        if (pc)
        {
            int cooldownMinutes = Math.Floor(RESPAWN_COOLDOWN_SECONDS / 60);
            SCR_NotificationSystem.SendNotification(pc, "You have respawned at " + m_RespawnName + ". Cooldown: " + cooldownMinutes + " minutes.");
        }
        
        return true;
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        RPC handler for respawn requests
        \param rpc The RPC object containing the call data
    */
    private void RPC_RequestRespawn(ScriptCallContext ctx)
    {
        int playerID;
        ctx.Read(playerID);
        
        HandleRespawnRequest(playerID);
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        Get the name of this respawn point
        \return The name of the respawn point
    */
    string GetRespawnName()
    {
        return m_RespawnName;
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        Get the team ID that owns this respawn point
        \return The team ID
    */
    int GetTeamID()
    {
        return m_TeamID;
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        Get the leader entity ID who purchased this respawn point
        \return The leader entity ID
    */
    int GetLeaderEntityID()
    {
        return m_LeaderEntityID;
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        Get the position of this respawn point
        \return The position vector
    */
    vector GetRespawnPosition()
    {
        return m_Position;
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        Check if a flagpole can be placed at a given position based on proximity to other flagpoles
        \param position The position to check
        \return True if the position is valid, false otherwise
    */
    static bool CanPlaceFlagpoleAt(vector position)
    {
        // Find all existing flagpoles in the world
        array<IEntity> existingFlagpoles = new array<IEntity>();
        GetGame().GetWorld().FindEntitiesByType(TeamFlagpole, existingFlagpoles);
        
        // Check distance to each existing flagpole
        foreach (IEntity entity : existingFlagpoles)
        {
            vector flagpolePos = entity.GetOrigin();
            float distance = vector.Distance(position, flagpolePos);
            
            // If too close to another flagpole, return false
            if (distance < MIN_FLAGPOLE_DISTANCE)
                return false;
        }
        
        return true;
    }
}