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
void keyboard_up(unsigned char key, int x, int y);
void special_keys(int key, int x, int y);
void special_keys_up(int key, int x, int y);
void animate(int frame);

//constants
const unsigned char ESCAPE_KEY = 27;

//globals
int ScreenWidth = 600; 
int ScreenHeight = 300;

bool Keystate[256];
bool SpecKeystate[256];
bool Paused = false;

Ball ball;
Paddle left_player;
Paddle right_player;

const float PaddleInc = .5;


int main(int argc, char *argv[])
{
    //set up the window
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(ScreenWidth, ScreenHeight);
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("Pong"); 
    glClearColor(0.0, 0.0, 0.0, 1.0); 

    //specify callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutSpecialFunc(special_keys);
    glutSpecialUpFunc(special_keys_up);

    glutTimerFunc(30, animate, 1);

    //TODO set up players and ball

    glutMainLoop(); 

    return 0; 
}


void display(void)
{
    ball.Draw();
    left_player.Draw();
    right_player.Draw();

    if (Paused)
    {
        //TODO Display pause message
    }

    glutSwapBuffers();
    glFlush();
}

void reshape(int w, int h)
{
    ScreenWidth = w;
    ScreenHeight = h;

    glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y)
{
    Keystate[key] = true;

    if (Keystate['w'] || Keystate['W'])
    {
        left_player.ChangeYSpeed(PaddleInc);
    }

    if (Keystate['a'] || Keystate['A'])
    {
        left_player.ChangeXSpeed((-1)*PaddleInc);
    }

    if (Keystate['s'] || Keystate['S'])
    {
        left_player.ChangeYSpeed(-1 * PaddleInc);
    }

    if (Keystate['d'] || Keystate['D'])
    {
        left_player.ChangeXSpeed(PaddleInc); 
    }

    if (Keystate['+'])
    {
        ball.IncreaseSpeed();
    }

    if (Keystate['-'])
    {
        ball.DecreaseSpeed();
    }

    if (Keystate[' '])
    {
        Paused = !Paused;
        //TODO Change paddle colors?
    }

    if (Keystate[ESCAPE_KEY])
    {
        glutExit();
    }
}

void keyboard_up(unsigned char key, int x, int y)
{
    Keystate[key] = false;
}

void special_keys(int key, int x, int y)
{
    SpecKeystate[key] = true;

    if (Keystate[GLUT_KEY_LEFT])
    {
        right_player.ChangeXSpeed(-1 * PaddleInc);
    }

    if (Keystate[GLUT_KEY_RIGHT])
    {
        right_player.ChangeXSpeed(PaddleInc);
    }

    if (Keystate[GLUT_KEY_UP])
    {
        right_player.ChangeYSpeed(PaddleInc);
    }

    if (Keystate[GLUT_KEY_DOWN])
    {
        right_player.ChangeYSpeed(-1 * PaddleInc);
    }
}

void special_keys_up(int key, int x, int y)
{
    SpecKeystate[key] = false;
}

void animate(int frame)
{
    if (!Paused)
    {
        left_player.Update();
        right_player.Update();
        ball.Update();
    }

    glutTimerFunc(30, animate, frame + 1);

    glutPostRedisplay();
}

