#pragma once
#include "GameObject.h"
class textObj : public GameObject
{
private:
  float m_velocity;
  Rectangle2D m_collisionShape;
  bool m_grounded;
  Vector2D m_scale;
  float m_targetAngle;
  float m_turnSpeed;
  bool m_frozen;
  GameMode m_gameMode;
  bool m_playerCentered;
  wchar_t m_text[30];
  int m_textSize;
public:
  void Initialise(Vector2D position, const wchar_t text[30], int size, float xVel, Vector2D scale);
  void Draw();
  void Update(float frameTime);
  void ProcessCollision(GameObject& other);
  void HandleEvent(Event evt);
  IShape2D& GetCollisionShape();

  textObj();
};

