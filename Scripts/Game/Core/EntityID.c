// EntityID.c - Entity ID class for ARMA Reforger
// This class provides a unique identifier for entities

/**
 * @brief Class representing a unique entity ID
 */
class EntityID
{
    // ID value (unique for each entity)
    protected int m_Value;
    
    // Static counter for generating unique IDs
    private static int s_NextID = 1;
    
    // Constructor
    void EntityID(int value = 0)
    {
        if (value == 0)
        {
            // Generate a new unique ID
            m_Value = s_NextID++;
        }
        else
        {
            // Use the provided ID
            m_Value = value;
        }
    }
    
    //------------------------------------------
    // Getter and setter
    //------------------------------------------
    
    /**
     * @brief Get the ID value
     * @return The ID value
     */
    int GetValue()
    {
        return m_Value;
    }
    
    /**
     * @brief Set the ID value
     * @param value The ID value
     */
    void SetValue(int value)
    {
        m_Value = value;
    }
    
    //------------------------------------------
    // Comparison operators
    //------------------------------------------
    
    /**
     * @brief Equality operator
     * @param other The other entity ID
     * @return True if equal, false otherwise
     */
    bool operator ==(EntityID other)
    {
        if (!other)
            return false;
            
        return m_Value == other.GetValue();
    }
    
    /**
     * @brief Inequality operator
     * @param other The other entity ID
     * @return True if not equal, false otherwise
     */
    bool operator !=(EntityID other)
    {
        return !(this == other);
    }
    
    /**
     * @brief Less than operator
     * @param other The other entity ID
     * @return True if this ID is less than the other, false otherwise
     */
    bool operator <(EntityID other)
    {
        if (!other)
            return false;
            
        return m_Value < other.GetValue();
    }
    
    /**
     * @brief Greater than operator
     * @param other The other entity ID
     * @return True if this ID is greater than the other, false otherwise
     */
    bool operator >(EntityID other)
    {
        if (!other)
            return true;
            
        return m_Value > other.GetValue();
    }
    
    /**
     * @brief Convert to string
     * @return String representation of the ID
     */
    string ToString()
    {
        return m_Value.ToString();
    }
}