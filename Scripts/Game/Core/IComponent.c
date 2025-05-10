// IComponent.c - Component interface for ARMA Reforger
// This class defines the base component interface that all entity components implement

// Forward declaration for IEntity
class IEntity;

/**
 * @brief Interface for all entity components
 */
class IComponent
{
    // Component ID
    protected int m_ID;
    
    // Component name
    protected string m_Name;
    
    // Component owner
    protected IEntity m_Owner;
    
    // Whether the component is active
    protected bool m_IsActive;
    
    // Constructor
    void IComponent(string name = "")
    {
        m_ID = 0;
        m_Name = name;
        m_Owner = null;
        m_IsActive = true;
    }
    
    //------------------------------------------
    // Lifecycle methods
    //------------------------------------------
    
    /**
     * @brief Initialize the component
     * Called after the component is created and attached to an entity
     */
    void OnInit()
    {
        // Base implementation does nothing
    }
    
    /**
     * @brief Called when the component is activated
     */
    void OnActivate()
    {
        m_IsActive = true;
    }
    
    /**
     * @brief Called when the component is deactivated
     */
    void OnDeactivate()
    {
        m_IsActive = false;
    }
    
    /**
     * @brief Called when the component is destroyed
     */
    void OnDestroy()
    {
        // Base implementation does nothing
    }
    
    //------------------------------------------
    // Getters and setters
    //------------------------------------------
    
    /**
     * @brief Get the component ID
     * @return The component ID
     */
    int GetID()
    {
        return m_ID;
    }
    
    /**
     * @brief Set the component ID
     * @param id The component ID
     */
    void SetID(int id)
    {
        m_ID = id;
    }
    
    /**
     * @brief Get the component name
     * @return The component name
     */
    string GetName()
    {
        return m_Name;
    }
    
    /**
     * @brief Set the component name
     * @param name The component name
     */
    void SetName(string name)
    {
        m_Name = name;
    }
    
    /**
     * @brief Get the component owner
     * @return The component owner
     */
    IEntity GetOwner()
    {
        return m_Owner;
    }
    
    /**
     * @brief Set the component owner
     * @param owner The component owner
     */
    void SetOwner(IEntity owner)
    {
        m_Owner = owner;
    }
    
    /**
     * @brief Check if the component is active
     * @return True if active, false otherwise
     */
    bool IsActive()
    {
        return m_IsActive;
    }
    
    /**
     * @brief Set the component active state
     * @param isActive The active state
     */
    void SetActive(bool isActive)
    {
        if (m_IsActive == isActive)
            return;
            
        if (isActive)
            OnActivate();
        else
            OnDeactivate();
    }
    
    /**
     * @brief Check if this component is or inherits from the specified type
     * @param type The type to check
     * @return True if this component is or inherits from the specified type, false otherwise
     */
    bool IsInherited(typename type)
    {
        return this.Type().IsInherited(type);
    }
}