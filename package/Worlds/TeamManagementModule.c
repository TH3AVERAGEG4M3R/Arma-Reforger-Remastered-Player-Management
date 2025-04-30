/**
 * @brief World module for initializing the team management system
 */
class TeamManagementModule : ScriptModule
{
    // Input manager reference
    protected InputManager m_InputManager;
    
    // Key binding ID for opening team menu
    protected int m_OpenTeamMenuActionID;
    
    // Team manager reference
    protected ref TeamManager m_TeamManager;
    
    // Team network component reference
    protected ref TeamNetworkComponent m_NetworkComponent;
    
    // Timer for handling expired invitations
    protected float m_InvitationCleanupTimer;
    
    // Timer for network synchronization
    protected float m_NetworkSyncTimer;
    
    // Time between cleaning up expired invitations (seconds)
    protected const float INVITATION_CLEANUP_INTERVAL = 30.0;
    
    // Time between network synchronizations (seconds)
    protected const float NETWORK_SYNC_INTERVAL = 10.0;
    
    /**
     * @brief Module initialization
     */
    override void OnInit()
    {
        Print("TeamManagementModule - Initializing...");
        
        // Create and initialize team manager
        m_TeamManager = TeamManager.GetInstance();
        
        // Initialize network component for multiplayer
        if (GetGame().IsMultiplayer())
        {
            m_NetworkComponent = TeamNetworkComponent.GetInstance();
            Print("TeamManagementModule - Network component initialized");
        }
        
        // Set up input manager
        m_InputManager = GetGame().GetInputManager();
        if (m_InputManager)
        {
            m_OpenTeamMenuActionID = m_InputManager.GetActionID("TeamManagement.OpenTeamMenu");
        }
        
        Print("TeamManagementModule - Initialized successfully");
    }
    
    /**
     * @brief Module shutdown
     */
    override void OnShutdown()
    {
        Print("TeamManagementModule - Shutting down...");
    }
    
    /**
     * @brief World update
     * @param timeslice Time since last update
     */
    override void OnUpdate(float timeslice)
    {
        // Check for team menu key press
        if (m_InputManager && m_InputManager.IsActionTriggered(m_OpenTeamMenuActionID))
        {
            OnOpenTeamMenuAction();
        }
        
        // Handle invitation cleanup
        m_InvitationCleanupTimer += timeslice;
        if (m_InvitationCleanupTimer >= INVITATION_CLEANUP_INTERVAL)
        {
            m_InvitationCleanupTimer = 0;
            CleanupExpiredInvitations();
        }
        
        // Handle network sync for multiplayer
        if (GetGame().IsMultiplayer() && GetGame().IsServer())
        {
            m_NetworkSyncTimer += timeslice;
            if (m_NetworkSyncTimer >= NETWORK_SYNC_INTERVAL)
            {
                m_NetworkSyncTimer = 0;
                SyncTeamData();
            }
        }
    }
    
    /**
     * @brief Handle the open team menu action
     */
    protected void OnOpenTeamMenuAction()
    {
        // Get player controller
        PlayerController playerController = GetGame().GetPlayerController();
        if (!playerController)
            return;
        
        // Create and show team management menu
        SCR_TeamManagementMenu.CreateMenu(playerController);
    }
    
    /**
     * @brief Clean up expired invitations
     */
    protected void CleanupExpiredInvitations()
    {
        if (!m_TeamManager)
            return;
        
        // Teams implementation would handle this internally
        // This is a placeholder for when we implement the invitation timeout feature
    }
    
    /**
     * @brief Sync team data for all players
     * Used in multiplayer to ensure all clients have up-to-date team information
     */
    protected void SyncTeamData()
    {
        if (!m_NetworkComponent || !GetGame().IsServer())
            return;
        
        // Get all players
        array<IEntity> players = new array<IEntity>();
        GetGame().GetWorld().GetPlayerManager().GetPlayers(players);
        
        // Sync team data for each player
        foreach (IEntity player : players)
        {
            m_NetworkComponent.SyncTeamData(player);
        }
    }
    
    /**
     * @brief Register new player
     * @param player The new player entity
     */
    void OnPlayerRegistered(IEntity player)
    {
        // Add any player-specific initialization here
        
        // For server: sync team data to new player if they're in a team
        if (GetGame().IsServer() && GetGame().IsMultiplayer() && m_NetworkComponent)
        {
            m_NetworkComponent.SyncTeamData(player);
        }
    }
    
    /**
     * @brief Handle player disconnection
     * @param player The disconnected player entity
     */
    void OnPlayerDisconnected(IEntity player)
    {
        if (!player || !m_TeamManager)
            return;
        
        // Get player controller
        PlayerController pc = PlayerController.Cast(player.GetController());
        if (!pc)
            return;
        
        // Remove player from team when they disconnect
        m_TeamManager.LeaveTeam(player);
    }
    
    /**
     * @brief Get the team manager instance
     * @return The team manager instance
     */
    TeamManager GetTeamManager()
    {
        return m_TeamManager;
    }
}
