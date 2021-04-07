#pragma once
#ifndef CHARTEMPLATE_H
#define CHARTEMPLATE_H

#include <iostream>
#include "SDL.h"
#include "commons.h"
#include "Constants.h"

class Texture2D;
class LevelMap;
class PhysicsManager;

class CharTemplate
{
	// variables
public:
	int m_centralX_position;
	int m_foot_position;
	Tile m_current_tile;
protected:
	SDL_Renderer* m_renderer;
	Vector2D* m_position;
	Vector2D* m_velocity;
	Texture2D* m_texture;
	Circle2D* m_collisionCirlce;
	Rect2D* m_collision_rect;
	LevelMap* m_current_map;
	Direction m_facing_direction;
	PhysicsManager* m_physics_manager;
	// varibles to handle movement
	bool m_moving_right;
	bool m_moving_left;
	bool m_can_jump;
	bool m_jumping;
	bool m_alive;
public:
	// contstructor and destructor
	CharTemplate(SDL_Renderer* renderer, std::string imagePath, Vector2D* start_position, LevelMap* map, Direction starting_direction, PhysicsManager* physics_manager);
	~CharTemplate();

	// collision functions
	Circle2D* GetCollisionCircle() { return m_collisionCirlce; }
	Rect2D* GetCollisionRect() { return m_collision_rect; }
	void HandleWallCollision();

	// render and update
	virtual void Render();
	virtual void Update(float deltaTime);

	// position functions
	void SetPosition(Vector2D* new_position);
	Vector2D* GetPosition();

	// jump related functions
	void Jump();
	bool IsJumping();
	void CancelJump();

	// life related functions
	bool GetAlive() { return m_alive; }
	void SetAlive(bool isAlive) { m_alive = isAlive; }
};
#endif // CHARTEMPLATE_Hk