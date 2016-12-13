#pragma once
#include "GameObject.h"
#include "wall.h"
#include "BgBlock.h"

class player : public GameObject
{
private:
	Vector2D m_velocity;
	Rectangle2D m_collisionShape;
	float m_gravity;
	bool m_grounded;
  Vector2D m_playerSize;
	float m_targetAngle;
	float m_turnSpeed;
  float m_maxJump;
  float m_curJump;
  bool m_jumped;
  bool m_frozen;
  bool m_inPos;
  GameMode m_gameMode;
  Vector2D m_targetPosition;

  wall *m_pTopWall;
  wall *m_pBottomWall;
public:
  void Initialise(float gravity, wall *topWall, wall *bottomWall);
	void Draw();
	void Update(float frameTime);
	void ProcessCollision(GameObject& other);
  void HandleEvent(Event evt);
  bool InPosition();
	IShape2D& GetCollisionShape();

	player();
};

