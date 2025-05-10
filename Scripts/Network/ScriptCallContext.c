// ScriptCallContext class for ARMA Reforger RPCs

class ScriptCallContext
{
    // Constructor
    void ScriptCallContext() {}
    
    // Read methods for different data types
    void Read(out int value) {}
    void Read(out float value) {}
    void Read(out bool value) {}
    void Read(out string value) {}
    void Read(out vector value) {}
    IEntity Read() { return null; }
    
    // Write methods for different data types
    void Write(int value) {}
    void Write(float value) {}
    void Write(bool value) {}
    void Write(string value) {}
    void Write(vector value) {}
    void Write(IEntity value) {}
}