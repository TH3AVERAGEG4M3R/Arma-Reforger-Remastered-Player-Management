/**
 * @brief Container class for team chat messages
 */
class TeamChatMessage
{
    // Team ID this message belongs to
    protected int m_TeamID;
    
    // ID of the player who sent the message
    protected string m_SenderID;
    
    // Name of the player who sent the message
    protected string m_SenderName;
    
    // The text content of the message
    protected string m_MessageText;
    
    // Timestamp when the message was created
    protected float m_Timestamp;
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Constructor
     * @param teamID The team ID
     * @param senderID The ID of the sender
     * @param senderName The name of the sender
     * @param messageText The text of the message
     */
    void TeamChatMessage(int teamID, string senderID, string senderName, string messageText)
    {
        m_TeamID = teamID;
        m_SenderID = senderID;
        m_SenderName = senderName;
        m_MessageText = messageText;
        m_Timestamp = GetGame().GetWorld().GetWorldTime();
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the team ID
     * @return The team ID
     */
    int GetTeamID()
    {
        return m_TeamID;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the sender ID
     * @return The sender ID
     */
    string GetSenderID()
    {
        return m_SenderID;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the sender name
     * @return The sender name
     */
    string GetSenderName()
    {
        return m_SenderName;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the message text
     * @return The message text
     */
    string GetMessageText()
    {
        return m_MessageText;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the timestamp
     * @return The timestamp
     */
    float GetTimestamp()
    {
        return m_Timestamp;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Check if the message has expired
     * @param currentTime The current time
     * @param lifespan The message lifespan in seconds
     * @return True if expired, false otherwise
     */
    bool IsExpired(float currentTime, float lifespan)
    {
        return (currentTime - m_Timestamp) > lifespan;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Format the message for network transmission
     * @return Formatted string for network transmission
     */
    string FormatForNetwork()
    {
        return string.Format("%1|%2|%3|%4", m_TeamID.ToString(), m_SenderID, m_SenderName, m_MessageText);
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Create a message from network-formatted string
     * @param formattedString The formatted string
     * @return New TeamChatMessage object, or null if parsing failed
     */
    static TeamChatMessage CreateFromNetworkString(string formattedString)
    {
        array<string> parts = new array<string>();
        formattedString.Split("|", parts);
        
        if (parts.Count() < 4)
            return null;
            
        int teamID = parts[0].ToInt();
        string senderID = parts[1];
        string senderName = parts[2];
        string messageText = parts[3];
        
        return new TeamChatMessage(teamID, senderID, senderName, messageText);
    }
}