#include <iostream>
#include "POW_Block.h"
#include "LevelMap.h"

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map)
{
	std::string imagePath = "Images/PowBlock.png";
	m_texture = new Texture2D(renderer);
	if (!m_texture->LoadFromFile(imagePath.c_str()))
	{
		std::cerr << "Failed to load texture." << std::endl;
		return;
	}

	m_level_map = map;
	m_single_spire_w = m_texture->GetWidth() / 3; // There are three images in the sprite sheet
	m_single_sprite_h = m_texture->GetHeight();
	m_num_hits_left = 3;
	m_position = Vector2D((SCREEN_WIDTH * 0.5f) - m_single_spire_w * 0.5f, 290);
	m_collision_rect = new Rect2D(&m_position, m_texture->GetWidth() / 3, m_texture->GetHeight());
}

PowBlock::~PowBlock()
{
	m_level_map = nullptr;
	m_renderer = nullptr;

	delete m_texture;
	m_texture = nullptr;
	delete m_collision_rect;
	m_collision_rect = nullptr;
}

void PowBlock::Render()
{
	if (m_num_hits_left > 0)
	{
		// Determine which sprite to draw
		int left = m_single_spire_w * (m_num_hits_left - 1);

		SDL_Rect potion_of_sprite = { left, 0, m_single_spire_w, m_single_sprite_h };

		// Determine where to draw it
		SDL_Rect dest_rect = { static_cast<int>(m_position.x), static_cast<int>(m_position.y),
									m_single_spire_w, m_single_sprite_h };

		// Draw the sprite
		m_texture->Render(&potion_of_sprite, dest_rect, SDL_FLIP_NONE);
	}
}

void PowBlock::TakeHit()
{
	hit = true;
	
	// Reduce the hitbox height
	m_collision_rect->height = m_collision_rect->height - m_collision_rect->height / 3;

	m_num_hits_left--;
}
