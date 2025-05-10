// ScriptComponent.c - Base class for script components in ARMA Reforger
// This class provides the base functionality for script-based components

#include "IComponent.c"

/**
 * @brief Base class for script components
 */
class ScriptComponent : IComponent
{
    // Constructor
    void ScriptComponent(string name = "")
    {
        // Call base constructor
        super.IComponent(name);
    }
    
    // Post-init method for script components
    void OnPostInit()
    {
        // Base implementation does nothing
    }
    
    // Save/load methods for replication
    void RplSave()
    {
        // Base implementation does nothing
    }
    
    void RplLoad()
    {
        // Base implementation does nothing
    }
}

// Specific script component types
class ScriptedWidgetComponent : ScriptComponent
{
    // Constructor
    void ScriptedWidgetComponent(string name = "")
    {
        // Call base constructor
        super.ScriptComponent(name);
    }
    
    // Additional widget-specific methods would go here
}

class GenericComponent : ScriptComponent
{
    // Constructor
    void GenericComponent(string name = "")
    {
        // Call base constructor
        super.ScriptComponent(name);
    }
    
    // Additional generic component methods would go here
}