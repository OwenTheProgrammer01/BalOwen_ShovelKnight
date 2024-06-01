#pragma once
#include "DirtPile.h"
#include "structs.h"
#include <vector>

class DirtPileManager final
{
public:
	DirtPileManager();
	~DirtPileManager();
	DirtPileManager(const DirtPileManager&) = delete;
	DirtPileManager& operator=(const DirtPileManager&) = delete;
	DirtPileManager(DirtPileManager&&) = delete;
	DirtPileManager& operator=(DirtPileManager&&) = delete;

	DirtPile* AddItem(const Point2f& spawnPos);
	void Update(float elapsedSec);
	void Draw() const;
	void ResetIsHitable();
	void DeleteItem();

	size_t Size() const;
	bool HitItem(const Rectf& rect);

private:
	std::vector<DirtPile*> m_pDirtPile;
};