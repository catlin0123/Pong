#ifndef _Paddle_H_
#define _Paddle_H_

#include "DrawableObject.h"

class Paddle : public DrawableObject
{
    private:
        int widthOffset; 
        int heightOffset;
        float x_inc; 
        float y_inc; 
    
    public: 
        Paddle(Point center, int w_offset, int h_offset, float color[]);
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