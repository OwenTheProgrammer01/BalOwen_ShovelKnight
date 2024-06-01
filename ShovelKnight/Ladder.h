#pragma once
#include "utils.h"
class Texture;

class Ladder
{
public:
	Ladder(const Rectf& Shape);
	~Ladder();
	void Draw() const;
	const Rectf& GetShape() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity, const bool& isClimbing) const;
	bool IsOnGround(const Rectf& actorShape) const;

private:
	Rectf m_Shape;
	std::vector<std::vector<Point2f>> m_Vertices;
};