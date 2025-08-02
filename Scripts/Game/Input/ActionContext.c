// ActionContext.c - Input action context for ARMA Reforger
// This file contains the ActionContext and ActionBase classes which are used for input handling

#include "../Core/Game.c"

/**
 * @brief Base class for input actions in the ARMA Reforger framework
 */
class ActionBase
{
    // Action ID
    protected int m_ActionID;
    
    // Action name
    protected string m_ActionName;
    
    // Whether the action is active
    protected bool m_IsActive;
    
    /**
     * @brief Constructor
     * @param actionID The unique identifier for this action
     * @param actionName The name of the action
     */
    void ActionBase(int actionID = 0, string actionName = "")
    {
        m_ActionID = actionID;
        m_ActionName = actionName;
        m_IsActive = false;
    }
    
    /**
     * @brief Get the action ID
     * @return The action ID
     */
    int GetActionID()
    {
        return m_ActionID;
    }
    
    /**
     * @brief Get the action name
     * @return The action name
     */
    string GetActionName()
    {
        return m_ActionName;
    }
    
    /**
     * @brief Check if the action is active
     * @return True if the action is active, false otherwise
     */
    bool IsActive()
    {
        return m_IsActive;
    }
    
    /**
     * @brief Set the active state of the action
     * @param active The new active state
     */
    void SetActive(bool active)
    {
        m_IsActive = active;
    }
    
    /**
     * @brief Execute the action
     * @param ctx The action context
     * @return True if the action was executed successfully, false otherwise
     */
    bool Execute(ActionContext ctx)
    {
        return false; // Base implementation does nothing
    }
}

/**
 * @brief Context for input actions in the ARMA Reforger framework
 */
class ActionContext
{
    // Input value (e.g., from a gamepad trigger)
    protected float m_InputValue;
    
    // Source of the input (e.g., keyboard, gamepad)
    protected int m_InputDevice;
    
    // Flags for the action context
    protected int m_Flags;
    
    // Entity associated with the action
    protected EntityID m_EntityID;
    
    /**
     * @brief Constructor
     * @param inputValue The input value
     * @param inputDevice The input device
     */
    void ActionContext(float inputValue = 0.0, int inputDevice = 0, EntityID entityID = EntityID.Invalid())
    {
        m_InputValue = inputValue;
        m_InputDevice = inputDevice;
        m_Flags = 0;
        m_EntityID = entityID;
    }
    
    /**
     * @brief Get the input value
     * @return The input value
     */
    float GetInputValue()
    {
        return m_InputValue;
    }
    
    /**
     * @brief Set the input value
     * @param value The new input value
     */
    void SetInputValue(float value)
    {
        m_InputValue = value;
    }
    
    /**
     * @brief Get the input device
     * @return The input device
     */
    int GetInputDevice()
    {
        return m_InputDevice;
    }
    
    /**
     * @brief Set the input device
     * @param device The new input device
     */
    void SetInputDevice(int device)
    {
        m_InputDevice = device;
    }
    
    /**
     * @brief Get the flags
     * @return The flags
     */
    int GetFlags()
    {
        return m_Flags;
    }
    
    /**
     * @brief Set the flags
     * @param flags The new flags
     */
    void SetFlags(int flags)
    {
        m_Flags = flags;
    }
    
    /**
     * @brief Get the entity ID
     * @return The entity ID
     */
    EntityID GetEntityID()
    {
        return m_EntityID;
    }
    
    /**
     * @brief Set the entity ID
     * @param entityID The new entity ID
     */
    void SetEntityID(EntityID entityID)
    {
        m_EntityID = entityID;
    }
    
    /**
     * @brief Get the entity associated with the action
     * @return The entity, or null if not found
     */
    IEntity GetEntity()
    {
        if (m_EntityID != EntityID.Invalid())
        {
            return GetGame().GetWorld().FindEntityByID(m_EntityID);
        }
        return null;
    }
}