// InputActions.c - Input action definitions for ARMA Reforger

// Action types
enum EInputActionType
{
    PRESS,      // Triggered once when pressed
    HOLD,       // Triggered continuously while held
    RELEASE,    // Triggered once when released
    AXIS        // Analog axis value (e.g., joystick movement)
}

// Action ID constants
enum EInputActionID
{
    UNDEFINED = 0,
    
    // Movement actions
    MOVE_FORWARD = 1,
    MOVE_BACKWARD = 2,
    MOVE_LEFT = 3,
    MOVE_RIGHT = 4,
    SPRINT = 5,
    CROUCH = 6,
    PRONE = 7,
    JUMP = 8,
    
    // Combat actions
    FIRE = 10,
    AIM = 11,
    RELOAD = 12,
    WEAPON_SWITCH = 13,
    GRENADE = 14,
    MELEE = 15,
    
    // Vehicle actions
    VEHICLE_ACCELERATE = 20,
    VEHICLE_BRAKE = 21,
    VEHICLE_STEER_LEFT = 22,
    VEHICLE_STEER_RIGHT = 23,
    VEHICLE_ENTER_EXIT = 24,
    
    // UI actions
    OPEN_MAP = 30,
    OPEN_INVENTORY = 31,
    OPEN_TEAM_MENU = 32,
    OPEN_CHAT = 33,
    UI_CONFIRM = 34,
    UI_CANCEL = 35,
    UI_TAB_NEXT = 36,
    UI_TAB_PREV = 37,
    
    // Team actions
    TEAM_CHAT = 40,
    TEAM_INVITE = 41,
    TEAM_KICK = 42,
    TEAM_RESPAWN = 43,
    
    // Mouse actions
    MOUSE_X = 50,
    MOUSE_Y = 51,
    MOUSE_WHEEL = 52
}

// Input action binding definition
class InputActionBinding
{
    protected EInputActionID m_ActionID;      // ID of the action
    protected EInputActionType m_ActionType;  // Type of the action
    protected int m_DeviceID;                 // Input device ID
    protected int m_InputID;                  // Input identifier (key code, button ID, etc.)
    protected float m_AxisMultiplier;         // Multiplier for axis values
    protected bool m_InvertAxis;              // Whether to invert axis values
    
    // Constructor
    void InputActionBinding(EInputActionID actionID, EInputActionType actionType, int deviceID, int inputID)
    {
        m_ActionID = actionID;
        m_ActionType = actionType;
        m_DeviceID = deviceID;
        m_InputID = inputID;
        m_AxisMultiplier = 1.0;
        m_InvertAxis = false;
    }
    
    //------------------------------------------
    // Getters and setters
    //------------------------------------------
    
    EInputActionID GetActionID()
    {
        return m_ActionID;
    }
    
    EInputActionType GetActionType()
    {
        return m_ActionType;
    }
    
    int GetDeviceID()
    {
        return m_DeviceID;
    }
    
    int GetInputID()
    {
        return m_InputID;
    }
    
    float GetAxisMultiplier()
    {
        return m_AxisMultiplier;
    }
    
    void SetAxisMultiplier(float multiplier)
    {
        m_AxisMultiplier = multiplier;
    }
    
    bool GetInvertAxis()
    {
        return m_InvertAxis;
    }
    
    void SetInvertAxis(bool invert)
    {
        m_InvertAxis = invert;
    }
}

// Input action manager
class InputActionManager
{
    // Singleton instance
    protected static ref InputActionManager s_Instance;
    
    // Registered input actions
    protected ref array<ref InputActionBinding> m_Bindings;
    
    // Default constructor
    void InputActionManager()
    {
        m_Bindings = new array<ref InputActionBinding>();
        RegisterDefaultBindings();
    }
    
    /**
     * @brief Get the singleton instance
     * @return The singleton instance
     */
    static InputActionManager GetInstance()
    {
        if (!s_Instance)
        {
            s_Instance = new InputActionManager();
        }
        
        return s_Instance;
    }
    
    /**
     * @brief Register default input bindings
     */
    protected void RegisterDefaultBindings()
    {
        // Movement bindings
        RegisterBinding(new InputActionBinding(EInputActionID.MOVE_FORWARD, EInputActionType.HOLD, 0, 87));  // W
        RegisterBinding(new InputActionBinding(EInputActionID.MOVE_BACKWARD, EInputActionType.HOLD, 0, 83)); // S
        RegisterBinding(new InputActionBinding(EInputActionID.MOVE_LEFT, EInputActionType.HOLD, 0, 65));     // A
        RegisterBinding(new InputActionBinding(EInputActionID.MOVE_RIGHT, EInputActionType.HOLD, 0, 68));    // D
        RegisterBinding(new InputActionBinding(EInputActionID.SPRINT, EInputActionType.HOLD, 0, 16));        // Shift
        RegisterBinding(new InputActionBinding(EInputActionID.CROUCH, EInputActionType.PRESS, 0, 67));       // C
        RegisterBinding(new InputActionBinding(EInputActionID.PRONE, EInputActionType.PRESS, 0, 90));        // Z
        RegisterBinding(new InputActionBinding(EInputActionID.JUMP, EInputActionType.PRESS, 0, 32));         // Space
        
        // Combat bindings
        RegisterBinding(new InputActionBinding(EInputActionID.FIRE, EInputActionType.PRESS, 1, 0));          // Left mouse button
        RegisterBinding(new InputActionBinding(EInputActionID.AIM, EInputActionType.HOLD, 1, 1));            // Right mouse button
        RegisterBinding(new InputActionBinding(EInputActionID.RELOAD, EInputActionType.PRESS, 0, 82));       // R
        RegisterBinding(new InputActionBinding(EInputActionID.WEAPON_SWITCH, EInputActionType.PRESS, 0, 70)); // F
        
        // UI bindings
        RegisterBinding(new InputActionBinding(EInputActionID.OPEN_MAP, EInputActionType.PRESS, 0, 77));      // M
        RegisterBinding(new InputActionBinding(EInputActionID.OPEN_INVENTORY, EInputActionType.PRESS, 0, 73)); // I
        RegisterBinding(new InputActionBinding(EInputActionID.OPEN_TEAM_MENU, EInputActionType.PRESS, 0, 84)); // T
        RegisterBinding(new InputActionBinding(EInputActionID.OPEN_CHAT, EInputActionType.PRESS, 0, 89));     // Y
        
        // Team bindings
        RegisterBinding(new InputActionBinding(EInputActionID.TEAM_CHAT, EInputActionType.PRESS, 0, 85));     // U
        
        // Mouse axes
        RegisterBinding(new InputActionBinding(EInputActionID.MOUSE_X, EInputActionType.AXIS, 1, 100));      // Special input ID for mouse X
        RegisterBinding(new InputActionBinding(EInputActionID.MOUSE_Y, EInputActionType.AXIS, 1, 101));      // Special input ID for mouse Y
        RegisterBinding(new InputActionBinding(EInputActionID.MOUSE_WHEEL, EInputActionType.AXIS, 1, 102));  // Special input ID for mouse wheel
    }
    
    /**
     * @brief Register a new binding
     * @param binding The binding to register
     */
    void RegisterBinding(InputActionBinding binding)
    {
        if (!binding)
            return;
            
        m_Bindings.Insert(binding);
    }
    
    /**
     * @brief Find bindings for an action
     * @param actionID The action ID to find bindings for
     * @return Array of matching bindings
     */
    array<ref InputActionBinding> FindBindings(EInputActionID actionID)
    {
        array<ref InputActionBinding> result = new array<ref InputActionBinding>();
        
        foreach (InputActionBinding binding : m_Bindings)
        {
            if (binding.GetActionID() == actionID)
            {
                result.Insert(binding);
            }
        }
        
        return result;
    }
    
    /**
     * @brief Process input and generate action contexts
     * Typically called every frame to convert raw input to actions
     * @param devices Array of input devices to process
     * @return Array of action contexts for triggered actions
     */
    array<ref ActionContext> ProcessInput(array<ref InputDevice> devices)
    {
        array<ref ActionContext> result = new array<ref ActionContext>();
        
        // Process all registered bindings
        foreach (InputActionBinding binding : m_Bindings)
        {
            int deviceID = binding.GetDeviceID();
            InputDevice device = FindDevice(devices, deviceID);
            
            if (!device || !device.IsConnected())
                continue;
                
            // Different handling based on device type and action type
            if (device.GetType() == EInputDeviceType.KEYBOARD)
            {
                KeyboardDevice keyboard = KeyboardDevice.Cast(device);
                if (!keyboard)
                    continue;
                    
                int keyCode = binding.GetInputID();
                bool isPressed = keyboard.IsKeyPressed(keyCode);
                
                if (isPressed && (binding.GetActionType() == EInputActionType.PRESS || binding.GetActionType() == EInputActionType.HOLD))
                {
                    ref ActionContext ctx = new ActionContext(null, device);
                    ctx.SetPressed(binding.GetActionType() == EInputActionType.PRESS);
                    ctx.SetDown(binding.GetActionType() == EInputActionType.HOLD);
                    ctx.SetValue(1.0); // Digital inputs are either 0.0 or 1.0
                    result.Insert(ctx);
                }
            }
            else if (device.GetType() == EInputDeviceType.MOUSE)
            {
                MouseDevice mouse = MouseDevice.Cast(device);
                if (!mouse)
                    continue;
                    
                int inputID = binding.GetInputID();
                
                // Handle mouse button
                if (inputID < 100) 
                {
                    bool isPressed = mouse.IsButtonPressed(inputID);
                    
                    if (isPressed && (binding.GetActionType() == EInputActionType.PRESS || binding.GetActionType() == EInputActionType.HOLD))
                    {
                        ref ActionContext ctx = new ActionContext(null, device);
                        ctx.SetPressed(binding.GetActionType() == EInputActionType.PRESS);
                        ctx.SetDown(binding.GetActionType() == EInputActionType.HOLD);
                        ctx.SetValue(1.0);
                        result.Insert(ctx);
                    }
                }
                // Handle mouse axes
                else if (binding.GetActionType() == EInputActionType.AXIS)
                {
                    float value = 0.0;
                    
                    if (inputID == 100) // Mouse X
                    {
                        value = mouse.GetPosX() * binding.GetAxisMultiplier();
                    }
                    else if (inputID == 101) // Mouse Y
                    {
                        value = mouse.GetPosY() * binding.GetAxisMultiplier();
                    }
                    else if (inputID == 102) // Mouse wheel
                    {
                        value = mouse.GetWheelDelta() * binding.GetAxisMultiplier();
                    }
                    
                    if (binding.GetInvertAxis())
                    {
                        value = -value;
                    }
                    
                    ref ActionContext ctx = new ActionContext(null, device);
                    ctx.SetValue(value);
                    result.Insert(ctx);
                }
            }
        }
        
        return result;
    }
    
    /**
     * @brief Find a device by ID
     * @param devices Array of devices to search
     * @param deviceID The device ID to find
     * @return The found device, or null if not found
     */
    protected InputDevice FindDevice(array<ref InputDevice> devices, int deviceID)
    {
        foreach (InputDevice device : devices)
        {
            if (device.GetDeviceID() == deviceID)
            {
                return device;
            }
        }
        
        return null;
    }
}