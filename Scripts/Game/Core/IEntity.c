// IEntity.c - Entity interface for ARMA Reforger
// This class defines the base entity interface that all game entities implement

#include "IComponent.c"
#include "EntityID.c"

/**
 * @brief Interface for all game entities
 */
class IEntity
{
    // Entity ID
    protected EntityID m_ID;
    
    // Entity name
    protected string m_Name;
    
    // Entity components
    protected ref array<ref IComponent> m_Components;
    
    // Entity world
    protected ref World m_World;
    
    // Constructor
    void IEntity(string name = "")
    {
        m_ID = new EntityID();
        m_Name = name;
        m_Components = new array<ref IComponent>();
        m_World = null;
    }
    
    //------------------------------------------
    // Getters and setters
    //------------------------------------------
    
    /**
     * @brief Get the entity ID
     * @return The entity ID
     */
    EntityID GetID()
    {
        return m_ID;
    }
    
    /**
     * @brief Get the entity name
     * @return The entity name
     */
    string GetName()
    {
        return m_Name;
    }
    
    /**
     * @brief Set the entity name
     * @param name The entity name
     */
    void SetName(string name)
    {
        m_Name = name;
    }
    
    /**
     * @brief Get the entity world
     * @return The entity world
     */
    World GetWorld()
    {
        return m_World;
    }
    
    /**
     * @brief Set the entity world
     * @param world The entity world
     */
    void SetWorld(World world)
    {
        m_World = world;
    }
    
    //------------------------------------------
    // Component management
    //------------------------------------------
    
    /**
     * @brief Find a component by type
     * @param componentType The component type
     * @return The found component, or null if not found
     */
    IComponent FindComponent(typename componentType)
    {
        foreach (IComponent component : m_Components)
        {
            if (component.IsInherited(componentType))
                return component;
        }
        
        return null;
    }
    
    /**
     * @brief Add a component to the entity
     * @param component The component to add
     * @return True if successful, false otherwise
     */
    bool AddComponent(IComponent component)
    {
        if (!component)
            return false;
            
        // Set component owner
        component.SetOwner(this);
        
        // Add to components list
        m_Components.Insert(component);
        
        return true;
    }
    
    /**
     * @brief Remove a component from the entity
     * @param component The component to remove
     * @return True if successful, false otherwise
     */
    bool RemoveComponent(IComponent component)
    {
        if (!component)
            return false;
            
        // Find the component
        int index = m_Components.Find(component);
        if (index < 0)
            return false;
            
        // Clear owner reference
        component.SetOwner(null);
        
        // Remove from components list
        m_Components.Remove(index);
        
        return true;
    }
    
    /**
     * @brief Get all components
     * @return The components array
     */
    array<ref IComponent> GetComponents()
    {
        return m_Components;
    }
}