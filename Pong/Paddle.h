#ifndef _Paddle_H_
#define _Paddle_H_

#include "DrawableObject.h"
#include <cmath>

class Paddle : public DrawableObject
{
    private:
        float _widthOffset; 
        float _heightOffset;
        float _originalHeight; 
        float _xInc; 
        float _yInc; 
    
    public:
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

        int Score = 0;

        void ReduceSize(); 
        void ResetSize(); 
};

#endif 