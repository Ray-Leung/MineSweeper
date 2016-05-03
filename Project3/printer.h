#pragma once
#include <string>

class Printer
{
public:
	enum {CELL_WIDTH = 30, CELL_HEIGHT = 30, BAR_HEIGHT = 30};
	void drawClosedField(int x, int y);
	void drawOpenedField(int x, int y, int minesAround);
	void drawFlag(int x, int y);
	void drawMine(int x, int y);
	void drawBadFlag(int x, int y);
	void drawTargetMine(int x, int y);
	void drawRestButton();
	void drawMineLeft(std::string str);
	void drawTimer(std::string str);

private:
	void drawOpenedField(int x, int y);
	
};

void drawSubWindow();

