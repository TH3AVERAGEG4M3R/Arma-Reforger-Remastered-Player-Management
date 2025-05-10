/**
 * @brief Class for managing RPC call contexts in ARMA Reforger
 */
class ScriptCallContext
{
    // Internal data writer
    protected ref ScriptBitWriter m_Writer;
    
    // Constructor
    void ScriptCallContext()
    {
        m_Writer = new ScriptBitWriter();
    }
    
    /**
     * @brief Write a value to the RPC context
     * @param value The value to write (can be int, string, float, bool, vector, etc.)
     */
    void Write(typename value)
    {
        // Implementation will be provided by ARMA Reforger engine
    }
    
    /**
     * @brief Write an int value
     * @param value The int value to write
     */
    void Write(int value)
    {
        // Implementation will be provided by ARMA Reforger engine
    }
    
    /**
     * @brief Write a float value
     * @param value The float value to write
     */
    void Write(float value)
    {
        // Implementation will be provided by ARMA Reforger engine
    }
    
    /**
     * @brief Write a string value
     * @param value The string value to write
     */
    void Write(string value)
    {
        // Implementation will be provided by ARMA Reforger engine
    }
    
    /**
     * @brief Write a bool value
     * @param value The bool value to write
     */
    void Write(bool value)
    {
        // Implementation will be provided by ARMA Reforger engine
    }
    
    /**
     * @brief Write a vector value
     * @param value The vector value to write
     */
    void Write(vector value)
    {
        // Implementation will be provided by ARMA Reforger engine
    }
    
    /**
     * @brief Write an entity
     * @param value The entity to write
     */
    void Write(IEntity value)
    {
        // Implementation will be provided by ARMA Reforger engine
    }
    
    /**
     * @brief Read a value from the RPC context
     * @return The read value of the specified type
     */
    typename Read()
    {
        // Implementation will be provided by ARMA Reforger engine
        return typename.Empty;
    }
    
    /**
     * @brief Read an int value
     * @return The read int value
     */
    int ReadInt()
    {
        // Implementation will be provided by ARMA Reforger engine
        return 0;
    }
    
    /**
     * @brief Read an int value with output parameter
     * @param value Out parameter to store the int value
     * @return True if read successful
     */
    bool Read(out int value)
    {
        value = ReadInt();
        return true;
    }
    
    /**
     * @brief Read a float value
     * @return The read float value
     */
    float ReadFloat()
    {
        // Implementation will be provided by ARMA Reforger engine
        return 0.0;
    }
    
    /**
     * @brief Read a float value with output parameter
     * @param value Out parameter to store the float value
     * @return True if read successful
     */
    bool Read(out float value)
    {
        value = ReadFloat();
        return true;
    }
    
    /**
     * @brief Read a string value
     * @return The read string value
     */
    string ReadString()
    {
        // Implementation will be provided by ARMA Reforger engine
        return "";
    }
    
    /**
     * @brief Read a string value with output parameter
     * @param value Out parameter to store the string value
     * @return True if read successful
     */
    bool Read(out string value)
    {
        value = ReadString();
        return true;
    }
    
    /**
     * @brief Read a bool value
     * @return The read bool value
     */
    bool ReadBool()
    {
        // Implementation will be provided by ARMA Reforger engine
        return false;
    }
    
    /**
     * @brief Read a bool value with output parameter
     * @param value Out parameter to store the bool value
     * @return True if read successful
     */
    bool Read(out bool value)
    {
        value = ReadBool();
        return true;
    }
    
    /**
     * @brief Read a vector value
     * @return The read vector value
     */
    vector ReadVector()
    {
        // Implementation will be provided by ARMA Reforger engine
        return vector.Zero;
    }
    
    /**
     * @brief Read a vector value with output parameter
     * @param value Out parameter to store the vector value
     * @return True if read successful
     */
    bool Read(out vector value)
    {
        value = ReadVector();
        return true;
    }
    
    /**
     * @brief Read an entity
     * @return The read entity
     */
    IEntity ReadEntity()
    {
        // Implementation will be provided by ARMA Reforger engine
        return null;
    }
    
    /**
     * @brief Read an entity with output parameter
     * @param value Out parameter to store the entity
     * @return True if read successful
     */
    bool Read(out IEntity value)
    {
        value = ReadEntity();
        return true;
    }
}