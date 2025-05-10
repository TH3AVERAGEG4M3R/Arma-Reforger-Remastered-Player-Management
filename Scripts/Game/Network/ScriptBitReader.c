/**
 * @brief Class for reading bit-packed data from network transmissions in ARMA Reforger
 */
class ScriptBitReader
{
    /**
     * @brief Read an int value
     * @param value Out parameter to store the int value
     * @return True if successful
     */
    bool ReadInt(out int value)
    {
        value = 0;
        return true;
    }
    
    /**
     * @brief Read a float value
     * @param value Out parameter to store the float value
     * @return True if successful
     */
    bool ReadFloat(out float value)
    {
        value = 0.0;
        return true;
    }
    
    /**
     * @brief Read a string value
     * @param value Out parameter to store the string value
     * @return True if successful
     */
    bool ReadString(out string value)
    {
        value = "";
        return true;
    }
    
    /**
     * @brief Read a bool value
     * @param value Out parameter to store the bool value
     * @return True if successful
     */
    bool ReadBool(out bool value)
    {
        value = false;
        return true;
    }
    
    /**
     * @brief Read a vector value
     * @param value Out parameter to store the vector value
     * @return True if successful
     */
    bool ReadVector(out vector value)
    {
        value = vector.Zero;
        return true;
    }
    
    /**
     * @brief Read an entity
     * @param value Out parameter to store the entity
     * @return True if successful
     */
    bool ReadEntity(out IEntity value)
    {
        value = null;
        return true;
    }
}