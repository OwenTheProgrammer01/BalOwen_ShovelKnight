#pragma once
class Texture;

class HUD
{
public:
	HUD();
	~HUD();
	
	void Draw(const float& health) const;

private:
	Rectf m_Shape;
	const Texture* m_pHealthTexture;
	Point2f m_HealthPos;
	float m_TotalHealth;
};