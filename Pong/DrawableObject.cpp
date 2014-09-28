#include "DrawableObject.h"

DrawableObject::DrawableObject()
{

}

 DrawableObject::DrawableObject(Point center, const float color[])
{
	Center = center;
    for (int i = 0; i < 4; i++)
    {
        _color[i] = color[i];
    }
}

 DrawableObject::DrawableObject(DrawableObject &d)
 {
	 Center = d.Center;

     for (int i = 0; i < 4; i++)
     {
         _color[i] = d._color[i];
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

     CollisionTypeEnum collision = NO_COLLISION; 
     if (left_collision)
     {
         collision = CollisionTypeEnum(collision | LEFT_COLLISION); 
		 (*this).Center.X = obj.X_Max() + ((*this).X_Max() - (*this).Center.X);
     }
     if (right_collision)
     {
         collision = CollisionTypeEnum(collision | RIGHT_COLLISION);
		 (*this).Center.X = obj.X_Min() - ((*this).X_Max() - (*this).Center.X);
     }
     if (top_collision)
     {
         collision = CollisionTypeEnum(collision | TOP_COLLISION);
		 (*this).Center.Y = obj.Y_Min() - ((*this).Y_Max() - (*this).Center.Y);
     }
     if (bottom_collision)
     {
         collision = CollisionTypeEnum(collision | BOTTOM_COLLISION);
		 (*this).Center.Y = obj.Y_Max() + ((*this).Y_Max() - (*this).Center.Y);
     }
	 return collision;
 }