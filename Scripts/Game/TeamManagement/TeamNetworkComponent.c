/**
 * @brief Network component for team management system
 * Handles RPC calls and data synchronization across the network
 */
 
// ScriptRPC type is provided by the game engine
class TeamNetworkComponent : ScriptedWidgetComponent
{
    // Singleton instance
    private static ref TeamNetworkComponent s_Instance;
    
    // The team manager reference
    protected ref TeamManager m_TeamManager;
    
    // RPC constants
    protected const string RPC_CREATE_TEAM = "RPC_CreateTeam";
    protected const string RPC_JOIN_TEAM = "RPC_JoinTeam";
    protected const string RPC_LEAVE_TEAM = "RPC_LeaveTeam";
    protected const string RPC_SEND_INVITATION = "RPC_SendInvitation";
    protected const string RPC_ACCEPT_INVITATION = "RPC_AcceptInvitation";
    protected const string RPC_DECLINE_INVITATION = "RPC_DeclineInvitation";
    protected const string RPC_SYNC_TEAM_DATA = "RPC_SyncTeamData";
    protected const string RPC_LOCK_VEHICLE = "RPC_LockVehicle";
    protected const string RPC_UNLOCK_VEHICLE = "RPC_UnlockVehicle";
    protected const string RPC_TEAM_CHAT_MESSAGE = "RPC_TeamChatMessage";
    
    /**
     * @brief Get the singleton instance
     * @return TeamNetworkComponent instance
     */
    static TeamNetworkComponent GetInstance()
    {
        if (!s_Instance)
            s_Instance = new TeamNetworkComponent();
        
        return s_Instance;
    }
    
    /**
     * @brief Constructor
     */
    void TeamNetworkComponent()
    {
        m_TeamManager = TeamManager.GetInstance();
        
        // Register RPC handlers
        RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
        if (rpl)
        {
            rpl.RegisterHandler(RPC_CREATE_TEAM, this, "OnRPC_CreateTeam");
            rpl.RegisterHandler(RPC_JOIN_TEAM, this, "OnRPC_JoinTeam");
            rpl.RegisterHandler(RPC_LEAVE_TEAM, this, "OnRPC_LeaveTeam");
            rpl.RegisterHandler(RPC_SEND_INVITATION, this, "OnRPC_SendInvitation");
            rpl.RegisterHandler(RPC_ACCEPT_INVITATION, this, "OnRPC_AcceptInvitation");
            rpl.RegisterHandler(RPC_DECLINE_INVITATION, this, "OnRPC_DeclineInvitation");
            rpl.RegisterHandler(RPC_SYNC_TEAM_DATA, this, "OnRPC_SyncTeamData");
            rpl.RegisterHandler(RPC_LOCK_VEHICLE, this, "OnRPC_LockVehicle");
            rpl.RegisterHandler(RPC_UNLOCK_VEHICLE, this, "OnRPC_UnlockVehicle");
            rpl.RegisterHandler(RPC_TEAM_CHAT_MESSAGE, this, "OnRPC_TeamChatMessage");
        }
    }
    
    /**
     * @brief Network-safe method to create a team
     * @param player The player creating the team
     * @return The ID of the newly created team
     */
    int CreateTeam(IEntity player)
    {
        if (!GetGame().IsServer())
        {
            // Client side - send RPC to server
            RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
            if (rpl)
            {
                ScriptCallContext rpc = new ScriptCallContext();
                rpc.Write(player);
                rpl.SendRpc(RPC_CREATE_TEAM, rpc, true, null);
            }
            
            return 0; // Actual team ID will be set by server response
        }
        else
        {
            // Server side - create team and broadcast to all clients
            int teamID = m_TeamManager.CreateTeam(player);
            
            if (teamID > 0)
            {
                RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
                if (rpl)
                {
                    ScriptCallContext rpc = new ScriptCallContext();
                    rpc.Write(player);
                    rpc.Write(teamID);
                    rpl.BroadcastRpc(RPC_CREATE_TEAM, rpc, true, null);
                }
            }
            
            return teamID;
        }
    }
    
    /**
     * @brief Network-safe method to join a team
     * @param teamID The ID of the team to join
     * @param player The player joining the team
     * @return True if successful, false otherwise
     */
    bool JoinTeam(int teamID, IEntity player)
    {
        if (!GetGame().IsServer())
        {
            // Client side - send RPC to server
            RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
            if (rpl)
            {
                ScriptCallContext rpc = new ScriptCallContext();
                rpc.Write(teamID);
                rpc.Write(player);
                rpl.SendRpc(RPC_JOIN_TEAM, rpc, true, null);
            }
            
            return false; // Actual result will be set by server response
        }
        else
        {
            // Server side - join team and broadcast to all clients
            bool success = m_TeamManager.JoinTeam(teamID, player);
            
            if (success)
            {
                RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
                if (rpl)
                {
                    ScriptCallContext rpc = new ScriptCallContext();
                    rpc.Write(teamID);
                    rpc.Write(player);
                    rpc.Write(success);
                    rpl.BroadcastRpc(RPC_JOIN_TEAM, rpc, true, null);
                }
            }
            
            return success;
        }
    }
    
    /**
     * @brief Network-safe method to leave a team
     * @param player The player leaving the team
     * @return True if successful, false otherwise
     */
    bool LeaveTeam(IEntity player)
    {
        if (!GetGame().IsServer())
        {
            // Client side - send RPC to server
            RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
            if (rpl)
            {
                ScriptCallContext rpc = new ScriptCallContext();
                rpc.Write(player);
                rpl.SendRpc(RPC_LEAVE_TEAM, rpc, true, null);
            }
            
            return false; // Actual result will be set by server response
        }
        else
        {
            // Get team ID before leaving (for notification)
            string playerID = GetPlayerIdentity(player);
            int teamID = m_TeamManager.GetPlayerTeam(playerID);
            
            // Server side - leave team and broadcast to all clients
            bool success = m_TeamManager.LeaveTeam(player);
            
            if (success)
            {
                RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
                if (rpl)
                {
                    ScriptCallContext rpc = new ScriptCallContext();
                    rpc.Write(player);
                    rpc.Write(teamID);
                    rpc.Write(success);
                    rpl.BroadcastRpc(RPC_LEAVE_TEAM, rpc, true, null);
                }
            }
            
            return success;
        }
    }
    
    /**
     * @brief Network-safe method to send a team invitation
     * @param sender The player sending the invitation
     * @param receiverID The identity of the player receiving the invitation
     * @return True if invitation sent successfully, false otherwise
     */
    bool SendInvitation(IEntity sender, string receiverID)
    {
        if (!GetGame().IsServer())
        {
            // Client side - send RPC to server
            RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
            if (rpl)
            {
                ScriptCallContext rpc = new ScriptCallContext();
                rpc.Write(sender);
                rpc.Write(receiverID);
                rpl.SendRpc(RPC_SEND_INVITATION, rpc, true, null);
            }
            
            return false; // Actual result will be set by server response
        }
        else
        {
            // Server side - send invitation and broadcast to relevant clients
            bool success = m_TeamManager.SendInvitation(sender, receiverID);
            
            if (success)
            {
                RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
                if (rpl)
                {
                    ScriptCallContext rpc = new ScriptCallContext();
                    rpc.Write(sender);
                    rpc.Write(receiverID);
                    rpc.Write(success);
                    
                    // Only send to sender and receiver
                    IEntity receiver = GetPlayerByIdentity(receiverID);
                    array<IEntity> targets = new array<IEntity>();
                    
                    if (sender)
                        targets.Insert(sender);
                    
                    if (receiver)
                        targets.Insert(receiver);
                    
                    foreach (IEntity target : targets)
                    {
                        rpl.SendRpc(RPC_SEND_INVITATION, rpc, true, target);
                    }
                }
            }
            
            return success;
        }
    }
    
    /**
     * @brief Network-safe method to accept a team invitation
     * @param invitationID The ID of the invitation
     * @param player The player accepting the invitation
     * @return True if accepted successfully, false otherwise
     */
    bool AcceptInvitation(string invitationID, IEntity player)
    {
        if (!GetGame().IsServer())
        {
            // Client side - send RPC to server
            RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
            if (rpl)
            {
                ScriptCallContext rpc = new ScriptCallContext();
                rpc.Write(invitationID);
                rpc.Write(player);
                rpl.SendRpc(RPC_ACCEPT_INVITATION, rpc, true, null);
            }
            
            return false; // Actual result will be set by server response
        }
        else
        {
            // Get invitation details before accepting (for notification)
            ref TeamInvitation invitation = m_TeamManager.GetInvitation(invitationID);
            int teamID = 0;
            string senderID = "";
            
            if (invitation)
            {
                teamID = invitation.GetTeamID();
                senderID = invitation.GetSenderID();
            }
            
            // Server side - accept invitation and broadcast to all clients
            bool success = m_TeamManager.AcceptInvitation(invitationID, player);
            
            if (success)
            {
                RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
                if (rpl)
                {
                    ScriptCallContext rpc = new ScriptCallContext();
                    rpc.Write(invitationID);
                    rpc.Write(player);
                    rpc.Write(teamID);
                    rpc.Write(success);
                    
                    // Broadcast to all players in the team
                    array<ref TeamMember> teamMembers = m_TeamManager.GetTeamMembers(teamID);
                    if (teamMembers)
                    {
                        foreach (ref TeamMember member : teamMembers)
                        {
                            IEntity memberEntity = GetPlayerByIdentity(member.GetPlayerID());
                            if (memberEntity)
                                rpl.SendRpc(RPC_ACCEPT_INVITATION, rpc, true, memberEntity);
                        }
                    }
                    
                    // Also send to sender if they're not in the team anymore
                    IEntity sender = GetPlayerByIdentity(senderID);
                    if (sender)
                        rpl.SendRpc(RPC_ACCEPT_INVITATION, rpc, true, sender);
                }
            }
            
            return success;
        }
    }
    
    /**
     * @brief Network-safe method to decline a team invitation
     * @param invitationID The ID of the invitation
     * @param player The player declining the invitation
     * @return True if declined successfully, false otherwise
     */
    bool DeclineInvitation(string invitationID, IEntity player)
    {
        if (!GetGame().IsServer())
        {
            // Client side - send RPC to server
            RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
            if (rpl)
            {
                ScriptCallContext rpc = new ScriptCallContext();
                rpc.Write(invitationID);
                rpc.Write(player);
                rpl.SendRpc(RPC_DECLINE_INVITATION, rpc, true, null);
            }
            
            return false; // Actual result will be set by server response
        }
        else
        {
            // Get invitation details before declining (for notification)
            ref TeamInvitation invitation = m_TeamManager.GetInvitation(invitationID);
            string senderID = "";
            
            if (invitation)
                senderID = invitation.GetSenderID();
            
            // Server side - decline invitation and notify sender
            bool success = m_TeamManager.DeclineInvitation(invitationID, player);
            
            if (success)
            {
                RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
                if (rpl)
                {
                    ScriptCallContext rpc = new ScriptCallContext();
                    rpc.Write(invitationID);
                    rpc.Write(player);
                    rpc.Write(success);
                    
                    // Send to player and sender
                    array<IEntity> targets = new array<IEntity>();
                    targets.Insert(player);
                    
                    IEntity sender = GetPlayerByIdentity(senderID);
                    if (sender)
                        targets.Insert(sender);
                    
                    foreach (IEntity target : targets)
                    {
                        rpl.SendRpc(RPC_DECLINE_INVITATION, rpc, true, target);
                    }
                }
            }
            
            return success;
        }
    }
    
    /**
     * @brief Sync team data to a specific player
     * @param player The player to sync with
     */
    void SyncTeamData(IEntity player)
    {
        if (!GetGame().IsServer())
            return; // Only server can sync data
        
        // Get player's team
        string playerID = GetPlayerIdentity(player);
        int teamID = m_TeamManager.GetPlayerTeam(playerID);
        
        if (teamID <= 0)
            return; // Player not in a team
        
        array<ref TeamMember> teamMembers = m_TeamManager.GetTeamMembers(teamID);
        if (!teamMembers)
            return;
        
        // Serialize team data
        RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
        if (rpl)
        {
            ScriptRPC rpc = new ScriptRPC();
            rpc.Write(teamID);
            rpc.Write(teamMembers.Count());
            
            foreach (ref TeamMember member : teamMembers)
            {
                rpc.Write(member.GetPlayerID());
                rpc.Write(member.GetPlayerName());
                rpc.Write(member.IsLeader());
            }
            
            // Send to player
            rpl.SendRpc(RPC_SYNC_TEAM_DATA, rpc, true, player);
        }
    }
    
    /**
     * @brief RPC handler for creating a team
     * @param rpl Replication component
     * @param ctx Script call context for RPC
     */
    void OnRPC_CreateTeam(RplComponent rpl, ScriptCallContext ctx)
    {
        IEntity player = ctx.Read();
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling (from server broadcast)
        int teamID = ctx.Read();
        
        // Update local team manager with the new team
        if (teamID > 0)
        {
            Print("TeamNetworkComponent: Team created with ID " + teamID);
            // Local team manager will be updated by join team RPC
        }
    }
    
    /**
     * @brief RPC handler for joining a team
     * @param rpl Replication component
     * @param ctx Script call context for RPC
     */
    void OnRPC_JoinTeam(RplComponent rpl, ScriptCallContext ctx)
    {
        int teamID = ctx.Read();
        IEntity player = ctx.Read();
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling (from server broadcast)
        bool success = ctx.Read();
        
        if (success)
        {
            Print("TeamNetworkComponent: Player joined team " + teamID);
            // Update local team manager
            m_TeamManager.JoinTeam(teamID, player);
        }
    }
    
    /**
     * @brief RPC handler for leaving a team
     * @param rpl Replication component
     * @param ctx Script call context for RPC
     */
    void OnRPC_LeaveTeam(RplComponent rpl, ScriptCallContext ctx)
    {
        IEntity player = ctx.Read();
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling (from server broadcast)
        int teamID = ctx.Read();
        bool success = ctx.Read();
        
        if (success)
        {
            Print("TeamNetworkComponent: Player left team " + teamID);
            // Update local team manager
            m_TeamManager.LeaveTeam(player);
        }
    }
    
    /**
     * @brief RPC handler for sending an invitation
     * @param rpl Replication component
     * @param ctx Script call context for RPC
     */
    void OnRPC_SendInvitation(RplComponent rpl, ScriptCallContext ctx)
    {
        IEntity sender = ctx.Read();
        string receiverID = ctx.Read();
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling
        bool success = ctx.Read();
        
        if (success)
        {
            Print("TeamNetworkComponent: Invitation sent from " + GetPlayerIdentity(sender) + " to " + receiverID);
            
            // Check if this is the receiver of the invitation
            string localPlayerID = GetPlayerIdentity(GetGame().GetPlayerController().GetControlledEntity());
            if (localPlayerID == receiverID)
            {
                // Get local sender entity
                m_TeamManager.SendInvitation(sender, receiverID);
            }
        }
    }
    
    /**
     * @brief RPC handler for accepting an invitation
     * @param rpl Replication component
     * @param ctx Script call context for RPC
     */
    void OnRPC_AcceptInvitation(RplComponent rpl, ScriptCallContext ctx)
    {
        string invitationID = ctx.Read();
        IEntity player = ctx.Read();
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling
        int teamID = ctx.Read();
        bool success = ctx.Read();
        
        if (success)
        {
            Print("TeamNetworkComponent: Invitation " + invitationID + " accepted");
            
            // Local update will be handled by join team update
            m_TeamManager.AcceptInvitation(invitationID, player);
        }
    }
    
    /**
     * @brief RPC handler for declining an invitation
     * @param rpl Replication component
     * @param ctx Script call context for RPC
     */
    void OnRPC_DeclineInvitation(RplComponent rpl, ScriptCallContext ctx)
    {
        string invitationID = ctx.Read();
        IEntity player = ctx.Read();
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling
        bool success = ctx.Read();
        
        if (success)
        {
            Print("TeamNetworkComponent: Invitation " + invitationID + " declined");
            m_TeamManager.DeclineInvitation(invitationID, player);
        }
    }
    
    /**
     * @brief RPC handler for team data synchronization
     * @param rpl Replication component
     * @param ctx Script call context for RPC
     */
    void OnRPC_SyncTeamData(RplComponent rpl, ScriptCallContext ctx)
    {
        if (GetGame().IsServer())
        {
            // Only clients need to sync from server
            return;
        }
        
        // Read team data
        int teamID = ctx.Read();
        int memberCount = ctx.Read();
        
        // Create team on client if it doesn't exist
        if (!m_TeamManager.TeamExists(teamID))
        {
            // Create team structure without members (they'll be added below)
            m_TeamManager.CreateTeamStructure(teamID);
        }
        
        // Clear current team members and add synced members
        m_TeamManager.ClearTeamMembers(teamID);
        
        for (int i = 0; i < memberCount; i++)
        {
            string playerID = ctx.Read();
            string playerName = ctx.Read();
            bool isLeader = ctx.Read();
            
            m_TeamManager.AddTeamMember(teamID, playerID, playerName, isLeader);
        }
        
        Print("TeamNetworkComponent: Team data synced for team " + teamID);
    }
    
    /**
     * @brief Get the identity of a player entity
     * @param player The player entity
     * @return The player's identity string
     */
    private string GetPlayerIdentity(IEntity player)
    {
        if (!player)
            return "";
        
        PlayerController pc = PlayerController.Cast(player.GetController());
        if (!pc)
            return "";
        
        return pc.GetPlayerId().ToString();
    }
    
    /**
     * @brief Get a player entity by their identity
     * @param playerID The identity of the player
     * @return The player entity, or null if not found
     */
    private IEntity GetPlayerByIdentity(string playerID)
    {
        array<IEntity> players = new array<IEntity>();
        GetGame().GetWorld().GetPlayerManager().GetPlayers(players);
        
        foreach (IEntity player : players)
        {
            if (GetPlayerIdentity(player) == playerID)
                return player;
        }
        
        return null;
    }
    
    //=====================================================
    // Vehicle Management Methods
    //=====================================================
    
    /**
     * @brief Network-safe method to lock a vehicle for team access
     * @param player The player locking the vehicle
     * @param vehicle The vehicle entity to lock
     * @return True if successful, false otherwise
     */
    bool LockVehicle(IEntity player, IEntity vehicle)
    {
        if (!GetGame().IsServer())
        {
            // Client side - send RPC to server
            RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
            if (rpl)
            {
                ScriptRPC rpc = new ScriptRPC();
                rpc.Write(player);
                rpc.Write(vehicle);
                rpl.SendRpc(RPC_LOCK_VEHICLE, rpc, true, null);
            }
            
            return false; // Actual result will be set by server response
        }
        else
        {
            // Get the player's team ID
            string playerID = GetPlayerIdentity(player);
            int teamID = m_TeamManager.GetPlayerTeam(playerID);
            
            // Player must be in a team to lock a vehicle
            if (teamID <= 0)
                return false;
            
            // Get or create vehicle component
            TeamVehicleComponent vehicleComp = TeamVehicleComponent.Cast(vehicle.FindComponent(TeamVehicleComponent));
            if (!vehicleComp)
            {
                vehicleComp = new TeamVehicleComponent();
                vehicle.AddComponent(vehicleComp);
            }
            
            // Lock the vehicle
            bool success = vehicleComp.LockVehicle(player);
            
            if (success)
            {
                // Broadcast to all team members
                RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
                if (rpl)
                {
                    ScriptRPC rpc = new ScriptRPC();
                    rpc.Write(player);
                    rpc.Write(vehicle);
                    rpc.Write(teamID);
                    rpc.Write(success);
                    
                    // Broadcast to all players in the team
                    array<ref TeamMember> teamMembers = m_TeamManager.GetTeamMembers(teamID);
                    if (teamMembers)
                    {
                        foreach (ref TeamMember member : teamMembers)
                        {
                            IEntity memberEntity = GetPlayerByIdentity(member.GetPlayerID());
                            if (memberEntity)
                                rpl.SendRpc(RPC_LOCK_VEHICLE, rpc, true, memberEntity);
                        }
                    }
                }
            }
            
            return success;
        }
    }
    
    /**
     * @brief Network-safe method to unlock a vehicle
     * @param player The player unlocking the vehicle
     * @param vehicle The vehicle entity to unlock
     * @return True if successful, false otherwise
     */
    bool UnlockVehicle(IEntity player, IEntity vehicle)
    {
        if (!GetGame().IsServer())
        {
            // Client side - send RPC to server
            RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
            if (rpl)
            {
                ScriptRPC rpc = new ScriptRPC();
                rpc.Write(player);
                rpc.Write(vehicle);
                rpl.SendRpc(RPC_UNLOCK_VEHICLE, rpc, true, null);
            }
            
            return false; // Actual result will be set by server response
        }
        else
        {
            // Get vehicle component
            TeamVehicleComponent vehicleComp = TeamVehicleComponent.Cast(vehicle.FindComponent(TeamVehicleComponent));
            if (!vehicleComp)
                return false;
            
            // Get player's team ID
            string playerID = GetPlayerIdentity(player);
            int teamID = m_TeamManager.GetPlayerTeam(playerID);
            
            // Unlock the vehicle
            bool success = vehicleComp.UnlockVehicle(player);
            
            if (success)
            {
                // Broadcast to all players
                RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
                if (rpl)
                {
                    ScriptRPC rpc = new ScriptRPC();
                    rpc.Write(player);
                    rpc.Write(vehicle);
                    rpc.Write(success);
                    
                    // Broadcast to everyone since the vehicle is now publicly accessible
                    rpl.BroadcastRpc(RPC_UNLOCK_VEHICLE, rpc, true, null);
                }
            }
            
            return success;
        }
    }
    
    /**
     * @brief RPC handler for locking a vehicle
     * @param ctx The script call context
     */
    void OnRPC_LockVehicle(RplComponent rpl, ScriptCallContext ctx)
    {
        if (!ctx)
            return;
        
        IEntity player = null;
        IEntity vehicle = null;
        
        // Read parameters
        player = ctx.Read();
        vehicle = ctx.Read();
        
        if (!player || !vehicle)
            return;
            
        if (GetGame().IsServer())
        {
            // Server side - handle the lock request
            LockVehicle(player, vehicle);
        }
        else
        {
            // Client side - update UI or show notification
            int teamID = ctx.Read();
            bool success = ctx.Read();
            
            if (success)
            {
                // Update local vehicle state
                TeamVehicleComponent vehicleComp = TeamVehicleComponent.Cast(vehicle.FindComponent(TeamVehicleComponent));
                if (!vehicleComp)
                {
                    vehicleComp = new TeamVehicleComponent();
                    vehicle.AddComponent(vehicleComp);
                }
                
                // Show notification
                Print("Vehicle locked for team " + teamID);
            }
        }
    }
    
    /**
     * @brief RPC handler for unlocking a vehicle
     * @param rpl Replication component
     * @param ctx Script call context for RPC
     */
    void OnRPC_UnlockVehicle(RplComponent rpl, ScriptCallContext ctx)
    {
        if (!ctx)
            return;
        
        IEntity player = null;
        IEntity vehicle = null;
        
        // Read parameters
        player = ctx.Read();
        vehicle = ctx.Read();
        
        if (!player || !vehicle)
            return;
            
        if (GetGame().IsServer())
        {
            // Server side - handle the unlock request
            UnlockVehicle(player, vehicle);
        }
        else
        {
            // Client side - update UI or show notification
            bool success = ctx.Read();
            
            if (success)
            {
                // Show notification
                Print("Vehicle unlocked");
            }
        }
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Network-safe method to send a team chat message
     * @param sender The player sending the message
     * @param messageText The text of the message
     * @return True if message sent successfully, false otherwise
     */
    bool SendTeamChatMessage(IEntity sender, string messageText)
    {
        if (!sender || messageText.Length() == 0)
            return false;
            
        string senderID = GetPlayerIdentity(sender);
        string senderName = GetPlayerName(sender);
        
        if (senderID.Length() == 0)
            return false;
            
        // Get the player's team
        int teamID = m_TeamManager.GetPlayerTeam(senderID);
        if (teamID <= 0)
            return false; // Player is not in a team
            
        if (!GetGame().IsServer())
        {
            // Client side - send RPC to server
            RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
            if (rpl)
            {
                ScriptRPC rpc = new ScriptRPC();
                rpc.Write(sender);
                rpc.Write(messageText);
                rpl.SendRpc(RPC_TEAM_CHAT_MESSAGE, rpc, true, null);
            }
            
            return false; // Actual result will be set by server response
        }
        else
        {
            // Server side - distribute message to all team members
            
            // Create message
            ref TeamChatMessage message = new TeamChatMessage(teamID, senderID, senderName, messageText);
            
            // Get all team members
            array<ref TeamMember> teamMembers = m_TeamManager.GetTeamMembers(teamID);
            if (!teamMembers || teamMembers.Count() == 0)
                return false;
                
            // Send message to all team members
            RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
            if (rpl)
            {
                ScriptRPC rpc = new ScriptRPC();
                rpc.Write(teamID);
                rpc.Write(senderID);
                rpc.Write(senderName);
                rpc.Write(messageText);
                
                foreach (ref TeamMember member : teamMembers)
                {
                    // Get player entity
                    IEntity memberEntity = GetPlayerByIdentity(member.GetPlayerID());
                    if (memberEntity)
                    {
                        // Send message to this team member
                        rpl.SendRpc(RPC_TEAM_CHAT_MESSAGE, rpc, true, memberEntity);
                    }
                }
            }
            
            return true;
        }
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief RPC handler for team chat messages
     * @param rpl Replication component
     * @param ctx Script call context for RPC
     */
    void OnRPC_TeamChatMessage(RplComponent rpl, ScriptCallContext ctx)
    {
        if (!ctx)
            return;
            
        if (GetGame().IsServer())
        {
            // Server side - process the message
            IEntity sender = ctx.Read();
            string messageText = ctx.Read();
            
            if (!sender || messageText.Length() == 0)
                return;
                
            // Forward the message to all team members
            SendTeamChatMessage(sender, messageText);
        }
        else
        {
            // Client side - display the message
            int teamID = ctx.Read();
            string senderID = ctx.Read();
            string senderName = ctx.Read();
            string messageText = ctx.Read();
            
            // Create message object
            ref TeamChatMessage message = new TeamChatMessage(teamID, senderID, senderName, messageText);
            
            // Find all player entities with team chat components
            array<IEntity> players = GetGame().GetPlayerManager().GetPlayers();
            if (players)
            {
                foreach (IEntity player : players)
                {
                    if (player.IsLocal())
                    {
                        // Get chat component
                        TeamChatComponent chatComponent = TeamChatComponent.Cast(player.FindComponent(TeamChatComponent));
                        if (chatComponent)
                        {
                            // Deliver the message
                            chatComponent.ReceiveTeamChatMessage(message);
                        }
                    }
                }
            }
        }
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get player name
     * @param player The player entity
     * @return The player name
     */
    protected string GetPlayerName(IEntity player)
    {
        if (!player)
            return "Unknown";
            
        PlayerController pc = PlayerController.Cast(player.GetController());
        if (!pc)
            return "Unknown";
            
        return pc.GetPlayerName();
    }
}
