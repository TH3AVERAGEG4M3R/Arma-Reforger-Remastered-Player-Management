/**
 * @brief Component for handling team member visual indicators on map and HUD
 */
class TeamVisualsComponent : SCR_BaseGameComponent
{
    // Color for team markers and indicators (default to blue)
    protected Color m_TeamColor = Color.Blue();
    
    // Size of markers on the map
    protected const float MARKER_SIZE = 24.0;
    
    // Maximum distance for HUD icon display
    protected const float MAX_HUD_DISPLAY_DISTANCE = 500.0;
    
    // Distance for name display
    protected const float NAME_DISPLAY_DISTANCE = 50.0;
    
    // The player's team
    protected int m_TeamID;
    
    // Team manager reference
    protected ref TeamManager m_TeamManager;
    
    // Map displays
    protected ref array<ref MapMarkerComponent> m_TeamMarkers = new array<ref MapMarkerComponent>();
    
    // HUD displays
    protected ref array<ref HudIcon> m_TeamIcons = new array<ref HudIcon>();
    
    // Is visuals system initialized
    protected bool m_Initialized = false;
    
    // Last update timestamp
    protected float m_LastUpdateTime = 0;
    
    // Update interval (seconds)
    protected const float UPDATE_INTERVAL = 1.0;
    
    //------------------------------------------------------------------------------------------------
    override void OnPostInit(IEntity owner)
    {
        super.OnPostInit(owner);
        
        // Get team manager
        m_TeamManager = TeamManager.GetInstance();
        if (!m_TeamManager)
        {
            Print("TeamVisualsComponent: Failed to get TeamManager instance");
            return;
        }
        
        // Register for team changes
        RegisterForTeamChanges();
        
        // Only proceed for local player
        PlayerController playerController = PlayerController.Cast(owner.GetController());
        if (!playerController || !playerController.IsLocalPlayer())
            return;
        
        // Set up update event
        GetGame().GetCallqueue().CallLater(UpdateTeamVisuals, 1000, true);
        
        m_Initialized = true;
        Print("TeamVisualsComponent initialized");
    }
    
    //------------------------------------------------------------------------------------------------
    override void OnDelete(IEntity owner)
    {
        // Clean up resources
        ClearAllTeamMarkers();
        ClearAllTeamIcons();
        
        // Remove update callback
        GetGame().GetCallqueue().Remove(UpdateTeamVisuals);
        
        super.OnDelete(owner);
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Register for team change events
     */
    protected void RegisterForTeamChanges()
    {
        if (!m_TeamManager)
            return;
            
        // Find player's team component
        IEntity owner = GetOwner();
        if (!owner)
            return;
            
        TeamPlayerComponent playerTeamComp = TeamPlayerComponent.Cast(owner.FindComponent(TeamPlayerComponent));
        if (!playerTeamComp)
            return;
            
        // Get current team
        m_TeamID = playerTeamComp.GetCurrentTeam();
        
        // Listen for team changes through script events
        ScriptInvokerBase<func void> teamChangedInvoker = m_TeamManager.GetOnTeamChangedInvoker();
        if (teamChangedInvoker)
        {
            teamChangedInvoker.Insert(OnTeamChanged);
        }
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Handle team change event
     */
    protected void OnTeamChanged(int playerEntityID, int oldTeamID, int newTeamID)
    {
        // Check if it's this player's team change
        IEntity owner = GetOwner();
        if (!owner || owner.GetID() != playerEntityID)
            return;
            
        // Update team ID
        m_TeamID = newTeamID;
        
        // Update visual indicators
        UpdateTeamVisuals();
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Update all team visual indicators
     */
    protected void UpdateTeamVisuals()
    {
        if (!m_Initialized || !m_TeamManager)
            return;
            
        // Skip if not enough time has passed
        float currentTime = GetGame().GetWorld().GetWorldTime();
        if (currentTime - m_LastUpdateTime < UPDATE_INTERVAL)
            return;
            
        m_LastUpdateTime = currentTime;
        
        // Clear old indicators
        ClearAllTeamMarkers();
        ClearAllTeamIcons();
        
        // If not in a team, nothing to display
        if (m_TeamID <= 0)
            return;
            
        // Get team members
        array<ref TeamMember> teamMembers = m_TeamManager.GetTeamMembers(m_TeamID);
        if (!teamMembers || teamMembers.Count() == 0)
            return;
            
        // Get local player's entity
        IEntity localPlayer = GetOwner();
        if (!localPlayer)
            return;
            
        int localPlayerID = localPlayer.GetID();
        
        // Create visual indicators for each team member
        foreach (TeamMember member : teamMembers)
        {
            // Skip self
            int memberEntityID = member.GetEntityID();
            if (memberEntityID == localPlayerID)
                continue;
                
            // Find team member entity
            IEntity memberEntity = GetGame().GetWorld().FindEntityByID(memberEntityID);
            if (!memberEntity)
                continue;
                
            // Create map marker
            CreateMapMarker(memberEntity, member.GetPlayerName(), member.IsLeader());
            
            // Create HUD icon
            CreateHudIcon(memberEntity, member.GetPlayerName(), member.IsLeader());
        }
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Create a map marker for a team member
     * @param entity The entity to mark
     * @param playerName The player's name
     * @param isLeader Whether this player is the team leader
     */
    protected void CreateMapMarker(IEntity entity, string playerName, bool isLeader)
    {
        if (!entity)
            return;
            
        // Get map display interface
        SCR_MapEntity mapEntity = SCR_MapEntity.GetMapInstance();
        if (!mapEntity)
            return;
            
        // Create marker
        MapMarkerComponent marker = new MapMarkerComponent();
        
        // Set marker properties
        marker.SetEntityTarget(entity);
        
        // Set different icon for leader vs regular member
        if (isLeader)
            marker.SetIconFromResource("{FEF31452F8FB99EB}UI/Textures/Map/MapIconLeader.edds");
        else
            marker.SetIconFromResource("{34A26F4542321B7D}UI/Textures/Map/MapIconTeamMember.edds");
            
        marker.SetBaseColor(m_TeamColor);
        marker.SetDisplayRadius(MARKER_SIZE);
        marker.SetDisplayName(playerName);
        
        // Add marker to map and store reference
        mapEntity.AddMarker(marker);
        m_TeamMarkers.Insert(marker);
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Create a HUD icon for a team member
     * @param entity The entity to mark
     * @param playerName The player's name
     * @param isLeader Whether this player is the team leader
     */
    protected void CreateHudIcon(IEntity entity, string playerName, bool isLeader)
    {
        if (!entity)
            return;
            
        // Get HUD manager
        SCR_HUDManagerComponent hudManager = SCR_HUDManagerComponent.GetInstance();
        if (!hudManager)
            return;
            
        // Create new HUD icon
        HudIcon icon = new HudIcon();
        
        // Set icon properties
        icon.SetTargetEntity(entity);
        
        // Set different icon for leader vs regular member
        if (isLeader)
            icon.SetIconResource("{A26C465055DBD649}UI/Textures/HUD/Icons/LeaderIcon.edds");
        else
            icon.SetIconResource("{D8CB338D0BF6837E}UI/Textures/HUD/Icons/TeamMemberIcon.edds");
            
        icon.SetColor(m_TeamColor);
        icon.SetDisplayRadius(16.0);
        icon.SetMaxDisplayDistance(MAX_HUD_DISPLAY_DISTANCE);
        icon.SetPlayerName(playerName, NAME_DISPLAY_DISTANCE);
        
        // Add icon to HUD and store reference
        hudManager.AddHudIcon(icon);
        m_TeamIcons.Insert(icon);
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Clear all team map markers
     */
    protected void ClearAllTeamMarkers()
    {
        // Get map display interface
        SCR_MapEntity mapEntity = SCR_MapEntity.GetMapInstance();
        if (!mapEntity)
            return;
            
        // Remove all markers
        foreach (MapMarkerComponent marker : m_TeamMarkers)
        {
            mapEntity.RemoveMarker(marker);
        }
        
        m_TeamMarkers.Clear();
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Clear all team HUD icons
     */
    protected void ClearAllTeamIcons()
    {
        // Get HUD manager
        SCR_HUDManagerComponent hudManager = SCR_HUDManagerComponent.GetInstance();
        if (!hudManager)
            return;
            
        // Remove all icons
        foreach (HudIcon icon : m_TeamIcons)
        {
            hudManager.RemoveHudIcon(icon);
        }
        
        m_TeamIcons.Clear();
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the team color
     * @param color The color to use for team visual indicators
     */
    void SetTeamColor(Color color)
    {
        m_TeamColor = color;
        UpdateTeamVisuals();
    }
}

// Hud Icon implementation for team members
class HudIcon
{
    protected IEntity m_TargetEntity;
    protected ResourceName m_IconResource;
    protected Color m_Color = Color.Blue();
    protected float m_DisplayRadius = 16.0;
    protected float m_MaxDisplayDistance = 500.0;
    protected string m_PlayerName;
    protected float m_NameDisplayDistance = 50.0;
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the target entity for this icon
     * @param entity The entity to track
     */
    void SetTargetEntity(IEntity entity)
    {
        m_TargetEntity = entity;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the icon resource
     * @param resourcePath Path to the icon texture
     */
    void SetIconResource(ResourceName resourcePath)
    {
        m_IconResource = resourcePath;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the icon color
     * @param color The color to use
     */
    void SetColor(Color color)
    {
        m_Color = color;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the display radius
     * @param radius The radius in pixels
     */
    void SetDisplayRadius(float radius)
    {
        m_DisplayRadius = radius;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the maximum display distance
     * @param distance The maximum distance in meters
     */
    void SetMaxDisplayDistance(float distance)
    {
        m_MaxDisplayDistance = distance;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the player name for display
     * @param name The player name
     * @param displayDistance Distance at which to display the name
     */
    void SetPlayerName(string name, float displayDistance)
    {
        m_PlayerName = name;
        m_NameDisplayDistance = displayDistance;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the target entity
     * @return The target entity
     */
    IEntity GetTargetEntity()
    {
        return m_TargetEntity;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the icon resource
     * @return The icon resource path
     */
    ResourceName GetIconResource()
    {
        return m_IconResource;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the icon color
     * @return The icon color
     */
    Color GetColor()
    {
        return m_Color;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the display radius
     * @return The display radius in pixels
     */
    float GetDisplayRadius()
    {
        return m_DisplayRadius;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the maximum display distance
     * @return The maximum display distance in meters
     */
    float GetMaxDisplayDistance()
    {
        return m_MaxDisplayDistance;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the player name
     * @return The player name
     */
    string GetPlayerName()
    {
        return m_PlayerName;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the name display distance
     * @return The distance at which to display the name
     */
    float GetNameDisplayDistance()
    {
        return m_NameDisplayDistance;
    }
}