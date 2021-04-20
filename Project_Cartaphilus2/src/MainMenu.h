#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameScreen.h"
#include "Commons.h"

class Texture2D;
class TextManager;

class MainMenu : GameScreen
{
private:
	Texture2D* m_background_texture;
	TextManager* m_play_button;
	TextManager* m_highscore_button;
	TextManager* m_quit_button;
public:
	MainMenu(SDL_Renderer* renderer);
	~MainMenu();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
private:
	bool SetupLevel();
};
#endif // MAINMENU_H

