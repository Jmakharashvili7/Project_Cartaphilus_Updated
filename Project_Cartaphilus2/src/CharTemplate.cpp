#include "CharTemplate.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include "PhysicsManager.h"

CharTemplate::CharTemplate(SDL_Renderer* renderer, std::string imagePath, Vector2D* start_position, LevelMap* map, Direction starting_direction, PhysicsManager* physics_manager)
{
	m_renderer = renderer;

	m_current_map = map;

	m_physics_manager = physics_manager;

	// setup texture
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cerr << "Character texture could not be loaded!" << std::endl;
	}

	// Character information
	m_position = start_position;
	m_velocity = new Vector2D(0, 0);
	m_facing_direction = starting_direction;
	m_alive = true;

	// variables for character movement
	m_jumping = false;
	m_moving_right = false;
	m_moving_left = false;
}

CharTemplate::~CharTemplate()
{
	m_renderer = nullptr;
}

void CharTemplate::HandleWallCollision()
{ 
	// set the initial index to top left of the 9 tiles we check
	int indexY = m_current_tile.m_array_pos->y - 1;
	int indexX = m_current_tile.m_array_pos->x - 1;

	// loop through the 9 tiles surrounding the character and check for collision
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// the current tile we're checking collision with
			Tile tile = m_current_map->GetTileAt(indexY + i, indexX + j);	

			// check that the tile isnt empty
			if (tile.m_tileType == FLOOR)
			{
				//if (m_physics_manager->BoxCollision(m_collision_rect, tile.m_collision_rect))
				{
					
				}
			}
		}
	}
}

void CharTemplate::Render()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(*m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(*m_position, SDL_FLIP_HORIZONTAL);
	}
}

void CharTemplate::Update(float deltaTime)
{
	// set the current tile to the center of the character
	m_current_tile = m_current_map->GetTileAt((int)(m_position->y + m_texture->GetHeight() * 0.5) / TILE_HEIGHT,
		(int)(m_position->x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH);

	// apply directional vectors to current position
	m_position->y += (m_velocity->y * deltaTime);
	m_position->x += (m_velocity->x * deltaTime);
	m_collision_rect->position = m_position;

	// Check if we're in the air or on the ground
	if (m_current_tile.m_tileType == EMPTY)
	{
		// Apply gravity
		m_velocity->y += GRAVITY * deltaTime;
		m_jumping = true;
	}
	else
	{
		// reset values
		if (m_jumping)
		{
			m_velocity->y = 0;
			m_jumping = false;
		}
	}
}

void CharTemplate::Jump()
{
	m_velocity->y -= JUMPHEIGHT;
}

void CharTemplate::SetPosition(Vector2D* new_position)
{
	m_position = new_position;
}

Vector2D* CharTemplate::GetPosition()
{
	return m_position;
}

bool CharTemplate::IsJumping()
{
	return m_jumping;
}

void CharTemplate::CancelJump()
{
	m_velocity->y = 0;
}