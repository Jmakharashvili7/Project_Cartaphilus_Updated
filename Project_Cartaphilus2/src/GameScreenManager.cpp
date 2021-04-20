#include "GameScreenManager.h"
#include "GameScreen.h"
#include "FirstLevel.h"
#include "MainMenu.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;
	m_current_level = nullptr;
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;
	delete m_current_level;
	m_current_level = nullptr;
}

void GameScreenManager::Render()
{
	m_current_level->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	m_current_level->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	// make sure we're not trying to change to the same screen
	if (m_current_screen != new_screen)
	{
		// temp variables to initialize level classes before casting to GameScreen
		FirstLevel* tempScreen;
		MainMenu* tempScreenMenu;

		switch (new_screen)
		{
		case SCREENS::SCREEN_MENU:
			// delete the current level if it isnt null
			if (m_current_level != nullptr)
			{
				delete m_current_level;
			}

			/* change screens (need a temp variable to initalize the level class and then cast it to
			   GameScreen that the level class inherits from) */
			tempScreenMenu = new MainMenu(m_renderer);
			m_current_level = (GameScreen*)tempScreenMenu;

			// set the new screen 
			m_current_screen = SCREENS::SCREEN_MENU;

			// set the temp screen variable to null as we dont need it anymore
			tempScreenMenu = nullptr;
			break;
		case SCREENS::SCREEN_LEVEL1:
			// delete the current level if it isnt null
			if (m_current_level != nullptr)
			{
				delete m_current_level;
			}

			/* change screens (need a temp variable to initalize the level class and then cast it to
			   GameScreen that the level class inherits from) */
			tempScreen = new FirstLevel(m_renderer);
			m_current_level = (GameScreen*)tempScreen;

			// set the new screen 
			m_current_screen = SCREENS::SCREEN_LEVEL1;

			// set the temp screen variable to null as we dont need it anymore
			tempScreen = nullptr;
			break;
		}
	}
}
