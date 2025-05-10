// InputDevice.c - Input device representation for ARMA Reforger
// This class defines the properties and methods for input devices

/**
 * @brief Enum for input device types
 */
enum EInputDeviceType
{
    KEYBOARD = 0,
    MOUSE = 1,
    GAMEPAD = 2,
    TOUCH = 3,
    OTHER = 4
}

/**
 * @brief Class representing an input device
 */
class InputDevice
{
    // The type of input device
    protected EInputDeviceType m_Type;
    
    // Device identifier
    protected int m_DeviceID;
    
    // Whether the device is connected
    protected bool m_IsConnected;
    
    // Device name
    protected string m_Name;
    
    // Constructor
    void InputDevice(EInputDeviceType type = EInputDeviceType.OTHER, int deviceID = 0)
    {
        m_Type = type;
        m_DeviceID = deviceID;
        m_IsConnected = true;
        m_Name = "Unknown Device";
        
        // Set default name based on type
        switch (type)
        {
            case EInputDeviceType.KEYBOARD:
                m_Name = "Keyboard";
                break;
                
            case EInputDeviceType.MOUSE:
                m_Name = "Mouse";
                break;
                
            case EInputDeviceType.GAMEPAD:
                m_Name = "Gamepad " + deviceID;
                break;
                
            case EInputDeviceType.TOUCH:
                m_Name = "Touch";
                break;
        }
    }
    
    //------------------------------------------
    // Getters and setters
    //------------------------------------------
    
    /**
     * @brief Get the device type
     * @return The device type
     */
    EInputDeviceType GetType()
    {
        return m_Type;
    }
    
    /**
     * @brief Set the device type
     * @param type The device type
     */
    void SetType(EInputDeviceType type)
    {
        m_Type = type;
    }
    
    /**
     * @brief Get the device ID
     * @return The device ID
     */
    int GetDeviceID()
    {
        return m_DeviceID;
    }
    
    /**
     * @brief Set the device ID
     * @param deviceID The device ID
     */
    void SetDeviceID(int deviceID)
    {
        m_DeviceID = deviceID;
    }
    
    /**
     * @brief Check if the device is connected
     * @return True if connected, false otherwise
     */
    bool IsConnected()
    {
        return m_IsConnected;
    }
    
    /**
     * @brief Set the connected state
     * @param isConnected The connected state
     */
    void SetConnected(bool isConnected)
    {
        m_IsConnected = isConnected;
    }
    
    /**
     * @brief Get the device name
     * @return The device name
     */
    string GetName()
    {
        return m_Name;
    }
    
    /**
     * @brief Set the device name
     * @param name The device name
     */
    void SetName(string name)
    {
        m_Name = name;
    }
    
    /**
     * @brief Check if this device is of the specified type
     * @param type The type to check
     * @return True if the device is of the specified type, false otherwise
     */
    bool IsType(EInputDeviceType type)
    {
        return m_Type == type;
    }
}