#include "MainMenu.h"

#include <iostream>

#include "Texture2D.h"
#include "Text.h"

MainMenu::MainMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetupLevel();
	m_renderer = renderer;

	// setup the menu buttons
	m_play_button = new TextManager(m_renderer, "fonts/OpenSans-Bold.ttf", 25, "Play", { 255, 255, 255, 255 });
	m_highscore_button = new TextManager(m_renderer, "fonts/OpenSans-Bold.ttf", 25, "Highscore Table", { 255, 255, 255, 255 });
	m_quit_button = new TextManager(m_renderer, "fonts/OpenSans-Bold.ttf", 25, "Quit", { 255, 255, 255, 255 });
}

MainMenu::~MainMenu()
{
	delete m_background_texture;
	m_background_texture = nullptr;

	delete m_play_button;
	m_play_button = nullptr;

	delete m_highscore_button;
	m_highscore_button = nullptr;

	delete m_quit_button;
	m_quit_button = nullptr;
}

void MainMenu::Render()
{
	// Draw the background
	m_background_texture->RenderV2(Vector2D(), SDL_FLIP_NONE);
	m_play_button->RenderText(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2);
	m_highscore_button->RenderText(SCREEN_WIDTH/2 - 90, SCREEN_HEIGHT/2 + 40);
	m_quit_button->RenderText(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2 + 80);
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
		LOG("Failed to load the background texture!");
		return false;
	}


	return true;
}
