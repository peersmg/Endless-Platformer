#pragma once
#include "GameObject.h"
class DestroyBlock :
  public GameObject
{
private:
  Rectangle2D m_collisionShape;
  float m_height;
  int m_pulseRate;

  color m_color;
  color m_targetColor;
public:
  void Initialise();
  //void Draw();
  void Update(float frameTime);
  void ProcessCollision(GameObject& other);
  void Draw();
  void HandleEvent(Event);
  IShape2D& GetCollisionShape();

  DestroyBlock();
};

