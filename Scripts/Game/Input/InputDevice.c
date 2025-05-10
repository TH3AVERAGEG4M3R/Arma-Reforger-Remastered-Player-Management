// InputDevice for ARMA Reforger input system
class InputDevice
{
    // Device type constants
    static const int KEYBOARD = 0;
    static const int MOUSE = 1;
    static const int GAMEPAD = 2;
    
    // Constructor
    void InputDevice() {}
    
    // Get the device type
    int GetType()
    {
        return KEYBOARD;
    }
    
    // Check if this is a keyboard device
    bool IsKeyboard()
    {
        return GetType() == KEYBOARD;
    }
    
    // Check if this is a mouse device
    bool IsMouse()
    {
        return GetType() == MOUSE;
    }
    
    // Check if this is a gamepad device
    bool IsGamepad()
    {
        return GetType() == GAMEPAD;
    }
    
    // Get the device ID
    int GetID()
    {
        return 0;
    }
}