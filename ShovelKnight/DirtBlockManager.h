#pragma once
#include "DirtBlock.h"
#include "structs.h"
#include <vector>

class DirtBlockManager final
{
public:
	DirtBlockManager();
	~DirtBlockManager();
	DirtBlockManager(const DirtBlockManager&) = delete;
	DirtBlockManager& operator=(const DirtBlockManager&) = delete;
	DirtBlockManager(DirtBlockManager&&) = delete;
	DirtBlockManager& operator=(DirtBlockManager&&) = delete;

	DirtBlock* AddItem(const Point2f& spawnPos, const bool& isBigRock);
	void Update(float elapsedSec);
	void Draw() const;

	size_t Size() const;
	bool HitItem(const Rectf& rect);
	void PopHitItem();

	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity, const bool& isLookingLeft, float elapsedSec) const;
	bool IsOnBlock(const Rectf& actorShape) const;

private:
	std::vector<DirtBlock*> m_pDirtBlock;
};