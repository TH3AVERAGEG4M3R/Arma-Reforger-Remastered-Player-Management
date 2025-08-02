# ARMA Reforger Team Management Mod

A comprehensive team management system for ARMA Reforger that enhances player coordination and team dynamics through advanced interaction tools and intelligent management systems.

## 🚀 Features

### Core Team Management
- **Team Creation & Joining**: Players can create new teams or join existing ones
- **Team Invitations**: Send and receive team invitations with accept/decline functionality
- **Team Leadership**: Designated team leaders with additional privileges
- **Real-time Synchronization**: Multiplayer support with network-based team data sync

### Advanced Systems
- **Vehicle Access Control**: Team-based vehicle locking system
- **Team Respawn Points**: Purchasable flagpole assets for strategic respawn locations
- **Visual Indicators**: Team member identification on map and HUD
- **Team Chat**: Dedicated communication channel for team members
- **Cooldown Management**: Balanced respawn system with 5-minute cooldowns

### User Interface
- **Team Management Menu**: Accessible via "T" key for team operations
- **Respawn Menu**: Automatic display on player death with available respawn points
- **Team Chat Interface**: Quick access via "Y" key for team communication
- **Admin Controls**: Server administrators can configure costs and restrictions

## 🛠️ Technical Architecture

### Framework
- **ARMA Reforger Modding Environment**: Built using ScriptedUnits framework
- **Custom UI Components**: Native widget implementation for seamless integration
- **Event-driven Architecture**: Responsive team management logic
- **Network Communication**: Custom RPC system for multiplayer synchronization

### Core Components
- `TeamManager.c` - Singleton pattern for centralized team operations
- `TeamNetworkComponent.c` - Network communication and RPC handling
- `TeamPlayerComponent.c` - Individual player team management
- `TeamFlagpole.c` - Respawn point management and placement
- `TeamChatComponent.c` - Team communication system

### Data Management
- **EntityID-based References**: Memory-safe entity handling
- **Team Data Structures**: Efficient team member and invitation tracking
- **Network Serialization**: Custom binary data handling for RPCs

## 📦 Installation

### Prerequisites
- ARMA Reforger (latest version)
- ARMA Reforger Tools (for development)

### For Players
1. Subscribe to the mod on the Steam Workshop
2. Launch ARMA Reforger
3. Enable the mod in the mod list
4. Join a server running the Team Management mod

### For Server Administrators
1. Download the mod files
2. Extract to your server's mod directory
3. Add the mod to your server configuration
4. Configure team settings in the mod configuration file
5. Restart the server

### For Developers
1. Clone this repository
2. Open the project in ARMA Reforger Tools
3. Build the mod using the provided build scripts
4. Test in the Reforger environment

## 🎮 Usage Guide

### Basic Team Operations
- **Create Team**: Open team menu (T) and click "Create Team"
- **Join Team**: Accept an invitation or request to join an existing team
- **Leave Team**: Use the team menu to leave your current team
- **Invite Players**: Team leaders can send invitations to other players

### Respawn System
- **Purchase Flagpoles**: Team leaders can buy respawn points for 1000 credits
- **Select Respawn Point**: Choose from available team respawn locations
- **Cooldown Management**: Wait 5 minutes between respawns at the same location

### Team Communication
- **Team Chat**: Press Y to open team chat interface
- **Quick Messages**: Use predefined messages for faster communication
- **Voice Integration**: Compatible with external voice communication systems

### Vehicle Management
- **Lock Vehicles**: Team members can lock vehicles for team-only access
- **Unlock Access**: Remove vehicle restrictions when needed
- **Team Sharing**: Automatic access for all team members

## 🔧 Configuration

### Server Configuration
```cpp
// config.cpp example settings
class TeamManagementSettings
{
    flagpoleCost = 1000;           // Cost to purchase respawn points
    maxTeamSize = 8;               // Maximum players per team
    respawnCooldown = 300;         // Cooldown in seconds (5 minutes)
    enableVehicleLocking = true;   // Allow team vehicle locking
    enableTeamChat = true;         // Enable team chat functionality
};
```

### Key Bindings
- `T` - Open Team Management Menu
- `Y` - Open Team Chat
- `Ctrl+T` - Quick Team Actions
- `Ctrl+Y` - Toggle Team Chat Window

## 🤝 Contributing

We welcome contributions to improve the Team Management mod!

### Development Setup
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Make your changes following our coding standards
4. Test thoroughly in the ARMA Reforger environment
5. Commit your changes (`git commit -m 'Add amazing feature'`)
6. Push to the branch (`git push origin feature/amazing-feature`)
7. Open a Pull Request

### Coding Standards
- Follow ARMA Reforger scripting conventions
- Use EntityID instead of direct entity references
- Document all public methods with JSDoc-style comments
- Include error handling and validation
- Test multiplayer functionality thoroughly

### Bug Reports
Please use the GitHub Issues tab to report bugs. Include:
- ARMA Reforger version
- Mod version
- Steps to reproduce
- Expected vs actual behavior
- Screenshots/videos if applicable

## 📝 Changelog

### Version 1.2.0 (Current)
- ✅ Added team chat functionality with dedicated UI
- ✅ Implemented EntityID-based memory management
- ✅ Enhanced network communication stability
- ✅ Improved UI responsiveness and error handling
- ✅ Fixed button handler compatibility issues

### Version 1.1.0
- ✅ Added vehicle locking system
- ✅ Implemented team respawn points
- ✅ Enhanced visual indicators for team members
- ✅ Improved network synchronization

### Version 1.0.0
- ✅ Initial release with basic team management
- ✅ Team creation, joining, and invitation system
- ✅ Multiplayer network support
- ✅ Basic UI implementation

## 🐛 Known Issues

- Minor UI scaling issues on ultrawide displays
- Occasional network desync in high-latency environments
- Flagpole placement restrictions in certain terrain types

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- ARMA Reforger development team for the modding framework
- Community contributors and testers
- Beta testers who provided valuable feedback

## 📞 Support

- **Discord**: Join our community server for real-time support
- **GitHub Issues**: Report bugs and request features
- **Steam Workshop**: Rate and review the mod
- **Documentation**: Check the `/docs` folder for detailed guides

## 🔗 Links

- [Steam Workshop Page](https://steamcommunity.com/sharedfiles/filedetails/?id=WORKSHOP_ID)
- [Official Documentation](docs/README.md)
- [Community Discord](https://discord.gg/DISCORD_INVITE)
- [Bug Tracker](https://github.com/USERNAME/arma-reforger-team-management/issues)

---

**Made with ❤️ for the ARMA Reforger community**