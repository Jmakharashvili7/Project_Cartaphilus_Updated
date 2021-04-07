#pragma once
#ifndef COMMONS_H
#define COMMONS_H

#include <string>
#include <iostream>
#include "Constants.h"

#ifdef PR_DEBUG
#define LOG(x) std::cout << x << std::endl
#else 
#define LOG(x) 
#endif

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vector2D(float initial_x, float initial_y)
	{
		x = initial_x;
		y = initial_y;
	}
};

struct Rect2D
{
	Vector2D* position;
	float height, width;

	Rect2D(Vector2D* position, float width, float height)
	{
		this->position = position;
		this->width = width;
		this->height = height;
	}
	Rect2D(float x, float y, float width, float height)
	{
		this->position = new Vector2D(x, y);
		this->width = width;
		this->height = height;
	}
	~Rect2D()
	{
		delete position;
	}
};

struct Circle2D
{
	float radius;
	Vector2D* center;

	Circle2D(float r, Vector2D* center)
	{
		radius = r;
		this->center = center;
	}
	~Circle2D()
	{
		delete center;
	}
};

enum class CollisionType 
{
	RIGHT,
	LEFT,
	TOP,
	BOTTOM,
	NONE
};

enum SCREENS
{
	SCREEN_INTRO,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum Direction
{
	FACING_LEFT,
	FACING_RIGHT,
	FACING_UP,
	FACING_DOWN
};

enum TILETYPE
{
	EMPTY,
	FLOOR,
	POWERUP
};

struct Tile
{
	Vector2D* m_array_pos;
	TILETYPE m_tileType;
	Rect2D* m_collision_rect;

	Tile() { }

	Tile(TILETYPE tileType, int x, int y) 
	{ 
		m_tileType = tileType; 
		m_array_pos = new Vector2D(x, y);
		m_collision_rect = new Rect2D(m_array_pos->x * TILE_WIDTH, m_array_pos->y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
	}
};
#endif // COMMONS_H
