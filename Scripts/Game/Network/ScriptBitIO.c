// ScriptBitIO.c - Bit-level reader and writer classes for network serialization in ARMA Reforger

/**
 * @brief A class for writing binary data with bit-level precision
 */
class ScriptBitWriter
{
    // Internal buffer
    protected ref array<int> m_Buffer = new array<int>();
    protected int m_BitPosition = 0;
    
    /**
     * @brief Constructor
     */
    void ScriptBitWriter()
    {
        Reset();
    }
    
    /**
     * @brief Reset the writer to its initial state
     */
    void Reset()
    {
        m_Buffer.Clear();
        m_BitPosition = 0;
    }
    
    /**
     * @brief Write a boolean value
     * @param value The value to write
     */
    void WriteBool(bool value)
    {
        // Convert bool to int (0 or 1)
        int intValue = value ? 1 : 0;
        WriteIntBits(intValue, 1); // Use 1 bit
    }
    
    /**
     * @brief Write an integer value (32-bit)
     * @param value The value to write
     */
    void WriteInt(int value)
    {
        WriteIntBits(value, 32); // Use all 32 bits
    }
    
    /**
     * @brief Write a floating point value (32-bit)
     * @param value The value to write
     */
    void WriteFloat(float value)
    {
        // Use raw memory copy to convert float to int bits
        int intBits;
        WriteRaw(&value, 4); // 4 bytes = 32 bits
    }
    
    /**
     * @brief Write a string value
     * @param value The string to write
     */
    void WriteString(string value)
    {
        // Write string length first (up to 16 bits for length)
        int length = value.Length();
        WriteIntBits(length, 16);
        
        // Write each character as a 16-bit value
        for (int i = 0; i < length; i++)
        {
            int charValue = value.GetChar(i);
            WriteIntBits(charValue, 16);
        }
    }
    
    /**
     * @brief Write raw binary data
     * @param data Pointer to the data
     * @param size Size of the data in bytes
     */
    void WriteRaw(void* data, int size)
    {
        // Ensure byte alignment
        AlignToByte();
        
        // Get data as byte array
        array<int> bytes = new array<int>();
        for (int i = 0; i < size; i++)
        {
            int byte = ((int*)data)[i];
            bytes.Insert(byte);
        }
        
        // Write each byte
        for (int i = 0; i < bytes.Count(); i++)
        {
            WriteIntBits(bytes[i], 8);
        }
    }
    
    /**
     * @brief Write an integer value using a specific number of bits
     * @param value The value to write
     * @param numBits The number of bits to use
     */
    protected void WriteIntBits(int value, int numBits)
    {
        // Ensure we have enough space in the buffer
        while (m_Buffer.Count() * 32 < m_BitPosition + numBits)
        {
            m_Buffer.Insert(0);
        }
        
        // Write the bits
        for (int i = 0; i < numBits; i++)
        {
            // Get the bit value (0 or 1)
            int bitValue = (value >> (numBits - i - 1)) & 1;
            
            // Calculate buffer index and bit position
            int bufferIndex = m_BitPosition / 32;
            int bufferBitPos = m_BitPosition % 32;
            
            // Set the bit in the buffer
            if (bitValue == 1)
            {
                m_Buffer[bufferIndex] |= (1 << (31 - bufferBitPos));
            }
            
            m_BitPosition++;
        }
    }
    
    /**
     * @brief Align the bit position to the next byte boundary
     */
    protected void AlignToByte()
    {
        int remainder = m_BitPosition % 8;
        if (remainder > 0)
        {
            m_BitPosition += (8 - remainder);
        }
    }
    
    /**
     * @brief Get the size of the written data in bytes
     * @return The size in bytes
     */
    int GetSize()
    {
        return (m_BitPosition + 7) / 8; // Round up to nearest byte
    }
    
    /**
     * @brief Get a pointer to the data buffer
     * @return Pointer to the data buffer
     */
    void* GetData()
    {
        return m_Buffer;
    }
}

/**
 * @brief A class for reading binary data with bit-level precision
 */
class ScriptBitReader
{
    // Internal buffer
    protected ref array<int> m_Buffer = new array<int>();
    protected int m_BitPosition = 0;
    
    /**
     * @brief Constructor
     */
    void ScriptBitReader()
    {
        Reset();
    }
    
    /**
     * @brief Reset the reader to its initial state
     */
    void Reset()
    {
        m_Buffer.Clear();
        m_BitPosition = 0;
    }
    
    /**
     * @brief Set the data for reading
     * @param data Pointer to the data buffer
     * @param size Size of the data in bytes
     */
    void SetData(void* data, int size)
    {
        Reset();
        
        // Copy data into internal buffer
        int numInts = (size + 3) / 4; // Round up to nearest int
        for (int i = 0; i < numInts; i++)
        {
            if (i * 4 < size)
            {
                int value;
                if (i * 4 + 4 <= size)
                {
                    // Full int
                    value = ((int*)data)[i];
                }
                else
                {
                    // Partial int at the end
                    value = 0;
                    for (int j = 0; j < size - i * 4; j++)
                    {
                        int byteValue = ((int*)data)[i * 4 + j];
                        value |= (byteValue << (24 - j * 8));
                    }
                }
                m_Buffer.Insert(value);
            }
        }
    }
    
    /**
     * @brief Read a boolean value
     * @return The read value
     */
    bool ReadBool()
    {
        return ReadIntBits(1) != 0;
    }
    
    /**
     * @brief Read an integer value (32-bit)
     * @return The read value
     */
    int ReadInt()
    {
        return ReadIntBits(32);
    }
    
    /**
     * @brief Read a floating point value (32-bit)
     * @return The read value
     */
    float ReadFloat()
    {
        // Use raw memory copy to convert int bits to float
        AlignToByte();
        float value;
        int intBits = ReadIntBits(32);
        // Copy bits to float
        value = intBits; // Simple cast for now
        return value;
    }
    
    /**
     * @brief Read a string value
     * @return The read string
     */
    string ReadString()
    {
        // Read string length
        int length = ReadIntBits(16);
        
        // Read each character
        string result = "";
        for (int i = 0; i < length; i++)
        {
            int charValue = ReadIntBits(16);
            result += charValue.ToString();
        }
        
        return result;
    }
    
    /**
     * @brief Read raw binary data
     * @param data Buffer to read into
     * @param size The size of the data in bytes
     * @return Number of bytes read
     */
    int ReadRaw(void* data, int size)
    {
        // Ensure byte alignment
        AlignToByte();
        
        // Read each byte
        for (int i = 0; i < size; i++)
        {
            if (m_BitPosition / 8 < GetSize())
            {
                int byteValue = ReadIntBits(8);
                ((int*)data)[i] = byteValue;
            }
            else
            {
                return i; // End of data
            }
        }
        
        return size;
    }
    
    /**
     * @brief Read an integer value using a specific number of bits
     * @param numBits The number of bits to read
     * @return The read value
     */
    protected int ReadIntBits(int numBits)
    {
        int result = 0;
        
        // Read the bits
        for (int i = 0; i < numBits; i++)
        {
            // Calculate buffer index and bit position
            int bufferIndex = m_BitPosition / 32;
            int bufferBitPos = m_BitPosition % 32;
            
            // Check if we have enough data
            if (bufferIndex >= m_Buffer.Count())
            {
                // Not enough data, return what we have
                return result;
            }
            
            // Get the bit from the buffer
            int bitValue = (m_Buffer[bufferIndex] >> (31 - bufferBitPos)) & 1;
            
            // Add the bit to the result
            result = (result << 1) | bitValue;
            
            m_BitPosition++;
        }
        
        return result;
    }
    
    /**
     * @brief Align the bit position to the next byte boundary
     */
    protected void AlignToByte()
    {
        int remainder = m_BitPosition % 8;
        if (remainder > 0)
        {
            m_BitPosition += (8 - remainder);
        }
    }
    
    /**
     * @brief Get the size of the data in bytes
     * @return The size in bytes
     */
    int GetSize()
    {
        return m_Buffer.Count() * 4; // Each int is 4 bytes
    }
}