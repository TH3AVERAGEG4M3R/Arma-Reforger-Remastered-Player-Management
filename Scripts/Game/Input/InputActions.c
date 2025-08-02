// InputActions.c - Input action definitions for ARMA Reforger
// This file contains constants and classes for input actions

#include "ActionContext.c"

// Input action IDs
enum EInputActionID
{
    // Basic movement
    MOVE_FORWARD = 1,
    MOVE_BACKWARD = 2,
    MOVE_LEFT = 3,
    MOVE_RIGHT = 4,
    
    // Basic interaction
    INTERACT = 10,
    USE = 11,
    
    // Stance
    STANCE_STANDING = 20,
    STANCE_CROUCHING = 21,
    STANCE_PRONE = 22,
    
    // Weapons
    FIRE = 30,
    AIM = 31,
    RELOAD = 32,
    CHANGE_FIREMODE = 33,
    
    // UI actions
    OPEN_MAP = 40,
    OPEN_INVENTORY = 41,
    OPEN_MENU = 42,
    OPEN_CHAT = 43,
    
    // Team-specific actions
    OPEN_TEAM_MENU = 50,
    OPEN_TEAM_CHAT = 51,
    
    // Vehicle actions
    VEHICLE_ENTER = 60,
    VEHICLE_EXIT = 61,
    VEHICLE_DRIVER = 62,
    VEHICLE_GUNNER = 63,
    VEHICLE_PASSENGER = 64
}

// Input device types
enum EInputDeviceType
{
    KEYBOARD = 1,
    MOUSE = 2,
    GAMEPAD = 3
}

/**
 * @brief Basic move forward action
 */
class InputAction_MoveForward : ActionBase
{
    /**
     * @brief Constructor
     */
    void InputAction_MoveForward()
    {
        m_ActionID = EInputActionID.MOVE_FORWARD;
        m_ActionName = "Move Forward";
    }
    
    /**
     * @brief Execute the action
     * @param ctx The action context
     * @return True if the action was executed successfully, false otherwise
     */
    override bool Execute(ActionContext ctx)
    {
        if (!ctx)
            return false;
        
        // Get the entity
        IEntity entity = ctx.GetEntity();
        if (!entity)
            return false;
        
        // Here would be the logic to move the entity forward
        
        return true;
    }
}

/**
 * @brief Team menu action
 */
class InputAction_OpenTeamMenu : ActionBase
{
    /**
     * @brief Constructor
     */
    void InputAction_OpenTeamMenu()
    {
        m_ActionID = EInputActionID.OPEN_TEAM_MENU;
        m_ActionName = "Open Team Menu";
    }
    
    /**
     * @brief Execute the action
     * @param ctx The action context
     * @return True if the action was executed successfully, false otherwise
     */
    override bool Execute(ActionContext ctx)
    {
        if (!ctx)
            return false;
        
        // Get the entity
        IEntity entity = ctx.GetEntity();
        if (!entity)
            return false;
        
        // Here would be the logic to open the team menu
        
        return true;
    }
}

/**
 * @brief Team chat action
 */
class InputAction_OpenTeamChat : ActionBase
{
    /**
     * @brief Constructor
     */
    void InputAction_OpenTeamChat()
    {
        m_ActionID = EInputActionID.OPEN_TEAM_CHAT;
        m_ActionName = "Open Team Chat";
    }
    
    /**
     * @brief Execute the action
     * @param ctx The action context
     * @return True if the action was executed successfully, false otherwise
     */
    override bool Execute(ActionContext ctx)
    {
        if (!ctx)
            return false;
        
        // Get the entity
        IEntity entity = ctx.GetEntity();
        if (!entity)
            return false;
        
        // Here would be the logic to open the team chat
        
        return true;
    }
}