#include "pch.h"
#include "BubbleManager.h"
#include <vector>

BubbleManager::BubbleManager()
	: m_pBubbles{},
	m_ItemHit{ },
	m_IsHit{ false }
{

}

BubbleManager::~BubbleManager()
{
	for (int index{ }; index < Size(); ++index)
	{
		delete m_pBubbles[index];
		m_pBubbles[index] = nullptr;
	}
}

Bubble* BubbleManager::AddItem(const Point2f& center, int ySpawnOffset)
{
	Bubble* bubble = new Bubble{ center, ySpawnOffset };
	m_pBubbles.push_back(bubble);
	return bubble;
}

void BubbleManager::Update(float elapsedSec)
{
	for (int index{ }; index < Size(); ++index)
	{
		m_pBubbles[index]->Update(elapsedSec);
	}
}

void BubbleManager::Draw() const
{
	for (int index{ }; index < Size(); ++index)
	{
		m_pBubbles[index]->Draw();
	}
}

size_t BubbleManager::Size() const
{
	return m_pBubbles.size();
}

bool BubbleManager::HitItem(const Rectf& rect)
{
	for (int index{ (int)Size() - 1 }; index >= 0; --index)
	{
		if (m_pBubbles[index]->IsOverlapping(rect))
		{
			m_ItemHit = index;
			m_IsHit = true;
			return true;
		}
	}
	return false;
}

const bool& BubbleManager::GetIsHit() const
{
	return m_IsHit;
}

void BubbleManager::PopHitItem()
{
	m_pBubbles[m_ItemHit]->Pop();
	if (m_pBubbles[m_ItemHit]->IsPopDone())
	{
		AddItem(m_pBubbles[m_ItemHit]->GetSpawnCenter(), m_pBubbles[m_ItemHit]->GetSpawnOffset());
		delete m_pBubbles[m_ItemHit];
		m_pBubbles[m_ItemHit] = m_pBubbles[Size() - 1];
		m_pBubbles.pop_back();
		m_IsHit = false;
	}
}