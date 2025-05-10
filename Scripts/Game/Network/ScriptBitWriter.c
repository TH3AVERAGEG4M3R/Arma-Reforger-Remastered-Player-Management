/**
 * @brief Network bit writer for serializing data
 */

class ScriptBitWriter
{
    // The data buffer
    protected ref array<byte> m_Data = new array<byte>();
    
    // The current position in bits
    protected int m_BitPosition;
    
    /**
     * @brief Constructor
     */
    void ScriptBitWriter()
    {
        m_BitPosition = 0;
    }
    
    /**
     * @brief Write a boolean value
     * @param value The value to write
     */
    void WriteBool(bool value)
    {
        // Add a new byte if needed
        if (m_BitPosition % 8 == 0)
            m_Data.Insert(0);
        
        // Set the bit in the current byte
        int byteIndex = m_BitPosition / 8;
        int bitIndex = m_BitPosition % 8;
        
        if (value)
            m_Data[byteIndex] |= (1 << bitIndex);
        
        m_BitPosition++;
    }
    
    /**
     * @brief Write an integer value
     * @param value The value to write
     */
    void WriteInt(int value)
    {
        // Write the value as 4 bytes (32 bits)
        for (int i = 0; i < 4; i++)
        {
            byte b = (value >> (i * 8)) & 0xFF;
            m_Data.Insert(b);
        }
        
        m_BitPosition += 32;
    }
    
    /**
     * @brief Write a float value
     * @param value The value to write
     */
    void WriteFloat(float value)
    {
        // Convert float to int bits and write those
        int intBits = *((int*)&value);
        WriteInt(intBits);
    }
    
    /**
     * @brief Write a string value
     * @param value The value to write
     */
    void WriteString(string value)
    {
        // Write the string length
        int length = value.Length();
        WriteInt(length);
        
        // Write each character
        for (int i = 0; i < length; i++)
        {
            int charCode = value[i]; // Get ASCII code of character
            WriteByte(charCode);
        }
    }
    
    /**
     * @brief Write a single byte
     * @param value The byte to write
     */
    void WriteByte(byte value)
    {
        m_Data.Insert(value);
        m_BitPosition += 8;
    }
    
    /**
     * @brief Get the serialized data
     * @return The serialized data as a byte array
     */
    array<byte> GetData()
    {
        return m_Data;
    }
    
    /**
     * @brief Reset the writer
     */
    void Reset()
    {
        m_Data.Clear();
        m_BitPosition = 0;
    }
}