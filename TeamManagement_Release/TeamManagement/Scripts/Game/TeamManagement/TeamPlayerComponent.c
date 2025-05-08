/**
 * @brief Component that attaches to player entities to handle team functionality
 */
class TeamPlayerComponent : GenericComponent
{
    protected ref TeamManager m_TeamManager;
    protected bool m_IsInitialized;
    
    /**
     * @brief Initialize component
     */
    void OnPostInit(IEntity owner)
    {
        super.OnPostInit(owner);
        
        // Get team manager instance
        m_TeamManager = TeamManager.GetInstance();
        m_IsInitialized = true;
        
        Print("TeamPlayerComponent initialized for player: " + GetPlayerName());
    }
    
    /**
     * @brief Handle component shutdown
     */
    void OnDelete(IEntity owner)
    {
        // If player is in a team, leave it when they disconnect
        if (m_IsInitialized && m_TeamManager)
        {
            int teamID = GetCurrentTeam();
            if (teamID > 0)
            {
                Print("Player disconnected, leaving team: " + teamID);
                m_TeamManager.LeaveTeam(owner);
            }
        }
        
        super.OnDelete(owner);
    }
    
    /**
     * @brief Get the current team ID of the player
     * @return The team ID, or 0 if not in a team
     */
    int GetCurrentTeam()
    {
        if (!m_IsInitialized || !m_TeamManager)
            return 0;
        
        IEntity owner = GetOwner();
        if (!owner)
            return 0;
        
        string playerID = GetPlayerID();
        return m_TeamManager.GetPlayerTeam(playerID);
    }
    
    /**
     * @brief Check if the player is a team leader
     * @return True if player is a team leader, false otherwise
     */
    bool IsTeamLeader()
    {
        if (!m_IsInitialized || !m_TeamManager)
            return false;
        
        int teamID = GetCurrentTeam();
        if (teamID <= 0)
            return false;
        
        string playerID = GetPlayerID();
        return m_TeamManager.IsTeamLeader(playerID, teamID);
    }
    
    /**
     * @brief Create a new team with this player as leader
     * @return The ID of the newly created team, or -1 if failed
     */
    int CreateTeam()
    {
        if (!m_IsInitialized || !m_TeamManager)
            return -1;
        
        IEntity owner = GetOwner();
        if (!owner)
            return -1;
        
        return m_TeamManager.CreateTeam(owner);
    }
    
    /**
     * @brief Leave the current team
     * @return True if successful, false otherwise
     */
    bool LeaveTeam()
    {
        if (!m_IsInitialized || !m_TeamManager)
            return false;
        
        IEntity owner = GetOwner();
        if (!owner)
            return false;
        
        return m_TeamManager.LeaveTeam(owner);
    }
    
    /**
     * @brief Send a team invitation to another player
     * @param receiverID The ID of the player to invite
     * @return True if invitation sent successfully, false otherwise
     */
    bool SendInvitation(string receiverID)
    {
        if (!m_IsInitialized || !m_TeamManager)
            return false;
        
        IEntity owner = GetOwner();
        if (!owner)
            return false;
        
        return m_TeamManager.SendInvitation(owner, receiverID);
    }
    
    /**
     * @brief Accept a team invitation
     * @param invitationID The ID of the invitation
     * @return True if accepted successfully, false otherwise
     */
    bool AcceptInvitation(string invitationID)
    {
        if (!m_IsInitialized || !m_TeamManager)
            return false;
        
        IEntity owner = GetOwner();
        if (!owner)
            return false;
        
        return m_TeamManager.AcceptInvitation(invitationID, owner);
    }
    
    /**
     * @brief Decline a team invitation
     * @param invitationID The ID of the invitation
     * @return True if declined successfully, false otherwise
     */
    bool DeclineInvitation(string invitationID)
    {
        if (!m_IsInitialized || !m_TeamManager)
            return false;
        
        IEntity owner = GetOwner();
        if (!owner)
            return false;
        
        return m_TeamManager.DeclineInvitation(invitationID, owner);
    }
    
    /**
     * @brief Get all pending invitations for this player
     * @return Array of pending invitations
     */
    array<ref TeamInvitation> GetPendingInvitations()
    {
        if (!m_IsInitialized || !m_TeamManager)
            return null;
        
        string playerID = GetPlayerID();
        return m_TeamManager.GetPendingInvitations(playerID);
    }
    
    /**
     * @brief Get the members of the player's current team
     * @return Array of team members, or null if not in a team
     */
    array<ref TeamMember> GetTeamMembers()
    {
        if (!m_IsInitialized || !m_TeamManager)
            return null;
        
        int teamID = GetCurrentTeam();
        if (teamID <= 0)
            return null;
        
        return m_TeamManager.GetTeamMembers(teamID);
    }
    
    /**
     * @brief Get the player's ID
     * @return The player's ID
     */
    private string GetPlayerID()
    {
        IEntity owner = GetOwner();
        if (!owner)
            return "";
        
        PlayerController pc = PlayerController.Cast(owner.GetController());
        if (!pc)
            return "";
        
        return pc.GetPlayerId().ToString();
    }
    
    /**
     * @brief Get the player's name
     * @return The player's name
     */
    private string GetPlayerName()
    {
        IEntity owner = GetOwner();
        if (!owner)
            return "Unknown";
        
        PlayerController pc = PlayerController.Cast(owner.GetController());
        if (!pc)
            return "Unknown";
        
        return pc.GetPlayerName();
    }
}