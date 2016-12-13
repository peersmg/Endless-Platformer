#include "GameOver.h"
#include "gamecode.h"
#include "myinputs.h"
#include "MainMenu.h"
#include "EndlessManager.h"

GameOver::GameOver() : GameObject(UI)
{

}

void GameOver::Initialise(double score, wall* topWall, wall* bottomWall, BgBlock* bgBlock)
{
  m_menuOption = 0;
  m_score = score;

  m_pTopWall = topWall;
  m_pBottomWall = bottomWall;
  m_pBgBlock = bgBlock;
}

void GameOver::Update(float deltaTime)
{

}

void GameOver::Draw()
{
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  
  pTheDrawEngine->WriteText(0, 900, L"Game Over", m_pBgBlock->GetColor(), 1, TOPCENTRE, 0);

  MyDrawEngine::GetInstance()->WriteDouble(-100, 500, m_score, MyDrawEngine::D3DWHITE, 1);

  const int NUMOPTIONS = 2;

  if (m_menuOption == 1)
  {
    pTheDrawEngine->WriteText(0, 50 - 175, L"Play Again", MyDrawEngine::D3DWHITE, 0, MIDDLECENTRE, 0);
  }
  else
  {
    pTheDrawEngine->WriteText(0, 50 - 175, L"Play Again", MyDrawEngine::D3DWHITE, 0, MIDDLECENTRE);
  }

  if (m_menuOption == 2)
  {
    pTheDrawEngine->WriteText(0, -300 - 175, L"Main Menu", MyDrawEngine::D3DWHITE, 0, MIDDLECENTRE, 0);
  }
  else
  {
    pTheDrawEngine->WriteText(0, -300 - 175, L"Main Menu", MyDrawEngine::D3DWHITE, 0, MIDDLECENTRE);
  }

  MyInputs* pInputs = MyInputs::GetInstance();

  pInputs->SampleKeyboard();
  if (pInputs->NewKeyPressed(DIK_UP))
  {
    m_menuOption--;
  }
  if (pInputs->NewKeyPressed(DIK_DOWN))
  {
    m_menuOption++;
  }
  if (m_menuOption<0)
  {
    m_menuOption = 0;
  }
  else if (m_menuOption >= NUMOPTIONS)
  {
    m_menuOption = NUMOPTIONS - 1;
  }

  if (pInputs->NewKeyPressed(DIK_RETURN))
  {
    if (m_menuOption == 0)
    {

      EndlessManager* pGM = new EndlessManager;
      pGM->Initialise(m_pTopWall, m_pBottomWall, m_pBgBlock);
      Game::instance.m_objects.AddItem(pGM, false);

      m_active = false;
    }

    if (m_menuOption == 1)
    {
      MainMenu* pMainMenu = new MainMenu;
      pMainMenu->Initialise(false, m_pTopWall, m_pBottomWall, m_pBgBlock);
      Game::instance.m_objects.AddItem(pMainMenu, false);

      m_active = false;
    }
  }

  if (m_menuOption == 0)
  {
    m_pTopWall->SetPosition(50);
    m_pBottomWall->SetPosition(-300);
  }
  if (m_menuOption == 1)
  {
    m_pTopWall->SetPosition(-300);
    m_pBottomWall->SetPosition(-650);
  }
}

void GameOver::HandleEvent(Event evt)
{

}


//Useless
IShape2D& GameOver::GetCollisionShape()
{
  return m_collisionShape;
}
void GameOver::ProcessCollision(GameObject &other)
{ }
