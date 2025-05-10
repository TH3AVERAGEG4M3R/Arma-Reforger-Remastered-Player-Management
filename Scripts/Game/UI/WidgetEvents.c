// WidgetEvents.c - UI widget event handling for ARMA Reforger
// This file defines event handling interfaces for UI widgets

#include "Widget.c"
#include "SCR_ButtonHandler.c"

/**
 * @brief Mouse button enum
 */
enum EMouseButton
{
    LEFT = 0,
    RIGHT = 1,
    MIDDLE = 2
}

/**
 * @brief Key event enum
 */
enum EKeyEvent
{
    KEY_DOWN = 0,
    KEY_UP = 1,
    KEY_PRESS = 2
}

/**
 * @brief Mouse event enum
 */
enum EMouseEvent
{
    MOUSE_DOWN = 0,
    MOUSE_UP = 1,
    MOUSE_MOVE = 2,
    MOUSE_ENTER = 3,
    MOUSE_LEAVE = 4,
    MOUSE_WHEEL = 5
}

/**
 * @brief Widget event handler
 */
class WidgetEventHandler
{
    // Protected reference to the widget
    protected Widget m_Widget;
    
    // Constructor
    void WidgetEventHandler(Widget widget = null)
    {
        m_Widget = widget;
    }
    
    /**
     * @brief Get the widget
     * @return The widget
     */
    Widget GetWidget()
    {
        return m_Widget;
    }
    
    /**
     * @brief Set the widget
     * @param widget The widget
     */
    void SetWidget(Widget widget)
    {
        m_Widget = widget;
    }
    
    /**
     * @brief Handle a mouse event
     * @param event The mouse event
     * @param x Mouse X position
     * @param y Mouse Y position
     * @param button Mouse button
     * @param wheelDelta Mouse wheel delta
     * @return True if the event was handled, false otherwise
     */
    bool HandleMouseEvent(EMouseEvent event, int x, int y, EMouseButton button = EMouseButton.LEFT, int wheelDelta = 0)
    {
        if (!m_Widget || !m_Widget.IsEnabled())
            return false;
            
        switch (event)
        {
            case EMouseEvent.MOUSE_DOWN:
                return m_Widget.OnMouseDown(x, y, button);
                
            case EMouseEvent.MOUSE_UP:
                return m_Widget.OnMouseUp(x, y, button);
                
            case EMouseEvent.MOUSE_MOVE:
                return m_Widget.OnMouseMove(x, y);
                
            case EMouseEvent.MOUSE_ENTER:
                return m_Widget.OnMouseEnter(x, y);
                
            case EMouseEvent.MOUSE_LEAVE:
                return m_Widget.OnMouseLeave(x, y);
                
            case EMouseEvent.MOUSE_WHEEL:
                // Mouse wheel events are not directly supported in the base Widget class
                return false;
        }
        
        return false;
    }
    
    /**
     * @brief Handle a key event
     * @param event The key event
     * @param key Key code
     * @return True if the event was handled, false otherwise
     */
    bool HandleKeyEvent(EKeyEvent event, int key)
    {
        if (!m_Widget || !m_Widget.IsEnabled())
            return false;
            
        switch (event)
        {
            case EKeyEvent.KEY_DOWN:
                return m_Widget.OnKeyDown(key);
                
            case EKeyEvent.KEY_UP:
                return m_Widget.OnKeyUp(key);
                
            case EKeyEvent.KEY_PRESS:
                // Key press events are not directly supported in the base Widget class
                return false;
        }
        
        return false;
    }
}

/**
 * @brief Button handler to convert SCR_ButtonHandler events to widget events
 */
class ButtonWidgetHandler : SCR_ButtonHandler
{
    // The widget to handle events for
    protected Widget m_Widget;
    
    // Constructor
    void ButtonWidgetHandler(Widget widget = null)
    {
        m_Widget = widget;
    }
    
    /**
     * @brief Get the widget
     * @return The widget
     */
    Widget GetWidget()
    {
        return m_Widget;
    }
    
    /**
     * @brief Set the widget
     * @param widget The widget
     */
    void SetWidget(Widget widget)
    {
        m_Widget = widget;
    }
    
    // Override SCR_ButtonHandler methods to forward to widget
    override bool OnMouseDown(Widget w, int x, int y, EMouseButton button)
    {
        if (m_Widget && w == m_Widget)
        {
            return m_Widget.OnMouseDown(x, y, button);
        }
        
        return false;
    }
    
    override bool OnMouseUp(Widget w, int x, int y, EMouseButton button)
    {
        if (m_Widget && w == m_Widget)
        {
            return m_Widget.OnMouseUp(x, y, button);
        }
        
        return false;
    }
    
    override bool OnMouseEnter(Widget w, int x, int y)
    {
        if (m_Widget && w == m_Widget)
        {
            return m_Widget.OnMouseEnter(x, y);
        }
        
        return false;
    }
    
    override bool OnMouseLeave(Widget w, int x, int y)
    {
        if (m_Widget && w == m_Widget)
        {
            return m_Widget.OnMouseLeave(x, y);
        }
        
        return false;
    }
    
    override bool OnKeyDown(Widget w, int key)
    {
        if (m_Widget && w == m_Widget)
        {
            return m_Widget.OnKeyDown(key);
        }
        
        return false;
    }
    
    override bool OnKeyUp(Widget w, int key)
    {
        if (m_Widget && w == m_Widget)
        {
            return m_Widget.OnKeyUp(key);
        }
        
        return false;
    }
    
    override bool OnFocus(Widget w, int x, int y)
    {
        if (m_Widget && w == m_Widget)
        {
            return m_Widget.OnFocus();
        }
        
        return false;
    }
    
    override bool OnFocusLost(Widget w, int x, int y)
    {
        if (m_Widget && w == m_Widget)
        {
            return m_Widget.OnFocusLost();
        }
        
        return false;
    }
}