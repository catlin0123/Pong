#ifndef _Paddle_H_
#define _Paddle_H_

#include "DrawableObject.h"

class Paddle : public DrawableObject
{
    private:
        float widthOffset; 
        float heightOffset;
        float x_inc; 
        float y_inc; 
    
    public:
		Paddle();
        Paddle(Point center, float width, float height, float color[]);
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

        void CollideLeft();
        void CollideRight();
        void CollideTop();
        void CollideBottom();

};

#endif 