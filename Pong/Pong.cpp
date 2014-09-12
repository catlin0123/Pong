//includes
#include <gl\freeglut.h>
#include <gl\GLU.h>
#include "Paddle.h"
#include "Ball.h"
#include "DrawableObject.h"

//callbacks 
void display(void); 
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void special_keys(int key, int x, int y);

//constants
const unsigned char ESCAPE_KEY = 27;

//globals
int ScreenWidth = 600; 
int ScreenHeight = 300; 


int main(int argc, char *argv[])
{
    //set up the window
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(ScreenWidth, ScreenHeight);
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("Pong"); 
    glClearColor(0.0, 0.0, 0.0, 1.0); 

    //specify callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keys);

    glutMainLoop(); 

    return 0; 
}


void display(void)
{
}

void reshape(int w, int h)
{
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
        case 'W':
            break;
        case 'a':
        case 'A':
            break;
        case 's':
        case 'S':
            break;
        case 'd':
        case 'D':
            break;
        case '+':
            break;
        case '-':
            break;
        case ' ':
            break;
        case ESCAPE_KEY:
            break;
        default:
            break;
    }
}

void special_keys(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_LEFT:
            break;
        case GLUT_KEY_RIGHT:
            break;
        case GLUT_KEY_UP:
            break;
        case GLUT_KEY_DOWN:
            break;
        default:
            break;
    }
}

