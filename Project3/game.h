#pragma once
#include <vector>

class Game
{
public:
	
	static int Width;
	static int Height;

	enum State
	{
		CLOSED, OPENED, FLAG
	};

	Game(int);
	Game();
	std::vector<std::vector<int>> mines;
	void draw(int sec);
	void open(int x, int y);
	void mark(int x, int y);
	bool gameState();
	int showFlags();
	void timer(int sec);

private:
	struct Cell
	{
		State state;
		bool hasMine = false;
		int mineAround = 0;

	};
	int numOfMines;
	int flags = 0;
	bool mineOpen;
	Cell field[30][30];
	bool checkMatch();
};

