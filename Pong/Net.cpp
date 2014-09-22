#include "Net.h"
#include <GL/freeglut.h>

Net::Net()
{

}

Net::Net(Point center, OrientationEnum orientation, const float color[], float length) :
    Wall(center, orientation, color, length)
{

}

Net::~Net()
{

}

void Net::Draw()
{
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xff00);

    Wall::Draw();

    glDisable(GL_LINE_STIPPLE);
}
