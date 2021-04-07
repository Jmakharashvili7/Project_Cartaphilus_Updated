#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameScreen.h"
#include "Commons.h"

class Texture2D;

class MainMenu : GameScreen
{
private:
	Texture2D* m_background_texture;
public:
	MainMenu(SDL_Renderer* renderer);
	~MainMenu();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
private:
	bool SetupLevel();
};
#endif // MAINMENU_H

