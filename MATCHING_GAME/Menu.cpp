#include "Menu.h"
using namespace std;

void drawTitleMenu()
{
	int x = 32;
	int y = 0;
	TextColor(14);
	goToXY(x, y);
	cout << " /$$$$$$$  /$$$$$$ /$$   /$$  /$$$$$$   /$$$$$$  /$$   /$$ /$$   /$$";
	goToXY(x, y + 1);
	cout << "| $$__  $$|_  $$_/| $$  /$$/ /$$__  $$ /$$__  $$| $$  | $$| $$  | $$";
	goToXY(x, y + 2);
	cout << "| $$  \\ $$  | $$  | $$ /$$/ | $$  \\ $$| $$  \\__/| $$  | $$| $$  | $$";
	goToXY(x, y + 3);
	cout << "| $$$$$$$/  | $$  | $$$$$/  | $$$$$$$$| $$      | $$$$$$$$| $$  | $$";
	goToXY(x, y + 4);
	cout << "| $$____/   | $$  | $$  $$  | $$__  $$| $$      | $$__  $$| $$  | $$";
	goToXY(x, y + 5);
	cout << "| $$        | $$  | $$\\  $$ | $$  | $$| $$    $$| $$  | $$| $$  | $$";
	goToXY(x, y + 6);
	cout << "| $$       /$$$$$$| $$ \\  $$| $$  | $$|  $$$$$$/| $$  | $$|  $$$$$$/";
	goToXY(x, y + 7);
	cout << "|__/      |______/|__/  \\__/|__/  |__/ \\______/ |__/  |__/ \\______/";
	TextColor(7);
}


void drawBox(int y)
{
	for (int i = 0;i < 3;i++)
	{
		goToXY(MenuX, MenuY + (y * 3) + i);
		cout << "                    ";
	}
	if (y == 0)
	{
		TextColor(9);//xanh duong
		goToXY(MenuX + 4, MenuY + 1);
		cout << "NORMAL MODE";
	}
	else if (y == 1)
	{
		TextColor(10); //xanh luc
		goToXY(MenuX + 3, MenuY + (y * 3) + 1);
		cout << "DIFFICULT MODE";
	}
	else if (y == 2)
	{
		TextColor(11);//xanh da troi
		goToXY(MenuX + 4, MenuY + (y * 3) + 1);
		cout << "LEADERBOARD";
	}
	else if (y == 3)
	{
		TextColor(14);//vang
		goToXY(MenuX + 4, MenuY + (y * 3) + 1);
		cout << "HOW TO PLAY";
	}
	else if (y == 4)
	{
		TextColor(12); //do
		goToXY(MenuX + 8, MenuY + (y * 3) + 1);
		cout << "EXIT";
	}
	TextColor(7);
}
void drawCurrBox(int y)
{
	if (y == 0)
	{
		TextColor(144);
		for (int i = 0;i < 3;i++)
		{
			goToXY(MenuX, MenuY + (y * 3) + i);
			cout << "                    ";
		}
		goToXY(MenuX + 4, MenuY + 1);
		cout << "NORMAL MODE";
	}
	else if (y == 1)
	{
		TextColor(160);
		for (int i = 0;i < 3;i++)
		{
			goToXY(MenuX, MenuY + (y * 3) + i);
			cout << "                    ";
		}
		goToXY(MenuX + 3, MenuY + (y * 3) + 1);
		cout << "DIFFICULT MODE";
	}
	else if (y == 2)
	{
		TextColor(176);
		for (int i = 0;i < 3;i++)
		{
			goToXY(MenuX, MenuY + (y * 3) + i);
			cout << "                    ";
		}
		goToXY(MenuX + 4, MenuY + (y * 3) + 1);
		cout << "LEADERBOARD";
	}
	else if (y == 3)
	{
		TextColor(224);
		for (int i = 0;i < 3;i++)
		{
			goToXY(MenuX, MenuY + (y * 3) + i);
			cout << "                    ";
		}
		goToXY(MenuX + 4, MenuY + (y * 3) + 1);
		cout << "HOW TO PLAY";
	}
	else if (y == 4)
	{
		TextColor(192);
		for (int i = 0;i < 3;i++)
		{
			goToXY(MenuX, MenuY + (y * 3) + i);
			cout << "                    ";
		}
		goToXY(MenuX + 8, MenuY + (y * 3) + 1);
		cout << "EXIT";
	}
	TextColor(7);
}


void moveMenu(int& curr, int& prev, int& statusMenu)
{
	char temp = _getch();
	if (temp == ENTER)
	{
		statusMenu = curr;
	}
	else if (temp == -32)
	{
		temp = _getch();
		prev = curr;
		if (temp == UP)
		{
			if (curr == 0)
				curr = 4;
			else
				curr = curr - 1;
		}
		else if (temp == DOWN)
		{
			if (curr == 4)
				curr = 0;
			else
				curr = curr + 1;
		}
	}
}







int statusMenu()
{
	drawTitleMenu();
	for (int i = 0;i < 5;i++)
	{
		drawBox(i);
	}
	int curr = 0;
	int prev = -1;
	drawCurrBox(curr);
	int statusMenu = -1;
	while (statusMenu == -1)
	{
		if (_kbhit)
		{
			moveMenu(curr, prev, statusMenu);
			drawBox(prev);
			drawCurrBox(curr);
		}
	}
	return statusMenu;
}