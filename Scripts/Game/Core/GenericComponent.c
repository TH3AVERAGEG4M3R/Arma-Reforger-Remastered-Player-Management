// GenericComponent base class for ARMA Reforger

class GenericComponentClass
{
}

class GenericComponent
{
    // Constructor
    void GenericComponent() {}
    
    // Initialize component
    void OnPostInit(IEntity owner) {}
    
    // FindComponent helper
    static GenericComponent Cast(GenericComponent component)
    {
        return component;
    }
    
    // Get component's owner entity
    IEntity GetOwner()
    {
        return null;
    }
    
    // Cleanup method
    void OnDelete(IEntity owner) {}
    
    // Find component on entity
    GenericComponent FindComponent(GenericComponentClass componentClass)
    {
        return null;
    }
}