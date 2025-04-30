/**
 * @brief UI class for team invitation popup in ARMA Reforger
 */
class SCR_TeamInvitationPopup : ScriptedWidgetComponent
{
    // Reference to UI elements
    protected Widget m_wRoot;
    protected TextWidget m_wInvitationText;
    protected ButtonWidget m_wAcceptButton;
    protected ButtonWidget m_wDeclineButton;
    
    // The invitation this popup is for
    protected ref TeamInvitation m_Invitation;
    
    // Whether the UI is initialized
    protected bool m_Initialized;
    
    // Player controller
    protected PlayerController m_PlayerController;
    
    /**
     * @brief Initialize the widget
     * @param w The root widget
     */
    override void HandlerAttached(Widget w)
    {
        super.HandlerAttached(w);
        m_wRoot = w;
        
        // Find UI elements
        m_wInvitationText = TextWidget.Cast(m_wRoot.FindAnyWidget("InvitationText"));
        m_wAcceptButton = ButtonWidget.Cast(m_wRoot.FindAnyWidget("AcceptButton"));
        m_wDeclineButton = ButtonWidget.Cast(m_wRoot.FindAnyWidget("DeclineButton"));
        
        // Add event handlers
        m_wAcceptButton.AddHandler(new SCR_TeamInvitationButtonHandler(this, "OnAcceptClicked"));
        m_wDeclineButton.AddHandler(new SCR_TeamInvitationButtonHandler(this, "OnDeclineClicked"));
        
        m_Initialized = true;
        
        // Update the UI with invitation details
        if (m_Invitation)
            UpdateUI();
    }
    
    /**
     * @brief Set the invitation this popup is for
     * @param invitation The invitation details
     */
    void SetInvitation(TeamInvitation invitation)
    {
        m_Invitation = invitation;
        
        if (m_Initialized)
            UpdateUI();
    }
    
    /**
     * @brief Set the player controller
     * @param playerController The player controller
     */
    void SetPlayerController(PlayerController playerController)
    {
        m_PlayerController = playerController;
    }
    
    /**
     * @brief Update the UI with invitation details
     */
    protected void UpdateUI()
    {
        if (!m_Invitation || !m_wInvitationText)
            return;
        
        string senderName = m_Invitation.GetSenderName();
        m_wInvitationText.SetText(senderName + " has invited you to join their team.");
    }
    
    /**
     * @brief Handler for the Accept button click
     */
    void OnAcceptClicked()
    {
        if (!m_Invitation)
            return;
        
        // Accept invitation
        TeamManager teamManager = TeamManager.GetInstance();
        IEntity playerEntity = m_PlayerController.GetControlledEntity();
        bool success = teamManager.AcceptInvitation(m_Invitation.GetInvitationID(), playerEntity);
        
        // Close popup
        ClosePopup();
    }
    
    /**
     * @brief Handler for the Decline button click
     */
    void OnDeclineClicked()
    {
        if (!m_Invitation)
            return;
        
        // Decline invitation
        TeamManager teamManager = TeamManager.GetInstance();
        IEntity playerEntity = m_PlayerController.GetControlledEntity();
        teamManager.DeclineInvitation(m_Invitation.GetInvitationID(), playerEntity);
        
        // Close popup
        ClosePopup();
    }
    
    /**
     * @brief Close the popup
     */
    protected void ClosePopup()
    {
        if (m_wRoot)
            m_wRoot.SetVisible(false);
    }
    
    /**
     * @brief Create and show an invitation popup
     * @param playerController The player controller
     * @param invitation The invitation details
     */
    static void CreateInvitationPopup(PlayerController playerController, TeamInvitation invitation)
    {
        if (!playerController || !invitation)
            return;
        
        // Create and show popup
        Widget root = GetGame().GetWorkspace().CreateWidgets("UI/layouts/TeamManagement/TeamInvitationPopup.layout");
        if (root)
        {
            SCR_TeamInvitationPopup popup = new SCR_TeamInvitationPopup();
            popup.SetPlayerController(playerController);
            popup.SetInvitation(invitation);
            root.AddHandler(popup);
            root.SetVisible(true);
        }
    }
}

/**
 * @brief Button handler for team invitation popup
 */
class SCR_TeamInvitationButtonHandler : ScriptedWidgetEventHandler
{
    protected SCR_TeamInvitationPopup m_Popup;
    protected string m_Callback;
    
    /**
     * @brief Constructor
     * @param popup The popup this handler is for
     * @param callback The callback method to call
     */
    void SCR_TeamInvitationButtonHandler(SCR_TeamInvitationPopup popup, string callback)
    {
        m_Popup = popup;
        m_Callback = callback;
    }
    
    /**
     * @brief Handle button click
     * @param w The button widget
     * @param x Cursor X position
     * @param y Cursor Y position
     */
    override bool OnMouseDown(Widget w, int x, int y, int button)
    {
        if (button == MouseButton.LEFT)
        {
            if (m_Popup)
            {
                m_Popup.Invoke(m_Callback);
                return true;
            }
        }
        
        return false;
    }
}
