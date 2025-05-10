// ScriptComponent for ARMA Reforger

class ScriptComponentClass
{
}

class ScriptComponent : GenericComponent
{
    // Constructor
    void ScriptComponent() {}
    
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
    static ScriptComponent Cast(GenericComponent component)
    {
        return null;
    }
}