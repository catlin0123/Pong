/*************************************************************************//**
* @file
*
* @brief THe header file for the ball class. 
****************************************************************************/
#ifndef _Ball_H_
#define _Ball_H_

#include "DrawableObject.h"

class Ball : public DrawableObject
{
private:
    /*!
    * @brief the radius of the ball
    */
    int _radius; 

    /*!
    * @brief the overall velocity of the ball
    */
    float _velocity;

    /*!
    * @brief the minimum velocity that ball should at a given time
    */
	float _minVelocity;

    /*!
    * @brief the x velocity of the ball
    */
    float _xVel; 

    /*!
    * @brief the y velocity of the ball
    */
    float _yVel; 

    void ScaleVelocity(float inc); 
    
public:
	Ball();
    Ball(Point center, int rad, const float color[]);
    Ball(Ball &b);
    void Draw();
    void Update();
	void IncreaseMinVelocity();
	void DecreaseMinVelocity();
    void IncreaseSpeed(float value = 0.5);
    void DecreaseSpeed(float value = 0.5); 
    void BounceOffPaddle(float ratio);
    void BounceOffPaddle(CollisionTypeEnum col); 
    void BounceOffWall(CollisionTypeEnum col);
    void ResetBall(float x, float y); 
    float X_Min();
    float Y_Min();
    float X_Max();
    float Y_Max();

	float Velocity();
};

#endif