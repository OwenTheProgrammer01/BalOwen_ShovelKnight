#pragma once
#include "Platform.h"
#include <vector>
#include "structs.h"
class PlatformManager final
{
public:
	PlatformManager();
	~PlatformManager();
	PlatformManager(const PlatformManager&) = delete;
	PlatformManager& operator=(const PlatformManager&) = delete;
	PlatformManager(PlatformManager&&) = delete;
	PlatformManager& operator=(PlatformManager&&) = delete;

	Platform* AddItem(const Point2f& bottomLeft, const Point2f& p1, const Point2f& p2, const bool& isHorizontal, const float speed);
	void Update(float elapsedSec);
	void Draw() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity, const bool& isLookingLeft, float elapsedSec) const;
	bool IsOnPlatform(const Rectf& actorShape) const;

	size_t Size() const;

private:
	std::vector<Platform*> m_pItems;
};