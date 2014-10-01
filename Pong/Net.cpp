/*************************************************************************//**
* @file
*
* @brief Contains the implemenations of the Net Class.
****************************************************************************/
#include "Net.h"
#include <GL/freeglut.h>

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* An empty contructor for the Net class.
*
* @returns an empty Net object
*
*****************************************************************************/
Net::Net() :
	Wall()
{

}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* A constructor that defines the center, orientation, color and length of a
* Net.
*
* @param[in] center - defines the center point of the net
* @param[in] orientation - defines whether the wall is vertical or horizontal
* @param[in] color - defines the color of the drawn wall
* @param[in] length - the length of the created wall
*
* @returns an initialized Net
*
*****************************************************************************/
Net::Net(Point center, OrientationEnum orientation, const float color[], float length) :
    Wall(center, orientation, color, length)
{

}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* An empty deconstructor for the Net class.
*
* @returns an empty drawable object
*
*****************************************************************************/
Net::~Net()
{

}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Overrides the Draw function of the Wall object to add stippling to the net
*
*****************************************************************************/
void Net::Draw()
{
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xff00);

    Wall::Draw();

    glDisable(GL_LINE_STIPPLE);
}
