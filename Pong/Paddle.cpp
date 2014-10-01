/*************************************************************************//**
* @file
*
* @brief Contains the implemenations of the Paddle Class.
****************************************************************************/
#include "Paddle.h"
#include "DrawableObject.h"
#include <gl\freeglut.h>

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* An empty contructor for the Paddle class.
*
* @returns an empty Paddle
*
*****************************************************************************/
Paddle::Paddle() :
	DrawableObject()
{
	_xInc = 0;
	_yInc = 0;
	_widthOffset = 0;
	_heightOffset = 0;
    _originalHeight = 0; 
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* A constructor that defines the center, width, height, and color of a Paddle
*
* @returns an initialized Paddle
*
*****************************************************************************/
Paddle::Paddle(Point center, float width, float height, const float color[]) :
    DrawableObject(center, color)
{
    _xInc = 0; 
    _yInc = 0; 
    _widthOffset = width / 2; 
    _heightOffset = height / 2; 
    _originalHeight = height / 2; 
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* An copy contructor for the Paddle class.
*
* @returns an initialized Paddle
*
*****************************************************************************/
Paddle::Paddle(Paddle &p) :
    DrawableObject(p.Center, p._color)
{
    _xInc = p._xInc; 
    _yInc = p._yInc;
    _widthOffset = p._widthOffset; 
    _heightOffset = p._heightOffset; 
    _originalHeight = p._originalHeight; 
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Draws the paddle in the buffer, but does NOT flush the buffer.
*
*****************************************************************************/
void Paddle::Draw()
{
    glColor4fv(_color);
    glBegin(GL_POLYGON); 
        glVertex2f(Center.X + _widthOffset, Center.Y + _heightOffset); 
        glVertex2f(Center.X + _widthOffset, Center.Y - _heightOffset);
        glVertex2f(Center.X - _widthOffset, Center.Y - _heightOffset);
        glVertex2f(Center.X - _widthOffset, Center.Y + _heightOffset);
    glEnd();
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Updates the position of the paddle based on its current x and y increments
*
*****************************************************************************/
void Paddle::Update()
{
    Center.X += _xInc;
    Center.Y += _yInc; 
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Changes the x increment by inc, limiting it to a max (+/-) of the widthOffset
* to keep it from running through walls at high speed.
*
* @param[in] inc - the amount, positive or negative, to change the x increment
*                  by.
*
*****************************************************************************/
void Paddle::ChangeXSpeed(float inc)
{
    if (_xInc < _widthOffset - 1  && _xInc > -1 * _widthOffset + 1)
    {
        _xInc += inc;
    }
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Changes the y increment by inc, limiting it to a max (+/-) of the heightOffset
* to keep it from running through walls at high speed.
*
* @param[in] inc - the amount, positive or negative, to change the y increment
*                  by.
*
*****************************************************************************/
void Paddle::ChangeYSpeed(float inc)
{
    if (_yInc < _heightOffset - 2 && _yInc > -1 * _heightOffset + 1)
    {
        _yInc += inc;
    }
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Resets the x increment to 0.
*
*****************************************************************************/
void Paddle::ResetXSpeed()
{
    _xInc = 0; 
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Resets the y increment to 0.
*
*****************************************************************************/
void Paddle::ResetYSpeed()
{
    _yInc = 0; 
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Resets the x and y increments to 0.
*
*****************************************************************************/
void Paddle::ResetSpeed()
{
    _xInc = 0; 
    _yInc = 0; 
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Calculates the farthest left x value of a Paddle
*
* @returns the farthest left x value of the Paddle
*
*****************************************************************************/
float Paddle::X_Min()
{
    return Center.X - _widthOffset; 
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Calculates the lowest y value of a Paddle
*
* @returns the lowest y value of the Paddle
*
*****************************************************************************/
float Paddle::Y_Min()
{
    return Center.Y - _heightOffset; 
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Calculates the farthest right x value of a Paddle
*
* @returns the farthest right x value of the Paddle
*
*****************************************************************************/
float Paddle::X_Max()
{
    return Center.X + _widthOffset; 
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Calculates the highest y value of a Paddle
*
* @returns the highest y value of the Paddle
*
*****************************************************************************/
float Paddle::Y_Max()
{
    return Center.Y + _heightOffset;
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Calculates the magnitude of the paddle's velocity
*
* @returns the magnitude of the paddle's velocity
*
*****************************************************************************/
float Paddle::Velocity()
{
	return sqrtf(_xInc * _xInc + _yInc * _yInc);
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Retrieves the x increment of a Paddle
*
* @returns the x increment of the Paddle
*
*****************************************************************************/
float Paddle::X_Vel()
{
    return _xInc;
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Retrieves the y increment of a Paddle
*
* @returns the y increment of the Paddle
*
*****************************************************************************/
float Paddle::Y_Vel()
{
    return _yInc;
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Reduces the hieght of the paddle by .5 on each side (1 total), limiting to a
* minimum of the width of the paddle.
*
*****************************************************************************/
void Paddle::ReduceSize()
{
    if (_heightOffset > _widthOffset)
    {
        _heightOffset -= .5;
    }
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Resets the size of the paddle to the original size.
*
*****************************************************************************/
void Paddle::ResetSize()
{
    _heightOffset = _originalHeight; 
}
