#include "Paddle.h"
#include "DrawableObject.h"
#include <gl\freeglut.h>

Paddle::Paddle() :
	DrawableObject()
{
	_xInc = 0;
	_yInc = 0;
	_widthOffset = 0;
	_heightOffset = 0;
    _originalHeight = 0; 
}

Paddle::Paddle(Point center, float width, float height, const float color[]) :
    DrawableObject(center, color)
{
    _xInc = 0; 
    _yInc = 0; 
    _widthOffset = width / 2; 
    _heightOffset = height / 2; 
    _originalHeight = height / 2; 
}

Paddle::Paddle(Paddle &p) :
    DrawableObject(p.Center, p._color)
{
    _xInc = p._xInc; 
    _yInc = p._yInc;
    _widthOffset = p._widthOffset; 
    _heightOffset = p._heightOffset; 
    _originalHeight = p._originalHeight; 
}

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
void Paddle::Update()
{
    Center.X += _xInc;
    Center.Y += _yInc; 
}
void Paddle::ChangeXSpeed(float inc)
{
    if (_xInc < _widthOffset - 1  && _xInc > -1 * _widthOffset + 1)
    {
        _xInc += inc;
    }
    /*if (_xInc > -1 && _xInc < 1)
    {
        ResetXSpeed();
    }*/
}
void Paddle::ChangeYSpeed(float inc)
{
    if (_yInc < _heightOffset - 2 && _yInc > -1 * _heightOffset + 1)
    {
        _yInc += inc;
    }
    /*if (_yInc > -1 && _yInc < 1)
    {
        ResetYSpeed(); 
    }*/
}
void Paddle::ResetXSpeed()
{
    _xInc = 0; 
}
void Paddle::ResetYSpeed()
{
    _yInc = 0; 
}

void Paddle::ResetSpeed()
{
    _xInc = 0; 
    _yInc = 0; 
}

float Paddle::X_Min()
{
    return Center.X - _widthOffset; 
}
float Paddle::Y_Min()
{
    return Center.Y - _heightOffset; 
}
float Paddle::X_Max()
{
    return Center.X + _widthOffset; 
}
float Paddle::Y_Max()
{
    return Center.Y + _heightOffset;
}

float Paddle::Velocity()
{
	return sqrtf(_xInc * _xInc + _yInc * _yInc);
}

float Paddle::X_Vel()
{
    return _xInc;
}

float Paddle::Y_Vel()
{
    return _yInc;
}

void Paddle::ReduceSize()
{
    if (_heightOffset > _widthOffset)
    {
        _heightOffset -= .5;
    }
}

void Paddle::ResetSize()
{
    _heightOffset = _originalHeight; 
}

