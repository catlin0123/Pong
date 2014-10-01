/*************************************************************************//**
* @file
*
* @brief The header file containing the Point structure for Pong
****************************************************************************/

/*************************************************************************//**
* @struct
*
* @brief The point struct, containing a float x and y value and a couple
*        simple constructors.
****************************************************************************/
struct Point
{
    float X;
    float Y;

	Point(float x, float y) { X = x; Y = y; }
	Point() { X = 0; Y = 0; }
};