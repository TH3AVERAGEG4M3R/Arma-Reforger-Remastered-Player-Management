// Collections for ARMA Reforger

class array<Class T>
{
    void array() {}
    
    int Count()
    {
        return 0;
    }
    
    T Get(int index)
    {
        return null;
    }
    
    void Insert(T item)
    {
    }
    
    bool Remove(T item)
    {
        return true;
    }
    
    void RemoveAt(int index)
    {
    }
    
    void Clear()
    {
    }
    
    int Find(T item)
    {
        return -1;
    }
    
    void Sort()
    {
    }
}

class map<Class K, Class V>
{
    void map() {}
    
    void Set(K key, V value)
    {
    }
    
    V Get(K key)
    {
        return null;
    }
    
    bool Contains(K key)
    {
        return false;
    }
    
    bool Remove(K key)
    {
        return true;
    }
    
    void Clear()
    {
    }
    
    int Count()
    {
        return 0;
    }
}

class EntityID
{
    private int id;
    
    void EntityID(int entityId = 0)
    {
        id = entityId;
    }
    
    int GetID()
    {
        return id;
    }
    
    bool IsValid()
    {
        return id != 0;
    }
}