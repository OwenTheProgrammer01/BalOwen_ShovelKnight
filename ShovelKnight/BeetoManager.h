#pragma once
#include "Beeto.h"
#include "structs.h"
#include <vector>

class BeetoManager final
{
public:
	BeetoManager();
	~BeetoManager();
	BeetoManager(const BeetoManager&) = delete;
	BeetoManager& operator=(const BeetoManager&) = delete;
	BeetoManager(BeetoManager&&) = delete;
	BeetoManager& operator=(BeetoManager&&) = delete;

	Beeto* AddItem(const Point2f& spawnPos, const Point2f& p1, const Point2f& p2, const bool& isLookingLeft);
	void Update(float elapsedSec);
	void Draw() const;
	void DeleteItem();

	void HandleCollisions(const Level& level);

	size_t Size() const;
	bool HitItem(const Rectf& rect, const bool& isHitbox);

private:
	std::vector<Beeto*> m_pBeeto;
};