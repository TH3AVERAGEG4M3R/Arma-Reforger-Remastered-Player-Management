// ActionContext for ARMA Reforger input system
#include "InputDevice.c"
class ActionBase
{
    bool GetActionPhase() { return true; }
    float GetActionValue() { return 1.0; }
    int GetID() { return 0; }
    InputDevice GetInputDevice() { return null; }
}

class ActionContext : ActionBase
{
    // Constructor
    void ActionContext() {}
    
    // Get the action value (0.0 to 1.0 for analog inputs)
    override float GetActionValue()
    {
        return 1.0;
    }
    
    // Get the action phase (pressed, released, etc.)
    override bool GetActionPhase()
    {
        return true;
    }
    
    // Get the action ID
    override int GetID()
    {
        return 0;
    }
    
    // Get the input device that triggered this action
    override InputDevice GetInputDevice()
    {
        return null;
    }
}