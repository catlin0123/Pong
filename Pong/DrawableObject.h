#ifndef _DrawableObject_H_
#define _DrawableObject_H_

#include "Point.h"

class DrawableObject
{
    protected:
        Point pnt;
        float Color[3];

    public:
        DrawableObject(float x, float y, float color[]);
        DrawableObject(DrawableObject &d); 
        virtual void Draw() = 0; 
};

#endif