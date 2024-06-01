#include "pch.h"
#include "Level.h"
#include <iostream>
#include "Texture.h"
#include "utils.h"
#include "SVGParser.h"
#include "Ladder.h"
#include "Player.h"

Level::Level()
	: m_pBackground1Texture{ new Texture("Images/Level/BG1.png") },
	m_pBackground2Texture{ new Texture("Images/Level/BG2.png") },
	m_pBackground3Texture{ new Texture("Images/Level/BG3.png") },
	m_pCastleTexture{ new Texture("Images/Level/Castle.png") },
	m_pCloudsTexture{ new Texture("Images/Level/Clouds.png") },
	m_pLevelL1Texture{ new Texture("Images/Level/Level1_L1.png") },
	m_pLevelL2Texture{ new Texture("Images/Level/Level1_L2.png") },
	m_pLevelL3Texture{ new Texture("Images/Level/Level1_L3.png") },
	m_LevelPart{ 1 },
	m_Boundaries{ 0, 416, 1632, 224 },
	m_Animation{ Animation::None },
	m_IsAnimating{ false }
{
	SVGParser::GetVerticesFromSvgFile("Images/Level/Level1_L1.svg", m_Vertices);
	SetLevelBoundaries();
	CreateLadders();
}

Level::~Level()
{
	delete m_pBackground1Texture;
	m_pBackground1Texture = nullptr;
	delete m_pBackground2Texture;
	m_pBackground2Texture = nullptr;
	delete m_pBackground3Texture;
	m_pBackground3Texture = nullptr;
	delete m_pCastleTexture;
	m_pCastleTexture = nullptr;
	delete m_pCloudsTexture;
	m_pCloudsTexture = nullptr;
	delete m_pLevelL1Texture;
	m_pLevelL1Texture = nullptr;
	delete m_pLevelL2Texture;
	m_pLevelL2Texture = nullptr;
	delete m_pLevelL3Texture;
	m_pLevelL3Texture = nullptr;
}

void Level::SetLevelBoundaries()
{
	// LevelBoundaries
	m_LevelBoundaries.push_back(Rectf{ 0, 416, 1632, 224 });
	m_LevelBoundaries.push_back(Rectf{ 1632, 416, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 2032, 416, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 2032, 624, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 2432, 624, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 2832, 624, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 2832, 416, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 2832, 208, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 2832, 0, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 2432, 0, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 3232, 0, 832, 224 });
	m_LevelBoundaries.push_back(Rectf{ 4064, 0, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 4064, 208, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 4464, 208, 576, 224 });
	m_LevelBoundaries.push_back(Rectf{ 4064, 416, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 4064, 624, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 4464, 624, 784, 224 });
	m_LevelBoundaries.push_back(Rectf{ 5248, 624, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 5648, 624, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 5648, 832, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 5648, 1040, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 5152, 1040, 496, 224 });
	m_LevelBoundaries.push_back(Rectf{ 6048, 1040, 400, 224 });
	m_LevelBoundaries.push_back(Rectf{ 6432, 1040, 400, 224 });
}

void Level::CreateLadders()
{
	//Ladders
	Ladder ladder01{ Rectf { 2320, 528, 16, 128 } };
	Ladder ladder02{ Rectf { 2064, 656, 16, 160 } };
	Ladder ladder03{ Rectf { 3168, 624, 16,  32 } };
	Ladder ladder04{ Rectf { 2912, 368, 16,  64 } };
	Ladder ladder05{ Rectf { 3120, 224, 16,  64 } };
	Ladder ladder06{ Rectf { 2992, 288, 16,  64 } };
	Ladder ladder07{ Rectf { 4416,  96, 16, 128 } };
	Ladder ladder08{ Rectf { 4064, 336, 16, 128 } };
	Ladder ladder09{ Rectf { 4160, 576, 16,  80 } };
	Ladder ladder10{ Rectf { 4336, 592, 16,  48 } };
	Ladder ladder11{ Rectf { 6016, 688, 16, 288 } };
	Ladder ladder12{ Rectf { 5776, 992, 16, 160 } };
	m_Ladders.push_back(ladder01);
	m_Ladders.push_back(ladder02);
	m_Ladders.push_back(ladder03);
	m_Ladders.push_back(ladder04);
	m_Ladders.push_back(ladder05);
	m_Ladders.push_back(ladder06);
	m_Ladders.push_back(ladder07);
	m_Ladders.push_back(ladder08);
	m_Ladders.push_back(ladder09);
	m_Ladders.push_back(ladder10);
	m_Ladders.push_back(ladder11);
	m_Ladders.push_back(ladder12);
}

void Level::DrawBackground() const
{
	m_pCloudsTexture->Draw(Rectf(0, 0, m_pCloudsTexture->GetWidth(), m_pCloudsTexture->GetHeight() + 16));
}

void Level::DrawMiddleGround() const
{
	m_pLevelL3Texture->Draw();
	m_pLevelL2Texture->Draw();

	// DEBUGGING
	/*for (Ladder ladder : m_Ladders)
	{
		ladder.Draw();
	}*/
}

void Level::DrawForeground() const
{
	m_pLevelL1Texture->Draw();

	// DEBUGGING
	/*for (int index{ 0 }; index < m_Vertices.size(); ++index)
	{
		utils::SetColor(Color4f(1.f, 1.f, 1.f, 1.f));
		utils::DrawPolygon(m_Vertices[index]);
	}*/
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity, const bool& isLookingLeft, const bool& isClimbing) const
{
	utils::HitInfo hitInfo{};
	for (int index{ 0 }; index < m_Vertices.size(); ++index)
	{
		// Horizontal collisions
		if (
				(
				utils::Raycast(
				m_Vertices[index],
				Point2f{ actorShape.left						, actorShape.bottom + 2 },
				Point2f{ actorShape.left + actorShape.width , actorShape.bottom + 2 },
				hitInfo)
				||
				utils::Raycast(
				m_Vertices[index],
				Point2f{ actorShape.left						, actorShape.bottom + actorShape.height / 2 },
				Point2f{ actorShape.left + actorShape.width , actorShape.bottom + actorShape.height / 2 },
				hitInfo)
				||
				utils::Raycast(
				m_Vertices[index],
				Point2f{ actorShape.left						, actorShape.bottom + actorShape.height - 2 },
				Point2f{ actorShape.left + actorShape.width , actorShape.bottom + actorShape.height - 2 },
				hitInfo)
				)
			&&
			hitInfo.normal.DotProduct(actorVelocity) < 0
			)
		{
			// Wall LEFT
			if (isLookingLeft)
			{
				actorShape.left = hitInfo.intersectPoint.x;
			}
			// Wall RIGHT
			else
			{
				actorShape.left = hitInfo.intersectPoint.x - actorShape.width;
			}
			actorVelocity.x = 0;
		}

		// Vertical Collisions
		if (
			(// LEFT
				utils::Raycast(
				m_Vertices[index],
				Point2f{ actorShape.left + 1, actorShape.bottom },
				Point2f{ actorShape.left + 1, actorShape.bottom + actorShape.height },
				hitInfo)
				||
				// RIGHT
				utils::Raycast(
				m_Vertices[index],
				Point2f{ actorShape.left  + actorShape.width - 1, actorShape.bottom },
				Point2f{ actorShape.left  + actorShape.width - 1, actorShape.bottom + actorShape.height },
				hitInfo)
			)
			&&
			hitInfo.normal.DotProduct(actorVelocity) <= 0
			)
		{
			// Ground
			if (actorVelocity.y < 0)
			{
				actorShape.bottom = hitInfo.intersectPoint.y;
			}
			// Ceiling
			if (actorVelocity.y > 0)
			{
				actorShape.bottom = hitInfo.intersectPoint.y - actorShape.height;
			}
			actorVelocity.y = 0;
		}
	}
	
	int index{ 0 };
	for (Ladder ladder : m_Ladders)
	{
		if (index != 1)
		{
			ladder.HandleCollision(actorShape, actorVelocity, isClimbing);
		}
		index++;
	}
}

bool Level::IsOnGround(const Rectf& actorShape) const
{
	utils::HitInfo hitInfo{};
	for (int index{ 0 }; index < m_Vertices.size(); ++index)
	{
		if (// LEFT
			utils::Raycast(
			m_Vertices[index],
			Point2f{ actorShape.left, actorShape.bottom - 1 },
			Point2f{ actorShape.left, actorShape.bottom + actorShape.height - 1 },
			hitInfo)
			||
			// RIGHT
			utils::Raycast(
			m_Vertices[index],
			Point2f{ actorShape.left + actorShape.width, actorShape.bottom - 1 },
			Point2f{ actorShape.left + actorShape.width, actorShape.bottom + actorShape.height - 1 },
			hitInfo)
			)
		{
			return true;
		}
	}

	int index { 0 };
	for (Ladder ladder : m_Ladders)
	{
		if (index != 1)
		{
			if (ladder.IsOnGround(actorShape))
			{
				return true;
			}
		}
		index++;
	}
	return false;
}

bool Level::IsOnLadder(const Rectf& actorShape) const
{
	for (Ladder ladder : m_Ladders)
	{
		if (ladder.GetShape().left								<= actorShape.left   + actorShape.width / 2 &&
			ladder.GetShape().left	 + ladder.GetShape().width	>= actorShape.left   + actorShape.width / 2 &&
			ladder.GetShape().bottom							<= actorShape.bottom + actorShape.height	&&
			ladder.GetShape().bottom + ladder.GetShape().height >= actorShape.bottom)
		{
			return true;
		}
	}
	return false;
}

const Rectf& Level::GetLadder(const Rectf& actorShape) const
{
	for (Ladder ladder : m_Ladders)
	{
		if (ladder.GetShape().left								<= actorShape.left	 + actorShape.width / 2 &&
			ladder.GetShape().left	 + ladder.GetShape().width	>= actorShape.left	 + actorShape.width / 2 &&
			ladder.GetShape().bottom							<= actorShape.bottom + actorShape.height	&&
			ladder.GetShape().bottom + ladder.GetShape().height >= actorShape.bottom)
		{
			return ladder.GetShape();
		}
	}
	return Rectf{};
}

const Rectf& Level::GetBoundaries() const
{
	return m_Boundaries;
}

const int& Level::GetLevelPart() const
{
	return m_LevelPart;
}

void Level::ChangeLevelPart(Player& player, float elapsedSec)
{
	// DEBUGGING
	/*const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_B])
	{
		std::cout << "LevelPart: " << m_LevelPart << "\n";
		std::cout << "Boundaries: { " << m_Boundaries.left << ", " << m_Boundaries.bottom << ", " << m_Boundaries.width << ", " << m_Boundaries.height << " }\n";
	}*/

	if (player.Respawn())
	{
		m_LevelPart = 1;
		m_Boundaries = m_LevelBoundaries[m_LevelPart - 1];
	}

	if (!m_IsAnimating)
	{
		switch (m_LevelPart)
		{
		case 1:
			AnimRight(player.GetShape(), +1);
			break;
		case 2:
			AnimLeft(player.GetShape(), -1);
			AnimRight(player.GetShape(), +1);
			break;
		case 3:
			AnimLeft(player.GetShape(), -1);
			AnimUp(player.GetShape(), +1);
			break;
		case 4:
			AnimDown(player.GetShape(), -1);
			AnimRight(player.GetShape(), +1);
			break;
		case 5:
			AnimLeft(player.GetShape(), -1);
			AnimRight(player.GetShape(), +1);
			break;
		case 6:
			AnimLeft(player.GetShape(), -1);
			AnimDown(player.GetShape(), +1);
			break;
		case 7:
		case 8:
			AnimUp(player.GetShape(), -1);
			AnimDown(player.GetShape(), +1);
			break;
		case 9:
			AnimLeft(player.GetShape(), +1);
			AnimRight(player.GetShape(), +2);
			break;
		case 10:
			AnimRight(player.GetShape(), -1);
			break;
		case 11:
			AnimLeft(player.GetShape(), -2);
			AnimRight(player.GetShape(), +1);
			break;
		case 12:
			AnimLeft(player.GetShape(), -1);
			AnimUp(player.GetShape(), +1);
			break;
		case 13:
			AnimDown(player.GetShape(), -1);
			AnimRight(player.GetShape(), +1);
			AnimUp(player.GetShape(), +2);
			break;
		case 14:
			AnimLeft(player.GetShape(), -1);
			break;
		case 15:
			AnimDown(player.GetShape(), -2);
			AnimUp(player.GetShape(), +1);
			break;
		case 16:
			AnimDown(player.GetShape(), -1);
			AnimRight(player.GetShape(), +1);
			break;
		case 17:
		case 18:
			AnimLeft(player.GetShape(), -1);
			AnimRight(player.GetShape(), +1);
			break;
		case 19:
			AnimLeft(player.GetShape(), -1);
			AnimUp(player.GetShape(), +1);
			break;
		case 20:
			AnimDown(player.GetShape(), -1);
			AnimUp(player.GetShape(), +1);
			break;
		case 21:
			AnimDown(player.GetShape(), -1);
			AnimLeft(player.GetShape(), +1);
			AnimRight(player.GetShape(), +2);
			break;
		case 22:
			AnimRight(player.GetShape(), -1);
			break;
		case 23:
			AnimLeft(player.GetShape(), -2);
			AnimRight(player.GetShape(), +1);
			break;
		case 24:
			AnimLeft(player.GetShape(), -1);
			break;
		}
	}
	LevelAnimation(player, elapsedSec);
}

void Level::LevelAnimation(Player& player, float elapsedSec)
{
	switch (m_Animation)
	{
	case Animation::None:
		m_IsAnimating = false;
		break;
	case Animation::Left:
		m_IsAnimating = true;
		if (m_Boundaries.left + m_Boundaries.width > m_LevelBoundaries[m_LevelPart - 1].left + m_LevelBoundaries[m_LevelPart - 1].width)
		{
			m_Boundaries.left -= 400 * elapsedSec;
			player.LevelChangeAnimation(Point2f{ -25, 0}, elapsedSec);
		}
		else
		{
			m_Boundaries = m_LevelBoundaries[m_LevelPart - 1];
			m_Animation = Animation::None;
		}
		break;
	case Animation::Right:
		m_IsAnimating = true;
		if (m_Boundaries.left < m_LevelBoundaries[m_LevelPart - 1].left)
		{
			m_Boundaries.left += 400 * elapsedSec;
			player.LevelChangeAnimation(Point2f{ 25, 0 }, elapsedSec);
		}
		else
		{
			m_Boundaries = m_LevelBoundaries[m_LevelPart - 1];
			m_Animation = Animation::None;
		}
		break;
	case Animation::Up:
		m_IsAnimating = true;
		if (m_Boundaries.bottom < m_LevelBoundaries[m_LevelPart - 1].bottom)
		{
			m_Boundaries.bottom += 224 * elapsedSec;
			player.LevelChangeAnimation(Point2f{ 0, 25 }, elapsedSec);
		}
		else
		{
			m_Boundaries = m_LevelBoundaries[m_LevelPart - 1];
			m_Animation = Animation::None;
		}
		break;
	case Animation::Down:
		m_IsAnimating = true;
		if (m_Boundaries.bottom > m_LevelBoundaries[m_LevelPart - 1].bottom)
		{
			m_Boundaries.bottom -= 224 * elapsedSec;
			player.LevelChangeAnimation(Point2f{ 0, -25 }, elapsedSec);
		}
		else
		{
			m_Boundaries = m_LevelBoundaries[m_LevelPart - 1];
			m_Animation = Animation::None;
		}
		break;
	}
}

void Level::AnimLeft(const Rectf& actorShape, int changeLevelPartWith)
{
	if (actorShape.left <= m_Boundaries.left)
	{
		m_LevelPart += changeLevelPartWith;
		m_Boundaries.width = 400;
		m_Animation = Animation::Left;
	}
}

void Level::AnimRight(const Rectf& actorShape, int changeLevelPartWith)
{
	if (actorShape.left + actorShape.width >= m_Boundaries.left + m_Boundaries.width)
	{
		m_LevelPart += changeLevelPartWith;
		m_Boundaries.width = 400;
		m_Boundaries.left = m_LevelBoundaries[m_LevelPart - 1].left - m_Boundaries.width;
		m_Animation = Animation::Right;
	}
}

void Level::AnimUp(const Rectf& actorShape, int changeLevelPartWith)
{
	if (actorShape.bottom + actorShape.height >= m_Boundaries.bottom + m_Boundaries.height)
	{
		m_LevelPart += changeLevelPartWith;
		m_Animation = Animation::Up;
	}
}

void Level::AnimDown(const Rectf& actorShape, int changeLevelPartWith)
{
	if (actorShape.bottom <= m_Boundaries.bottom)
	{
		m_LevelPart += changeLevelPartWith;
		m_Animation = Animation::Down;
	}
}