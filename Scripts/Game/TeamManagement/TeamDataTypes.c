// Team Management Data Types for ARMA Reforger

#include "../Core/Collections.c"

class TeamMember
{
    protected string m_PlayerID;
    protected string m_PlayerName;
    protected int m_TeamID;
    protected bool m_IsLeader;
    protected int m_EntityID;
    
    void TeamMember(string playerID, string playerName, int teamID, bool isLeader = false, int entityID = 0)
    {
        m_PlayerID = playerID;
        m_PlayerName = playerName;
        m_TeamID = teamID;
        m_IsLeader = isLeader;
        m_EntityID = entityID;
    }
    
    string GetPlayerID()
    {
        return m_PlayerID;
    }
    
    string GetPlayerName()
    {
        return m_PlayerName;
    }
    
    int GetTeamID()
    {
        return m_TeamID;
    }
    
    bool IsLeader()
    {
        return m_IsLeader;
    }
    
    int GetEntityID()
    {
        return m_EntityID;
    }
    
    void SetTeamID(int teamID)
    {
        m_TeamID = teamID;
    }
    
    void SetIsLeader(bool isLeader)
    {
        m_IsLeader = isLeader;
    }
    
    void SetEntityID(int entityID)
    {
        m_EntityID = entityID;
    }
}

class TeamInvitation
{
    protected string m_InvitationID;
    protected string m_SenderID;
    protected string m_SenderName;
    protected string m_ReceiverID;
    protected int m_TeamID;
    protected float m_Timestamp;
    
    void TeamInvitation(string senderID, string senderName, string receiverID, int teamID)
    {
        m_InvitationID = senderID + "_" + receiverID + "_" + teamID;
        m_SenderID = senderID;
        m_SenderName = senderName;
        m_ReceiverID = receiverID;
        m_TeamID = teamID;
        m_Timestamp = 0; // Should use GetGame().GetTime() in real implementation
    }
    
    string GetInvitationID()
    {
        return m_InvitationID;
    }
    
    string GetSenderID()
    {
        return m_SenderID;
    }
    
    string GetSenderName()
    {
        return m_SenderName;
    }
    
    string GetReceiverID()
    {
        return m_ReceiverID;
    }
    
    int GetTeamID()
    {
        return m_TeamID;
    }
    
    float GetTimestamp()
    {
        return m_Timestamp;
    }
}

class TeamChatMessage
{
    protected string m_SenderID;
    protected string m_SenderName;
    protected string m_Message;
    protected float m_Timestamp;
    protected int m_TeamID;
    
    void TeamChatMessage(string senderID, string senderName, string message, int teamID)
    {
        m_SenderID = senderID;
        m_SenderName = senderName;
        m_Message = message;
        m_TeamID = teamID;
        m_Timestamp = 0; // Should use GetGame().GetTime() in real implementation
    }
    
    string GetSenderID()
    {
        return m_SenderID;
    }
    
    string GetSenderName()
    {
        return m_SenderName;
    }
    
    string GetMessage()
    {
        return m_Message;
    }
    
    int GetTeamID()
    {
        return m_TeamID;
    }
    
    float GetTimestamp()
    {
        return m_Timestamp;
    }
    
    string GetFormattedMessage()
    {
        return "[" + m_SenderName + "]: " + m_Message;
    }
}