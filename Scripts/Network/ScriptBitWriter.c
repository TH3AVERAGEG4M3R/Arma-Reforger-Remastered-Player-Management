// ScriptBitWriter for ARMA Reforger networking

class ScriptBitWriter
{
    void ScriptBitWriter() {}
    
    void WriteInt(int value) {}
    void WriteFloat(float value) {}
    void WriteBool(bool value) {}
    void WriteString(string value) {}
    void WriteVector(vector value) {}
    void WriteEntity(IEntity entity) {}
}

class ScriptBitReader
{
    void ScriptBitReader() {}
    
    int ReadInt() { return 0; }
    float ReadFloat() { return 0.0; }
    bool ReadBool() { return false; }
    string ReadString() { return ""; }
    vector ReadVector() { return "0 0 0"; }
    IEntity ReadEntity() { return null; }
}