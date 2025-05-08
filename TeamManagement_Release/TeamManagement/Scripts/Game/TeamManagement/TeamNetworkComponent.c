/**
 * @brief Network component for team management system
 * Handles RPC calls and data synchronization across the network
 */
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
                ScriptRPC rpc = new ScriptRPC();
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
                    ScriptRPC rpc = new ScriptRPC();
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
                ScriptRPC rpc = new ScriptRPC();
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
                    ScriptRPC rpc = new ScriptRPC();
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
                ScriptRPC rpc = new ScriptRPC();
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
                    ScriptRPC rpc = new ScriptRPC();
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
                ScriptRPC rpc = new ScriptRPC();
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
                    ScriptRPC rpc = new ScriptRPC();
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
                ScriptRPC rpc = new ScriptRPC();
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
                    ScriptRPC rpc = new ScriptRPC();
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
                ScriptRPC rpc = new ScriptRPC();
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
                    ScriptRPC rpc = new ScriptRPC();
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
     * @param ctx RPC context
     * @param rpc RPC data
     */
    void OnRPC_CreateTeam(RplComponent rpl, RPC rpc)
    {
        IEntity player = rpc.Read();
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling (from server broadcast)
        int teamID = rpc.Read();
        
        // Update local team manager with the new team
        if (teamID > 0)
        {
            Print("TeamNetworkComponent: Team created with ID " + teamID);
            // Local team manager will be updated by join team RPC
        }
    }
    
    /**
     * @brief RPC handler for joining a team
     * @param ctx RPC context
     * @param rpc RPC data
     */
    void OnRPC_JoinTeam(RplComponent rpl, RPC rpc)
    {
        int teamID = rpc.Read();
        IEntity player = rpc.Read();
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling (from server broadcast)
        bool success = rpc.Read();
        
        if (success)
        {
            Print("TeamNetworkComponent: Player joined team " + teamID);
            // Update local team manager
            m_TeamManager.JoinTeam(teamID, player);
        }
    }
    
    /**
     * @brief RPC handler for leaving a team
     * @param ctx RPC context
     * @param rpc RPC data
     */
    void OnRPC_LeaveTeam(RplComponent rpl, RPC rpc)
    {
        IEntity player = rpc.Read();
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling (from server broadcast)
        int teamID = rpc.Read();
        bool success = rpc.Read();
        
        if (success)
        {
            Print("TeamNetworkComponent: Player left team " + teamID);
            // Update local team manager
            m_TeamManager.LeaveTeam(player);
        }
    }
    
    /**
     * @brief RPC handler for sending an invitation
     * @param ctx RPC context
     * @param rpc RPC data
     */
    void OnRPC_SendInvitation(RplComponent rpl, RPC rpc)
    {
        IEntity sender = rpc.Read();
        string receiverID = rpc.Read();
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling
        bool success = rpc.Read();
        
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
     * @param ctx RPC context
     * @param rpc RPC data
     */
    void OnRPC_AcceptInvitation(RplComponent rpl, RPC rpc)
    {
        string invitationID = rpc.Read();
        IEntity player = rpc.Read();
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling
        int teamID = rpc.Read();
        bool success = rpc.Read();
        
        if (success)
        {
            Print("TeamNetworkComponent: Invitation " + invitationID + " accepted");
            
            // Local update will be handled by join team update
            m_TeamManager.AcceptInvitation(invitationID, player);
        }
    }
    
    /**
     * @brief RPC handler for declining an invitation
     * @param ctx RPC context
     * @param rpc RPC data
     */
    void OnRPC_DeclineInvitation(RplComponent rpl, RPC rpc)
    {
        string invitationID = rpc.Read();
        IEntity player = rpc.Read();
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling
        bool success = rpc.Read();
        
        if (success)
        {
            Print("TeamNetworkComponent: Invitation " + invitationID + " declined");
            m_TeamManager.DeclineInvitation(invitationID, player);
        }
    }
    
    /**
     * @brief RPC handler for team data synchronization
     * @param ctx RPC context
     * @param rpc RPC data
     */
    void OnRPC_SyncTeamData(RplComponent rpl, RPC rpc)
    {
        if (GetGame().IsServer())
        {
            // Only clients need to sync from server
            return;
        }
        
        // Read team data
        int teamID = rpc.Read();
        int memberCount = rpc.Read();
        
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
            string playerID = rpc.Read();
            string playerName = rpc.Read();
            bool isLeader = rpc.Read();
            
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
}