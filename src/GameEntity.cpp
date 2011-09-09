#include "Iw2D.h"
#include "GameEntity.h"

GameEntity::GameEntity(const char* image)
	: m_Position(0,0)
{
	m_Image = Iw2DCreateImageResource(image);
}


GameEntity::~GameEntity()
{
	delete m_Image;
}


void GameEntity::SetPosition(CIwSVec2 position)
{
	m_Position = position;
}


void GameEntity::Draw() 
{
	Iw2DDrawImage(m_Image, m_Position);
}
