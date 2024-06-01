#include "pch.h"
#include "Player.h"
#include "Texture.h"
#include <iostream>

Player::Player()
	: m_SBubbleBounce{ "Sounds/Hero_Bounce.wav" },
	m_SDie{ "Sounds/Hero_Die.wav" },
	m_SDig{ "Sounds/Hero_Dig.wav" },
	m_SDamage{ "Sounds/Hero_Dmg.wav" },
	m_SJump{ "Sounds/Hero_Jump.wav" },
	m_SLand{ "Sounds/Hero_Land.wav" },
	m_SShovel{ "Sounds/Hero_Shovel.wav" },
	m_SRockBounce{ "Sounds/RockBounce.wav" },
	m_SRockShovel{ "Sounds/RockShovel.wav" },
	m_SpawnLoc { 112, 480 },
	m_Shape{ m_SpawnLoc.x, m_SpawnLoc.y, 14, 28 },
	m_Hitbox{ m_Shape.left + m_Shape.width / 2, m_Shape.bottom + m_Shape.height / 2, 0, 0 },
	m_HorSpeed{ 100.0f },
	m_VerSpeed{ 75.0f },
	m_JumpSpeed{ 370.0f },
	m_Velocity{ 0.0f, 0.0f },
	m_Acceleration{ 0, -981.0f },
	m_Health { 8.0f },
	m_CanDamage{ true },
	m_ProtectionTimer{ 0 },
	m_ActionState{ ActionState::Running },
	m_pPlayer{ new Texture("Images/ShovelKnight.png") },
	m_ClipWidth{ 60.0f },
	m_ClipHeight{ 51.0f },
	m_NrOfFrames{ 9 },
	m_NrFramesPerSec{ 12 },
	m_AnimTime{ 0 },
	m_AnimFrameX{ 0 },
	m_AnimFrameY{ 0 },
	m_IsLookingLeft{ false },
	m_IsClimbing{ false },
	m_IsMoving{ false },
	m_IsAttacking{ false },
	m_SpriteOffsetX{ 12 },
	m_SpriteOffsetY{ 3 },
	m_LastActionState{ ActionState::Running } // DEBUG ONLY
{

}

Player::~Player()
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void Player::Update(float elapsedSec, Level& level, PlatformManager& platformManager, const DirtBlockManager& dirtBlockManager)
{
	/* ------------------- */
	// TESTMODE : For fast moving in level (without collisions).
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_T])
	{
		m_TESTMODE = true;
	}

	if (pStates[SDL_SCANCODE_R])
	{
		m_TESTMODE = false;
	}

	// TESTMODE
	if (m_TESTMODE)
	{
		m_Velocity.x = 0;
		if (pStates[SDL_SCANCODE_D])
		{
			m_Velocity.x = 600;
		}
		if (pStates[SDL_SCANCODE_A])
		{
			m_Velocity.x = -600;
		}
		m_Velocity.y = 0;
		if (pStates[SDL_SCANCODE_W])
		{
			m_Velocity.y = 600;
		}
		if (pStates[SDL_SCANCODE_S])
		{
			m_Velocity.y = -600;
		}
		m_Shape.left += m_Velocity.x * elapsedSec;
		m_Shape.bottom += m_Velocity.y * elapsedSec;
	}
	/* ------------------- */
	// NORMAL CODE
	else
	{
		CheckState(level, platformManager, dirtBlockManager);
		HandleMovement(elapsedSec, level, platformManager, dirtBlockManager);
		HandleCollisions(level, platformManager, dirtBlockManager, elapsedSec);
		Animation(elapsedSec);
		Protection(elapsedSec);
	}

	// DEBUGGING
	//std::cout << "Health: " << m_Health << "\n";

	// DEBUGGING
	/*if (m_ActionState != m_LastActionState)
	{
		switch (m_ActionState)
		{
		case ActionState::Idle:
			std::cout << "State: Idle\n";
			m_LastActionState = m_ActionState;
			break;
		case ActionState::Running:
			std::cout << "State: Running\n";
			m_LastActionState = m_ActionState;
			break;
		case ActionState::Jumping:
			std::cout << "State: Jumping\n";
			m_LastActionState = m_ActionState;
			break;
		}
	}*/
}

void Player::Draw() const
{
	glPushMatrix();
	{
		glTranslatef(
			m_Shape.left - m_SpriteOffsetX,
			m_Shape.bottom - m_SpriteOffsetY,
			0.0f
		);
		if (m_IsLookingLeft)
		{
			glScalef(-1, 1, 1);
			glTranslatef(
				-m_Shape.width - m_SpriteOffsetX * 2,
				0.0f,
				0.0f
			);
		}
		m_pPlayer->Draw(Point2f(),
				Rectf(m_ClipWidth * m_AnimFrameX,
				m_ClipHeight * m_AnimFrameY,
				m_ClipWidth,
				m_ClipHeight)
		);
	}
	glPopMatrix();

	// DEBUGGING
	//utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	//utils::DrawRect(m_Shape);

	//utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	//utils::DrawRect(m_Hitbox);
}

const Rectf& Player::GetShape() const
{
	return m_Shape;
}

const float& Player::GetHealth() const
{
	return m_Health;
}

const bool& Player::GetIsAttacking() const
{
	return m_IsAttacking;
}

const Rectf& Player::GetHitbox() const
{
	return m_Hitbox;
}

void Player::CheckState(const Level& level, const PlatformManager& platformManager, const DirtBlockManager& dirtBlockManager)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	const bool isOnGround{ level.IsOnGround(m_Shape) || platformManager.IsOnPlatform(m_Shape) || dirtBlockManager.IsOnBlock(m_Shape) };
	const bool isOnLadder{ level.IsOnLadder(m_Shape) };
	const bool isMoving{ pStates[SDL_SCANCODE_A] ||	pStates[SDL_SCANCODE_D]	};

	if (m_Velocity.x != 0)
	{
		m_IsMoving = true;
	}
	else
	{
		m_IsMoving = false;
	}

	switch (m_ActionState)
	{
	case ActionState::Idle:
		m_Hitbox = Rectf{ m_Shape.left + m_Shape.width / 2, m_Shape.bottom + m_Shape.height / 2, 0, 0 };
		m_Velocity.x = 0;
		if (isOnGround && isMoving)
		{
			m_AnimFrameX = 0;
			m_ActionState = ActionState::Running;
			break;
		}
		if (!isOnGround)
		{
			m_AnimFrameX = 0;
			m_SJump.Play(false);
			m_ActionState = ActionState::Jumping;
			break;
		}
		if (pStates[SDL_SCANCODE_J])
		{
			m_AnimFrameX = 0;
			m_SShovel.Play(false);
			m_ActionState = ActionState::NormalAttack;
			break;
		}
		break;
	case ActionState::Running:
		m_Hitbox = Rectf{ m_Shape.left + m_Shape.width / 2, m_Shape.bottom + m_Shape.height / 2, 0, 0 };
		if (isOnGround && (!isMoving && !m_IsMoving))
		{
			m_AnimFrameX = 0;
			m_ActionState = ActionState::Idle;
			break;
		}
		if (!isOnGround)
		{
			m_AnimFrameX = 0;
			m_SJump.Play(false);
			m_ActionState = ActionState::Jumping;
			break;
		}
		if (pStates[SDL_SCANCODE_J])
		{
			m_AnimFrameX = 0;
			m_SShovel.Play(false);
			m_ActionState = ActionState::NormalAttack;
			break;
		}
		break;
	case ActionState::Jumping:
		m_Hitbox = Rectf{ m_Shape.left + m_Shape.width / 2, m_Shape.bottom + m_Shape.height / 2, 0, 0 };
		if (isOnGround && isMoving)
		{
			m_AnimFrameX = 0;
			m_ActionState = ActionState::Running;
			break;
		}
		if (isOnGround)
		{
			m_AnimFrameX = 0;
			m_ActionState = ActionState::Idle;
			break;
		}
		if (pStates[SDL_SCANCODE_J])
		{
			m_AnimFrameX = 0;
			m_SShovel.Play(false);
			m_ActionState = ActionState::NormalAttack;
			break;
		}
		if (pStates[SDL_SCANCODE_S])
		{
			m_AnimFrameX = 0;
			m_ActionState = ActionState::FallDownAttack;
			break;
		}
		break;
	case ActionState::FallDownAttack:
		m_Hitbox = Rectf{ m_Shape.left + 2, m_Shape.bottom - 2, m_Shape.width - 4, 10 };
		if (level.IsOnGround(m_Shape) || platformManager.IsOnPlatform(m_Shape))
		{
			m_AnimFrameX = 0;
			m_ActionState = ActionState::Idle;
			break;
		}
		if (pStates[SDL_SCANCODE_J])
		{
			m_AnimFrameX = 0;
			m_SShovel.Play(false);
			m_ActionState = ActionState::NormalAttack;
			break;
		}
		break;
	case ActionState::NormalAttack:
		if (m_IsLookingLeft)
		{
			m_Hitbox = Rectf{ m_Shape.left - 30, m_Shape.bottom + 1, 25, m_Shape.height / 2 };
		}

		if (!m_IsLookingLeft)
		{
			m_Hitbox = Rectf{ m_Shape.left + m_Shape.width + 5, m_Shape.bottom + 1, 25, m_Shape.height / 2 };
		}

		if (m_AnimFrameX == 5)
		{
			m_AnimFrameX = 0;
			if (!pStates[SDL_SCANCODE_J])
			{
				m_ActionState = ActionState::Jumping;
			}
			break;
		}
		break;
	case ActionState::Climbing:
		m_Hitbox = Rectf{ m_Shape.left + m_Shape.width / 2, m_Shape.bottom + m_Shape.height / 2, 0, 0 };
		m_IsClimbing = true;
		if (!isOnLadder)
		{
			m_ActionState = ActionState::Running;
		}

		if (pStates[SDL_SCANCODE_J])
		{
			m_AnimFrameX = 0;
			m_SShovel.Play(false);
			m_ActionState = ActionState::ClimbAttack;
		}
		break;
	case ActionState::ClimbAttack:
		m_Hitbox = Rectf{ m_Shape.left + m_Shape.width / 2, m_Shape.bottom + m_Shape.height / 2, 0, 0 };
		m_IsClimbing = true;
		break;
	case ActionState::Damage:
		m_CanDamage = false;
		break;
	case ActionState::Die:
		m_Hitbox = Rectf{ m_Shape.left + m_Shape.width / 2, m_Shape.bottom + m_Shape.height / 2, 0, 0 };
		break;
	}

	if (m_ActionState != ActionState::Climbing && m_ActionState != ActionState::ClimbAttack)
	{
		m_IsClimbing = false;
	}

	if (m_ActionState == ActionState::NormalAttack || m_ActionState == ActionState::FallDownAttack)
	{
		m_IsAttacking = true;
	}
	else
	{
		m_IsAttacking = false;
	}

	// DEBUGGING
	//std::cout << "xVel : " << m_Velocity.x << ", " << "yVel : " << m_Velocity.y << "\n";
}

void Player::HandleMovement(float elapsedSec, const Level& level, const PlatformManager& platformManager, const DirtBlockManager& dirtBlockManager)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	m_Velocity.x = 0;
	if (m_ActionState != ActionState::Die)
	{
		if (pStates[SDL_SCANCODE_D])
		{
			if (m_ActionState != ActionState::NormalAttack && m_ActionState != ActionState::ClimbAttack)
			{
				if (!(m_IsClimbing == true && (pStates[SDL_SCANCODE_W] || pStates[SDL_SCANCODE_S])))
				{
					m_IsLookingLeft = false;
				}
			}
			m_Velocity.x = m_HorSpeed;
		}
		if (pStates[SDL_SCANCODE_A])
		{
			if (m_ActionState != ActionState::NormalAttack && m_ActionState != ActionState::ClimbAttack)
			{
				if (!(m_IsClimbing == true && (pStates[SDL_SCANCODE_W] || pStates[SDL_SCANCODE_S])))
				{
					m_IsLookingLeft = true;
				}
			}
			m_Velocity.x = -m_HorSpeed;
		}
		if (pStates[SDL_SCANCODE_W])
		{
			if (level.IsOnLadder(m_Shape) && m_ActionState != ActionState::ClimbAttack)
			{
				m_ActionState = ActionState::Climbing;
			}
			if (m_ActionState == ActionState::Climbing)
			{
				m_Velocity.y = m_VerSpeed;
				m_Shape.left = level.GetLadder(m_Shape).left + 1;
				m_Shape.bottom += m_Velocity.y * elapsedSec;
			}
		}
		if (pStates[SDL_SCANCODE_S])
		{
			if (level.IsOnLadder(m_Shape) && m_ActionState != ActionState::ClimbAttack)
			{
				m_ActionState = ActionState::Climbing;
			}
			if (m_ActionState == ActionState::Climbing)
			{
				m_Velocity.y = -m_VerSpeed;
				m_Shape.left = level.GetLadder(m_Shape).left;
				m_Shape.bottom += m_Velocity.y * elapsedSec;
			}
		}
		if (m_ActionState != ActionState::Damage)
		{
			if (pStates[SDL_SCANCODE_K] || pStates[SDL_SCANCODE_SPACE])
			{
				if (level.IsOnGround(m_Shape) || platformManager.IsOnPlatform(m_Shape) || dirtBlockManager.IsOnBlock(m_Shape))
				{
					m_Velocity.y = m_JumpSpeed;
					m_ActionState = ActionState::Jumping;
					m_SJump.Play(false);
				}
				if (m_ActionState == ActionState::Climbing && !pStates[SDL_SCANCODE_W] && !pStates[SDL_SCANCODE_S])
				{
					m_ActionState = ActionState::Jumping;
					m_SJump.Play(false);
				}
			}
		}
	}
	if ((m_ActionState != ActionState::NormalAttack || (m_ActionState == ActionState::NormalAttack && !level.IsOnGround(m_Shape) && !platformManager.IsOnPlatform(m_Shape) && !dirtBlockManager.IsOnBlock(m_Shape))) && m_ActionState != ActionState::Climbing && m_ActionState != ActionState::ClimbAttack)
	{
		m_Shape.left += m_Velocity.x * elapsedSec;
		m_Velocity.y += m_Acceleration.y * elapsedSec;
		m_Shape.bottom += m_Velocity.y * elapsedSec;
	}

	// DEBUGGING
	/*if (pStates[SDL_SCANCODE_P])
	{
		// Gives player pos in world
		std::cout << "PlayerPos: { " << m_Shape.left << ", " << m_Shape.bottom << " }\n";
	}*/
}

void Player::HandleCollisions(const Level& level, const PlatformManager& platformManager, const DirtBlockManager& dirtBlockManager, float elapsedSec)
{
	level.HandleCollision(m_Shape, m_Velocity, m_IsLookingLeft, m_IsClimbing);
	platformManager.HandleCollision(m_Shape, m_Velocity, m_IsLookingLeft, elapsedSec);
	dirtBlockManager.HandleCollision(m_Shape, m_Velocity, m_IsLookingLeft, m_IsClimbing);

	if (m_Shape.left < level.GetBoundaries().left)
	{
		m_Shape.left = level.GetBoundaries().left;
	}
	if (m_Shape.left + m_Shape.width > level.GetBoundaries().left + level.GetBoundaries().width)
	{
		m_Shape.left = level.GetBoundaries().left + level.GetBoundaries().width - m_Shape.width;
	}
	if (m_Shape.bottom < level.GetBoundaries().bottom)
	{
		m_Shape.bottom = level.GetBoundaries().bottom;
	}
	if (m_Shape.bottom + m_Shape.height > level.GetBoundaries().bottom + level.GetBoundaries().height)
	{
		m_Shape.bottom = level.GetBoundaries().bottom + level.GetBoundaries().height - m_Shape.height;
	}
}

void Player::Animation(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	switch (m_ActionState)
	{
	case ActionState::Idle:
		m_AnimFrameY = 1;
		break;
	case ActionState::Running:
		m_AnimTime += elapsedSec;
		m_AnimFrameY = 2;
		if (m_AnimTime >= 1.0f / m_NrFramesPerSec)
		{
			m_AnimFrameX = (m_AnimFrameX + 1) % (m_NrOfFrames - 3);
			m_AnimTime = 0;
		}
		break;
	case ActionState::Jumping:
		m_AnimFrameY = 4;
		if (m_Velocity.y > 0)
		{
			m_AnimFrameX = 0;
		}
		else if (m_Velocity.y < 0)
		{
			m_AnimFrameX = 1;
		}
		break;
	case ActionState::Climbing:
		m_AnimFrameY = 6;
		m_AnimFrameX = 4;
		
		if (pStates[SDL_SCANCODE_W] || pStates[SDL_SCANCODE_S])
		{
			m_AnimTime += elapsedSec;
			if (m_AnimTime >= 1.f / 5)
			{
				m_IsLookingLeft = !m_IsLookingLeft;
				m_AnimTime = 0;
			}
		}
		break;
	case ActionState::NormalAttack:
		m_AnimTime += elapsedSec;
		m_AnimFrameY = 5;
		if (m_AnimTime >= 1.0f / m_NrFramesPerSec)
		{
			++m_AnimFrameX;
			m_AnimTime = 0;
		}
		break;
	case ActionState::FallDownAttack:
		m_AnimFrameY = 4;
		m_AnimFrameX = 2;
		break;
	case ActionState::ClimbAttack:
		m_AnimTime += elapsedSec;
		m_AnimFrameY = 6;
		if (m_AnimFrameX == 2)
		{
			if (m_AnimTime >= 1.0f / 6)
			{
				m_ActionState = ActionState::Climbing;
				m_AnimTime = 0;
			}
		}
		else
		{
			if (m_AnimTime >= 1.0f / 6)
			{
				++m_AnimFrameX;
				m_AnimTime = 0;
			}
		}
		break;
	case ActionState::Damage:
		m_AnimTime += elapsedSec;
		m_AnimFrameY = 3;
		m_AnimFrameX = 0;
		if (m_AnimTime >= 1.0f / 2)
		{
			m_AnimTime = 0;
			m_ActionState = ActionState::Running;
		}
		break;
	case ActionState::Die:
		m_AnimTime += elapsedSec;
		m_AnimFrameY = 7;
		if (m_AnimFrameX != 2)
		{
			if (m_AnimTime >= 1.0f / 2)
			{
				m_AnimFrameX = (m_AnimFrameX + 1) % (m_NrOfFrames - 6);
				m_AnimTime = 0;
			}
		}
		else
		{
			m_ActionState = ActionState::Respawn;
		}
		break;
	}
}

void Player::LevelChangeAnimation(const Point2f& speed, float elapsedSec)
{
	m_Velocity.x += speed.x * elapsedSec;
	m_Velocity.y += speed.y * elapsedSec;
	m_Shape.left += speed.x * elapsedSec;
	m_Shape.bottom += speed.y * elapsedSec;
}

void Player::HitBubble()
{
	if (m_ActionState == ActionState::FallDownAttack)
	{
		m_Velocity.y = m_JumpSpeed;
		m_SBubbleBounce.Play(false);
	}
	else
	{
		Damage();
	}
}

void Player::HitDirtBlock()
{
	if (m_ActionState == ActionState::FallDownAttack)
	{
		m_Velocity.y = m_JumpSpeed;
		m_SRockBounce.Play(false);
	}
	else
	{
		m_SRockShovel.Play(false);
	}
}

void Player::HitBeeto()
{
	if (m_ActionState == ActionState::FallDownAttack)
	{
		m_Velocity.y = m_JumpSpeed;
	}
}

bool Player::IsAttack() const
{
	if (m_ActionState == ActionState::NormalAttack)
	{
		return true;
	}
	return false;
}

bool Player::IsDownAttack() const
{
	if (m_ActionState == ActionState::FallDownAttack)
	{
		return true;
	}
	return false;
}

bool Player::IsClimbAttack() const
{
	if (m_ActionState == ActionState::ClimbAttack)
	{
		return true;
	}
	return false;
}

void Player::Damage()
{
	if (m_CanDamage)
	{
		--m_Health;
		m_ActionState = ActionState::Damage;
		m_SDamage.Play(false);
		m_ProtectionTimer = 0;
		m_CanDamage = false;
	}

	if (m_Health <= 0)
	{
		Die();
	}
}

void Player::Protection(float elapsedSec)
{
	if (!m_CanDamage)
	{
		m_ProtectionTimer += elapsedSec;
		if (m_ProtectionTimer >= 2.0f)
		{
			m_CanDamage = true;
			m_ProtectionTimer = 0;
		}
	}
}

void Player::Die()
{
	if (m_ActionState != ActionState::Die)
	{
		m_Health = 0;
		m_AnimFrameX = 0;
		m_ActionState = ActionState::Die;
		m_SDie.Play(false);
	}
}

bool Player::Respawn()
{
	if (m_ActionState == ActionState::Respawn)
	{
		m_ActionState = ActionState::Idle;
		m_Health = 8;
		m_CanDamage = true;
		m_Shape.left = m_SpawnLoc.x;
		m_Shape.bottom = m_SpawnLoc.y;
		return true;
	}
	return false;
}