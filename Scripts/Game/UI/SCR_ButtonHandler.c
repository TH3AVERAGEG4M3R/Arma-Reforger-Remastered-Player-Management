// SCR_ButtonHandler.c implementation for ARMA Reforger UI system
#include "Widget.c"

// Mouse button enum already defined in WidgetEvents.c
// Using the same definition here for standalone usage
enum EMouseButton
{
    LEFT = 0,
    RIGHT = 1,
    MIDDLE = 2
};

class SCR_ButtonHandler
{
    // Private member variables
    protected Widget m_Widget;
    
    // Constructor
    void SCR_ButtonHandler()
    {
    }
    
    // Called when mouse button is pressed over the widget
    // This is overridden by derived classes
    virtual bool OnMouseDown(Widget w, int x, int y, EMouseButton button)
    {
        return false;
    }
    
    // Called when mouse button is released over the widget
    virtual bool OnMouseUp(Widget w, int x, int y, EMouseButton button)
    {
        return false;
    }
    
    // Called when a widget is clicked (press and release over the same widget)
    virtual bool OnClick(Widget w, int x, int y, EMouseButton button)
    {
        return false;
    }
    
    // Called when the mouse cursor enters a widget
    virtual bool OnMouseEnter(Widget w, int x, int y)
    {
        return false;
    }
    
    // Called when the mouse cursor leaves a widget
    virtual bool OnMouseLeave(Widget w, int x, int y)
    {
        return false;
    }
    
    // Called when a key is pressed while the widget has focus
    virtual bool OnKeyDown(Widget w, int key)
    {
        return false;
    }
    
    // Called when a key is released while the widget has focus
    virtual bool OnKeyUp(Widget w, int key)
    {
        return false;
    }
    
    // Called when a widget gets focus
    virtual bool OnFocus(Widget w, int x, int y)
    {
        return false;
    }
    
    // Called when a widget loses focus
    virtual bool OnFocusLost(Widget w, int x, int y)
    {
        return false;
    }
}