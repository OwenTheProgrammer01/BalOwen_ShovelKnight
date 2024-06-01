#pragma once
#include "Vector2f.h"

class Level;
class Texture;

class Beeto final
{
public:
	explicit Beeto(const Point2f& spawnPos, const Point2f& p1, const Point2f& p2, const bool& isLookingLeft);
	~Beeto();

	void Update(float elapsedSec);
	void Draw() const;
	void Animation(float elapsedSec);
	void DeathAnimation(float elapsedSec);

	void Hit(const bool& doDamage);
	bool IsDeathAnimDone() const;

	void SetDeath();

	bool IsOverlapping(const Rectf& rect) const;
	const bool& GetIsHit() const;
	const Rectf& GetShape() const;

	void HandleCollision(const Level& level);
	void HandleMovement(float elapsedSec);

private:
	Texture* m_pBeeto;
	Point2f m_P1Trail;
	Point2f m_P2Trail;
	Vector2f m_Speed;
	Vector2f m_Acceleration;
	float m_ClipWidth;
	float m_ClipHeight;
	Rectf m_Shape;
	int m_NrOfFrames;
	int m_NrFramesPerSec;
	float m_AnimTime;
	float m_DeathAnimTime;
	int m_AnimFrameX;
	int m_AnimFrameY;
	bool m_IsLookingLeft;
	bool m_IsHit;
	bool m_DeathAnimDone;
	int m_CountDeathAnim;
};