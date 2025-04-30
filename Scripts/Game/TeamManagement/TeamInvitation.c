/**
 * @brief Class representing a team invitation in ARMA Reforger
 */
class TeamInvitation
{
    // The unique ID of this invitation
    protected string m_InvitationID;
    
    // The ID of the team the invitation is for
    protected int m_TeamID;
    
    // The ID of the sender
    protected string m_SenderID;
    
    // The name of the sender
    protected string m_SenderName;
    
    // The ID of the receiver
    protected string m_ReceiverID;
    
    // The name of the receiver
    protected string m_ReceiverName;
    
    // The timestamp when the invitation was created
    protected float m_Timestamp;
    
    /**
     * @brief Constructor
     * @param invitationID Unique ID for this invitation
     * @param teamID ID of the team
     * @param senderID ID of the sender
     * @param senderName Name of the sender
     * @param receiverID ID of the receiver
     * @param receiverName Name of the receiver
     */
    void TeamInvitation(string invitationID, int teamID, string senderID, string senderName, string receiverID, string receiverName)
    {
        m_InvitationID = invitationID;
        m_TeamID = teamID;
        m_SenderID = senderID;
        m_SenderName = senderName;
        m_ReceiverID = receiverID;
        m_ReceiverName = receiverName;
        m_Timestamp = GetGame().GetWorld().GetWorldTime();
    }
    
    /**
     * @brief Get the unique ID of this invitation
     * @return The invitation ID
     */
    string GetInvitationID()
    {
        return m_InvitationID;
    }
    
    /**
     * @brief Get the team ID this invitation is for
     * @return The team ID
     */
    int GetTeamID()
    {
        return m_TeamID;
    }
    
    /**
     * @brief Get the ID of the sender
     * @return The sender's ID
     */
    string GetSenderID()
    {
        return m_SenderID;
    }
    
    /**
     * @brief Get the name of the sender
     * @return The sender's name
     */
    string GetSenderName()
    {
        return m_SenderName;
    }
    
    /**
     * @brief Get the ID of the receiver
     * @return The receiver's ID
     */
    string GetReceiverID()
    {
        return m_ReceiverID;
    }
    
    /**
     * @brief Get the name of the receiver
     * @return The receiver's name
     */
    string GetReceiverName()
    {
        return m_ReceiverName;
    }
    
    /**
     * @brief Get the timestamp when the invitation was created
     * @return The timestamp
     */
    float GetTimestamp()
    {
        return m_Timestamp;
    }
    
    /**
     * @brief Check if the invitation has expired
     * @param expiryTime Time in seconds after which invitations expire (default: 120 seconds)
     * @return True if expired, false otherwise
     */
    bool IsExpired(float expiryTime = 120.0)
    {
        float currentTime = GetGame().GetWorld().GetWorldTime();
        return (currentTime - m_Timestamp) > expiryTime;
    }
}
