/*************************************************************************//**
* @file
*
* @brief Contains the implemenations of the Ball Class.
****************************************************************************/
#include "CollisionManager.h"

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* An empty constructor for the CollisionManager class.
*
* @returns an empty CollisionManager
*
*****************************************************************************/
CollisionManager::CollisionManager()
{

}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* An empty deconstructor for the CollisionManager class.
*
*****************************************************************************/
CollisionManager::~CollisionManager()
{
	_collisions.clear();
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Registers a function to be called when collider collides with collidee
*
* @param[in] collider - the object that didCollide is called on
* @param[in] collidee - the object passed into didCollide
* @param[in] collide - the function that is called when
*                      (collider).didCollide((collidee)) returns a collision
*
*****************************************************************************/
void CollisionManager::RegisterCollision(DrawableObject *collider, DrawableObject *collidee, void(*collide)(CollisionTypeEnum))
{
	_collisions[make_pair(collider, collidee)] = collide;
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Clears all collisions from the CollisionManager
*
*****************************************************************************/
void CollisionManager::ClearCollisions()
{
	_collisions.clear();
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Checks each registered pair of DrawableObjects for a collision, and if it
* finds one, calls the collide function.
*
*****************************************************************************/
void CollisionManager::CheckAndExecuteCollisions()
{
	for (pair<pair<DrawableObject*, DrawableObject*>, void(*)(CollisionTypeEnum)> objs : _collisions)
	{
		CollisionTypeEnum temp = objs.first.first->didCollide(*(objs.first.second));
		if (temp != NO_COLLISION)
		{
			objs.second(temp);
		}
	}
}
