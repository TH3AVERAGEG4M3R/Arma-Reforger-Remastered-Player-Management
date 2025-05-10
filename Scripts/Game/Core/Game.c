// Game.c - Core game class for ARMA Reforger
// This class provides access to the game world and other global systems

#include "World.c"

/**
 * @brief Singleton class representing the game
 */
class Game
{
    // Singleton instance
    private static ref Game s_Instance;
    
    // Game world
    protected ref World m_World;
    
    // Private constructor (use GetInstance())
    private void Game()
    {
        m_World = new World();
    }
    
    /**
     * @brief Get the singleton instance
     * @return The singleton instance
     */
    static Game GetInstance()
    {
        if (!s_Instance)
            s_Instance = new Game();
            
        return s_Instance;
    }
    
    /**
     * @brief Get the game world
     * @return The game world
     */
    World GetWorld()
    {
        return m_World;
    }
}

// Convenience function for getting the game instance
Game GetGame()
{
    return Game.GetInstance();
}