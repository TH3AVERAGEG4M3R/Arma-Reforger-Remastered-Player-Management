// Widget.c - Widget classes for ARMA Reforger UI
// This file contains the base Widget class and common event types

/**
 * @brief Base class for UI widgets in the ARMA Reforger framework
 */
class Widget
{
    // Widget name
    protected string m_Name;
    
    // Widget position and size
    protected vector2 m_Position;
    protected vector2 m_Size;
    
    // Parent widget
    protected Widget m_Parent;
    
    // Child widgets
    protected ref array<ref Widget> m_Children = new array<ref Widget>();
    
    // Visibility
    protected bool m_IsVisible = true;
    
    // Internal widget reference for the actual UI system
    protected int m_InternalWidgetID;
    
    /**
     * @brief Constructor
     * @param name The name of the widget
     */
    void Widget(string name = "")
    {
        m_Name = name;
        m_Position = Vector2(0, 0);
        m_Size = Vector2(100, 100);
        m_Parent = null;
    }
    
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
     * @param name The new widget name
     */
    void SetName(string name)
    {
        m_Name = name;
    }
    
    /**
     * @brief Get the widget position
     * @return The widget position
     */
    vector2 GetPosition()
    {
        return m_Position;
    }
    
    /**
     * @brief Set the widget position
     * @param position The new widget position
     */
    void SetPosition(vector2 position)
    {
        m_Position = position;
    }
    
    /**
     * @brief Get the widget size
     * @return The widget size
     */
    vector2 GetSize()
    {
        return m_Size;
    }
    
    /**
     * @brief Set the widget size
     * @param size The new widget size
     */
    void SetSize(vector2 size)
    {
        m_Size = size;
    }
    
    /**
     * @brief Get the parent widget
     * @return The parent widget, or null if the widget has no parent
     */
    Widget GetParent()
    {
        return m_Parent;
    }
    
    /**
     * @brief Set the parent widget
     * @param parent The new parent widget
     */
    void SetParent(Widget parent)
    {
        if (m_Parent)
        {
            m_Parent.RemoveChild(this);
        }
        
        m_Parent = parent;
        
        if (m_Parent)
        {
            m_Parent.AddChild(this);
        }
    }
    
    /**
     * @brief Add a child widget
     * @param child The child widget to add
     */
    void AddChild(Widget child)
    {
        if (!child)
            return;
            
        if (m_Children.Find(child) == -1)
        {
            m_Children.Insert(child);
        }
    }
    
    /**
     * @brief Remove a child widget
     * @param child The child widget to remove
     */
    void RemoveChild(Widget child)
    {
        if (!child)
            return;
            
        int index = m_Children.Find(child);
        if (index != -1)
        {
            m_Children.Remove(index);
        }
    }
    
    /**
     * @brief Get all child widgets
     * @return An array of child widgets
     */
    array<ref Widget> GetChildren()
    {
        return m_Children;
    }
    
    /**
     * @brief Check if the widget is visible
     * @return True if the widget is visible, false otherwise
     */
    bool IsVisible()
    {
        return m_IsVisible;
    }
    
    /**
     * @brief Set the visibility of the widget
     * @param visible The new visibility state
     */
    void SetVisible(bool visible)
    {
        m_IsVisible = visible;
    }
    
    /**
     * @brief Find a child widget by name
     * @param name The name of the widget to find
     * @return The found widget, or null if not found
     */
    Widget FindAnyWidget(string name)
    {
        if (m_Name == name)
            return this;
            
        foreach (Widget child : m_Children)
        {
            Widget found = child.FindAnyWidget(name);
            if (found)
                return found;
        }
        
        return null;
    }
    
    /**
     * @brief Clear all items in a list widget (placeholder for list widgets)
     */
    void ClearItems()
    {
        // Base implementation does nothing
    }
    
    /**
     * @brief Add an event handler for the widget
     * @param handler The event handler to add
     */
    void AddHandler(Class handler)
    {
        // Base implementation does nothing
    }
}

/**
 * @brief Basic button widget
 */
class ButtonWidget : Widget
{
    // Button text
    protected string m_Text;
    
    // Button state
    protected bool m_IsEnabled = true;
    
    // Button color
    protected vector m_Color = Vector(1, 1, 1);
    
    // Event handlers
    protected ref array<Class> m_EventHandlers = new array<Class>();
    
    /**
     * @brief Constructor
     * @param name The name of the button
     */
    void ButtonWidget(string name = "")
    {
        m_Name = name;
        m_Text = "";
    }
    
    /**
     * @brief Get the button text
     * @return The button text
     */
    string GetText()
    {
        return m_Text;
    }
    
    /**
     * @brief Set the button text
     * @param text The new button text
     */
    void SetText(string text)
    {
        m_Text = text;
    }
    
    /**
     * @brief Check if the button is enabled
     * @return True if the button is enabled, false otherwise
     */
    bool IsEnabled()
    {
        return m_IsEnabled;
    }
    
    /**
     * @brief Set the enabled state of the button
     * @param enabled The new enabled state
     */
    void SetEnabled(bool enabled)
    {
        m_IsEnabled = enabled;
    }
    
    /**
     * @brief Get the button color
     * @return The button color
     */
    vector GetColor()
    {
        return m_Color;
    }
    
    /**
     * @brief Set the button color
     * @param color The new button color
     */
    void SetColor(vector color)
    {
        m_Color = color;
    }
    
    /**
     * @brief Add an event handler for the button
     * @param handler The event handler to add
     */
    override void AddHandler(Class handler)
    {
        if (!handler)
            return;
            
        m_EventHandlers.Insert(handler);
    }
    
    /**
     * @brief Trigger a click event
     */
    void Click()
    {
        if (!m_IsEnabled)
            return;
            
        foreach (Class handler : m_EventHandlers)
        {
            ButtonHandlerBase buttonHandler = ButtonHandlerBase.Cast(handler);
            if (buttonHandler)
            {
                buttonHandler.OnClick(this);
            }
        }
    }
}

/**
 * @brief Text widget for displaying text
 */
class TextWidget : Widget
{
    // Text content
    protected string m_Text;
    
    // Text color
    protected vector m_Color = Vector(1, 1, 1);
    
    /**
     * @brief Constructor
     * @param name The name of the text widget
     */
    void TextWidget(string name = "")
    {
        m_Name = name;
        m_Text = "";
    }
    
    /**
     * @brief Get the text content
     * @return The text content
     */
    string GetText()
    {
        return m_Text;
    }
    
    /**
     * @brief Set the text content
     * @param text The new text content
     */
    void SetText(string text)
    {
        m_Text = text;
    }
    
    /**
     * @brief Get the text color
     * @return The text color
     */
    vector GetColor()
    {
        return m_Color;
    }
    
    /**
     * @brief Set the text color
     * @param color The new text color
     */
    void SetColor(vector color)
    {
        m_Color = color;
    }
}

/**
 * @brief Edit box widget for text input
 */
class EditBoxWidget : Widget
{
    // Text content
    protected string m_Text;
    
    // Text color
    protected vector m_Color = Vector(1, 1, 1);
    
    // Whether the edit box is enabled
    protected bool m_IsEnabled = true;
    
    /**
     * @brief Constructor
     * @param name The name of the edit box
     */
    void EditBoxWidget(string name = "")
    {
        m_Name = name;
        m_Text = "";
    }
    
    /**
     * @brief Get the text content
     * @return The text content
     */
    string GetText()
    {
        return m_Text;
    }
    
    /**
     * @brief Set the text content
     * @param text The new text content
     */
    void SetText(string text)
    {
        m_Text = text;
    }
    
    /**
     * @brief Get the text color
     * @return The text color
     */
    vector GetColor()
    {
        return m_Color;
    }
    
    /**
     * @brief Set the text color
     * @param color The new text color
     */
    void SetColor(vector color)
    {
        m_Color = color;
    }
    
    /**
     * @brief Check if the edit box is enabled
     * @return True if the edit box is enabled, false otherwise
     */
    bool IsEnabled()
    {
        return m_IsEnabled;
    }
    
    /**
     * @brief Set the enabled state of the edit box
     * @param enabled The new enabled state
     */
    void SetEnabled(bool enabled)
    {
        m_IsEnabled = enabled;
    }
}

/**
 * @brief Base class for button handlers
 */
class ButtonHandlerBase
{
    /**
     * @brief Called when the button is clicked
     * @param button The button that was clicked
     */
    void OnClick(ButtonWidget button)
    {
        // Base implementation does nothing
    }
}