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
int mainWindow;
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
		}
			glutPostRedisplay();
	}
}

void reset()
{
	num = dis(gen);
	game = Game::Game(num);
	FIRSTCLICK = true;
	time = 0;
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

	num = dis(gen);
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
	glutMainLoop();

	return 0;
}