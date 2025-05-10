/**
 * @brief Network bit reader for deserializing data
 */

class ScriptBitReader
{
    // The data buffer
    protected ref array<byte> m_Data;
    
    // The current position in bits
    protected int m_BitPosition;
    
    /**
     * @brief Constructor
     */
    void ScriptBitReader()
    {
        m_Data = new array<byte>();
        m_BitPosition = 0;
    }
    
    /**
     * @brief Set the data to read from
     * @param data The data to read
     */
    void SetData(array<byte> data)
    {
        m_Data = data;
        m_BitPosition = 0;
    }
    
    /**
     * @brief Read a boolean value
     * @return The read value
     */
    bool ReadBool()
    {
        if (m_Data.Count() == 0)
            return false;
        
        int byteIndex = m_BitPosition / 8;
        int bitIndex = m_BitPosition % 8;
        
        if (byteIndex >= m_Data.Count())
            return false;
        
        bool value = (m_Data[byteIndex] & (1 << bitIndex)) != 0;
        m_BitPosition++;
        
        return value;
    }
    
    /**
     * @brief Read an integer value
     * @return The read value
     */
    int ReadInt()
    {
        int value = 0;
        
        // Read 4 bytes (32 bits)
        for (int i = 0; i < 4; i++)
        {
            if (m_BitPosition / 8 + i >= m_Data.Count())
                break;
            
            byte b = m_Data[m_BitPosition / 8 + i];
            value |= (b << (i * 8));
        }
        
        m_BitPosition += 32;
        return value;
    }
    
    /**
     * @brief Read a float value
     * @return The read value
     */
    float ReadFloat()
    {
        // Read the int bits and convert to float
        int intBits = ReadInt();
        return *((float*)&intBits);
    }
    
    /**
     * @brief Read a string value
     * @return The read value
     */
    string ReadString()
    {
        // Read the string length
        int length = ReadInt();
        if (length <= 0 || length > 10000) // Sanity check
            return "";
        
        // Read each character
        string result = "";
        for (int i = 0; i < length; i++)
        {
            byte charCode = ReadByte();
            result += ((char)charCode).ToString();
        }
        
        return result;
    }
    
    /**
     * @brief Read a single byte
     * @return The read byte
     */
    byte ReadByte()
    {
        int byteIndex = m_BitPosition / 8;
        if (byteIndex >= m_Data.Count())
            return 0;
        
        byte value = m_Data[byteIndex];
        m_BitPosition += 8;
        
        return value;
    }
    
    /**
     * @brief Reset the reader
     */
    void Reset()
    {
        m_BitPosition = 0;
    }
}