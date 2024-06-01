#pragma once
class SpikesAndFallPits final
{
public:
	explicit SpikesAndFallPits(const Rectf& shape);
	~SpikesAndFallPits();

	void Draw() const;

	bool IsOverlapping(const Rectf& rect) const;
	const Rectf& GetShape() const;

private:
	Rectf m_Shape;
};