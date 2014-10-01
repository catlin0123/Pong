/*************************************************************************//**
* @file
*
* @brief The header file containing enums for Pong
****************************************************************************/
#pragma once

/*************************************************************************//**
* @enum
*
* @brief Defines the different kinds of collisions as or-able values.
****************************************************************************/
enum CollisionTypeEnum
{
    NO_COLLISION = 0, 
    TOP_COLLISION = 1, 
    BOTTOM_COLLISION = 2,
    LEFT_COLLISION = 4, 
    RIGHT_COLLISION = 8,
};


/*************************************************************************//**
* @enum
*
* @brief Defines the different orientations of a wall
****************************************************************************/
enum OrientationEnum
{
	VERTICAL,
	HORIZONTAL
};