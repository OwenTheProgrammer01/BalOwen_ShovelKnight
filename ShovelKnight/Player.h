#pragma once
#include "Vector2f.h"
#include "Level.h"
#include "PlatformManager.h"
#include "DirtBlockManager.h"
#include "SoundEffect.h"

class Player
{
public:
	Player();
	~Player();
	void Update(float elapsedSec, Level& level, PlatformManager& platformManager, const DirtBlockManager& dirtBlockManager);
	void Draw() const;
	const Rectf& GetShape() const;
	const float& GetHealth() const;
	const bool& GetIsAttacking() const;
	const Rectf& GetHitbox() const;
	
	void CheckState(const Level& level, const PlatformManager& platformManager, const DirtBlockManager& dirtBlockManager);
	void HandleMovement(float elapsedSec, const Level& level, const PlatformManager& platformManager, const DirtBlockManager& dirtBlockManager);
	void HandleCollisions(const Level& level, const PlatformManager& platformManager, const DirtBlockManager& dirtBlockManager, float elapsedSec);

	void Animation(float elapsedSec);
	void LevelChangeAnimation(const Point2f& speed, float elapsedSec);

	void HitBubble();
	void HitDirtBlock();
	void HitBeeto();

	bool IsAttack() const;
	bool IsDownAttack() const;
	bool IsClimbAttack() const;

	void Damage();
	void Protection(float elapsedSec);
	void Die();
	bool Respawn();

private:
	SoundEffect m_SBubbleBounce;
	SoundEffect m_SDie;
	SoundEffect m_SDig;
	SoundEffect m_SDamage;
	SoundEffect m_SJump;
	SoundEffect m_SLand;
	SoundEffect m_SShovel;
	SoundEffect m_SRockBounce;
	SoundEffect m_SRockShovel;

	Point2f m_SpawnLoc;
	Rectf m_Shape;
	Rectf m_Hitbox;
	const float m_HorSpeed;
	const float m_VerSpeed;
	const float m_JumpSpeed;
	Vector2f m_Velocity;
	Vector2f m_Acceleration;
	float m_Health;
	bool m_CanDamage;
	float m_ProtectionTimer;
	enum class ActionState
	{
		Idle,
		Running,
		Jumping,
		Climbing,
		FallDownAttack,
		NormalAttack,
		ClimbAttack,
		Damage,
		Die,
		Respawn
	};
	ActionState m_ActionState;
	const Texture* m_pPlayer;
	float m_ClipWidth;
	float m_ClipHeight;
	int m_NrOfFrames;
	int m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrameX;
	int m_AnimFrameY;
	bool m_IsLookingLeft;
	bool m_IsClimbing;
	bool m_IsMoving;
	bool m_IsAttacking;
	const float m_SpriteOffsetX;
	const float m_SpriteOffsetY;
	ActionState m_LastActionState; // DEBUG ONLY
	bool m_TESTMODE{ false }; // DEBUG ONLY
};
