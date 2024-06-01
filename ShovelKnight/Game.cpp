#include "pch.h"
#include "Game.h"
#include <iostream>

Game::Game(const Window& window)
	: BaseGame{ window },
	m_Window{ 0, 0, window.width, window.height },
	m_Level{},
	m_Camera{ m_Window.width, m_Window.height },
	m_ThemeSong{ "Sounds/Level1Theme.mp3" },
	m_IsGamePaused{ false }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_ThemeSong.Play(true);
	m_Camera.Zoom(3.214f);
	m_Camera.SetLevelBoundaries(m_Level.GetBoundaries());
	AddBubbles();
	AddDirtBlocks();
	AddSpikesAndFallPits();
	AddPlatforms();
	AddDirtPiles();
	AddBeetos();
}

void Game::Cleanup()
{
}

void Game::Update(float elapsedSec)
{
	if (!m_IsGamePaused)
	{
		m_ThemeSong.Resume();

		// Update game objects
		m_Player.Update(elapsedSec, m_Level, m_PlatformManager, m_DirtBlockManager);
		m_Level.ChangeLevelPart(m_Player, elapsedSec);
		m_Camera.SetLevelBoundaries(m_Level.GetBoundaries());
		m_BubbleManager.Update(elapsedSec);
		m_DirtBlockManager.Update(elapsedSec);
		m_PlatformManager.Update(elapsedSec);
		m_DirtPileManager.Update(elapsedSec);
		m_BeetoManager.Update(elapsedSec);

		DoCollisions(elapsedSec);
	}
	else
	{
		m_ThemeSong.Pause();
	}
}

void Game::Draw() const
{
	ClearBackground();

	glPushMatrix();
	{
		m_Level.DrawBackground();
		m_Camera.Transform(m_Player.GetShape());
		m_Level.DrawMiddleGround();
		m_DirtPileManager.Draw();
		m_DirtBlockManager.Draw();
		m_BeetoManager.Draw();
		m_Player.Draw();
		m_Level.DrawForeground();
		//m_SpikesAndFallPitsManager.Draw(); // <---- DEBUG ONLY
		m_BubbleManager.Draw();
		m_PlatformManager.Draw();
	}
	glPopMatrix();
	m_HUD.Draw(m_Player.GetHealth());
	if (m_IsGamePaused)
	{
		ShowMenu();
	}
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch ( e.keysym.sym )
	{
	case SDLK_ESCAPE:
		m_IsGamePaused = !m_IsGamePaused;
		break;
	case SDLK_i:
		PrintControls();
	}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	// DEBUG
	// WORLD POSITION
	/*if (m_Player.GetShape().left + m_Player.GetShape().width / 2 < 640 / 3.214)
	{
		std::cout << "WorldPos: { " << e.x / 3.214 << ", " << e.y / 3.214 + 416 << " }\n";
	}
	else if (m_Player.GetShape().left + m_Player.GetShape().width / 2 > 6832 - 640 / 3.214)
	{
		std::cout << "WorldPos: { " << 6832 - (640 / 3.214) + (e.x - 640) / 3.214 << ", " << e.y / 3.214 + 416 << " }\n";
	}
	else
	{
		std::cout << "WorldPos: { " << (e.x - 640) / 3.214 + m_Player.GetShape().left + m_Player.GetShape().width / 2 << ", " << e.y / 3.214 + 416 << " }\n";
	}*/
	// --------------------
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::AddBubbles()
{
	m_BubbleManager.AddItem(Point2f{ 2224, 496 }, 96);
	m_BubbleManager.AddItem(Point2f{ 4248, 32 }, 48);
	m_BubbleManager.AddItem(Point2f{ 4576, 240 }, 48);
	m_BubbleManager.AddItem(Point2f{ 4640, 240 }, 48);
	m_BubbleManager.AddItem(Point2f{ 4832, 272 }, 80);
	m_BubbleManager.AddItem(Point2f{ 4896, 256 }, 64);
	m_BubbleManager.AddItem(Point2f{ 5392, 1104 }, 80);
}

void Game::AddDirtBlocks()
{
	m_DirtBlockManager.AddItem(Point2f{ 928, 512 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 1200, 512 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 1568, 480 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 1568, 512 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 1568, 544 }, true);
	
	m_DirtBlockManager.AddItem(Point2f{ 1728, 480 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 1824, 512 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 1824, 480 }, true);

	m_DirtBlockManager.AddItem(Point2f{ 2480, 688 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 2480, 656 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 2752, 656 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 2768, 656 }, true);

	m_DirtBlockManager.AddItem(Point2f{ 2864, 464 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 2880, 464 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 2864, 448 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 2880, 448 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 2864, 432 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 2880, 432 }, false);

	m_DirtBlockManager.AddItem(Point2f{ 3168, 224 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 3168, 256 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 3168, 288 }, true);

	m_DirtBlockManager.AddItem(Point2f{ 2960, 32 }, false);

	m_DirtBlockManager.AddItem(Point2f{ 3392, 96 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 3424, 96 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 3456, 96 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 3488, 64 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 3488, 32 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 3520, 64 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 3520, 32 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 3680, 32 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3696, 32 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3696, 48 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3712, 32 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 3712, 64 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3728, 64 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3728, 80 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3744, 64 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 3744, 96 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3760, 96 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3760, 112 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3776, 64 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3776, 80 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3776, 96 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3776, 112 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3792, 32 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3792, 48 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3792, 64 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3792, 80 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 3792, 112 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3808, 32 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 3808, 64 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3808, 112 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3824, 64 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3824, 80 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3824, 96 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3824, 112 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3840, 32 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3840, 48 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3840, 64 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3840, 96 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 3856, 32 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3856, 48 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3856, 64 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3872, 32 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 3872, 64 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3872, 80 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3888, 64 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3888, 80 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3872, 96 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 3904, 32 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3904, 48 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3904, 64 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3920, 32 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3920, 48 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 3936, 32 }, false);

	m_DirtBlockManager.AddItem(Point2f{ 4288, 32 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 4304, 32 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 4320, 32 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 4336, 32 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 4288, 48 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 4304, 48 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 4320, 48 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 4336, 48 }, false);

	m_DirtBlockManager.AddItem(Point2f{ 5296, 720 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 5328, 720 }, true);

	m_DirtBlockManager.AddItem(Point2f{ 5872, 896 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5888, 896 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5904, 896 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5920, 896 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5936, 896 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5952, 896 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5872, 912 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5888, 912 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5904, 912 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5920, 912 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5936, 912 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5952, 912 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5872, 928 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5888, 928 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5904, 928 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5920, 928 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5936, 928 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5952, 928 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5840, 944 }, true);
	m_DirtBlockManager.AddItem(Point2f{ 5872, 944 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5888, 944 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5904, 944 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5920, 944 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5936, 944 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5952, 944 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5872, 960 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5888, 960 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5904, 960 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5920, 960 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5936, 960 }, false);
	m_DirtBlockManager.AddItem(Point2f{ 5952, 960 }, false);
}

void Game::AddSpikesAndFallPits()
{
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 1472, 416, 32, 8});
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 2544, 624, 176, 8 });
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 3024, 16, 48, 8 });
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 2528, 0, 32, 8 });
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 2672, 0, 32, 8 });
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 4208, 0, 80, 8 });
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 4544, 208, 128, 8 });
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 4784, 208, 160, 8 });
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 4560, 624, 32, 8 });
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 4912, 624, 32, 8 });
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 5008, 624, 128, 8 });
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 5296, 624, 32, 8 });
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 5440, 624, 48, 8 });
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 5744, 624, 48, 8 });
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 5904, 624, 48, 8 });
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 5968, 624, 64, 8 });
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 5552, 1040, 32, 8 });
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 5504, 1040, 32, 8 });
	m_SpikesAndFallPitsManager.AddItem(Rectf{ 5328, 1040, 112, 8 });
}

void Game::AddPlatforms()
{
	m_PlatformManager.AddItem(Point2f{ 2160, 736 }, Point2f{ 2160, 736 }, Point2f{ 2272, 736 }, true, 40);
	m_PlatformManager.AddItem(Point2f{ 2576, 640 }, Point2f{ 2576, 640 }, Point2f{ 2688, 640 }, true, 40);
	m_PlatformManager.AddItem(Point2f{ 4128, 256 }, Point2f{ 4128, 256 }, Point2f{ 4128, 288 }, false, 20);
	m_PlatformManager.AddItem(Point2f{ 4224, 288 }, Point2f{ 4224, 288 }, Point2f{ 4336, 288 }, true, 40);
	m_PlatformManager.AddItem(Point2f{ 5072, 640 }, Point2f{ 5072, 640 }, Point2f{ 5072, 752 }, false, 40);
}

void Game::AddDirtPiles()
{
	m_DirtPileManager.AddItem(Point2f{ 344, 448 });
	m_DirtPileManager.AddItem(Point2f{ 952, 448 });

	m_DirtPileManager.AddItem(Point2f{ 1912, 448 });

	m_DirtPileManager.AddItem(Point2f{ 2888, 224 });

	m_DirtPileManager.AddItem(Point2f{ 2616, 32 });

	m_DirtPileManager.AddItem(Point2f{ 5672, 912 });
}

void Game::AddBeetos()
{
	m_BeetoManager.AddItem(Point2f{ 608, 448 }, Point2f{ 464, 448 }, Point2f{ 608, 448 }, true);
	m_BeetoManager.AddItem(Point2f{ 704, 512 }, Point2f{ 704, 512 }, Point2f{ 728, 512 }, false);
	m_BeetoManager.AddItem(Point2f{ 816, 448 }, Point2f{ 816, 448 }, Point2f{ 1008, 448 }, false);
	m_BeetoManager.AddItem(Point2f{ 1008, 448 }, Point2f{ 816, 448 }, Point2f{ 1008, 448 }, true);
	m_BeetoManager.AddItem(Point2f{ 1232, 448 }, Point2f{ 1088, 448 }, Point2f{ 1232, 448 }, true);
	m_BeetoManager.AddItem(Point2f{ 1312, 480 }, Point2f{ 1312, 480 }, Point2f{ 1344, 480 }, false);
	m_BeetoManager.AddItem(Point2f{ 1952, 448 }, Point2f{ 1824, 448 }, Point2f{ 1952, 448 }, true);
	m_BeetoManager.AddItem(Point2f{ 2400, 768 }, Point2f{ 2336, 768 }, Point2f{ 2400, 768 }, true);
	m_BeetoManager.AddItem(Point2f{ 3152, 32 }, Point2f{ 3072, 32 }, Point2f{ 3152, 32 }, true);
	m_BeetoManager.AddItem(Point2f{ 5888, 1120 }, Point2f{ 5856, 1120 }, Point2f{ 5888, 1120 }, true);
	m_BeetoManager.AddItem(Point2f{ 5952, 1088 }, Point2f{ 5921, 1088 }, Point2f{ 5952, 1088 }, true);
}

void Game::DoCollisions(float elapsedSec)
{
	m_BeetoManager.HandleCollisions(m_Level);

	if (m_BubbleManager.HitItem(m_Player.GetShape()))
	{
		m_BubbleManager.PopHitItem();
		m_Player.HitBubble();
	}

	if (m_BubbleManager.GetIsHit())
	{
		m_BubbleManager.PopHitItem();
	}

	if (m_SpikesAndFallPitsManager.HitItem(m_Player.GetShape()))
	{
		m_Player.Die();
	}

	if (m_Player.IsAttack() || m_Player.IsDownAttack())
	{
		if (m_DirtBlockManager.HitItem(m_Player.GetHitbox()))
		{
			m_DirtBlockManager.PopHitItem();
			m_Player.HitDirtBlock();
		}
	}

	if (m_Player.IsAttack())
	{
		
		m_DirtPileManager.HitItem(m_Player.GetHitbox());
	}
	else
	{
		m_DirtPileManager.ResetIsHitable();
	}
	
	if (m_Player.IsAttack() || m_Player.IsDownAttack() || m_Player.IsClimbAttack())
	{
		if (m_BeetoManager.HitItem(m_Player.GetHitbox(), true))
		{
			m_Player.HitBeeto();
		}
	}
	else
	{
		if (m_BeetoManager.HitItem(m_Player.GetShape(), false))
		{
			m_Player.Damage();
		}
	}
}

void Game::PrintControls() const
{
	std::cout << "Control keys:\n"
		"LEFT: A\n"
		"Right: D\n"
		"JUMP: K or SPACE\n"
		"ATTACK: J\n"
		"DOWN ATTACK: S\n"
		"CLIMB: W and S\n";
}

void Game::ShowMenu() const
{
	glPushMatrix();
	{
		utils::SetColor(Color4f{ 0.f, 0.f, 0.f, 1.f });
		utils::FillRect(m_Window.width / 3.214f / 4, m_Window.height / 3.214f / 4, m_Window.width / 3.214f / 2, m_Window.height / 3.214f / 2);
		glPopMatrix();
	}
}