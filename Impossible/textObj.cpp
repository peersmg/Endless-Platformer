#include "textObj.h"
#include "objecttypes.h"

textObj::textObj() : GameObject(TEXT)
{

}

void textObj::Initialise(Vector2D position, const wchar_t text[30], int size, float xVel, Vector2D scale)
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  m_handleEvents = true;

  m_velocity = xVel;
  m_position = position;
  m_turnSpeed = 0.3f;
  m_targetAngle = 0;
  m_scale = scale;
  m_frozen = false;
  m_gameMode = NORMAL;
  m_playerCentered = false;
  m_textSize = size;
  
  for (int i = 0; i < m_textSize; i++)
  {
    m_text[i] = text[i];
  }
  
}

void textObj::Update(float deltaTime)
{
  if (!m_frozen)
  {
    m_position.XValue -= m_velocity*deltaTime;

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
    else
    {
      if (m_targetAngle > 0)
      {
        m_targetAngle = -0.05;
      }
      else
      {
        m_targetAngle = 0.05;
      }
    }
  }
  m_grounded = false;
}

void textObj::Draw()
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();

  pTheDrawEngine->WriteText(m_position.XValue, m_position.YValue, m_text, MyDrawEngine::D3DWHITE, 0, MIDDLECENTRE, m_angle,
    Vector2D(1 + (m_angle / 2), 1 + (m_angle / 2)));
  //Draw text
}

void textObj::HandleEvent(Event evt)
{
  if (evt.type == EVENT_DELETEGAMEOBJECTS)
  {
    m_active = false;
  }
  else if (evt.type == EVENT_FREEZEALL)
  {
    m_frozen = true;
  }
}

void textObj::ProcessCollision(GameObject &other)
{
  if (other.GetType() == DESTROY)
  {
    m_active = false;
  }
}

IShape2D& textObj::GetCollisionShape()
{
  return m_collisionShape;
}