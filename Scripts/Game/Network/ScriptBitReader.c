// ScriptBitReader.c - Network data reader for ARMA Reforger
// This class handles reading binary data received over the network

class ScriptBitReader
{
    // Data buffer
    protected void* m_Buffer;
    
    // Current read position in bits
    protected int m_BitPosition;
    
    // Current buffer size in bytes
    protected int m_BufferSize;
    
    // Constructor
    void ScriptBitReader()
    {
        m_Buffer = null;
        m_BitPosition = 0;
        m_BufferSize = 0;
    }
    
    // Destructor
    void ~ScriptBitReader()
    {
        // We don't free the buffer here as it might be owned by someone else
        m_Buffer = null;
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
        // Check if we have enough data
        if (!CanRead(32))
        {
            Print("ScriptBitReader: Trying to read past the end of the buffer!");
            return 0;
        }
        
        // Read the value
        int bytePosition = m_BitPosition >> 3; // Divide by 8
        int bitOffset = m_BitPosition & 7;     // Modulo 8
        
        int value;
        
        if (bitOffset == 0)
        {
            // Aligned read (faster)
            int* src = (int*)(((byte*)m_Buffer) + bytePosition);
            value = *src;
        }
        else
        {
            // Unaligned read (slower)
            byte* src = ((byte*)m_Buffer) + bytePosition;
            
            // Read byte by byte with bit shifting
            value = ((src[0] >> bitOffset) |
                    (src[1] << (8 - bitOffset)) |
                    (src[2] << (16 - bitOffset)) |
                    (src[3] << (24 - bitOffset)));
            
            if (bitOffset > 24)
            {
                value |= (src[4] << (32 - bitOffset));
            }
        }
        
        // Update bit position
        m_BitPosition += 32;
        
        return value;
    }
    
    /**
     * @brief Read a boolean value
     * @return The read value
     */
    bool ReadBool()
    {
        // Check if we have enough data
        if (!CanRead(1))
        {
            Print("ScriptBitReader: Trying to read past the end of the buffer!");
            return false;
        }
        
        // Read the value
        int bytePosition = m_BitPosition >> 3; // Divide by 8
        int bitOffset = m_BitPosition & 7;     // Modulo 8
        
        byte* src = ((byte*)m_Buffer) + bytePosition;
        bool value = (*src & (1 << bitOffset)) != 0;
        
        // Update bit position
        m_BitPosition += 1;
        
        return value;
    }
    
    /**
     * @brief Read a float value
     * @return The read value
     */
    float ReadFloat()
    {
        // Read as int and reinterpret
        int intValue = ReadInt();
        return *((float*)&intValue);
    }
    
    /**
     * @brief Read a string value
     * @return The read value
     */
    string ReadString()
    {
        // Read string length first
        int length = ReadInt();
        
        // For empty string, return early
        if (length == 0)
            return "";
            
        // Read characters
        string result = "";
        for (int i = 0; i < length; i++)
        {
            int charValue = ReadInt();
            result += (char)charValue;
        }
        
        return result;
    }
    
    /**
     * @brief Read raw data directly
     * @param data Buffer to read into
     * @param size The size of the data in bytes
     * @return Number of bytes read
     */
    int ReadRaw(void* data, int size)
    {
        // If we're not byte-aligned, align first
        AlignToByte();
        
        // Calculate available bytes
        int availableBytes = ((m_BufferSize * 8) - m_BitPosition) >> 3;
        int bytesToRead = Math.Min(size, availableBytes);
        
        // If no bytes to read, return early
        if (bytesToRead <= 0)
            return 0;
            
        // Copy the data
        int bytePosition = m_BitPosition >> 3; // Divide by 8
        byte* src = ((byte*)m_Buffer) + bytePosition;
        memcpy(data, src, bytesToRead);
        
        // Update bit position
        m_BitPosition += (bytesToRead * 8);
        
        return bytesToRead;
    }
    
    //------------------------------------------
    // Utility methods
    //------------------------------------------
    
    /**
     * @brief Check if we can read the requested number of bits
     * @param bitCount Number of bits to read
     * @return True if we can read, false otherwise
     */
    protected bool CanRead(int bitCount)
    {
        return m_Buffer && (m_BitPosition + bitCount <= m_BufferSize * 8);
    }
    
    /**
     * @brief Align the bit position to the next byte boundary
     */
    void AlignToByte()
    {
        if (m_BitPosition & 7) // If not aligned
        {
            m_BitPosition = (m_BitPosition + 7) & ~7; // Round up to next multiple of 8
        }
    }
    
    /**
     * @brief Reset the reader
     */
    void Reset()
    {
        m_BitPosition = 0;
    }
    
    /**
     * @brief Set the data buffer for reading
     * @param data Pointer to the data buffer
     * @param size Size of the buffer in bytes
     */
    void SetData(void* data, int size)
    {
        m_Buffer = data;
        m_BufferSize = size;
        m_BitPosition = 0;
    }
    
    /**
     * @brief Get the current read position in bits
     * @return Current position in bits
     */
    int GetBitPosition()
    {
        return m_BitPosition;
    }
    
    /**
     * @brief Set the read position in bits
     * @param position New position in bits
     */
    void SetBitPosition(int position)
    {
        // Ensure the position is valid
        if (position < 0)
        {
            position = 0;
        }
        else if (position > m_BufferSize * 8)
        {
            position = m_BufferSize * 8;
        }
        
        m_BitPosition = position;
    }
    
    /**
     * @brief Check if we reached the end of the buffer
     * @return True if at end, false otherwise
     */
    bool IsAtEnd()
    {
        return m_BitPosition >= m_BufferSize * 8;
    }
}