#include "pch.h"
#include "DirtPileManager.h"
#include <vector>

DirtPileManager::DirtPileManager()
	: m_pDirtPile{ }
{

}

DirtPileManager::~DirtPileManager()
{
	for (int index{ }; index < Size(); ++index)
	{
		delete m_pDirtPile[index];
		m_pDirtPile[index] = nullptr;
	}
}

DirtPile* DirtPileManager::AddItem(const Point2f& spawnPos)
{
	DirtPile* dirtPile = new DirtPile{ spawnPos };
	m_pDirtPile.push_back(dirtPile);
	return dirtPile;
}

void DirtPileManager::Update(float elapsedSec)
{
	for (int index{ }; index < Size(); ++index)
	{
		m_pDirtPile[index]->Update(elapsedSec);
	}
}

void DirtPileManager::Draw() const
{
	for (int index{ }; index < Size(); ++index)
	{
		m_pDirtPile[index]->Draw();
	}
}

void DirtPileManager::ResetIsHitable()
{
	for (int index{ (int)Size() - 1 }; index >= 0; --index)
	{
		m_pDirtPile[index]->ResetIsHitable();
	}
}

size_t DirtPileManager::Size() const
{
	return m_pDirtPile.size();
}

bool DirtPileManager::HitItem(const Rectf& rect)
{
	for (int index{ (int)Size() - 1 }; index >= 0; --index)
	{
		if (m_pDirtPile[index]->IsOverlapping(rect))
		{
			m_pDirtPile[index]->Hit();
			DeleteItem();
			return true;
		}
	}
	return false;
}

void DirtPileManager::DeleteItem()
{
	for (int index{ }; index < Size(); ++index)
	{
		if (m_pDirtPile[index]->GetHit() == 5)
		{
			delete m_pDirtPile[index];
			m_pDirtPile[index] = m_pDirtPile[Size() - 1];
			m_pDirtPile.pop_back();
		}
	}
}