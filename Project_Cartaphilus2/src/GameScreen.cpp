#include "GameScreen.h"

#include <fstream>
#include <iostream>


#include "text.h"
#include "Commons.h"

int GameScreen::m_score;
std::vector<int> GameScreen::m_highscores;

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

GameScreen::~GameScreen()
{
	m_renderer = nullptr;
	LOG("test");
}

void GameScreen::Render() {}

void GameScreen::Update(float deltaTime, SDL_Event e) {}

bool GameScreen::LoadHighscoreTable()
{
	std::ifstream inFile;

	// open the file and check for error flags
	inFile.open("SavedInfo/highscores.txt");
	if (!inFile.good())
	{
		LOG("Failed to open highscore file! for load");
		return false;
	}

	for (unsigned int i = 0; i < HIGHSCORE_COUNT; i++)
	{
		int temp; // to hold the input from file
		inFile >> temp;
		m_highscores.push_back(temp);
	}

	// close the file and exit
	inFile.close();
	return true;
}

bool GameScreen::UpdateHighscore(int score)
{
	// insert the new score and remove the 11th member of the array
	m_highscores.insert(m_highscores.begin(), score);
	m_highscores.erase(m_highscores.end() - 1);

	std::ofstream outFile;

	// open the file, then clear the file, and check for error flags
	outFile.open("SavedInfo/highscores.txt", std::ios::trunc);
	if (!outFile.good())
	{
		LOG("Failed to open highscore file for update!");
		return false;
	}

	// write the new highscore table to the file
	for (unsigned int i = 0; i < HIGHSCORE_COUNT; i++)
	{
		outFile << m_highscores[i] << std::endl;
	}

	// close the file and exit 
	outFile.close();
	return true;
}


