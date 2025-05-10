// Enums and classes for RPC (Remote Procedure Calls) in ARMA Reforger

enum EScriptRPCFlags
{
    kIsReliable = 1
};

class RplComponent
{
    void RegisterRPC(string functionName, string callbackMethod, EScriptRPCFlags flags)
    {
        // Implementation would register an RPC function in the game engine
    }
    
    void RegisterHandler(string functionName, Class instance, string methodName)
    {
        // Implementation would register a handler for RPC calls
    }
    
    void SendRpc(string functionName, ScriptCallContext ctx, bool isReliable, IEntity target)
    {
        // Implementation would send an RPC to a specific target
    }
    
    void BroadcastRpc(string functionName, ScriptCallContext ctx, bool isReliable, IEntity target)
    {
        // Implementation would broadcast an RPC to all clients
    }
    
    void SendRPC(string functionName, ScriptCallContext ctx)
    {
        // Implementation would send an RPC with no specific target
    }
}