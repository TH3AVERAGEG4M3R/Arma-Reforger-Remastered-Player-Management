/**
 * @brief Classes and enums for widget events in ARMA Reforger
 */

/**
 * @brief Type definitions for widget event handlers
 */
typedef func bool WidgetEventHandler(Widget w, int x, int y, int button);

/**
 * @brief Widget event handler class
 */
class WidgetEventHandler
{
    /**
     * @brief Handle widget events
     * @param w The widget
     * @param x X coordinate
     * @param y Y coordinate
     * @param button Button code
     * @return True if handled, false otherwise
     */
    bool OnWidgetEvent(Widget w, int x, int y, int button)
    {
        return false;
    }
}