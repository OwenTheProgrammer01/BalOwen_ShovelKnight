#include "pch.h"
#include "DirtBlockManager.h"
#include <vector>

DirtBlockManager::DirtBlockManager()
	: m_pDirtBlock{ }
{

}

DirtBlockManager::~DirtBlockManager()
{
	for (int index{ }; index < Size(); ++index)
	{
		delete m_pDirtBlock[index];
		m_pDirtBlock[index] = nullptr;
	}
}

DirtBlock* DirtBlockManager::AddItem(const Point2f& spawnPos, const bool& isBigRock)
{
	DirtBlock* dirtBlock = new DirtBlock{ spawnPos, isBigRock };
	m_pDirtBlock.push_back(dirtBlock);
	return dirtBlock;
}

void DirtBlockManager::Update(float elapsedSec)
{
	for (int index{ }; index < Size(); ++index)
	{
		m_pDirtBlock[index]->Update(elapsedSec);
	}
	PopHitItem();
}

void DirtBlockManager::Draw() const
{
	for (int index{ }; index < Size(); ++index)
	{
		m_pDirtBlock[index]->Draw();
	}
}

size_t DirtBlockManager::Size() const
{
	return m_pDirtBlock.size();
}

bool DirtBlockManager::HitItem(const Rectf& rect)
{
	for (int index{ (int)Size() - 1 }; index >= 0; --index)
	{
		if (m_pDirtBlock[index]->IsOverlapping(rect))
		{
			m_pDirtBlock[index]->Pop();
			return true;
		}
	}
	return false;
}

void DirtBlockManager::PopHitItem()
{
	for (int index{ }; index < Size(); ++index)
	{
		if (m_pDirtBlock[index]->GetIsPop())
		{
			if (m_pDirtBlock[index]->IsPopDone())
			{

				delete m_pDirtBlock[index];
				m_pDirtBlock[index] = m_pDirtBlock[Size() - 1];
				m_pDirtBlock.pop_back();
			}
		}
	}
}

void DirtBlockManager::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity, const bool& isLookingLeft, float elapsedSec) const
{
	for (int index{ }; index < Size(); ++index)
	{
		m_pDirtBlock[index]->HandleCollision(actorShape, actorVelocity, isLookingLeft, elapsedSec);
	}
}

bool DirtBlockManager::IsOnBlock(const Rectf& actorShape) const
{
	for (int index{ (int)Size() - 1 }; index >= 0; --index)
	{
		if (m_pDirtBlock[index]->IsOnBlock(actorShape))
		{
			return true;
		}
	}
	return false;
}