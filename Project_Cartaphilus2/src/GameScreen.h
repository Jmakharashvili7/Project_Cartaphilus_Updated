#pragma once
#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>
#include <vector>

#include "Commons.h"

class GameScreen
{
protected:
	SDL_Renderer* m_renderer;
	static int m_score;
	static std::vector<int> m_highscores;
public:
	GameScreen(SDL_Renderer* renderer);
	virtual ~GameScreen();
	
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void DetectButtonClick(SDL_Event e);
protected:
	bool LoadHighscoreTable();
	bool UpdateHighscore(int score);
};
#endif //_GAMESCREEN_H