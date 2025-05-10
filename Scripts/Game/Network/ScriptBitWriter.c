// ScriptBitWriter.c - Network data writer for ARMA Reforger
// This class handles writing binary data for network transmission

class ScriptBitWriter
{
    // Buffer size in bytes
    protected const int DEFAULT_BUFFER_SIZE = 1024;
    
    // Data buffer
    protected void* m_Buffer;
    
    // Current write position in bits
    protected int m_BitPosition;
    
    // Current buffer size in bytes
    protected int m_BufferSize;
    
    // Constructor
    void ScriptBitWriter()
    {
        m_Buffer = malloc(DEFAULT_BUFFER_SIZE);
        m_BitPosition = 0;
        m_BufferSize = DEFAULT_BUFFER_SIZE;
    }
    
    // Destructor
    void ~ScriptBitWriter()
    {
        if (m_Buffer)
        {
            free(m_Buffer);
            m_Buffer = null;
        }
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
        // Ensure buffer has enough space
        EnsureSize(m_BitPosition + 32);
        
        // Write the value
        int bytePosition = m_BitPosition >> 3; // Divide by 8
        int bitOffset = m_BitPosition & 7;     // Modulo 8
        
        if (bitOffset == 0)
        {
            // Aligned write (faster)
            int* dest = (int*)(((byte*)m_Buffer) + bytePosition);
            *dest = value;
        }
        else
        {
            // Unaligned write (slower)
            byte* dest = ((byte*)m_Buffer) + bytePosition;
            
            // Write byte by byte with bit shifting
            dest[0] |= (value & 0xFF) << bitOffset;
            dest[1] = (value >> (8 - bitOffset)) & 0xFF;
            dest[2] = (value >> (16 - bitOffset)) & 0xFF;
            dest[3] = (value >> (24 - bitOffset)) & 0xFF;
            
            if (bitOffset > 24)
            {
                dest[4] = (value >> (32 - bitOffset)) & 0xFF;
            }
        }
        
        // Update bit position
        m_BitPosition += 32;
    }
    
    /**
     * @brief Write a boolean value
     * @param value The value to write
     */
    void WriteBool(bool value)
    {
        // Ensure buffer has enough space
        EnsureSize(m_BitPosition + 1);
        
        // Write the value
        int bytePosition = m_BitPosition >> 3; // Divide by 8
        int bitOffset = m_BitPosition & 7;     // Modulo 8
        
        byte* dest = ((byte*)m_Buffer) + bytePosition;
        
        if (value)
        {
            *dest |= (1 << bitOffset); // Set the bit
        }
        else
        {
            *dest &= ~(1 << bitOffset); // Clear the bit
        }
        
        // Update bit position
        m_BitPosition += 1;
    }
    
    /**
     * @brief Write a float value
     * @param value The value to write
     */
    void WriteFloat(float value)
    {
        // Reinterpret float as int and write it
        int intValue = *((int*)&value);
        WriteInt(intValue);
    }
    
    /**
     * @brief Write a string value
     * @param value The value to write
     */
    void WriteString(string value)
    {
        // Write string length first
        int length = value.Length();
        WriteInt(length);
        
        // For empty string, we're done
        if (length == 0)
            return;
            
        // Write string characters
        for (int i = 0; i < length; i++)
        {
            WriteInt(value[i]); // Write each character as an int
        }
    }
    
    /**
     * @brief Write raw data directly
     * @param data The data to write
     * @param size The size of the data in bytes
     */
    void WriteRaw(void* data, int size)
    {
        // If we're not byte-aligned, align first
        AlignToByte();
        
        // Ensure buffer has enough space
        EnsureSize(m_BitPosition + (size * 8));
        
        // Copy the data
        int bytePosition = m_BitPosition >> 3; // Divide by 8
        byte* dest = ((byte*)m_Buffer) + bytePosition;
        memcpy(dest, data, size);
        
        // Update bit position
        m_BitPosition += (size * 8);
    }
    
    //------------------------------------------
    // Utility methods
    //------------------------------------------
    
    /**
     * @brief Ensure the buffer has enough space
     * @param bitSize Required bit size
     */
    protected void EnsureSize(int bitSize)
    {
        // Convert bit size to byte size (round up)
        int requiredBytes = (bitSize + 7) >> 3; // Divide by 8 and round up
        
        // Check if we need to resize
        if (requiredBytes <= m_BufferSize)
            return;
            
        // Calculate new size (double until it's enough)
        int newSize = m_BufferSize;
        while (newSize < requiredBytes)
        {
            newSize *= 2;
        }
        
        // Allocate new buffer
        void* newBuffer = malloc(newSize);
        
        // Copy old data
        memcpy(newBuffer, m_Buffer, m_BufferSize);
        
        // Free old buffer
        free(m_Buffer);
        
        // Update buffer and size
        m_Buffer = newBuffer;
        m_BufferSize = newSize;
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
     * @brief Reset the writer
     */
    void Reset()
    {
        // Clear the buffer
        memset(m_Buffer, 0, m_BufferSize);
        
        // Reset bit position
        m_BitPosition = 0;
    }
    
    /**
     * @brief Get the size of the written data in bytes
     * @return The size in bytes
     */
    int GetSize()
    {
        return (m_BitPosition + 7) >> 3; // Divide by 8 and round up
    }
    
    /**
     * @brief Get the data buffer
     * @return Pointer to the data buffer
     */
    void* GetData()
    {
        return m_Buffer;
    }
}