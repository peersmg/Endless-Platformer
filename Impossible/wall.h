#pragma once
#include "GameObject.h"
class wall : public GameObject
{
private:
	Rectangle2D m_collisionShape;
  float m_height;
  float m_targetPos;
  int m_pulseRate;
  bool m_frozen;
  color m_color;
  color m_targetColor;
  bool m_isTopWall;
public:
  void Initialise(float yPos, float height, color startColor, color targetColor, int pulseRate, bool isTop);
	//void Draw();
	void Update(float frameTime);
  unsigned int GetColor();
	void ProcessCollision(GameObject& other);
	void Draw();
  void SetPosition(float y);
  bool InPosition();
  void HandleEvent(Event);
	IShape2D& GetCollisionShape();

	wall();
};

