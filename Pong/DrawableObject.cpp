#include "DrawableObject.h"

DrawableObject::DrawableObject()
{

}

 DrawableObject::DrawableObject(Point center, float color[])
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

 void DrawableObject::Collide(DrawableObject &obj)
 {
     bool CollideLeft = false; 
     bool CollideRight = false;
     bool CollideUp = false;
     bool CollideDown = false;




 }

 CollisionTypeEnum didCollide(DrawableObject &obj)
 {
	 return NO_COLLISION;
 }