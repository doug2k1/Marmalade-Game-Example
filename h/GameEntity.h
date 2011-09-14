#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

class GameEntity
{
public:
	GameEntity(const char* image);
	~GameEntity();
	inline void SetCenter(CIwSVec2 center) { m_Center = center; }
	inline CIwFVec2 GetPosition() { return m_Position; }
	inline void SetPosition(CIwFVec2 position) { m_Position = position; }
	inline void SetMovSpeed(CIwFVec2 speed) { m_MovSpeed = speed; }
	inline iwangle GetRotation() { return m_Angle; }
	inline void SetRotation(iwangle angle) { m_Angle = angle; }
	void SetAnimated(bool animated, float speed, CIwSVec2 frameCount = CIwSVec2());
	void Update(float deltaTime);
	void Draw();

private:
	CIwSVec2 m_Center;
	CIwFVec2 m_Position;
	CIwFVec2 m_MovSpeed;
	iwangle m_Angle;
	bool m_Animated;
	float m_AnimSpeed;
	CIwSVec2 m_FrameSize;
	float m_CurrentFrame;
	CIwSVec2 m_FrameCount;
	CIw2DImage* m_Image;
};

#endif