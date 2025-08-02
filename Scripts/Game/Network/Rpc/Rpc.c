// Rpc.c - RPC utility classes for ARMA Reforger
// This file contains the ScriptRPC class which is used for remote procedure calls

#include "../../Core/Game.c"
#include "../ScriptCallContext.c"

/**
 * @brief Enumeration of RPC execution modes
 */
enum ERpcExecType
{
    SERVER,     // Execute on server
    CLIENT,     // Execute on client
    BROADCAST,  // Execute on all clients
    TARGET      // Execute on a specific client
}

/**
 * @brief Utility class for handling Remote Procedure Calls in the Reforger scripting environment
 */
class ScriptRPC
{
    // RPC name
    protected string m_Function;
    
    // Execution mode
    protected ERpcExecType m_Type;
    
    // Target player ID for TARGET execution mode
    protected string m_TargetId;
    
    // Call context for parameter passing
    protected ref ScriptCallContext m_Context;
    
    /**
     * @brief Constructor
     * @param function The name of the RPC function to call
     * @param type The execution mode for this RPC
     */
    void ScriptRPC(string function = "", ERpcExecType type = ERpcExecType.SERVER)
    {
        m_Function = function;
        m_Type = type;
        m_Context = new ScriptCallContext();
    }
    
    /**
     * @brief Set the RPC function name
     * @param function The function name
     */
    void SetFunction(string function)
    {
        m_Function = function;
    }
    
    /**
     * @brief Set the execution mode
     * @param type The execution mode
     */
    void SetType(ERpcExecType type)
    {
        m_Type = type;
    }
    
    /**
     * @brief Set the target player ID for TARGET execution mode
     * @param targetId The target player's ID
     */
    void SetTarget(string targetId)
    {
        m_TargetId = targetId;
        m_Type = ERpcExecType.TARGET;
    }
    
    /**
     * @brief Send the RPC
     * @return True if the RPC was sent successfully, false otherwise
     */
    bool Send()
    {
        // Check if valid function name provided
        if (m_Function.Length() == 0)
            return false;
        
        // Get the RPC component
        RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
        if (!rpl)
            return false;
        
        // Send based on execution mode
        switch (m_Type)
        {
            case ERpcExecType.SERVER:
                rpl.SendRPC(m_Function, m_Context);
                break;
                
            case ERpcExecType.CLIENT:
                // Client-only execution not directly supported
                // Handled via the target system
                return false;
                
            case ERpcExecType.BROADCAST:
                // Server broadcasts to all clients
                if (GetGame().IsServer())
                {
                    rpl.BroadcastRPC(m_Function, m_Context);
                }
                else
                {
                    // Clients can't broadcast
                    return false;
                }
                break;
                
            case ERpcExecType.TARGET:
                // Server targets a specific client
                if (GetGame().IsServer() && m_TargetId.Length() > 0)
                {
                    rpl.SendRPCToPlayer(m_Function, m_Context, m_TargetId);
                }
                else
                {
                    // Invalid for clients or missing target ID
                    return false;
                }
                break;
                
            default:
                return false;
        }
        
        return true;
    }
    
    /**
     * @brief Write an integer value to the RPC parameters
     * @param value The value to write
     */
    void WriteInt(int value)
    {
        m_Context.WriteInt(value);
    }
    
    /**
     * @brief Write a boolean value to the RPC parameters
     * @param value The value to write
     */
    void WriteBool(bool value)
    {
        m_Context.WriteBool(value);
    }
    
    /**
     * @brief Write a float value to the RPC parameters
     * @param value The value to write
     */
    void WriteFloat(float value)
    {
        m_Context.WriteFloat(value);
    }
    
    /**
     * @brief Write a string value to the RPC parameters
     * @param value The value to write
     */
    void WriteString(string value)
    {
        m_Context.WriteString(value);
    }
    
    /**
     * @brief Write an entity to the RPC parameters
     * @param entity The entity to write
     */
    void Write(IEntity entity)
    {
        m_Context.Write(entity);
    }
    
    /**
     * @brief Write a vector value to the RPC parameters
     * @param value The value to write
     */
    void WriteVector(vector value)
    {
        m_Context.WriteVector(value);
    }
}

/**
 * @brief Utility function to register an RPC handler
 * @param functionName The name of the RPC function
 * @param handlerMethod The method to call when the RPC is received
 * @param instance The instance object for the handler method
 */
void RPC_RegisterHandler(string functionName, func handlerMethod, Class instance = null)
{
    if (functionName.Length() == 0 || !handlerMethod)
        return;
    
    // Get the RPC component
    RplComponent rpl = RplComponent.Cast(GetGame().GetRplComponent());
    if (!rpl)
        return;
    
    // Register the handler
    rpl.RegisterRPC(functionName, handlerMethod, instance);
}