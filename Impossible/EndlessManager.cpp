#include "EndlessManager.h"
#include "player.h"
#include "ObjectManager.h"
#include "objecttypes.h"
#include "gamecode.h"
#include "block.h"
#include "DestroyBlock.h"
#include "GameOver.h"
#include "BgBlock.h"
#include "textObj.h"

EndlessManager::EndlessManager() : GameObject(GM)
{

}

void EndlessManager::Initialise(wall* topWall, wall* bottomWall, BgBlock* bgBlock)
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  m_handleEvents = true;

  m_phaseCount = 0;
  m_obsticles = 0;
  m_waiting = true;
  m_pulseRate = 1;
  m_colorDelay = 0;
  m_score = 0;
  m_frozen = false;
  m_color = color(BLUE_L);
  m_targetColor = color(BLUE_L);
  m_targetColorType = BLUE_L;
  m_wallsAdded = false;
  m_gameMode = NORMAL;

  m_pBgBlock = bgBlock;
  m_pTopWall = topWall;
  m_pBottomWall = bottomWall;
  
  Rectangle2D screen = pTheDrawEngine->GetViewport();

  m_pTopWall->SetPosition(400);
  m_pBottomWall->SetPosition(-400);
}

void EndlessManager::Update(float deltaTime)
{
  if (!m_frozen)
  {
    if (m_color.GetColor() == m_targetColor.GetColor())
    {
      ChangeColor();
    }
    else
    {
      m_color.Blend(m_targetColor, m_pulseRate);
    }

    if (m_obsticles == 0 && !m_waiting && m_pTopWall->InPosition() && m_pBottomWall->InPosition())
    {
      NextMode();
      m_phaseCount++;
    }

    if (m_obsticles == 0 && m_waiting && m_pTopWall->InPosition() && m_pBottomWall->InPosition())
    {
      NextPhase(m_gameMode);
      m_phaseCount++;
    }
    
    m_score += deltaTime;
    m_score = round(m_score * 100.0) / 100.0;
  }

  m_topWallPos = m_pTopWall->GetPosition().YValue;
  m_bottomWallPos = m_pBottomWall->GetPosition().YValue;

  if (!m_wallsAdded)
  {
    MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
    Rectangle2D screen = pTheDrawEngine->GetViewport();
    float m_wallHeight = 600;
    float screenWidth = screen.GetBottomLeft().XValue - screen.GetBottomRight().XValue;

    DestroyBlock* pDestroyBlock = new DestroyBlock;
    pDestroyBlock->Initialise();
    Game::instance.m_objects.AddItem(pDestroyBlock, true);

    player* pPlayer = new player;
    pPlayer->Initialise(-200, m_pTopWall, m_pBottomWall);
    Game::instance.m_objects.AddItem(pPlayer, true);

    m_wallsAdded = true;
  }
}

void EndlessManager::NextMode()
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  Rectangle2D screen = pTheDrawEngine->GetViewport();
  float randVal = rand() % 30;
  
  //Normal mode
  if (randVal < 10)
  {
    if (m_gameMode == ROCKET)
    {
      Event evt;
      evt.pSource = this;
      evt.type = EVENT_DISABLEROCKETMODE;
      Game::instance.NotifyEvent(evt);
    }
    else if (m_gameMode == JUMP)
    {
      Event evt;
      evt.pSource = this;
      evt.type = EVENT_DISABLEJUMPMODE;
      Game::instance.NotifyEvent(evt);
    }

    m_gameMode = NORMAL;
  }
  //Rocket Mode
  else if (randVal < 20)
  {
    if (m_gameMode == JUMP)
    {
      Event evt;
      evt.pSource = this;
      evt.type = EVENT_DISABLEJUMPMODE;
      Game::instance.NotifyEvent(evt);

      evt.pSource = this;
      evt.type = EVENT_ENABLEROCKETMODE;
      Game::instance.NotifyEvent(evt);
    }
    else if (m_gameMode == NORMAL)
    {
      Event evt;
      evt.pSource = this;
      evt.type = EVENT_ENABLEROCKETMODE;
      Game::instance.NotifyEvent(evt);
    }

    m_gameMode = ROCKET;
  }
  
  //Jump mode
  else
  {
  
    if (m_gameMode == ROCKET)
    {
      Event evt;
      evt.pSource = this;
      evt.type = EVENT_DISABLEROCKETMODE;
      Game::instance.NotifyEvent(evt);

      evt.pSource = this;
      evt.type = EVENT_ENABLEJUMPMODE;
      Game::instance.NotifyEvent(evt);
    }
    else if (m_gameMode == NORMAL)
    {
      Event evt;
      evt.pSource = this;
      evt.type = EVENT_ENABLEJUMPMODE;
      Game::instance.NotifyEvent(evt);
    }

    m_gameMode = JUMP;
  }
  
  m_waiting = true;
  NextPhase(m_gameMode);
}

void EndlessManager::NextPhase(GameMode mode)
{
  m_colorDelay = 1;

  if (mode == NORMAL)
  {
    NormalPhase();
  }
  else if (mode == ROCKET)
  {
    RocketPhase();
  }
  else if (mode == JUMP)
  {
    JumpPhase();
  }
}

void EndlessManager::Draw()
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  Rectangle2D screen = pTheDrawEngine->GetViewport();

  //Score text
  MyDrawEngine::GetInstance()->WriteDouble(screen.GetTopLeft().XValue, screen.GetTopLeft().YValue, m_score, MyDrawEngine::D3DWHITE);
}

void EndlessManager::ChangeColor()
{
  int randNum = rand() % 10;
  
  if (randNum < 4 || m_colorDelay == 0)
  {
    if (m_targetColorType == BLUE)
    {
      m_targetColor = color(BLUE_L);
      m_targetColorType = BLUE_L;
    }
    else if (m_targetColorType == BLUE_L)
    {
      m_targetColor = color(BLUE);
      m_targetColorType = BLUE;
    }
    
    if (m_targetColorType == RED)
    {
      m_targetColor = color(RED_L);
      m_targetColorType = RED_L;
    }
    else if (m_targetColorType == RED_L)
    {
      m_targetColor = color(RED);
      m_targetColorType = RED;
    }
  }
  else
  {
    if (m_targetColorType == RED)
    {
      m_targetColor = color(BLUE);
      m_targetColorType = BLUE;
    }
    else if (m_targetColorType == RED_L)
    {
      m_targetColor = color(BLUE);
      m_targetColorType = BLUE;
    }

    else if (m_targetColorType == BLUE)
    {
      m_targetColor = color(RED);
      m_targetColorType = RED;
    }
    else if (m_targetColorType == BLUE_L)
    {
      m_targetColor = color(RED);
      m_targetColorType = RED;
    }

    m_colorDelay = 0;
  }

  //New color event
  Event evt;
  evt.position = m_position;
  evt.pSource = this;
  evt.type = EVENT_COLORCHANGE;
  evt.newPulseRate = m_pulseRate;
  evt.data1 = 0;
  evt.newTargetColor = m_targetColor;
  Game::instance.NotifyEvent(evt);
}

void EndlessManager::HandleEvent(Event evt)
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  Rectangle2D screen = pTheDrawEngine->GetViewport();

  if (evt.type == EVENT_OBJECTDESTROYED)
  {
    m_obsticles--;
  }
  else if (evt.type == EVENT_ENABLEROCKETMODE)
  {
    textObj* ptextObj = new textObj;
    ptextObj->Initialise(Vector2D(screen.GetBottomRight().XValue, 0), L"Rocket Mode Enabled!", 20, 2800, Vector2D(1, 1));
    Game::instance.m_objects.AddItem(ptextObj, true);
  }
  else if(evt.type == EVENT_DISABLEROCKETMODE)
  {
    /*
    textObj* ptextObj = new textObj;
    ptextObj->Initialise(Vector2D(screen.GetBottomRight().XValue, 0), L"Rocket Mode Disabled!", 21, 2800, Vector2D(1, 1));
    Game::instance.m_objects.AddItem(ptextObj, true);
    */
  }
  else if (evt.type == EVENT_ENABLEJUMPMODE)
  {
    textObj* ptextObj = new textObj;
    ptextObj->Initialise(Vector2D(screen.GetBottomRight().XValue, 0), L"Jump Mode Enabled!", 18, 2800, Vector2D(1, 1));
    Game::instance.m_objects.AddItem(ptextObj, true);
  }
  else if (evt.type == EVENT_DISABLEJUMPMODE)
  {
    /*
    textObj* ptextObj = new textObj;
    ptextObj->Initialise(Vector2D(screen.GetBottomRight().XValue, 0), L"Jump Mode Disabled!", 19, 2800, Vector2D(1, 1));
    Game::instance.m_objects.AddItem(ptextObj, true);
    */
  }
  else if (evt.type == EVENT_FREEZEALL)
  {
    m_frozen = true;
  }
  else if (evt.type == EVENT_GAMEOVER)
  {
    Event evt;
    evt.pSource = this;
    evt.type = EVENT_DELETEGAMEOBJECTS;
    Game::instance.NotifyEvent(evt);

    //Create game over screen
  }
  else if (evt.type == EVENT_DELETEGAMEOBJECTS)
  {
    GameOver* pGameOver = new GameOver;
    pGameOver->Initialise(m_score, m_pTopWall, m_pBottomWall, m_pBgBlock);
    Game::instance.m_objects.AddItem(pGameOver, false);

    m_active = false;
  }
}

void EndlessManager::NormalPhase()
{
  if (m_pBottomWall->InPosition())
  {
    m_waiting = false;

    MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();

    for (int i = 0; i < 5; i++)
    {
      block* pSpike = new block;
      pSpike->Initialise(Vector2D((pTheDrawEngine->GetScreenWidth() * 4) + 1250 + (2500 * i), m_pBottomWall->GetPosition().YValue + 224),
        Vector2D(124, 448), 2800,
        m_color,
        m_targetColor,
        m_pulseRate);
      Game::instance.m_objects.AddItem(pSpike, true);

      block* pSpike2 = new block;
      pSpike2->Initialise(Vector2D((pTheDrawEngine->GetScreenWidth() * 4) + (2500 * i), m_pTopWall->GetPosition().YValue - 224),
        Vector2D(124, 448), 2800,
        m_color,
        m_targetColor,
        m_pulseRate);
      Game::instance.m_objects.AddItem(pSpike2, true);

      m_obsticles += 2;
    }
  }
}

void EndlessManager::RocketPhase()
{
  if (m_pBottomWall->InPosition())
  {
    m_waiting = false;

    MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
    
    if (rand() % 20 < 10)
    {
      for (int i = 0; i < 5; i++)
      {
        block* pSpike = new block;
        pSpike->Initialise(Vector2D((pTheDrawEngine->GetScreenWidth() * 4) + 1250 + (2500 * i), m_pBottomWall->GetPosition().YValue + 224),
          Vector2D(124, 448), 2800,
          m_color,
          m_targetColor,
          m_pulseRate);
        Game::instance.m_objects.AddItem(pSpike, true);

        block* pSpike2 = new block;
        pSpike2->Initialise(Vector2D((pTheDrawEngine->GetScreenWidth() * 4) + (2500 * i), m_pTopWall->GetPosition().YValue - 224),
          Vector2D(124, 448), 2800,
          m_color,
          m_targetColor,
          m_pulseRate);
        Game::instance.m_objects.AddItem(pSpike2, true);

        m_obsticles += 2;
      }
    }
    else
    {
      for (int i = 0; i < 5; i++)
      {

        float randVal = (rand() % 750);

        float bottomBlockHeight = randVal;
        float topBlockHeight = (1000 - randVal) - (rand() % 200 + 250);

        block* pSpike = new block;
        pSpike->Initialise(Vector2D((pTheDrawEngine->GetScreenWidth() * 4) + (2500 * i), m_pBottomWall->GetPosition().YValue + (bottomBlockHeight / 2)),
          Vector2D(224, bottomBlockHeight), 2800,
          m_color,
          m_targetColor,
          m_pulseRate);
        Game::instance.m_objects.AddItem(pSpike, true);

        block* pSpike2 = new block;
        pSpike2->Initialise(Vector2D((pTheDrawEngine->GetScreenWidth() * 4) + (2500 * i), m_pTopWall->GetPosition().YValue - (topBlockHeight / 2)),
          Vector2D(224, topBlockHeight), 2800,
          m_color,
          m_targetColor,
          m_pulseRate);
        Game::instance.m_objects.AddItem(pSpike2, true);

        m_obsticles += 2;
      }
    }
  }
}

void EndlessManager::JumpPhase()
{
  if (m_pBottomWall->InPosition())
  {
    m_waiting = false;

    MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();

    for (int i = 0; i < 5; i++)
    {

      float randVal = (rand() % 600);

      float bottomBlockHeight = randVal;
      float topBlockHeight = (1400-randVal)-(rand()%300 + 250);

      block* pSpike = new block;
      pSpike->Initialise(Vector2D((pTheDrawEngine->GetScreenWidth() * 4) + (2500 * i), m_pBottomWall->GetPosition().YValue + (bottomBlockHeight / 2)),
        Vector2D(224, bottomBlockHeight), 2800,
        m_color,
        m_targetColor,
        m_pulseRate);
      Game::instance.m_objects.AddItem(pSpike, true);

      block* pSpike2 = new block;
      pSpike2->Initialise(Vector2D((pTheDrawEngine->GetScreenWidth() * 4) + (2500 * i), m_pTopWall->GetPosition().YValue - (topBlockHeight/2)),
        Vector2D(224, topBlockHeight), 2800,
        m_color,
        m_targetColor,
        m_pulseRate);
      Game::instance.m_objects.AddItem(pSpike2, true);

      m_obsticles += 2;
    }
  }
}

//Useless
IShape2D& EndlessManager::GetCollisionShape()
{ return m_collisionShape; }
void EndlessManager::ProcessCollision(GameObject &other)
{ }