/*************************************************************************//**
* @file
*
* @brief The header file for the Wall
****************************************************************************/
#pragma once
#include "DrawableObject.h"

class Wall :
	public DrawableObject
{
public:
	/*!
	* @brief The orientation of the wall (HORIZONTAL/VERTICAL)
	*/
	OrientationEnum Orientation;

	/*!
	* @brief Length of the wall
	*/
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

