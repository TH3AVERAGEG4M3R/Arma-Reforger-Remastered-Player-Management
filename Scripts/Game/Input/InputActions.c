// InputActions.c - Input action definitions for ARMA Reforger
// This class defines the input actions available in the game

// Required includes
#include "ActionContext.c"
#include "InputDevice.c"

/**
 * @brief Base class for input actions
 */
class ActionBase
{
    // Action name
    protected string m_Name;
    
    // Action ID
    protected int m_ID;
    
    // Constructor
    void ActionBase(string name = "", int id = -1)
    {
        m_Name = name;
        m_ID = id;
    }
    
    //------------------------------------------
    // Virtual methods
    //------------------------------------------
    
    /**
     * @brief Execute the action
     * @param context The action context
     * @return True if the action was handled, false otherwise
     */
    bool Execute(ActionContext context)
    {
        return false;
    }
    
    //------------------------------------------
    // Getters and setters
    //------------------------------------------
    
    /**
     * @brief Get the action name
     * @return The action name
     */
    string GetName()
    {
        return m_Name;
    }
    
    /**
     * @brief Set the action name
     * @param name The action name
     */
    void SetName(string name)
    {
        m_Name = name;
    }
    
    /**
     * @brief Get the action ID
     * @return The action ID
     */
    int GetID()
    {
        return m_ID;
    }
    
    /**
     * @brief Set the action ID
     * @param id The action ID
     */
    void SetID(int id)
    {
        m_ID = id;
    }
}

/**
 * @brief Registry for all input actions
 */
class InputActions
{
    // Singleton instance
    private static ref InputActions s_Instance;
    
    // Registered actions
    private ref map<int, ref ActionBase> m_ActionMap;
    
    // Next available action ID
    private int m_NextActionID = 1;
    
    // Constructor
    private void InputActions()
    {
        m_ActionMap = new map<int, ref ActionBase>();
        RegisterDefaultActions();
    }
    
    /**
     * @brief Get the singleton instance
     * @return The singleton instance
     */
    static InputActions GetInstance()
    {
        if (!s_Instance)
            s_Instance = new InputActions();
            
        return s_Instance;
    }
    
    /**
     * @brief Register default game actions
     */
    private void RegisterDefaultActions()
    {
        // Examples of common actions - these would be filled in by the game
        RegisterAction(new ActionBase("MoveForward", m_NextActionID++));
        RegisterAction(new ActionBase("MoveBackward", m_NextActionID++));
        RegisterAction(new ActionBase("MoveLeft", m_NextActionID++));
        RegisterAction(new ActionBase("MoveRight", m_NextActionID++));
        RegisterAction(new ActionBase("Jump", m_NextActionID++));
        RegisterAction(new ActionBase("Crouch", m_NextActionID++));
        RegisterAction(new ActionBase("Prone", m_NextActionID++));
        RegisterAction(new ActionBase("Fire", m_NextActionID++));
        RegisterAction(new ActionBase("AimDown", m_NextActionID++));
        RegisterAction(new ActionBase("Reload", m_NextActionID++));
        RegisterAction(new ActionBase("Use", m_NextActionID++));
        RegisterAction(new ActionBase("SwitchWeapon", m_NextActionID++));
        RegisterAction(new ActionBase("NextFireMode", m_NextActionID++));
        RegisterAction(new ActionBase("ThrowGrenade", m_NextActionID++));
        RegisterAction(new ActionBase("OpenInventory", m_NextActionID++));
        RegisterAction(new ActionBase("OpenMap", m_NextActionID++));
        
        // Team management specific actions
        RegisterAction(new ActionBase("TeamMenu", m_NextActionID++));
        RegisterAction(new ActionBase("TeamChat", m_NextActionID++));
    }
    
    /**
     * @brief Register an action
     * @param action The action to register
     * @return True if registration succeeded, false otherwise
     */
    bool RegisterAction(ActionBase action)
    {
        if (!action)
            return false;
            
        int id = action.GetID();
        if (id < 0)
        {
            id = m_NextActionID++;
            action.SetID(id);
        }
        
        m_ActionMap[id] = action;
        return true;
    }
    
    /**
     * @brief Unregister an action
     * @param id The action ID
     * @return True if unregistration succeeded, false otherwise
     */
    bool UnregisterAction(int id)
    {
        if (!m_ActionMap.Contains(id))
            return false;
            
        m_ActionMap.Remove(id);
        return true;
    }
    
    /**
     * @brief Get an action by ID
     * @param id The action ID
     * @return The action, or null if not found
     */
    ActionBase GetAction(int id)
    {
        return m_ActionMap.Get(id);
    }
    
    /**
     * @brief Get an action by name
     * @param name The action name
     * @return The action, or null if not found
     */
    ActionBase GetActionByName(string name)
    {
        foreach (int id, ref ActionBase action : m_ActionMap)
        {
            if (action.GetName() == name)
                return action;
        }
        
        return null;
    }
    
    /**
     * @brief Execute an action
     * @param id The action ID
     * @param context The action context
     * @return True if the action was handled, false otherwise
     */
    bool ExecuteAction(int id, ActionContext context)
    {
        ActionBase action = GetAction(id);
        if (!action)
            return false;
            
        return action.Execute(context);
    }
    
    /**
     * @brief Execute an action by name
     * @param name The action name
     * @param context The action context
     * @return True if the action was handled, false otherwise
     */
    bool ExecuteActionByName(string name, ActionContext context)
    {
        ActionBase action = GetActionByName(name);
        if (!action)
            return false;
            
        return action.Execute(context);
    }
}