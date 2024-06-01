#pragma once
class Camera
{
public:
	Camera(float width, float height);
	~Camera();
	void SetLevelBoundaries(const Rectf& levelBoundaries);
	void Transform(const Rectf& target) const;
	Point2f Track(const Rectf& target) const;
	void Clamp(Point2f& bottomLeftPos) const;
	void Zoom(const float zoom);

private:
	float m_Width{};
	float m_Height{};
	Rectf m_LevelBoundaries{};
};