#ifndef _DrawableObject_H_
#define _DrawableObject_H_

#include "Point.h"
#include "Enums.h"

class DrawableObject
{
    protected:
        /*!
        * @brief the color of the object
        */
        float _color[4];

    public:
        /*!
        * @brief the center location of the object.
        */
        Point Center;

		DrawableObject();
        DrawableObject(Point center, const float color[]);
        DrawableObject(DrawableObject &d); 
        virtual void Draw() = 0; 
        virtual float X_Min() = 0; 
        virtual float Y_Min() = 0; 
        virtual float X_Max() = 0; 
        virtual float Y_Max() = 0;
        CollisionTypeEnum didCollide(DrawableObject &obj);
};

#endif