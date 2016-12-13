#pragma once
#include "GameObject.h"
class block : public GameObject
{
private:
  Vector2D m_velocity;
  Rectangle2D m_collisionShape;
  float m_xVel;
  Vector2D m_size;
  int m_pulseRate;
  bool m_frozen;
  color m_color;
  color m_targetColor;
public:
  void Initialise(Vector2D position, Vector2D size, float speed, 
    color startColor, color targetColor, int pulseRate);

  void Draw();
  void Update(float frameTime);
  void ProcessCollision(GameObject& other);
  void HandleEvent(Event evt);
  IShape2D& GetCollisionShape();

  block();
};

