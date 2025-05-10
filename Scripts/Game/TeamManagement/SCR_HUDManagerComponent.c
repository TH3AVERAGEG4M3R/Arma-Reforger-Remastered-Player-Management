#include "../Input/ActionContext.c"

class TeamHUDManagerComponentClass : ScriptComponentClass
{
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