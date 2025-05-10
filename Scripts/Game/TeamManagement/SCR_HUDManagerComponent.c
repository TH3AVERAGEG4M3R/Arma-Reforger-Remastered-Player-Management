#include "../Input/ActionContext.c"
#include "../Input/InputActions.c"
#include "../Core/ScriptComponent.c"
#include "../Core/IEntity.c"
#include "../Core/Game.c"

class TeamHUDManagerComponentClass : ScriptComponentClass
{
}

/**
 * @brief HUD Icon class for displaying icons on the HUD
 */
class HudIcon
{
    // The entity this icon is attached to
    protected IEntity m_Entity;
    
    // The icon resource
    protected ResourceName m_IconResource;
    
    // The icon color
    protected Color m_Color = Color.Green();
    
    // The display size
    protected float m_DisplaySize = 16.0;
    
    // The display name
    protected string m_DisplayName;
    
    // Whether to show name
    protected bool m_ShowName = true;
    
    // Whether to show icon
    protected bool m_ShowIcon = true;
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the entity target for this icon
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
     * @brief Set the display size
     * @param size The size in pixels
     */
    void SetDisplaySize(float size)
    {
        m_DisplaySize = size;
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
     * @brief Set whether to show the name
     * @param show True to show name, false to hide
     */
    void SetShowName(bool show)
    {
        m_ShowName = show;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set whether to show the icon
     * @param show True to show icon, false to hide
     */
    void SetShowIcon(bool show)
    {
        m_ShowIcon = show;
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
     * @brief Get the display size
     * @return The display size
     */
    float GetDisplaySize()
    {
        return m_DisplaySize;
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
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Check if name should be shown
     * @return True if name should be shown
     */
    bool ShouldShowName()
    {
        return m_ShowName;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Check if icon should be shown
     * @return True if icon should be shown
     */
    bool ShouldShowIcon()
    {
        return m_ShowIcon;
    }
}

class TeamHUDManagerComponent : ScriptComponent
{
    // Singleton instance
    protected static TeamHUDManagerComponent s_Instance;

    // Array of active HUD icons 
    protected ref array<ref HudIcon> m_HudIcons = new array<ref HudIcon>();

    // Whether the HUD is visible
    protected bool m_HudVisible = true;

    void TeamHUDManagerComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
    {
        s_Instance = this;
    }

    void ~TeamHUDManagerComponent()
    {
        if (s_Instance == this)
            s_Instance = null;
    }

    static TeamHUDManagerComponent GetInstance()
    {
        return s_Instance;
    }

    override void OnPostInit(IEntity owner)
    {
        super.OnPostInit(owner);
        GetGame().GetInputManager().AddActionListener("ToggleHUD", EActionTrigger.DOWN, ToggleHUD);
    }

    bool AddHudIcon(HudIcon icon)
    {
        if (!icon)
            return false;
        m_HudIcons.Insert(icon);
        return true;
    }

    bool RemoveHudIcon(HudIcon icon)
    {
        if (!icon)
            return false;
        int idx = m_HudIcons.Find(icon);
        if (idx != -1)
        {
            m_HudIcons.Remove(idx);
            return true;
        }
        return false;
    }

    protected bool ToggleHUD(ActionContext action)
    {
        m_HudVisible = !m_HudVisible;
        return true;
    }

    array<ref HudIcon> GetHudIcons()
    {
        return m_HudIcons;
    }

    bool IsHudVisible()
    {
        return m_HudVisible;
    }
}