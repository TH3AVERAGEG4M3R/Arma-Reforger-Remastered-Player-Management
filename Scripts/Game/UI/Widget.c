// Widget.c - Base UI widget class for ARMA Reforger
// This class defines the base UI element for user interfaces

class Widget
{
    // Widget properties
    protected string m_Name;               // Unique name of the widget
    protected Widget m_Parent;             // Parent widget
    protected ref array<ref Widget> m_Children; // Child widgets
    protected bool m_IsVisible;            // Is the widget visible?
    protected bool m_IsEnabled;            // Is the widget enabled?
    protected int m_PosX;                  // X position relative to parent
    protected int m_PosY;                  // Y position relative to parent
    protected int m_Width;                 // Width of the widget
    protected int m_Height;                // Height of the widget
    protected int m_ZOrder;                // Z-order for overlapping widgets
    protected string m_Style;              // Style class name
    
    // Constructor
    void Widget(string name = "", Widget parent = null)
    {
        m_Name = name;
        m_Parent = parent;
        m_Children = new array<ref Widget>();
        m_IsVisible = true;
        m_IsEnabled = true;
        m_PosX = 0;
        m_PosY = 0;
        m_Width = 100;
        m_Height = 30;
        m_ZOrder = 0;
        m_Style = "";
        
        // Add to parent if provided
        if (m_Parent)
        {
            m_Parent.AddChild(this);
        }
    }
    
    //------------------------------------------
    // Child management
    //------------------------------------------
    
    /**
     * @brief Add a child widget
     * @param child The child widget to add
     */
    void AddChild(Widget child)
    {
        if (!child)
            return;
            
        // Set parent reference
        child.SetParent(this);
        
        // Add to children list
        m_Children.Insert(child);
    }
    
    /**
     * @brief Remove a child widget
     * @param child The child widget to remove
     */
    void RemoveChild(Widget child)
    {
        if (!child)
            return;
            
        // Find the child
        int index = m_Children.Find(child);
        if (index >= 0)
        {
            // Clear parent reference
            child.SetParent(null);
            
            // Remove from children list
            m_Children.Remove(index);
        }
    }
    
    /**
     * @brief Get a child widget by name
     * @param name The name of the child to find
     * @return The found child widget, or null if not found
     */
    Widget FindWidget(string name)
    {
        // Check if this is the widget we're looking for
        if (m_Name == name)
            return this;
            
        // Search children
        foreach (Widget child : m_Children)
        {
            Widget found = child.FindWidget(name);
            if (found)
                return found;
        }
        
        return null;
    }
    
    //------------------------------------------
    // Getters and setters
    //------------------------------------------
    
    /**
     * @brief Get the widget name
     * @return The widget name
     */
    string GetName()
    {
        return m_Name;
    }
    
    /**
     * @brief Set the widget name
     * @param name The new name
     */
    void SetName(string name)
    {
        m_Name = name;
    }
    
    /**
     * @brief Get the parent widget
     * @return The parent widget
     */
    Widget GetParent()
    {
        return m_Parent;
    }
    
    /**
     * @brief Set the parent widget
     * @param parent The new parent
     */
    void SetParent(Widget parent)
    {
        m_Parent = parent;
    }
    
    /**
     * @brief Get all child widgets
     * @return Array of child widgets
     */
    array<ref Widget> GetChildren()
    {
        return m_Children;
    }
    
    /**
     * @brief Check if the widget is visible
     * @return True if visible, false otherwise
     */
    bool IsVisible()
    {
        return m_IsVisible;
    }
    
    /**
     * @brief Set visibility
     * @param visible The new visibility state
     */
    void SetVisible(bool visible)
    {
        m_IsVisible = visible;
        
        // Recursive visibility update
        foreach (Widget child : m_Children)
        {
            child.SetVisible(visible);
        }
    }
    
    /**
     * @brief Check if the widget is enabled
     * @return True if enabled, false otherwise
     */
    bool IsEnabled()
    {
        return m_IsEnabled;
    }
    
    /**
     * @brief Set enabled state
     * @param enabled The new enabled state
     */
    void SetEnabled(bool enabled)
    {
        m_IsEnabled = enabled;
    }
    
    /**
     * @brief Get the X position
     * @return The X position
     */
    int GetPosX()
    {
        return m_PosX;
    }
    
    /**
     * @brief Get the Y position
     * @return The Y position
     */
    int GetPosY()
    {
        return m_PosY;
    }
    
    /**
     * @brief Set the position
     * @param x The new X position
     * @param y The new Y position
     */
    void SetPosition(int x, int y)
    {
        m_PosX = x;
        m_PosY = y;
    }
    
    /**
     * @brief Get the width
     * @return The width
     */
    int GetWidth()
    {
        return m_Width;
    }
    
    /**
     * @brief Get the height
     * @return The height
     */
    int GetHeight()
    {
        return m_Height;
    }
    
    /**
     * @brief Set the size
     * @param width The new width
     * @param height The new height
     */
    void SetSize(int width, int height)
    {
        m_Width = width;
        m_Height = height;
    }
    
    /**
     * @brief Get the Z-order
     * @return The Z-order
     */
    int GetZOrder()
    {
        return m_ZOrder;
    }
    
    /**
     * @brief Set the Z-order
     * @param zOrder The new Z-order
     */
    void SetZOrder(int zOrder)
    {
        m_ZOrder = zOrder;
    }
    
    /**
     * @brief Get the style class
     * @return The style class
     */
    string GetStyle()
    {
        return m_Style;
    }
    
    /**
     * @brief Set the style class
     * @param style The new style class
     */
    void SetStyle(string style)
    {
        m_Style = style;
    }
    
    //------------------------------------------
    // Event handling
    //------------------------------------------
    
    /**
     * @brief Called when the widget is created
     */
    void OnCreate()
    {
        // Base implementation does nothing
    }
    
    /**
     * @brief Called when the widget is destroyed
     */
    void OnDestroy()
    {
        // Base implementation does nothing
    }
    
    /**
     * @brief Called when the mouse button is pressed on this widget
     * @param x X position relative to widget
     * @param y Y position relative to widget
     * @param button The button that was pressed
     * @return True if the event was handled, false otherwise
     */
    bool OnMouseDown(int x, int y, int button)
    {
        // Base implementation does nothing
        return false;
    }
    
    /**
     * @brief Called when the mouse button is released on this widget
     * @param x X position relative to widget
     * @param y Y position relative to widget
     * @param button The button that was released
     * @return True if the event was handled, false otherwise
     */
    bool OnMouseUp(int x, int y, int button)
    {
        // Base implementation does nothing
        return false;
    }
    
    /**
     * @brief Called when the mouse moves over this widget
     * @param x X position relative to widget
     * @param y Y position relative to widget
     * @return True if the event was handled, false otherwise
     */
    bool OnMouseMove(int x, int y)
    {
        // Base implementation does nothing
        return false;
    }
    
    /**
     * @brief Called when the mouse enters this widget
     * @param x X position relative to widget
     * @param y Y position relative to widget
     * @return True if the event was handled, false otherwise
     */
    bool OnMouseEnter(int x, int y)
    {
        // Base implementation does nothing
        return false;
    }
    
    /**
     * @brief Called when the mouse leaves this widget
     * @param x X position relative to widget
     * @param y Y position relative to widget
     * @return True if the event was handled, false otherwise
     */
    bool OnMouseLeave(int x, int y)
    {
        // Base implementation does nothing
        return false;
    }
    
    /**
     * @brief Called when a key is pressed while this widget has focus
     * @param key The key that was pressed
     * @return True if the event was handled, false otherwise
     */
    bool OnKeyDown(int key)
    {
        // Base implementation does nothing
        return false;
    }
    
    /**
     * @brief Called when a key is released while this widget has focus
     * @param key The key that was released
     * @return True if the event was handled, false otherwise
     */
    bool OnKeyUp(int key)
    {
        // Base implementation does nothing
        return false;
    }
    
    /**
     * @brief Called when this widget gains focus
     * @return True if the event was handled, false otherwise
     */
    bool OnFocus()
    {
        // Base implementation does nothing
        return false;
    }
    
    /**
     * @brief Called when this widget loses focus
     * @return True if the event was handled, false otherwise
     */
    bool OnFocusLost()
    {
        // Base implementation does nothing
        return false;
    }
}