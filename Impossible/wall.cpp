#include "wall.h"
#include "gamecode.h"
#include "myinputs.h"

wall::wall() : GameObject(WALL)
{

}

void wall::Initialise(float yPos, float height, color startColor, color targetColor, int pulseRate, bool top)
{
  m_handleEvents = true;
  m_height = height;
  m_position = Vector2D(0, yPos);
  m_color = startColor;
  m_targetColor = targetColor;
  m_pulseRate = pulseRate;
  m_isTopWall = top;
  m_targetPos = yPos;
}

unsigned int wall::GetColor()
{
  return m_color.GetColor();
}

IShape2D& wall::GetCollisionShape()
{
	MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();

  Rectangle2D screen = pTheDrawEngine->GetViewport();
  float screenWidth = screen.GetBottomLeft().XValue - screen.GetBottomRight().XValue;
  float screenHeight = screen.GetTopRight().YValue - screen.GetBottomLeft().YValue;

  if (m_isTopWall)
  {
    m_collisionShape.PlaceAt(
      Vector2D(m_position.XValue - screenWidth, m_position.YValue),
      Vector2D(m_position.XValue + screenWidth, screenHeight / 2));
  }
  else
  {
    m_collisionShape.PlaceAt(Vector2D(m_position.XValue - screenWidth, -screenHeight / 2),
      Vector2D(m_position.XValue + screenWidth, m_position.YValue));
  }


	return m_collisionShape;
}

void wall::ProcessCollision(GameObject &other)
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();

  if (other.GetType() == PLAYER)
  {
    if (m_isTopWall)
    {
      //Hit top
      other.SetPosition(Vector2D(other.GetPosition().XValue, m_position.YValue-62));
    }
    else
    {
      //Hit Bottom
      other.SetPosition(Vector2D(other.GetPosition().XValue, m_position.YValue+62));
    }
  }
}

void wall::Update(float deltaTime)
{
  m_color.Blend(m_targetColor, m_pulseRate);

  if (m_position.YValue > m_targetPos)
  {
    m_position.YValue -= 2000 * deltaTime;
    if (m_position.YValue < m_targetPos)
    {
      m_position.YValue = m_targetPos;
    }
  }
  else if (m_position.YValue < m_targetPos)
  {
    m_position.YValue += 2000 * deltaTime;
    if (m_position.YValue > m_targetPos)
    {
      m_position.YValue = m_targetPos;
    }
  }
}

void wall::SetPosition(float y)
{
  m_targetPos = y;
}

bool wall::InPosition()
{
  if (m_targetPos == m_position.YValue)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void wall::Draw()
{
	MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
	Rectangle2D wallObj;

	Rectangle2D screen = pTheDrawEngine->GetViewport();
  float screenWidth = screen.GetBottomLeft().XValue - screen.GetBottomRight().XValue;
  float screenHeight = screen.GetTopRight().YValue - screen.GetBottomLeft().YValue;

  if (m_isTopWall)
  {
    wallObj.PlaceAt(
      Vector2D(m_position.XValue - screenWidth, m_position.YValue),
      Vector2D(m_position.XValue + screenWidth, screenHeight/2));
  }
  else
  {
    wallObj.PlaceAt(Vector2D(m_position.XValue - screenWidth, -screenHeight/2),
      Vector2D(m_position.XValue + screenWidth, m_position.YValue));
  }

  pTheDrawEngine->FillRect(wallObj, m_color.GetColor());
}

void wall::HandleEvent(Event evt)
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  Rectangle2D screen = pTheDrawEngine->GetViewport();

  if (evt.type == EVENT_COLORCHANGE)
  {
    m_targetColor = evt.newTargetColor;
    m_pulseRate = evt.newPulseRate;
  }
  else if (evt.type == EVENT_DELETEGAMEOBJECTS)
  {
    //m_active = false;
  }
  else if (evt.type == EVENT_FREEZEALL)
  {
    m_frozen = true;
  }
  else if (evt.type == EVENT_ENABLEROCKETMODE)
  {
    if (m_isTopWall)
    {
      SetPosition(500);
    }
    else
    {
      SetPosition(-500);
    }
  }
  else if (evt.type == EVENT_DISABLEROCKETMODE)
  {
    if (m_isTopWall)
    {
      SetPosition(400);
    }
    else
    {
      SetPosition(-400);
    }
  }
  else if (evt.type == EVENT_ENABLEJUMPMODE)
  {
    if (m_isTopWall)
    {
      SetPosition(700);
    }
    else
    {
      SetPosition(-700);
    }
  }
  else if (evt.type == EVENT_DISABLEJUMPMODE)
  {
    if (m_isTopWall)
    {
      SetPosition(400);
    }
    else
    {
      SetPosition(-400);
    }
  }
}