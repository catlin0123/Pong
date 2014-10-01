/*************************************************************************//**
* @file
*
* @brief The header file for the CollisionManager
****************************************************************************/
#pragma once

#include "DrawableObject.h"
#include "Enums.h"
#include <map>

using namespace std;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void RegisterCollision(DrawableObject *collider, DrawableObject *collidee, void(*collide)(CollisionTypeEnum));
	void ClearCollisions();
	void CheckAndExecuteCollisions();

private:
	/*!
	* @brief Holds the objects to be checked and the function to be called if they collide
	*/
	map<pair<DrawableObject*, DrawableObject*>, void(*)(CollisionTypeEnum)> _collisions;
};

