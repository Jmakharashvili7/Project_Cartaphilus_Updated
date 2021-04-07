#pragma once
#ifndef CHARACTERKOOPA_H
#define CHARACTERKOOPA_H

#include "CharTemplate.h"

class PhysicsManager;

class CharacterKoopa : public CharTemplate
{
private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_movement_speed;
	bool m_injured;
	bool m_injured_time;
public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D* start_position, 
		Direction start_facing, float movement_speed, PhysicsManager* physics_manager);
	~CharacterKoopa();
	void TakeDamage(float deltaTime);
	void Render() override;
	void Update(float deltaTime) override;
	bool GetInjured() { return m_injured; }
private:
	void FlipRightWayUp();
};

#endif // CHARACTERKOOPA_H

