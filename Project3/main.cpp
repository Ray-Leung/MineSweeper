#include <gl\freeglut.h>
#include <iostream>
#include <random>
#include "game.h"
#include "printer.h"

using namespace std;

Game game;
void display();
void mouse(int button, int state, int x, int y);
void reset();
void createSubWindow();
void subDisplay();
void subMouse(int button, int state, int x, int y);
void subCloseFunc();
int mainWindow, subwindow;
int num = 0;
int time = 0;
static bool FIRSTCLICK = true;
static bool SUBWINDOW_ACTIVATED = true;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	game.draw(time);
	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{	
	if (state == GLUT_UP && !SUBWINDOW_ACTIVATED)
	{	
		
		switch (button)
		{

		case GLUT_LEFT_BUTTON:
			
			if (y < Printer::CELL_HEIGHT && x >= ((Game::Width + 1)/2 - 1) * Printer::CELL_WIDTH && x <= ((Game::Width + 1)/2) * Printer::CELL_WIDTH)
			{
				reset();
				break;
			}

			if (FIRSTCLICK)
				game = Game::Game(num, x / Printer::CELL_WIDTH, (y - Printer::BAR_HEIGHT - 4) / Printer::CELL_HEIGHT);
				FIRSTCLICK = false;
			if (!game.gameState() && y > Printer::BAR_HEIGHT)
			{
				
				game.open(x / Printer::CELL_WIDTH, (y - Printer::BAR_HEIGHT - 4) / Printer::CELL_HEIGHT);
			}
				break;

		case GLUT_RIGHT_BUTTON:
			if (y < Printer::BAR_HEIGHT)
				break;
			if (FIRSTCLICK)
				game = Game::Game(num, 0, 0);
				FIRSTCLICK = false;
			if (!game.gameState())
				
				game.mark(x / Printer::CELL_WIDTH, (y - Printer::BAR_HEIGHT - 4)/ Printer::CELL_HEIGHT);
			break;

		case GLUT_MIDDLE_BUTTON:
			SUBWINDOW_ACTIVATED = true;
			glutSetWindow(subwindow);
			glutPositionWindow(200 + (Game::Width * Printer::CELL_WIDTH) / 2 - (0.6 * 9 * 30) / 2
				, 120 + (Game::Height * Printer::CELL_HEIGHT + Printer::BAR_HEIGHT) / 2 - (0.6 * 9 * 30) / 2);
			glutShowWindow();
			break;
		}
			glutPostRedisplay();
	}
}

void reset()
{
	
	FIRSTCLICK = true;
	time = 0;
	game = Game::Game(num);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutReshapeWindow(Game::Width * Printer::CELL_WIDTH, Game::Height * Printer::CELL_HEIGHT + Printer::BAR_HEIGHT);
	glOrtho(0, Game::Width * Printer::CELL_WIDTH, Game::Height * Printer::CELL_HEIGHT + Printer::BAR_HEIGHT, 0, -1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void timer_func(int n)
{
	
	if (FIRSTCLICK || SUBWINDOW_ACTIVATED)
	{	
		goto end;
	}
	else if(game.gameState())
	{
		return;
	}
	else 
	{
		time += n;
		glutPostRedisplay();
	}
end:
	
	glutTimerFunc(n, timer_func, n);
}

void createSubWindow()
{
	glutInitWindowSize(0.6 * 9 * 30,
		0.6 * 9 * 30);
	glutInitWindowPosition(200 + (Game::Width * Printer::CELL_WIDTH) / 2 - (0.6 * 9 * 30) / 2
		, 120 + (Game::Height * Printer:: CELL_HEIGHT + Printer::BAR_HEIGHT) / 2 - (0.6 * 9 * 30) / 2);
	subwindow = glutCreateWindow(" ");
	glutSetWindow(subwindow);
	glClearColor(0.8f, 0.8f, 0.8f, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 0.6 * Game::Width * Printer::CELL_WIDTH,
		0.6 * Game::Height * Printer::CELL_HEIGHT, 0, -1.0, 1.0);
	glutDisplayFunc(subDisplay);
	glutMouseFunc(subMouse);
}

void subDisplay() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawSubWindow();
	glutSwapBuffers();
}

void subMouse(int button, int state, int x, int y)
{
	if (state == GLUT_UP)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			if (y >= 15 && y <= 45)
				num = 0;
			
			if (y >= 60 && y <= 90)
				num = 1;

			if (y >= 105 && y <= 135)
				num = 2;

			SUBWINDOW_ACTIVATED = false;
			glutHideWindow();
			glutSetWindow(mainWindow);
			reset();
			glutPostWindowRedisplay(mainWindow);
			break;

		case GLUT_MIDDLE_BUTTON:
			SUBWINDOW_ACTIVATED = false;
			glutHideWindow();
			glutSetWindow(mainWindow);
			glutPostWindowRedisplay(mainWindow);
			break;
		}
	}
}

int main(int argc, char **argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	game = Game::Game();
	glutInitWindowSize(Game::Width * Printer::CELL_WIDTH, Game::Height * Printer::CELL_HEIGHT + Printer::BAR_HEIGHT);
	glutInitWindowPosition(200, 120);
	mainWindow = glutCreateWindow("MINE SWEEPER");
	glClearColor(0.8f, 0.8f, 0.8f, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, Game::Width * Printer::CELL_WIDTH, Game::Height * Printer::CELL_HEIGHT + Printer::BAR_HEIGHT, 0, -1.0, 1.0);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	timer_func(110);
	createSubWindow();
	glutMainLoop();
	return 0;
}