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
        version = "1.0.0";
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
    
    // Default player entity
    class BasePlayer;
    class PlayerBase: BasePlayer
    {
        components[] += {"TeamPlayerComponent"};
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
    };
};
