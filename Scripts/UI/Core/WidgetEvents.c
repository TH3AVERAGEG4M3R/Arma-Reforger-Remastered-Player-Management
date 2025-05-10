enum EMouseButton
{
    LEFT = 0,
    RIGHT = 1,
    MIDDLE = 2
};

class WidgetEventHandler
{
    // Widget event handlers
    bool OnMouseEnter(Widget w, int x, int y)
    {
        return false;
    }
    
    bool OnMouseLeave(Widget w, Widget enterW)
    {
        return false;
    }
    
    bool OnMouseDown(Widget w, int x, int y, EMouseButton button)
    {
        return false;
    }
    
    bool OnMouseUp(Widget w, int x, int y, EMouseButton button)
    {
        return false;
    }
}