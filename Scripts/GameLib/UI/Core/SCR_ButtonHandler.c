// SCR_ButtonHandler.c implementation for ARMA Reforger UI system

class SCR_ButtonHandler
{
    // Private member variables
    protected Widget m_Widget;
    
    // Constructor
    void SCR_ButtonHandler()
    {
    }
    
    // Called when mouse button is pressed over the widget
    bool OnMouseDown(Widget w, int x, int y, EMouseButton button)
    {
        return false;
    }
    
    // Called when mouse button is released over the widget
    bool OnMouseUp(Widget w, int x, int y, EMouseButton button)
    {
        return false;
    }
    
    // Called when a widget is clicked (press and release over the same widget)
    bool OnClick(Widget w, int x, int y, EMouseButton button)
    {
        return false;
    }
    
    // Called when the mouse cursor enters a widget
    bool OnMouseEnter(Widget w, int x, int y)
    {
        return false;
    }
    
    // Called when the mouse cursor leaves a widget
    bool OnMouseLeave(Widget w, int x, int y)
    {
        return false;
    }
    
    // Called when a key is pressed while the widget has focus
    bool OnKeyDown(Widget w, int key)
    {
        return false;
    }
    
    // Called when a key is released while the widget has focus
    bool OnKeyUp(Widget w, int key)
    {
        return false;
    }
    
    // Called when a widget gets focus
    bool OnFocus(Widget w, int x, int y)
    {
        return false;
    }
    
    // Called when a widget loses focus
    bool OnFocusLost(Widget w, int x, int y)
    {
        return false;
    }
}