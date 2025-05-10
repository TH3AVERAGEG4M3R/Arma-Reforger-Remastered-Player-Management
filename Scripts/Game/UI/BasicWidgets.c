// BasicWidgets.c - Basic UI widget classes for ARMA Reforger
// This file defines common UI widget types used in the game

#include "Widget.c"

/**
 * @brief Button widget class
 */
class ButtonWidget : Widget
{
    // Button properties
    protected string m_Text;
    protected bool m_IsPressed;
    protected bool m_IsToggle;
    protected bool m_IsToggled;
    
    // Constructor
    void ButtonWidget(string name = "", Widget parent = null)
    {
        // Call base constructor
        super.Widget(name, parent);
        
        // Initialize
        m_Text = "";
        m_IsPressed = false;
        m_IsToggle = false;
        m_IsToggled = false;
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
     * @param text The button text
     */
    void SetText(string text)
    {
        m_Text = text;
    }
    
    /**
     * @brief Check if the button is pressed
     * @return True if pressed, false otherwise
     */
    bool IsPressed()
    {
        return m_IsPressed;
    }
    
    /**
     * @brief Set the pressed state
     * @param isPressed The pressed state
     */
    void SetPressed(bool isPressed)
    {
        m_IsPressed = isPressed;
    }
    
    /**
     * @brief Check if the button is a toggle button
     * @return True if toggle, false otherwise
     */
    bool IsToggle()
    {
        return m_IsToggle;
    }
    
    /**
     * @brief Set whether the button is a toggle button
     * @param isToggle True for toggle, false for normal button
     */
    void SetToggle(bool isToggle)
    {
        m_IsToggle = isToggle;
    }
    
    /**
     * @brief Check if the toggle button is toggled
     * @return True if toggled, false otherwise
     */
    bool IsToggled()
    {
        return m_IsToggled;
    }
    
    /**
     * @brief Set the toggled state
     * @param isToggled The toggled state
     */
    void SetToggled(bool isToggled)
    {
        m_IsToggled = isToggled;
    }
    
    /**
     * @brief Toggle the button state
     * @return The new toggled state
     */
    bool Toggle()
    {
        m_IsToggled = !m_IsToggled;
        return m_IsToggled;
    }
    
    // Override event handling
    override bool OnMouseDown(int x, int y, int button)
    {
        if (button == 0) // Left mouse button
        {
            m_IsPressed = true;
            return true;
        }
        
        return false;
    }
    
    override bool OnMouseUp(int x, int y, int button)
    {
        if (button == 0 && m_IsPressed) // Left mouse button
        {
            m_IsPressed = false;
            
            if (m_IsToggle)
            {
                Toggle();
            }
            
            return true;
        }
        
        return false;
    }
}

/**
 * @brief Text widget class
 */
class TextWidget : Widget
{
    // Text properties
    protected string m_Text;
    protected int m_TextColor;
    protected int m_FontSize;
    protected string m_FontName;
    
    // Constructor
    void TextWidget(string name = "", Widget parent = null)
    {
        // Call base constructor
        super.Widget(name, parent);
        
        // Initialize
        m_Text = "";
        m_TextColor = 0xFFFFFFFF; // White
        m_FontSize = 12;
        m_FontName = "Arial";
    }
    
    /**
     * @brief Get the text
     * @return The text
     */
    string GetText()
    {
        return m_Text;
    }
    
    /**
     * @brief Set the text
     * @param text The text
     */
    void SetText(string text)
    {
        m_Text = text;
    }
    
    /**
     * @brief Get the text color
     * @return The text color
     */
    int GetTextColor()
    {
        return m_TextColor;
    }
    
    /**
     * @brief Set the text color
     * @param color The text color
     */
    void SetTextColor(int color)
    {
        m_TextColor = color;
    }
    
    /**
     * @brief Get the font size
     * @return The font size
     */
    int GetFontSize()
    {
        return m_FontSize;
    }
    
    /**
     * @brief Set the font size
     * @param size The font size
     */
    void SetFontSize(int size)
    {
        m_FontSize = size;
    }
    
    /**
     * @brief Get the font name
     * @return The font name
     */
    string GetFontName()
    {
        return m_FontName;
    }
    
    /**
     * @brief Set the font name
     * @param name The font name
     */
    void SetFontName(string name)
    {
        m_FontName = name;
    }
}

/**
 * @brief Image widget class
 */
class ImageWidget : Widget
{
    // Image properties
    protected string m_ImagePath;
    protected int m_ImageColor;
    
    // Constructor
    void ImageWidget(string name = "", Widget parent = null)
    {
        // Call base constructor
        super.Widget(name, parent);
        
        // Initialize
        m_ImagePath = "";
        m_ImageColor = 0xFFFFFFFF; // White
    }
    
    /**
     * @brief Get the image path
     * @return The image path
     */
    string GetImagePath()
    {
        return m_ImagePath;
    }
    
    /**
     * @brief Set the image path
     * @param path The image path
     */
    void SetImagePath(string path)
    {
        m_ImagePath = path;
    }
    
    /**
     * @brief Get the image color
     * @return The image color
     */
    int GetImageColor()
    {
        return m_ImageColor;
    }
    
    /**
     * @brief Set the image color
     * @param color The image color
     */
    void SetImageColor(int color)
    {
        m_ImageColor = color;
    }
}

/**
 * @brief Edit box widget class
 */
class EditBoxWidget : Widget
{
    // Edit box properties
    protected string m_Text;
    protected string m_Placeholder;
    protected int m_TextColor;
    protected int m_PlaceholderColor;
    protected int m_FontSize;
    protected string m_FontName;
    protected bool m_IsMultiline;
    protected bool m_IsReadOnly;
    protected bool m_IsPassword;
    
    // Constructor
    void EditBoxWidget(string name = "", Widget parent = null)
    {
        // Call base constructor
        super.Widget(name, parent);
        
        // Initialize
        m_Text = "";
        m_Placeholder = "";
        m_TextColor = 0xFFFFFFFF; // White
        m_PlaceholderColor = 0xAAAAAA; // Gray
        m_FontSize = 12;
        m_FontName = "Arial";
        m_IsMultiline = false;
        m_IsReadOnly = false;
        m_IsPassword = false;
    }
    
    /**
     * @brief Get the text
     * @return The text
     */
    string GetText()
    {
        return m_Text;
    }
    
    /**
     * @brief Set the text
     * @param text The text
     */
    void SetText(string text)
    {
        m_Text = text;
    }
    
    /**
     * @brief Get the placeholder text
     * @return The placeholder text
     */
    string GetPlaceholder()
    {
        return m_Placeholder;
    }
    
    /**
     * @brief Set the placeholder text
     * @param placeholder The placeholder text
     */
    void SetPlaceholder(string placeholder)
    {
        m_Placeholder = placeholder;
    }
    
    /**
     * @brief Get the text color
     * @return The text color
     */
    int GetTextColor()
    {
        return m_TextColor;
    }
    
    /**
     * @brief Set the text color
     * @param color The text color
     */
    void SetTextColor(int color)
    {
        m_TextColor = color;
    }
    
    /**
     * @brief Get the placeholder color
     * @return The placeholder color
     */
    int GetPlaceholderColor()
    {
        return m_PlaceholderColor;
    }
    
    /**
     * @brief Set the placeholder color
     * @param color The placeholder color
     */
    void SetPlaceholderColor(int color)
    {
        m_PlaceholderColor = color;
    }
    
    /**
     * @brief Get the font size
     * @return The font size
     */
    int GetFontSize()
    {
        return m_FontSize;
    }
    
    /**
     * @brief Set the font size
     * @param size The font size
     */
    void SetFontSize(int size)
    {
        m_FontSize = size;
    }
    
    /**
     * @brief Get the font name
     * @return The font name
     */
    string GetFontName()
    {
        return m_FontName;
    }
    
    /**
     * @brief Set the font name
     * @param name The font name
     */
    void SetFontName(string name)
    {
        m_FontName = name;
    }
    
    /**
     * @brief Check if the edit box is multiline
     * @return True if multiline, false otherwise
     */
    bool IsMultiline()
    {
        return m_IsMultiline;
    }
    
    /**
     * @brief Set whether the edit box is multiline
     * @param isMultiline True for multiline, false for single line
     */
    void SetMultiline(bool isMultiline)
    {
        m_IsMultiline = isMultiline;
    }
    
    /**
     * @brief Check if the edit box is read-only
     * @return True if read-only, false otherwise
     */
    bool IsReadOnly()
    {
        return m_IsReadOnly;
    }
    
    /**
     * @brief Set whether the edit box is read-only
     * @param isReadOnly True for read-only, false for editable
     */
    void SetReadOnly(bool isReadOnly)
    {
        m_IsReadOnly = isReadOnly;
    }
    
    /**
     * @brief Check if the edit box is password
     * @return True if password, false otherwise
     */
    bool IsPassword()
    {
        return m_IsPassword;
    }
    
    /**
     * @brief Set whether the edit box is password
     * @param isPassword True for password, false for normal text
     */
    void SetPassword(bool isPassword)
    {
        m_IsPassword = isPassword;
    }
}