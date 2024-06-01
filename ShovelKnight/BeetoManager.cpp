#include "pch.h"
#include "BeetoManager.h"
#include <vector>

BeetoManager::BeetoManager()
	: m_pBeeto{ }
{

}

BeetoManager::~BeetoManager()
{
	for (int index{ }; index < Size(); ++index)
	{
		delete m_pBeeto[index];
		m_pBeeto[index] = nullptr;
	}
}

Beeto* BeetoManager::AddItem(const Point2f& spawnPos, const Point2f& p1, const Point2f& p2, const bool& isLookingLeft)
{
	Beeto* beeto = new Beeto{ spawnPos, p1, p2, isLookingLeft };
	m_pBeeto.push_back(beeto);
	return beeto;
}

void BeetoManager::Update(float elapsedSec)
{
	for (int index{ }; index < Size(); ++index)
	{
		m_pBeeto[index]->Update(elapsedSec);
	}
	DeleteItem();
}

void BeetoManager::Draw() const
{
	for (int index{ }; index < Size(); ++index)
	{
		m_pBeeto[index]->Draw();
	}
}

size_t BeetoManager::Size() const
{
	return m_pBeeto.size();
}

bool BeetoManager::HitItem(const Rectf& rect, const bool& isHitbox)
{
	if (isHitbox)
	{
		for (int index{ (int)Size() - 1 }; index >= 0; --index)
		{
			if (m_pBeeto[index]->IsOverlapping(rect))
			{
				m_pBeeto[index]->Hit(false);
				return true;
			}
		}
	}
	else
	{
		for (int index{ (int)Size() - 1 }; index >= 0; --index)
		{
			if (m_pBeeto[index]->IsOverlapping(rect) && !m_pBeeto[index]->GetIsHit())
			{
				m_pBeeto[index]->Hit(true);
				return true;
			}
		}
	}
	return false;
}

void BeetoManager::DeleteItem()
{
	for (int index{ }; index < Size(); ++index)
	{
		if (m_pBeeto[index]->GetIsHit())
		{
			if (m_pBeeto[index]->IsDeathAnimDone())
			{
				delete m_pBeeto[index];
				m_pBeeto[index] = m_pBeeto[Size() - 1];
				m_pBeeto.pop_back();
			}
		}
	}
}

void BeetoManager::HandleCollisions(const Level& level)
{
	for (int index{ }; index < Size(); ++index)
	{
		m_pBeeto[index]->HandleCollision(level);
	}
}