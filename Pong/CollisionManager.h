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
	map<pair<DrawableObject*, DrawableObject*>, void(*)(CollisionTypeEnum)> _collisions;
};

