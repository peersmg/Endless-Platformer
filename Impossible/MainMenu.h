#pragma once
#include "GameObject.h"
#include "BgBlock.h"
#include "wall.h"

class MainMenu : public GameObject
{
private:
  Circle2D m_collisionShape;
  int m_menuOption;
  int m_gameMode;
  float m_modeTextPosition;
  float m_modeTextTargetPosition;
  float m_rectPosition;
  float m_rectTargetPosition;
  float m_rectHeight;
  float m_titleRotation;
  float m_titleTargetRotation;
  float m_selectedScale;
  color m_titleColorOne, m_titleTargetColorOne;
  color m_titleColorTwo, m_titleTargetColorTwo;
  color m_bgColor, m_bgTargetColor;
  ColorType m_bgTargetColorType;

  wall* m_pBottomWall;
  wall* m_pTopWall;
  BgBlock* m_pBgBlock;
public:
  void Initialise(bool firstCreate, wall* topWall = nullptr, wall* bottomWall = nullptr, BgBlock* bgBlock = nullptr);

  void Update(float frameTime);
  IShape2D& GetCollisionShape();
  void ProcessCollision(GameObject &other);
  void Draw();
  void MoveWall();
  void HandleEvent(Event evt);
  void ChangeColor();

  MainMenu();
};

