#include "pch.h"
#include "Beeto.h"

#include <iostream>

#include "Level.h"
#include "Texture.h"
#include "utils.h"

Beeto::Beeto(const Point2f& spawnPos, const Point2f& p1, const Point2f& p2, const bool& isLookingLeft)
	: m_pBeeto{ new Texture("Images/Beeto.png") },
	m_P1Trail{ p1 },
	m_P2Trail{ p2 },
	m_Speed{ 10, 0 },
	m_Acceleration{ 0, -981.0f },
	m_ClipWidth{ m_pBeeto->GetWidth() / 4 },
	m_ClipHeight{ m_pBeeto->GetHeight() / 2 },
	m_Shape{ spawnPos.x, spawnPos.y, m_ClipWidth, m_ClipHeight },
	m_NrOfFrames{ 4 },
	m_NrFramesPerSec{ 4 },
	m_AnimTime{ 0 },
	m_DeathAnimTime{ 0 },
	m_AnimFrameX{ 0 },
	m_AnimFrameY{ 1 },
	m_IsLookingLeft{ isLookingLeft },
	m_IsHit{ false },
	m_DeathAnimDone{ false },
	m_CountDeathAnim{ 0 }
{

}

Beeto::~Beeto()
{
	delete m_pBeeto;
	m_pBeeto = nullptr;
}

void Beeto::Update(float elapsedSec)
{
	if (!m_IsHit)
	{
		Animation(elapsedSec);
	}
	else
	{
		DeathAnimation(elapsedSec);
	}
	HandleMovement(elapsedSec);
}

void Beeto::Draw() const
{
	glPushMatrix();
	{
		glTranslatef(
			m_Shape.left,
			m_Shape.bottom,
			0.0f
		);
		if (m_IsLookingLeft)
		{
			glScalef(-1, 1, 1);
			glTranslatef(
				-m_Shape.width,
				0.0f,
				0.0f
			);
		}
		m_pBeeto->Draw(Point2f(),
			Rectf(m_ClipWidth * m_AnimFrameX,
				m_ClipHeight * m_AnimFrameY,
				m_ClipWidth,
				m_ClipHeight)
		);
	}
	glPopMatrix();
	//utils::SetColor(Color4f{ 0.f, 0.f, 0.f, 1.f });
	//utils::DrawRect(m_Shape);
}

void Beeto::Animation(float elapsedSec)
{
	m_AnimTime += elapsedSec;
	m_AnimFrameY = 1;
	if (m_AnimTime >= 1.0f / m_NrFramesPerSec)
	{
		m_AnimFrameX = (m_AnimFrameX + 1) % m_NrOfFrames;
		m_AnimTime = 0;
	}
}

void Beeto::DeathAnimation(float elapsedSec)
{
	if (m_CountDeathAnim == 0)
	{
		m_AnimFrameX = 0;
	}

	m_AnimFrameY = 0;
	m_DeathAnimTime += elapsedSec;
	if (m_DeathAnimTime >= 1.0f / 4)
	{
		m_AnimFrameX = (m_AnimFrameX + 1) % 2;
		++m_CountDeathAnim;
		m_DeathAnimTime = 0;
	}

	if (m_CountDeathAnim == 3)
	{
		m_DeathAnimDone = true;
	}
}

void Beeto::Hit(const bool& doDamage)
{
	if (!doDamage)
	{
		m_AnimFrameX = 0;
		m_AnimFrameY = 0;
		m_Speed.y = 200;
		m_IsHit = true;
	}
}

bool Beeto::IsDeathAnimDone() const
{
	return m_DeathAnimDone;
}

void Beeto::SetDeath()
{
	m_DeathAnimDone = true;
}

bool Beeto::IsOverlapping(const Rectf& rect) const
{
	return utils::IsOverlapping(rect, m_Shape);
}

const bool& Beeto::GetIsHit() const
{
	return m_IsHit;
}

const Rectf& Beeto::GetShape() const
{
	return m_Shape;
}

void Beeto::HandleCollision(const Level& level)
{
	level.HandleCollision(m_Shape, m_Speed, m_IsLookingLeft, false);
}

void Beeto::HandleMovement(float elapsedSec)
{
	if (m_IsLookingLeft)
	{
		m_Speed.x = -abs(m_Speed.x);
	}
	else
	{
		m_Speed.x = abs(m_Speed.x);
	}
	m_Shape.left += m_Speed.x * elapsedSec;

	if (m_Shape.left > m_P2Trail.x)
	{
		m_IsLookingLeft = true;
	}

	if (m_Shape.left < m_P1Trail.x)
	{
		m_IsLookingLeft = false;
	}

	m_Shape.left += m_Speed.x * elapsedSec;
	m_Speed.y += m_Acceleration.y * elapsedSec;
	m_Shape.bottom += m_Speed.y * elapsedSec;
}