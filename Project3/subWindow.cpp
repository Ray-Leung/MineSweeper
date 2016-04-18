#include "subWindow.h"
#include <gl\freeglut.h>
#include <Windows.h>
#include <string>

#define MAX_CHAR 128
void display();
void drawString(std::string str);

static std::string outText;
void subWindow::newWindow(char *c)
{

	glutCreateSubWindow(1, 50, 50, Width, Height);
	drawString(outText);
}

void subWindow::gameLose()
{
	outText = "You Suck!";
	newWindow("LOSE");
}


void subWindow::gameWin()
{
	outText = "Congrt!";
	newWindow("WIN");
}


void drawString(std::string str)
{
	static bool isFirstCall = true;
	static GLuint lists;
	

	if (isFirstCall)
	{
		isFirstCall = false;
		lists = glGenLists(MAX_CHAR);

		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	for (char c : str)
	{
		glCallList(lists + c);
	}
}
