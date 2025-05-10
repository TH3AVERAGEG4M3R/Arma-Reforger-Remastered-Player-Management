/**
 * @brief Map Entity for managing map markers and displays
 */
 
// Import necessary classes from the engine
#include "../Input/ActionContext.c"
#include "../Input/InputActions.c"
#include "../Core/ScriptComponent.c"
#include "../Core/IEntity.c"
#include "../Core/Game.c"
class TeamMapEntityClass : ScriptComponentClass
{
}

//------------------------------------------------------------------------------------------------
/*!
    Entity for managing map displays including team indicators
*/
class TeamMapEntity : ScriptComponent
{
    // Singleton instance
    protected static TeamMapEntity s_Instance;
    
    // Array of active map markers
    protected ref array<ref MapMarkerComponent> m_MapMarkers = new array<ref MapMarkerComponent>();
    
    // Whether the map is open/visible
    protected bool m_MapVisible = false;
    
    //------------------------------------------------------------------------------------------------
    void TeamMapEntity(IEntityComponentSource src, IEntity ent, IEntity parent)
    {
        s_Instance = this;
    }
    
    //------------------------------------------------------------------------------------------------
    void ~TeamMapEntity()
    {
        if (s_Instance == this)
            s_Instance = null;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the singleton instance
     * @return The map entity instance
     */
    static TeamMapEntity GetMapInstance()
    {
        return s_Instance;
    }
    
    //------------------------------------------------------------------------------------------------
    override void OnPostInit(IEntity owner)
    {
        super.OnPostInit(owner);
        
        // Register for map open/close events
        GetGame().GetInputManager().AddActionListener("OpenMap", EActionTrigger.DOWN, OnMapOpen);
        GetGame().GetInputManager().AddActionListener("CloseMap", EActionTrigger.DOWN, OnMapClose);
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Add a map marker
     * @param marker The marker to add
     * @return True if added successfully
     */
    bool AddMarker(MapMarkerComponent marker)
    {
        if (!marker)
            return false;
            
        m_MapMarkers.Insert(marker);
        return true;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Remove a map marker
     * @param marker The marker to remove
     * @return True if removed successfully
     */
    bool RemoveMarker(MapMarkerComponent marker)
    {
        if (!marker)
            return false;
            
        int idx = m_MapMarkers.Find(marker);
        if (idx != -1)
        {
            m_MapMarkers.Remove(idx);
            return true;
        }
        
        return false;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Handle map open event
     * @param action The action context
     * @return True if handled
     */
    protected bool OnMapOpen(ActionContext action)
    {
        m_MapVisible = true;
        return true;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Handle map close event
     * @param action The action context
     * @return True if handled
     */
    protected bool OnMapClose(ActionContext action)
    {
        m_MapVisible = false;
        return true;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get all map markers
     * @return Array of map markers
     */
    array<ref MapMarkerComponent> GetMapMarkers()
    {
        return m_MapMarkers;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Check if map is visible
     * @return True if map is visible
     */
    bool IsMapVisible()
    {
        return m_MapVisible;
    }
}

/**
 * @brief Component for map markers
 */
class MapMarkerComponent
{
    // The entity this marker is attached to
    protected IEntity m_Entity;
    
    // The icon resource
    protected ResourceName m_IconResource;
    
    // The marker color
    protected Color m_Color = Color.Blue();
    
    // The display radius
    protected float m_DisplayRadius = 24.0;
    
    // The display name
    protected string m_DisplayName;
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the entity target for this marker
     * @param entity The entity to track
     */
    void SetEntityTarget(IEntity entity)
    {
        m_Entity = entity;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the icon from a resource
     * @param resourcePath Path to the icon texture
     */
    void SetIconFromResource(ResourceName resourcePath)
    {
        m_IconResource = resourcePath;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the base color
     * @param color The color to use
     */
    void SetBaseColor(Color color)
    {
        m_Color = color;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the display radius
     * @param radius The radius in pixels
     */
    void SetDisplayRadius(float radius)
    {
        m_DisplayRadius = radius;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the display name
     * @param name The name to display
     */
    void SetDisplayName(string name)
    {
        m_DisplayName = name;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the entity target
     * @return The entity target
     */
    IEntity GetEntityTarget()
    {
        return m_Entity;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the icon resource
     * @return The icon resource path
     */
    ResourceName GetIconResource()
    {
        return m_IconResource;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the base color
     * @return The base color
     */
    Color GetBaseColor()
    {
        return m_Color;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the display radius
     * @return The display radius
     */
    float GetDisplayRadius()
    {
        return m_DisplayRadius;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the display name
     * @return The display name
     */
    string GetDisplayName()
    {
        return m_DisplayName;
    }
}