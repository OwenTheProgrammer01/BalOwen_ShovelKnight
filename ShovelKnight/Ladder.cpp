#include "pch.h"
#include "Ladder.h"
#include "Texture.h"
#include "utils.h"

Ladder::Ladder(const Rectf& Shape)
	: m_Shape{Shape}
{
	m_Vertices.push_back(std::vector<Point2f>{
		Point2f{ Shape.left			  , Shape.bottom + Shape.height }, 
		Point2f{ Shape.left + Shape.width, Shape.bottom + Shape.height }
	});
}

Ladder::~Ladder()
{
	
}

// DEBUGGING
void Ladder::Draw() const
{
	glPushMatrix();
	{
		utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
		utils::DrawRect(m_Shape);

		for (int index{ 0 }; index < m_Vertices.size(); ++index)
		{
			utils::SetColor(Color4f(1.f, 1.f, 1.f, 1.f));
			utils::DrawPolygon(m_Vertices[index]);
		}
	}
	glPopMatrix();
}
// ---------

const Rectf& Ladder::GetShape() const
{
	return m_Shape;
}

void Ladder::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity, const bool& isClimbing) const
{
	if (!isClimbing)
	{
		utils::HitInfo hitInfo{};
		for (int index{ 0 }; index < m_Vertices.size(); ++index)
		{
			// Y Collisions
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
				actorShape.bottom = hitInfo.intersectPoint.y;
				actorVelocity.y = 0;
			}
		}
	}
}

bool Ladder::IsOnGround(const Rectf& actorShape) const
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