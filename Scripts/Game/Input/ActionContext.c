// ActionContext.c - Input action context for ARMA Reforger
// This class defines the context in which input actions are executed

class ActionContext
{
    // Reference to the entity that initiated the action (usually a player)
    protected IEntity m_Entity;
    
    // Input device that triggered the action
    protected InputDevice m_InputDevice;
    
    // Additional action data
    protected float m_Value;           // For analog inputs (e.g., joystick axis)
    protected bool m_IsPressed;        // Whether a button is pressed
    protected bool m_IsDown;           // Whether a button is held down
    protected bool m_IsReleased;       // Whether a button was released
    
    // Constructor
    void ActionContext(IEntity entity = null, InputDevice device = null)
    {
        m_Entity = entity;
        m_InputDevice = device;
        m_Value = 0.0;
        m_IsPressed = false;
        m_IsDown = false;
        m_IsReleased = false;
    }
    
    //------------------------------------------
    // Getters and setters
    //------------------------------------------
    
    /**
     * @brief Get the entity that initiated the action
     * @return The entity
     */
    IEntity GetEntity()
    {
        return m_Entity;
    }
    
    /**
     * @brief Set the entity that initiated the action
     * @param entity The entity
     */
    void SetEntity(IEntity entity)
    {
        m_Entity = entity;
    }
    
    /**
     * @brief Get the input device that triggered the action
     * @return The input device
     */
    InputDevice GetInputDevice()
    {
        return m_InputDevice;
    }
    
    /**
     * @brief Set the input device that triggered the action
     * @param device The input device
     */
    void SetInputDevice(InputDevice device)
    {
        m_InputDevice = device;
    }
    
    /**
     * @brief Get the analog value of the action
     * @return The value
     */
    float GetValue()
    {
        return m_Value;
    }
    
    /**
     * @brief Set the analog value of the action
     * @param value The value
     */
    void SetValue(float value)
    {
        m_Value = value;
    }
    
    /**
     * @brief Check if the action was pressed (button down event)
     * @return True if pressed, false otherwise
     */
    bool IsPressed()
    {
        return m_IsPressed;
    }
    
    /**
     * @brief Set the pressed state
     * @param isPressed The pressed state
     */
    void SetPressed(bool isPressed)
    {
        m_IsPressed = isPressed;
    }
    
    /**
     * @brief Check if the action is down (button held)
     * @return True if down, false otherwise
     */
    bool IsDown()
    {
        return m_IsDown;
    }
    
    /**
     * @brief Set the down state
     * @param isDown The down state
     */
    void SetDown(bool isDown)
    {
        m_IsDown = isDown;
    }
    
    /**
     * @brief Check if the action was released (button up event)
     * @return True if released, false otherwise
     */
    bool IsReleased()
    {
        return m_IsReleased;
    }
    
    /**
     * @brief Set the released state
     * @param isReleased The released state
     */
    void SetReleased(bool isReleased)
    {
        m_IsReleased = isReleased;
    }
}