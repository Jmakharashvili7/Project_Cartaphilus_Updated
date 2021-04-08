#pragma once
#ifndef _FIRSTLEVEL_H
#define _FIRSTLEVEL_H

#include <vector>
#include "GameScreen.h"
#include "Commons.h"
#include "PlayerCharacter.h"
#include "CharacterKoopa.h"

class Texture2D;	
class PlayerCharacter;
class PhysicsManager;
class LevelMap;
class PowBlock;

class FirstLevel : GameScreen
{
private:
	Texture2D* m_background_texture;
	PlayerCharacter* player_character;
	PhysicsManager* physicsManager;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	std::vector<CharacterKoopa*> m_koopas; 
	float m_background_yPos;
public:
	FirstLevel(SDL_Renderer* renderer);
	~FirstLevel();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock(SDL_Event e);
private:
	void SetLevelMap();
	bool SetupLevel();	
	void DoScreenshake();
	void UpdateKoopas(float deltaTime);
	void CreateKoopa(Vector2D* position, Direction direction, float speed);
};
#endif //_FIRSTLEVEL_H

