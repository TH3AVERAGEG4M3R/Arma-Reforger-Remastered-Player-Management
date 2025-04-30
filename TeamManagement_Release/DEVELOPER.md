# ARMA Reforger Team Management System - Developer Guide

This document provides technical details about the Team Management System for developers who want to understand, modify, or extend the system.

## Architecture Overview

The Team Management System follows a client-server architecture with these key components:

### Core Components

1. **TeamManager**: Singleton class that manages all team operations centrally.
   - Location: `Scripts/Game/TeamManagement/TeamManager.c`
   - Responsibilities: Team creation, joining, leaving, invitation management

2. **TeamNetworkComponent**: Handles network synchronization for multiplayer.
   - Location: `Scripts/Game/TeamManagement/TeamNetworkComponent.c`
   - Responsibilities: RPC handling, data synchronization

3. **TeamPlayerComponent**: Component attached to player entities.
   - Location: `Scripts/Game/TeamManagement/TeamPlayerComponent.c`
   - Responsibilities: Player-specific team operations

4. **TeamManagementModule**: World module that initializes the system.
   - Location: `Worlds/TeamManagementModule.c`
   - Responsibilities: System initialization, keyboard handling

### Data Classes

1. **TeamMember**: Represents a player in a team.
   - Location: `Scripts/Game/TeamManagement/TeamMember.c`
   - Stores player ID, name, leader status

2. **TeamInvitation**: Represents a team invitation.
   - Location: `Scripts/Game/TeamManagement/TeamInvitation.c`
   - Stores invitation data, sender, receiver, expiration

### UI Components

1. **TeamManagementMenu**: Main UI for team management.
   - Location: `Scripts/Game/TeamManagement/TeamManagementMenu.c`
   - UI Layout: `UI/layouts/TeamManagement/TeamManagementMenu.layout`

2. **TeamInvitationPopup**: UI for invitation responses.
   - Location: `Scripts/Game/TeamManagement/TeamInvitationPopup.c`
   - UI Layout: `UI/layouts/TeamManagement/TeamInvitationPopup.layout`

## Network Synchronization

The system uses ARMA Reforger's RPC (Remote Procedure Call) system for network operations:

### RPC Handlers

1. **Create Team**: `RPC_CreateTeam`
2. **Join Team**: `RPC_JoinTeam`
3. **Leave Team**: `RPC_LeaveTeam`
4. **Send Invitation**: `RPC_SendInvitation`
5. **Accept Invitation**: `RPC_AcceptInvitation`
6. **Decline Invitation**: `RPC_DeclineInvitation`
7. **Sync Team Data**: `RPC_SyncTeamData`

### Data Flow

1. Client initiates an action (e.g., create team)
2. TeamManager routes request to TeamNetworkComponent in multiplayer
3. TeamNetworkComponent sends RPC to server
4. Server processes request and updates its TeamManager state
5. Server broadcasts changes to other clients
6. Clients update their local TeamManager state

### Synchronization Optimization

- Periodic sync for newly connected players
- Targeted RPCs to minimize network traffic
- Server authoritative model to prevent cheating

## Extending the System

### Adding New Team Features

1. Add new methods to TeamManager
2. Create corresponding RPC handlers in TeamNetworkComponent
3. Add UI elements to TeamManagementMenu if needed

### Custom Team Attributes

To add custom team attributes (e.g., team color, emblem):

1. Modify TeamMember or create a new TeamAttributes class
2. Update TeamManager to store and manage these attributes
3. Add serialization to TeamNetworkComponent's sync methods
4. Update UI to display/edit these attributes

### Integration with Other Systems

To integrate with other systems (e.g., squad mechanics, mission system):

1. Use TeamManager's public API to query team information
2. Subscribe to team events if implemented
3. Consider adding callback hooks to TeamManager

## Debugging

The system includes extensive debug logging:

1. Check console for "TeamManagementModule", "TeamManager", or "TeamNetworkComponent" prefixed logs
2. Enable verbose logging in config.cpp if needed
3. Use RplComponent logs to trace network issues

## Performance Considerations

1. Team operations are lightweight but should not be called every frame
2. Network synchronization is optimized but consider impact on large servers
3. UI updates are throttled to reduce performance impact

## Configuration Options

Key configurable options in TeamManager:

1. `MAX_TEAM_SIZE`: Maximum number of players in a team
2. `INVITATION_CLEANUP_INTERVAL`: How often to clean up expired invitations
3. `NETWORK_SYNC_INTERVAL`: How often to sync team data