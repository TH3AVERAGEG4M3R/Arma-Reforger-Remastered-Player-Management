/**
 * @brief RPC (Remote Procedure Call) related definitions for ARMA Reforger
 */
#include "../ScriptCallContext.c"

// Enumeration for RPC flags
enum EScriptRPCFlags
{
    kFlagNone = 0,       // No special flags
    kIsReliable = 1,     // Ensure delivery (TCP-like)
    kIsUnreliable = 2,   // Fast but not guaranteed (UDP-like)
    kIsPriority = 4,     // Higher priority in queue
    kIsTarget = 8,       // Targeted to specific client(s)
    kIsBroadcast = 16    // Broadcast to all clients
}

/**
 * @brief RPC Component for managing network replication
 */
class RplComponent
{
    /**
     * @brief Register an RPC method
     * @param methodName The method name to register
     * @param functionName The function name to call
     * @param flags The RPC flags
     * @return True if registered successfully
     */
    bool RegisterRPC(string methodName, string functionName, EScriptRPCFlags flags)
    {
        // Implementation will be provided by ARMA Reforger engine
        return true;
    }
    
    /**
     * @brief Send an RPC call
     * @param methodName The method name to call
     * @param context The call context
     * @param target Optional target client ID (for targeted RPCs)
     * @return True if sent successfully
     */
    bool SendRPC(string methodName, ScriptCallContext context, int target = -1)
    {
        // Implementation will be provided by ARMA Reforger engine
        return true;
    }
}