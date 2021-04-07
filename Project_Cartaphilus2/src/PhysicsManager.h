#pragma once
#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <iostream>
#include "SDL.h"
#include "commons.h"
#include "Constants.h"
#include "PlayerCharacter.h"

class PhysicsManager
{
public:
	~PhysicsManager();

	static PhysicsManager* Instance();

	bool CircleCollision(Circle2D* char1, Circle2D* char2);
	bool POWMarioCollision(PlayerCharacter* player, Rect2D* pow);
	bool BoxCircleCollision(Circle2D* circle, Rect2D* rect);
	CollisionType BoxCollision(Rect2D* rect1, Rect2D* rect2);
private:
	PhysicsManager();

	static PhysicsManager* m_instance;
};
#endif // PHYSICSMANAGER_H
