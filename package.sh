#!/bin/bash

# Script to package ARMA Reforger Team Management mod

echo "Packaging ARMA Reforger Team Management Mod..."

# Create TeamManagement release directory if it doesn't exist
mkdir -p ./TeamManagement_Release

# Clean release directory
rm -rf ./TeamManagement_Release/*

# Create proper directory structure for ARMA Reforger mod
echo "Creating directory structure..."
mkdir -p ./TeamManagement_Release/TeamManagement/Scripts/Game/TeamManagement
mkdir -p ./TeamManagement_Release/TeamManagement/UI/layouts/TeamManagement
mkdir -p ./TeamManagement_Release/TeamManagement/Worlds

# Copy the mod files with proper directory structure
echo "Copying mod files..."
cp -r ./Scripts/Game/TeamManagement/* ./TeamManagement_Release/TeamManagement/Scripts/Game/TeamManagement/
cp -r ./UI/layouts/TeamManagement/* ./TeamManagement_Release/TeamManagement/UI/layouts/TeamManagement/
cp -r ./Worlds/* ./TeamManagement_Release/TeamManagement/Worlds/
cp config.cpp ./TeamManagement_Release/TeamManagement/
cp generated-icon.png ./TeamManagement_Release/TeamManagement/

# Copy documentation files
cp README.md ./TeamManagement_Release/
cp Changelog.md ./TeamManagement_Release/
cp INSTALLATION.md ./TeamManagement_Release/
cp DEVELOPER.md ./TeamManagement_Release/
cp LICENSE ./TeamManagement_Release/

# Output message
echo "Package created: ./TeamManagement_Release"
echo ""
echo "======================="
echo "PACKAGING COMPLETE"
echo "======================="
echo ""
echo "The mod is now ready for distribution to ARMA Reforger Workshop!"
echo ""
echo "To install manually:"
echo "1. Copy the TeamManagement folder from TeamManagement_Release to your ARMA Reforger addons folder"
echo "2. Enable the mod in the ARMA Reforger launcher"
echo ""
echo "To upload to Workshop:"
echo "1. Open ARMA Reforger"
echo "2. Go to the Workshop tab"
echo "3. Click 'Create New'"
echo "4. Select the TeamManagement folder from TeamManagement_Release"
echo "5. Fill in the details and upload"