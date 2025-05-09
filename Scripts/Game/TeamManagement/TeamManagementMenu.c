/**
 * @brief UI class for the team management menu in ARMA Reforger
 */
class SCR_TeamManagementMenu : ScriptedWidgetComponent
{
    // Reference to UI elements
    protected Widget m_wRoot;
    protected TextWidget m_wTitle;
    protected Widget m_wNoTeamFrame;
    protected Widget m_wTeamFrame;
    protected TextWidget m_wTeamTitle;
    protected VerticalLayoutWidget m_wMembersVerticalLayout;
    protected ButtonWidget m_wCreateTeamButton;
    protected ButtonWidget m_wJoinTeamButton;
    protected ButtonWidget m_wInvitePlayerButton;
    protected ButtonWidget m_wVehicleLockButton;
    protected ButtonWidget m_wLeaveTeamButton;
    protected ButtonWidget m_wCloseButton;
    
    // Player controller
    protected PlayerController m_PlayerController;
    
    // Whether the UI is initialized
    protected bool m_Initialized;
    
    // The current player's entity
    protected IEntity m_PlayerEntity;
    
    // The current player's ID
    protected string m_PlayerID;
    
    // The current player's team ID
    protected int m_TeamID;
    
    // Whether the player is a team leader
    protected bool m_IsLeader;
    
    // Timer for refreshing the UI
    protected float m_RefreshTimer;
    
    // Time between UI refreshes (seconds)
    protected const float REFRESH_INTERVAL = 1.0;
    
    /**
     * @brief Initialize the widget
     * @param w The root widget
     */
    override void HandlerAttached(Widget w)
    {
        super.HandlerAttached(w);
        m_wRoot = w;
        
        // Get player controller
        m_PlayerController = GetGame().GetPlayerController();
        if (!m_PlayerController)
            return;
        
        // Get player entity
        m_PlayerEntity = m_PlayerController.GetControlledEntity();
        if (!m_PlayerEntity)
            return;
        
        // Get player ID
        m_PlayerID = GetPlayerIdentity();
        
        // Find UI elements
        m_wTitle = TextWidget.Cast(m_wRoot.FindAnyWidget("Title"));
        m_wNoTeamFrame = m_wRoot.FindAnyWidget("NoTeamFrame");
        m_wTeamFrame = m_wRoot.FindAnyWidget("TeamFrame");
        m_wTeamTitle = TextWidget.Cast(m_wRoot.FindAnyWidget("TeamTitle"));
        m_wMembersVerticalLayout = VerticalLayoutWidget.Cast(m_wRoot.FindAnyWidget("MembersVerticalLayout"));
        m_wCreateTeamButton = ButtonWidget.Cast(m_wRoot.FindAnyWidget("CreateTeamButton"));
        m_wJoinTeamButton = ButtonWidget.Cast(m_wRoot.FindAnyWidget("JoinTeamButton"));
        m_wInvitePlayerButton = ButtonWidget.Cast(m_wRoot.FindAnyWidget("InvitePlayerButton"));
        m_wVehicleLockButton = ButtonWidget.Cast(m_wRoot.FindAnyWidget("VehicleLockButton"));
        m_wLeaveTeamButton = ButtonWidget.Cast(m_wRoot.FindAnyWidget("LeaveTeamButton"));
        m_wCloseButton = ButtonWidget.Cast(m_wRoot.FindAnyWidget("CloseButton"));
        
        // Add event handlers
        m_wCreateTeamButton.AddHandler(new SCR_TeamManagementButtonHandler(this, "OnCreateTeamClicked"));
        m_wJoinTeamButton.AddHandler(new SCR_TeamManagementButtonHandler(this, "OnJoinTeamClicked"));
        m_wInvitePlayerButton.AddHandler(new SCR_TeamManagementButtonHandler(this, "OnInvitePlayerClicked"));
        m_wVehicleLockButton.AddHandler(new SCR_TeamManagementButtonHandler(this, "OnVehicleLockClicked"));
        m_wLeaveTeamButton.AddHandler(new SCR_TeamManagementButtonHandler(this, "OnLeaveTeamClicked"));
        m_wCloseButton.AddHandler(new SCR_TeamManagementButtonHandler(this, "OnCloseClicked"));
        
        m_Initialized = true;
        
        // Initial refresh
        RefreshUI();
    }
    
    /**
     * @brief Frame update
     * @param timeslice Time since last frame
     */
    void Update(float timeslice)
    {
        super.Update(timeslice);
        
        if (!m_Initialized)
            return;
        
        // Refresh UI at intervals
        m_RefreshTimer += timeslice;
        if (m_RefreshTimer >= REFRESH_INTERVAL)
        {
            m_RefreshTimer = 0;
            RefreshUI();
        }
    }
    
    /**
     * @brief Refresh the UI based on current team status
     */
    void RefreshUI()
    {
        // Get player's current team
        TeamManager teamManager = TeamManager.GetInstance();
        m_TeamID = teamManager.GetPlayerTeam(m_PlayerID);
        
        // Update visibility of frames
        bool inTeam = m_TeamID > 0;
        m_wNoTeamFrame.SetVisible(!inTeam);
        m_wTeamFrame.SetVisible(inTeam);
        
        if (inTeam)
        {
            // Update team info
            m_wTeamTitle.SetText("YOUR TEAM (ID: " + m_TeamID + ")");
            
            // Check if player is leader
            m_IsLeader = teamManager.IsTeamLeader(m_PlayerID, m_TeamID);
            
            // Update invite button visibility (only leaders can invite)
            m_wInvitePlayerButton.SetVisible(m_IsLeader);
            
            // Vehicle lock button is visible to all team members
            m_wVehicleLockButton.SetVisible(true);
            
            // Clear and rebuild members list
            m_wMembersVerticalLayout.ClearItems();
            
            array<ref TeamMember> teamMembers = teamManager.GetTeamMembers(m_TeamID);
            if (teamMembers)
            {
                foreach (ref TeamMember member : teamMembers)
                {
                    Widget memberWidget = CreateMemberWidget(member);
                    if (memberWidget)
                        m_wMembersVerticalLayout.AddChild(memberWidget);
                }
            }
        }
    }
    
    /**
     * @brief Create a widget for displaying a team member
     * @param member The team member data
     * @return The created widget
     */
    protected Widget CreateMemberWidget(TeamMember member)
    {
        // Create widget from layout
        Widget widget = GetGame().GetWorkspace().CreateWidgets("UI/layouts/TeamManagement/TeamMemberItem.layout");
        if (!widget)
            return null;
        
        // Get elements
        TextWidget nameText = TextWidget.Cast(widget.FindAnyWidget("MemberName"));
        ImageWidget leaderIcon = ImageWidget.Cast(widget.FindAnyWidget("LeaderIcon"));
        
        // Set values
        if (nameText)
            nameText.SetText(member.GetPlayerName());
        
        if (leaderIcon)
            leaderIcon.SetVisible(member.IsLeader());
        
        // Highlight if this is the current player
        if (member.GetPlayerID() == m_PlayerID)
        {
            ImageWidget background = ImageWidget.Cast(widget.FindAnyWidget("Background"));
            if (background)
                background.SetColor(Color.FromRGBA(100, 100, 200, 100));
        }
        
        return widget;
    }
    
    /**
     * @brief Get the player's identity string
     * @return The player's identity string
     */
    protected string GetPlayerIdentity()
    {
        if (!m_PlayerController)
            return "";
        
        return m_PlayerController.GetPlayerId().ToString();
    }
    
    /**
     * @brief Handler for the Create Team button click
     */
    void OnCreateTeamClicked()
    {
        TeamManager teamManager = TeamManager.GetInstance();
        int teamID = teamManager.CreateTeam(m_PlayerEntity);
        
        if (teamID > 0)
        {
            // Team created successfully
            RefreshUI();
        }
        else
        {
            // Show error message
            SCR_NotificationSystem.SendNotification("Cannot create team. You may already be in a team.");
        }
    }
    
    /**
     * @brief Handler for the Join Team button click
     */
    void OnJoinTeamClicked()
    {
        // Open dialog to enter team ID
        SCR_InputDialogUI.OpenDialog("Enter Team ID:", "JOIN", this, "OnTeamIDEntered");
    }
    
    /**
     * @brief Callback when team ID is entered
     * @param teamIDString The entered team ID as string
     */
    void OnTeamIDEntered(string teamIDString)
    {
        // Parse team ID
        int teamID;
        if (!teamIDString.ToInt(teamID) || teamID <= 0)
        {
            // Invalid team ID
            SCR_NotificationSystem.SendNotification("Invalid team ID.");
            return;
        }
        
        // Try to join team
        TeamManager teamManager = TeamManager.GetInstance();
        bool success = teamManager.JoinTeam(teamID, m_PlayerEntity);
        
        if (success)
        {
            // Joined team successfully
            RefreshUI();
        }
        else
        {
            // Show error message
            SCR_NotificationSystem.SendNotification("Cannot join team. The team may not exist or is full.");
        }
    }
    
    /**
     * @brief Handler for the Invite Player button click
     */
    void OnInvitePlayerClicked()
    {
        // Open player selection dialog
        array<IEntity> players = new array<IEntity>();
        GetGame().GetWorld().GetPlayerManager().GetPlayers(players);
        
        array<string> playerNames = new array<string>();
        array<string> playerIDs = new array<string>();
        
        // Filter out players already in the team
        TeamManager teamManager = TeamManager.GetInstance();
        foreach (IEntity player : players)
        {
            string playerID = GetPlayerIDFromEntity(player);
            string playerName = GetPlayerNameFromEntity(player);
            
            // Skip current player
            if (playerID == m_PlayerID)
                continue;
            
            // Skip players already in a team
            int playerTeamID = teamManager.GetPlayerTeam(playerID);
            if (playerTeamID > 0)
                continue;
            
            playerNames.Insert(playerName);
            playerIDs.Insert(playerID);
        }
        
        // Show player selection dialog
        SCR_SelectionDialogUI.OpenDialog("Select Player to Invite:", playerNames, this, "OnPlayerSelected", playerIDs);
    }
    
    /**
     * @brief Callback when a player is selected for invitation
     * @param index The index of the selected player
     * @param data The player ID
     */
    void OnPlayerSelected(int index, string playerID)
    {
        // Send invitation
        TeamManager teamManager = TeamManager.GetInstance();
        bool success = teamManager.SendInvitation(m_PlayerEntity, playerID);
        
        if (!success)
        {
            // Show error message
            SCR_NotificationSystem.SendNotification("Could not send invitation.");
        }
    }
    
    /**
     * @brief Handler for the Leave Team button click
     */
    void OnLeaveTeamClicked()
    {
        // Confirm leaving team
        SCR_ConfirmationDialogUI.OpenDialog("Are you sure you want to leave the team?", "LEAVE", "CANCEL", this, "OnLeaveTeamConfirmed");
    }
    
    /**
     * @brief Callback when leaving team is confirmed
     */
    void OnLeaveTeamConfirmed()
    {
        // Leave team
        TeamManager teamManager = TeamManager.GetInstance();
        bool success = teamManager.LeaveTeam(m_PlayerEntity);
        
        if (success)
        {
            // Left team successfully
            RefreshUI();
        }
        else
        {
            // Show error message
            SCR_NotificationSystem.SendNotification("Cannot leave team.");
        }
    }
    
    /**
     * @brief Handler for the Vehicle Lock button click
     */
    void OnVehicleLockClicked()
    {
        // Only allow if player is in a team
        if (m_TeamID <= 0)
        {
            SCR_NotificationSystem.SendNotification("You must be in a team to use vehicle locking.");
            return;
        }
        
        // Check if player is looking at a vehicle
        IEntity nearestVehicle = FindNearestVehicle();
        if (!nearestVehicle)
        {
            SCR_NotificationSystem.SendNotification("No vehicle detected nearby.");
            return;
        }
        
        // Create and show vehicle lock dialog
        OpenVehicleLockDialog(nearestVehicle);
    }
    
    /**
     * @brief Find the nearest vehicle to the player
     * @return The nearest vehicle entity, or null if none found
     */
    protected IEntity FindNearestVehicle()
    {
        if (!m_PlayerEntity)
            return null;
            
        // For the prototype, we'll check for a nearby vehicle in a simple manner
        // In a real implementation, this would use raycasting or other detection methods
        
        // Get all vehicles in the world
        array<IEntity> vehicles = new array<IEntity>();
        GetGame().GetWorld().QueryEntitiesByID(Vehicle, vehicles);
        
        // Find closest vehicle
        IEntity closestVehicle = null;
        float closestDistance = 10.0; // Maximum distance (meters)
        vector playerPos = m_PlayerEntity.GetOrigin();
        
        foreach (IEntity vehicle : vehicles)
        {
            vector vehiclePos = vehicle.GetOrigin();
            float distance = vector.Distance(playerPos, vehiclePos);
            
            if (distance < closestDistance)
            {
                closestDistance = distance;
                closestVehicle = vehicle;
            }
        }
        
        return closestVehicle;
    }
    
    /**
     * @brief Open the vehicle lock dialog
     * @param vehicle The vehicle to control
     */
    protected void OpenVehicleLockDialog(IEntity vehicle)
    {
        // Create and show dialog
        Widget root = GetGame().GetWorkspace().CreateWidgets("UI/layouts/TeamManagement/VehicleLockDialog.layout");
        if (root)
        {
            VehicleLockDialog dialog = new VehicleLockDialog();
            root.AddHandler(dialog);
            dialog.Init(vehicle);
            root.SetVisible(true);
        }
    }

    /**
     * @brief Handler for the Close button click
     */
    void OnCloseClicked()
    {
        // Close menu
        if (m_wRoot)
            m_wRoot.SetVisible(false);
    }
    
    /**
     * @brief Get player ID from entity
     * @param player The player entity
     * @return The player's ID
     */
    protected string GetPlayerIDFromEntity(IEntity player)
    {
        if (!player)
            return "";
        
        PlayerController pc = PlayerController.Cast(player.GetController());
        if (!pc)
            return "";
        
        return pc.GetPlayerId().ToString();
    }
    
    /**
     * @brief Get player name from entity
     * @param player The player entity
     * @return The player's name
     */
    protected string GetPlayerNameFromEntity(IEntity player)
    {
        if (!player)
            return "Unknown";
        
        PlayerController pc = PlayerController.Cast(player.GetController());
        if (!pc)
            return "Unknown";
        
        return pc.GetPlayerName();
    }
    
    /**
     * @brief Create and show the team management menu
     * @param playerController The player controller
     */
    static void CreateMenu(PlayerController playerController)
    {
        if (!playerController)
            return;
        
        // Create and show menu
        Widget root = GetGame().GetWorkspace().CreateWidgets("UI/layouts/TeamManagement/TeamManagementMenu.layout");
        if (root)
        {
            SCR_TeamManagementMenu menu = new SCR_TeamManagementMenu();
            root.AddHandler(menu);
            root.SetVisible(true);
        }
    }
}

/**
 * @brief Button handler for team management menu
 */
class SCR_TeamManagementButtonHandler : ScriptedWidgetEventHandler
{
    protected SCR_TeamManagementMenu m_Menu;
    protected string m_Callback;
    
    /**
     * @brief Constructor
     * @param menu The menu this handler is for
     * @param callback The callback method to call
     */
    void SCR_TeamManagementButtonHandler(SCR_TeamManagementMenu menu, string callback)
    {
        m_Menu = menu;
        m_Callback = callback;
    }
    
    /**
     * @brief Handle button click
     * @param w The button widget
     * @param x Cursor X position
     * @param y Cursor Y position
     */
    bool OnMouseDown(Widget w, int x, int y, int button)
    {
        if (button == MouseButton.LEFT)
        {
            if (m_Menu)
            {
                m_Menu.Invoke(m_Callback);
                return true;
            }
        }
        
        return false;
    }
}
