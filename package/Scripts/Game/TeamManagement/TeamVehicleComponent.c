/**
 * @brief Component for handling team-based vehicle locking and access
 */
class TeamVehicleComponent : GenericComponent
{
    protected ref TeamManager m_TeamManager;
    protected bool m_IsInitialized;
    protected bool m_IsLocked;
    protected int m_OwnerTeamID;
    protected string m_OwnerPlayerID;
    
    /**
     * @brief Initialize component
     */
    void OnPostInit(IEntity owner)
    {
        super.OnPostInit(owner);
        
        // Get team manager instance
        m_TeamManager = TeamManager.GetInstance();
        m_IsInitialized = true;
        m_IsLocked = false;
        m_OwnerTeamID = 0;
        m_OwnerPlayerID = "";
        
        Print("TeamVehicleComponent initialized for vehicle: " + owner.GetName());
    }
    
    /**
     * @brief Check if the vehicle is locked
     * @return True if locked, false otherwise
     */
    bool IsLocked()
    {
        return m_IsLocked;
    }
    
    /**
     * @brief Get the team ID that owns (locked) this vehicle
     * @return The team ID, or 0 if not locked by a team
     */
    int GetOwnerTeamID()
    {
        return m_OwnerTeamID;
    }
    
    /**
     * @brief Get the player ID that locked this vehicle
     * @return The player ID, or empty string if not locked
     */
    string GetOwnerPlayerID()
    {
        return m_OwnerPlayerID;
    }
    
    /**
     * @brief Lock the vehicle for team access
     * @param player The player locking the vehicle
     * @return True if successful, false otherwise
     */
    bool LockVehicle(IEntity player)
    {
        if (!m_IsInitialized || !m_TeamManager)
            return false;
        
        IEntity owner = GetOwner();
        if (!owner)
            return false;
        
        // Get player information
        string playerID = GetPlayerIdentity(player);
        int teamID = m_TeamManager.GetPlayerTeam(playerID);
        
        // Player must be in a team to lock a vehicle
        if (teamID <= 0)
            return false;
        
        // Set vehicle as locked
        m_IsLocked = true;
        m_OwnerTeamID = teamID;
        m_OwnerPlayerID = playerID;
        
        // Update vehicle locked state
        SetVehicleLockState(true);
        
        // Notify player
        NotifyPlayer(player, "Vehicle locked. Only your team members can access it.");
        
        return true;
    }
    
    /**
     * @brief Unlock the vehicle
     * @param player The player unlocking the vehicle
     * @return True if successful, false otherwise
     */
    bool UnlockVehicle(IEntity player)
    {
        if (!m_IsInitialized)
            return false;
        
        IEntity owner = GetOwner();
        if (!owner)
            return false;
        
        // Get player information
        string playerID = GetPlayerIdentity(player);
        
        // Only the owner or a team member can unlock
        if (!CanAccessVehicle(player))
            return false;
        
        // Set vehicle as unlocked
        m_IsLocked = false;
        m_OwnerTeamID = 0;
        m_OwnerPlayerID = "";
        
        // Update vehicle locked state
        SetVehicleLockState(false);
        
        // Notify player
        NotifyPlayer(player, "Vehicle unlocked. Anyone can access it now.");
        
        return true;
    }
    
    /**
     * @brief Check if a player can access this vehicle
     * @param player The player trying to access the vehicle
     * @return True if access is allowed, false otherwise
     */
    bool CanAccessVehicle(IEntity player)
    {
        if (!m_IsInitialized)
            return true; // Default to allowing access if not initialized
        
        if (!m_IsLocked)
            return true; // Vehicle is not locked, anyone can access
        
        // Get player information
        string playerID = GetPlayerIdentity(player);
        
        // The owner can always access
        if (playerID == m_OwnerPlayerID)
            return true;
        
        // Check if player is in the same team as the owner
        int playerTeamID = m_TeamManager.GetPlayerTeam(playerID);
        if (playerTeamID > 0 && playerTeamID == m_OwnerTeamID)
            return true;
        
        return false;
    }
    
    /**
     * @brief Set the physical lock state of the vehicle
     * @param isLocked Whether the vehicle should be locked
     */
    protected void SetVehicleLockState(bool isLocked)
    {
        IEntity owner = GetOwner();
        if (!owner)
            return;
            
        // Get vehicle component that handles locking
        BaseVehicleComponent vehicleComponent = BaseVehicleComponent.Cast(owner.FindComponent(BaseVehicleComponent));
        if (vehicleComponent)
        {
            vehicleComponent.SetLocked(isLocked);
            Print("Vehicle " + owner.GetName() + " lock state set to: " + isLocked);
        }
    }
    
    /**
     * @brief Get the player's identity string
     * @param player The player entity
     * @return The player's identity string
     */
    protected string GetPlayerIdentity(IEntity player)
    {
        if (!player)
            return "";
        
        PlayerController pc = PlayerController.Cast(player.GetController());
        if (!pc)
            return "";
        
        return pc.GetPlayerId().ToString();
    }
    
    /**
     * @brief Send a notification to a player
     * @param player The player to notify
     * @param message The message to send
     */
    protected void NotifyPlayer(IEntity player, string message)
    {
        if (!player)
            return;
            
        // Use HUD notification if available
        // For now, just print to console
        Print("NOTIFY: " + message);
    }
}