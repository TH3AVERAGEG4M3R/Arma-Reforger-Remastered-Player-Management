/**
 * @brief Network component for team management system
 * Handles RPC calls and data synchronization across the network
 */

// Import necessary classes from the engine
#include "../Core/IEntity.c"
#include "../Core/Game.c"
#include "../Core/ScriptedWidgetComponent.c"
#include "../Core/GenericComponent.c"
#include "../Core/ScriptComponent.c"
#include "../Core/PlayerController.c"

/**
 * @brief Simple call context for sending RPC data
 */
class ScriptCallContext
{
    // Data storage (simplified for our implementation)
    protected ref array<int> m_IntValues = new array<int>();
    protected ref array<bool> m_BoolValues = new array<bool>();
    protected ref array<float> m_FloatValues = new array<float>();
    protected ref array<string> m_StringValues = new array<string>();
    protected ref array<int> m_EntityIDs = new array<int>();
    protected ref array<vector> m_VectorValues = new array<vector>();
    
    // Current read positions
    protected int m_IntReadPos = 0;
    protected int m_BoolReadPos = 0;
    protected int m_FloatReadPos = 0;
    protected int m_StringReadPos = 0;
    protected int m_EntityReadPos = 0;
    protected int m_VectorReadPos = 0;
    
    // Constructor
    void ScriptCallContext() 
    {
        Reset();
    }
    
    // Write methods
    void WriteInt(int value) { m_IntValues.Insert(value); }
    void WriteBool(bool value) { m_BoolValues.Insert(value); }
    void WriteFloat(float value) { m_FloatValues.Insert(value); }
    void WriteString(string value) { m_StringValues.Insert(value); }
    void WriteVector(vector value) { m_VectorValues.Insert(value); }
    
    void Write(IEntity entity)
    {
        if (entity)
            m_EntityIDs.Insert(entity.GetID());
        else
            m_EntityIDs.Insert(0);
    }
    
    // Read methods
    int ReadInt() 
    {
        if (m_IntReadPos < m_IntValues.Count())
            return m_IntValues[m_IntReadPos++];
        return 0;
    }
    
    bool ReadBool()
    {
        if (m_BoolReadPos < m_BoolValues.Count())
            return m_BoolValues[m_BoolReadPos++];
        return false;
    }
    
    float ReadFloat()
    {
        if (m_FloatReadPos < m_FloatValues.Count())
            return m_FloatValues[m_FloatReadPos++];
        return 0.0;
    }
    
    string ReadString()
    {
        if (m_StringReadPos < m_StringValues.Count())
            return m_StringValues[m_StringReadPos++];
        return "";
    }
    
    IEntity ReadEntity()
    {
        if (m_EntityReadPos < m_EntityIDs.Count())
        {
            int entityID = m_EntityIDs[m_EntityReadPos++];
            if (entityID > 0)
                return GetGame().GetWorld().FindEntityByID(entityID);
        }
        return null;
    }
    
    vector ReadVector()
    {
        if (m_VectorReadPos < m_VectorValues.Count())
            return m_VectorValues[m_VectorReadPos++];
        return "0 0 0";
    }
    
    // Reset all data
    void Reset()
    {
        m_IntValues.Clear();
        m_BoolValues.Clear();
        m_FloatValues.Clear();
        m_StringValues.Clear();
        m_EntityIDs.Clear();
        m_VectorValues.Clear();
        
        m_IntReadPos = 0;
        m_BoolReadPos = 0;
        m_FloatReadPos = 0;
        m_StringReadPos = 0;
        m_EntityReadPos = 0;
        m_VectorReadPos = 0;
    }
}

/**
 * @brief Simple RPC class for network communication
 */
class ScriptRPC
{
    protected string m_FunctionName;
    protected ref ScriptCallContext m_Context;
    protected int m_SenderID;
    protected int m_TargetID;
    protected bool m_IsReliable;
    
    void ScriptRPC(string functionName = "")
    {
        m_FunctionName = functionName;
        m_Context = new ScriptCallContext();
        m_SenderID = 0;
        m_TargetID = 0;
        m_IsReliable = true;
    }
    
    // Parameter writing methods
    void WriteInt(int value) { m_Context.WriteInt(value); }
    void WriteBool(bool value) { m_Context.WriteBool(value); }
    void WriteFloat(float value) { m_Context.WriteFloat(value); }
    void WriteString(string value) { m_Context.WriteString(value); }
    void Write(IEntity entity) { m_Context.Write(entity); }
    void WriteVector(vector value) { m_Context.WriteVector(value); }
    
    // Parameter reading methods
    int ReadInt() { return m_Context.ReadInt(); }
    bool ReadBool() { return m_Context.ReadBool(); }
    float ReadFloat() { return m_Context.ReadFloat(); }
    string ReadString() { return m_Context.ReadString(); }
    IEntity ReadEntity() { return m_Context.ReadEntity(); }
    vector ReadVector() { return m_Context.ReadVector(); }
    
    // Getters and setters
    string GetFunctionName() { return m_FunctionName; }
    void SetFunctionName(string name) { m_FunctionName = name; }
    
    int GetSenderID() { return m_SenderID; }
    void SetSenderID(int id) { m_SenderID = id; }
    
    int GetTargetID() { return m_TargetID; }
    void SetTargetID(int id) { m_TargetID = id; }
    
    bool IsReliable() { return m_IsReliable; }
    void SetReliable(bool reliable) { m_IsReliable = reliable; }
    
    ScriptCallContext GetContext() { return m_Context; }
    
    void Reset()
    {
        m_FunctionName = "";
        m_Context.Reset();
        m_SenderID = 0;
        m_TargetID = 0;
        m_IsReliable = true;
    }
}

/**
 * @brief Replication component for network communication
 */
class RplComponent
{
    protected IEntity m_Owner;
    protected int m_ID;
    
    void RplComponent(IEntity owner = null)
    {
        m_Owner = owner;
        m_ID = 0;
    }
    
    bool SendRPC(string functionName, ScriptCallContext context, int targetID = 0, bool isReliable = true)
    {
        // In our implementation, we just log the RPC call
        Print(string.Format("Sending RPC: %1 to %2", functionName, targetID));
        return true;
    }
    
    IEntity GetOwner() { return m_Owner; }
    void SetOwner(IEntity owner) { m_Owner = owner; }
    
    int GetID() { return m_ID; }
    void SetID(int id) { m_ID = id; }
    
    void RegisterHandler(string rpcName, Object handler, string methodName)
    {
        // In our implementation, we just log the registration
        Print(string.Format("Registered RPC handler: %1 -> %2::%3", rpcName, handler.Type().Name, methodName));
    }
    
    static RplComponent Cast(IComponent component)
    {
        return RplComponent.Cast(component);
    }
}
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
                rpc.WriteInt(player.GetID());
                rpl.SendRPC(RPC_CREATE_TEAM, rpc);
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
                    rpc.WriteInt(player.GetID());
                    rpc.WriteInt(teamID);
                    rpl.SendRPC(RPC_CREATE_TEAM, rpc);
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
                rpc.WriteInt(teamID);
                rpc.WriteInt(player.GetID());
                rpl.SendRPC(RPC_JOIN_TEAM, rpc);
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
                    rpc.WriteInt(teamID);
                    rpc.WriteInt(player.GetID());
                    rpc.WriteBool(success);
                    rpl.SendRPC(RPC_JOIN_TEAM, rpc);
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
                rpc.WriteInt(player.GetID());
                rpl.SendRPC(RPC_LEAVE_TEAM, rpc);
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
                    rpc.WriteInt(player.GetID());
                    rpc.WriteInt(teamID);
                    rpc.WriteBool(success);
                    rpl.SendRPC(RPC_LEAVE_TEAM, rpc);
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
                rpc.WriteInt(sender.GetID());
                rpc.WriteString(receiverID);
                rpl.SendRPC(RPC_SEND_INVITATION, rpc);
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
                    rpc.WriteInt(sender.GetID());
                    rpc.WriteString(receiverID);
                    rpc.WriteBool(success);
                    
                    // Only send to sender and receiver
                    IEntity receiver = GetPlayerByIdentity(receiverID);
                    array<IEntity> targets = new array<IEntity>();
                    
                    if (sender)
                        targets.Insert(sender);
                    
                    if (receiver)
                        targets.Insert(receiver);
                    
                    foreach (IEntity target : targets)
                    {
                        rpl.SendRPC(RPC_SEND_INVITATION, rpc);
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
                rpc.WriteString(invitationID);
                rpc.WriteInt(player.GetID());
                rpl.SendRPC(RPC_ACCEPT_INVITATION, rpc);
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
                    rpc.WriteString(invitationID);
                    rpc.WriteInt(player.GetID());
                    rpc.WriteInt(teamID);
                    rpc.WriteBool(success);
                    
                    // Broadcast to all players in the team
                    array<ref TeamMember> teamMembers = m_TeamManager.GetTeamMembers(teamID);
                    if (teamMembers)
                    {
                        foreach (ref TeamMember member : teamMembers)
                        {
                            IEntity memberEntity = GetPlayerByIdentity(member.GetPlayerID());
                            if (memberEntity)
                                rpl.SendRPC(RPC_ACCEPT_INVITATION, rpc, true, memberEntity);
                        }
                    }
                    
                    // Also send to sender if they're not in the team anymore
                    IEntity sender = GetPlayerByIdentity(senderID);
                    if (sender)
                        rpl.SendRPC(RPC_ACCEPT_INVITATION, rpc, true, sender);
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
                rpc.WriteString(invitationID);
                rpc.WriteInt(player.GetID());
                rpl.SendRPC(RPC_DECLINE_INVITATION, rpc);
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
                    rpc.WriteString(invitationID);
                    rpc.WriteInt(player.GetID());
                    rpc.WriteBool(success);
                    
                    // Send to player and sender
                    array<IEntity> targets = new array<IEntity>();
                    targets.Insert(player);
                    
                    IEntity sender = GetPlayerByIdentity(senderID);
                    if (sender)
                        targets.Insert(sender);
                    
                    foreach (IEntity target : targets)
                    {
                        rpl.SendRPC(RPC_DECLINE_INVITATION, rpc);
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
            ScriptCallContext rpc = new ScriptCallContext();
            rpc.WriteInt(teamID);
            rpc.WriteInt(teamMembers.Count());
            
            foreach (ref TeamMember member : teamMembers)
            {
                rpc.WriteString(member.GetPlayerID());
                rpc.WriteString(member.GetPlayerName());
                rpc.WriteBool(member.IsLeader());
            }
            
            // Send to player
            rpl.SendRPC(RPC_SYNC_TEAM_DATA, rpc);
        }
    }
    
    /**
     * @brief RPC handler for creating a team
     * @param rpl Replication component
     * @param ctx Script call context for RPC
     */
    void OnRPC_CreateTeam(RplComponent rpl, ScriptCallContext ctx)
    {
        int playerID = ctx.ReadInt();
        IEntity player = GetGame().GetWorld().FindEntityByID(playerID);
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling (from server broadcast)
        int teamID = ctx.ReadInt();
        
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
        int teamID = ctx.ReadInt();
        int playerID = ctx.ReadInt();
        IEntity player = GetGame().GetWorld().FindEntityByID(playerID);
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling (from server broadcast)
        bool success = ctx.ReadBool();
        
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
        int playerID = ctx.ReadInt();
        IEntity player = GetGame().GetWorld().FindEntityByID(playerID);
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling (from server broadcast)
        int teamID = ctx.ReadInt();
        bool success = ctx.ReadBool();
        
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
        int senderID = ctx.ReadInt();
        IEntity sender = GetGame().GetWorld().FindEntityByID(senderID);
        string receiverID = ctx.ReadString();
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling
        bool success = ctx.ReadBool();
        
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
        string invitationID = ctx.ReadString();
        int playerID = ctx.ReadInt();
        IEntity player = GetGame().GetWorld().FindEntityByID(playerID);
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling
        int teamID = ctx.ReadInt();
        bool success = ctx.ReadBool();
        
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
        string invitationID = ctx.ReadString();
        int playerID = ctx.ReadInt();
        IEntity player = GetGame().GetWorld().FindEntityByID(playerID);
        
        if (GetGame().IsServer())
        {
            // Already handled by server-side code
            return;
        }
        
        // Client side handling
        bool success = ctx.ReadBool();
        
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
        int teamID = ctx.ReadInt();
        int memberCount = ctx.ReadInt();
        
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
            string playerID = ctx.ReadString();
            string playerName = ctx.ReadString();
            bool isLeader = ctx.ReadBool();
            
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
                ScriptCallContext rpc = new ScriptCallContext();
                rpc.WriteInt(player.GetID());
                rpc.WriteInt(vehicle.GetID());
                rpl.SendRPC(RPC_LOCK_VEHICLE, rpc);
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
                    ScriptCallContext rpc = new ScriptCallContext();
                    rpc.WriteInt(player.GetID());
                    rpc.WriteInt(vehicle.GetID());
                    rpc.WriteInt(teamID);
                    rpc.WriteBool(success);
                    
                    // Broadcast to all players in the team
                    array<ref TeamMember> teamMembers = m_TeamManager.GetTeamMembers(teamID);
                    if (teamMembers)
                    {
                        foreach (ref TeamMember member : teamMembers)
                        {
                            IEntity memberEntity = GetPlayerByIdentity(member.GetPlayerID());
                            if (memberEntity)
                                rpl.SendRPC(RPC_LOCK_VEHICLE, rpc);
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
                ScriptCallContext rpc = new ScriptCallContext();
                rpc.WriteInt(player.GetID());
                rpc.WriteInt(vehicle.GetID());
                rpl.SendRPC(RPC_UNLOCK_VEHICLE, rpc);
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
                    ScriptCallContext rpc = new ScriptCallContext();
                    rpc.WriteInt(player.GetID());
                    rpc.WriteInt(vehicle.GetID());
                    rpc.WriteBool(success);
                    
                    // Broadcast to everyone since the vehicle is now publicly accessible
                    rpl.SendRPC(RPC_UNLOCK_VEHICLE, rpc);
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
        
        // Read parameters
        int playerID = ctx.ReadInt();
        int vehicleID = ctx.ReadInt();
        
        IEntity player = GetGame().GetWorld().FindEntityByID(playerID);
        IEntity vehicle = GetGame().GetWorld().FindEntityByID(vehicleID);
        
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
            int teamID = ctx.ReadInt();
            bool success = ctx.ReadBool();
            
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
        
        // Read parameters
        int playerID = ctx.ReadInt();
        int vehicleID = ctx.ReadInt();
        
        IEntity player = GetGame().GetWorld().FindEntityByID(playerID);
        IEntity vehicle = GetGame().GetWorld().FindEntityByID(vehicleID);
        
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
            bool success = ctx.ReadBool();
            
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
                ScriptCallContext rpc = new ScriptCallContext();
                rpc.WriteInt(sender.GetID());
                rpc.WriteString(messageText);
                rpl.SendRPC(RPC_TEAM_CHAT_MESSAGE, rpc);
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
                ScriptCallContext rpc = new ScriptCallContext();
                rpc.WriteInt(teamID);
                rpc.WriteString(senderID);
                rpc.WriteString(senderName);
                rpc.WriteString(messageText);
                
                foreach (ref TeamMember member : teamMembers)
                {
                    // Get player entity
                    IEntity memberEntity = GetPlayerByIdentity(member.GetPlayerID());
                    if (memberEntity)
                    {
                        // Send message to this team member
                        rpl.SendRPC(RPC_TEAM_CHAT_MESSAGE, rpc);
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
            int senderID = ctx.ReadInt();
            string messageText = ctx.ReadString();
            
            IEntity sender = GetGame().GetWorld().FindEntityByID(senderID);
            if (!sender || messageText.Length() == 0)
                return;
                
            // Forward the message to all team members
            SendTeamChatMessage(sender, messageText);
        }
        else
        {
            // Client side - display the message
            int teamID = ctx.ReadInt();
            string senderID = ctx.ReadString();
            string senderName = ctx.ReadString();
            string messageText = ctx.ReadString();
            
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
