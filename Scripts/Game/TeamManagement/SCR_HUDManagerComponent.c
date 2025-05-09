/**
 * @brief HUD Manager Component for managing HUD elements
 */
class SCR_HUDManagerComponentClass : ScriptComponentClass
{
}

//------------------------------------------------------------------------------------------------
/*!
    Component for managing HUD elements including team indicators
*/
class SCR_HUDManagerComponent : ScriptComponent
{
    // Singleton instance
    protected static SCR_HUDManagerComponent s_Instance;
    
    // Array of active HUD icons
    protected ref array<ref HudIcon> m_HudIcons = new array<ref HudIcon>();
    
    // Whether the HUD is visible
    protected bool m_HudVisible = true;
    
    //------------------------------------------------------------------------------------------------
    void SCR_HUDManagerComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
    {
        s_Instance = this;
    }
    
    //------------------------------------------------------------------------------------------------
    void ~SCR_HUDManagerComponent()
    {
        if (s_Instance == this)
            s_Instance = null;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the singleton instance
     * @return The HUD manager instance
     */
    static SCR_HUDManagerComponent GetInstance()
    {
        return s_Instance;
    }
    
    //------------------------------------------------------------------------------------------------
    override void OnPostInit(IEntity owner)
    {
        super.OnPostInit(owner);
        
        // Register for HUD update events
        GetGame().GetInputManager().AddActionListener("ToggleHUD", EActionTrigger.DOWN, ToggleHUD);
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Add a HUD icon
     * @param icon The icon to add
     * @return True if added successfully
     */
    bool AddHudIcon(HudIcon icon)
    {
        if (!icon)
            return false;
            
        m_HudIcons.Insert(icon);
        return true;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Remove a HUD icon
     * @param icon The icon to remove
     * @return True if removed successfully
     */
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
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Toggle HUD visibility
     * @param action The action context
     * @return True if handled
     */
    protected bool ToggleHUD(ActionContext action)
    {
        m_HudVisible = !m_HudVisible;
        return true;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get all HUD icons
     * @return Array of HUD icons
     */
    array<ref HudIcon> GetHudIcons()
    {
        return m_HudIcons;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Check if HUD is visible
     * @return True if HUD is visible
     */
    bool IsHudVisible()
    {
        return m_HudVisible;
    }
}