#include <iostream>
#include "Menu.h"
#include "NormalMode.h"
#include "DifficultMode.h"
#include "Login.h"
#include "Leaderboard.h"

using namespace std;

int main()
{
	playSound(BACKGROUND);
	resizeWindow(1000, 500);
	setCursor(0);
	intro();
	system("cls");
	int status;
	int playerPos;



	LogOrRegis(playerPos);
	while ((status = statusMenu()) != 4)
	{
		system("cls");
		switch (status)
		{
		case 0:
			NormalMode(playerPos);
			system("cls");
			break;
		case 1:
			DifficultMode(playerPos);
			system("cls");
			break;
		case 2:
			printLeaderboard();
			system("cls");
			break;
		case 3:
			HowToPlay();
			system("cls");
			break;
		default:
			break;
		}
	}

	system("cls");
	return 0;
}