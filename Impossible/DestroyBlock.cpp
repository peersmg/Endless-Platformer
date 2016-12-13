#include "DestroyBlock.h"


DestroyBlock::DestroyBlock() : GameObject(DESTROY)
{
}

void DestroyBlock::Initialise()
{
  m_handleEvents = true;
}

IShape2D& DestroyBlock::GetCollisionShape()
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();

  Rectangle2D screen = pTheDrawEngine->GetViewport();
  float screenHeight = screen.GetBottomLeft().YValue - screen.GetTopRight().YValue;

  m_collisionShape.PlaceAt(Vector2D(screen.GetBottomLeft().XValue-400, -(screenHeight/2)),
    Vector2D(screen.GetBottomLeft().XValue-200, (screenHeight / 2)));

  return m_collisionShape;
}

void DestroyBlock::ProcessCollision(GameObject &other)
{
}

void DestroyBlock::Update(float deltaTime)
{

}

void DestroyBlock::Draw()
{
  
}

void DestroyBlock::HandleEvent(Event evt)
{
  if (evt.type == EVENT_DELETEGAMEOBJECTS)
  {
    m_active = false;
  }
}