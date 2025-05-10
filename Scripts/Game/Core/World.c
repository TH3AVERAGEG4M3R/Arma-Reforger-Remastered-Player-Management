// World.c - Game world class for ARMA Reforger
// This class represents the game world and manages entities within it

#include "IEntity.c"
#include "Collections.c"

/**
 * @brief Class representing the game world
 */
class World
{
    // All entities in the world
    protected ref map<int, ref IEntity> m_Entities;
    
    // Constructor
    void World()
    {
        m_Entities = new map<int, ref IEntity>();
    }
    
    /**
     * @brief Add an entity to the world
     * @param entity The entity to add
     * @return True if successful, false otherwise
     */
    bool AddEntity(IEntity entity)
    {
        if (!entity)
            return false;
            
        // Set entity world
        entity.SetWorld(this);
        
        // Add to entities map
        int id = entity.GetID().GetValue();
        m_Entities[id] = entity;
        
        return true;
    }
    
    /**
     * @brief Remove an entity from the world
     * @param entity The entity to remove
     * @return True if successful, false otherwise
     */
    bool RemoveEntity(IEntity entity)
    {
        if (!entity)
            return false;
            
        int id = entity.GetID().GetValue();
        return RemoveEntityByID(id);
    }
    
    /**
     * @brief Remove an entity from the world by ID
     * @param id The entity ID
     * @return True if successful, false otherwise
     */
    bool RemoveEntityByID(int id)
    {
        if (!m_Entities.Contains(id))
            return false;
            
        // Clear entity world reference
        IEntity entity = m_Entities[id];
        if (entity)
        {
            entity.SetWorld(null);
        }
        
        // Remove from entities map
        m_Entities.Remove(id);
        
        return true;
    }
    
    /**
     * @brief Find an entity by ID
     * @param id The entity ID
     * @return The found entity, or null if not found
     */
    IEntity FindEntityByID(int id)
    {
        return m_Entities.Get(id);
    }
    
    /**
     * @brief Find an entity by ID
     * @param id The entity ID
     * @return The found entity, or null if not found
     */
    IEntity FindEntityByID(EntityID id)
    {
        if (!id)
            return null;
            
        return FindEntityByID(id.GetValue());
    }
    
    /**
     * @brief Find entities by name
     * @param name The entity name
     * @return Array of found entities
     */
    array<ref IEntity> FindEntitiesByName(string name)
    {
        array<ref IEntity> result = new array<ref IEntity>();
        
        foreach (int id, ref IEntity entity : m_Entities)
        {
            if (entity.GetName() == name)
            {
                result.Insert(entity);
            }
        }
        
        return result;
    }
    
    /**
     * @brief Get all entities in the world
     * @return Array of all entities
     */
    array<ref IEntity> GetAllEntities()
    {
        array<ref IEntity> result = new array<ref IEntity>();
        
        foreach (int id, ref IEntity entity : m_Entities)
        {
            result.Insert(entity);
        }
        
        return result;
    }
    
    /**
     * @brief Get the number of entities in the world
     * @return The number of entities
     */
    int GetEntityCount()
    {
        return m_Entities.Count();
    }
}