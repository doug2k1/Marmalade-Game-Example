#include "Iw2D.h"
#include "GameEntity.h"

GameEntity::GameEntity(const char* image)
	: m_Center(0,0), 
	m_Position(0,0),
	m_Angle(0),
	m_Animated(false)
{
	m_Image = Iw2DCreateImageResource(image);
}


GameEntity::~GameEntity()
{
	delete m_Image;
}


void GameEntity::SetAnimated(bool animated, CIwSVec2 frameCount)
{
	m_Animated = animated;

	if (animated) 
	{
		m_FrameSize = CIwSVec2((m_Image->GetWidth() / frameCount.x), (m_Image->GetHeight() / frameCount.y));
		m_CurrentFrame = 0;
		m_FrameCount = frameCount; 
	}
}


void GameEntity::Update(int deltaTime)
{
	m_CurrentFrame += 0.02 * deltaTime;

	if (m_CurrentFrame > (m_FrameCount.x * m_FrameCount.y)) { m_CurrentFrame = 0; }
}


void GameEntity::Draw() 
{
	if (m_Angle != 0) {
		CIwMat2D rotMatrix;
		rotMatrix.SetRot(m_Angle, CIwVec2(m_Position));
		Iw2DSetTransformMatrix(rotMatrix);
	}

	if (m_Animated) 
	{
		CIwSVec2 offset(((int)m_CurrentFrame % m_FrameCount.x) * m_FrameSize.x, ((int)m_CurrentFrame / m_FrameCount.x) * m_FrameSize.y);
		Iw2DDrawImageRegion(m_Image, m_Position - m_Center, offset, m_FrameSize);
	} 
	else
	{
		Iw2DDrawImage(m_Image, m_Position - m_Center);
	}

	if (m_Angle != 0) {
		Iw2DSetTransformMatrix(CIwMat2D::g_Identity);
	}
}
