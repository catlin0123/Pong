#include "DrawableObject.h"
#include "Ball.h"
#include <math.h>
#include <GL/freeglut.h>

Ball::Ball(Point center, int rad, float color[]) :
    DrawableObject(center.x, center.y, color)
{
    radius = rad;
    velocity = 1.0; 
    x_vel = 1.0;
    y_vel = 0.0; 
}

Ball::Ball(Ball &b) : 
    DrawableObject(pnt.x, pnt.y, Color)
{
    radius = b.radius; 
    velocity = b.velocity; 
    x_vel = b.x_vel; 
    y_vel = b.y_vel; 
}

void Ball::Draw()
{
    int num_segments = 20; 
    const double PI = 3.14159265358979323846;

    glColor3fv(Color);
    glBegin(GL_POLYGON);
        for (int i = 0; i < num_segments; i++)
        {
            glVertex2d(pnt.x + radius * cos(2 * PI * i / num_segments),
                pnt.y + radius * sin(2 * PI * i / num_segments)); 
        }
    glEnd(); 
}

void Ball::Update()
{
    pnt.x += x_vel; 
    pnt.y += y_vel; 
}

void Ball::IncreaseSpeed()
{
    velocity += 1; 
    ScaleVelocity(); 
}

void Ball::DecreaseSpeed()
{
    if (velocity > 1)
    {
        velocity -= 1; 
        ScaleVelocity();
    }
}

void Ball::BounceOffPaddle()
{
    x_vel *= -1; 
}

void Ball::BounceOffPaddle(float change)
{
    throw ERROR_CALL_NOT_IMPLEMENTED; 
}

void Ball::BounceOffPaddle(int spin)
{
    throw ERROR_CALL_NOT_IMPLEMENTED;
}

void Ball::BounceOffWall()
{
    y_vel *= -1; 
}

void Ball::ResetBall(float x, float y)
{
    pnt.x = x; 
    pnt.y = y; 
    velocity = 1.0;
    ScaleVelocity(); 
}

void Ball::ScaleVelocity()
{
    float angle = atan(y_vel / x_vel);
    y_vel = velocity * cos(angle);
    x_vel = velocity * cos(angle);
}

float Ball::X_Min()
{
    return pnt.x - radius;
}

float Ball::Y_Min()
{
    return pnt.y - radius;
}

float Ball::X_Max()
{
    return pnt.x + radius;
}

float Ball::Y_Max()
{
    return pnt.y + radius;
}

void Ball::CollideLeft()
{
    if (x_vel < 0)
    {
        x_vel *= -1; 
    }
}
void Ball::CollideRight()
{
    if (x_vel > 0)
    {
        x_vel *= -1; 
    }
}
void Ball::CollideTop()
{
    if (y_vel < 0)
    {
        y_vel *= -1; 
    }
}
void Ball::CollideBottom()
{
    if (y_vel > 0)
    {
        y_vel *= -1; 
    }
}