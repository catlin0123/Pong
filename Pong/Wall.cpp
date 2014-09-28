#include "Wall.h"
#include <GL/freeglut.h>

Wall::Wall() :
	DrawableObject()
{

}

Wall::Wall(Point center, OrientationEnum orientation, const float color[], float length) :
	DrawableObject(center, color)
{
	Orientation = orientation;
	Length = length;
}


Wall::~Wall()
{
}

void Wall::Draw()
{
    glColor3fv(_color);

    glBegin(GL_LINES);
        glVertex2d(X_Min(), Y_Min());
        glVertex2d(X_Max(), Y_Max());
    glEnd();
}

float Wall::X_Min()
{
	return Orientation == HORIZONTAL ? Center.X - Length / 2 : Center.X;
}

float Wall::Y_Min()
{
	return Orientation == VERTICAL ? Center.Y - Length / 2 : Center.Y;
}

float Wall::X_Max()
{
	return Orientation == HORIZONTAL ? Center.X + Length / 2 : Center.X;
}

float Wall::Y_Max()
{
	return Orientation == VERTICAL ? Center.Y + Length / 2 : Center.Y;
}