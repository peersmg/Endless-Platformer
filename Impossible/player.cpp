#include "player.h"
#include "myinputs.h"
#include "gamecode.h"
#include "MainMenu.h"
#include "BgBlock.h"

player::player() : GameObject(PLAYER)
{

}

void player::Initialise(float gravity, wall *topWall, wall *bottomWall)
{
	MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  Rectangle2D screen = pTheDrawEngine->GetViewport();
  float screenWidth = screen.GetBottomLeft().XValue - screen.GetBottomRight().XValue;
  m_handleEvents = true;

  m_pTopWall = topWall;
  m_pBottomWall = bottomWall;
  m_playerSize = Vector2D(124, 124);
  m_position = Vector2D((screenWidth / 2) - (m_playerSize.XValue), 0);
	m_gravity = gravity;
	m_turnSpeed = 10.0f;
	m_targetAngle = 0;
  m_frozen = false;
  m_gameMode = NORMAL;
  m_velocity = Vector2D(0,0);

  m_maxJump = 6200;
  m_curJump = 0;

  m_targetPosition = Vector2D(-700, m_position.YValue);
  m_inPos = false;
}

IShape2D& player::GetCollisionShape()
{
	MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
	Rectangle2D screen = pTheDrawEngine->GetViewport();

  m_collisionShape.PlaceAt(Vector2D(m_position.XValue - (m_playerSize.XValue / 2), 
    m_position.YValue - (m_playerSize.YValue/2)), 
    Vector2D(m_position.XValue + (m_playerSize.XValue / 2),
    m_position.YValue + (m_playerSize.YValue / 2)));

	return m_collisionShape;
}

void player::Update(float deltaTime)
{
	MyInputs* pTheInputs = MyInputs::GetInstance();
	pTheInputs->SampleKeyboard();
  pTheInputs->SampleMouse();

  bool upPressed = false;
  bool downPressed = false;
  bool gravSwitch = false;

  unsigned char upKey[3];
  unsigned char downKey[3];

  upKey[0] = DIK_UPARROW;
  upKey[1] = DIK_W;

  downKey[0] = DIK_DOWNARROW;
  downKey[1] = DIK_S;

  // Handle target position
  if (m_inPos == false && m_pTopWall->InPosition() && m_pBottomWall->InPosition() && m_position.YValue == 0)
  {
    m_position = Vector2D(m_position.XValue, m_pBottomWall->GetPosition().YValue + 62);
    m_targetPosition = Vector2D(m_targetPosition.XValue, m_position.YValue);
  }

  if (!InPosition() && m_pTopWall->InPosition() && m_pBottomWall->InPosition())
  {
    if (m_position.YValue > m_targetPosition.YValue)
    {
      m_position = Vector2D(m_position.XValue, m_position.YValue - (1800 * deltaTime));

      if (m_position.YValue < m_targetPosition.YValue)
      {
        m_position.YValue = m_targetPosition.YValue;
      }
    }
    else
    {
      m_position = Vector2D(m_position.XValue, m_position.YValue + (1800 * deltaTime));

      if (m_position.YValue > m_targetPosition.YValue)
      {
        m_position.YValue = m_targetPosition.YValue;
      }
    }

    if (m_position.XValue > 0)
    {
      m_position = Vector2D(m_position.XValue - (1800 * deltaTime), m_position.YValue);

      if (m_position.XValue < m_targetPosition.XValue)
      {
        m_position.XValue = m_targetPosition.XValue;
      }
    }
    else
    {
      m_position = Vector2D(m_position.XValue + (1800 * deltaTime), m_position.YValue);

      if (m_position.XValue > m_targetPosition.XValue)
      {
        m_position.XValue = m_targetPosition.XValue;
      }
    }
  }

  ///

  if (!m_frozen && InPosition())
  {

    for (int i = 0; i < 3; i++)
    {
      if (!upPressed)
        upPressed = pTheInputs->KeyPressed(upKey[i]) || pTheInputs->IfMouseLeftDown();

      if (!downPressed)
        downPressed = pTheInputs->KeyPressed(downKey[i]) || pTheInputs->IfMouseRightDown();
    }

    if (!upPressed && m_curJump > 0)
    {
      m_jumped = true;
    }

    if (m_curJump == 0)
    {
      m_jumped = false;
    }

    if (m_gameMode == ROCKET)
    {
      if (InPosition() && !m_grounded)
      {
        if (upPressed)
        {
          //Move up
          m_position = Vector2D(m_position.XValue, m_position.YValue + (1400 * deltaTime));
        }
        else if (downPressed)
        {
          //Move down
          m_position = Vector2D(m_position.XValue, m_position.YValue - (1400 * deltaTime));
        }
      }
      else if (!m_grounded)
      {
        m_targetPosition.YValue = 0;
      }
    }
    else if (m_gameMode == NORMAL)
    {
      gravSwitch = (m_gravity > 0 && InPosition() && downPressed) || (m_gravity < 0 && InPosition() && upPressed);

      if (gravSwitch && m_grounded)
      {
        m_gravity = -m_gravity;
        m_grounded = false;

        if (m_gravity > 0)
        {
          m_targetAngle += 3.14159f;
        }
        else
        {
          m_targetAngle -= 3.14159f;
        }
      }
    }
    else if (m_gameMode == JUMP)
    {
      if (upPressed)
      {
        if ((pTheInputs->NewKeyPressed(DIK_UPARROW) || pTheInputs->NewKeyPressed(DIK_W)) && m_grounded)
        {
          m_jumped = false;
        }

        if (m_jumped == false)
        {
          if (m_curJump == 0)
          {
            m_targetAngle -= 3.14159f;
            m_curJump = 400;
            m_grounded = false;
          }

          if (m_curJump < m_maxJump)
          {
            m_curJump += 400;
            m_velocity.YValue = 2200;
          }
        }
      }
    }

    if (m_angle < m_targetAngle)
    {
      m_angle += m_turnSpeed*deltaTime;
      if (m_angle > m_targetAngle)
      {
        m_angle = m_targetAngle;
      }
    }
    else if (m_angle > m_targetAngle)
    {
      m_angle -= m_turnSpeed*deltaTime;

      if (m_angle < m_targetAngle)
      {
        m_angle = m_targetAngle;
      }
    }

    if (m_grounded)
    {
      m_position = Vector2D(m_position.XValue, m_position.YValue);
      m_velocity.YValue = 0;
    }
    else if (InPosition())
    {
      m_velocity.YValue += m_gravity;

      if (m_gameMode == NORMAL)
      {
        m_velocity.YValue = m_gravity * 10;
      }

      m_position = Vector2D(m_position.XValue, m_position.YValue + (m_velocity.YValue * deltaTime));
    }
  }

  m_grounded = false;
}

bool player::InPosition()
{
  if (m_position == m_targetPosition || m_inPos)
  {
    m_inPos = true;
    return true;
  }
  else
  {
    return false;
  }
}

void player::Draw()
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();

  //pTheDrawEngine->WriteInt(Vector2D(0, 0), m_velocity.YValue, MyDrawEngine::D3DBLUE);

  Rectangle2D playerObj;

  playerObj.PlaceAt(Vector2D(m_position.XValue - (m_playerSize.XValue / 2),
    m_position.YValue - (m_playerSize.YValue / 2)),
    Vector2D(m_position.XValue + (m_playerSize.XValue / 2),
    m_position.YValue + (m_playerSize.YValue / 2)));

  pTheDrawEngine->FillRect(playerObj, m_pBottomWall->GetColor(), -m_angle);
}

void player::ProcessCollision(GameObject &other)
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();

  if (other.GetType() == WALL)
  {
    m_grounded = true;
    m_curJump = 0;
  }

  else if (other.GetType() == BLOCK)
  {
    if (m_position.XValue + (m_size.XValue / 2) <= other.GetPosition().XValue - (other.GetSize().XValue / 2))
    {
      Event evt;
      evt.position = m_position;
      evt.pSource = this;
      evt.type = EVENT_GAMEOVER;
      Game::instance.NotifyEvent(evt);
    }
    else
    {
      m_grounded = true;
    }
  }
}

void player::HandleEvent(Event evt)
{
  if (evt.type == EVENT_DELETEGAMEOBJECTS)
  {
    m_active = false;
  }
  else if (evt.type == EVENT_FREEZEALL)
  {
    m_frozen = true;
  }
  else if (evt.type == EVENT_ENABLEROCKETMODE)
  {
    m_velocity.YValue = 0;

    m_targetPosition = Vector2D(m_position.XValue, 0);
    m_inPos = false;

    m_gameMode = ROCKET;
    m_gravity = 0;
  }
  else if (evt.type == EVENT_DISABLEROCKETMODE)
  {
    m_gameMode = NORMAL;
    m_gravity = -200;
  }
  else if (evt.type == EVENT_ENABLEJUMPMODE)
  {
    m_gameMode = JUMP;
    m_gravity = -200;
  }
  else if (evt.type == EVENT_DISABLEJUMPMODE)
  {
    m_gameMode = NORMAL;
  }
}
