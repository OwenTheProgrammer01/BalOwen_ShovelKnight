#include "pch.h"
#include "SpikesAndFallPitsManager.h"
#include <vector>

SpikesAndFallPitsManager::SpikesAndFallPitsManager()
	: m_pItems{ }
{

}

SpikesAndFallPitsManager::~SpikesAndFallPitsManager()
{
	for (int index{ }; index < Size(); ++index)
	{
		delete m_pItems[index];
		m_pItems[index] = nullptr;
	}
}

void SpikesAndFallPitsManager::Draw() const
{
	for (int index{ }; index < Size(); ++index)
	{
		m_pItems[index]->Draw();
	}
}

SpikesAndFallPits* SpikesAndFallPitsManager::AddItem(const Rectf& shape)
{
	SpikesAndFallPits* spikesAndFallPits = new SpikesAndFallPits{ shape };
	m_pItems.push_back(spikesAndFallPits);
	return spikesAndFallPits;
}

size_t SpikesAndFallPitsManager::Size() const
{
	return m_pItems.size();
}

bool SpikesAndFallPitsManager::HitItem(const Rectf& rect)
{
	for (int index{ (int)Size() - 1 }; index >= 0; --index)
	{
		if (m_pItems[index]->IsOverlapping(rect))
		{
			return true;
		}
	}
	return false;
}