#include "MainMenu.h"
#include "gamecode.h"
#include "myinputs.h"
#include "BgBlock.h"
#include <time.h>
#include "EndlessManager.h"
#include "objecttypes.h"

MainMenu::MainMenu() : GameObject(UI)
{

}

void MainMenu::Initialise(bool firstCreate, wall* topWall, wall* bottomWall, BgBlock* bgBlock)
{
  m_menuOption = 0;
  m_gameMode = 0;
  m_modeTextPosition = 0;
  m_modeTextTargetPosition = m_modeTextPosition;
  m_handleEvents = true;
  m_rectPosition = 100;
  m_rectHeight = 300;
  m_rectTargetPosition = m_rectPosition;
  m_titleRotation = 0;
  m_titleTargetRotation = 0.1;
  m_pTopWall = topWall;
  m_pBottomWall = bottomWall;
  m_pBgBlock = bgBlock;

  m_titleColorOne = color(RED);
  m_titleTargetColorOne = color(RED_L);
  m_titleColorTwo = color(LIGHTYELLOW_L);
  m_titleTargetColorTwo = color(LIGHTYELLOW);
    
  m_bgColor = color(BLUE);
  m_bgTargetColor = color(BLUE);
  m_bgTargetColorType = BLUE;

  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  Rectangle2D screen = pTheDrawEngine->GetViewport();
  float screenWidth = screen.GetBottomLeft().XValue - screen.GetBottomRight().XValue;
  float screenHeight = screen.GetBottomLeft().YValue - screen.GetBottomRight().YValue;

  if (firstCreate)
  {
    // Add walls and player to the game
    m_pTopWall = new wall;
    m_pTopWall->Initialise(screenHeight * 2, 600,
      color(LIGHTBLUE), color(LIGHTBLUE), 1, true);
    Game::instance.m_objects.AddItem(m_pTopWall, true);

    m_pBottomWall = new wall;
    m_pBottomWall->Initialise(-screenHeight * 2, 600,
      color(LIGHTBLUE), color(LIGHTBLUE), 1, false);
    Game::instance.m_objects.AddItem(m_pBottomWall, true);

    //Add BG
    m_pBgBlock = new BgBlock;
    m_pBgBlock->Initialise(0, screenWidth,
      m_bgColor, m_bgTargetColor, 1);
    Game::instance.m_objects.AddItem(m_pBgBlock, false);
  }
}

void MainMenu::Update(float deltaTime)
{
  if (m_modeTextPosition > m_modeTextTargetPosition)
  {
    m_modeTextPosition -= 2800 * deltaTime;
    if (m_modeTextPosition < m_modeTextTargetPosition)
    {
      m_modeTextPosition = m_modeTextTargetPosition;
    }
  }
  else if (m_modeTextPosition < m_modeTextTargetPosition)
  {
    m_modeTextPosition += 2800 * deltaTime;
    if (m_modeTextPosition > m_modeTextTargetPosition)
    {
      m_modeTextPosition = m_modeTextTargetPosition;
    }
  }

  if (m_titleRotation > m_titleTargetRotation)
  {
    m_titleRotation -= 0.005;
    if (m_titleRotation < m_titleTargetRotation)
    {
      m_titleRotation = m_titleTargetRotation;
    }
  }
  else if (m_titleRotation < m_titleTargetRotation)
  {
    m_titleRotation += 0.005;
    if (m_titleRotation > m_titleTargetRotation)
    {
      m_titleRotation = m_titleTargetRotation;
    }
  }
  else
  {
    if (m_titleTargetRotation > 0)
    {
      m_titleTargetRotation = -0.1;
    }
    else
    {
      m_titleTargetRotation = 0.1;
    }
  }

  if (!m_titleColorOne.Blend(m_titleTargetColorOne, 1))
  {
    if (m_titleTargetColorOne.GetColor() == color(RED).GetColor())
    {
      m_titleTargetColorOne = color(RED_L);
    }
    else
    {
      m_titleTargetColorOne = color(RED);
    }
  }

  if (!m_titleColorTwo.Blend(m_titleTargetColorTwo, 1))
  {
    if (m_titleTargetColorTwo.GetColor() == color(LIGHTYELLOW).GetColor())
    {
      m_titleTargetColorTwo = color(LIGHTYELLOW_L);
    }
    else
    {
      m_titleTargetColorTwo = color(LIGHTYELLOW);
    }
  }

  if (m_bgColor.GetColor() == m_bgTargetColor.GetColor())
  {
      ChangeColor();
  }

  m_bgColor.Blend(m_bgTargetColor, 1);
  MoveWall();
}

void MainMenu::Draw()
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  Rectangle2D screen = pTheDrawEngine->GetViewport();
  float screenWidth = screen.GetBottomLeft().XValue - screen.GetBottomRight().XValue;

  unsigned int black = D3DCOLOR_ARGB(255, 1, 1, 1);

  const int NUMOPTIONS = 4;
  wchar_t screenMode[15] = L"Go Fullscreen";

  pTheDrawEngine->WriteText(0, 900, L"Game Name", m_pBgBlock->GetColor(), 1, TOPCENTRE, m_titleRotation,
    Vector2D(1 + m_titleRotation, 1 + m_titleRotation));
  
  if (pTheDrawEngine->IsWindowFullScreen())
  {
    wcscpy_s(screenMode, 15, L"Go Windowed");
  }

  if (m_menuOption == 0)
  {
    if (m_gameMode == 0)
    {
      pTheDrawEngine->WriteText(m_modeTextPosition, 400 - 175, L"Challenges"
        , MyDrawEngine::D3DWHITE, 0, MIDDLECENTRE, 0, Vector2D(0.9 + m_titleRotation, 0.9 + m_titleRotation));
      pTheDrawEngine->WriteText(m_modeTextPosition + 1000, 400 - 175, L"Endless", MyDrawEngine::D3DWHITE, 0, MIDDLECENTRE);
    }
    else
    {
      pTheDrawEngine->WriteText(m_modeTextPosition, 400 - 175, L"Challenges", MyDrawEngine::D3DWHITE, 0, MIDDLECENTRE);
      pTheDrawEngine->WriteText(m_modeTextPosition + 1000, 400 - 175, L"Endless", MyDrawEngine::D3DWHITE, 0, MIDDLECENTRE, 0, Vector2D(0.9 + m_titleRotation, 0.9 + m_titleRotation));
    }
  }
  else
  {
    pTheDrawEngine->WriteText(m_modeTextPosition, 400 - 175, L"Challenges", MyDrawEngine::D3DWHITE, 0, MIDDLECENTRE);
    pTheDrawEngine->WriteText(m_modeTextPosition + 1000, 400 - 175, L"Endless", MyDrawEngine::D3DWHITE, 0, MIDDLECENTRE);
  }

  if (m_menuOption == 1)
  {
    pTheDrawEngine->WriteText(0, 50 - 175, screenMode, MyDrawEngine::D3DWHITE, 0, MIDDLECENTRE, 0, Vector2D(0.9 + m_titleRotation, 0.9 + m_titleRotation));
  }
  else
  {
    pTheDrawEngine->WriteText(0, 50 - 175, screenMode, MyDrawEngine::D3DWHITE, 0, MIDDLECENTRE);
  }

  if (m_menuOption == 2)
  {
    pTheDrawEngine->WriteText(0, -300 - 175, L"Credits", MyDrawEngine::D3DWHITE, 0, MIDDLECENTRE, 0, Vector2D(0.9 + m_titleRotation, 0.9 + m_titleRotation));
  }
  else
  {
    pTheDrawEngine->WriteText(0, -300 - 175, L"Credits", MyDrawEngine::D3DWHITE, 0, MIDDLECENTRE);
  }

  if (m_menuOption == 3)
  {
    pTheDrawEngine->WriteText(0, -650 - 175, L"Quit", MyDrawEngine::D3DWHITE, 0, MIDDLECENTRE, 0, Vector2D(0.9 + m_titleRotation, 0.9 + m_titleRotation));
  }
  else
  {
    pTheDrawEngine->WriteText(0, -650 - 175, L"Quit", MyDrawEngine::D3DWHITE, 0, MIDDLECENTRE);
  }
  
  MyInputs* pInputs = MyInputs::GetInstance();
  
  pInputs->SampleKeyboard();
  if (pInputs->NewKeyPressed(DIK_UP))
  {
    m_menuOption--;

    if (m_menuOption < 0)
    {
      m_menuOption = NUMOPTIONS-1;
    }
  }
  if (pInputs->NewKeyPressed(DIK_DOWN))
  {
    m_menuOption++;

    if (m_menuOption >= NUMOPTIONS)
    {
      m_menuOption = 0;
    }
  }

  if (pInputs->NewKeyPressed(DIK_LEFT) && m_menuOption == 0 && m_gameMode == 1)
  {
    m_gameMode = 0;
    m_modeTextTargetPosition = 0;
  }

  if (pInputs->NewKeyPressed(DIK_RIGHT) && m_menuOption == 0 && m_gameMode == 0)
  {
    m_gameMode = 1;
    m_modeTextTargetPosition = -1000;
  }

  if (pInputs->NewKeyPressed(DIK_RETURN))
  {
    if (m_menuOption == 0)
    {
      if (m_gameMode == 0)
      {
        // Go to challanges menu
      }
      else
      {
        // Code to set up your game
        EndlessManager* pGM = new EndlessManager;
        pGM->Initialise(m_pTopWall, m_pBottomWall, m_pBgBlock);
        Game::instance.m_objects.AddItem(pGM, false);

        m_active = false;
      }
    }

    if (m_menuOption == 1)
    {
      if (MyDrawEngine::GetInstance()->IsWindowFullScreen())
      {
        MyDrawEngine::GetInstance()->GoWindowed();
      }
      else
      {
        MyDrawEngine::GetInstance()->GoFullScreen();
      }
    }
    if (m_menuOption == 3)
    {
      Game::instance.ChangeState(Game::instance.GAMEOVER);
    }
  }
  
}

void MainMenu::MoveWall()
{
  if (m_menuOption == 0)
  {
    m_pTopWall->SetPosition(400);
    m_pBottomWall->SetPosition(50);
  }
  if (m_menuOption == 1)
  {
    m_pTopWall->SetPosition(50);
    m_pBottomWall->SetPosition(-300);
  }
  if (m_menuOption == 2)
  {
    m_pTopWall->SetPosition(-300);
    m_pBottomWall->SetPosition(-650);
  }
  if (m_menuOption == 3)
  {
    m_pTopWall->SetPosition(-650);
    m_pBottomWall->SetPosition(-1000);
  }
}

void MainMenu::HandleEvent(Event evt)
{
  if (evt.type == EVENT_DELETEGAMEOBJECTS)
  {
    m_active = false;
  }
}

void MainMenu::ChangeColor()
{
  
  if (m_bgTargetColorType == BLUE)
  {
    m_bgTargetColor = color(BLUE_L);
    m_bgTargetColorType = BLUE_L;
  }
  else if (m_bgTargetColorType == BLUE_L)
  {
    m_bgTargetColor = color(BLUE);
    m_bgTargetColorType = BLUE;
  }

  if (m_bgTargetColorType == RED)
  {
    m_bgTargetColor = color(RED_L);
    m_bgTargetColorType = RED_L;
  }
  else if (m_bgTargetColorType == RED_L)
  {
    m_bgTargetColor = color(RED);
    m_bgTargetColorType = RED;
  }
  
    //m_colorDelay = 0;
  //}

  //New color event
  Event evt;
  evt.position = m_position;
  evt.pSource = this;
  evt.type = EVENT_COLORCHANGE;
  evt.newPulseRate = 1;
  evt.data1 = 0;
  evt.newTargetColor = m_bgTargetColor;
  Game::instance.NotifyEvent(evt);
}


//Useless
IShape2D& MainMenu::GetCollisionShape()
{
  return m_collisionShape;
}
void MainMenu::ProcessCollision(GameObject &other)
{ }
