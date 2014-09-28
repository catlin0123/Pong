#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
	_collisions.clear();
}

void CollisionManager::RegisterCollision(DrawableObject *collider, DrawableObject *collidee, void(*collide)(CollisionTypeEnum))
{
	_collisions[make_pair(collider, collidee)] = collide;
}

void CollisionManager::ClearCollisions()
{
	_collisions.clear();
}

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
