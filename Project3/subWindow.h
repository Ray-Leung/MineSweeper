#pragma once

class subWindow
{
public:
	enum
	{
		Width = 200, Height = 80
	};

	void gameLose();
	void gameWin();

private:
	void newWindow(char *c);
	void mouse(int button, int state, int x, int y);
};

