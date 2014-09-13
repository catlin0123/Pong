#include "DrawableObject.h"

 DrawableObject::DrawableObject(float x, float y, float color[])
{
    pnt.x = x; 
    pnt.y = y; 
    for (int i = 0; i < 3; i++)
    {
        Color[i] = color[i];
    }
}

 DrawableObject::DrawableObject(DrawableObject &d)
 {
     pnt.x = d.pnt.x; 
     pnt.y = d.pnt.y; 

     for (int i = 0; i < 3; i++)
     {
         Color[i] = d.Color[i];
     }
 }
