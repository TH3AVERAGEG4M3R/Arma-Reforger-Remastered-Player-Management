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
            "scripts"
        };
    };
};

class CfgMods
{
    class TeamManagementMod
    {
        name = "Team Management System";
        author = "Your Name";
        version = "1.0";
        description = "Team management system with UI for joining, leaving, and inviting players to teams";
        picture = "";
        actionName = "GitHub";
        action = "";
        dir = "TeamManagement";
        authorID = "";
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
        uiDescription = "Team management system with UI for joining, leaving, and inviting players to teams";
        priority = 1;
        categoryName = "Game";
        class OpenTeamMenu
        {
            displayName = "Open Team Menu";
            defaultKey = "KeyT";
        };
    };
};
