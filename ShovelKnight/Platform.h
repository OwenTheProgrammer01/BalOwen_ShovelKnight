#pragma once
#include "utils.h"
class Texture;
class Platform
{
public:
	Platform(const Point2f& bottomLeft, const Point2f& p1, const Point2f& p2, const bool& isHorizontal, const float speed);
	~Platform();
	void Update(float elapsedSec);
	void Draw() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity, const bool& isLookingLeft, float elapsedSec) const;
	bool IsOnPlatform(const Rectf& actorShape) const;

private:
	Texture* m_pPlatform;
	Point2f m_BottomLeft;
	Point2f m_P1Trail;
	Point2f m_P2Trail;
	Point2f m_P1Collision;
	Point2f m_P2Collision;
	float m_PlatformSpeed;
	bool m_Direction;
	bool m_IsHorizontal;
	std::vector<std::vector<Point2f>> m_Vertices;
};