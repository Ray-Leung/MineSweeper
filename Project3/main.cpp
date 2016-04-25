#include <gl\freeglut.h>
#include <iostream>
#include <random>
#include "game.h"
#include "printer.h"

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dis(0, 2);
Game game;
void display();
void mouse(int button, int state, int x, int y);
void reset();
void createSubWindow();
void subDisplay();
void subMouse(int button, int state, int x, int y);
int mainWindow, subwindow;
int num = 0;
int time = 0;
static bool FIRSTCLICK = true;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	game.draw(time);
	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_UP)
	{	
		
		switch (button)
		{

		case GLUT_LEFT_BUTTON:
			FIRSTCLICK = false;

			if (y < Printer::CELL_HEIGHT)
			{
				reset();
				break;
			}
			if (!game.gameState())
				game.open(x / Printer::CELL_WIDTH, (y - Printer::BAR_HEIGHT - 4) / Printer::CELL_HEIGHT);
			break;

		case GLUT_RIGHT_BUTTON:
			if (y < Printer::CELL_HEIGHT)
				break;

			if (!game.gameState())
				game.mark(x / Printer::CELL_WIDTH, (y - Printer::BAR_HEIGHT - 4)/ Printer::CELL_HEIGHT);
			break;

		case GLUT_MIDDLE_BUTTON:
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
	
	if (FIRSTCLICK)
	{	
		goto end;
	}
	else 
	{
		time += n;
		glutPostRedisplay();
	}
end:
	glutTimerFunc(n, timer_func, n);
}

int main(int argc, char **argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	game = Game::Game(num);
	glutInitWindowSize(Game::Width * Printer::CELL_WIDTH, Game::Height * Printer::CELL_HEIGHT + Printer::BAR_HEIGHT);
	glutInitWindowPosition(200, 120);
	mainWindow = glutCreateWindow("MINE SWEEPER");
	glClearColor(0.6f, 0.6f, 0.6f, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, Game::Width * Printer::CELL_WIDTH, Game::Height * Printer::CELL_HEIGHT + Printer::BAR_HEIGHT, 0, -1.0, 1.0);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	timer_func(130);
	createSubWindow();
	glutMainLoop();
	return 0;
}

void createSubWindow()
{
	glutInitWindowSize(0.6 * 9 * 30,
		0.6 * 9 * 30);
	glutInitWindowPosition(200 + (Game::Width * Printer::CELL_WIDTH) / 2 - (0.6 * 9 * 30) / 2
		, 120 + (Game::Height * Printer:: CELL_HEIGHT + Printer::BAR_HEIGHT) / 2 - (0.6 * 9 * 30) / 2);
	subwindow = glutCreateWindow(" ");
	glutSetWindow(subwindow);
	glClearColor(0.0f, 0.0f, 0.0f, 0);
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

	glColor3f(0.8f, 0.8f, 0.8f);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(0, 0.6 * 9 * 30);
	glVertex2f(0.6 * 9 * 30, 0.7 * 9 * 30);
	glVertex2f(0.6 * 9 * 30, 0);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(8, 15);
	glVertex2f(8, 45);
	glVertex2f(8, 15);
	glVertex2f(0.6 * 9 * 30 - 8, 15);
	glEnd();
	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_LINES);
	glVertex2f(0.6 * 9 * 30 - 8, 15);
	glVertex2f(0.6 * 9 * 30 - 8, 45);
	glVertex2f(0.6 * 9 * 30 - 8, 45);
	glVertex2f(8, 45);
	glEnd();
	glRasterPos2f(50, 35);
	for (char c : "Beginner")
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(8, 60);
	glVertex2f(8, 90);
	glVertex2f(8, 60);
	glVertex2f(0.6 * 9 * 30 - 8, 60);
	glEnd();
	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_LINES);
	glVertex2f(0.6 * 9 * 30 - 8, 60);
	glVertex2f(0.6 * 9 * 30 - 8, 90);
	glVertex2f(0.6 * 9 * 30 - 8, 90);
	glVertex2f(8, 90);
	glEnd();
	glRasterPos2f(35, 80);
	for (char c : "Intermediate")
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(8, 105);
	glVertex2f(8, 135);
	glVertex2f(8, 105);
	glVertex2f(0.6 * 9 * 30 - 8, 105);
	glEnd();
	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_LINES);
	glVertex2f(0.6 * 9 * 30 - 8, 105);
	glVertex2f(0.6 * 9 * 30 - 8, 135);
	glVertex2f(0.6 * 9 * 30 - 8, 135);
	glVertex2f(8, 135);
	glEnd();
	glRasterPos2f(55, 125);
	for (char c : "Expert")
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}
	glEnd();

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
			break;

		}
		glutHideWindow();
		glutSetWindow(mainWindow);
		reset();
		glutPostWindowRedisplay(mainWindow);
	}
}

