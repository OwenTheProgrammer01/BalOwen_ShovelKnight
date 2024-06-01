#pragma once
#include "BaseGame.h"
#include "Level.h"
#include "Camera.h"
#include "HUD.h"
#include "Player.h"
#include "BubbleManager.h"
#include "DirtBlockManager.h"
#include "SpikesAndFallPitsManager.h"
#include "PlatformManager.h"
#include "DirtPileManager.h"
#include "BeetoManager.h"
#include "SoundStream.h"

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:
	// DATA MEMBERS
	Rectf m_Window;

	Level m_Level;
	Player m_Player;
	Camera m_Camera;
	HUD m_HUD;
	BubbleManager m_BubbleManager;
	DirtBlockManager m_DirtBlockManager;
	SpikesAndFallPitsManager m_SpikesAndFallPitsManager;
	PlatformManager m_PlatformManager;
	DirtPileManager m_DirtPileManager;
	BeetoManager m_BeetoManager;
	SoundStream m_ThemeSong;

	bool m_IsGamePaused;

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
	void AddBubbles();
	void AddDirtBlocks();
	void AddSpikesAndFallPits();
	void AddPlatforms();
	void AddDirtPiles();
	void AddBeetos();
	void DoCollisions(float elapsedSec);
	void PrintControls() const;
	void ShowMenu() const;
};