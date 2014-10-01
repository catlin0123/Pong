/*************************************************************************//**
* @file
*
* @brief Contains the implemenations of the Wall Class.
****************************************************************************/
#include "Wall.h"
#include <GL/freeglut.h>

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* An empty contructor for the Wall class.
*
* @returns an initialized Wall
*
*****************************************************************************/
Wall::Wall() :
	DrawableObject()
{

}
/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* An constructor that defines the center, orientation, color, and length of a
* Wall.
*
* @returns an initialized Wall
*
*****************************************************************************/
Wall::Wall(Point center, OrientationEnum orientation, const float color[], float length) :
	DrawableObject(center, color)
{
	Orientation = orientation;
	Length = length;
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* An empty deconstructor for the Wall class.
*
*****************************************************************************/
Wall::~Wall()
{

}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Draws the wall as a line.
*
*****************************************************************************/
void Wall::Draw()
{
    glColor3fv(_color);

    glBegin(GL_LINES);
        glVertex2d(X_Min(), Y_Min());
        glVertex2d(X_Max(), Y_Max());
    glEnd();
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Calculates the farthest left x value of the wall
*
* @returns the farthest left x value of the wall
*
*****************************************************************************/
float Wall::X_Min()
{
	return Orientation == HORIZONTAL ? Center.X - Length / 2 : Center.X;
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Calculates the lowest y value of the wall
*
* @returns the lowest y value of the wall
*
*****************************************************************************/
float Wall::Y_Min()
{
	return Orientation == VERTICAL ? Center.Y - Length / 2 : Center.Y;
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Calculates the farthest right x value of the wall
*
* @returns the farthest right x value of the wall
*
*****************************************************************************/
float Wall::X_Max()
{
	return Orientation == HORIZONTAL ? Center.X + Length / 2 : Center.X;
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Calculates the highest y value of the wall
*
* @returns the highest y value of the wall
*
*****************************************************************************/
float Wall::Y_Max()
{
	return Orientation == VERTICAL ? Center.Y + Length / 2 : Center.Y;
}