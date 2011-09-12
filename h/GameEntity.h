#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

class GameEntity
{
public:
	GameEntity(const char* image);
	~GameEntity();
	inline void SetCenter(CIwSVec2 center) { m_Center = center; }
	inline CIwSVec2 GetPosition() { return m_Position; }
	inline void SetPosition(CIwSVec2 position) { m_Position = position; }
	inline iwangle GetRotation() { return m_Angle; }
	inline void SetRotation(iwangle angle) { m_Angle = angle; }
	void SetAnimated(bool animated, CIwSVec2 frameCount = CIwSVec2());
	void Update(int deltaTime);
	void Draw();

private:
	CIwSVec2 m_Center;
	CIwSVec2 m_Position;
	iwangle m_Angle;
	bool m_Animated;
	CIwSVec2 m_FrameSize;
	double m_CurrentFrame;
	CIwSVec2 m_FrameCount;
	CIw2DImage* m_Image;
};

#endif