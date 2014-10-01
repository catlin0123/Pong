/*************************************************************************//**
* @file
*
* @mainpage Program 1 - pong
*
* @section course_section Course Information
*
* @author Paul Blasi, Caitlin Taggart
*
* @date <program date due>
*
* @par Professor:
*         Dr. Weiss
*
* @par Course:
*         Graphics  -  9 AM
*
* @par Location:
*         McLaury - 313
*
* @section program_section Program Information
*
* @details This program is a remake of the classic video game Pong.
* Along with the basic ping pong style gameplay, this version also
* adds:
*	- left and right movement to the basic up and down
*	- ability to change ball speed
*	- acceleration and decelleration of paddle movement
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
@verbatim
c:\> make pong
@endverbatim
*
* @par Usage:
@verbatim
On Windows:
	c:\> pong.exe

On Linux:
	c:\> ./pong
@endverbatim
*
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
* @bug If bouncing quickly between a paddle and the wall, the ball will occassionally bounce out of the wall.
*
* @todo Document all of the files
*
* @par Modifications and Development Timeline:
@verbatim
Date          Modification
------------  --------------------------------------------------------------
Sep 11, 2014  Initial project setup
Sep 12, 2014  Created base class, as well as initial attempt at the Ball
			  class
Sep 14, 2014  Finished basic ball and paddles
Sep 14, 2014  Cleaned up code, added Wall class
Sep 14, 2014  Added Enums class
Sep 22, 2014  Added CollisionManager, started on functions for collisions
Sep 23, 2014  Tweaking the collision functions.
Sep 24, 2014  Made the windows resizable, keeping the aspect ratio 2:1
Sep 26, 2014  Finished paddle decelleration, added velocity to the ball
			  depending on the speed of the paddle it collides with
Sep 27, 2014  Normalized naming scheme, followed C# naming scheme as that's
			  what we're used to.
Sep 28, 2014  Lot's of documentation
@endverbatim
*
*****************************************************************************/

//includes
#include <gl\freeglut.h>
#include <gl\GLU.h>
#include <string>

#include "Paddle.h"
#include "Ball.h"
#include "DrawableObject.h"
#include "CollisionManager.h"
#include "Wall.h"
#include "Enums.h"
#include "Net.h"

//callbacks 
void Display(void); 
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void SpecialKeys(int key, int x, int y);
void SpecialKeysUp(int key, int x, int y);
void Animate(int frame);
void BallCollideWithWall(CollisionTypeEnum col);
void BallCollideWithLeftPaddle(CollisionTypeEnum col);
void BallCollideWithRightPaddle(CollisionTypeEnum col);
void Score(CollisionTypeEnum col);
void LeftCollideWithWall(CollisionTypeEnum col);
void RightCollideWithWall(CollisionTypeEnum col);
void UpdatePaddles();

//constants
const unsigned char ESCAPE_KEY = 27;
const float WHITE[4] = { 1.0, 1.0, 1.0, 1.0 };

//globals
int SCREEN_WIDTH = 600; 
int SCREEN_HEIGHT = 300;

bool KEYSTATE[256];
bool SPECKEYSTATE[256];
bool PAUSED = false;

Ball BALL;

Paddle LEFT_PLAYER;
Paddle RIGHT_PLAYER;

CollisionManager COLLISION_MAN;
string LAST_PADDLE_COLLISION;

Net NET;

Wall LEFT_WALL; 
Wall RIGHT_WALL; 
Wall TOP_WALL; 
Wall BOTTOM_WALL; 

const float PADDLE_INC = .5;
const float PADDLE_DEC = 3 * PADDLE_INC;

/**************************************************************************//**
* @author Paul Blasi, Caitlin Taggart
*
* @par Description:
* Main execution point of the app. Initializes the window and prepares the
* main objects to be drawn on the screen. Also sets up the callback events.
*
* @returns Execution outcome.
*
*****************************************************************************/
int main(int argc, char *argv[])
{
    //set up the window
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("Pong"); 
    glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //specify callbacks
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(KeyboardUp);
    glutSpecialFunc(SpecialKeys);
    glutSpecialUpFunc(SpecialKeysUp);

    glutTimerFunc(30, Animate, 1);

    //TODO set up players and ball
	BALL = Ball(Point(100, 50),5, WHITE);

    LEFT_PLAYER = Paddle(Point(10, 50), 10, 40, WHITE);
    RIGHT_PLAYER = Paddle(Point(190, 50), 10, 40, WHITE);

    NET = Net(Point(100, 50), VERTICAL, WHITE, 98);

    TOP_WALL = Wall(Point(100, 99), HORIZONTAL, WHITE, 198);
    BOTTOM_WALL = Wall(Point(100, 1), HORIZONTAL, WHITE, 198);
    LEFT_WALL = Wall(Point(1, 50), VERTICAL, WHITE, 98);
    RIGHT_WALL = Wall(Point(199, 50), VERTICAL, WHITE, 98);

    COLLISION_MAN.RegisterCollision(&BALL, &LEFT_PLAYER, BallCollideWithLeftPaddle);
    COLLISION_MAN.RegisterCollision(&BALL, &RIGHT_PLAYER, BallCollideWithRightPaddle);
    COLLISION_MAN.RegisterCollision(&BALL, &TOP_WALL, BallCollideWithWall); 
    COLLISION_MAN.RegisterCollision(&BALL, &BOTTOM_WALL, BallCollideWithWall);
    COLLISION_MAN.RegisterCollision(&BALL, &LEFT_WALL, Score);
    COLLISION_MAN.RegisterCollision(&BALL, &RIGHT_WALL, Score);

    COLLISION_MAN.RegisterCollision(&LEFT_PLAYER, &TOP_WALL, LeftCollideWithWall);
    COLLISION_MAN.RegisterCollision(&LEFT_PLAYER, &BOTTOM_WALL, LeftCollideWithWall);
    COLLISION_MAN.RegisterCollision(&LEFT_PLAYER, &LEFT_WALL, LeftCollideWithWall);
    COLLISION_MAN.RegisterCollision(&LEFT_PLAYER, &NET, LeftCollideWithWall);

    COLLISION_MAN.RegisterCollision(&RIGHT_PLAYER, &TOP_WALL, RightCollideWithWall);
    COLLISION_MAN.RegisterCollision(&RIGHT_PLAYER, &BOTTOM_WALL, RightCollideWithWall);
    COLLISION_MAN.RegisterCollision(&RIGHT_PLAYER, &RIGHT_WALL, RightCollideWithWall);
    COLLISION_MAN.RegisterCollision(&RIGHT_PLAYER, &NET, RightCollideWithWall);

    glutMainLoop(); 

    return 0; 
}

/**************************************************************************//**
* @author Paul Blasi, Caitlin Taggart
*
* @par Description:
* The display callback. Draws each of the objects and displays score for each
* player. If the game is currently paused, it also draws a translucent box
* over the play area and the text "Paused".
*
*****************************************************************************/
void Display(void) 
{
	int length;
	
	glClear(GL_COLOR_BUFFER_BIT);
    
    BALL.Draw();
    LEFT_PLAYER.Draw();
    RIGHT_PLAYER.Draw();
    LEFT_WALL.Draw();
    RIGHT_WALL.Draw();
    TOP_WALL.Draw();
    BOTTOM_WALL.Draw();
    NET.Draw();

	string right_score = to_string(RIGHT_PLAYER.Score);
	string left_score = to_string(LEFT_PLAYER.Score);


	glColor4fv(WHITE);

	length = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)left_score.c_str());
	glRasterPos2i(50 - (200.0 / SCREEN_WIDTH * length / 2.0), 90);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)left_score.c_str());

	length = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)right_score.c_str());
	glRasterPos2i(150 - (200.0 / SCREEN_WIDTH * length / 2.0), 90);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)right_score.c_str());

    if (PAUSED)
    {
		float alphaBlack[4] = { 0.0, 0.0, 0.0, .60 };
		Paddle temp;
		temp = Paddle(Point(100, 50), 200, 100, alphaBlack);
		temp.Draw();

		glColor4fv(WHITE);
		length = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)"PAUSED");
		glRasterPos2i(100 - (200.0/SCREEN_WIDTH * length / 2.0), 50);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)"PAUSED");
    }	

    //glFlush();
    glutSwapBuffers();
}

/**************************************************************************//**
* @author Paul Blasi, Caitlin Taggart
*
* @par Description:
* Resizes the ViewPort, maintaining the aspect ratio of 2:1
*
* @param[in] w - the new width of the screen
* @param[in] h - the new height of the screen
*
*****************************************************************************/
void Reshape(int w, int h)
{
    SCREEN_WIDTH = w;
    SCREEN_HEIGHT = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 200, 0, 100);

    if (float(w) / h > 2)
        glViewport((w - 2 * h) / 2, 0, 2 * h, h);
    else
        glViewport(0, (h - w / 2) / 2, w, w / 2);
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Stores the state of the pressed key and does an initial update of the left
* player. Also handles the key presses for space, which pauses, escape, which
* exits the game, and +/-, which incresses and decreases the speed of the ball
* respectively.
*
* @param[in] key - the key that was pressed
* @param[in] x - the x position of the mouse when the key was pressed
* @param[in] y - the y position of the mouse when the key was pressed
*
*****************************************************************************/
void Keyboard(unsigned char key, int x, int y)
{
	KEYSTATE[key] = true;

	if ((KEYSTATE['w'] || KEYSTATE['W']) && !PAUSED)
	{
		LEFT_PLAYER.ChangeYSpeed(PADDLE_INC);
	}

	if ((KEYSTATE['a'] || KEYSTATE['A']) && !PAUSED)
	{
		LEFT_PLAYER.ChangeXSpeed((-1)*PADDLE_INC);
	}

	if ((KEYSTATE['s'] || KEYSTATE['S']) && !PAUSED)
	{
		LEFT_PLAYER.ChangeYSpeed(-1 * PADDLE_INC);
	}

	if ((KEYSTATE['d'] || KEYSTATE['D']) && !PAUSED)
	{
		LEFT_PLAYER.ChangeXSpeed(PADDLE_INC);
	}

	if (KEYSTATE['+'] && !PAUSED)
    {
        BALL.IncreaseMinVelocity();
    }

	if (KEYSTATE['-'] && !PAUSED)
    {
        BALL.DecreaseMinVelocity();
    }

    if (KEYSTATE[' '])
    {
        PAUSED = !PAUSED;

		if (PAUSED)
		{
			glutPostRedisplay();
		}
		else
		{
			glutTimerFunc(30, Animate, 0);
		}
    }

    if (KEYSTATE[ESCAPE_KEY])
    {
        glutExit();
    }
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Stores the state of the key that was released.
*
* @param[in] key - the key that was pressed
* @param[in] x - the x position of the mouse when the key was pressed
* @param[in] y - the y position of the mouse when the key was pressed
*
*****************************************************************************/
void KeyboardUp(unsigned char key, int x, int y)
{
    KEYSTATE[key] = false;
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Stores the state of the special key that was released.
*
* @param[in] key - the special key that was pressed
* @param[in] x - the x position of the mouse when the key was pressed
* @param[in] y - the y position of the mouse when the key was pressed
*
*****************************************************************************/
void SpecialKeys(int key, int x, int y)
{
	SPECKEYSTATE[key] = true;

	if (SPECKEYSTATE[GLUT_KEY_LEFT] && !PAUSED)
	{
		RIGHT_PLAYER.ChangeXSpeed(-1 * PADDLE_INC);
	}

	if (SPECKEYSTATE[GLUT_KEY_RIGHT] && !PAUSED)
	{
		RIGHT_PLAYER.ChangeXSpeed(PADDLE_INC);
	}

	if (SPECKEYSTATE[GLUT_KEY_UP] && !PAUSED)
	{
		RIGHT_PLAYER.ChangeYSpeed(PADDLE_INC);
	}

	if (SPECKEYSTATE[GLUT_KEY_DOWN] && !PAUSED)
	{
		RIGHT_PLAYER.ChangeYSpeed(-1 * PADDLE_INC);
	}
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Stores the state of the special key that was released.
*
* @param[in] key - the special key that was pressed
* @param[in] x - the x position of the mouse when the key was pressed
* @param[in] y - the y position of the mouse when the key was pressed
*
*****************************************************************************/
void SpecialKeysUp(int key, int x, int y)
{
    SPECKEYSTATE[key] = false;
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Updates the state of the CollisionManager and all of the movable objects
*
* @param[in] frame -  the frame count since the last pause/start of the game
*
*****************************************************************************/
void Animate(int frame)
{
    if (!PAUSED)
    {
		if (frame % 10 == 0)
		{
			UpdatePaddles();
		}

        COLLISION_MAN.CheckAndExecuteCollisions();
        LEFT_PLAYER.Update();
        RIGHT_PLAYER.Update();
        BALL.Update();

        glutTimerFunc(30, Animate, frame + 1);
    }

    glutPostRedisplay();
}

/**************************************************************************//**
* @author Paul Blasi, Caitlin Taggart
*
* @par Description:
* The action a ball is to take when it collides with the left paddle
*
* @param[in] col - the type of collision that occurred
*
*****************************************************************************/
void BallCollideWithLeftPaddle(CollisionTypeEnum col)
{
    BALL.BounceOffPaddle(col); 
    float ratio = ((LEFT_PLAYER.Center.Y - BALL.Center.Y) / (LEFT_PLAYER.Center.Y - LEFT_PLAYER.Y_Max()));
    BALL.BounceOffPaddle(ratio);

	if (LEFT_PLAYER.X_Vel() >= 0)
	{
		if (LEFT_PLAYER.Velocity() > BALL.Velocity())
		{
			BALL.IncreaseSpeed((LEFT_PLAYER.Velocity() - BALL.Velocity()) / 3);
		}
		else
		{
			BALL.DecreaseSpeed(-1 * (LEFT_PLAYER.Velocity() - BALL.Velocity()) / 3);
		}
	}

	if (LAST_PADDLE_COLLISION != "Left")
	{
		LEFT_PLAYER.ReduceSize();
		RIGHT_PLAYER.ReduceSize();
	}

	LAST_PADDLE_COLLISION = "Left";
}

/**************************************************************************//**
* @author Paul Blasi, Caitlin Taggart
*
* @par Description:
* The action a ball is to take when it collides with the right paddle
*
* @param[in] col - the type of collision that occurred
*
*****************************************************************************/
void BallCollideWithRightPaddle(CollisionTypeEnum col)
{
    BALL.BounceOffPaddle(col);
    float ratio = ((RIGHT_PLAYER.Center.Y - BALL.Center.Y) / (RIGHT_PLAYER.Center.Y - RIGHT_PLAYER.Y_Max()));
	BALL.BounceOffPaddle(ratio);

	if (RIGHT_PLAYER.X_Vel() <= 0)
	{
		if (RIGHT_PLAYER.Velocity() > BALL.Velocity())
		{
			BALL.IncreaseSpeed((RIGHT_PLAYER.Velocity() - BALL.Velocity()) / 3);
		}
		else
		{
			BALL.DecreaseSpeed(-1 * (RIGHT_PLAYER.Velocity() - BALL.Velocity()) / 3);
		}
	}
    
	if (LAST_PADDLE_COLLISION != "Right")
	{
		LEFT_PLAYER.ReduceSize();
		RIGHT_PLAYER.ReduceSize();
	}

	LAST_PADDLE_COLLISION = "Right";
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* The action a ball is to take when it collides with a non-scoring wall
*
* @param[in] col - the type of collision that occurred
*
*****************************************************************************/
void BallCollideWithWall(CollisionTypeEnum col)
{
    BALL.BounceOffWall(col); 
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* The action a ball is to take when it collides with a scoring wall
*
* @param[in] col - the type of collision that occurred
*
*****************************************************************************/
void Score(CollisionTypeEnum col)
{
    if (col == LEFT_COLLISION)
    {
        RIGHT_PLAYER.Score++;
    }
    if (col == RIGHT_COLLISION)
    {
        LEFT_PLAYER.Score++;
    }

	if (LEFT_PLAYER.Score == 10 || RIGHT_PLAYER.Score == 10)
	{
		LEFT_PLAYER.Score = 0;
		RIGHT_PLAYER.Score = 0;

		PAUSED = true;
	}

    LEFT_PLAYER.ResetSize();
    RIGHT_PLAYER.ResetSize(); 
    BALL.ResetBall(100, 50);
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* The action the left paddle is to take when it collides with any wall. Keeps
* the paddles from travelling through walls.
*
* @param[in] col - the type of collision that occurred
*
*****************************************************************************/
void LeftCollideWithWall(CollisionTypeEnum col)
{
    if (col == RIGHT_COLLISION)
    {
        if (LEFT_PLAYER.X_Vel() > 0)
        {
            LEFT_PLAYER.ResetXSpeed();
        }
    }
    if (col == LEFT_COLLISION)
    {
        if (LEFT_PLAYER.X_Vel() < 0)
        {
            LEFT_PLAYER.ResetXSpeed();
        }
    }
    if (col == TOP_COLLISION)
    {
        if (LEFT_PLAYER.Y_Vel() > 0)
        {
            LEFT_PLAYER.ResetYSpeed();
        }
    }
    if (col == BOTTOM_COLLISION)
    {
        if (LEFT_PLAYER.Y_Vel() < 0)
        {
            LEFT_PLAYER.ResetYSpeed();
        }
    }
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* The action the right paddle is to take when it collides with any wall. Keeps
* the paddles from travelling through walls.
*
* @param[in] col - the type of collision that occurred
*
*****************************************************************************/
void RightCollideWithWall(CollisionTypeEnum col)
{
    if (col == RIGHT_COLLISION)
    {
        if (RIGHT_PLAYER.X_Vel() > 0)
        {
            RIGHT_PLAYER.ResetXSpeed(); 
        }
    }
    if (col == LEFT_COLLISION)
    {
        if (RIGHT_PLAYER.X_Vel() < 0)
        {
            RIGHT_PLAYER.ResetXSpeed();
        }
    }
    if (col == TOP_COLLISION)
    {
        if (RIGHT_PLAYER.Y_Vel() > 0)
        {
            RIGHT_PLAYER.ResetYSpeed();
        }
    }
    if (col == BOTTOM_COLLISION)
    {
        if (RIGHT_PLAYER.Y_Vel() < 0)
        {
            RIGHT_PLAYER.ResetYSpeed();
        }
    }
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Updates each of the paddles x and y speeds every 1/3rd of a second
*
*****************************************************************************/
void UpdatePaddles()
{
	if ((KEYSTATE['w'] || KEYSTATE['W']) && !PAUSED)
	{
		LEFT_PLAYER.ChangeYSpeed(PADDLE_INC);
	}
	else if (LEFT_PLAYER.Y_Vel() > 0)
	{
		if (LEFT_PLAYER.Y_Vel() < PADDLE_DEC)
		{
			LEFT_PLAYER.ResetYSpeed();
		}
		else
		{
			LEFT_PLAYER.ChangeYSpeed(-1 * PADDLE_DEC);
		}
	}

	if ((KEYSTATE['a'] || KEYSTATE['A']) && !PAUSED)
	{
		LEFT_PLAYER.ChangeXSpeed((-1)*PADDLE_INC);
	}
	else if (LEFT_PLAYER.X_Vel() < 0)
	{
		if (LEFT_PLAYER.X_Vel() > -1 * PADDLE_DEC)
		{

			LEFT_PLAYER.ResetXSpeed();
		}
		else
		{
			LEFT_PLAYER.ChangeXSpeed(PADDLE_DEC);
		}
	}

	if ((KEYSTATE['s'] || KEYSTATE['S']) && !PAUSED)
	{
		LEFT_PLAYER.ChangeYSpeed(-1 * PADDLE_INC);
	}
	else if (LEFT_PLAYER.Y_Vel() < 0)
	{
		if (LEFT_PLAYER.Y_Vel() >  -1 * PADDLE_DEC)
		{

			LEFT_PLAYER.ResetYSpeed();
		}
		else
		{
			LEFT_PLAYER.ChangeYSpeed(PADDLE_DEC);
		}
	}

	if ((KEYSTATE['d'] || KEYSTATE['D']) && !PAUSED)
	{
		LEFT_PLAYER.ChangeXSpeed(PADDLE_INC);
	}
	else if (LEFT_PLAYER.X_Vel() > 0)
	{
		if (LEFT_PLAYER.X_Vel() < PADDLE_DEC)
		{

			LEFT_PLAYER.ResetXSpeed();
		}
		else
		{
			LEFT_PLAYER.ChangeXSpeed(-1 * PADDLE_DEC);
		}
	}

	if (SPECKEYSTATE[GLUT_KEY_LEFT] && !PAUSED)
	{
		RIGHT_PLAYER.ChangeXSpeed(-1 * PADDLE_INC);
	}
	else if (RIGHT_PLAYER.X_Vel() < 0)
	{
		if (RIGHT_PLAYER.X_Vel() > -1 * PADDLE_DEC)
		{

			RIGHT_PLAYER.ResetXSpeed();
		}
		else
		{
			RIGHT_PLAYER.ChangeXSpeed(PADDLE_DEC);
		}
	}

	if (SPECKEYSTATE[GLUT_KEY_RIGHT] && !PAUSED)
	{
		RIGHT_PLAYER.ChangeXSpeed(PADDLE_INC);
	}
	else if (RIGHT_PLAYER.X_Vel() > 0)
	{
		if (RIGHT_PLAYER.X_Vel() < PADDLE_DEC)
		{

			RIGHT_PLAYER.ResetXSpeed();
		}
		else
		{
			RIGHT_PLAYER.ChangeXSpeed(-1 * PADDLE_DEC);
		}
	}

	if (SPECKEYSTATE[GLUT_KEY_UP] && !PAUSED)
	{
		RIGHT_PLAYER.ChangeYSpeed(PADDLE_INC);
	}
	else if (RIGHT_PLAYER.Y_Vel() > 0)
	{
		if (RIGHT_PLAYER.Y_Vel() < PADDLE_DEC)
		{

			RIGHT_PLAYER.ResetYSpeed();
		}
		else
		{
			RIGHT_PLAYER.ChangeYSpeed(-1 * PADDLE_DEC);
		}
	}

	if (SPECKEYSTATE[GLUT_KEY_DOWN] && !PAUSED)
	{
		RIGHT_PLAYER.ChangeYSpeed(-1 * PADDLE_INC);
	}
	else if (RIGHT_PLAYER.Y_Vel() < 0)
	{
		if (RIGHT_PLAYER.Y_Vel() > -1 * PADDLE_DEC)
		{

			RIGHT_PLAYER.ResetYSpeed();
		}
		else
		{
			RIGHT_PLAYER.ChangeYSpeed(PADDLE_DEC);
		}
	}
}