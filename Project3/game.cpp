#include "game.h"
#include "printer.h"
#include <random>
#include <iostream>
#include <string>

int width[3] = { 9, 16, 30 };
int height[3] = { 9, 16, 16 };
int mine[3] = { 10, 40, 99 };
int Game::Width = 9;
int Game::Height = 9;

Game::Game()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> disHeight(0, 9 - 1);
	std::uniform_int_distribution<int> disWidth(0, 9 - 1);
	
	Width = 9;
	Height = 9;
	numOfMines = 10;
	mineOpen = false;
	flags = 0;

	for (int i = 0; i < 10; i++)
	{
		int x1, y1;
		do
		{
			x1 = disWidth(gen);
			y1 = disHeight(gen);
		} while (field[x1][y1].hasMine);
		field[x1][y1].hasMine = true;
		mines.push_back({ x1, y1 });
	}

	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			field[x][y].state = CLOSED;
			field[x][y].mineAround = 0;
			if (!field[x][y].hasMine)
			{

				for (int y1 = y - 1; y1 <= y + 1; y1++)
				{
					for (int x1 = x - 1; x1 <= x + 1; x1++)
					{
						if ((x1 == x && y1 == y) || x1 < 0 || x1 >= Width || y1 < 0 || y1 >= Height) continue;

						if (field[x1][y1].hasMine)
						{
							field[x][y].mineAround++;
						}
					}
				}
			}
		}
	}
}

Game::Game(int n)
{	
	Width = width[n];
	Height = height[n];
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> disHeight(0, Height - 1);
	std::uniform_int_distribution<int> disWidth(0, Width - 1);
	
	numOfMines = mine[n];

	mineOpen = false;
	flags = 0;

	for (int i = 0; i < numOfMines; i++)
	{
		int x1, y1;
		do
		{
			x1 = disWidth(gen);
			y1 = disHeight(gen);
		} while (field[x1][y1].hasMine);
		field[x1][y1].hasMine = true;
		mines.push_back({ x1, y1 });
	}
	
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{	
			field[x][y].state = CLOSED;
			field[x][y].mineAround = 0;
			if (!field[x][y].hasMine)
			{

				for (int y1 = y - 1; y1 <= y + 1; y1++)
				{
					for (int x1 = x - 1; x1 <= x + 1; x1++)
					{
						if ((x1 == x && y1 == y) || x1 < 0 || x1 >= Width || y1 < 0 || y1 >= Height) continue;

						if (field[x1][y1].hasMine)
						{
							field[x][y].mineAround++;
						}
					}
				}
			}
		}
	}
}

void Game::draw(float sec)
{
	static int xx = -1, yy = -1;
	Printer p;
	bool flag;
	static int prevTime = 0;
	std::string second = "0.00";
	
	std::string str = std::to_string(numOfMines - showFlags());
	p.drawRestButton();
	p.drawMineLeft(str);
	if (!gameState())
	{	
		if (sec != 0)
		{
			double t = sec / 1000;
			second = std::to_string(t);
			
		}
		p.drawTimer(second);
		prevTime = sec;
	}
	else
	{	
		float t = prevTime / 1000;
		second = std::to_string(t);
		p.drawTimer(second);
	}

	do {
		flag = false;
		for (int y = 0; y < Height; y++)
		{
			for (int x = 0; x < Width; x++)
			{
				switch (field[x][y].state)
				{
				case CLOSED:
					p.drawClosedField(x, y);
					break;

				case OPENED:
					if (!field[x][y].hasMine)
					{
						p.drawOpenedField(x, y, field[x][y].mineAround);
						if (field[x][y].mineAround == 0)
						{
							for (int y2 = y - 1; y2 <= y + 1; y2++)
							{
								for (int x2 = x - 1; x2 <= x + 1; x2++)
								{
									if ((x2 == x && y2 == y) || x2 < 0 || x2 >= Width || y2 < 0 || y2 >= Height || field[x2][y2].state != CLOSED) continue;

									field[x2][y2].state = OPENED;
									p.drawOpenedField(x2, y2, field[x2][y2].mineAround);
									if (x2 < x || y2 < y) flag = true;
								}
							}
						}
					}
					else
					{
						if (!mineOpen)
						{
							mineOpen = true;
							std::cout << '\a'<< std::endl;
							p.drawTargetMine(x, y);
							xx = x, yy = y;
							for (std::vector<int> v : mines)
							{
								int x0 = v[0], y0 = v[1];
								if ((x0 == x && y0 == y) || field[x0][y0].state == FLAG) continue;
								open(x0, y0);
								p.drawMine(x0, y0);
								flag = true;
							}
						}
						else
						{
							if (x == xx && y == yy) p.drawTargetMine(x, y);

							else p.drawMine(x, y);
						}
					}
					break;

				case FLAG:
					if (mineOpen && !field[x][y].hasMine)
						p.drawBadFlag(x, y);
					else
						p.drawFlag(x, y);

					break;

				}
			}
		}
	} while (flag);
}

void Game::open(int x, int y)
{	
	if (field[x][y].state == FLAG)
		return;
	field[x][y].state = OPENED;
}

void Game::mark(int x, int y)
{
	switch (field[x][y].state)
	{
	case OPENED:
		break;

	case CLOSED:
		field[x][y].state = FLAG;
		flags++;
		break;

	case FLAG:
		field[x][y].state = CLOSED;
		flags--;
		break;

	}
}

bool Game::gameState()
{
	return (mineOpen || checkMatch());
}

int Game::showFlags()
{
	return flags;
}

bool Game::checkMatch()
{	
	if (mineOpen) return false;
	int count = 0;
	for (int x = 0; x < Width; x++)
	{
		for (int y = 0; y < Height; y++)
		{
			if (field[x][y].state == FLAG && field[x][y].hasMine)
				count++;
		}
		if (count == mines.size()) return true;

	}
	return false;
}
