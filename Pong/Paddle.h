/*************************************************************************//**
* @file
*
* @brief The header file for the Paddle
****************************************************************************/
#ifndef _Paddle_H_
#define _Paddle_H_

#include "DrawableObject.h"
#include <cmath>

class Paddle : public DrawableObject
{
    private:
		/*!
		* @brief 1/2 the width of the Paddle
		*/
        float _widthOffset; 

		/*!
		* @brief 1/2 the height of the Paddle
		*/
		float _heightOffset;

		/*!
		* @brief 1/2 the original height of the Paddle
		*/
		float _originalHeight;

		/*!
		* @brief x increment during each update
		*/
		float _xInc;

		/*!
		* @brief y increment during each update
		*/
        float _yInc; 
    
	public:

		/*!
		* @brief Points accumulated by the paddle
		*/
        int Score = 0;

		Paddle();
        Paddle(Point center, float width, float height, const float color[]);
        Paddle(Paddle &p);

        void Draw(); 
        void Update(); 

        void ChangeXSpeed(float inc);
        void ChangeYSpeed(float inc); 

        void ResetXSpeed(); 
        void ResetYSpeed(); 
        void ResetSpeed();

        float X_Min();
        float Y_Min();
        float X_Max();
		float Y_Max();

        float X_Vel();
        float Y_Vel();

		float Velocity();

        void ReduceSize(); 
        void ResetSize(); 
};

#endif 