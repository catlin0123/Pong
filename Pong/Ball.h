#ifndef _Ball_H_
#define _Ball_H_

#include "DrawableObject.h"

class Ball : public DrawableObject
{
private:
    int radius; 
    float velocity; 
    float x_vel; 
    float y_vel; 
    void ScaleVelocity(float inc); 
    
public:
	Ball();
    Ball(Point center, int rad, const float color[]);
    Ball(Ball &b);
    void Draw();
    void Update();
    void IncreaseSpeed();
    void DecreaseSpeed(); 
    void BounceOffPaddle(float ratio);
    void BounceOffPaddle(int spin);
    void BounceOffPaddle(CollisionTypeEnum col); 
    void BounceOffWall(CollisionTypeEnum col);
    void ResetBall(float x, float y); 
    float X_Min();
    float Y_Min();
    float X_Max();
    float Y_Max();
};

#endif