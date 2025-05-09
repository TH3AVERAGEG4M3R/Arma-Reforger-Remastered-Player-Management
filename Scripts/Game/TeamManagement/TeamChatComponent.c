/**
 * @brief Team Chat Component for handling team-specific messaging
 */
class TeamChatComponentClass : ScriptComponentClass
{
}

//------------------------------------------------------------------------------------------------
/*!
    Component for handling team chat functionality
*/
class TeamChatComponent : ScriptComponent
{
    // Maximum number of chat messages to store in history
    protected const int MAX_CHAT_HISTORY = 50;
    
    // Maximum character length of a chat message
    protected const int MAX_MESSAGE_LENGTH = 128;
    
    // Time in seconds that a chat message remains visible
    protected const float MESSAGE_DISPLAY_TIME = 10.0;
    
    // Reference to team manager
    protected ref TeamManager m_TeamManager;
    
    // Reference to chat message history (cached locally)
    protected ref array<ref TeamChatMessage> m_ChatHistory = new array<ref TeamChatMessage>();
    
    // Network component for multiplayer support
    protected ref TeamNetworkComponent m_NetworkComponent;
    
    // Chat UI Widget
    protected ref Widget m_ChatWidget;
    
    // Input widget for typing messages
    protected ref EditBoxWidget m_InputBox;
    
    // Chat message display widget
    protected ref TextListboxWidget m_ChatDisplay;
    
    // Is the chat input currently active
    protected bool m_InputActive = false;
    
    // Player entity this component is attached to
    protected IEntity m_PlayerEntity;
    
    // Current team ID
    protected int m_CurrentTeamID = 0;
    
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
            
        // Get network component if in multiplayer
        if (GetGame().IsMultiplayer())
        {
            m_NetworkComponent = TeamNetworkComponent.GetInstance();
        }
        
        // Register input for opening chat
        RegisterChatInputs();
        
        // Create and configure UI
        CreateChatUI();
        
        // Get current team ID
        UpdateTeamID();
        
        // Register for team change events
        if (m_TeamManager)
            m_TeamManager.GetOnTeamChanged().Insert(OnTeamChanged);
    }
    
    //------------------------------------------------------------------------------------------------
    void ~TeamChatComponent()
    {
        // Unregister from team change events
        if (m_TeamManager)
            m_TeamManager.GetOnTeamChanged().Remove(OnTeamChanged);
            
        // Unregister input handlers
        UnregisterInputs();
        
        // Clean up UI
        if (m_ChatWidget)
        {
            m_ChatWidget.RemoveFromHierarchy();
            m_ChatWidget = null;
        }
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Update the team ID when team changes
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
        
        // Notify player about team chat availability
        if (newTeamID > 0)
        {
            NotifyPlayer("Team chat available. Press T to open team management or Y to open team chat");
        }
        else
        {
            NotifyPlayer("You have left the team. Team chat is no longer available.");
        }
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Update the current team ID
     */
    protected void UpdateTeamID()
    {
        if (!m_TeamManager || !m_PlayerEntity)
            return;
            
        string playerID = GetPlayerIdentity(m_PlayerEntity);
        m_CurrentTeamID = m_TeamManager.GetPlayerTeam(playerID);
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Register input handlers for chat
     */
    protected void RegisterChatInputs()
    {
        // Only register inputs for the local player
        PlayerController playerController = PlayerController.Cast(m_PlayerEntity.GetController());
        if (!playerController || !playerController.IsLocalPlayer())
            return;
            
        // Get the input manager
        InputManager inputManager = GetGame().GetInputManager();
        if (!inputManager)
            return;
            
        // Register for the Team Chat key binding (Y)
        inputManager.AddActionListener("TeamManagement.OpenTeamChat", EActionTrigger.DOWN, OpenTeamChat);
        
        // Register for the Close UI key binding (Escape)
        inputManager.AddActionListener("MenuBack", EActionTrigger.DOWN, CloseTeamChat);
        
        Print("Team Chat key bindings registered for player: " + GetPlayerName());
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Unregister input handlers
     */
    protected void UnregisterInputs()
    {
        InputManager inputManager = GetGame().GetInputManager();
        if (!inputManager)
            return;
            
        inputManager.RemoveActionListener("TeamManagement.OpenTeamChat", EActionTrigger.DOWN, OpenTeamChat);
        inputManager.RemoveActionListener("MenuBack", EActionTrigger.DOWN, CloseTeamChat);
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Handle opening team chat (Y key)
     * @param action The action context
     * @return True if handled, false otherwise
     */
    protected bool OpenTeamChat(Class action)
    {
        // Only continue for local player
        PlayerController playerController = PlayerController.Cast(m_PlayerEntity.GetController());
        if (!playerController || !playerController.IsLocalPlayer())
            return false;
            
        // Check if player is in a team
        if (m_CurrentTeamID <= 0)
        {
            NotifyPlayer("You are not in a team. Join a team to use team chat.");
            return true;
        }
            
        // Toggle chat input visibility
        ToggleChatInput();
        
        return true;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Handle closing team chat (Escape key)
     * @param action The action context
     * @return True if handled, false otherwise
     */
    protected bool CloseTeamChat(Class action)
    {
        // Only handle if chat input is active
        if (!m_InputActive)
            return false;
            
        // Hide chat input
        HideChatInput();
        
        return true;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Toggle chat input visibility
     */
    protected void ToggleChatInput()
    {
        if (m_InputActive)
            HideChatInput();
        else
            ShowChatInput();
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Show chat input
     */
    protected void ShowChatInput()
    {
        if (!m_ChatWidget || !m_InputBox)
            return;
            
        // Show input box
        m_InputBox.SetVisible(true);
        m_InputBox.SetText("");
        m_InputBox.SetFocus(true);
        m_InputActive = true;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Hide chat input
     */
    protected void HideChatInput()
    {
        if (!m_ChatWidget || !m_InputBox)
            return;
            
        // Hide input box
        m_InputBox.SetVisible(false);
        m_InputBox.SetFocus(false);
        m_InputActive = false;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Create and configure chat UI
     */
    protected void CreateChatUI()
    {
        // Only create UI for local player
        PlayerController playerController = PlayerController.Cast(m_PlayerEntity.GetController());
        if (!playerController || !playerController.IsLocalPlayer())
            return;
            
        // Create chat widget layout
        m_ChatWidget = GetGame().GetWorkspace().CreateWidgets("UI/layouts/TeamManagement/TeamChatWidget.layout");
        if (!m_ChatWidget)
        {
            Print("ERROR: Failed to create team chat widget!");
            return;
        }
        
        // Get child widgets
        m_ChatDisplay = TextListboxWidget.Cast(m_ChatWidget.FindAnyWidget("ChatDisplay"));
        m_InputBox = EditBoxWidget.Cast(m_ChatWidget.FindAnyWidget("InputBox"));
        
        if (!m_ChatDisplay || !m_InputBox)
        {
            Print("ERROR: Could not find all required chat widgets!");
            return;
        }
        
        // Configure input box
        m_InputBox.SetVisible(false);
        m_InputBox.SetText("");
        m_InputBox.SetHandler(this);
        
        // Handle Enter key to send message
        m_InputBox.SetEnterHandler(this, "OnEnterPressed");
        
        // Display chat widget (messages are always visible, input only when active)
        m_ChatWidget.SetVisible(true);
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Handle Enter key in chat input
     * @return True if handled
     */
    bool OnEnterPressed()
    {
        // Get message text
        string messageText = m_InputBox.GetText();
        
        // Trim and validate message
        messageText = messageText.Trim();
        if (messageText != "")
        {
            // Limit message length
            if (messageText.Length() > MAX_MESSAGE_LENGTH)
                messageText = messageText.Substring(0, MAX_MESSAGE_LENGTH);
                
            // Send the message
            SendTeamChatMessage(messageText);
        }
        
        // Hide input box
        HideChatInput();
        
        return true;
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Send a team chat message
     * @param messageText The text of the message
     */
    void SendTeamChatMessage(string messageText)
    {
        if (m_CurrentTeamID <= 0)
        {
            NotifyPlayer("You are not in a team. Join a team to use team chat.");
            return;
        }
        
        // Format the message
        string playerName = GetPlayerName();
        
        // In multiplayer, send through network component
        if (GetGame().IsMultiplayer() && m_NetworkComponent)
        {
            m_NetworkComponent.SendTeamChatMessage(m_PlayerEntity, messageText);
            return;
        }
        
        // In single player or server, create and distribute the message
        ref TeamChatMessage message = new TeamChatMessage(m_CurrentTeamID, GetPlayerIdentity(m_PlayerEntity), playerName, messageText);
        DistributeTeamChatMessage(message);
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Distribute a team chat message to appropriate players
     * @param message The message to distribute
     */
    void DistributeTeamChatMessage(TeamChatMessage message)
    {
        if (!message)
            return;
            
        // Add to local chat history
        AddChatMessageToHistory(message);
        
        // Display the message
        DisplayChatMessage(message);
        
        // In single player, server, or host mode, distribute to all team members
        if (!GetGame().IsMultiplayer() || GetGame().IsServer())
        {
            // Get all players in the team
            array<ref TeamMember> teamMembers = m_TeamManager.GetTeamMembers(message.GetTeamID());
            if (!teamMembers)
                return;
                
            // Distribute to all team members except the sender
            foreach (ref TeamMember member : teamMembers)
            {
                // Skip the sender (already displayed locally)
                if (member.GetPlayerID() == message.GetSenderID())
                    continue;
                    
                // Get the player entity and send the message
                IEntity playerEntity = GetGame().GetPlayerManager().GetPlayerByPlayerId(member.GetPlayerID());
                if (playerEntity)
                {
                    TeamChatComponent chatComponent = TeamChatComponent.Cast(playerEntity.FindComponent(TeamChatComponent));
                    if (chatComponent)
                    {
                        chatComponent.ReceiveTeamChatMessage(message);
                    }
                }
            }
        }
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Receive a team chat message
     * @param message The message to receive
     */
    void ReceiveTeamChatMessage(TeamChatMessage message)
    {
        if (!message)
            return;
            
        // Verify player is in the same team as the message
        if (m_CurrentTeamID != message.GetTeamID())
            return;
            
        // Add to local chat history
        AddChatMessageToHistory(message);
        
        // Display the message
        DisplayChatMessage(message);
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Add a chat message to history
     * @param message The message to add
     */
    protected void AddChatMessageToHistory(TeamChatMessage message)
    {
        if (!message)
            return;
            
        // Add to history
        m_ChatHistory.Insert(message);
        
        // Trim history if too large
        while (m_ChatHistory.Count() > MAX_CHAT_HISTORY)
        {
            m_ChatHistory.Remove(0);
        }
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Display a chat message in the UI
     * @param message The message to display
     */
    protected void DisplayChatMessage(TeamChatMessage message)
    {
        if (!message || !m_ChatDisplay)
            return;
            
        // Format the message for display
        string displayText = "[Team] " + message.GetSenderName() + ": " + message.GetMessageText();
        
        // Add to chat display
        m_ChatDisplay.AddItem(displayText);
        
        // Scroll to the bottom
        m_ChatDisplay.EnsureVisible(m_ChatDisplay.GetItemCount() - 1);
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
    protected string GetPlayerName()
    {
        if (!m_PlayerEntity)
            return "Unknown";
            
        PlayerController pc = PlayerController.Cast(m_PlayerEntity.GetController());
        if (!pc)
            return "Unknown";
            
        return pc.GetPlayerName();
    }
    
    //------------------------------------------------------------------------------------------------
    /**
     * @brief Send a notification to the player
     * @param message The message to send
     */
    protected void NotifyPlayer(string message)
    {
        // Use game's notification system
        PlayerController pc = PlayerController.Cast(m_PlayerEntity.GetController());
        if (!pc)
            return;
        
        // Show notification
        SCR_NotificationSystem.SendNotification(pc, message);
    }
}