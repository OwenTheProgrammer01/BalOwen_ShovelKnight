#include "pch.h"
#include "Bubble.h"
#include <iostream>
#include "Texture.h"
#include "utils.h"

Bubble::Bubble(const Point2f& center, int ySpawnOffset)
	: m_pBubble{ new Texture("Images/Bubble.png") },
	m_pBubblePop{ new Texture("Images/BubblePop.png") },
	m_SpawnCenter{ center },
	m_YSpawnOffset{ ySpawnOffset },
	m_Shape{ Point2f{ center.x, center.y - m_YSpawnOffset }, m_pBubble->GetHeight() * 2 / 5 },
	m_ClipWidth{ m_pBubble->GetWidth() / 4 },
	m_ClipHeight{ m_pBubble->GetHeight() },
	m_ClipWidthPop{ m_pBubblePop->GetWidth() / 2 },
	m_NrOfFrames{ 4 },
	m_NrFramesPerSec{ 6 },
	m_PopSpeed{ 4 },
	m_AnimTime{ 0 },
	m_AnimFrame{ 0 },
	m_Pop{ false },
	m_PopAnimDone{ false },
	m_SpawnAnim{ true },
	m_SpawnCount{ 0 },
	m_AnimTimeSpawn{ 0 },
	m_WaitSecToSpawn{ 2 },
	m_HaveWaitedToSpawn{ false }
{
	
}

Bubble::~Bubble()
{
	delete m_pBubble;
	m_pBubble = nullptr;
	delete m_pBubblePop;
	m_pBubblePop = nullptr;
}

void Bubble::Update(float elapsedSec)
{
	Animation(elapsedSec);
}

void Bubble::Draw() const
{
	glPushMatrix();
	{
		// DEBUGGING
		//utils::SetColor(Color4f{1.f, 0.f, 0.f, 1.f});
		//utils::FillEllipse(m_Shape.center, m_Shape.radius, m_Shape.radius);

		glTranslatef(
			m_Shape.center.x,
			m_Shape.center.y,
			0
		);
		glTranslatef(
			-m_Shape.radius * 5 / 4,
			-m_Shape.radius * 5 / 4,
			0
		);
		if (!m_Pop)
		{
			m_pBubble->Draw(Point2f{},
				Rectf(m_ClipWidth * m_AnimFrame,
					m_ClipHeight,
					m_ClipWidth,
					m_ClipHeight)
			);
		}
		else
		{
			m_pBubblePop->Draw(Point2f{},
				Rectf(m_ClipWidth * m_AnimFrame,
					m_ClipHeight,
					m_ClipWidth,
					m_ClipHeight)
			);
		}
	}
	glPopMatrix();
}

void Bubble::Animation(float elapsedSec)
{
	if (m_SpawnAnim)
	{
		if (m_HaveWaitedToSpawn)
		{
			if (m_SpawnCount < m_YSpawnOffset)
			{
				m_AnimTimeSpawn += elapsedSec;
				if (m_AnimTimeSpawn >= 1.0f / 40)
				{
					m_Shape.center.y += 1;
					m_AnimTimeSpawn = 0;
					m_SpawnCount++;
				}
			}
			else
			{
				m_SpawnAnim = false;
			}
		}
		else
		{
			m_AnimTimeSpawn += elapsedSec;
			if (m_AnimTimeSpawn >= m_WaitSecToSpawn)
			{
				m_HaveWaitedToSpawn = true;
				m_AnimTimeSpawn = 0;
			}
		}
	}

	if (!m_Pop)
	{
		m_AnimTime += elapsedSec;
		if (m_AnimTime >= 1.0f / m_NrFramesPerSec)
		{
			m_AnimFrame = (m_AnimFrame + 1) % (m_NrOfFrames);
			m_AnimTime = 0;
		}
	}
	else
	{
		m_AnimTime += elapsedSec;
		if (m_AnimTime >= 1.0f / m_PopSpeed)
		{
			m_AnimFrame = (m_AnimFrame + 1) % (m_NrOfFrames / 2);
			m_AnimTime = 0;
		}

		if (m_AnimFrame == 1)
		{
			m_PopAnimDone = true;
		}
	}
}

void Bubble::Pop()
{
	m_Pop = true;
}

bool Bubble::IsPopDone() const
{
	return m_PopAnimDone;
}

bool Bubble::IsOverlapping(const Rectf& rect) const
{
	return utils::IsOverlapping(rect, m_Shape);
}

const Circlef& Bubble::GetShape() const
{
	return m_Shape;
}

const Point2f& Bubble::GetSpawnCenter() const
{
	return m_SpawnCenter;
}

const int& Bubble::GetSpawnOffset() const
{
	return m_YSpawnOffset;
}