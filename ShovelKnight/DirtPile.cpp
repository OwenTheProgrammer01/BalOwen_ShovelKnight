#include "pch.h"
#include "DirtPile.h"
#include "Texture.h"

DirtPile::DirtPile(const Point2f& spawnPos)
	: m_pDirtPile{ new Texture("Images/DirtPile.png") },
	m_ClipWidth{ m_pDirtPile->GetWidth() / 5 },
	m_ClipHeight{ m_pDirtPile->GetHeight() / 5 },
	m_Shape{ spawnPos.x, spawnPos.y, m_ClipWidth, m_ClipHeight },
	m_NrFramesPerSec{ 5 },
	m_AnimTime{ 0 },
	m_AnimFrame{ 0 },
	m_Hit{ 0 },
	m_IsHitable{ true }
{

}

DirtPile::~DirtPile()
{
	delete m_pDirtPile;
	m_pDirtPile = nullptr;
}

void DirtPile::Update(float elapsedSec)
{
	m_AnimTime += elapsedSec;
	if (m_AnimFrame == 0)
	{
		if (m_AnimTime >= 3.0f)
		{
			m_AnimFrame = (m_AnimFrame + 1) % 5;
			m_AnimTime = 0;
		}
	}
	else
	{
		if (m_AnimTime >= 1.0f / m_NrFramesPerSec)
		{
			m_AnimFrame = (m_AnimFrame + 1) % 5;
			m_AnimTime = 0;
		}
	}
}

void DirtPile::Draw() const
{
	glPushMatrix();
	{
		glTranslatef(
			m_Shape.left,
			m_Shape.bottom,
			0
		);

		m_pDirtPile->Draw(Point2f{},
			Rectf(m_ClipWidth * m_AnimFrame,
				m_ClipHeight * (m_Hit + 1),
				m_ClipWidth,
				m_ClipHeight)
		);
	}
	glPopMatrix();
}

void DirtPile::Hit()
{
	if (m_IsHitable)
	{
		++m_Hit;
		m_IsHitable = false;
	}
}

void DirtPile::ResetIsHitable()
{
	m_IsHitable = true;
}

bool DirtPile::IsOverlapping(const Rectf& rect) const
{
	return utils::IsOverlapping(rect, m_Shape);
}

const Rectf& DirtPile::GetShape() const
{
	return m_Shape;
}

const int& DirtPile::GetHit() const
{
	return m_Hit;
}