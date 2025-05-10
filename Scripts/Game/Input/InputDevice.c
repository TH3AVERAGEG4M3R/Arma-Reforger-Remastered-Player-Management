// InputDevice.c - Input device base class for ARMA Reforger
// This class represents an abstract input device

enum EInputDeviceType
{
    KEYBOARD,
    MOUSE,
    GAMEPAD
}

class InputDevice
{
    // Type of the input device
    protected EInputDeviceType m_Type;
    
    // Device identifier
    protected int m_DeviceID;
    
    // Is the device connected/available?
    protected bool m_IsConnected;
    
    // Constructor
    void InputDevice(EInputDeviceType type = EInputDeviceType.KEYBOARD, int deviceID = 0)
    {
        m_Type = type;
        m_DeviceID = deviceID;
        m_IsConnected = true;
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
     * @brief Get the device ID
     * @return The device ID
     */
    int GetDeviceID()
    {
        return m_DeviceID;
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
    
    //------------------------------------------
    // Virtual methods to be overridden by derived classes
    //------------------------------------------
    
    /**
     * @brief Update the device state
     * Should be called every frame to update the device state
     */
    void Update()
    {
        // Base implementation does nothing
    }
}

//------------------------------------------
// Derived classes for specific input devices
//------------------------------------------

class KeyboardDevice : InputDevice
{
    // States of all keys (pressed or not)
    protected array<bool> m_KeyStates;
    
    // Constructor
    void KeyboardDevice(int deviceID = 0)
    {
        // Call base constructor with keyboard type
        InputDevice(EInputDeviceType.KEYBOARD, deviceID);
        
        // Initialize key states (common keyboard has 256 keys)
        m_KeyStates = new array<bool>();
        for (int i = 0; i < 256; i++)
        {
            m_KeyStates.Insert(false);
        }
    }
    
    /**
     * @brief Check if a key is pressed
     * @param keyCode The key code to check
     * @return True if pressed, false otherwise
     */
    bool IsKeyPressed(int keyCode)
    {
        // Ensure keyCode is in valid range
        if (keyCode < 0 || keyCode >= m_KeyStates.Count())
            return false;
            
        return m_KeyStates[keyCode];
    }
    
    /**
     * @brief Set the state of a key
     * @param keyCode The key code to set
     * @param isPressed The pressed state
     */
    void SetKeyState(int keyCode, bool isPressed)
    {
        // Ensure keyCode is in valid range
        if (keyCode < 0 || keyCode >= m_KeyStates.Count())
            return;
            
        m_KeyStates[keyCode] = isPressed;
    }
}

class MouseDevice : InputDevice
{
    // Mouse position
    protected int m_PosX;
    protected int m_PosY;
    
    // Mouse wheel delta
    protected float m_WheelDelta;
    
    // Mouse button states
    protected array<bool> m_ButtonStates;
    
    // Constructor
    void MouseDevice(int deviceID = 0)
    {
        // Call base constructor with mouse type
        InputDevice(EInputDeviceType.MOUSE, deviceID);
        
        // Initialize position and wheel
        m_PosX = 0;
        m_PosY = 0;
        m_WheelDelta = 0.0;
        
        // Initialize button states (left, right, middle, and possible extra buttons)
        m_ButtonStates = new array<bool>();
        for (int i = 0; i < 5; i++)
        {
            m_ButtonStates.Insert(false);
        }
    }
    
    /**
     * @brief Get the mouse X position
     * @return The X position
     */
    int GetPosX()
    {
        return m_PosX;
    }
    
    /**
     * @brief Get the mouse Y position
     * @return The Y position
     */
    int GetPosY()
    {
        return m_PosY;
    }
    
    /**
     * @brief Set the mouse position
     * @param x The X position
     * @param y The Y position
     */
    void SetPosition(int x, int y)
    {
        m_PosX = x;
        m_PosY = y;
    }
    
    /**
     * @brief Get the mouse wheel delta
     * @return The wheel delta
     */
    float GetWheelDelta()
    {
        return m_WheelDelta;
    }
    
    /**
     * @brief Set the mouse wheel delta
     * @param delta The wheel delta
     */
    void SetWheelDelta(float delta)
    {
        m_WheelDelta = delta;
    }
    
    /**
     * @brief Check if a mouse button is pressed
     * @param button The button to check
     * @return True if pressed, false otherwise
     */
    bool IsButtonPressed(int button)
    {
        // Ensure button is in valid range
        if (button < 0 || button >= m_ButtonStates.Count())
            return false;
            
        return m_ButtonStates[button];
    }
    
    /**
     * @brief Set the state of a mouse button
     * @param button The button to set
     * @param isPressed The pressed state
     */
    void SetButtonState(int button, bool isPressed)
    {
        // Ensure button is in valid range
        if (button < 0 || button >= m_ButtonStates.Count())
            return;
            
        m_ButtonStates[button] = isPressed;
    }
}