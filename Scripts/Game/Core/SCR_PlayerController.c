// SCR_PlayerController.c - Player controller class for ARMA Reforger
// This class extends the base player controller with game-specific functionality

#include "PlayerController.c"
#include "../Input/InputActions.c"
#include "../Input/ActionContext.c"

/**
 * @brief Game-specific player controller class
 */
class SCR_PlayerController : PlayerController
{
    // References to player components
    protected ref array<ref IComponent> m_GameComponents;
    
    // Player status
    protected bool m_IsAlive;
    protected bool m_IsInVehicle;
    protected IEntity m_CurrentVehicle;
    
    // Constructor
    void SCR_PlayerController(int playerID = 0, string playerName = "")
    {
        // Call base constructor
        super.PlayerController(playerID, playerName);
        
        // Initialize
        m_GameComponents = new array<ref IComponent>();
        m_IsAlive = true;
        m_IsInVehicle = false;
        m_CurrentVehicle = null;
    }
    
    //------------------------------------------
    // Component management
    //------------------------------------------
    
    /**
     * @brief Register a game component
     * @param component The component to register
     * @return True if successful, false otherwise
     */
    bool RegisterComponent(IComponent component)
    {
        if (!component)
            return false;
            
        m_GameComponents.Insert(component);
        return true;
    }
    
    /**
     * @brief Unregister a game component
     * @param component The component to unregister
     * @return True if successful, false otherwise
     */
    bool UnregisterComponent(IComponent component)
    {
        if (!component)
            return false;
            
        int index = m_GameComponents.Find(component);
        if (index < 0)
            return false;
            
        m_GameComponents.Remove(index);
        return true;
    }
    
    /**
     * @brief Find a component of a specific type
     * @param componentType The component type
     * @return The found component, or null if not found
     */
    IComponent FindComponent(typename componentType)
    {
        foreach (IComponent component : m_GameComponents)
        {
            if (component.IsInherited(componentType))
                return component;
        }
        
        return null;
    }
    
    //------------------------------------------
    // Player status
    //------------------------------------------
    
    /**
     * @brief Check if the player is alive
     * @return True if alive, false otherwise
     */
    bool IsAlive()
    {
        return m_IsAlive;
    }
    
    /**
     * @brief Set the player alive status
     * @param isAlive The alive status
     */
    void SetAlive(bool isAlive)
    {
        m_IsAlive = isAlive;
    }
    
    /**
     * @brief Check if the player is in a vehicle
     * @return True if in a vehicle, false otherwise
     */
    bool IsInVehicle()
    {
        return m_IsInVehicle;
    }
    
    /**
     * @brief Get the current vehicle
     * @return The current vehicle, or null if not in a vehicle
     */
    IEntity GetCurrentVehicle()
    {
        return m_CurrentVehicle;
    }
    
    /**
     * @brief Enter a vehicle
     * @param vehicle The vehicle to enter
     * @return True if successful, false otherwise
     */
    bool EnterVehicle(IEntity vehicle)
    {
        if (!vehicle)
            return false;
            
        m_CurrentVehicle = vehicle;
        m_IsInVehicle = true;
        return true;
    }
    
    /**
     * @brief Exit the current vehicle
     * @return True if successful, false otherwise
     */
    bool ExitVehicle()
    {
        if (!m_IsInVehicle)
            return false;
            
        m_CurrentVehicle = null;
        m_IsInVehicle = false;
        return true;
    }
    
    //------------------------------------------
    // Player actions
    //------------------------------------------
    
    /**
     * @brief Process player death
     */
    void OnDeath()
    {
        m_IsAlive = false;
        
        // Exit vehicle if in one
        if (m_IsInVehicle)
        {
            ExitVehicle();
        }
        
        // Notify components
        foreach (IComponent component : m_GameComponents)
        {
            // Call death handlers if component has them
            // (In a real implementation, we would use a more structured approach)
        }
    }
    
    /**
     * @brief Process player respawn
     * @param respawnPosition The respawn position
     * @return True if successful, false otherwise
     */
    bool OnRespawn(vector respawnPosition)
    {
        m_IsAlive = true;
        
        // Notify components
        foreach (IComponent component : m_GameComponents)
        {
            // Call respawn handlers if component has them
            // (In a real implementation, we would use a more structured approach)
        }
        
        return true;
    }
}