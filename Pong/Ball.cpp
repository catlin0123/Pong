#include "DrawableObject.h"
#include "Ball.h"
#include <math.h>
#include <GL/freeglut.h>

Ball::Ball() :
	DrawableObject()
{
    
}

Ball::Ball(Point center, int rad, const float color[]) :
    DrawableObject(center, color)
{
    _radius = rad;
    _velocity = _minVelocity = 1.0; 
    _xVel = sqrt(2.0)/2;
    _yVel = sqrt(2.0)/2; 
}

Ball::Ball(Ball &b) : 
    DrawableObject(b.Center, b._color)
{
    _radius = b._radius; 
    _velocity = b._velocity; 
    _xVel = b._xVel; 
    _yVel = b._yVel; 
}

void Ball::Draw()
{
    int num_segments = 20; 
    const double PI = 3.14159265358979323846;

    glColor3fv(_color);
    glBegin(GL_POLYGON);
        for (int i = 0; i < num_segments; i++)
        {
            glVertex2d(Center.X + _radius * cos(2 * PI * i / num_segments),
                Center.Y + _radius * sin(2 * PI * i / num_segments)); 
        }
    glEnd(); 
}

void Ball::Update()
{
    Center.X += _xVel; 
    Center.Y += _yVel; 
}

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

void Ball::BounceOffPaddle(int spin)
{
    throw ERROR_CALL_NOT_IMPLEMENTED;
}

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

void Ball::ResetBall(float x, float y)
{
    Center.X = x; 
    Center.Y = y; 
    _xVel *= -1;
}

void Ball::ScaleVelocity(float inc)
{
    float yangle = asin(_yVel / _velocity);
	float xangle = acos(_xVel / _velocity);
	_velocity += inc; 
    _yVel = _velocity * sin(yangle);
    _xVel = _velocity * cos(xangle);
}

float Ball::X_Min()
{
    return Center.X - _radius;
}

float Ball::Y_Min()
{
    return Center.Y - _radius;
}

float Ball::X_Max()
{
    return Center.X + _radius;
}

float Ball::Y_Max()
{
    return Center.Y + _radius;
}

float Ball::Velocity()
{
	return _velocity;
}