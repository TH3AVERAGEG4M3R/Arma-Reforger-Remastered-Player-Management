# ARMA Reforger Team Management System

A comprehensive team management system for ARMA Reforger with full multiplayer support.

## Features

- Create and manage teams in ARMA Reforger
- Join existing teams or leave your current team
- Send and receive team invitations
- Full multiplayer support with proper network synchronization
- User-friendly interface for all team operations
- Keyboard shortcut (default: T) to open the team management menu

## Technical Implementation

### Core Components

- **TeamManager**: Singleton that manages all team operations and data
- **TeamMember**: Class representing a player in a team
- **TeamInvitation**: Class for handling team invitations
- **TeamNetworkComponent**: Handles network synchronization for multiplayer
- **TeamPlayerComponent**: Attaches to player entities and provides team functionality

### Networking

The team management system is designed from the ground up with multiplayer in mind. All team operations (create, join, leave, invite) are properly synchronized across the network using:

- RPC (Remote Procedure Call) system for operations
- Proper client/server architecture
- Periodic team data synchronization
- Optimized data transfer

### User Interface

- **TeamManagementMenu**: Main UI for managing teams
- **TeamInvitationPopup**: UI for receiving and responding to invitations

## Installation

1. Subscribe to the mod on the ARMA Reforger Workshop
2. Enable the mod in the ARMA Reforger launcher
3. Start the game and press T to open the team management menu

## Usage

### Creating a Team

1. Press T to open the team management menu
2. Click "Create Team" to create a new team
3. You will be automatically assigned as the team leader

### Inviting Players

1. Press T to open the team management menu
2. Find the player you want to invite in the player list
3. Click "Invite" next to their name
4. They will receive an invitation popup

### Accepting/Declining Invitations

1. When you receive an invitation, a popup will appear
2. Click "Accept" to join the team or "Decline" to reject the invitation

### Leaving a Team

1. Press T to open the team management menu
2. Click "Leave Team" to leave your current team
3. If you are the team leader, leadership will pass to another member

## Configuration

The default key binding (T) can be changed in the game's control settings menu.

## Developer Information

This mod is built using the ARMA Reforger scripting system and follows best practices for mod development. The code is structured in a modular way to make it easy to integrate with other mods.

Key files:
- `Scripts/Game/TeamManagement/TeamManager.c`: Core team management logic
- `Scripts/Game/TeamManagement/TeamNetworkComponent.c`: Network synchronization
- `Scripts/Game/TeamManagement/TeamPlayerComponent.c`: Player-attached component
- `UI/layouts/TeamManagement/TeamManagementMenu.layout`: Main UI layout

## License

Created by ARMA Team Management (2025)