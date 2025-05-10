/**
 * @brief Input Device class for handling input devices in ARMA Reforger
 */
class InputDevice
{
    // Device type enum
    enum EDeviceType
    {
        KEYBOARD,
        MOUSE,
        GAMEPAD,
        TOUCH,
        UNKNOWN
    }
    
    // Device type
    protected EDeviceType m_DeviceType;
    
    // Device ID or index
    protected int m_DeviceID;
    
    // Device name
    protected string m_DeviceName;
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Constructor with device type
     * @param type The device type
     */
    void InputDevice(EDeviceType type = EDeviceType.UNKNOWN)
    {
        m_DeviceType = type;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the device ID
     * @param id The device ID
     */
    void SetDeviceID(int id)
    {
        m_DeviceID = id;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the device name
     * @param name The device name
     */
    void SetDeviceName(string name)
    {
        m_DeviceName = name;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the device type
     * @return The device type
     */
    EDeviceType GetDeviceType()
    {
        return m_DeviceType;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the device ID
     * @return The device ID
     */
    int GetDeviceID()
    {
        return m_DeviceID;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the device name
     * @return The device name
     */
    string GetDeviceName()
    {
        return m_DeviceName;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Check if this is a keyboard device
     * @return True if keyboard
     */
    bool IsKeyboard()
    {
        return m_DeviceType == EDeviceType.KEYBOARD;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Check if this is a mouse device
     * @return True if mouse
     */
    bool IsMouse()
    {
        return m_DeviceType == EDeviceType.MOUSE;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Check if this is a gamepad device
     * @return True if gamepad
     */
    bool IsGamepad()
    {
        return m_DeviceType == EDeviceType.GAMEPAD;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Check if this is a touch device
     * @return True if touch
     */
    bool IsTouch()
    {
        return m_DeviceType == EDeviceType.TOUCH;
    }
}