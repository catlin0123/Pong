#include "Paddle.h"
#include "DrawableObject.h"
#include <gl\freeglut.h>

Paddle::Paddle(Point center, int w_offset, int h_offset, float color[]) :
    DrawableObject(center.x, center.y, color)
{
    x_inc = 0; 
    y_inc = 0; 
    widthOffset = w_offset; 
    heightOffset = heightOffset; 
}

Paddle::Paddle(Paddle &p) :
    DrawableObject(p.pnt.x, p.pnt.y, p.Color)
{
    x_inc = p.x_inc; 
    y_inc = p.y_inc;
    widthOffset = p.widthOffset; 
    heightOffset = p.heightOffset; 
}

void Paddle::Draw()
{
    glColor3fv(Color);
    glBegin(GL_POLYGON); 
        glVertex2f(pnt.x + widthOffset, pnt.y + heightOffset); 
        glVertex2f(pnt.x + widthOffset, pnt.y - heightOffset);
        glVertex2f(pnt.x - widthOffset, pnt.y - heightOffset);
        glVertex2f(pnt.x - widthOffset, pnt.y + heightOffset);
    glEnd();
}
void Paddle::Update()
{
    pnt.x += x_inc;
    pnt.y += y_inc; 
}
void Paddle::ChangeXSpeed(float inc)
{
    x_inc += inc; 
    if (x_inc > -1 && x_inc < 1)
    {
        ResetXSpeed();
    }
}
void Paddle::ChangeYSpeed(float inc)
{
    y_inc += inc; 
    if (y_inc > -1 && y_inc < 1)
    {
        ResetYSpeed(); 
    }
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
    return pnt.x - widthOffset; 
}
float Paddle::Y_Min()
{
    return pnt.y - heightOffset; 
}
float Paddle::X_Max()
{
    return pnt.x + widthOffset; 
}
float Paddle::Y_Max()
{
    return pnt.y + heightOffset;
}
void Paddle::CollideLeft()
{

}
void Paddle::CollideRight()
{

}
void Paddle::CollideTop()
{

}
void Paddle::CollideBottom()
{

}

