#include <iostream>
#include "MainMenu.h"
#include "Texture2D.h"

MainMenu::MainMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetupLevel();
	m_renderer = renderer;
}

MainMenu::~MainMenu()
{
	delete m_background_texture;
	m_background_texture = nullptr;
}

void MainMenu::Render()
{
	// Draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void MainMenu::Update(float deltaTime, SDL_Event e)
{
}

bool MainMenu::SetupLevel()
{
	// load texture 
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/MainMenu.jpg"))
	{
		std::cout << "Failed to load the background texture!" << std::endl;
		return false;
	}
	return true;
}
