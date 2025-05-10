// PlayerController.c - Player controller class for ARMA Reforger
// This class handles player input and controls a player entity

#include "IEntity.c"
#include "../Input/InputActions.c"
#include "../Input/ActionContext.c"

/**
 * @brief Class representing a player controller
 */
class PlayerController
{
    // The player entity
    protected IEntity m_PlayerEntity;
    
    // Player ID
    protected int m_PlayerID;
    
    // Player name
    protected string m_PlayerName;
    
    // Input context
    protected ref ActionContext m_ActionContext;
    
    // Constructor
    void PlayerController(int playerID = 0, string playerName = "")
    {
        m_PlayerEntity = null;
        m_PlayerID = playerID;
        m_PlayerName = playerName;
        m_ActionContext = new ActionContext();
    }
    
    /**
     * @brief Get the player entity
     * @return The player entity
     */
    IEntity GetPlayerEntity()
    {
        return m_PlayerEntity;
    }
    
    /**
     * @brief Set the player entity
     * @param entity The player entity
     */
    void SetPlayerEntity(IEntity entity)
    {
        m_PlayerEntity = entity;
        m_ActionContext.SetEntity(entity);
    }
    
    /**
     * @brief Get the player ID
     * @return The player ID
     */
    int GetPlayerID()
    {
        return m_PlayerID;
    }
    
    /**
     * @brief Set the player ID
     * @param playerID The player ID
     */
    void SetPlayerID(int playerID)
    {
        m_PlayerID = playerID;
    }
    
    /**
     * @brief Get the player name
     * @return The player name
     */
    string GetPlayerName()
    {
        return m_PlayerName;
    }
    
    /**
     * @brief Set the player name
     * @param playerName The player name
     */
    void SetPlayerName(string playerName)
    {
        m_PlayerName = playerName;
    }
    
    /**
     * @brief Get the input context
     * @return The input context
     */
    ActionContext GetActionContext()
    {
        return m_ActionContext;
    }
    
    /**
     * @brief Process input and execute actions
     * @param action The action to execute
     * @param value The input value (for analog inputs)
     * @param pressed Whether the input was pressed
     * @param down Whether the input is down
     * @param released Whether the input was released
     * @return True if the action was handled, false otherwise
     */
    bool ProcessInput(ActionBase action, float value = 0.0, bool pressed = false, bool down = false, bool released = false)
    {
        if (!action)
            return false;
            
        // Update context
        m_ActionContext.SetValue(value);
        m_ActionContext.SetPressed(pressed);
        m_ActionContext.SetDown(down);
        m_ActionContext.SetReleased(released);
        
        // Execute the action
        return action.Execute(m_ActionContext);
    }
}