#ifndef _Ball_H_
#define _Ball_H_

#include "DrawableObject.h"

class Ball : public DrawableObject
{
private:
    int radius; 

public:
    Ball(Point center, int radius, float color[]);
    Ball(Ball &p);
    void Draw();
};

#endif