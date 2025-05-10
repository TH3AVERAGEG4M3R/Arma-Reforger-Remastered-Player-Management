// ScriptCallContext.c - Network call context for ARMA Reforger
// This class handles serialization and deserialization of RPC data

class ScriptCallContext
{
    // Binary data for reading/writing
    protected ref ScriptBitWriter m_Writer;
    protected ref ScriptBitReader m_Reader;
    
    // Constructor
    void ScriptCallContext()
    {
        m_Writer = new ScriptBitWriter();
        m_Reader = new ScriptBitReader();
    }
    
    //------------------------------------------
    // Writer methods
    //------------------------------------------
    
    /**
     * @brief Write an integer value
     * @param value The value to write
     */
    void WriteInt(int value)
    {
        m_Writer.WriteInt(value);
    }
    
    /**
     * @brief Write a boolean value
     * @param value The value to write
     */
    void WriteBool(bool value)
    {
        m_Writer.WriteBool(value);
    }
    
    /**
     * @brief Write a float value
     * @param value The value to write
     */
    void WriteFloat(float value)
    {
        m_Writer.WriteFloat(value);
    }
    
    /**
     * @brief Write a string value
     * @param value The value to write
     */
    void WriteString(string value)
    {
        m_Writer.WriteString(value);
    }
    
    /**
     * @brief Write an entity ID
     * @param entity The entity to write the ID of
     */
    void Write(IEntity entity)
    {
        if (entity)
        {
            m_Writer.WriteBool(true);
            m_Writer.WriteInt(entity.GetID());
        }
        else
        {
            m_Writer.WriteBool(false);
        }
    }
    
    /**
     * @brief Write a vector value
     * @param value The value to write
     */
    void WriteVector(vector value)
    {
        m_Writer.WriteFloat(value[0]);
        m_Writer.WriteFloat(value[1]);
        m_Writer.WriteFloat(value[2]);
    }
    
    /**
     * @brief Write raw data directly
     * @param data The data to write
     * @param size The size of the data in bytes
     */
    void WriteRaw(void* data, int size)
    {
        m_Writer.WriteRaw(data, size);
    }
    
    //------------------------------------------
    // Reader methods
    //------------------------------------------
    
    /**
     * @brief Read an integer value
     * @return The read value
     */
    int ReadInt()
    {
        return m_Reader.ReadInt();
    }
    
    /**
     * @brief Read a boolean value
     * @return The read value
     */
    bool ReadBool()
    {
        return m_Reader.ReadBool();
    }
    
    /**
     * @brief Read a float value
     * @return The read value
     */
    float ReadFloat()
    {
        return m_Reader.ReadFloat();
    }
    
    /**
     * @brief Read a string value
     * @return The read value
     */
    string ReadString()
    {
        return m_Reader.ReadString();
    }
    
    /**
     * @brief Read an entity
     * @return The read entity, or null if the entity was null or not found
     */
    IEntity ReadEntity()
    {
        bool hasEntity = m_Reader.ReadBool();
        if (!hasEntity)
            return null;
            
        int entityID = m_Reader.ReadInt();
        return GetGame().GetWorld().FindEntityByID(entityID);
    }
    
    /**
     * @brief Read a vector value
     * @return The read value
     */
    vector ReadVector()
    {
        float x = m_Reader.ReadFloat();
        float y = m_Reader.ReadFloat();
        float z = m_Reader.ReadFloat();
        return Vector(x, y, z);
    }
    
    /**
     * @brief Read raw data directly
     * @param data Buffer to read into
     * @param size The size of the data in bytes
     * @return Number of bytes read
     */
    int ReadRaw(void* data, int size)
    {
        return m_Reader.ReadRaw(data, size);
    }
    
    //------------------------------------------
    // Utility methods
    //------------------------------------------
    
    /**
     * @brief Get the size of the written data in bytes
     * @return The size in bytes
     */
    int GetSize()
    {
        return m_Writer.GetSize();
    }
    
    /**
     * @brief Reset the reader and writer
     */
    void Reset()
    {
        m_Writer.Reset();
        m_Reader.Reset();
    }
    
    /**
     * @brief Get the raw data buffer
     * @return Pointer to the data buffer
     */
    void* GetData()
    {
        return m_Writer.GetData();
    }
    
    /**
     * @brief Set the data for reading
     * @param data Pointer to the data buffer
     * @param size Size of the data in bytes
     */
    void SetData(void* data, int size)
    {
        m_Reader.SetData(data, size);
    }
}