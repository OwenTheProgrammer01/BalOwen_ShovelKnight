#pragma once
#include "SpikesAndFallPits.h"
#include <vector>
#include "structs.h"

class SpikesAndFallPitsManager final
{
public:
	SpikesAndFallPitsManager();
	~SpikesAndFallPitsManager();
	SpikesAndFallPitsManager(const SpikesAndFallPitsManager&) = delete;
	SpikesAndFallPitsManager& operator=(const SpikesAndFallPitsManager&) = delete;
	SpikesAndFallPitsManager(SpikesAndFallPitsManager&&) = delete;
	SpikesAndFallPitsManager& operator=(SpikesAndFallPitsManager&&) = delete;

	void Draw() const;

	SpikesAndFallPits* AddItem(const Rectf& shape);

	size_t Size() const;
	bool HitItem(const Rectf& rect);

private:
	std::vector<SpikesAndFallPits*> m_pItems;
};