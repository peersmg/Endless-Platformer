#pragma once
#include "GameObject.h"
#include "wall.h"
#include "BgBlock.h"

class EndlessManager :
  public GameObject
{
private:
  Circle2D m_collisionShape;
  int m_phaseCount;
  float m_wallHeight;
  int m_obsticles;
  bool m_waiting;
  int m_pulseRate;
  float m_topWallPos;
  float m_bottomWallPos;
  float m_colorDelay;
  double m_score;
  bool m_frozen;
  bool m_wallsAdded;
  GameMode m_gameMode;
  color m_color;
  color m_targetColor;
  ColorType m_targetColorType;

  BgBlock *m_pBgBlock;
  wall *m_pTopWall;
  wall *m_pBottomWall;
public:
  void Initialise(wall* topWall, wall* bottomWall, BgBlock* bgBlock);

  void Update(float frameTime);
  IShape2D& GetCollisionShape();
  void ProcessCollision(GameObject &other);
  void Draw();
  void HandleEvent(Event evt);
  void NextPhase(GameMode mode);
  void NextMode();

  void NormalPhase();
  void RocketPhase();
  void JumpPhase();

  void ChangeColor();
  EndlessManager();
};

