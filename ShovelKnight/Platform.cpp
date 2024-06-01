#include "pch.h"
#include "Platform.h"
#include "Texture.h"
#include "utils.h"

Platform::Platform(const Point2f& bottomLeft, const Point2f& p1, const Point2f& p2, const bool& isHorizontal, const float speed)
	: m_pPlatform{ new Texture{"Images/Platform.png"} },
	m_BottomLeft{ bottomLeft },
	m_P1Trail{ p1 },
	m_P2Trail{ p2 },
	m_P1Collision{ m_BottomLeft.x - 16, m_BottomLeft.y + 16 },
	m_P2Collision{ m_BottomLeft.x - 16 + m_pPlatform->GetWidth(), m_BottomLeft.y + 16 },
	m_PlatformSpeed{ speed },
	m_Direction{ true },
	m_IsHorizontal{ isHorizontal }
{
	m_Vertices.push_back(std::vector<Point2f>{ m_P1Collision, m_P2Collision });
	m_Vertices.push_back(std::vector<Point2f>{ m_P2Collision, Point2f{ m_BottomLeft.x - 16 + m_pPlatform->GetWidth(), m_BottomLeft.y } });
	m_Vertices.push_back(std::vector<Point2f>{ Point2f{ m_BottomLeft.x - 16, m_BottomLeft.y },
											   Point2f{ m_BottomLeft.x - 16 + m_pPlatform->GetWidth(), m_BottomLeft.y } });
	m_Vertices.push_back(std::vector<Point2f>{ Point2f{ m_BottomLeft.x - 16, m_BottomLeft.y }, m_P1Collision });
}

Platform::~Platform()
{
	delete m_pPlatform;
	m_pPlatform = nullptr;
}

void Platform::Update(float elapsedSec)
{
	m_P1Collision = Point2f{ m_BottomLeft.x - 16, m_BottomLeft.y + 16 };
	m_P2Collision = Point2f{ m_BottomLeft.x - 16 + m_pPlatform->GetWidth(), m_BottomLeft.y + 16 };

	if (m_Direction)
	{
		m_PlatformSpeed = abs(m_PlatformSpeed);
		if (m_IsHorizontal)
		{
			m_BottomLeft.x += m_PlatformSpeed * elapsedSec;
		}
		else
		{
			m_BottomLeft.y += m_PlatformSpeed * elapsedSec;
		}

	}
	else
	{
		m_PlatformSpeed = -abs(m_PlatformSpeed);
		if (m_IsHorizontal)
		{
			m_BottomLeft.x += m_PlatformSpeed * elapsedSec;
		}
		else
		{
			m_BottomLeft.y += m_PlatformSpeed * elapsedSec;
		}
	}

	if (m_BottomLeft.x > m_P2Trail.x || m_BottomLeft.y > m_P2Trail.y)
	{
		m_Direction = false;
	}

	if (m_BottomLeft.x < m_P1Trail.x || m_BottomLeft.y < m_P1Trail.y)
	{
		m_Direction = true;
	}

	m_Vertices[0] = std::vector<Point2f>{ m_P1Collision, m_P2Collision };
	m_Vertices[1] = std::vector<Point2f>{ m_P2Collision, Point2f{ m_BottomLeft.x - 16 + m_pPlatform->GetWidth(), m_BottomLeft.y } };
	m_Vertices[2] = std::vector<Point2f>{ Point2f{ m_BottomLeft.x - 16 + m_pPlatform->GetWidth(), m_BottomLeft.y }, 
										  Point2f{ m_BottomLeft.x - 16, m_BottomLeft.y } };
	m_Vertices[3] = std::vector<Point2f>{ Point2f{ m_BottomLeft.x - 16, m_BottomLeft.y }, m_P1Collision };
}

void Platform::Draw() const
{
	glPushMatrix();
	{
		// DEBUGGING
		/*utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
		utils::DrawLine(m_P1Collision, m_P2Collision);
		utils::SetColor(Color4f{ 0.f, 0.f, 1.f, 1.f });
		utils::DrawLine(Point2f{ m_BottomLeft.x - 16 + m_pTexture->GetWidth(), m_BottomLeft.y },
						Point2f{ m_BottomLeft.x - 16, m_BottomLeft.y });
		utils::DrawLine(Point2f{ m_BottomLeft.x - 16, m_BottomLeft.y }, m_P1Collision);
		utils::DrawLine(Point2f{ m_BottomLeft.x - 16 + m_pTexture->GetWidth(), m_BottomLeft.y }, m_P2Collision);*/
		m_pPlatform->Draw(Point2f{  m_BottomLeft.x - 16, m_BottomLeft.y }, Rectf{ 0, 0, m_pPlatform->GetWidth(), m_pPlatform->GetHeight() });
	}
	glPopMatrix();
} 

void Platform::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity, const bool& isLookingLeft, float elapsedSec) const
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
					Point2f{ actorShape.left + actorShape.width - 1, actorShape.bottom },
					Point2f{ actorShape.left + actorShape.width - 1, actorShape.bottom + actorShape.height },
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
			// Bottom Platform
			if (actorVelocity.y > 0)
			{
				actorShape.bottom = hitInfo.intersectPoint.y - actorShape.height;
			}
			actorVelocity.y = 0;

			if (m_IsHorizontal && index == 0)
			{
				actorShape.left += m_PlatformSpeed * elapsedSec;
			}
			else
			{
				actorShape.bottom += m_PlatformSpeed * elapsedSec;
			}
		}
	}
}

bool Platform::IsOnPlatform(const Rectf& actorShape) const
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
	return false;
}