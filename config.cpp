/**
 * @brief Configuration file for the Team Management mod for ARMA Reforger
 */
class CfgPatches
{
    class TeamManagementMod
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {
            "Engine", 
            "GameLib", 
            "scripts",
            "Network"
        };
        author = "ARMA Team Management";
        version = "1.2.0";
    };
};

class CfgMods
{
    class TeamManagementMod
    {
        name = "Team Management System";
        author = "ARMA Team Management";
        version = "1.0.0";
        description = "Comprehensive team management system with UI for creating, joining, leaving, and inviting players to teams with full multiplayer support";
        picture = "generated-icon.png";
        actionName = "GitHub";
        action = "";
        dir = "TeamManagement";
        authorID = "ARMA_TM";
        dependencies[] = {"Game"};
    };
};

class CfgVehicles
{
    class ScriptModule;
    class TeamManagementModule: ScriptModule
    {
        dependencies[] = {
            "World"
        };
    };
    
    // Player component for team management
    class ScriptedPlayerComponent;
    class TeamPlayerComponent: ScriptedPlayerComponent
    {
        componentNames[] = {};
    };
    
    // Team chat component for player
    class TeamChatComponent: ScriptedPlayerComponent
    {
        componentNames[] = {};
    };
    
    // Default player entity
    class BasePlayer;
    class PlayerBase: BasePlayer
    {
        components[] += {"TeamPlayerComponent", "TeamChatComponent"};
    };
    
    // Respawn flagpole entity
    class GenericEntity;
    class TeamFlagpole: GenericEntity
    {
        displayName = "Team Respawn Flagpole";
        descriptionShort = "Allows team members to respawn at this location";
        model = "TeamManagement/Models/Flagpole.emat";
        hiddenSelectionsTextures[] = {};
        physicsCategory = "item";
        
        class Hierarchy
        {
            components[] = {
                "RplComponent",
                "TeamRespawnComponent"
            };
        };
        
        class BaseComponentTypes
        {
            TeamRespawnComponentClass TeamRespawnComponent;
        };
    };
    
    // Vehicle component for team-based locking
    class GenericComponent;
    class TeamVehicleComponent: GenericComponent
    {
        componentNames[] = {};
    };
    
    // Respawn component for flagpole
    class TeamRespawnComponent: GenericComponent
    {
        componentNames[] = {};
    };
};

class CfgWorlds
{
    class DefaultWorld;
    class World: DefaultWorld
    {
        class ScriptModules
        {
            class TeamManagementModule
            {
                files[] = {"TeamManagement/Worlds/TeamManagementModule.c"};
            };
        };
        
        class ScriptComponents
        {
            // Network components
            class TeamNetworkComponentClass
            {
                files[] = {"TeamManagement/Scripts/Game/TeamManagement/TeamNetworkComponent.c"};
            };
            
            // Player components
            class TeamPlayerComponentClass
            {
                files[] = {"TeamManagement/Scripts/Game/TeamManagement/TeamPlayerComponent.c"};
            };
            
            // Core team management components
            class TeamManagerClass
            {
                files[] = {"TeamManagement/Scripts/Game/TeamManagement/TeamManager.c"};
            };
            
            class TeamMemberClass
            {
                files[] = {"TeamManagement/Scripts/Game/TeamManagement/TeamMember.c"};
            };
            
            class TeamInvitationClass
            {
                files[] = {"TeamManagement/Scripts/Game/TeamManagement/TeamInvitation.c"};
            };
            
            // UI components
            class TeamManagementMenuClass
            {
                files[] = {"TeamManagement/Scripts/Game/TeamManagement/TeamManagementMenu.c"};
            };
            
            class TeamInvitationPopupClass
            {
                files[] = {"TeamManagement/Scripts/Game/TeamManagement/TeamInvitationPopup.c"};
            };
            
            // Vehicle components
            class TeamVehicleComponentClass
            {
                files[] = {"TeamManagement/Scripts/Game/TeamManagement/TeamVehicleComponent.c"};
            };
            
            // Respawn components
            class TeamRespawnComponentClass
            {
                files[] = {"TeamManagement/Scripts/Game/TeamManagement/TeamRespawnComponent.c"};
            };
            
            class TeamFlagpoleClass
            {
                files[] = {"TeamManagement/Scripts/Game/TeamManagement/TeamFlagpole.c"};
            };
            
            class TeamRespawnMenuClass
            {
                files[] = {"TeamManagement/Scripts/Game/TeamManagement/TeamRespawnMenu.c"};
            };
            
            // Team chat components
            class TeamChatComponentClass
            {
                files[] = {"TeamManagement/Scripts/Game/TeamManagement/TeamChatComponent.c"};
            };
            
            class TeamChatMessageClass
            {
                files[] = {"TeamManagement/Scripts/Game/TeamManagement/TeamChatMessage.c"};
            };
        };
    };
};

class CfgWrapperUI
{
    class LayoutSettings
    {
        class TeamManagement
        {
            layoutPath = "TeamManagement/UI/layouts/TeamManagement";
        };
    };
    
    class WidgetClasses
    {
        // TeamManagementMenu
        class TeamManagementMenu
        {
            scriptClass = "TeamManagementMenu";
            scriptFile = "TeamManagement/Scripts/Game/TeamManagement/TeamManagementMenu.c";
        };
        
        // TeamInvitationPopup
        class TeamInvitationPopup
        {
            scriptClass = "TeamInvitationPopup";
            scriptFile = "TeamManagement/Scripts/Game/TeamManagement/TeamInvitationPopup.c";
        };
        
        // TeamRespawnMenu
        class TeamRespawnMenu
        {
            scriptClass = "TeamRespawnMenu";
            scriptFile = "TeamManagement/Scripts/Game/TeamManagement/TeamRespawnMenu.c";
        };
    };
};

class CfgKeyBinding
{
    class TeamManagement
    {
        name = "Team Management";
        uiName = "Team Management";
        uiDescription = "Comprehensive team management system with multiplayer support";
        priority = 1;
        categoryName = "Game";
        class OpenTeamMenu
        {
            displayName = "Open Team Menu";
            defaultKey = "KeyT";
            description = "Open the team management interface to create, join, or manage teams";
        };
        
        class OpenTeamChat
        {
            displayName = "Open Team Chat";
            defaultKey = "KeyY";
            description = "Open team chat to communicate with your team members";
        };
    };
};
