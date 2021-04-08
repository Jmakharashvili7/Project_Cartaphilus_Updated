#include <iostream>
#include <fstream>
#include "FirstLevel.h"
#include "Texture2D.h"
#include "PhysicsManager.h"
#include "LevelMap.h"
#include "POW_Block.h"

using namespace std;

FirstLevel::FirstLevel(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetLevelMap();
	SetupLevel();
	m_renderer = renderer;
	physicsManager = PhysicsManager::Instance();
}

FirstLevel::~FirstLevel()
{
	// clean up background texture
	delete m_background_texture;
	m_background_texture = nullptr;

	// clean up the character
	delete player_character;
	player_character = nullptr;

	// clean up block
	delete m_pow_block;
	m_pow_block = nullptr;

	// clean up koopas
	m_koopas.clear();
}

void FirstLevel::Render()
{
	// Draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	// render character
	player_character->Render();

	// render POW block
	m_pow_block->Render();

	for (int i = 0; i < m_koopas.size(); i++)
	{
		m_koopas[i]->Render();
	}
}

void FirstLevel::Update(float deltaTime, SDL_Event e)
{
	// Update character
	player_character->Update(deltaTime, e);

	if (m_pow_block->IsAvailable())
		UpdatePOWBlock(e);

	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		// end shake after duration
		if (m_shake_time <= 0)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;	
		}
	}

	UpdateKoopas(deltaTime);

	/*
	switch (physicsManager->BoxCollision(player_character->GetCollisionRect(), m_koopas[0]->GetCollisionRect()))
	{
	case CollisionType::TOP:
		player_character->CancelJump();
		std::cout << "sex" << std::endl;
		break;
	case CollisionType::BOTTOM:
		std::cout << "sex" << std::endl;
		break;
	case CollisionType::RIGHT:
		break;
	case CollisionType::LEFT:
		break;
	}
	*/
}

void FirstLevel::UpdatePOWBlock(SDL_Event e)
{
	switch (physicsManager->BoxCollision(player_character->GetCollisionRect(), m_pow_block->GetCollisionRect()))
	{
	case CollisionType::TOP:
		if (m_pow_block->hit == false && player_character->IsJumping())
		{
			DoScreenshake();
			player_character->CancelJump();
			m_pow_block->TakeHit();
		}
		break;
	case CollisionType::BOTTOM:
		if (m_pow_block->hit == false && player_character->IsJumping())
		{
			player_character->CancelJump();
		}
		break;
	case CollisionType::RIGHT:
		if (m_pow_block->hit == false && player_character->IsJumping())
		{
			if (player_character->GetDirection() == FACING_RIGHT)
			{
				player_character->CancelMovement();
			}
		}
		break;
	case CollisionType::LEFT:
		if (m_pow_block->hit == false && player_character->IsJumping())
		{
			if (player_character->GetDirection() == FACING_LEFT)
			{
				player_character->CancelMovement();
			}
		}
		break;
	case CollisionType::NONE:
		m_pow_block->hit = false;
		break;
	}
}

void FirstLevel::SetLevelMap()
{
	// Clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}
	m_level_map = new LevelMap("maps/level1.txt");

	m_pow_block = new PowBlock(m_renderer, m_level_map);
	
	// add new koopa
	m_koopas.push_back(new CharacterKoopa(m_renderer, "Images/Koopa.png", m_level_map, new Vector2D(90, 200), FACING_RIGHT, 50.0f, physicsManager));
}

bool FirstLevel::SetupLevel()
{
	player_character = new PlayerCharacter(m_renderer, "Images/Mario.png", new Vector2D(64, 342), m_level_map, FACING_RIGHT, physicsManager);

	// load texture 
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		cout << "Failed to load the background texture!" << endl;
		return false;
	}
	return true;

	m_screenshake = false;
	m_background_yPos = 0.0f;
}

void FirstLevel::DoScreenshake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
}

void FirstLevel::UpdateKoopas(float deltaTime)
{
	if (!m_koopas.empty())
	{
		int enemyIndexToDelete = -1;
		for (int i = 0; i < m_koopas.size(); i++)
		{
			m_koopas[i]->Update(deltaTime);

			// check to see if the player collides with player
			if ((m_koopas[i]->GetPosition()->y > 300.0f || m_koopas[i]->GetPosition()->y <= 64.0f) &&
				(m_koopas[i]->GetPosition()->x < 64.0f || m_koopas[i]->GetPosition()->x > SCREEN_WIDTH - 96.0f))
			{
				// ignore collision if behind pipe
			}
			else
			{
				if (physicsManager->CircleCollision(m_koopas[i]->GetCollisionCircle(), player_character->GetCollisionCircle()))
				{
					if (m_koopas[i]->GetInjured())
					{
						//m_koopas[i]->SetAlive(false);
					}
					else
					{
						m_koopas[i]->TakeDamage(deltaTime);
					}
				}
			}

			// if the enemy is no longer alive then schedule it for deletion
			if (!m_koopas[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		// remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_koopas.erase(m_koopas.begin() + enemyIndexToDelete);
		}
	}
}

void FirstLevel::CreateKoopa(Vector2D* position, Direction direction, float speed)
{

}
