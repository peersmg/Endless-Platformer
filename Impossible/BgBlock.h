#pragma once
#include "GameObject.h"

class BgBlock :
  public GameObject
{
private:
  Rectangle2D m_collisionShape;
  float m_width;
  int m_pulseRate;
  bool m_frozen;
  color m_color;
  color m_targetColor;
public:
  void Initialise(float xPos, float width, color startColor, color targetColor, int pulseRate);
  //void Draw();
  void Update(float frameTime);
  void ProcessCollision(GameObject& other);
  void Draw();
  void HandleEvent(Event);
  void SetColor(color newTarget);
  unsigned int GetColor();
  IShape2D& GetCollisionShape();
public:
  BgBlock();
};

