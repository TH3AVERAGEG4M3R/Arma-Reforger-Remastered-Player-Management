/**
 * @brief Action Context for handling input context in ARMA Reforger
 */
#include "InputDevice.c"
class ActionContext
{
    // Input device that triggered this action
    protected InputDevice m_Device;
    
    // Input action name or ID
    protected string m_ActionName;
    
    // Additional action parameters if needed
    protected ref map<string, float> m_ActionParameters;
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Constructor
     */
    void ActionContext()
    {
        m_ActionParameters = new map<string, float>();
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the action name
     * @param actionName The name of the action
     */
    void SetActionName(string actionName)
    {
        m_ActionName = actionName;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the input device
     * @param device The input device
     */
    void SetDevice(InputDevice device)
    {
        m_Device = device;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set an action parameter value
     * @param name The parameter name
     * @param value The parameter value
     */
    void SetActionParam(string name, float value)
    {
        m_ActionParameters.Set(name, value);
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the action name
     * @return The action name
     */
    string GetActionName()
    {
        return m_ActionName;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the input device
     * @return The input device
     */
    InputDevice GetDevice()
    {
        return m_Device;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get an action parameter value
     * @param name The parameter name
     * @param defaultValue Default value if parameter not found
     * @return The parameter value or default value
     */
    float GetActionParam(string name, float defaultValue = 0.0)
    {
        if (m_ActionParameters.Contains(name))
            return m_ActionParameters.Get(name);
        
        return defaultValue;
    }
}