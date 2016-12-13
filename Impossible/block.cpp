#include "block.h"
#include "gamecode.h"

block::block() : GameObject(BLOCK)
{

}

void block::Initialise(Vector2D position, Vector2D size, float speed, 
                      color startColor, color targetColor, int pulseRate)
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  Rectangle2D screen = pTheDrawEngine->GetViewport();

  m_handleEvents = true;
  m_position = position;
  m_size = size;
  m_xVel = speed;
  m_color = startColor;
  m_targetColor = targetColor;
  m_pulseRate = pulseRate;
  m_frozen = false;
}

IShape2D& block::GetCollisionShape()
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  Rectangle2D screen = pTheDrawEngine->GetViewport();

  m_collisionShape.PlaceAt(Vector2D(m_position.XValue - (m_size.XValue / 2), m_position.YValue - (m_size.YValue / 2)), 
    Vector2D(m_position.XValue + (m_size.XValue / 2), m_position.YValue + (m_size.YValue / 2)));

  return m_collisionShape;
}

void block::ProcessCollision(GameObject &other)
{
  if (other.GetType() == DESTROY)
  {
    Event evt;
    evt.position = m_position;
    evt.pSource = this;
    evt.type = EVENT_OBJECTDESTROYED;
    Game::instance.NotifyEvent(evt);

    m_active = false;
  }
}

void block::Update(float deltaTime)
{
  if (!m_frozen)
  {
    m_color.Blend(m_targetColor, m_pulseRate);

    m_position = Vector2D(m_position.XValue - (m_xVel*deltaTime), m_position.YValue);
  }
}

void block::Draw()
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  Rectangle2D blockObj;

  blockObj.PlaceAt(Vector2D(m_position.XValue - (m_size.XValue / 2), m_position.YValue - (m_size.YValue / 2)),
    Vector2D(m_position.XValue + (m_size.XValue / 2), m_position.YValue + (m_size.YValue / 2)));

  pTheDrawEngine->FillRect(blockObj, m_color.GetColor());
}

void block::HandleEvent(Event evt)
{
  if (evt.type == EVENT_COLORCHANGE)
  {
    m_targetColor = evt.newTargetColor;
    m_pulseRate = evt.newPulseRate;
  }
  else if (evt.type == EVENT_DELETEGAMEOBJECTS)
  {
    m_active = false;
  }
  else if (evt.type == EVENT_FREEZEALL)
  {
    m_frozen = true;
  }
}