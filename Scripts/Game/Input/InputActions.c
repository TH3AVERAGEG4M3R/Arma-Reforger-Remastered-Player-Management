/**
 * @brief Input Actions for handling input actions and triggers in ARMA Reforger
 */

// Enumeration for input action triggers
enum EActionTrigger
{
    DOWN,       // Triggered when input is pressed
    UP,         // Triggered when input is released
    VALUE,      // Triggered when input value changes
    HOLD,       // Triggered when input is held
    DOUBLE_TAP, // Triggered when input is double-tapped
    HOLD_END    // Triggered when hold ends
}

/**
 * @brief Input Manager for handling input actions and devices
 */
class InputManager
{
    // Singleton instance
    protected static InputManager s_Instance;
    
    // Action listeners mapped by action name
    protected ref map<string, ref array<ref ActionMapping>> m_ActionListeners = new map<string, ref array<ref ActionMapping>>();
    
    //------------------------------------------------------------------------------------------------
    void InputManager()
    {
        s_Instance = this;
    }
    
    //------------------------------------------------------------------------------------------------
    void ~InputManager()
    {
        if (s_Instance == this)
            s_Instance = null;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the singleton instance
     * @return The input manager instance
     */
    static InputManager GetInstance()
    {
        if (!s_Instance)
            s_Instance = new InputManager();
        
        return s_Instance;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Add an action listener
     * @param actionName The action name to listen for
     * @param trigger The trigger type
     * @param callback The callback function
     * @return True if added successfully
     */
    bool AddActionListener(string actionName, EActionTrigger trigger, func<ActionContext, bool> callback)
    {
        if (!m_ActionListeners.Contains(actionName))
            m_ActionListeners.Set(actionName, new array<ref ActionMapping>());
            
        ActionMapping mapping = new ActionMapping(actionName, trigger, callback);
        m_ActionListeners.Get(actionName).Insert(mapping);
        
        return true;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Remove an action listener
     * @param actionName The action name to remove
     * @param callback The callback function to remove
     * @return True if removed successfully
     */
    bool RemoveActionListener(string actionName, func<ActionContext, bool> callback)
    {
        if (!m_ActionListeners.Contains(actionName))
            return false;
            
        array<ref ActionMapping> listeners = m_ActionListeners.Get(actionName);
        for (int i = 0; i < listeners.Count(); i++)
        {
            ActionMapping mapping = listeners[i];
            if (mapping.GetCallback() == callback)
            {
                listeners.RemoveOrdered(i);
                return true;
            }
        }
        
        return false;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Process an action
     * @param action The action context
     * @return True if processed
     */
    bool ProcessAction(ActionContext action)
    {
        string actionName = action.GetActionName();
        if (!m_ActionListeners.Contains(actionName))
            return false;
            
        bool handled = false;
        array<ref ActionMapping> listeners = m_ActionListeners.Get(actionName);
        foreach (ActionMapping mapping : listeners)
        {
            if (mapping.ProcessAction(action))
                handled = true;
        }
        
        return handled;
    }
}

/**
 * @brief Action Mapping for mapping actions to callbacks
 */
class ActionMapping
{
    // Action name
    protected string m_ActionName;
    
    // Trigger type
    protected EActionTrigger m_TriggerType;
    
    // Callback function
    protected func<ActionContext, bool> m_Callback;
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Constructor
     * @param actionName The action name
     * @param trigger The trigger type
     * @param callback The callback function
     */
    void ActionMapping(string actionName, EActionTrigger trigger, func<ActionContext, bool> callback)
    {
        m_ActionName = actionName;
        m_TriggerType = trigger;
        m_Callback = callback;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Process an action
     * @param action The action context
     * @return True if processed
     */
    bool ProcessAction(ActionContext action)
    {
        if (m_Callback)
            return m_Callback.Invoke(action);
            
        return false;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the action name
     * @return The action name
     */
    string GetActionName()
    {
        return m_ActionName;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the trigger type
     * @return The trigger type
     */
    EActionTrigger GetTriggerType()
    {
        return m_TriggerType;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the callback function
     * @return The callback function
     */
    func<ActionContext, bool> GetCallback()
    {
        return m_Callback;
    }
}