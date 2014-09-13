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
    void ScaleVelocity(); 
    
public:
    Ball(Point center, int rad, float color[]);
    Ball(Ball &b);
    void Draw();
    void Update(); 
    void IncreaseSpeed();
    void DecreaseSpeed(); 
    void BounceOffPaddle(float change);
    void BounceOffPaddle(int spin);
    void BounceOffPaddle(); 
    void BounceOffWall();
    float FurthestLeftCoord();
    float FurthestRightCoord();
    float FurthestTopCoord();
    float FurthestBottomCoord();
    void ResetBall(float x, float y); 
};

#endif