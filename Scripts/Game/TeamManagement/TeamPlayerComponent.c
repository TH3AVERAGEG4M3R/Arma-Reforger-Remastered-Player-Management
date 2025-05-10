/**
 * @brief Component that attaches to player entities to handle team functionality
 */

// Import necessary classes from the engine
#include "$scripts:Game/Input/InputActions.c"
class TeamPlayerComponent : GenericComponent
{
    protected ref TeamManager m_TeamManager;
    protected bool m_IsInitialized;
    
    // Reference to the team management menu
    protected ref TeamManagementMenu m_TeamMenu;
    
    // Reference to the team respawn menu
    protected ref TeamRespawnMenu m_RespawnMenu;
    
    /**
     * @brief Initialize component
     */
    void OnPostInit(IEntity owner)
    {
        super.OnPostInit(owner);
        
        // Get team manager instance
        m_TeamManager = TeamManager.GetInstance();
        m_IsInitialized = true;
        
        Print("TeamPlayerComponent initialized for player: " + GetPlayerName());
        
        // Register for vehicle interaction callbacks if supported
        RegisterForVehicleInteractions();
        
        // Register for input events
        RegisterInputs(owner);
        
        // Register for player death events
        RegisterForPlayerDeath(owner);
        
        // Add visuals component for team indicators if it doesn't exist
        AddVisualsComponent(owner);
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        Register for player death events
        \param owner The entity that owns this component
    */
    protected void RegisterForPlayerDeath(IEntity owner)
    {
        // Only register for the local player
        PlayerController playerController = PlayerController.Cast(owner.GetController());
        if (!playerController || !playerController.IsLocalPlayer())
            return;
            
        // Get or add an SCR_CharacterDamageManagerComponent to handle death events
        SCR_CharacterDamageManagerComponent damageManager = SCR_CharacterDamageManagerComponent.Cast(owner.FindComponent(SCR_CharacterDamageManagerComponent));
        if (damageManager)
        {
            // Register for the OnDeath event
            damageManager.GetOnDeath().Insert(OnPlayerDeath);
            Print("Registered for player death events: " + GetPlayerName());
        }
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        Callback for when the player dies
        \param character The character entity that died
        \param damageInfo Information about the damage that caused death
    */
    protected void OnPlayerDeath(IEntity character, EDamageType damageType, float damage)
    {
        // Only continue if this is the local player
        PlayerController playerController = PlayerController.Cast(character.GetController());
        if (!playerController || !playerController.IsLocalPlayer())
            return;
            
        Print("Player died, showing respawn menu: " + GetPlayerName());
        
        // Show the team respawn menu
        ShowRespawnMenu();
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        Show the team respawn menu
    */
    void ShowRespawnMenu()
    {
        // Create or show the respawn menu
        if (!m_RespawnMenu)
        {
            m_RespawnMenu = new TeamRespawnMenu();
            m_RespawnMenu.Init();
        }
        
        // Show the menu
        m_RespawnMenu.Show();
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        Register input handlers for key bindings
        \param owner The entity that owns this component
    */
    protected void RegisterInputs(IEntity owner)
    {
        // Only register inputs for the local player
        PlayerController playerController = PlayerController.Cast(owner.GetController());
        if (!playerController || !playerController.IsLocalPlayer())
            return;
            
        // Get the input manager
        InputManager inputManager = GetGame().GetInputManager();
        if (!inputManager)
            return;
            
        // Register for the Team Menu key binding (T)
        inputManager.AddActionListener("TeamManagement.OpenTeamMenu", EActionTrigger.DOWN, OpenTeamMenu);
        
        Print("Team Management key bindings registered for player: " + GetPlayerName());
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        Handle opening the team management menu (T key)
        \param action The action context
        \return True if handled, false otherwise
    */
    protected bool OpenTeamMenu(ActionContext action)
    {
        // Only continue for local player
        IEntity owner = GetOwner();
        PlayerController playerController = PlayerController.Cast(owner.GetController());
        if (!playerController || !playerController.IsLocalPlayer())
            return false;
            
        Print("Opening Team Management Menu for player: " + GetPlayerName());
        
        // Create or show the team management menu
        if (!m_TeamMenu)
        {
            m_TeamMenu = new TeamManagementMenu();
            m_TeamMenu.Init();
        }
        
        // Toggle the menu visibility
        m_TeamMenu.Toggle();
        
        return true;
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        Handle opening the respawn menu (R key)
        \param action The action context
        \return True if handled, false otherwise
    */
    protected bool OpenRespawnMenu(ActionContext action)
    {
        // Only continue for local player
        IEntity owner = GetOwner();
        PlayerController playerController = PlayerController.Cast(owner.GetController());
        if (!playerController || !playerController.IsLocalPlayer())
            return false;
            
        Print("Opening Team Respawn Menu for player: " + GetPlayerName());
        
        // Create or show the respawn menu
        if (!m_RespawnMenu)
        {
            m_RespawnMenu = new TeamRespawnMenu();
            m_RespawnMenu.Init();
        }
        
        // Toggle the menu visibility
        m_RespawnMenu.Toggle();
        
        return true;
    }
    
    /**
     * @brief Handle component shutdown
     */
    void OnDelete(IEntity owner)
    {
        // If player is in a team, leave it when they disconnect
        if (m_IsInitialized && m_TeamManager)
        {
            int teamID = GetCurrentTeam();
            if (teamID > 0)
            {
                Print("Player disconnected, leaving team: " + teamID);
                m_TeamManager.LeaveTeam(owner);
            }
        }
        
        super.OnDelete(owner);
    }
    
    /**
     * @brief Register for vehicle interaction callbacks
     */
    protected void RegisterForVehicleInteractions()
    {
        // Register for vehicle-related events
        // This will be implementation-specific depending on the game's vehicle system
        Print("Player registered for vehicle interactions");
    }
    
    /**
     * @brief Get the current team ID of the player
     * @return The team ID, or 0 if not in a team
     */
    int GetCurrentTeam()
    {
        if (!m_IsInitialized || !m_TeamManager)
            return 0;
        
        IEntity owner = GetOwner();
        if (!owner)
            return 0;
        
        string playerID = GetPlayerID();
        return m_TeamManager.GetPlayerTeam(playerID);
    }
    
    /**
     * @brief Check if the player is a team leader
     * @return True if player is a team leader, false otherwise
     */
    bool IsTeamLeader()
    {
        if (!m_IsInitialized || !m_TeamManager)
            return false;
        
        int teamID = GetCurrentTeam();
        if (teamID <= 0)
            return false;
        
        string playerID = GetPlayerID();
        return m_TeamManager.IsTeamLeader(playerID, teamID);
    }
    
    /**
     * @brief Create a new team with this player as leader
     * @return The ID of the newly created team, or -1 if failed
     */
    int CreateTeam()
    {
        if (!m_IsInitialized || !m_TeamManager)
            return -1;
        
        IEntity owner = GetOwner();
        if (!owner)
            return -1;
        
        return m_TeamManager.CreateTeam(owner);
    }
    
    /**
     * @brief Leave the current team
     * @return True if successful, false otherwise
     */
    bool LeaveTeam()
    {
        if (!m_IsInitialized || !m_TeamManager)
            return false;
        
        IEntity owner = GetOwner();
        if (!owner)
            return false;
        
        return m_TeamManager.LeaveTeam(owner);
    }
    
    /**
     * @brief Send a team invitation to another player
     * @param receiverID The ID of the player to invite
     * @return True if invitation sent successfully, false otherwise
     */
    bool SendInvitation(string receiverID)
    {
        if (!m_IsInitialized || !m_TeamManager)
            return false;
        
        IEntity owner = GetOwner();
        if (!owner)
            return false;
        
        return m_TeamManager.SendInvitation(owner, receiverID);
    }
    
    /**
     * @brief Accept a team invitation
     * @param invitationID The ID of the invitation
     * @return True if accepted successfully, false otherwise
     */
    bool AcceptInvitation(string invitationID)
    {
        if (!m_IsInitialized || !m_TeamManager)
            return false;
        
        IEntity owner = GetOwner();
        if (!owner)
            return false;
        
        return m_TeamManager.AcceptInvitation(invitationID, owner);
    }
    
    /**
     * @brief Decline a team invitation
     * @param invitationID The ID of the invitation
     * @return True if declined successfully, false otherwise
     */
    bool DeclineInvitation(string invitationID)
    {
        if (!m_IsInitialized || !m_TeamManager)
            return false;
        
        IEntity owner = GetOwner();
        if (!owner)
            return false;
        
        return m_TeamManager.DeclineInvitation(invitationID, owner);
    }
    
    /**
     * @brief Get all pending invitations for this player
     * @return Array of pending invitations
     */
    array<ref TeamInvitation> GetPendingInvitations()
    {
        if (!m_IsInitialized || !m_TeamManager)
            return null;
        
        string playerID = GetPlayerID();
        return m_TeamManager.GetPendingInvitations(playerID);
    }
    
    /**
     * @brief Get the members of the player's current team
     * @return Array of team members, or null if not in a team
     */
    array<ref TeamMember> GetTeamMembers()
    {
        if (!m_IsInitialized || !m_TeamManager)
            return null;
        
        int teamID = GetCurrentTeam();
        if (teamID <= 0)
            return null;
        
        return m_TeamManager.GetTeamMembers(teamID);
    }
    
    /**
     * @brief Get the player's ID
     * @return The player's ID
     */
    private string GetPlayerID()
    {
        IEntity owner = GetOwner();
        if (!owner)
            return "";
        
        PlayerController pc = PlayerController.Cast(owner.GetController());
        if (!pc)
            return "";
        
        return pc.GetPlayerId().ToString();
    }
    
    /**
     * @brief Get the player's name
     * @return The player's name
     */
    private string GetPlayerName()
    {
        IEntity owner = GetOwner();
        if (!owner)
            return "Unknown";
        
        PlayerController pc = PlayerController.Cast(owner.GetController());
        if (!pc)
            return "Unknown";
        
        return pc.GetPlayerName();
    }
    
    //=====================================================
    // Vehicle Management Methods
    //=====================================================
    
    /**
     * @brief Lock a vehicle and restrict access to team members
     * @param vehicle The vehicle entity to lock
     * @return True if successful, false otherwise
     */
    bool LockVehicleForTeam(IEntity vehicle)
    {
        if (!m_IsInitialized || !vehicle)
            return false;
        
        int teamID = GetCurrentTeam();
        if (teamID <= 0)
        {
            // Player not in a team
            NotifyPlayer("You must be in a team to lock a vehicle for team access");
            return false;
        }
        
        // Get or create the vehicle team component
        TeamVehicleComponent vehicleComp = GetOrCreateVehicleComponent(vehicle);
        if (!vehicleComp)
            return false;
        
        // Get player entity
        IEntity owner = GetOwner();
        if (!owner)
            return false;
            
        return vehicleComp.LockVehicle(owner);
    }
    
    /**
     * @brief Unlock a previously locked vehicle
     * @param vehicle The vehicle entity to unlock
     * @return True if successful, false otherwise
     */
    bool UnlockVehicle(IEntity vehicle)
    {
        if (!m_IsInitialized || !vehicle)
            return false;
        
        // Get vehicle team component
        TeamVehicleComponent vehicleComp = TeamVehicleComponent.Cast(vehicle.FindComponent(TeamVehicleComponent));
        if (!vehicleComp)
            return false;
        
        // Get player entity
        IEntity owner = GetOwner();
        if (!owner)
            return false;
            
        return vehicleComp.UnlockVehicle(owner);
    }
    
    /**
     * @brief Check if player can access a vehicle based on team membership
     * @param vehicle The vehicle to check
     * @return True if access is allowed, false otherwise
     */
    bool CanAccessVehicle(IEntity vehicle)
    {
        if (!m_IsInitialized || !vehicle)
            return true; // Default to allowing access
        
        // Get vehicle team component
        TeamVehicleComponent vehicleComp = TeamVehicleComponent.Cast(vehicle.FindComponent(TeamVehicleComponent));
        if (!vehicleComp)
            return true; // No team component, allow access
        
        // Get player entity
        IEntity owner = GetOwner();
        if (!owner)
            return false;
            
        return vehicleComp.CanAccessVehicle(owner);
    }
    
    /**
     * @brief Event handler for vehicle access attempts
     * Called by the game when a player tries to enter a vehicle
     * @param vehicle The vehicle being accessed
     * @return True to allow access, false to deny
     */
    bool OnVehicleAccessAttempt(IEntity vehicle)
    {
        if (!m_IsInitialized || !vehicle)
            return true; // Default to allowing access
            
        bool canAccess = CanAccessVehicle(vehicle);
        
        if (!canAccess)
        {
            // Notify player they can't access this vehicle
            NotifyPlayer("You cannot access this vehicle as it is locked by another team");
        }
        
        return canAccess;
    }
    
    /**
     * @brief Get or create a TeamVehicleComponent for the specified vehicle
     * @param vehicle The vehicle entity
     * @return The TeamVehicleComponent, or null if failed
     */
    private TeamVehicleComponent GetOrCreateVehicleComponent(IEntity vehicle)
    {
        if (!vehicle)
            return null;
            
        // Try to find existing component
        TeamVehicleComponent vehicleComp = TeamVehicleComponent.Cast(vehicle.FindComponent(TeamVehicleComponent));
        
        // If not found, create a new one
        if (!vehicleComp)
        {
            vehicleComp = new TeamVehicleComponent();
            vehicle.AddComponent(vehicleComp);
        }
        
        return vehicleComp;
    }
    
    /**
     * @brief Send a notification to the player
     * @param message The message to send
     */
    private void NotifyPlayer(string message)
    {
        // Use game's notification system if available
        // For now, just print to the console
        Print("NOTIFICATION: " + message);
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Add the TeamVisualsComponent for team HUD/map indicators
     * @param owner The entity to add the component to
     */
    protected void AddVisualsComponent(IEntity owner)
    {
        // Check if component already exists
        TeamVisualsComponent visualsComponent = TeamVisualsComponent.Cast(owner.FindComponent(TeamVisualsComponent));
        if (visualsComponent)
            return; // Already has the component
        
        // Create and add the component
        visualsComponent = new TeamVisualsComponent();
        if (owner.AddComponent(visualsComponent))
        {
            Print("Added TeamVisualsComponent to player: " + GetPlayerName());
        }
        else
        {
            Print("Failed to add TeamVisualsComponent to player: " + GetPlayerName());
        }
    }
}