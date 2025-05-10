// Basic widget classes for ARMA Reforger UI

#include "Widget.c"
#include "Color.c"

class ButtonWidget : Widget
{
    void ButtonWidget() {}
    
    void SetEnabled(bool enabled) {}
    
    void SetText(string text) {}
    
    void SetColor(Color color) {}
    
    void AddHandler(SCR_ButtonHandler handler) {}
    
    static ButtonWidget Cast(Widget w)
    {
        return null;
    }
}

class TextWidget : Widget
{
    void TextWidget() {}
    
    void SetText(string text) {}
    
    string GetText() { return ""; }
    
    void SetColor(Color color) {}
    
    static TextWidget Cast(Widget w)
    {
        return null;
    }
}

class ImageWidget : Widget
{
    void ImageWidget() {}
    
    void SetColor(Color color) {}
    
    void SetOpacity(float opacity) {}
    
    void SetImage(string path) {}
    
    static ImageWidget Cast(Widget w)
    {
        return null;
    }
}

class EditBoxWidget : Widget
{
    void EditBoxWidget() {}
    
    void SetText(string text) {}
    
    string GetText() { return ""; }
    
    void SetHandler(Class handler) {}
    
    void SetEnterHandler(Class instance, string methodName) {}
    
    void SetFocus(bool focus) {}
    
    static EditBoxWidget Cast(Widget w)
    {
        return null;
    }
}

class TextListboxWidget : Widget
{
    void TextListboxWidget() {}
    
    int AddItem(string text) { return 0; }
    
    void RemoveItem(int index) {}
    
    void ClearItems() {}
    
    static TextListboxWidget Cast(Widget w)
    {
        return null;
    }
}

class VerticalLayoutWidget : Widget
{
    void VerticalLayoutWidget() {}
    
    void AddChild(Widget child) {}
    
    void RemoveChild(Widget child) {}
    
    void ClearItems() {}
    
    static VerticalLayoutWidget Cast(Widget w)
    {
        return null;
    }
}