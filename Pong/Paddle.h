#ifndef _Paddle_H_
#define _Paddle_H_

#include "DrawableObject.h"

class Paddle : public DrawableObject
{
    private:
        int widthOffset; 
        int heightOffset;
    
    public: 
        Paddle(Point center, int w_offset, int h_offset, float color[]);
        Paddle(Paddle &p); 
        void Draw(); 
};

#endif 