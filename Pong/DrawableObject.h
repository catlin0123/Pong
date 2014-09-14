#ifndef _DrawableObject_H_
#define _DrawableObject_H_

#include "Point.h"
#include "Enums.h"

class DrawableObject
{
    protected:
        Point Center;
        float Color[3];

    public:
		DrawableObject();
        DrawableObject(Point center, float color[]);
        DrawableObject(DrawableObject &d); 
        virtual void Draw() = 0; 
        virtual float X_Min() = 0; 
        virtual float Y_Min() = 0; 
        virtual float X_Max() = 0; 
        virtual float Y_Max() = 0; 
        virtual void CollideLeft() = 0;
        virtual void CollideRight() = 0;
        virtual void CollideTop() = 0;
        virtual void CollideBottom() = 0;
        void Collide(DrawableObject &obj); 
        CollisionTypeEnum didCollide(DrawableObject &obj);
};

#endif