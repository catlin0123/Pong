/*************************************************************************//**
* @file
*
* @brief The header file for the Net
****************************************************************************/
#pragma once
#include "Wall.h"
class Net :
    public Wall
{
public:
    Net();
    Net(Point center, OrientationEnum orientation, const float color[], float length);
    ~Net();

    virtual void Draw();
};

