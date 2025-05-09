/**
 * @brief Team Manager class for handling team operations in ARMA Reforger
 */
class TeamManager
{
    // Map of teams with team ID as key and array of team members as value
    protected ref map<int, ref array<ref TeamMember>> m_Teams = new map<int, ref array<ref TeamMember>>();
    
    // Map of pending invitations with invitation ID as key and invitation details as value
    protected ref map<string, ref TeamInvitation> m_PendingInvitations = new map<string, ref TeamInvitation>();
    
    // Counter for team IDs
    protected int m_TeamIDCounter = 1;
    
    // Singleton instance
    private static ref TeamManager s_Instance;
    
    // Maximum number of players allowed in a team
    static const int MAX_TEAM_SIZE = 8;
    
    // Network component for multiplayer support
    protected ref TeamNetworkComponent m_NetworkComponent;
    
    /**
     * @brief Get the singleton instance of TeamManager
     * @return TeamManager instance
     */
    static TeamManager GetInstance()
    {
        if (!s_Instance)
        {
            s_Instance = new TeamManager();
            
            // Initialize network component if needed
            if (GetGame().IsMultiplayer())
            {
                s_Instance.m_NetworkComponent = TeamNetworkComponent.GetInstance();
            }
        }
        
        return s_Instance;
    }
    
    /**
     * @brief Create a new team with a player as the leader
     * @param player The player who will be the team leader
     * @return The ID of the newly created team
     */
    int CreateTeam(IEntity player)
    {
        // In multiplayer, route through network component
        if (GetGame().IsMultiplayer() && m_NetworkComponent)
        {
            return m_NetworkComponent.CreateTeam(player);
        }
        
        // Single player or server implementation
        string playerID = GetPlayerIdentity(player);
        string playerName = GetPlayerName(player);
        
        // Check if player is already in a team
        int currentTeam = GetPlayerTeam(playerID);
        if (currentTeam > 0)
            return -1; // Player already in a team
        
        int teamID = m_TeamIDCounter++;
        
        ref TeamMember leaderMember = new TeamMember(playerID, playerName, true);
        leaderMember.SetTeamID(teamID);
        ref array<ref TeamMember> newTeam = new array<ref TeamMember>();
        newTeam.Insert(leaderMember);
        
        m_Teams.Insert(teamID, newTeam);
        
        // Notify player they created a team
        NotifyPlayer(player, "You have created a new team (ID: " + teamID + ")");
        
        return teamID;
    }
    
    /**
     * @brief Add a player to an existing team
     * @param teamID The ID of the team to join
     * @param player The player joining the team
     * @return True if successful, false otherwise
     */
    bool JoinTeam(int teamID, IEntity player)
    {
        // In multiplayer, route through network component
        if (GetGame().IsMultiplayer() && m_NetworkComponent)
        {
            return m_NetworkComponent.JoinTeam(teamID, player);
        }
        
        // Single player or server implementation
        if (!m_Teams.Contains(teamID))
            return false; // Team doesn't exist
        
        ref array<ref TeamMember> team = m_Teams.Get(teamID);
        if (team.Count() >= MAX_TEAM_SIZE)
            return false; // Team is full
        
        string playerID = GetPlayerIdentity(player);
        string playerName = GetPlayerName(player);
        
        // Check if player is already in a team
        int currentTeam = GetPlayerTeam(playerID);
        if (currentTeam > 0)
            return false; // Player already in a team
        
        // Add player to team
        ref TeamMember newMember = new TeamMember(playerID, playerName, false);
        newMember.SetTeamID(teamID);
        team.Insert(newMember);
        
        // Notify all team members about the new player
        NotifyTeam(teamID, playerName + " has joined your team");
        
        // Notify player they joined a team
        NotifyPlayer(player, "You have joined team " + teamID);
        
        return true;
    }
    
    /**
     * @brief Remove a player from their current team
     * @param player The player leaving the team
     * @return True if successful, false otherwise
     */
    bool LeaveTeam(IEntity player)
    {
        // In multiplayer, route through network component
        if (GetGame().IsMultiplayer() && m_NetworkComponent)
        {
            return m_NetworkComponent.LeaveTeam(player);
        }
        
        // Single player or server implementation
        string playerID = GetPlayerIdentity(player);
        string playerName = GetPlayerName(player);
        
        int teamID = GetPlayerTeam(playerID);
        if (teamID <= 0)
            return false; // Player not in a team
        
        ref array<ref TeamMember> team = m_Teams.Get(teamID);
        if (!team)
            return false; // Team doesn't exist
        
        bool isLeader = false;
        int memberIndex = -1;
        
        // Find the player in the team
        for (int i = 0; i < team.Count(); i++)
        {
            if (team[i].GetPlayerID() == playerID)
            {
                isLeader = team[i].IsLeader();
                memberIndex = i;
                break;
            }
        }
        
        if (memberIndex == -1)
            return false; // Player not found in the team
        
        // Remove player from team
        team.RemoveOrdered(memberIndex);
        
        // Notify remaining team members
        NotifyTeam(teamID, playerName + " has left the team");
        
        // Notify player they left the team
        NotifyPlayer(player, "You have left team " + teamID);
        
        // If player was the leader and there are still members, assign new leader
        if (isLeader && team.Count() > 0)
        {
            team[0].SetLeader(true);
            string newLeaderName = team[0].GetPlayerName();
            NotifyTeam(teamID, newLeaderName + " is now the team leader");
        }
        
        // If team is empty, remove it
        if (team.Count() == 0)
        {
            m_Teams.Remove(teamID);
        }
        
        return true;
    }
    
    /**
     * @brief Send a team invitation to a player
     * @param sender The player sending the invitation
     * @param receiverID The identity of the player receiving the invitation
     * @return True if invitation sent successfully, false otherwise
     */
    bool SendInvitation(IEntity sender, string receiverID)
    {
        // In multiplayer, route through network component
        if (GetGame().IsMultiplayer() && m_NetworkComponent)
        {
            return m_NetworkComponent.SendInvitation(sender, receiverID);
        }
        
        // Single player or server implementation
        string senderID = GetPlayerIdentity(sender);
        string senderName = GetPlayerName(sender);
        
        // Check if sender is in a team and is the leader
        int teamID = GetPlayerTeam(senderID);
        if (teamID <= 0)
            return false; // Sender not in a team
        
        if (!IsTeamLeader(senderID, teamID))
            return false; // Sender is not the team leader
        
        // Check if team is full
        ref array<ref TeamMember> team = m_Teams.Get(teamID);
        if (team.Count() >= MAX_TEAM_SIZE)
            return false; // Team is full
        
        // Check if receiver is already in a team
        int receiverTeam = GetPlayerTeam(receiverID);
        if (receiverTeam > 0)
            return false; // Receiver already in a team
        
        // Get receiver as entity
        IEntity receiver = GetPlayerByIdentity(receiverID);
        if (!receiver)
            return false; // Receiver not found
        
        string receiverName = GetPlayerName(receiver);
        
        // Generate unique invitation ID
        string invitationID = senderID + "_" + receiverID + "_" + teamID + "_" + m_TeamIDCounter;
        
        // Create and store invitation
        ref TeamInvitation invitation = new TeamInvitation(invitationID, teamID, senderID, senderName, receiverID, receiverName);
        m_PendingInvitations.Insert(invitationID, invitation);
        
        // Notify receiver about invitation
        NotifyPlayer(receiver, "You have received a team invitation from " + senderName);
        
        // Send popup to receiver
        ShowInvitationPopup(receiver, invitation);
        
        // Notify sender invitation was sent
        NotifyPlayer(sender, "Team invitation sent to " + receiverName);
        
        return true;
    }
    
    /**
     * @brief Accept a team invitation
     * @param invitationID The ID of the invitation
     * @param player The player accepting the invitation
     * @return True if accepted successfully, false otherwise
     */
    bool AcceptInvitation(string invitationID, IEntity player)
    {
        // In multiplayer, route through network component
        if (GetGame().IsMultiplayer() && m_NetworkComponent)
        {
            return m_NetworkComponent.AcceptInvitation(invitationID, player);
        }
        
        // Single player or server implementation
        ref TeamInvitation invitation = m_PendingInvitations.Get(invitationID);
        if (!invitation)
            return false; // Invitation not found
        
        string playerID = GetPlayerIdentity(player);
        if (invitation.GetReceiverID() != playerID)
            return false; // Invitation not for this player
        
        int teamID = invitation.GetTeamID();
        
        // Check if team still exists
        if (!m_Teams.Contains(teamID))
        {
            m_PendingInvitations.Remove(invitationID);
            NotifyPlayer(player, "The team no longer exists");
            return false;
        }
        
        // Check if team is now full
        ref array<ref TeamMember> team = m_Teams.Get(teamID);
        if (team.Count() >= MAX_TEAM_SIZE)
        {
            m_PendingInvitations.Remove(invitationID);
            NotifyPlayer(player, "The team is now full");
            return false;
        }
        
        // Accept invitation and add player to team
        bool success = JoinTeam(teamID, player);
        if (success)
        {
            // Remove invitation
            m_PendingInvitations.Remove(invitationID);
            
            // Get sender entity
            IEntity sender = GetPlayerByIdentity(invitation.GetSenderID());
            if (sender)
            {
                NotifyPlayer(sender, GetPlayerName(player) + " has accepted your team invitation");
            }
        }
        
        return success;
    }
    
    /**
     * @brief Decline a team invitation
     * @param invitationID The ID of the invitation
     * @param player The player declining the invitation
     * @return True if declined successfully, false otherwise
     */
    bool DeclineInvitation(string invitationID, IEntity player)
    {
        // In multiplayer, route through network component
        if (GetGame().IsMultiplayer() && m_NetworkComponent)
        {
            return m_NetworkComponent.DeclineInvitation(invitationID, player);
        }
        
        // Single player or server implementation
        ref TeamInvitation invitation = m_PendingInvitations.Get(invitationID);
        if (!invitation)
            return false; // Invitation not found
        
        string playerID = GetPlayerIdentity(player);
        if (invitation.GetReceiverID() != playerID)
            return false; // Invitation not for this player
        
        // Remove invitation
        m_PendingInvitations.Remove(invitationID);
        
        // Get sender entity
        IEntity sender = GetPlayerByIdentity(invitation.GetSenderID());
        if (sender)
        {
            NotifyPlayer(sender, GetPlayerName(player) + " has declined your team invitation");
        }
        
        NotifyPlayer(player, "You have declined the team invitation");
        
        return true;
    }
    
    /**
     * @brief Get the team ID a player belongs to
     * @param playerID The identity of the player
     * @return The team ID, or 0 if player is not in a team
     */
    int GetPlayerTeam(string playerID)
    {
        foreach (int teamID, ref array<ref TeamMember> team : m_Teams)
        {
            foreach (ref TeamMember member : team)
            {
                if (member.GetPlayerID() == playerID)
                    return teamID;
            }
        }
        
        return 0; // Not in a team
    }
    
    /**
     * @brief Check if a player is the leader of a team
     * @param playerID The identity of the player
     * @param teamID The ID of the team
     * @return True if player is leader, false otherwise
     */
    bool IsTeamLeader(string playerID, int teamID)
    {
        ref array<ref TeamMember> team = m_Teams.Get(teamID);
        if (!team)
            return false;
        
        foreach (ref TeamMember member : team)
        {
            if (member.GetPlayerID() == playerID && member.IsLeader())
                return true;
        }
        
        return false;
    }
    
    /**
     * @brief Get all members of a team
     * @param teamID The ID of the team
     * @return Array of team members, or null if team doesn't exist
     */
    array<ref TeamMember> GetTeamMembers(int teamID)
    {
        return m_Teams.Get(teamID);
    }
    
    /**
     * @brief Get a team member by entity ID (not player identity)
     * @param entityID The entity ID of the player
     * @return The team member, or null if not found
     */
    TeamMember GetTeamMemberByEntityID(int entityID)
    {
        IEntity playerEntity = GetGame().GetWorld().FindEntityByID(entityID);
        if (!playerEntity)
            return null;
            
        string playerID = GetPlayerIdentity(playerEntity);
        
        foreach (int teamID, ref array<ref TeamMember> team : m_Teams)
        {
            foreach (ref TeamMember member : team)
            {
                if (member.GetPlayerID() == playerID)
                    return member;
            }
        }
        
        return null;
    }
    
    /**
     * @brief Get all pending invitations for a player
     * @param playerID The identity of the player
     * @return Array of pending invitations
     */
    array<ref TeamInvitation> GetPendingInvitations(string playerID)
    {
        ref array<ref TeamInvitation> playerInvitations = new array<ref TeamInvitation>();
        
        foreach (string invitationID, ref TeamInvitation invitation : m_PendingInvitations)
        {
            if (invitation.GetReceiverID() == playerID)
                playerInvitations.Insert(invitation);
        }
        
        return playerInvitations;
    }
    
    /**
     * @brief Get an invitation by ID
     * @param invitationID The ID of the invitation
     * @return The invitation, or null if not found
     */
    TeamInvitation GetInvitation(string invitationID)
    {
        return m_PendingInvitations.Get(invitationID);
    }
    
    /**
     * @brief Check if a team exists
     * @param teamID The ID of the team
     * @return True if team exists, false otherwise
     */
    bool TeamExists(int teamID)
    {
        return m_Teams.Contains(teamID);
    }
    
    /**
     * @brief Create a team structure without members
     * Used for network synchronization
     * @param teamID The ID of the team
     */
    void CreateTeamStructure(int teamID)
    {
        if (!m_Teams.Contains(teamID))
        {
            ref array<ref TeamMember> newTeam = new array<ref TeamMember>();
            m_Teams.Insert(teamID, newTeam);
            
            // Update team ID counter if needed
            if (teamID >= m_TeamIDCounter)
                m_TeamIDCounter = teamID + 1;
        }
    }
    
    /**
     * @brief Clear all members from a team
     * Used for network synchronization
     * @param teamID The ID of the team
     */
    void ClearTeamMembers(int teamID)
    {
        if (m_Teams.Contains(teamID))
        {
            ref array<ref TeamMember> team = m_Teams.Get(teamID);
            team.Clear();
        }
    }
    
    /**
     * @brief Add a member to a team
     * Used for network synchronization
     * @param teamID The ID of the team
     * @param playerID The ID of the player
     * @param playerName The name of the player
     * @param isLeader Whether the player is the team leader
     */
    void AddTeamMember(int teamID, string playerID, string playerName, bool isLeader)
    {
        if (m_Teams.Contains(teamID))
        {
            ref array<ref TeamMember> team = m_Teams.Get(teamID);
            ref TeamMember newMember = new TeamMember(playerID, playerName, isLeader);
            team.Insert(newMember);
        }
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
     * @brief Get the name of a player entity
     * @param player The player entity
     * @return The player's name
     */
    private string GetPlayerName(IEntity player)
    {
        if (!player)
            return "Unknown";
        
        PlayerController pc = PlayerController.Cast(player.GetController());
        if (!pc)
            return "Unknown";
        
        return pc.GetPlayerName();
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
    
    /**
     * @brief Show an invitation popup to a player
     * @param player The player to show the popup to
     * @param invitation The invitation details
     */
    private void ShowInvitationPopup(IEntity player, TeamInvitation invitation)
    {
        // Get player controller
        PlayerController pc = PlayerController.Cast(player.GetController());
        if (!pc)
            return;
        
        // Create and show invitation popup
        SCR_TeamInvitationPopup.CreateInvitationPopup(pc, invitation);
    }
    
    /**
     * @brief Notify a player with a message
     * @param player The player to notify
     * @param message The message to display
     */
    private void NotifyPlayer(IEntity player, string message)
    {
        // Get player controller
        PlayerController pc = PlayerController.Cast(player.GetController());
        if (!pc)
            return;
        
        // Show notification
        SCR_NotificationSystem.SendNotification(pc, message);
    }
    
    /**
     * @brief Notify all members of a team with a message
     * @param teamID The ID of the team
     * @param message The message to display
     */
    private void NotifyTeam(int teamID, string message)
    {
        ref array<ref TeamMember> team = m_Teams.Get(teamID);
        if (!team)
            return;
        
        foreach (ref TeamMember member : team)
        {
            IEntity player = GetPlayerByIdentity(member.GetPlayerID());
            if (player)
                NotifyPlayer(player, message);
        }
    }
}
