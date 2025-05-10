// ScriptedWidgetComponent for ARMA Reforger UI

class ScriptedWidgetComponent : GenericComponent
{
    // Constructor
    void ScriptedWidgetComponent() {}
    
    // Initialize component
    override void OnPostInit(IEntity owner)
    {
        super.OnPostInit(owner);
    }
    
    // Cleanup component
    override void OnDelete(IEntity owner)
    {
        super.OnDelete(owner);
    }
    
    // Static cast method
    static ScriptedWidgetComponent Cast(GenericComponent component)
    {
        return null;
    }
}