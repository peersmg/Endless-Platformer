// GameCode.cpp		


// Version  13.03	Draw Engine no longer requires a height / width
// Version 13.0   Update to wchar_t and wstring

//Version 11			5/3/08	
// These three functions form the basis of a game loop in the window created in the
// wincode.cpp file

#include "gamecode.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "myinputs.h"
#include <time.h>
#include "gametimer.h"
#include "errorlogger.h"
#include <math.h>
#include "shapes.h"
#include "ObjectManager.h"
#include "EndlessManager.h"
#include "MainMenu.h"

ErrorType Game::Main()
// Called repeatedly - the game loop
{
	//Flip and clear the back buffer
	MyDrawEngine* pTheDrawEngine= MyDrawEngine::GetInstance();
	pTheDrawEngine->Flip();
	pTheDrawEngine->ClearBackBuffer();

	ErrorType err;

	switch(m_currentState)
	{
	case MENU:

    err = Update();

		break;
	case RUNNING:


    err = Update();
		break;

	case GAMEOVER:

		err = FAILURE;
	default:
		// Not a valid state
		err = FAILURE;
    break;
	}

	return err;
}

void Game::ChangeState(GameState newState)
{
	// Very crude state system
	// Close old state
	switch(m_currentState)
	{
	case MENU:
    
		break;
	case RUNNING:
 
		break;
	}

	// Change the state
	m_currentState = newState;
	m_menuOption = 0;

	// Transition to new state
	switch(m_currentState)
	{
	case MENU:

		break;
	case RUNNING:

		break;
	}
}

ErrorType Game::Setup(bool bFullScreen, HWND hwnd, HINSTANCE hinstance)
// Called once before entering game loop. 
{
	// Create the engines - this should be done before creating other DDraw objects
	if(FAILED(MyDrawEngine::Start(hwnd, bFullScreen)))
	{
		ErrorLogger::Writeln(L"Failed to start MyDrawEngine");
		return FAILURE;
	}
	if(FAILED(MySoundEngine::Start(hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MySoundEngine");
		return FAILURE;
	}
	if(FAILED(MyInputs::Start(hinstance, hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MyInputs");
		return FAILURE;
	}
  // Seed rand
  srand(unsigned(time(NULL)));

	return (SUCCESS);
}

void Game::Shutdown()
// Called once before entering game loop. 
{
	m_objects.DeleteAllObjects();

	// (engines must be terminated last)
	MyDrawEngine::Terminate();
	MySoundEngine::Terminate();
	MyInputs::Terminate();
}
// **********************************************************************************************
// The game !!! *********************************************************************************
// **********************************************************************************************

ErrorType Game::Menu()
{
	// Code for a basic main menu

  m_objects.UpdateAll();
  m_objects.DrawAll();

	return SUCCESS;
}

ErrorType Game::StartOfGame()
{
  

	return SUCCESS;
}

ErrorType Game::Update()
{
	m_objects.UpdateAll();
	m_objects.ProcessCollisions();
	m_objects.DrawAll();

  if (m_menuCreated == false)
  {
    // Add main menu object here
    MainMenu* pMainMenu = new MainMenu;
    pMainMenu->Initialise(true);
    m_objects.AddItem(pMainMenu, false);

    m_menuCreated = true;
  }

	// Garbage collect any objects. Possibly slow
	m_objects.DeleteInactiveItems();

	// Any code here to run the game,
	// but try to do this within a game object if possible

	return SUCCESS;
}

ErrorType Game::EndOfGame()
// called when the game ends by returning to main menu
{
	// Add code here to tidy up ********************************
	
	
	
	
	
	
	
	
	
	m_objects.DeleteAllObjects();

	return SUCCESS;
}

Game::Game()
{
	// No-op
}

Game::~Game()
{
	// No-op
}


void Game::NotifyEvent(Event evt)
{
	m_objects.HandleEvent(evt);
}

Game Game::instance;