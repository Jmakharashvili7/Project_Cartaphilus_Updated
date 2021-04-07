#pragma once
#ifndef POW_BLOCK_H
#define POW_BLOCK_H

#include <iostream>
#include "SDL.h"
#include "Commons.h"
#include "Texture2D.h"

class LevelMap;

class PowBlock
{
public:
	bool hit = false;
private:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	LevelMap* m_level_map;
	Rect2D* m_collision_rect;

	float m_single_spire_w;
	float m_single_sprite_h;
	int m_num_hits_left;
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();
	void Render();
	inline Rect2D* GetCollisionRect() { return m_collision_rect; }
	void TakeHit();
	inline bool IsAvailable() { return m_num_hits_left > 0; }
};
#endif // POW_BLOCK_H
