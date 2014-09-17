#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
	Collisions.clear();
}

void CollisionManager::RegisterCollision(DrawableObject *collider, DrawableObject *collidee, void(*collide)(CollisionTypeEnum))
{
	Collisions[make_pair(collider, collidee)] = collide;
}

void CollisionManager::ClearCollisions()
{
	Collisions.clear();
}

void CollisionManager::CheckAndExecuteCollisions()
{
	for (pair<pair<DrawableObject*, DrawableObject*>, void(*)(CollisionTypeEnum)> objs : Collisions)
	{
		CollisionTypeEnum temp = objs.first.first->didCollide(*(objs.first.second));
		if (temp != NO_COLLISION)
		{
			objs.second(temp);
		}
	}
}
