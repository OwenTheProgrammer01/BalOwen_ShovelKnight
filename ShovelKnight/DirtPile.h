#pragma once
#include "utils.h"
class Texture;

class DirtPile final
{
public:
	explicit DirtPile(const Point2f& spawnPos);
	~DirtPile();

	void Update(float elapsedSec);
	void Draw() const;
	void Hit();
	void ResetIsHitable();
	bool IsOverlapping(const Rectf& rect) const;
	const Rectf& GetShape() const;
	const int& GetHit() const;

private:
	Texture* m_pDirtPile;
	float m_ClipWidth;
	float m_ClipHeight;
	Rectf m_Shape;
	int m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;
	int m_Hit;
	bool m_IsHitable;
};