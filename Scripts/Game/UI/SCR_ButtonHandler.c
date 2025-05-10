// SCR_ButtonHandler for ARMA Reforger UI system

enum EMouseButton
{
    LEFT,
    RIGHT,
    MIDDLE
}

class SCR_ButtonHandler
{
    // Constructor
    void SCR_ButtonHandler() {}
    
    // OnMouseDown event handler for buttons
    bool OnMouseDown(Widget w, int x, int y, EMouseButton button)
    {
        return false;
    }
    
    // OnMouseUp event handler for buttons
    bool OnMouseUp(Widget w, int x, int y, EMouseButton button)
    {
        return false;
    }
    
    // OnClick event handler for buttons
    bool OnClick(Widget w, int x, int y, EMouseButton button)
    {
        return false;
    }
    
    // OnFocus event handler for buttons
    bool OnFocus(Widget w, int x, int y)
    {
        return false;
    }
    
    // OnFocusLost event handler for buttons
    bool OnFocusLost(Widget w, int x, int y)
    {
        return false;
    }
}