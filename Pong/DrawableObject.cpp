/*************************************************************************//**
* @file
*
* @brief Contains the implemenation of the Drawable Object Class
****************************************************************************/
#include "DrawableObject.h"


/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* An empty contructor for the Drawable Object class.
* 
* @returns an empty drawable object
*
*****************************************************************************/
DrawableObject::DrawableObject()
{

}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* A contructor for the drawable object calss, takes a center and a color. 
* 
* @param[in] center - the center point of the object. 
* @param[in] color - the color of the object. 
* 
* @returns a drawable object.
*
*****************************************************************************/
 DrawableObject::DrawableObject(Point center, const float color[])
{
	Center = center;
    for (int i = 0; i < 4; i++)
    {
        _color[i] = color[i];
    }
}

 /**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* A copy constructor for the drawable object class
* 
* @param[in] d - the drawable object to copy
* 
* @returns a drawable object copy of d.
*
*****************************************************************************/
 DrawableObject::DrawableObject(DrawableObject &d)
 {
	 Center = d.Center;

     for (int i = 0; i < 4; i++)
     {
         _color[i] = d._color[i];
     }
 }

 /**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* decides if two drawable objects collided or not based on the positioning of
* this object and the other and then tells what type of collision this object
* had. 
* 
* @param[in] obj - the object to check if this drawable object collided with
* 
* @returns the type of collision to occured (mulitiple if needed)
*
*****************************************************************************/
 CollisionTypeEnum DrawableObject::didCollide(DrawableObject &obj)
 {
     float x1, y1, x2, y2; 
     x1 = (*this).Center.X;
     x2 = obj.Center.X; 
     y1 = (*this).Center.Y; 
     y2 = obj.Center.Y; 

     //determine which side the object is on
     bool to_left = x1 < x2; 
     bool above = y1 > y2; 

     bool left_collision = false; 
     bool right_collision = false; 
     bool top_collision = false; 
     bool bottom_collision = false; 

     //determine what kind of collision occured
     //if the object is overlapped according to its relative position and its x and y parameters, while 
     //also having its center in between the middle of the of either its x and y min and max parameters 
     //a collision occurred. 
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

     //or the collisions types to ensure that all collisions are documents for correct movement 
     //if the object it two things at once. 
     //also move the object so that it doesn't go out of the bounds of where it should be. 
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