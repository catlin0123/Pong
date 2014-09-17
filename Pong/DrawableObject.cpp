#include "DrawableObject.h"

DrawableObject::DrawableObject()
{

}

 DrawableObject::DrawableObject(Point center, const float color[])
{
	Center = center;
    for (int i = 0; i < 3; i++)
    {
        Color[i] = color[i];
    }
}

 DrawableObject::DrawableObject(DrawableObject &d)
 {
	 Center = d.Center;

     for (int i = 0; i < 3; i++)
     {
         Color[i] = d.Color[i];
     }
 }

 CollisionTypeEnum DrawableObject::didCollide(DrawableObject &obj)
 {
	 return NO_COLLISION;
 }