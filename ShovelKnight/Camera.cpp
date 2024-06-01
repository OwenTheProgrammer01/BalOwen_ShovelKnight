#include "pch.h"
#include "Camera.h"
#include "utils.h"

Camera::Camera(float width, float height)
	: m_Width{ width },
	m_Height{ height },
	m_LevelBoundaries{ }
{

}

Camera::~Camera()
{
	
}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

void Camera::Transform(const Rectf& target) const
{
	Point2f cameraPos{ Track(target) };
	Clamp(cameraPos);
	glTranslatef(-cameraPos.x, -cameraPos.y, 0);
}

Point2f Camera::Track(const Rectf& target) const
{
	return Point2f(target.left + target.width / 2 - m_Width / 2, target.bottom + target.height - m_Height);
}

void Camera::Clamp(Point2f& bottomLeftPos) const
{
	if (bottomLeftPos.x < m_LevelBoundaries.left)
	{
		bottomLeftPos.x = m_LevelBoundaries.left;
	}

	if (bottomLeftPos.x + m_Width > m_LevelBoundaries.left + m_LevelBoundaries.width)
	{
		bottomLeftPos.x = m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width;
	}

	if (bottomLeftPos.y < m_LevelBoundaries.bottom)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom;
	}

	if (bottomLeftPos.y + m_Height > m_LevelBoundaries.bottom + m_LevelBoundaries.height)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom + m_LevelBoundaries.height - m_Height;
	}
}

void Camera::Zoom(const float zoom)
{
	m_Width /= zoom;
	m_Height /= zoom;
	glScalef(zoom, zoom, 1);
}