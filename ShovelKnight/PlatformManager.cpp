#include "pch.h"
#include "PlatformManager.h"
#include <vector>

PlatformManager::PlatformManager()
	: m_pItems{ }
{

}

PlatformManager::~PlatformManager()
{
	for (int index{ }; index < Size(); ++index)
	{
		delete m_pItems[index];
		m_pItems[index] = nullptr;
	}
}

Platform* PlatformManager::AddItem(const Point2f& bottomLeft, const Point2f& p1, const Point2f& p2, const bool& isHorizontal, const float speed)
{
	Platform* platform = new Platform{ bottomLeft, p1, p2, isHorizontal, speed };
	m_pItems.push_back(platform);
	return platform;
}

void PlatformManager::Update(float elapsedSec)
{
	for (int index{ }; index < Size(); ++index)
	{
		m_pItems[index]->Update(elapsedSec);
	}
}

void PlatformManager::Draw() const
{
	for (int index{ }; index < Size(); ++index)
	{
		m_pItems[index]->Draw();
	}
}

void PlatformManager::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity, const bool& isLookingLeft, float elapsedSec) const
{
	for (int index{ }; index < Size(); ++index)
	{
		m_pItems[index]->HandleCollision(actorShape, actorVelocity, isLookingLeft, elapsedSec);
	}
}

bool PlatformManager::IsOnPlatform(const Rectf& actorShape) const
{
	for (int index{ }; index < Size(); ++index)
	{
		if (m_pItems[index]->IsOnPlatform(actorShape))
		{
			return true;
		}
	}
	return false;
}

size_t PlatformManager::Size() const
{
	return m_pItems.size();
}