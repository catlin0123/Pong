#include "Paddle.h"
#include "DrawableObject.h"
#include <gl\freeglut.h>

Paddle::Paddle() :
	DrawableObject()
{
	x_inc = 0;
	y_inc = 0;
	widthOffset = 0;
	heightOffset = 0;
    originalHeight = 0; 
}

Paddle::Paddle(Point center, float width, float height, const float color[]) :
    DrawableObject(center, color)
{
    x_inc = 0; 
    y_inc = 0; 
    widthOffset = width / 2; 
    heightOffset = height / 2; 
    originalHeight = height / 2; 
}

Paddle::Paddle(Paddle &p) :
    DrawableObject(p.Center, p.Color)
{
    x_inc = p.x_inc; 
    y_inc = p.y_inc;
    widthOffset = p.widthOffset; 
    heightOffset = p.heightOffset; 
    originalHeight = p.originalHeight; 
}

void Paddle::Draw()
{
    glColor4fv(Color);
    glBegin(GL_POLYGON); 
        glVertex2f(Center.X + widthOffset, Center.Y + heightOffset); 
        glVertex2f(Center.X + widthOffset, Center.Y - heightOffset);
        glVertex2f(Center.X - widthOffset, Center.Y - heightOffset);
        glVertex2f(Center.X - widthOffset, Center.Y + heightOffset);
    glEnd();
}
void Paddle::Update()
{
    Center.X += x_inc;
    Center.Y += y_inc; 
}
void Paddle::ChangeXSpeed(float inc)
{
    if (x_inc < widthOffset - 1  && x_inc > -1 * widthOffset + 1)
    {
        x_inc += inc;
    }
    /*if (x_inc > -1 && x_inc < 1)
    {
        ResetXSpeed();
    }*/
}
void Paddle::ChangeYSpeed(float inc)
{
    if (y_inc < heightOffset - 2 && y_inc > -1 * heightOffset + 1)
    {
        y_inc += inc;
    }
    /*if (y_inc > -1 && y_inc < 1)
    {
        ResetYSpeed(); 
    }*/
}
void Paddle::ResetXSpeed()
{
    x_inc = 0; 
}
void Paddle::ResetYSpeed()
{
    y_inc = 0; 
}

void Paddle::ResetSpeed()
{
    x_inc = 0; 
    y_inc = 0; 
}

float Paddle::X_Min()
{
    return Center.X - widthOffset; 
}
float Paddle::Y_Min()
{
    return Center.Y - heightOffset; 
}
float Paddle::X_Max()
{
    return Center.X + widthOffset; 
}
float Paddle::Y_Max()
{
    return Center.Y + heightOffset;
}

float Paddle::X_Vel()
{
    return x_inc;
}

float Paddle::Y_Vel()
{
    return y_inc;
}

void Paddle::ReduceSize()
{
    if (heightOffset > widthOffset)
    {
        heightOffset -= .5;
    }
}

void Paddle::ResetSize()
{
    heightOffset = originalHeight; 
}

