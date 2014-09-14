#pragma once
#include "DrawableObject.h"

class Wall :
	public DrawableObject
{
public:
	OrientationEnum Orientation;
	float Length;

	Wall();
	Wall(Point center, OrientationEnum orientation, float color[], float length);
	~Wall();

	virtual void Draw();

	virtual float X_Min();
	virtual float Y_Min();
	virtual float X_Max();
	virtual float Y_Max();

	virtual void CollideLeft();
	virtual void CollideRight();
	virtual void CollideTop();
	virtual void CollideBottom();

	void Collide(DrawableObject &obj);
	CollisionTypeEnum didCollide(DrawableObject &obj);
};

