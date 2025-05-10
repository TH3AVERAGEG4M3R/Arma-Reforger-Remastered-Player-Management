/**
 * @brief ActionContext class for handling input events
 */

class ActionContext
{
    // The action name associated with this context
    protected string m_ActionName;
    
    // The priority of this action context
    protected int m_Priority;
    
    // Whether this action context is active
    protected bool m_IsActive;
    
    // The parent context for this action
    protected ActionContext m_ParentContext;
    
    /**
     * @brief Constructor
     */
    void ActionContext(string actionName = "", int priority = 0)
    {
        m_ActionName = actionName;
        m_Priority = priority;
        m_IsActive = true;
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
     * @brief Get the priority of this action context
     * @return The priority (higher values mean higher priority)
     */
    int GetPriority()
    {
        return m_Priority;
    }
    
    /**
     * @brief Check if this action context is active
     * @return True if active, false otherwise
     */
    bool IsActive()
    {
        return m_IsActive;
    }
    
    /**
     * @brief Set the active state of this action context
     * @param active The new active state
     */
    void SetActive(bool active)
    {
        m_IsActive = active;
    }
    
    /**
     * @brief Set the parent context
     * @param parent The parent context
     */
    void SetParentContext(ActionContext parent)
    {
        m_ParentContext = parent;
    }
    
    /**
     * @brief Get the parent context
     * @return The parent context
     */
    ActionContext GetParentContext()
    {
        return m_ParentContext;
    }
}

/**
 * @brief ActionBase class for handling specific input actions
 */
class ActionBase
{
    // The name of this action
    protected string m_Name;
    
    // The context this action is associated with
    protected ActionContext m_Context;
    
    /**
     * @brief Constructor
     */
    void ActionBase(string name = "")
    {
        m_Name = name;
    }
    
    /**
     * @brief Get the name of this action
     * @return The action name
     */
    string GetName()
    {
        return m_Name;
    }
    
    /**
     * @brief Set the context for this action
     * @param context The context to set
     */
    void SetContext(ActionContext context)
    {
        m_Context = context;
    }
    
    /**
     * @brief Get the context for this action
     * @return The action context
     */
    ActionContext GetContext()
    {
        return m_Context;
    }
    
    /**
     * @brief Check if this action is active
     * @return True if active, false otherwise
     */
    bool IsActive()
    {
        if (!m_Context)
            return false;
            
        return m_Context.IsActive();
    }
}