#include "PhysicsManager.h"
#include <cmath>

PhysicsManager* PhysicsManager::m_instance = nullptr;

PhysicsManager::~PhysicsManager()
{
	m_instance = nullptr;
}

PhysicsManager* PhysicsManager::Instance()
{
	if (!m_instance)
	{
		m_instance = new PhysicsManager;
	}
	return m_instance;
}

bool PhysicsManager::CircleCollision(Circle2D* char1, Circle2D* char2)
{
	Vector2D vec = Vector2D((char1->center->x - char2->center->x),
		(char1->center->y - char2->center->y));

	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	double combined_distance = double(char1->radius + char2->radius);

	return distance < combined_distance;
}

bool PhysicsManager::POWMarioCollision(PlayerCharacter* player, Rect2D* pow)
{
	// mario variables
	int mLeft = player->GetPosition()->x;
	int mRight = player->GetPosition()->x + player->GetCollisionRect()->width;
	int mUp = player->GetPosition()->y;
	int mDown = player->GetPosition()->y + player->GetCollisionRect()->height;

	// POW block variables
	int pLeft = pow->position->x;
	int pRight = pow->position->x + pow->width;
	int pUp = pow->position->y;
	int pDown = pow->position->y + pow->height;

	// top player and bottom pow
	if (mUp == pDown && mLeft < pRight && mRight > pLeft)
	{
		return true;
	}
	return false;
}

bool PhysicsManager::BoxCircleCollision(Circle2D* c, Rect2D* r)
{
	if (c->center)
	return false;
}

CollisionType PhysicsManager::BoxCollision(Rect2D* rect1, Rect2D* rect2)
{
	// detect if there is any collision
	if (rect1->position->y < rect2->position->y + rect2->height && 
		rect1->position->y + rect1->height > rect2->position->y && 
		rect1->position->x < rect2->position->x + rect2->width &&
		rect1->position->x + rect1->width > rect2->position->x)
	{
		// rect 1 left and rect 2 right
		if (abs(rect1->position->x - (rect2->position->x + rect2->width)) < 1.0f)
		{
			return CollisionType::LEFT;
		}
		// rect 1 right and rect 2 left
		else if (abs((rect1->position->x + rect1->width) - rect2->position->x) < 1.0f)
		{
			return CollisionType::RIGHT;
		}
		// rect 1 top and rect 2 bottom 
		else if (abs(rect1->position->y - (rect2->position->y + rect2->height)) < 1.0f)
		{
			return CollisionType::TOP;
		}
		// rect 1 bot and rect 1 top
		else if (abs((rect1->position->y + rect1->height) - rect2->position->y) < 1.0f)
		{
			return CollisionType::BOTTOM;
		}
	}
	else
	{
		return CollisionType::NONE;
	}
}

PhysicsManager::PhysicsManager() {}
