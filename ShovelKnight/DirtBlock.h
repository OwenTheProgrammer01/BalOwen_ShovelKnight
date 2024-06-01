 #pragma once
#include "utils.h"
class Texture;
class DirtBlock final
{
public:
	explicit DirtBlock(const Point2f& spawnPos, const bool& isBigRock);
	~DirtBlock();

	void Update(float elapsedSec);
	void Draw() const;
	void PopAnimation(float elapsedSec);
	void Pop();
	bool IsPopDone() const;
	bool IsOverlapping(const Rectf& rect) const;
	const Rectf& GetShape() const;
	const bool& GetIsPop() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity, const bool& isLookingLeft, float elapsedSec) const;
	bool IsOnBlock(const Rectf& actorShape) const;

private:
	Texture* m_pDirtBlockBig;
	Texture* m_pDirtBlockBigPop;
	Texture* m_pDirtBlockSmall;
	Texture* m_pDirtBlockSmallPop;
	Rectf m_Shape;
	bool m_IsBigRock;
	float m_ClipWidthBigPop;
	float m_ClipWidthSmallPop;
	int m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;
	bool m_Pop;
	bool m_PopAnimDone;
	std::vector<std::vector<Point2f>> m_Vertices;
};