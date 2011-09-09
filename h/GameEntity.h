#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

class GameEntity
{
public:
	GameEntity(const char* image);
	~GameEntity();
	void SetPosition(CIwSVec2 position);
	void Draw();

private:
	CIwSVec2 m_Position;
	CIw2DImage* m_Image;
};

#endif