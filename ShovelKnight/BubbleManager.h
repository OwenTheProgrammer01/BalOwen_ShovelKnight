#pragma once
#include "Bubble.h"
#include <vector>
#include "structs.h"

class BubbleManager final
{
public:
	BubbleManager();
	~BubbleManager();
	BubbleManager(const BubbleManager&) = delete;
	BubbleManager& operator=(const BubbleManager&) = delete;
	BubbleManager(BubbleManager&&) = delete;
	BubbleManager& operator=(BubbleManager&&) = delete;

	Bubble* AddItem(const Point2f& center, int ySpawnOffset);
	void Update(float elapsedSec);
	void Draw() const;

	size_t Size() const;
	bool HitItem(const Rectf& rect);
	const bool& GetIsHit() const;
	void PopHitItem();

private:
	std::vector<Bubble*> m_pBubbles;
	int m_ItemHit;
	bool m_IsHit;
};