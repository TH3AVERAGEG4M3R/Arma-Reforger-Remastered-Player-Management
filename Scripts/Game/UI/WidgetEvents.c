// WidgetEvents class for ARMA Reforger UI system

class WidgetEventHandler
{
    // Constructor
    void WidgetEventHandler() {}
    
    // Register a mouse event for a widget
    void AddMouseEventHandler(Widget w, int eventType, Class instance, string methodName) {}
    
    // Remove a mouse event for a widget
    void RemoveMouseEventHandler(Widget w, int eventType, Class instance, string methodName) {}
    
    // Add a keyboard event handler for a widget
    void AddKeyEventHandler(Widget w, int eventType, Class instance, string methodName) {}
    
    // Remove a keyboard event handler for a widget
    void RemoveKeyEventHandler(Widget w, int eventType, Class instance, string methodName) {}
}