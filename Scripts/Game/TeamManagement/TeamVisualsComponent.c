/**
 * @brief HUD Icon class for displaying team member icons on the HUD
 */
class HudIcon
{
    // The entity this icon is attached to
    protected IEntity m_Entity;

    // Icon resource
    protected ResourceName m_IconResource;

    // Icon color
    protected ref Color m_Color;

    // Whether the icon is visible
    protected bool m_Visible = true;

    // Display name
    protected string m_DisplayName;

    // Icon size
    protected float m_Size = 16.0;

    //------------------------------------------------------------------------------------------------
    /**
     * @brief Constructor
     * @param entity The entity this icon is attached to
     */
    void HudIcon(IEntity entity)
    {
        m_Entity = entity;
        m_Color = Color.White();
    }

    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the icon resource
     * @param resourcePath Path to the icon resource
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
     * @brief Set whether the icon is visible
     * @param visible True to show, false to hide
     */
    void SetVisible(bool visible)
    {
        m_Visible = visible;
    }

    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the display name
     * @param name The name to display
     */
    void SetDisplayName(string name)
    {
        m_DisplayName = name;
    }

    //------------------------------------------------------------------------------------------------
    /**
     * @brief Set the icon size
     * @param size Size in pixels
     */
    void SetSize(float size)
    {
        m_Size = size;
    }

    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the target entity
     * @return The entity
     */
    IEntity GetEntity()
    {
        return m_Entity;
    }

    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the icon resource
     * @return The resource path
     */
    ResourceName GetIconResource()
    {
        return m_IconResource;
    }

    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the icon color
     * @return The color
     */
    Color GetColor()
    {
        return m_Color;
    }

    //------------------------------------------------------------------------------------------------
    /**
     * @brief Check if the icon is visible
     * @return True if visible
     */
    bool IsVisible()
    {
        return m_Visible;
    }

    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the display name
     * @return The display name
     */
    string GetDisplayName()
    {
        return m_DisplayName;
    }

    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get the icon size
     * @return Size in pixels
     */
    float GetSize()
    {
        return m_Size;
    }
}

/**
 * @brief Team Visuals Component for displaying team indicators
 */
class TeamVisualsComponentClass : ScriptComponentClass
{
}

//------------------------------------------------------------------------------------------------
/*!
    Component for handling visual indicators for team members
*/
class TeamVisualsComponent : ScriptComponent
{
    // Resources for team member indicators
    protected const ResourceName LEADER_ICON_RESOURCE = "UI/Textures/HUD/Icons/LeaderIcon.edds";
    protected const ResourceName MEMBER_ICON_RESOURCE = "UI/Textures/HUD/Icons/TeamMemberIcon.edds";
    protected const ResourceName MAP_LEADER_ICON_RESOURCE = "UI/Textures/Map/MapIconLeader.edds";
    protected const ResourceName MAP_MEMBER_ICON_RESOURCE = "UI/Textures/Map/MapIconTeamMember.edds";

    // Team colors for different teams
    protected const array<ref Color> TEAM_COLORS = {
        Color.Yellow(),  // Team 1
        Color.Blue(),    // Team 2
        Color.Red(),     // Team 3
        Color.Green(),   // Team 4
        Color.Magenta(), // Team 5
        Color.Cyan(),    // Team 6
        Color.Orange(),  // Team 7
        Color.Purple()   // Team 8
    };

    // Player entity this component is attached to
    protected IEntity m_PlayerEntity;

    // Current team ID
    protected int m_CurrentTeamID = 0;

    // Map indicator for this player
    protected ref MapMarkerComponent m_MapMarker;

    // HUD indicator for this player
    protected ref HudIcon m_HudIcon;

    // Team manager reference
    protected ref TeamManager m_TeamManager;

    // Is player a leader
    protected bool m_IsLeader = false;

    // Reference to HUD manager
    protected TeamHUDManagerComponent m_HudManager;
    // Reference to Map entity
    protected TeamMapEntity m_MapEntity;

    //------------------------------------------------------------------------------------------------
    override void OnPostInit(IEntity owner)
    {
        super.OnPostInit(owner);

        // Store reference to player entity
        m_PlayerEntity = owner;

        // Get team manager
        m_TeamManager = TeamManager.GetInstance();
        if (!m_TeamManager)
            return;

        // Get HUD manager
        m_HudManager = TeamHUDManagerComponent.GetInstance();

        // Get Map entity
        m_MapEntity = TeamMapEntity.GetMapInstance();

        // Create map marker
        CreateMapMarker();

        // Create HUD icon
        CreateHudIcon();

        // Register for team change events
        if (m_TeamManager)
            m_TeamManager.GetOnTeamChanged().Insert(OnTeamChanged);
    }

    //------------------------------------------------------------------------------------------------
    void ~TeamVisualsComponent()
    {
        // Unregister from team change events
        if (m_TeamManager)
            m_TeamManager.GetOnTeamChanged().Remove(OnTeamChanged);

        // Remove map marker
        if (m_MapEntity && m_MapMarker)
            m_MapEntity.RemoveMarker(m_MapMarker);

        // Remove HUD icon
        if (m_HudManager && m_HudIcon)
            m_HudManager.RemoveHudIcon(m_HudIcon);
    }

    //------------------------------------------------------------------------------------------------
    /**
     * @brief Handle team change events
     * @param entityID The entity ID of the player
     * @param oldTeamID The previous team ID
     * @param newTeamID The new team ID
     */
    void OnTeamChanged(int entityID, int oldTeamID, int newTeamID)
    {
        // Check if this is the player we are attached to
        if (m_PlayerEntity.GetID() != entityID)
            return;

        // Update team ID
        m_CurrentTeamID = newTeamID;

        // Check if player is a leader
        string playerID = GetPlayerIdentity(m_PlayerEntity);
        m_IsLeader = m_TeamManager.IsTeamLeader(playerID, newTeamID);

        // Update visuals
        UpdateMarkerVisuals();
        UpdateHudVisuals();
    }

    //------------------------------------------------------------------------------------------------
    /**
     * @brief Create a map marker for this player
     */
    protected void CreateMapMarker()
    {
        if (!m_MapEntity)
            return;

        m_MapMarker = new MapMarkerComponent();
        m_MapMarker.SetEntityTarget(m_PlayerEntity);

        // Set initial properties
        UpdateMarkerVisuals();

        // Add to map
        m_MapEntity.AddMarker(m_MapMarker);
    }

    //------------------------------------------------------------------------------------------------
    /**
     * @brief Create a HUD icon for this player
     */
    protected void CreateHudIcon()
    {
        if (!m_HudManager)
            return;

        m_HudIcon = new HudIcon(m_PlayerEntity);

        // Set initial properties
        UpdateHudVisuals();

        // Add to HUD
        m_HudManager.AddHudIcon(m_HudIcon);
    }

    //------------------------------------------------------------------------------------------------
    /**
     * @brief Update marker visuals based on current properties
     */
    protected void UpdateMarkerVisuals()
    {
        if (!m_MapMarker)
            return;

        // If not in a team, hide the marker
        if (m_CurrentTeamID <= 0)
        {
            m_MapMarker.SetVisible(false);
            return;
        }

        // Show the marker
        m_MapMarker.SetVisible(true);

        // Set appropriate icon
        if (m_IsLeader)
            m_MapMarker.SetIconFromResource(MAP_LEADER_ICON_RESOURCE);
        else
            m_MapMarker.SetIconFromResource(MAP_MEMBER_ICON_RESOURCE);

        // Set team color
        int colorIndex = (m_CurrentTeamID - 1) % TEAM_COLORS.Count();
        m_MapMarker.SetBaseColor(TEAM_COLORS[colorIndex]);

        // Set display name (player name)
        m_MapMarker.SetDisplayName(GetPlayerName(m_PlayerEntity));
    }

    //------------------------------------------------------------------------------------------------
    /**
     * @brief Update HUD visuals based on current properties
     */
    protected void UpdateHudVisuals()
    {
        if (!m_HudIcon)
            return;

        // If not in a team, hide the icon
        if (m_CurrentTeamID <= 0)
        {
            m_HudIcon.SetVisible(false);
            return;
        }

        // Show the icon
        m_HudIcon.SetVisible(true);

        // Set appropriate icon
        if (m_IsLeader)
            m_HudIcon.SetIconResource(LEADER_ICON_RESOURCE);
        else
            m_HudIcon.SetIconResource(MEMBER_ICON_RESOURCE);

        // Set team color
        int colorIndex = (m_CurrentTeamID - 1) % TEAM_COLORS.Count();
        m_HudIcon.SetColor(TEAM_COLORS[colorIndex]);

        // Set display name (player name)
        m_HudIcon.SetDisplayName(GetPlayerName(m_PlayerEntity));
    }

    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get player identity
     * @param player The player entity
     * @return The player identity string
     */
    protected string GetPlayerIdentity(IEntity player)
    {
        if (!player)
            return "";

        PlayerController pc = PlayerController.Cast(player.GetController());
        if (!pc)
            return "";

        return pc.GetPlayerId();
    }

    //------------------------------------------------------------------------------------------------
    /**
     * @brief Get player name
     * @param player The player entity
     * @return The player name
     */
    protected string GetPlayerName(IEntity player)
    {
        if (!player)
            return "Unknown";

        PlayerController pc = PlayerController.Cast(player.GetController());
        if (!pc)
            return "Unknown";

        return pc.GetPlayerName();
    }
}