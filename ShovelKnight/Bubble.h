#pragma once
class Texture;

class Bubble final
{
public:
	explicit Bubble(const Point2f& center, int ySpawnOffset);
	~Bubble();

	void Update(float elapsedSec);
	void Draw() const;
	void Animation(float elapsedSec);
	void Pop();
	bool IsPopDone() const;
	bool IsOverlapping(const Rectf& rect) const;
	const Circlef& GetShape() const;
	const Point2f& GetSpawnCenter() const;
	const int& GetSpawnOffset() const;

private:
	Texture* m_pBubble;
	Texture* m_pBubblePop;
	Point2f m_SpawnCenter;
	int m_YSpawnOffset;
	Circlef m_Shape;
	Circlef m_ShapePop;
	float m_ClipWidth;
	float m_ClipHeight;
	float m_ClipWidthPop;
	int m_NrOfFrames;
	int m_NrFramesPerSec;
	int m_PopSpeed;
	float m_AnimTime;
	int m_AnimFrame;
	bool m_Pop;
	bool m_PopAnimDone;
	bool m_SpawnAnim;
	int m_SpawnCount;
	float m_AnimTimeSpawn;
	float m_WaitSecToSpawn;
	bool m_HaveWaitedToSpawn;
};