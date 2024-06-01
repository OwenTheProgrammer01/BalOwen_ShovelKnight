#pragma once
#include "utils.h"

class Player;
class Ladder;
class Texture;

class Level
{
public:
	Level();
	~Level();
	void SetLevelBoundaries();
	void CreateLadders();
	void DrawBackground() const;
	void DrawMiddleGround() const;
	void DrawForeground() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity, const bool& isLookingLeft, const bool& isClimbing) const;
	bool IsOnGround(const Rectf& actorShape) const;
	bool IsOnLadder(const Rectf& actorShape) const;
	const Rectf& GetLadder(const Rectf& actorShape) const;
	const Rectf& GetBoundaries() const;
	const int& GetLevelPart() const;
	void ChangeLevelPart(Player& player, float elapsedSec);
	void LevelAnimation(Player& player, float elapsedSec);
	void AnimLeft(const Rectf& actorShape, int changeLevelPartWith);
	void AnimRight(const Rectf& actorShape, int changeLevelPartWith);
	void AnimUp(const Rectf& actorShape, int changeLevelPartWith);
	void AnimDown(const Rectf& actorShape, int changeLevelPartWith);

private:
	std::vector<std::vector<Point2f>> m_Vertices;
	Texture* m_pBackground1Texture;
	Texture* m_pBackground2Texture;
	Texture* m_pBackground3Texture;
	Texture* m_pCastleTexture;
	Texture* m_pCloudsTexture;
	Texture* m_pLevelL1Texture;
	Texture* m_pLevelL2Texture;
	Texture* m_pLevelL3Texture;
	int m_LevelPart;
	Rectf m_Boundaries;
	enum class Animation
	{
		None,
		Left,
		Right,
		Up,
		Down
	};
	Animation m_Animation;
	bool m_IsAnimating;
	std::vector<Ladder> m_Ladders;
	std::vector<Rectf> m_LevelBoundaries;
};