// Rpc.c - RPC handling for ARMA Reforger
// This class defines the RPC functionality for network communication

#include "../ScriptCallContext.c"

/**
 * @brief Class representing an RPC call
 */
class ScriptRPC
{
    // RPC function name
    protected string m_FunctionName;
    
    // Call context for parameters
    protected ref ScriptCallContext m_Context;
    
    // Sender entity ID (for server to client RPCs)
    protected int m_SenderID;
    
    // Target entity ID (for client to server RPCs)
    protected int m_TargetID;
    
    // Whether this is a reliable RPC (guaranteed delivery)
    protected bool m_IsReliable;
    
    // Constructor
    void ScriptRPC(string functionName = "")
    {
        m_FunctionName = functionName;
        m_Context = new ScriptCallContext();
        m_SenderID = 0;
        m_TargetID = 0;
        m_IsReliable = true;
    }
    
    //------------------------------------------
    // Parameter writing methods (forwards to context)
    //------------------------------------------
    
    /**
     * @brief Write an integer parameter
     * @param value The integer value
     */
    void WriteInt(int value)
    {
        m_Context.WriteInt(value);
    }
    
    /**
     * @brief Write a boolean parameter
     * @param value The boolean value
     */
    void WriteBool(bool value)
    {
        m_Context.WriteBool(value);
    }
    
    /**
     * @brief Write a float parameter
     * @param value The float value
     */
    void WriteFloat(float value)
    {
        m_Context.WriteFloat(value);
    }
    
    /**
     * @brief Write a string parameter
     * @param value The string value
     */
    void WriteString(string value)
    {
        m_Context.WriteString(value);
    }
    
    /**
     * @brief Write an entity parameter
     * @param entity The entity
     */
    void Write(IEntity entity)
    {
        m_Context.Write(entity);
    }
    
    /**
     * @brief Write a vector parameter
     * @param value The vector value
     */
    void WriteVector(vector value)
    {
        m_Context.WriteVector(value);
    }
    
    //------------------------------------------
    // Parameter reading methods (forwards to context)
    //------------------------------------------
    
    /**
     * @brief Read an integer parameter
     * @return The integer value
     */
    int ReadInt()
    {
        return m_Context.ReadInt();
    }
    
    /**
     * @brief Read a boolean parameter
     * @return The boolean value
     */
    bool ReadBool()
    {
        return m_Context.ReadBool();
    }
    
    /**
     * @brief Read a float parameter
     * @return The float value
     */
    float ReadFloat()
    {
        return m_Context.ReadFloat();
    }
    
    /**
     * @brief Read a string parameter
     * @return The string value
     */
    string ReadString()
    {
        return m_Context.ReadString();
    }
    
    /**
     * @brief Read an entity parameter
     * @return The entity, or null if not found
     */
    IEntity ReadEntity()
    {
        return m_Context.ReadEntity();
    }
    
    /**
     * @brief Read a vector parameter
     * @return The vector value
     */
    vector ReadVector()
    {
        return m_Context.ReadVector();
    }
    
    //------------------------------------------
    // Getters and setters
    //------------------------------------------
    
    /**
     * @brief Get the function name
     * @return The function name
     */
    string GetFunctionName()
    {
        return m_FunctionName;
    }
    
    /**
     * @brief Set the function name
     * @param name The function name
     */
    void SetFunctionName(string name)
    {
        m_FunctionName = name;
    }
    
    /**
     * @brief Get the sender ID
     * @return The sender ID
     */
    int GetSenderID()
    {
        return m_SenderID;
    }
    
    /**
     * @brief Set the sender ID
     * @param id The sender ID
     */
    void SetSenderID(int id)
    {
        m_SenderID = id;
    }
    
    /**
     * @brief Get the target ID
     * @return The target ID
     */
    int GetTargetID()
    {
        return m_TargetID;
    }
    
    /**
     * @brief Set the target ID
     * @param id The target ID
     */
    void SetTargetID(int id)
    {
        m_TargetID = id;
    }
    
    /**
     * @brief Check if this RPC is reliable
     * @return True if reliable, false otherwise
     */
    bool IsReliable()
    {
        return m_IsReliable;
    }
    
    /**
     * @brief Set whether this RPC is reliable
     * @param reliable The reliability flag
     */
    void SetReliable(bool reliable)
    {
        m_IsReliable = reliable;
    }
    
    /**
     * @brief Get the call context
     * @return The call context
     */
    ScriptCallContext GetContext()
    {
        return m_Context;
    }
    
    /**
     * @brief Reset the RPC for reuse
     */
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
 * @brief RPC component for handling network messages
 */
class RplComponent
{
    // The entity that owns this component
    protected IEntity m_Owner;
    
    // Component ID
    protected int m_ID;
    
    // Constructor
    void RplComponent(IEntity owner = null)
    {
        m_Owner = owner;
        m_ID = 0;
    }
    
    /**
     * @brief Send an RPC to clients or server
     * @param functionName The RPC function name
     * @param context The call context with parameters
     * @param targetID The target entity ID (0 for broadcast)
     * @param isReliable Whether the RPC is reliable
     * @return True if successful, false otherwise
     */
    bool SendRPC(string functionName, ScriptCallContext context, int targetID = 0, bool isReliable = true)
    {
        // In a real implementation, this would send data over the network
        // For our implementation, we'll just log
        Print(string.Format("Sending RPC: %1 to %2", functionName, targetID));
        return true;
    }
    
    /**
     * @brief Get the entity that owns this component
     * @return The owner entity
     */
    IEntity GetOwner()
    {
        return m_Owner;
    }
    
    /**
     * @brief Set the entity that owns this component
     * @param owner The owner entity
     */
    void SetOwner(IEntity owner)
    {
        m_Owner = owner;
    }
    
    /**
     * @brief Get the component ID
     * @return The component ID
     */
    int GetID()
    {
        return m_ID;
    }
    
    /**
     * @brief Set the component ID
     * @param id The component ID
     */
    void SetID(int id)
    {
        m_ID = id;
    }
    
    /**
     * @brief Cast a component to RplComponent
     * @param component The component to cast
     * @return The RplComponent, or null if the component is not an RplComponent
     */
    static RplComponent Cast(IComponent component)
    {
        return RplComponent.Cast(component);
    }
}