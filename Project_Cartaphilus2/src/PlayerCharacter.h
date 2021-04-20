#pragma once
#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H

#include <iostream>
#include <SDL_mixer.h>
#include "SDL.h"
#include "commons.h"
#include "Constants.h"

class PhysicsManager;
class Texture2D;
class LevelMap;
class Audio;

class PlayerCharacter
{
	// variables
public:
	int centralX_position;
	int foot_position;
protected:
	SDL_Renderer* m_renderer;
	Vector2D* m_position;
	Vector2D* m_velocity;
	Texture2D* m_texture;
	Circle2D* m_collision_circle;
	Rect2D* m_collision_rect;
	LevelMap* m_current_map;
	PhysicsManager* m_physics_manager;
	Tile m_current_tile;
	// varibles to handle input
	bool m_moving_right;
	bool m_moving_left;
	bool m_can_jump;
	bool m_jumping;
	bool m_grounded;
private:
	Direction m_facing_direction;
	Audio* m_jump_SFX;
public:
	PlayerCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D* start_position, LevelMap* map, Direction direction, 
		PhysicsManager* physics_manager);
	~PlayerCharacter();

	// inline functions
	inline Circle2D* GetCollisionCircle() { return m_collision_circle; }
	inline Rect2D* GetCollisionRect() { return m_collision_rect; }
	inline Direction GetDirection() { return m_facing_direction; }
	inline void SetPosition(Vector2D* new_position) { m_position = new_position; }
	inline Vector2D* GetPosition() { return m_position; }
	inline bool IsJumping() { return m_jumping; }
	inline void CancelJump() { m_velocity->y = 0; }
	inline void CancelMovement() { m_velocity->x = 0.0f; }
	inline void SetGrounded(bool result) { m_grounded = result; }

	// normal functions
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void Grounded();
	virtual void HandleJump(SDL_Event e);
	virtual void HandleMovement(SDL_Event e, float deltaTime);
	virtual void HandleWallCollision();
};
#endif // MAINCHARACTER_H

