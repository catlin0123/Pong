#include "Wall.h"

Wall::Wall() :
	DrawableObject()
{

}

Wall::Wall(Point center, OrientationEnum orientation, float color[], float length) :
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

void Wall::CollideLeft()
{

}

void Wall::CollideRight()
{

}

void Wall::CollideTop()
{

}

void Wall::CollideBottom()
{

}