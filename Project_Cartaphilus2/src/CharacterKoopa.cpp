#include "CharacterKoopa.h"
#include "Texture2D.h"
#include "PhysicsManager.h"
#include "Text.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D* start_position, Direction start_facing, float movement_speed, PhysicsManager* physics_manager) : CharTemplate(renderer, imagePath, start_position, map, start_facing, physics_manager)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_injured = false;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();

	m_collisionCirlce = new Circle2D(15.0f, m_position);
	m_collision_rect = new Rect2D(m_position, m_single_sprite_w, m_single_sprite_h);

	LOG("new koopa");
}

CharacterKoopa::~CharacterKoopa()
{
}

void CharacterKoopa::TakeDamage(float deltaTime)
{
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Render()
{
	// variable to hold the left position of the sprite we want to draw
	int left = 0.0f;

	// if injured make the left position to be the left position of the second image of the sprite sheet
	if (m_injured)
		left = m_single_sprite_w;

	// get the portion of the sprite sheet you want to draw

	SDL_Rect portion_of_the_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h };

	// determine where you want to draw it
	SDL_Rect destRect = { (int)(m_position->x), (int)(m_position->y), m_single_sprite_w, m_single_sprite_h };

	// then draw it facing the correct direction
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(&portion_of_the_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(&portion_of_the_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterKoopa::Update(float deltaTime)
{
	// call update funtion of base class
	CharTemplate::Update(deltaTime);

	if (!m_injured)
	{
		// enemy is not injured so move
		if (m_facing_direction == FACING_LEFT)
		{
			m_moving_left = true;
			m_moving_right = false;
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_right = true;
			m_moving_left = false;
		}
	}
	else
	{
		// we should not be moving when injured
		m_moving_left = false;
		m_moving_right = false;	

		// count down injured time
		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0)
			FlipRightWayUp();
	}
}

void CharacterKoopa::FlipRightWayUp()
{
	if (m_facing_direction == FACING_LEFT)
	{
		m_facing_direction = FACING_RIGHT;
	}
	else if (m_facing_direction == FACING_RIGHT)
	{
		m_facing_direction = FACING_LEFT;
	}
	m_injured = false;
	Jump();
}
