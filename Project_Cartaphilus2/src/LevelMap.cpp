#include "LevelMap.h"
#include <iostream>
#include <fstream>

using namespace std;

LevelMap::LevelMap(string path)
{
	ifstream inFile;
	inFile.open(path, ifstream::in);
	
	// Check if the file is good
	if (!inFile.good())
	{
		cerr << "Map couldnt be opened" << endl;
		m_map = nullptr;
	}
	else
	{
		// temp variable to hold the input from the file
		int temp;

		// allocate memory for the level map
		m_map = new Tile*[MAP_HEIGHT];
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			m_map[i] = new Tile[MAP_WIDTH];
		}

		// populate the array
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				inFile >> temp;

				m_map[i][j] = Tile((TILETYPE)temp, j, i);
			}
		}
	}
}

LevelMap::~LevelMap()
{
	// delete all elements of the array
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		delete[] m_map[i];
	}
	delete[]m_map;
}

Tile LevelMap::GetTileAt(unsigned int h, unsigned int w)
{
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return m_map[h][w];
	}
	else
	{
		std::cerr << "Incorrect height or width!" << std::endl;
	}
}