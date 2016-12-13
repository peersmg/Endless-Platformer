#include "BgBlock.h"

BgBlock::BgBlock() : GameObject(BACKGROUND)
{

}

void BgBlock::Initialise(float xPos, float width, color startColor, color targetColor, int pulseRate)
{
  m_handleEvents = true;
  m_width = width;
  m_position = Vector2D(xPos, 0);
  m_color = startColor;
  m_targetColor = targetColor;
  m_pulseRate = pulseRate;
}

IShape2D& BgBlock::GetCollisionShape()
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();

  Rectangle2D screen = pTheDrawEngine->GetViewport();
  float screenHeight = screen.GetBottomLeft().YValue - screen.GetTopRight().YValue;

  m_collisionShape.PlaceAt(Vector2D(m_position.XValue - (m_width / 2), m_position.YValue - screenHeight),
    Vector2D(m_position.XValue + (m_width / 2), m_position.YValue + screenHeight));

  return m_collisionShape;
}

void BgBlock::Update(float deltaTime)
{
  m_color.Blend(m_targetColor, m_pulseRate);
}

unsigned int BgBlock::GetColor()
{
  return m_color.GetColor();
}

void BgBlock::Draw()
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  Rectangle2D wallObj;

  Rectangle2D screen = pTheDrawEngine->GetViewport();
  float screenHeight = screen.GetBottomLeft().YValue - screen.GetTopRight().YValue;

  wallObj.PlaceAt(Vector2D(m_position.XValue - (m_width / 2), m_position.YValue - screenHeight),
    Vector2D(m_position.XValue + (m_width / 2), m_position.YValue + screenHeight));

  pTheDrawEngine->FillRect(wallObj, m_color.GetColor());
}

void BgBlock::HandleEvent(Event evt)
{
  if (evt.type == EVENT_COLORCHANGE)
  {
    if (evt.data1 == 0)
    {
      if (evt.newTargetColor.GetColor() == color(GREEN).GetColor())
        m_targetColor = color(LIGHTGREEN);
      if (evt.newTargetColor.GetColor() == color(GREEN_L).GetColor())
        m_targetColor = color(LIGHTGREEN_L);

      if (evt.newTargetColor.GetColor() == color(PURPLE).GetColor())
        m_targetColor = color(LIGHTPURPLE);
      if (evt.newTargetColor.GetColor() == color(PURPLE_L).GetColor())
        m_targetColor = color(LIGHTPURPLE_L);

      if (evt.newTargetColor.GetColor() == color(BLUE).GetColor())
        m_targetColor = color(LIGHTBLUE);
      if (evt.newTargetColor.GetColor() == color(BLUE_L).GetColor())
        m_targetColor = color(LIGHTBLUE_L);

      if (evt.newTargetColor.GetColor() == color(YELLOW).GetColor())
        m_targetColor = color(LIGHTYELLOW);
      if (evt.newTargetColor.GetColor() == color(YELLOW_L).GetColor())
        m_targetColor = color(LIGHTYELLOW_L);

      if (evt.newTargetColor.GetColor() == color(RED).GetColor())
        m_targetColor = color(LIGHTRED);
      if (evt.newTargetColor.GetColor() == color(RED_L).GetColor())
        m_targetColor = color(LIGHTRED_L);

      if (evt.newTargetColor.GetColor() == color(ORANGE).GetColor())
        m_targetColor = color(LIGHTORANGE);
      if (evt.newTargetColor.GetColor() == color(ORANGE_L).GetColor())
        m_targetColor = color(LIGHTORANGE_L);

      m_pulseRate = evt.newPulseRate;
    }
    else if (evt.data1 == 1)
    {
      m_targetColor = evt.newTargetColor;
      m_pulseRate = 1;
    }
  }
  else if (evt.type == EVENT_DELETEGAMEOBJECTS)
  {
    //m_active = false;
  }
  else if (evt.type == EVENT_FREEZEALL)
  {
    m_frozen = true;
  }
}

void BgBlock::SetColor(color newTarget)
{
  m_targetColor = newTarget;
}


void BgBlock::ProcessCollision(GameObject &other)
{ }