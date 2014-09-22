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
    radius = rad;
    velocity = 1.0; 
    x_vel = 1.0;
    y_vel = 1.0; 
}

Ball::Ball(Ball &b) : 
    DrawableObject(b.Center, b.Color)
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
            glVertex2d(Center.X + radius * cos(2 * PI * i / num_segments),
                Center.Y + radius * sin(2 * PI * i / num_segments)); 
        }
    glEnd(); 
}

void Ball::Update()
{
    Center.X += x_vel; 
    Center.Y += y_vel; 
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

void Ball::BounceOffPaddle(CollisionTypeEnum col)
{
    if ((col & LEFT_COLLISION) == LEFT_COLLISION)
    {
        if (x_vel < 0)
        {
            x_vel *= -1;
        }
    }
    if ((col & RIGHT_COLLISION) == RIGHT_COLLISION)
    {
        if (x_vel > 0)
        {
            x_vel *= -1;
        }
    }
    if ((col & TOP_COLLISION) == TOP_COLLISION)
    {
        if (y_vel > 0)
        {
            y_vel *= -1;
        }
    }
    if ((col & BOTTOM_COLLISION) == BOTTOM_COLLISION)
    {
        if (y_vel < 0)
        {
            y_vel *= -1;
        }
    }
}

void Ball::BounceOffPaddle(float change)
{
    throw ERROR_CALL_NOT_IMPLEMENTED; 
}

void Ball::BounceOffPaddle(int spin)
{
    throw ERROR_CALL_NOT_IMPLEMENTED;
}

void Ball::BounceOffWall(CollisionTypeEnum col)
{
    if ((col & LEFT_COLLISION) == LEFT_COLLISION)
    {
        if (x_vel < 0)
        {
            x_vel *= -1;
        }
    }
    if ((col & RIGHT_COLLISION) == RIGHT_COLLISION)
    {
        if (x_vel > 0)
        {
            x_vel *= -1;
        }
    }
    if ((col & TOP_COLLISION) == TOP_COLLISION)
    {
        if (y_vel > 0)
        {
            y_vel *= -1; 
        }
    }
    if ((col & BOTTOM_COLLISION) == BOTTOM_COLLISION)
    {
        if (y_vel < 0)
        {
            y_vel *= -1; 
        }
    }
}

void Ball::ResetBall(float x, float y)
{
    Center.X = x; 
    Center.Y = y; 
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
    return Center.X - radius;
}

float Ball::Y_Min()
{
    return Center.Y - radius;
}

float Ball::X_Max()
{
    return Center.X + radius;
}

float Ball::Y_Max()
{
    return Center.Y + radius;
}