/**
 * @brief Input actions for the game
 */

#include "ActionContext.c"
#include "InputDevice.c"

/**
 * @brief Base input manager class
 */
class InputManager
{
    // Singleton instance
    protected static InputManager s_Instance;
    
    // Map of registered action contexts
    protected ref map<string, ref ActionContext> m_RegisteredContexts = new map<string, ref ActionContext>();
    
    // Map of registered actions
    protected ref map<string, ref ActionBase> m_RegisteredActions = new map<string, ref ActionBase>();
    
    // Input devices
    protected ref array<ref InputDevice> m_InputDevices = new array<ref InputDevice>();
    
    /**
     * @brief Get the singleton instance
     */
    static InputManager GetInstance()
    {
        if (!s_Instance)
        {
            s_Instance = new InputManager();
        }
        
        return s_Instance;
    }
    
    /**
     * @brief Initialize the input manager
     */
    void Init()
    {
        // Register keyboard device
        RegisterInputDevice(new KeyboardInputDevice());
        
        // Register mouse device
        RegisterInputDevice(new MouseInputDevice());
        
        // Register default action context
        RegisterActionContext(new ActionContext("Default", 0));
    }
    
    /**
     * @brief Register an input device
     * @param device The device to register
     */
    void RegisterInputDevice(InputDevice device)
    {
        if (!device)
            return;
            
        m_InputDevices.Insert(device);
    }
    
    /**
     * @brief Register an action context
     * @param context The context to register
     */
    void RegisterActionContext(ActionContext context)
    {
        if (!context)
            return;
            
        string name = context.GetActionName();
        if (name.Length() > 0)
        {
            m_RegisteredContexts.Insert(name, context);
        }
    }
    
    /**
     * @brief Get an action context by name
     * @param name The name of the context
     * @return The context, or null if not found
     */
    ActionContext GetActionContext(string name)
    {
        ActionContext context = null;
        m_RegisteredContexts.Find(name, context);
        return context;
    }
    
    /**
     * @brief Register an action
     * @param action The action to register
     */
    void RegisterAction(ActionBase action)
    {
        if (!action)
            return;
            
        string name = action.GetName();
        if (name.Length() > 0)
        {
            m_RegisteredActions.Insert(name, action);
        }
    }
    
    /**
     * @brief Get an action by name
     * @param name The name of the action
     * @return The action, or null if not found
     */
    ActionBase GetAction(string name)
    {
        ActionBase action = null;
        m_RegisteredActions.Find(name, action);
        return action;
    }
    
    /**
     * @brief Handle key down event
     * @param key The key code
     * @return True if the event was handled, false otherwise
     */
    bool OnKeyDown(int key)
    {
        foreach (InputDevice device : m_InputDevices)
        {
            if (device.HandleKeyDown(key))
                return true;
        }
        
        return false;
    }
    
    /**
     * @brief Handle key up event
     * @param key The key code
     * @return True if the event was handled, false otherwise
     */
    bool OnKeyUp(int key)
    {
        foreach (InputDevice device : m_InputDevices)
        {
            if (device.HandleKeyUp(key))
                return true;
        }
        
        return false;
    }
}

/**
 * @brief Class to handle team management hotkeys
 */
class TeamManagementInputActions
{
    // Key codes
    const int KEY_T = 84;  // 'T' key for team menu
    const int KEY_Y = 89;  // 'Y' key for team chat
    
    // Action contexts
    static const string TEAM_MENU_CONTEXT = "TeamMenuContext";
    static const string TEAM_CHAT_CONTEXT = "TeamChatContext";
    
    // Actions
    static const string TEAM_MENU_ACTION = "TeamMenuAction";
    static const string TEAM_CHAT_ACTION = "TeamChatAction";
    
    // Register actions with the input manager
    static void RegisterActions()
    {
        InputManager inputManager = InputManager.GetInstance();
        
        // Register contexts
        inputManager.RegisterActionContext(new ActionContext(TEAM_MENU_CONTEXT, 10));
        inputManager.RegisterActionContext(new ActionContext(TEAM_CHAT_CONTEXT, 20));
        
        // Register actions
        ActionBase teamMenuAction = new ActionBase(TEAM_MENU_ACTION);
        teamMenuAction.SetContext(inputManager.GetActionContext(TEAM_MENU_CONTEXT));
        inputManager.RegisterAction(teamMenuAction);
        
        ActionBase teamChatAction = new ActionBase(TEAM_CHAT_ACTION);
        teamChatAction.SetContext(inputManager.GetActionContext(TEAM_CHAT_CONTEXT));
        inputManager.RegisterAction(teamChatAction);
    }
    
    // Get the team menu action
    static ActionBase GetTeamMenuAction()
    {
        return InputManager.GetInstance().GetAction(TEAM_MENU_ACTION);
    }
    
    // Get the team chat action
    static ActionBase GetTeamChatAction()
    {
        return InputManager.GetInstance().GetAction(TEAM_CHAT_ACTION);
    }
}