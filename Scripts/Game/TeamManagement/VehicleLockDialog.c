/**
 * @brief Dialog for controlling vehicle locking
 */
class VehicleLockDialog: ScriptedWidgetComponent
{
    // UI References
    protected TextWidget m_VehicleNameText;
    protected TextWidget m_LockStatusText;
    protected TextWidget m_TeamInfoText;
    protected TextWidget m_TeamMembersText;
    protected ButtonWidget m_LockButton;
    protected ButtonWidget m_UnlockButton;
    
    // Data
    protected IEntity m_Vehicle;
    protected IEntity m_Player;
    protected TeamPlayerComponent m_PlayerComponent;
    protected TeamVehicleComponent m_VehicleComponent;
    protected bool m_IsInTeam;
    protected int m_TeamID;
    
    /**
     * @brief Initialize the dialog
     * @param vehicle The vehicle to control locking for
     */
    void Init(IEntity vehicle)
    {
        m_Vehicle = vehicle;
        m_Player = GetGame().GetPlayerController().GetControlledEntity();
        
        // Get components
        m_PlayerComponent = TeamPlayerComponent.Cast(m_Player.FindComponent(TeamPlayerComponent));
        m_VehicleComponent = TeamVehicleComponent.Cast(m_Vehicle.FindComponent(TeamVehicleComponent));
        
        // Create vehicle component if it doesn't exist
        if (!m_VehicleComponent && m_PlayerComponent)
        {
            m_VehicleComponent = m_PlayerComponent.GetOrCreateVehicleComponent(m_Vehicle);
        }
        
        // Get team info
        m_IsInTeam = false;
        m_TeamID = 0;
        
        if (m_PlayerComponent)
        {
            m_TeamID = m_PlayerComponent.GetCurrentTeam();
            m_IsInTeam = (m_TeamID > 0);
        }
        
        // Get UI references
        m_VehicleNameText = TextWidget.Cast(GetRootWidget().FindAnyWidget("VehicleNameText"));
        m_LockStatusText = TextWidget.Cast(GetRootWidget().FindAnyWidget("LockStatusText"));
        m_TeamInfoText = TextWidget.Cast(GetRootWidget().FindAnyWidget("TeamInfoText"));
        m_TeamMembersText = TextWidget.Cast(GetRootWidget().FindAnyWidget("TeamMembersText"));
        m_LockButton = ButtonWidget.Cast(GetRootWidget().FindAnyWidget("LockButton"));
        m_UnlockButton = ButtonWidget.Cast(GetRootWidget().FindAnyWidget("UnlockButton"));
        
        // Set button handlers
        if (m_LockButton)
            m_LockButton.AddHandler(new VehicleLockButtonHandler(this));
        
        if (m_UnlockButton)
            m_UnlockButton.AddHandler(new VehicleUnlockButtonHandler(this));
        
        // Update UI
        UpdateUI();
    }
    
    /**
     * @brief Update all UI elements
     */
    void UpdateUI()
    {
        if (!m_Vehicle || !m_Player)
            return;
            
        // Update vehicle name
        if (m_VehicleNameText)
            m_VehicleNameText.SetText("Vehicle: " + m_Vehicle.GetName());
        
        // Update lock status
        bool isLocked = false;
        string lockOwner = "None";
        
        if (m_VehicleComponent)
        {
            isLocked = m_VehicleComponent.IsLocked();
            int ownerTeamID = m_VehicleComponent.GetOwnerTeamID();
            if (ownerTeamID > 0)
                lockOwner = "Team " + ownerTeamID;
        }
        
        if (m_LockStatusText)
        {
            if (isLocked)
                m_LockStatusText.SetText("Status: Locked by " + lockOwner);
            else
                m_LockStatusText.SetText("Status: Unlocked");
        }
        
        // Update team info
        if (m_TeamInfoText)
        {
            if (m_IsInTeam)
                m_TeamInfoText.SetText("Your Team: Team " + m_TeamID);
            else
                m_TeamInfoText.SetText("You are not in a team");
        }
        
        // Update team members
        if (m_TeamMembersText && m_PlayerComponent)
        {
            string membersText = "";
            array<ref TeamMember> members = m_PlayerComponent.GetTeamMembers();
            
            if (members && members.Count() > 0)
            {
                for (int i = 0; i < members.Count(); i++)
                {
                    if (i > 0)
                        membersText += ", ";
                        
                    membersText += members[i].GetPlayerName();
                    
                    if (members[i].IsLeader())
                        membersText += " (Leader)";
                }
            }
            else
            {
                membersText = "No team members";
            }
            
            m_TeamMembersText.SetText(membersText);
        }
        
        // Update button states
        if (m_LockButton)
        {
            // Disable lock button if already locked or not in a team
            m_LockButton.SetEnabled(!isLocked && m_IsInTeam);
        }
        
        if (m_UnlockButton)
        {
            // Only enable unlock if vehicle is locked and player is owner or in same team
            bool canUnlock = isLocked && m_VehicleComponent && m_VehicleComponent.CanAccessVehicle(m_Player);
            m_UnlockButton.SetEnabled(canUnlock);
        }
    }
    
    /**
     * @brief Lock the vehicle for team access
     */
    void LockVehicle()
    {
        if (!m_Vehicle || !m_Player || !m_PlayerComponent)
            return;
            
        bool success = m_PlayerComponent.LockVehicleForTeam(m_Vehicle);
        
        if (success)
            Print("Vehicle locked successfully for team " + m_TeamID);
        else
            Print("Failed to lock vehicle");
            
        UpdateUI();
    }
    
    /**
     * @brief Unlock the vehicle
     */
    void UnlockVehicle()
    {
        if (!m_Vehicle || !m_Player || !m_PlayerComponent)
            return;
            
        bool success = m_PlayerComponent.UnlockVehicle(m_Vehicle);
        
        if (success)
            Print("Vehicle unlocked successfully");
        else
            Print("Failed to unlock vehicle");
            
        UpdateUI();
    }
}

/**
 * @brief Handler for the lock button
 */
class VehicleLockButtonHandler: ScriptedWidgetEventHandler
{
    protected VehicleLockDialog m_Dialog;
    
    void VehicleLockButtonHandler(VehicleLockDialog dialog)
    {
        m_Dialog = dialog;
    }
    
    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (m_Dialog)
            m_Dialog.LockVehicle();
            
        return true;
    }
}

/**
 * @brief Handler for the unlock button
 */
class VehicleUnlockButtonHandler: ScriptedWidgetEventHandler
{
    protected VehicleLockDialog m_Dialog;
    
    void VehicleUnlockButtonHandler(VehicleLockDialog dialog)
    {
        m_Dialog = dialog;
    }
    
    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (m_Dialog)
            m_Dialog.UnlockVehicle();
            
        return true;
    }
}