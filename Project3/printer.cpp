#include "printer.h"
#include "game.h"
#include <GL\freeglut.h>
#include <gl\GL.h>
#include <math.h>
#include <iostream>

const double Pi = 3.1415926;

void Printer::drawClosedField(int x, int y)
{
	glColor3f(0.8f, 0.8f, 0.8f);
	glBegin(GL_QUADS);
	glVertex2f(x * CELL_WIDTH, y * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f((x + 1) * CELL_WIDTH, y * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f((x + 1) * CELL_WIDTH, (y + 1) * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH, (y + 1) * CELL_HEIGHT + BAR_HEIGHT);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(x * CELL_WIDTH, y * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f((x + 1) * CELL_WIDTH - 1, y * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH, y * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH, (y + 1) * CELL_HEIGHT - 1 + BAR_HEIGHT);
	glEnd();
	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_LINES);
	glVertex2f((x + 1) * CELL_WIDTH - 1, y * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f((x + 1) * CELL_WIDTH - 1, (y + 1)* CELL_HEIGHT - 1 + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH, (y + 1) * CELL_HEIGHT - 1 + BAR_HEIGHT);
	glVertex2f((x + 1) * CELL_WIDTH - 1, (y + 1) * CELL_HEIGHT - 1 + BAR_HEIGHT);
	glEnd();

}

void Printer::drawFlag(int x, int y)
{
	glColor3f(0.8f, 0.8f, 0.8f);
	glBegin(GL_QUADS);
	glVertex2f(x * CELL_WIDTH, y * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f((x + 1) * CELL_WIDTH, y * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f((x + 1) * CELL_WIDTH, (y + 1) * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH, (y + 1) * CELL_HEIGHT + BAR_HEIGHT);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(x * CELL_WIDTH + CELL_WIDTH / 2, y * CELL_HEIGHT + 3 + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH + CELL_WIDTH / 2, (y + 1) * CELL_HEIGHT - 8 + BAR_HEIGHT);
	glEnd();
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(x * CELL_WIDTH + CELL_WIDTH / 2 - 1, y * CELL_HEIGHT + 3 + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH + CELL_WIDTH / 2 - 8, y * CELL_HEIGHT + 4 + 3 + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH + CELL_WIDTH / 2 - 1, y * CELL_HEIGHT + 4 + 4 + 3 + BAR_HEIGHT);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(x * CELL_WIDTH + CELL_WIDTH / 3 - 2, (y + 1) * CELL_HEIGHT - 9 + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH + CELL_WIDTH * 2 / 3 + 2, (y + 1) * CELL_HEIGHT - 9 + BAR_HEIGHT);
	glEnd();
}

void Printer::drawBadFlag(int x, int y)
{
	glColor3f(0.8f, 0.8f, 0.8f);
	glBegin(GL_QUADS);
	glVertex2f(x * CELL_WIDTH, y * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f((x + 1) * CELL_WIDTH, y * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f((x + 1) * CELL_WIDTH, (y + 1) * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH, (y + 1) * CELL_HEIGHT + BAR_HEIGHT);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(x * CELL_WIDTH + CELL_WIDTH / 2, y * CELL_HEIGHT + 3 + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH + CELL_WIDTH / 2, (y + 1) * CELL_HEIGHT - 8 + BAR_HEIGHT);
	glEnd();
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(x * CELL_WIDTH + CELL_WIDTH / 2 - 1, y * CELL_HEIGHT + 3 + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH + CELL_WIDTH / 2 - 8, y * CELL_HEIGHT + 4 + 3 + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH + CELL_WIDTH / 2 - 1, y * CELL_HEIGHT + 4 + 4 + 3 + BAR_HEIGHT);
	glEnd();
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(x * CELL_WIDTH + 3, y * CELL_HEIGHT + 3 + BAR_HEIGHT);
	glVertex2f((x + 1) * CELL_WIDTH - 3, (y + 1) * CELL_HEIGHT - 3 + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH + 3, (y + 1) * CELL_HEIGHT - 3 + BAR_HEIGHT);
	glVertex2f((x + 1) * CELL_WIDTH - 3, y * CELL_HEIGHT + 3 + BAR_HEIGHT);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(x * CELL_WIDTH + CELL_WIDTH / 3 - 2, (y + 1) * CELL_HEIGHT - 9 + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH + CELL_WIDTH * 2 / 3 + 2, (y + 1) * CELL_HEIGHT - 9 + BAR_HEIGHT);
	glEnd();
}

void Printer::drawOpenedField(int x, int y, int minesAround)
{
	drawOpenedField(x, y);
	if (minesAround > 0)
	{
		switch (minesAround)
		{
		case 1:
			glColor3f(0.0f, 0.0f, 0.8f);
			break;
		case 2:
			glColor3f(0.0f, 1.0f, 0.0f);
			break;
		case 3:
			glColor3f(1.0f, 0.0f, 0.0f);
			break;
		case 4:
			glColor3f(0.0f, 0.0f, 1.0f);
			break;
		case 5:
			glColor3f(0.5f, 0.4f, 0.0f);
			break;
		case 6:
			glColor3f(0.0f, 0.8f, 0.5f);
			break;
		case 7:
			glColor3f(0.0f, 0.0f, 0.0f);
			break;
		case 8:
			glColor3f(0.8f, 0.8f, 0.8f);
			break;
		}
		glRasterPos2f(x * CELL_WIDTH + (29 - 9) / 2 + 1, (y + 1) * CELL_HEIGHT - 10 + BAR_HEIGHT);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (minesAround + '0'));
		glEnd();
	}
}

void Printer::drawMine(int x, int y)
{
	drawOpenedField(x, y);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < 13; i++)
	{
		glVertex2f(x * CELL_WIDTH + CELL_WIDTH / 2 + 9.0f * cos(2 * Pi * i / 13), y * CELL_HEIGHT + CELL_HEIGHT / 2 + 9.0f * sin(2 * Pi * i / 13) + BAR_HEIGHT);
	}
	glEnd();
	
}

void Printer::drawOpenedField(int x, int y)
{
	glColor3f(0.6f, 0.6f, 0.6f);
	glBegin(GL_QUADS);
	glVertex2f(x * CELL_WIDTH, y * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f((x + 1) * CELL_WIDTH, y * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f((x + 1) * CELL_WIDTH, (y + 1) * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH, (y + 1) * CELL_HEIGHT + BAR_HEIGHT);
	glEnd();
	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_LINES);
	glVertex2f((x + 1) * CELL_WIDTH - 1, y * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f((x + 1) * CELL_WIDTH - 1, (y + 1) * CELL_HEIGHT - 1 + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH, (y + 1) * CELL_HEIGHT - 1 + BAR_HEIGHT);
	glVertex2f((x + 1) * CELL_WIDTH - 1, (y + 1) * CELL_HEIGHT - 1 + BAR_HEIGHT);
	glEnd();
}



void Printer::drawTargetMine(int x, int y)
{
	drawOpenedField(x, y);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < 13; i++)
	{
		glVertex2f(x * CELL_WIDTH + CELL_WIDTH / 2 + 9.0f * cos(2 * Pi * i / 13), y * CELL_HEIGHT + CELL_HEIGHT / 2 + 9.0f * sin(2 * Pi * i / 13) + BAR_HEIGHT);
	}
	glEnd();
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(x * CELL_WIDTH + 3, y * CELL_HEIGHT + 3 + BAR_HEIGHT);
	glVertex2f((x + 1) * CELL_WIDTH - 3, (y + 1) * CELL_HEIGHT - 3 + BAR_HEIGHT);
	glVertex2f(x * CELL_WIDTH + 3, (y + 1) * CELL_HEIGHT - 3 + BAR_HEIGHT);
	glVertex2f((x + 1) * CELL_WIDTH - 3, y * CELL_HEIGHT + 3 + BAR_HEIGHT);
	glEnd();
}

void Printer::drawRestButton()
{	
	
	double mid = (Game::Width + 1) / 2;
	glColor3f(0.8f, 0.8f, 0.8f);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(0, BAR_HEIGHT);
	glVertex2f(Game::Width * CELL_WIDTH, Game::Height * CELL_HEIGHT + BAR_HEIGHT);
	glVertex2f(Game::Width * CELL_WIDTH, 0);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f((mid - 1) * CELL_WIDTH, 0);
	glVertex2f(mid * CELL_WIDTH - 1, 0);
	glVertex2f((mid - 1) * CELL_WIDTH, 0);
	glVertex2f((mid - 1) * CELL_WIDTH, BAR_HEIGHT - 1);
	glEnd();
	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_LINES);
	glVertex2f(mid * CELL_WIDTH - 1, 0);
	glVertex2f(mid * CELL_WIDTH - 1, BAR_HEIGHT - 1);
	glVertex2f((mid - 1) * CELL_WIDTH, BAR_HEIGHT - 1);
	glVertex2f(mid * CELL_WIDTH - 1, BAR_HEIGHT - 1);
	glEnd();
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < 20; i++)
	{
		glVertex2f((mid - 1) * CELL_WIDTH + CELL_WIDTH / 2 + 13.0f * cos(2 * Pi * i / 20) - 1, CELL_HEIGHT / 2 + 13.0f * sin(2 * Pi * i / 20));
	}
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2f((mid - 1) * CELL_WIDTH + CELL_WIDTH  / 3 + 2, BAR_HEIGHT / 3);
	glVertex2f(mid * CELL_WIDTH - CELL_WIDTH  / 3 + 2, BAR_HEIGHT / 3);
	glEnd();
	glPointSize(6.0f);
	glBegin(GL_LINES);
	glVertex2f((mid - 1) * CELL_WIDTH + 3, BAR_HEIGHT / 3);
	glVertex2f(mid * CELL_WIDTH - CELL_WIDTH / 3, BAR_HEIGHT / 3);
	glVertex2f((mid - 1) * CELL_WIDTH + 3, BAR_HEIGHT / 3);
	glVertex2f((mid - 1) * CELL_WIDTH + 3, BAR_HEIGHT / 3 + 1);
	glVertex2f((mid - 1) * CELL_WIDTH + 3, BAR_HEIGHT / 3 + 1);
	glVertex2f((mid - 1) * CELL_WIDTH + 1, BAR_HEIGHT / 3 + 1);
	glEnd();
	glLineWidth(2.4f);
	glBegin(GL_LINES);
	glVertex2f((mid - 1) * CELL_WIDTH + CELL_WIDTH * 2 / mid + 2, BAR_HEIGHT * 3 / 5);
	glVertex2f(mid * CELL_WIDTH - CELL_WIDTH / 3 + 2, BAR_HEIGHT * 3 / 5);
	glEnd();
}

void Printer::drawMineLeft(std::string str)
{
	
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(Game::Width * CELL_WIDTH - 3 * CELL_WIDTH, 0);
	glVertex2f(Game::Width * CELL_WIDTH, 0);
	glVertex2f(Game::Width * CELL_WIDTH, BAR_HEIGHT);
	glVertex2f(Game::Width * CELL_WIDTH - 3 * CELL_WIDTH, BAR_HEIGHT);
	glEnd();
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2f(Game::Width * CELL_WIDTH - 2 * CELL_WIDTH + 3, BAR_HEIGHT - 7);
	for (char c : str)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	glEnd();
}

void Printer::drawTimer(std::string str)
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(3 * Printer::CELL_WIDTH, 0);
	glVertex2f(3 * Printer::CELL_WIDTH, Printer::BAR_HEIGHT);
	glVertex2f(0, Printer::BAR_HEIGHT);
	glEnd();
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2f(1.3 * CELL_WIDTH, BAR_HEIGHT - 7);

	int count = 1;
	for (char c : str)
	{	
		if (count == 4 && c == '.')
			break;
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
		if (count == 4)
			break;
		count++;
	}
	glEnd();
}

void drawSubWindow()
{

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
	glColor3f(0.0f, 0.0f, 0.0f);
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
}