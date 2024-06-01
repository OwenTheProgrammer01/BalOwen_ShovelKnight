#include "pch.h"
#include "HUD.h"
#include "Texture.h"
#include "utils.h"

HUD::HUD()
	: m_Shape{ Rectf{ 0, 208, 400, 16 } },
	m_pHealthTexture{ new Texture{ "Images/HUD/HealthIcon.png" } },
	m_HealthPos{ 180, 212 },
	m_TotalHealth{ 8.0f }
{
	
}

HUD::~HUD()
{
	delete m_pHealthTexture;
	m_pHealthTexture = nullptr;
}

void HUD::Draw(const float& health) const
{
	utils::SetColor(Color4f{ 0.f, 0.f, 0.f, 1.f });
	utils::FillRect(m_Shape);

	for (int index{ 0 }; index < m_TotalHealth / 2; ++index)
	{
		if ((health - 1) / 2 > index)
		{
			m_pHealthTexture->Draw(
				Point2f(
					m_HealthPos.x + index * m_pHealthTexture->GetWidth() / 3,
					m_HealthPos.y
				),
				Rectf(
					0,
					0,
					m_pHealthTexture->GetWidth() / 3,
					m_pHealthTexture->GetHeight()
				)
			);
		}
		else if (health != 0 && (health - 1) / 2 == index)
		{
			m_pHealthTexture->Draw(
				Point2f(
					m_HealthPos.x + index * m_pHealthTexture->GetWidth() / 3,
					m_HealthPos.y
				),
				Rectf(
					m_pHealthTexture->GetWidth() / 3,
					0,
					m_pHealthTexture->GetWidth() / 3,
					m_pHealthTexture->GetHeight()
				)
			);
		}
		else
		{
			m_pHealthTexture->Draw(
				Point2f(
					m_HealthPos.x + index * m_pHealthTexture->GetWidth() / 3,
					m_HealthPos.y
				),
				Rectf(
					m_pHealthTexture->GetWidth() / 3 * 2,
					0,
					m_pHealthTexture->GetWidth() / 3,
					m_pHealthTexture->GetHeight()
				)
			);
		}
	}
}