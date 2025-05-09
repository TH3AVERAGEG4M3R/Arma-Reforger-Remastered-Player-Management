# Changelog

## Version 1.2.0 (2025-05-09)

### Added
- Team chat functionality with dedicated UI
- Team-only messaging system with player name display
- Network synchronization for chat messages
- Keyboard shortcut (Y) to open team chat
- Chat message history with scrollable display
- Message length limitations for network efficiency
- Automatic team message filtering based on membership

### Technical Implementation
- TeamChatComponent for handling team chat functionality
- TeamChatMessage class for message encapsulation
- Custom TeamChatWidget layout for chat interface
- Network RPC handlers for secure message transmission
- Team-based message filtering system
- Event-based chat update system
- Integration with team membership events

## Version 1.1.0 (2025-05-09)

### Added
- Team visualization system for map and HUD
- Unique map icons for team leaders and team members
- Color-coded team indicators for easy identification
- Automatic visibility based on team membership
- Enhanced team events system for live visual updates
- Team manager events for synchronizing visual changes
- HUD icon class for consistent display of team members

### Technical Implementation
- SCR_HUDManagerComponent for managing HUD elements
- SCR_MapEntity for handling map markers
- TeamVisualsComponent for player-attached visuals
- ScriptInvoker system for team change event handling
- Optimized update logic to minimize performance impact
- Custom textures for map and HUD indicators

## Version 1.0.5 (2025-05-05)

### Added
- Vehicle locking system for team-restricted access
- Automated team member access to locked team vehicles
- Purchasable team respawn flagpoles
- Team-specific respawn functionality
- 100-meter proximity limit between team respawn points
- Limit of 1 active respawn point per team
- 5-minute (300 seconds) cooldown on respawn usage
- Respawn cooldown UI with timer display

### Technical Implementation
- TeamVehicleComponent for vehicle functionality
- TeamRespawnComponent for respawn management
- TeamFlagpole entity for respawn points
- Cooldown tracking system for respawn points
- Proximity detection for flagpole placement

## Version 1.0.0 (2025-04-30)

### Added
- Initial release of Team Management System
- Core team management functionality (create, join, leave teams)
- Team invitation system with accept/decline functionality
- Comprehensive network synchronization for multiplayer
- Team player component for player-specific functionality
- UI for team management and invitation responses
- Keyboard shortcut (T) to open team management menu

### Technical Implementation
- TeamManager singleton for centralized team operations
- TeamNetworkComponent for multiplayer synchronization
- TeamPlayerComponent for player attachment
- RPC handlers for all network operations
- Periodic team data synchronization
- Optimized data transfer to minimize network traffic