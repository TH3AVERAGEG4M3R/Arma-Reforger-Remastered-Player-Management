// GenericEntity for ARMA Reforger

class IEntitySource
{
}

class GenericEntity : IEntity
{
    // Constructor
    void GenericEntity(IEntitySource src, IEntity parent) {}
    
    // Get entity position
    vector GetOrigin()
    {
        return "0 0 0";
    }
    
    // Get transform axis
    vector GetTransformAxis(int axis)
    {
        return "0 0 0";
    }
    
    // Find component
    GenericComponent FindComponent(GenericComponentClass componentClass)
    {
        return null;
    }
    
    // Static cast method
    static GenericEntity Cast(IEntity entity)
    {
        return null;
    }
}