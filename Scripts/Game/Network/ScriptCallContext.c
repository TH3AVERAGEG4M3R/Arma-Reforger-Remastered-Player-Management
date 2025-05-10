/**
 * @brief Network script call context for RPC calls
 */

#include "ScriptBitWriter.c"
#include "ScriptBitReader.c"

class ScriptCallContext
{
    // The internal bit writer for serializing data
    protected ref ScriptBitWriter m_Writer;
    
    // The internal bit reader for deserializing data
    protected ref ScriptBitReader m_Reader;
    
    // Whether this context is for writing (true) or reading (false)
    protected bool m_IsWriter;
    
    /**
     * @brief Constructor
     */
    void ScriptCallContext()
    {
        m_Writer = new ScriptBitWriter();
        m_Reader = new ScriptBitReader();
        m_IsWriter = true; // Default to writer mode
    }
    
    /**
     * @brief Set the context to writer mode
     */
    void SetWriter()
    {
        m_IsWriter = true;
    }
    
    /**
     * @brief Set the context to reader mode
     */
    void SetReader(array<byte> data)
    {
        m_IsWriter = false;
        m_Reader.SetData(data);
    }
    
    /**
     * @brief Write a boolean value
     * @param value The value to write
     */
    void Write(bool value)
    {
        if (m_IsWriter)
            m_Writer.WriteBool(value);
    }
    
    /**
     * @brief Write an integer value
     * @param value The value to write
     */
    void Write(int value)
    {
        if (m_IsWriter)
            m_Writer.WriteInt(value);
    }
    
    /**
     * @brief Write a float value
     * @param value The value to write
     */
    void Write(float value)
    {
        if (m_IsWriter)
            m_Writer.WriteFloat(value);
    }
    
    /**
     * @brief Write a string value
     * @param value The value to write
     */
    void Write(string value)
    {
        if (m_IsWriter)
            m_Writer.WriteString(value);
    }
    
    /**
     * @brief Write a vector value
     * @param value The value to write
     */
    void Write(vector value)
    {
        if (m_IsWriter)
        {
            m_Writer.WriteFloat(value[0]);
            m_Writer.WriteFloat(value[1]);
            m_Writer.WriteFloat(value[2]);
        }
    }
    
    /**
     * @brief Read a boolean value
     * @return The read value
     */
    bool ReadBool()
    {
        if (!m_IsWriter)
            return m_Reader.ReadBool();
        
        return false;
    }
    
    /**
     * @brief Read an integer value
     * @return The read value
     */
    int ReadInt()
    {
        if (!m_IsWriter)
            return m_Reader.ReadInt();
        
        return 0;
    }
    
    /**
     * @brief Read a float value
     * @return The read value
     */
    float ReadFloat()
    {
        if (!m_IsWriter)
            return m_Reader.ReadFloat();
        
        return 0.0;
    }
    
    /**
     * @brief Read a string value
     * @return The read value
     */
    string ReadString()
    {
        if (!m_IsWriter)
            return m_Reader.ReadString();
        
        return "";
    }
    
    /**
     * @brief Read a vector value
     * @return The read value
     */
    vector ReadVector()
    {
        if (!m_IsWriter)
        {
            float x = m_Reader.ReadFloat();
            float y = m_Reader.ReadFloat();
            float z = m_Reader.ReadFloat();
            return Vector(x, y, z);
        }
        
        return Vector(0, 0, 0);
    }
    
    /**
     * @brief Get the serialized data
     * @return The serialized data as a byte array
     */
    array<byte> GetData()
    {
        if (m_IsWriter)
            return m_Writer.GetData();
        
        return null;
    }
}