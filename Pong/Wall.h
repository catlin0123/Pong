#pragma once
#include "DrawableObject.h"

class Wall :
	public DrawableObject
{
public:
	OrientationEnum Orientation;
	float Length;

	Wall();
	Wall(Point center, OrientationEnum orientation, const float color[], float length);
	~Wall();

	virtual void Draw();

	virtual float X_Min();
	virtual float Y_Min();
	virtual float X_Max();
	virtual float Y_Max();
};

