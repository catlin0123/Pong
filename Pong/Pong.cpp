//includes
#include <gl\freeglut.h>
#include <gl\GLU.h>
#include "Paddle.h"
#include "Ball.h"
#include "DrawableObject.h"
#include "CollisionManager.h"
#include "Wall.h"
#include "Enums.h"
#include "Net.h"

//callbacks 
void display(void); 
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);
void special_keys(int key, int x, int y);
void special_keys_up(int key, int x, int y);
void animate(int frame);
void BallCollideWithWall(CollisionTypeEnum col);
void BallCollideWithPaddle(CollisionTypeEnum col);
void Score(CollisionTypeEnum col);
void LeftCollideWithWall(CollisionTypeEnum col);
void RightCollideWithWall(CollisionTypeEnum col);

//constants
const unsigned char ESCAPE_KEY = 27;
const float WHITE[3] = { 1.0, 1.0, 1.0 };

//globals
int ScreenWidth = 600; 
int ScreenHeight = 300;

bool Keystate[256];
bool SpecKeystate[256];
bool Paused = false;

Ball ball;

Paddle left_player;
Paddle right_player;

CollisionManager collision_man; 

Net net;

Wall left_wall; 
Wall right_wall; 
Wall top_wall; 
Wall bottom_wall; 

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
	ball = Ball(Point(50, 50),5, WHITE);

    left_player = Paddle(Point(10, 50), 10, 40, WHITE);
    right_player = Paddle(Point(190, 50), 10, 40, WHITE);

    net = Net(Point(100, 50), VERTICAL, WHITE, 98);

    top_wall = Wall(Point(100, 99), HORIZONTAL, WHITE, 198);
    bottom_wall = Wall(Point(100, 1), HORIZONTAL, WHITE, 198);
    left_wall = Wall(Point(1, 50), VERTICAL, WHITE, 98);
    right_wall = Wall(Point(199, 50), VERTICAL, WHITE, 98);

    collision_man.RegisterCollision(&ball, &left_player, BallCollideWithPaddle);
    collision_man.RegisterCollision(&ball, &right_player, BallCollideWithPaddle);
    collision_man.RegisterCollision(&ball, &top_wall, BallCollideWithWall); 
    collision_man.RegisterCollision(&ball, &bottom_wall, BallCollideWithWall);
    collision_man.RegisterCollision(&ball, &left_wall, Score);
    collision_man.RegisterCollision(&ball, &right_wall, Score);

    collision_man.RegisterCollision(&left_player, &top_wall, LeftCollideWithWall);
    collision_man.RegisterCollision(&left_player, &bottom_wall, LeftCollideWithWall);
    collision_man.RegisterCollision(&left_player, &left_wall, LeftCollideWithWall);
    collision_man.RegisterCollision(&left_player, &net, LeftCollideWithWall);

    collision_man.RegisterCollision(&right_player, &top_wall, RightCollideWithWall);
    collision_man.RegisterCollision(&right_player, &bottom_wall, RightCollideWithWall);
    collision_man.RegisterCollision(&right_player, &right_wall, RightCollideWithWall);
    collision_man.RegisterCollision(&right_player, &net, RightCollideWithWall);

    glutMainLoop(); 

    return 0; 
}


void display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);
    
    ball.Draw();
    left_player.Draw();
    right_player.Draw();
    left_wall.Draw();
    right_wall.Draw();
    top_wall.Draw();
    bottom_wall.Draw();
    net.Draw();

    if (Paused)
    {
        //TODO Display pause message
    }	

    //glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    ScreenWidth = w;
    ScreenHeight = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 200, 0, 100);
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
        //Paused = !Paused;
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

    if (SpecKeystate[GLUT_KEY_LEFT])
    {
        right_player.ChangeXSpeed(-1 * PaddleInc);
    }

    if (SpecKeystate[GLUT_KEY_RIGHT])
    {
        right_player.ChangeXSpeed(PaddleInc);
    }

    if (SpecKeystate[GLUT_KEY_UP])
    {
        right_player.ChangeYSpeed(PaddleInc);
    }

    if (SpecKeystate[GLUT_KEY_DOWN])
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
        collision_man.CheckAndExecuteCollisions();
        left_player.Update();
        right_player.Update();
        ball.Update();

        glutTimerFunc(30, animate, frame + 1);
    }

    glutPostRedisplay();
}

void BallCollideWithPaddle(CollisionTypeEnum col)
{
    ball.BounceOffPaddle(col); 
}

void BallCollideWithWall(CollisionTypeEnum col)
{
    ball.BounceOffWall(col); 
}

void Score(CollisionTypeEnum col)
{
    if (LEFT_COLLISION)
    {
        right_player.Score++;
    }
    if (RIGHT_COLLISION)
    {
        left_player.Score++;
    }

    ball.ResetBall(100, 50);
}

void LeftCollideWithWall(CollisionTypeEnum col)
{
    if (col == RIGHT_COLLISION)
    {
        if (left_player.X_Vel() > 0)
        {
            left_player.ResetXSpeed();
        }
    }
    if (col == LEFT_COLLISION)
    {
        if (left_player.X_Vel() < 0)
        {
            left_player.ResetXSpeed();
        }
    }
    if (col == TOP_COLLISION)
    {
        if (left_player.Y_Vel() > 0)
        {
            left_player.ResetYSpeed();
        }
    }
    if (col == BOTTOM_COLLISION)
    {
        if (left_player.Y_Vel() < 0)
        {
            left_player.ResetYSpeed();
        }
    }
}

void RightCollideWithWall(CollisionTypeEnum col)
{
    if (col == RIGHT_COLLISION)
    {
        if (right_player.X_Vel() > 0)
        {
            right_player.ResetXSpeed(); 
        }
    }
    if (col == LEFT_COLLISION)
    {
        if (right_player.X_Vel() < 0)
        {
            right_player.ResetXSpeed();
        }
    }
    if (col == TOP_COLLISION)
    {
        if (right_player.Y_Vel() > 0)
        {
            right_player.ResetYSpeed();
        }
    }
    if (col == BOTTOM_COLLISION)
    {
        if (right_player.Y_Vel() < 0)
        {
            right_player.ResetYSpeed();
        }
    }
}