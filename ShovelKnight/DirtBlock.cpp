#include "pch.h"
#include "DirtBlock.h"
#include "Texture.h"

DirtBlock::DirtBlock(const Point2f& spawnPos, const bool& isBigRock)
	: m_pDirtBlockBig{ new Texture("Images/RockBig.png") },
	m_pDirtBlockBigPop{ new Texture("Images/RockBigPop.png") },
	m_pDirtBlockSmall{ new Texture("Images/RockSmall.png") },
	m_pDirtBlockSmallPop{ new Texture("Images/RockSmallPop.png") },
	m_IsBigRock{ isBigRock },
	m_ClipWidthBigPop{ m_pDirtBlockBigPop->GetWidth() / 3 },
	m_ClipWidthSmallPop{ m_pDirtBlockSmallPop->GetWidth() / 3 },
	m_NrFramesPerSec{ 9 },
	m_AnimTime{ 0 },
	m_AnimFrame{ 0 },
	m_Pop{ false },
	m_PopAnimDone{ false }
{
	m_Shape = Rectf{ spawnPos.x, spawnPos.y, m_pDirtBlockSmall->GetWidth(), m_pDirtBlockSmall->GetHeight() };
	if (isBigRock) m_Shape = Rectf{ spawnPos.x, spawnPos.y, m_pDirtBlockBig->GetWidth(), m_pDirtBlockBig->GetHeight() };

	m_Vertices.push_back(std::vector<Point2f>
	{
		Point2f{m_Shape.left					, m_Shape.bottom + m_Shape.height},
		Point2f{m_Shape.left + m_Shape.width	, m_Shape.bottom + m_Shape.height},
		Point2f{m_Shape.left + m_Shape.width	, m_Shape.bottom },
		Point2f{m_Shape.left					, m_Shape.bottom }
	});
}

DirtBlock::~DirtBlock()
{
	delete m_pDirtBlockBig;
	m_pDirtBlockBig = nullptr;
	delete m_pDirtBlockBigPop;
	m_pDirtBlockBigPop = nullptr;
	delete m_pDirtBlockSmall;
	m_pDirtBlockSmall = nullptr;
	delete m_pDirtBlockSmallPop;
	m_pDirtBlockSmallPop = nullptr;
}

void DirtBlock::Update(float elapsedSec)
{
	if (m_Pop)
	{
		m_Shape.width = 0;
		m_Shape.height = 0;
		PopAnimation(elapsedSec);
	}
}

void DirtBlock::Draw() const
{
	glPushMatrix();
	{
		glTranslatef(
			m_Shape.left,
			m_Shape.bottom,
			0
		);
		if (m_IsBigRock)
		{
			if (!m_Pop)
			{
				m_pDirtBlockBig->Draw(Point2f{},
					Rectf(m_pDirtBlockBig->GetWidth(),
						m_pDirtBlockBig->GetHeight(),
						m_pDirtBlockBig->GetWidth(),
						m_pDirtBlockBig->GetHeight())
				);
			}
			else
			{
				m_pDirtBlockBigPop->Draw(Point2f{},
					Rectf(m_ClipWidthBigPop * m_AnimFrame,
						m_pDirtBlockBigPop->GetHeight(),
						m_pDirtBlockBigPop->GetWidth() / 3,
						m_pDirtBlockBigPop->GetHeight())
				);
			}
		}
		else
		{
			if (!m_Pop)
			{
				m_pDirtBlockSmall->Draw(Point2f{},
					Rectf(m_pDirtBlockSmall->GetWidth(),
						m_pDirtBlockSmall->GetHeight(),
						m_pDirtBlockSmall->GetWidth(),
						m_pDirtBlockSmall->GetHeight())
				);
			}
			else
			{
				m_pDirtBlockSmallPop->Draw(Point2f{},
					Rectf(m_ClipWidthSmallPop * m_AnimFrame,
						m_pDirtBlockSmallPop->GetHeight(),
						m_pDirtBlockSmallPop->GetWidth() / 3,
						m_pDirtBlockSmallPop->GetHeight())
				);
			}
		}
	}
	glPopMatrix();
}

void DirtBlock::PopAnimation(float elapsedSec)
{
	m_AnimTime += elapsedSec;
	if (m_AnimTime >= 1.0f / m_NrFramesPerSec)
	{
		++m_AnimFrame;
		m_AnimTime = 0;
	}

	if (m_AnimFrame == 3)
	{
		m_PopAnimDone = true;
	}
}

void DirtBlock::Pop()
{
	m_Pop = true;
}

bool DirtBlock::IsPopDone() const
{
	return m_PopAnimDone;
}

bool DirtBlock::IsOverlapping(const Rectf& rect) const
{
	return utils::IsOverlapping(rect, m_Shape);
}

const Rectf& DirtBlock::GetShape() const
{
	return m_Shape;
}

const bool& DirtBlock::GetIsPop() const
{
	return m_Pop;
}

void DirtBlock::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity, const bool& isLookingLeft, float elapsedSec) const
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
		}
	}
}

bool DirtBlock::IsOnBlock(const Rectf& actorShape) const
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