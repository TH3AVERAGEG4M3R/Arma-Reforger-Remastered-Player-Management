class TeamRespawnMenuClass: SCR_ScriptedWidgetComponentClass
{
};

//------------------------------------------------------------------------------------------------
/*!
    UI component for managing team respawn points.
    Allows team leaders to purchase flagpoles and all team members to select respawn points.
*/
class TeamRespawnMenu: SCR_ScriptedWidgetComponent
{
    // Widget references
    protected Widget m_wRoot;
    protected Widget m_wRespawnPointsList;
    protected ButtonWidget m_wBuyFlagpoleButton;
    protected EditBoxWidget m_wRespawnNameInput;
    protected TextWidget m_wStatusText;

    // Selected respawn point data
    protected int m_SelectedRespawnEntityID = -1;

    // Reference to the TeamManager
    protected TeamManager m_TeamManager;

    // List of available respawn points for the player's team
    protected ref array<IEntity> m_AvailableRespawnPoints = new array<IEntity>();

    //------------------------------------------------------------------------------------------------
    /*!
        Initialize the respawn menu
    */
    void Init()
    {
        // Create the menu widget from layout
        m_wRoot = GetGame().GetWorkspace().CreateWidgets("UI/layouts/TeamManagement/TeamRespawnMenu.layout");
        if (!m_wRoot)
        {
            Print("Failed to create TeamRespawnMenu layout");
            return;
        }

        // Add this handler to the widget
        m_wRoot.AddHandler(this);

        // Hide by default
        m_wRoot.SetVisible(false);
    }

    //------------------------------------------------------------------------------------------------
    override void HandlerAttached(Widget w)
    {
        super.HandlerAttached(w);

        m_wRoot = w;

        // Get the TeamManager
        m_TeamManager = TeamManager.GetInstance();

        // Find widgets
        m_wRespawnPointsList = w.FindAnyWidget("RespawnPointsList");
        m_wBuyFlagpoleButton = ButtonWidget.Cast(w.FindAnyWidget("BuyFlagpoleButton"));
        m_wRespawnNameInput = EditBoxWidget.Cast(w.FindAnyWidget("RespawnNameInput"));
        m_wStatusText = TextWidget.Cast(w.FindAnyWidget("StatusText"));

        // Initialize UI components
        if (m_wBuyFlagpoleButton)
        {
            m_wBuyFlagpoleButton.SetVisible(false); // Only show to team leaders
        }

        // Register for button handlers
        if (m_wBuyFlagpoleButton)
        {
            m_wBuyFlagpoleButton.AddHandler(new PurchaseFlagpoleButtonHandler(this));
        }

        // Update the UI
        UpdateUI();
    }

    //------------------------------------------------------------------------------------------------
    void UpdateUI()
    {
        // Clear the list
        if (m_wRespawnPointsList)
        {
            m_wRespawnPointsList.ClearItems();
        }

        if (!m_TeamManager)
            return;

        // Get the local player entity
        IEntity playerEntity = SCR_PlayerController.GetLocalControlledEntity();
        if (!playerEntity)
            return;

        int playerID = playerEntity.GetID();

        // Get the player's team member
        TeamMember playerMember = m_TeamManager.GetTeamMemberByEntityID(playerID);
        if (!playerMember)
        {
            if (m_wStatusText)
            {
                m_wStatusText.SetText("You are not in a team. Join a team to access respawn points.");
            }
            return;
        }

        // Show buy button for team leaders
        if (m_wBuyFlagpoleButton)
        {
            m_wBuyFlagpoleButton.SetVisible(playerMember.IsLeader());
        }

        // Get the player's team ID
        int teamID = playerMember.GetTeamID();

        // Find all team flagpoles in the world
        FindTeamRespawnPoints(teamID);

        // Add respawn points to the list
        foreach (IEntity respawnEntity : m_AvailableRespawnPoints)
        {
            TeamFlagpole flagpole = TeamFlagpole.Cast(respawnEntity);
            if (!flagpole)
                continue;

            TeamRespawnComponent respawnComponent = flagpole.GetRespawnComponent();
            if (!respawnComponent)
                continue;

            // Create list item
            Widget respawnItem = GetGame().GetWorkspace().CreateWidgets("UI/layouts/TeamManagement/RespawnPointListItem.layout", m_wRespawnPointsList);
            if (!respawnItem)
                continue;

            // Set respawn point info
            TextWidget nameText = TextWidget.Cast(respawnItem.FindAnyWidget("RespawnPointName"));
            if (nameText)
            {
                nameText.SetText(respawnComponent.GetRespawnName());
            }

            // Check if player is on cooldown for this respawn point
            float remainingCooldown;
            bool onCooldown = respawnComponent.IsPlayerOnCooldown(playerID, remainingCooldown);

            // Set button handler for selecting this respawn point
            ButtonWidget selectButton = ButtonWidget.Cast(respawnItem.FindAnyWidget("SelectRespawnButton"));
            if (selectButton)
            {
                if (onCooldown)
                {
                    // Format cooldown time
                    int minutes = Math.Floor(remainingCooldown / 60);
                    int seconds = Math.Floor(remainingCooldown) % 60;
                    string secondsStr = seconds < 10 ? "0" + seconds.ToString() : seconds.ToString();
                    string cooldownText = minutes.ToString() + ":" + secondsStr;

                    // Disable button and show cooldown time
                    selectButton.SetEnabled(false);
                    selectButton.SetText("COOLDOWN: " + cooldownText);
                    selectButton.SetColor(Color.Red());
                }
                else
                {
                    // Enable button for respawn
                    selectButton.SetEnabled(true);
                    selectButton.SetText("SELECT");
                    selectButton.SetColor(Color.Blue());
                    selectButton.AddHandler(new SelectRespawnButtonHandler(this, respawnEntity.GetID()));
                }
            }
        }
    }

    // Update status text
    if (m_wStatusText)
        {
            if (m_AvailableRespawnPoints.Count() > 0)
            {
                m_wStatusText.SetText("Select a respawn point to spawn at that location.");
            }
            else
            {
                m_wStatusText.SetText("No team respawn points available. Team leaders can purchase respawn points.");
            }
        }
    }
    
    //------------------------------------------------------------------------------------------------
    /*!
        Find all respawn points available for the player's team
        \param teamID The team ID to search for
    */
    void FindTeamRespawnPoints(int teamID)
    {
        m_AvailableRespawnPoints.Clear();

        // Find all flagpoles in the world
        array<IEntity> foundEntities = new array<IEntity>();
        GetGame().GetWorld().FindEntitiesByType(TeamFlagpole, foundEntities);

        // Filter for the player's team
        foreach (IEntity entity : foundEntities)
        {
            TeamFlagpole flagpole = TeamFlagpole.Cast(entity);
            if (!flagpole)
                continue;

            TeamRespawnComponent respawnComponent = flagpole.GetRespawnComponent();
            if (!respawnComponent)
                continue;

            // Check if this respawn point belongs to the player's team
            if (respawnComponent.GetTeamID() == teamID)
            {
                m_AvailableRespawnPoints.Insert(entity);
            }
        }
    }

    //------------------------------------------------------------------------------------------------
    /*!
        Handle purchasing a new flagpole
    */
    void OnPurchaseFlagpole()
    {
        if (!m_TeamManager)
            return;

        // Get the local player entity
        IEntity playerEntity = SCR_PlayerController.GetLocalControlledEntity();
        if (!playerEntity)
            return;

        int playerID = playerEntity.GetID();

        // Get the player's team member
        TeamMember playerMember = m_TeamManager.GetTeamMemberByEntityID(playerID);
        if (!playerMember || !playerMember.IsLeader())
            return;

        // Get custom name from input field
        string customName = "";
        if (m_wRespawnNameInput)
        {
            customName = m_wRespawnNameInput.GetText();
            if (customName == "")
            {
                customName = "Team Respawn Point";
            }
        }

        // Find nearby positions to place the flagpole
        vector playerPos = playerEntity.GetOrigin();
        vector spawnPos = playerPos + playerEntity.GetTransformAxis(0) * 2; // Spawn 2 meters in front of the player

        // Spawn the flagpole entity
        EntitySpawnParams spawnParams = new EntitySpawnParams();
        spawnParams.TransformMode = ETransformMode.WORLD;
        spawnParams.Transform[3] = spawnPos;

        // Note: "TeamManagement.TeamFlagpole" should match the resource name in config.cpp
        Resource res = Resource.Load("TeamManagement.TeamFlagpole");
        if (!res)
        {
            if (m_wStatusText)
            {
                m_wStatusText.SetText("Failed to load flagpole resource. Contact an administrator.");
            }
            return;
        }

        // Spawn the entity
        IEntity flagpoleEntity = GetGame().SpawnEntityPrefab(res, GetGame().GetWorld(), spawnParams);
        if (!flagpoleEntity)
        {
            if (m_wStatusText)
            {
                m_wStatusText.SetText("Failed to spawn flagpole. Try a different location.");
            }
            return;
        }

        // Purchase the flagpole
        TeamFlagpole flagpole = TeamFlagpole.Cast(flagpoleEntity);
        if (flagpole)
        {
            flagpole.PurchaseFlagpole(playerID, customName);

            if (m_wStatusText)
            {
                m_wStatusText.SetText("Flagpole purchased successfully!");
            }

            // Reset the input field
            if (m_wRespawnNameInput)
            {
                m_wRespawnNameInput.SetText("");
            }

            // Update the UI to show the new respawn point
            UpdateUI();
        }
    }

    //------------------------------------------------------------------------------------------------
    /*!
        Show the respawn menu (used when player dies)
    */
    void Show()
    {
        if (m_wRoot)
        {
            // Always show and update when called after death
            m_wRoot.SetVisible(true);
            UpdateUI();
        }
    }

    //------------------------------------------------------------------------------------------------
    /*!
        Handle selecting a respawn point
        \param respawnEntityID The entity ID of the selected respawn point
    */
    void OnSelectRespawnPoint(int respawnEntityID)
    {
        m_SelectedRespawnEntityID = respawnEntityID;

        // Get the local player entity
        IEntity playerEntity = SCR_PlayerController.GetLocalControlledEntity();
        if (!playerEntity)
            return;

        int playerID = playerEntity.GetID();

        // Get the respawn entity
        IEntity respawnEntity = GetGame().GetWorld().FindEntityByID(respawnEntityID);
        if (!respawnEntity)
            return;

        TeamFlagpole flagpole = TeamFlagpole.Cast(respawnEntity);
        if (!flagpole)
            return;

        TeamRespawnComponent respawnComponent = flagpole.GetRespawnComponent();
        if (!respawnComponent)
            return;

        // Request respawn at the selected point
        if (GetGame().GetNetMode() == ENetMode.NM_Client)
        {
            // Send RPC to server
            RplComponent rpl = RplComponent.Cast(respawnEntity.FindComponent(RplComponent));
            if (rpl)
            {
                ScriptRPC rpc = new ScriptRPC();
                rpc.Write(playerID);
                rpl.SendRPC("RPC_RequestRespawn", rpc);
            }
        }
        else
        {
            // Direct call on the server
            respawnComponent.HandleRespawnRequest(playerID);
        }

        // Update status text
        if (m_wStatusText)
        {
            m_wStatusText.SetText("Respawning at selected point...");
        }

        // Close the respawn menu
        if (m_wRoot)
        {
            m_wRoot.SetVisible(false);
        }
    }
}

//------------------------------------------------------------------------------------------------
class PurchaseFlagpoleButtonHandler : SCR_ButtonHandler
{
    protected TeamRespawnMenu m_Menu;

    void PurchaseFlagpoleButtonHandler(TeamRespawnMenu menu)
    {
        m_Menu = menu;
    }

    override bool OnClick(Widget w)
    {
        if (m_Menu)
        {
            m_Menu.OnPurchaseFlagpole();
        }
        return true;
    }
}

//------------------------------------------------------------------------------------------------
class SelectRespawnButtonHandler : SCR_ButtonHandler
{
    protected TeamRespawnMenu m_Menu;
    protected int m_RespawnEntityID;

    void SelectRespawnButtonHandler(TeamRespawnMenu menu, int respawnEntityID)
    {
        m_Menu = menu;
        m_RespawnEntityID = respawnEntityID;
    }

    override bool OnClick(Widget w)
    {
        if (m_Menu)
        {
            m_Menu.OnSelectRespawnPoint(m_RespawnEntityID);
        }
        return true;
    }
}