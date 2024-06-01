#include "pch.h"
#include "SpikesAndFallPits.h"
#include "utils.h"

SpikesAndFallPits::SpikesAndFallPits(const Rectf& shape)
	: m_Shape{ shape }
{
	
}

SpikesAndFallPits::~SpikesAndFallPits()
{

}

void SpikesAndFallPits::Draw() const
{
	glPushMatrix();
	{
		// DEBUGGING
		utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
		utils::FillRect(m_Shape);
	}
	glPopMatrix();
}

bool SpikesAndFallPits::IsOverlapping(const Rectf& rect) const
{
	return utils::IsOverlapping(rect, m_Shape);
}

const Rectf& SpikesAndFallPits::GetShape() const
{
	return m_Shape;
}