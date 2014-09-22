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
     float x1, y1, x2, y2; 
     x1 = (*this).Center.X;
     x2 = obj.Center.X; 
     y1 = (*this).Center.Y; 
     y2 = obj.Center.Y; 

     bool to_left = x1 < x2; 
     bool above = y1 > y2; 

     bool left_collision = false; 
     bool right_collision = false; 
     bool top_collision = false; 
     bool bottom_collision = false; 

     if (to_left)
     {
         right_collision = ((*this).X_Max() > obj.X_Min()) && (y1 < obj.Y_Max()) && (y1 > obj.Y_Min()); 
     }
     else
     {
         left_collision = ((*this).X_Min() < obj.X_Max()) && (y1 < obj.Y_Max()) && (y1 > obj.Y_Min());
     }

     if (above)
     {
         bottom_collision = ((*this).Y_Min() < obj.Y_Max()) && (x1 < obj.X_Max()) && (x1 > obj.X_Min()); 
     }
     else
     {
         top_collision = ((*this).Y_Max() > obj.Y_Min()) && (x1 < obj.X_Max()) && (x1 > obj.X_Min());
     }

     /*float x_min, x_max, y_min, y_max;
     x_min = (*this).X_Min();
     x_max = (*this).X_Max();
     y_min = (*this).Y_Min();
     y_max = (*this).Y_Max();

     left_collision = x_min < obj.X_Max() && y1 > obj.Y_Min() && y1 < obj.Y_Max();*/

     CollisionTypeEnum collision = NO_COLLISION; 
     if (left_collision)
     {
         collision = CollisionTypeEnum(collision | LEFT_COLLISION); 
     }
     if (right_collision)
     {
         collision = CollisionTypeEnum(collision | RIGHT_COLLISION);
     }
     if (top_collision)
     {
         collision = CollisionTypeEnum(collision | TOP_COLLISION);
     }
     if (bottom_collision)
     {
         collision = CollisionTypeEnum(collision | BOTTOM_COLLISION); 
     }
	 return collision;
 }