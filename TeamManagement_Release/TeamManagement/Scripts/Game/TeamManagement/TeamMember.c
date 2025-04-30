/**
 * @brief Class representing a team member in ARMA Reforger
 */
class TeamMember
{
    // The ID of the player
    protected string m_PlayerID;
    
    // The name of the player
    protected string m_PlayerName;
    
    // Whether this player is the team leader
    protected bool m_IsLeader;
    
    // The timestamp when the player joined the team
    protected float m_JoinTimestamp;
    
    /**
     * @brief Constructor
     * @param playerID The ID of the player
     * @param playerName The name of the player
     * @param isLeader Whether this player is the team leader
     */
    void TeamMember(string playerID, string playerName, bool isLeader)
    {
        m_PlayerID = playerID;
        m_PlayerName = playerName;
        m_IsLeader = isLeader;
        m_JoinTimestamp = GetGame().GetWorld().GetWorldTime();
    }
    
    /**
     * @brief Get the ID of the player
     * @return The player's ID
     */
    string GetPlayerID()
    {
        return m_PlayerID;
    }
    
    /**
     * @brief Get the name of the player
     * @return The player's name
     */
    string GetPlayerName()
    {
        return m_PlayerName;
    }
    
    /**
     * @brief Set the name of the player
     * @param playerName The player's name
     */
    void SetPlayerName(string playerName)
    {
        m_PlayerName = playerName;
    }
    
    /**
     * @brief Check if this player is the team leader
     * @return True if player is leader, false otherwise
     */
    bool IsLeader()
    {
        return m_IsLeader;
    }
    
    /**
     * @brief Set whether this player is the team leader
     * @param isLeader True to make player the leader, false otherwise
     */
    void SetLeader(bool isLeader)
    {
        m_IsLeader = isLeader;
    }
    
    /**
     * @brief Get the timestamp when the player joined the team
     * @return The join timestamp
     */
    float GetJoinTimestamp()
    {
        return m_JoinTimestamp;
    }
}
