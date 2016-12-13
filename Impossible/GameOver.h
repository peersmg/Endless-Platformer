#pragma once
#include "GameObject.h"
#include "wall.h"
#include "BgBlock.h"
class GameOver : public GameObject
{
private:
  Circle2D m_collisionShape;
  int m_menuOption;
  double m_score;

  BgBlock *m_pBgBlock;
  wall *m_pTopWall;
  wall *m_pBottomWall;
public:
  void Initialise(double score, wall* topWall, wall* bottomWall, BgBlock* bgBlock);

  void Update(float frameTime);
  IShape2D& GetCollisionShape();
  void ProcessCollision(GameObject &other);
  void Draw();
  void HandleEvent(Event evt);
public:
  GameOver();
};

