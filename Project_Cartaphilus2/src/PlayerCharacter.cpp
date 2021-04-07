#include "PlayerCharacter.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include "PhysicsManager.h"

PlayerCharacter::PlayerCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D* start_position, LevelMap* map, Direction direction, PhysicsManager* physics_manager)
{
	m_renderer = renderer;

	m_current_map = map;

	// setup texture
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cerr << "Character texture could not be loaded!" << std::endl;
	}

	// Character information
	m_position = start_position;
	m_collision_circle = new Circle2D(15.0f, m_position);
	m_collision_rect = new Rect2D(m_position, m_texture->GetWidth(), m_texture->GetHeight());
	m_velocity = new Vector2D(0, 0);

	// variables for user input
	m_jumping = false;
	m_can_jump = true;
	m_facing_direction = direction;
	m_moving_right = false;
	m_moving_left = false;
}

PlayerCharacter::~PlayerCharacter()
{
	m_renderer = nullptr;
}

void PlayerCharacter::Render()
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

void PlayerCharacter::Update(float deltaTime, SDL_Event e)
{ 
	// set the current tile to the center of the character
	m_current_tile = m_current_map->GetTileAt((int)(m_position->y + m_texture->GetHeight() * 0.5) / TILE_HEIGHT,
		(int)(m_position->x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH);

	Tile m_foot_tile = m_current_map->GetTileAt((int)(m_position->y + m_texture->GetHeight()) / TILE_HEIGHT,
		(int)(m_position->x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH);
	
	// apply directional vectors to current position
	m_position->y += (m_velocity->y * deltaTime);
	m_position->x += (m_velocity->x * deltaTime);
	m_collision_rect->position = m_position;

	if (!m_grounded)
	{
		m_velocity->y += GRAVITY * deltaTime;
	}
	else
	{
		Grounded();
	}

	if (m_velocity->x >= MOVESPEEDLIMIT)
		m_velocity->x = MOVESPEEDLIMIT;

	if (m_velocity->x <= -MOVESPEEDLIMIT)
		m_velocity->x = -MOVESPEEDLIMIT;

	HandleMovement(e, deltaTime);
	HandleJump(e);
	HandleWallCollision(e);
}

void PlayerCharacter::HandleJump(SDL_Event e)
{
	// Check if the character can jump
	if (e.key.keysym.sym == SDLK_SPACE && m_can_jump)
	{
		m_velocity->y = -JUMPHEIGHT;
		m_can_jump = false;
		m_jumping = true;
		m_grounded = false;
	}
}		

void PlayerCharacter::HandleMovement(SDL_Event e, float deltaTime)
{
	// Check input
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = true;
			break;
		case SDLK_d:
			m_moving_right = true;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = false;
			break;
		case SDLK_d:
			m_moving_right = false;
			break;
		}
		break;
	}

	// move based on input
	if (m_moving_left)
	{
		m_velocity->x -= deltaTime * MOVESPEED;
		m_facing_direction = FACING_LEFT;
	}
	else if (m_moving_right)
	{
		m_velocity->x += deltaTime * MOVESPEED;
		m_facing_direction = FACING_RIGHT;
	}
	else
	{
		m_velocity->x = 0;
	}
}

void PlayerCharacter::HandleWallCollision(SDL_Event e)
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
				switch (m_physics_manager->BoxCollision(m_collision_rect, tile.m_collision_rect))
				{
				case CollisionType::TOP:
					// move mario outside of collision
					m_position->y = tile.m_collision_rect->position->y + tile.m_collision_rect->height;
					CancelJump();
					break;
				case CollisionType::RIGHT:
					// move mario outside of collision
					m_position->x = tile.m_collision_rect->position->x - m_collision_rect->width;

					// if mario is facing the block prevent horizontal movement
					if (m_facing_direction == FACING_RIGHT)
					{
						CancelMovement();
					}
					break;
				case CollisionType::LEFT:
					// move mario outside of collision
					m_position->x = tile.m_collision_rect->position->x + tile.m_collision_rect->width;
					// if mario is facing the block prevent horizontal movement
					if (m_facing_direction == FACING_LEFT)
					{
						CancelMovement();
					}
					break;                
				case CollisionType::BOTTOM:
					// move mario outside of collision
					m_position->y = tile.m_collision_rect->position->y - m_collision_rect->height;
					m_grounded = true;
					LOG("anal beads");
					break;
				case CollisionType::NONE:
					break;
				}
			}
		}
	}
}

void PlayerCharacter::Grounded()
{
	// reset values
	if (m_jumping)
	{
		m_can_jump = true;
		m_jumping = false;
	}
	else
	{
		m_velocity->y = 0;
	}
}

// Implement air resistance and terminal velocity. try to add a slide as well. make movement feel as good as possible.