/*************************************************************************//**
* @file
*
* @brief Contains the implemenations of the Ball Class. 
****************************************************************************/
#include "DrawableObject.h"
#include "Ball.h"
#include <math.h>
#include <GL/freeglut.h>

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* An empty contructor for the ball class. 
*
* @returns an empty ball
*
*****************************************************************************/
Ball::Ball() :
	DrawableObject()
{
    
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* A contructor for the ball class. Initializes the center, radius, and velocity
* of the ball.
*
* @param[in] center - the center x and y coordinate of the ball
* @param[in] rad - the radius of the ball
* @param[in] color - the color of the ball specified in rgba
* 
* @ returns a ball
*
*****************************************************************************/
Ball::Ball(Point center, int rad, const float color[]) :
    DrawableObject(center, color)
{
    _radius = rad;
    _velocity = _minVelocity = 1.0; 
    _xVel = sqrt(2.0)/2;
    _yVel = sqrt(2.0)/2; 
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* A copy contructor for the ball class.
*
* @param[in] b - the ball to copy. 
*
*****************************************************************************/
Ball::Ball(Ball &b) : 
    DrawableObject(b.Center, b._color)
{
    _radius = b._radius; 
    _velocity = b._velocity; 
    _xVel = b._xVel; 
    _yVel = b._yVel; 
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* The function to draw the ball using OpenGL functions. It does so by drawing 
* a multisided polygon. 
*
*****************************************************************************/
void Ball::Draw()
{
    int num_segments = 20; 
    const double PI = 3.14159265358979323846;

    glColor3fv(_color);
    glBegin(GL_POLYGON);
        for (int i = 0; i < num_segments; i++)
        {
            //draw a new line segment on the circle
            glVertex2d(Center.X + _radius * cos(2 * PI * i / num_segments),
                Center.Y + _radius * sin(2 * PI * i / num_segments)); 
        }
    glEnd(); 
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* This moves the center of the ball so when it is redrawn it will be in a new
* location. It does this by updating moving by the x and y velocity. 
*
*****************************************************************************/
void Ball::Update()
{
    Center.X += _xVel; 
    Center.Y += _yVel; 
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Increases the minimum velocity so that the ball will go faster in general. 
* Limits the maximum speed to half the radius of the ball. 
*
*****************************************************************************/
void Ball::IncreaseMinVelocity()
{
	if (_minVelocity + 0.5 < _radius / 2)
	{
		_minVelocity += 0.5;
	}
	else
	{
		_minVelocity = _radius / 2;
	}
	IncreaseSpeed();
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Decreases the minimum velocity of the ball so that the ball will slow down.
* Limits the minumum speed to 1. 
*
*****************************************************************************/
void Ball::DecreaseMinVelocity()
{
	if (_minVelocity - 0.5 > 1)
	{
		_minVelocity -= 0.5;
	}
	else
	{
		_minVelocity = 1;
	}
	DecreaseSpeed();
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Increases the speed of the ball as long as it is not over the maximum speed 
* of the ball. 
*
*****************************************************************************/
void Ball::IncreaseSpeed(float value)
{
	if (value > 0)
	{
		if (_velocity + value < _radius / 2)
		{
			ScaleVelocity(value);
		}
		else if (_velocity < _radius / 2)
		{
			ScaleVelocity((_radius / 2) - _velocity);
		}
	}
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Decreases the speed of the ball as long as it is not under the minimum speed
* of the ball.
*
*****************************************************************************/
void Ball::DecreaseSpeed(float value)
{
	if (value > 0)
	{
		if (_velocity - value > _minVelocity)
		{
			ScaleVelocity(-1 * value);
		}
		else if (_velocity > _minVelocity)
		{
			ScaleVelocity(-1 * _velocity - _minVelocity);
		}
	}
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Takes a type of collision (left, right, top, or bottom) and changes the balls
* direction bases upon which side of the ball it hit. 
*
* @param[in] col - on what side of the ball the item collided with. 
*
*****************************************************************************/
void Ball::BounceOffPaddle(CollisionTypeEnum col)
{
    if ((col & LEFT_COLLISION) == LEFT_COLLISION)
    {
        if (_xVel < 0)
        {
            _xVel *= -1;
        }
    }
    if ((col & RIGHT_COLLISION) == RIGHT_COLLISION)
    {
        if (_xVel > 0)
        {
            _xVel *= -1;
        }
    }
    if ((col & TOP_COLLISION) == TOP_COLLISION)
    {
        if (_yVel > 0)
        {
            _yVel *= -1;
        }
    }
    if ((col & BOTTOM_COLLISION) == BOTTOM_COLLISION)
    {
        if (_yVel < 0)
        {
            _yVel *= -1;
        }
    }
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Changes the direction of the ball from 0 to 45 degrees based upon the ratio 
* (a number from 0 to 1) on how far it is from the center of the object to the
* length of the object. 
*
* @param[in] ratio - a number from 0 to 1 to scale the change in the ball
*
*****************************************************************************/
void Ball::BounceOffPaddle(float ratio)
{
    if (ratio < 0)
    {
        ratio *= -1; 
    }
    const double PI = 3.14159265358979323846;
    bool x_is_neg = _xVel < 0;
    bool y_is_neg = _yVel < 0; 
    float radians = ratio *  PI / 4; 
    _xVel = _velocity * cos(radians); 
    _yVel = _velocity * sin(radians);
    if ((x_is_neg && _xVel > 0) || (!x_is_neg && _xVel < 0))
    {
        _xVel *= -1; 
    }
    if ((y_is_neg && _yVel > 0) || (!y_is_neg && _yVel < 0))
    {
        _yVel *= -1;
    }
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Decides what happens to the ball when it hits a wall based on the collision 
* type. 
*
* @param[in] col - the type of collision that occured with the wall.
*
*****************************************************************************/
void Ball::BounceOffWall(CollisionTypeEnum col)
{
    if ((col & LEFT_COLLISION) == LEFT_COLLISION)
    {
        if (_xVel < 0)
        {
            _xVel *= -1;
        }
    }
    if ((col & RIGHT_COLLISION) == RIGHT_COLLISION)
    {
        if (_xVel > 0)
        {
            _xVel *= -1;
        }
    }
    if ((col & TOP_COLLISION) == TOP_COLLISION)
    {
        if (_yVel > 0)
        {
            _yVel *= -1; 
        }
    }
    if ((col & BOTTOM_COLLISION) == BOTTOM_COLLISION)
    {
        if (_yVel < 0)
        {
            _yVel *= -1; 
        }
    }
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Resets the placement of the ball, and changes the direction the ball was going. 
*
* @param[in] x - the x position to move the ball to.
* @param[in] y - the y position to move the ball to. 
*
*****************************************************************************/
void Ball::ResetBall(float x, float y)
{
    Center.X = x; 
    Center.Y = y; 
    _xVel *= -1;
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Scales the velocity while keeping the x and y direction the same. Should be 
* used every time the velocity is changed. 
*
* @param[in] inc - the amount to change the overall velocity by. 
*
*****************************************************************************/
void Ball::ScaleVelocity(float inc)
{
    float yangle = asin(_yVel / _velocity);
	float xangle = acos(_xVel / _velocity);
	_velocity += inc; 
    _yVel = _velocity * sin(yangle);
    _xVel = _velocity * cos(xangle);
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Gives the minimum x position of the ball
*
* @returns the minimum x position of the ball
*
*****************************************************************************/
float Ball::X_Min()
{
    return Center.X - _radius;
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Gives the minimum y position of the ball
*
* @returns the minimum y position of the ball
*
*****************************************************************************/
float Ball::Y_Min()
{
    return Center.Y - _radius;
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Gives the maximum x position of the ball
*
* @returns the maximum x position of the ball
*
*****************************************************************************/
float Ball::X_Max()
{
    return Center.X + _radius;
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Gives the maximum y position of the ball
*
* @returns the maximum y position of the ball
*
*****************************************************************************/
float Ball::Y_Max()
{
    return Center.Y + _radius;
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Gives the current velocity of the ball. 
*
* @returns the velocity of the ball
*
*****************************************************************************/
float Ball::Velocity()
{
	return _velocity;
}