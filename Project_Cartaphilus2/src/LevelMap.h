#pragma once
#ifndef LEVELMAP_H
#define LEVELMAP_H

#include <iostream>
#include "Constants.h"
#include "Commons.h"

class LevelMap
{
public:
	LevelMap(std::string path);
	~LevelMap();

	Tile GetTileAt(unsigned int h, unsigned int w);
private:
	Tile** m_map;
};

#endif // LEVELMAP_H 
