#include "Graphic.h"

void drawBorder(int m, int n)
{
	TextColor(14);
	for (int i = 8;i <= (n - 1) * 8;i++)
	{
		goToXY(i, 3);
		cout << char(205);
		goToXY(i, (m - 1) * 4 + 1);
		cout << char(205);
	}
	for (int i = 4;i <= (m - 1) * 4;i++)
	{
		goToXY(7, i);
		cout << char(186);
		goToXY((n - 1) * 8 + 1, i);
		cout << char(186);
	}
	goToXY(7, 3);
	cout << char(201);
	goToXY(7, (m - 1) * 4 + 1);
	cout << char(200);
	goToXY((n - 1) * 8 + 1, 3);
	cout << char(187);
	goToXY((n - 1) * 8 + 1, (m - 1) * 4 + 1);
	cout << char(188);
	TextColor(7);
}


void drawBoxPlayer(int x, int y)
{
	TextColor(12);
	for (int i = x; i <= x + 30;i++)
	{
		goToXY(i, y);
		cout << char(205);
		goToXY(i, y + 7);
		cout << char(205);
		goToXY(i, y + 2);
		cout << char(205);
	}
	for (int i = y; i < y + 7;i++)
	{
		goToXY(x, i);
		cout << char(186);
		goToXY(x + 30, i);
		cout << char(186);
	}
	goToXY(x, y);
	cout << char(201);
	goToXY(x, y + 7);
	cout << char(200);
	goToXY(x + 30, y);
	cout << char(187);
	goToXY(x + 30, y + 7);
	cout << char(188);
	TextColor(7);
	goToXY(x + 5, y + 1);
	cout << "PLAYER'S INFORMATION";
	goToXY(x + 3, y + 3);
	cout << "Name:";
	goToXY(x + 3, y + 4);
	cout << "Score:";
	goToXY(x + 3, y + 5);
	cout << "Life:";
	goToXY(x + 3, y + 6);
	cout << "Move suggestion:";

	TextColor(10);
	goToXY(x + 2, y + 10);
	cout << "PRESS ARROW KEY TO MOVE";
	goToXY(x + 2, y + 11);
	cout << "PRESS ENTER TO SELECT CELL";
	goToXY(x + 2, y + 12);
	cout << "PRESS ESC TO EXIT";
	goToXY(x + 2, y + 13);
	cout << "PRESS M TO GET MOVE SUGGESTION";
	TextColor(7);
}


void drawBG(char bg[16][40])
{
	ifstream file;
	file.open("background.txt");
	for (int i = 0; i < 16;i++)
	{
		for (int j = 0;j < 40;j++)
		{
			bg[i][j] = file.get();
		}
		file.ignore();
	}
	file.close();
}

void displayBG(char bg[16][40], int x, int y)
{
	TextColor(11);
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0; j < 8;j++)
		{
			goToXY(x * 8 + j, y * 4 + i);
			cout << bg[(y - 1) * 4 + i][(x - 1) * 8 + j];
		}
	}
	TextColor(7);
}


void drawTitle()
{
	TextColor(14);
	goToXY(10, 2);
	cout << " ______    __   __  ___      ___       ______  __    __   __    __";
	goToXY(10, 3);
	cout << "|   _  \\  |  | |  |/  /     /   \\     /      ||  |  |  | |  |  |  |";
	goToXY(10, 4);
	cout << "|  |_)  | |  | |  '  /     /  ^  \\   |  ,----'|  |__|  | |  |  |  |";
	goToXY(10, 5);
	cout << "|   ___/  |  | |    <     /  /_\\  \\  |  |     |   __   | |  |  |  |";
	goToXY(10, 6);
	cout << "|  |      |  | |  .  \\   /  _____  \\ |  `----.|  |  |  | |  `--'  |";
	goToXY(10, 7);
	cout << "|__|      |__| |__|\\__\\ /__/     \\__\\ \\______||__|  |__|  \\______/";


	TextColor(11);
	goToXY(20, 10);
	cout << "  _______      ___       ___    ___  _______";
	goToXY(20, 11);
	cout << " /  _____|    /   \\     |    \\/    ||   ____|";
	goToXY(20, 12);
	cout << "|  '   __    /  ^  \\    |  |\\  /|  ||  |___";
	goToXY(20, 13);
	cout << "|  |  |  |  /  /_\\  \\   |  | \\/ |  ||   ___|";
	goToXY(20, 14);
	cout << "|  `__|  | /  _____  \\  |  |    |  ||  |____";
	goToXY(20, 15);
	cout << " \\______/ /__/     \\__\\ |__|    |__||_______|";
	TextColor(7);
}

void drawPikachu()
{
	TextColor(6);
	ifstream file;
	file.open("PIKACHU.txt", ios::in);
	int pos = 2;
	while (!file.eof())
	{
		string s;
		getline(file, s);
		goToXY(80, pos);
		cout << s << endl;
		pos++;
	}
	file.close();
	TextColor(7);
}

void drawLoadingBar()
{
	TextColor(160);
	for (int i = 0;i < 50;i++)
	{
		goToXY(15 + i, 20);
		cout << " ";
		goToXY(15 + 1, 20);
		cout << (i + 1) * 2 << "%";
		Sleep(70);
	}
	TextColor(7);
}


void intro()
{
	drawPikachu();
	drawTitle();
	drawLoadingBar();
}

void drawHowtoPlayBox()
{
	TextColor(6);
	goToXY(25, 1);
	cout << "--------------------WELCOME TO OUR MATCHING GAME!--------------------";
	TextColor(7);
	for (int i = 0;i <= 115;i++)
	{
		goToXY(i, 2);
		cout << char(205);
		goToXY(i, 6);
		cout << char(205);
		goToXY(i, 21);
		cout << char(205);
		goToXY(i, 26);
		cout << char(205);
		goToXY(i, 30);
		cout << char(205);
	}
	for (int i = 3;i < 30;i++)
	{
		goToXY(0, i);
		cout << char(186);
		goToXY(115, i);
		cout << char(186);
		goToXY(15, i);
		cout << char(186);
	}
	TextColor(11);
	goToXY(6, 4);
	cout << "MOVE";

	TextColor(9);
	goToXY(5, 12);
	cout << "NORMAl";
	goToXY(6, 13);
	cout << "MODE";

	TextColor(10);
	goToXY(3, 23);
	cout << "DIFFICULT";
	goToXY(6, 24);
	cout << "MODE";


	TextColor(13);
	goToXY(5, 28);
	cout << "SCORE";

	TextColor(7);
	goToXY(20, 3);
	cout << "Up: Up arrow                  Down: Down arrow";
	goToXY(20, 5);
	cout << "Left: Left arrow              Right: Right arrow";
	goToXY(20, 7);
	cout << "+ Our Matching Game, just like the original Matching Game (commonly known as Pikachu Puzzle";
	goToXY(17, 8);
	cout << "Game), includes a board of multiple cells, each of which represents a letter. The players are";
	goToXY(17, 9);
	cout << "allowed to choose the size for the board(the number of cells must be even).";
	goToXY(20, 11);
	cout << "+ The goal of players is to find and pick 2 cells that contain the same letter and are able";
	goToXY(17, 12);
	cout << "to connect to each other in a particular pattern(I, Z, L, U) as fast as possible.";
	goToXY(20, 14);
	cout << "+ If the matching is legal, the two selected cells will disapear and you will earn 10 points.";
	goToXY(17, 15);
	cout << "However, if the matching is wrong, you will get 5 points minus. ";
	goToXY(20, 17);
	cout << "+ Each player has 3 chances of connecting wrong and 2 move suggestions.";
	goToXY(20, 19);
	cout << "+ The player win the game when all the cells have disappeared and lose when there is no ";
	goToXY(17, 20);
	cout << "chance of connecting wrong left.";
	goToXY(20, 22);
	cout << "+ The rule of Difficult Mode is basically similar to the rule of Normal Mode.";
	goToXY(20, 24);
	cout << "+ The only difference is that after the cells are matched, the neighboring";
	goToXY(17, 25);
	cout << "cells will slide into the newly emptied spaces from right to left.";
	goToXY(20, 27);
	cout << "+ Each stage: You have 3 life and 2 move suggestion";
	goToXY(20, 29);
	cout << "Matched: +10 point         Not Matched: -1 life";
	goToXY(0, 2);
	cout << char(201);
	goToXY(0, 30);
	cout << char(200);
	goToXY(115, 2);
	cout << char(187);
	goToXY(115, 30);
	cout << char(188);
	goToXY(18, 31);

	TextColor(12);
	cout << "------------------------------PRESS ESC TO EXIT------------------------------";
}

void HowToPlay()
{
	drawHowtoPlayBox();
	while (1)
	{
		if (_kbhit())
		{
			char temp = _getch();
			if (temp == 27)
			{
				break;
			}
		}
	}
}

void title_Leaderboard()
{
	TextColor(11);
	goToXY(30, 0);
	cout << "    __    _________    ____  __________  ____  ____  ___    ____  ____ ";
	goToXY(30, 1);
	cout << "   / /   / ____/   |  / __ \\/ ____/ __ \\/ __ )/ __ \\/   |  / __ \\/ __ \\";
	goToXY(30, 2);
	cout << "  / /   / __/ / /| | / / / / __/ / /_/ / __  / / / / /| | / /_/ / / / /";
	goToXY(30, 3);
	cout << " / /___/ /___/ ___ |/ /_/ / /___/ _, _/ /_/ / /_/ / ___ |/ _, _/ /_/ / ";
	goToXY(30, 4);
	cout << "/_____/_____/_/  |_/_____/_____/_/ |_/_____/\\____/_/  |_/_/ |_/_____/  ";
	TextColor(7);
}


void drawLeaderBoard(int mode, PLAYER* player)
{
	int x = 30;
	int y = 7;
	if (mode == 2)
	{
		TextColor(9);
		x = 30;
		y = 20;
		goToXY(x + 10, y);
		cout << "  _  ___  _  _ ___  _       ___         _   _   _";
		goToXY(x + 10, y + 1);
		cout << " | \\  |  |_ |_  |  /  | | |  |    |\\/| / \\ | \\ |_";
		goToXY(x + 10, y + 2);
		cout << " |_/ _|_ |  |  _|_ \\_ |_| |_ |    |  | \\_/ |_/ |_";
		TextColor(7);
		for (int i = 0;i < 5;i++)
		{
			goToXY(x + 5, y + 6 + i);
			cout << i + 1;
			goToXY(x + 15, y + 6 + i);
			cout << player[i].name;
			goToXY(x + 47, y + 6 + i);
			cout << player[i].diffRec.score;
			goToXY(x + 62, y + 6 + i);
			cout << player[i].diffRec.playTime;
		}
	}
	else
	{
		TextColor(10);
		goToXY(x + 12, y);
		cout << "       _   _                       _   _   _";
		goToXY(x + 12, y + 1);
		cout << " |\\ | / \\ |_) |\\/|  /\\  |    |\\/| / \\ | \\ |_";
		goToXY(x + 12, y + 2);
		cout << " | \\| \\_/ | \\ |  | /--\\ |_   |  | \\_/ |_/ |_";
		TextColor(7);
		for (int i = 0;i < 5;i++)
		{
			goToXY(x + 5, y + 6 + i);
			cout << i + 1;
			goToXY(x + 15, y + 6 + i);
			cout << player[i].name;
			goToXY(x + 47, y + 6 + i);
			cout << player[i].norRec.score;
			goToXY(x + 62, y + 6 + i);
			cout << player[i].norRec.playTime;
		}
	}

	TextColor(14);
	for (int i = x;i < x + 70;i++)
	{
		goToXY(i, y + 3);
		cout << char(205);
		goToXY(i, y + 5);
		cout << char(205);
		goToXY(i, y + 11);
		cout << char(205);
	}
	for (int i = y + 4;i < y + 11;i++)
	{
		goToXY(x, i);
		cout << char(186);
		goToXY(x + 70, i);
		cout << char(186);
		goToXY(x + 10, i);
		cout << char(186);
		goToXY(x + 40, i);
		cout << char(186);
		goToXY(x + 56, i);
		cout << char(186);
	}
	goToXY(x, y + 3);
	cout << char(201);
	goToXY(x + 70, y + 3);
	cout << char(187);
	goToXY(x, y + 11);
	cout << char(200);
	goToXY(x + 70, y + 11);
	cout << char(188);

	goToXY(x + 3, y + 4);
	cout << "RANK";
	goToXY(x + 19, y + 4);
	cout << "PLAYER'S NAME";
	goToXY(x + 46, y + 4);
	cout << "SCORE";
	goToXY(x + 61, y + 4);
	cout << "TIME";
	

	TextColor(7);
}
void drawButton(int choice)
{
	int x = 30;
	int y = 10;
	if (choice == 1)
	{
		TextColor(176);
		goToXY(x + 10, y + 6);
		cout << "            ";
		goToXY(x + 10, y + 7);
		cout << "   LOG IN   ";
		goToXY(x + 10, y + 8);
		cout << "            ";
		TextColor(7);


		for (int i = 0;i < 12;i++)
		{
			goToXY(x + 28 + i, y + 6);
			cout << char(196);
			goToXY(x + 28 + i, y + 8);
			cout << char(196);
		}
		goToXY(x + 28, y + 7);
		cout << "  REGISTER  ";
		goToXY(x + 28, y + 7);
		cout << char(179);
		goToXY(x + 39, y + 7);
		cout << char(179);

		goToXY(x + 28, y + 6);
		cout << char(218);
		goToXY(x + 39, y + 6);
		cout << char(191);
		goToXY(x + 28, y + 8);
		cout << char(192);
		goToXY(x + 39, y + 8);
		cout << char(217);
	}
	else
	{
		for (int i = 0;i < 12;i++)
		{
			goToXY(x + 10 + i, y + 6);
			cout << char(196);
			goToXY(x + 10 + i, y + 8);
			cout << char(196);
		}
		goToXY(x + 10, y + 7);
		cout << "   LOG IN   ";
		goToXY(x + 10, y + 7);
		cout << char(179);
		goToXY(x + 21, y + 7);
		cout << char(179);

		goToXY(x + 10, y + 6);
		cout << char(218);
		goToXY(x + 21, y + 6);
		cout << char(191);
		goToXY(x + 10, y + 8);
		cout << char(192);
		goToXY(x + 21, y + 8);
		cout << char(217);


		TextColor(176);
		goToXY(x + 28, y + 6);
		cout << "            ";
		goToXY(x + 28, y + 7);
		cout << "  REGISTER  ";
		goToXY(x + 28, y + 8);
		cout << "            ";
		TextColor(7);
	}
	
}

void drawBoxLogorRegis()
{
	int x = 30;
	int y = 10;
	TextColor(10);
	for (int i = x;i < x + 50;i++)
	{
		goToXY(i, y);
		cout << char(205);
		goToXY(i, y + 10);
		cout << char(205);
	}
	for (int i = y + 1;i < y + 10;i++)
	{
		goToXY(x, i);
		cout << char(186);
		goToXY(x + 50, i);
		cout << char(186);
	}
	goToXY(x, y);
	cout << char(201);
	goToXY(x + 50, y);
	cout << char(187);
	goToXY(x, y + 10);
	cout << char(200);
	goToXY(x + 50, y + 10);
	cout << char(188);

	TextColor(14);
	goToXY(x + 9, y + 1);
	cout << "Log in your account to play game.";
	goToXY(x + 10, y + 3);
	cout << "If you do not have an account,";
	goToXY(x + 7, y + 4);
	cout << "please create an account for the game";

	TextColor(7);
}

void drawEndGame(int result, State curr)
{
	int x = 50;
	int y = 10;

	if (result == 1)
	{
		goToXY(x, y);
		cout << " __        __ ___  _   _";
		goToXY(x, y + 1);
		cout << " \\ \\      / /|_ _|| \\ | |";
		goToXY(x, y + 2);
		cout << "  \\ \\ /\\ / /  | | |  \\| |";
		goToXY(x, y + 3);
		cout << "   \\ V  V /   | | | |\\  |";
		goToXY(x, y + 4);
		cout << "    \\_/\\_/   |___||_| \\_|";
	}
	else
	{
		goToXY(x, y);
		cout << "  _      ___   ____   _____";
		goToXY(x, y + 1);
		cout << " | |    / _ \\ / ___| | ____|";
		goToXY(x, y + 2);
		cout << " | |   | | | |\\___ \\ |  _| ";
		goToXY(x, y + 3);
		cout << " | |___| |_| | ___) || |___";
		goToXY(x, y + 4);
		cout << " |_____|\\___/ |____/ |_____|";
	}
	goToXY(x, y + 7);
	cout << "****************************";
	goToXY(x + 3, y + 9);
	cout << "SCORE:";
	goToXY(x + 12, y + 9);
	cout << curr.game.score;
	goToXY(x + 3, y + 11);
	cout << "TIME:";
	goToXY(x + 12, y + 11);
	cout << curr.game.playTime;
	goToXY(x, y + 13);
	cout << "****************************";
}

void drawButton_2(int choice)
{
	int x = 50;
	int y = 25;
	if (choice == 1)
	{
		TextColor(176);
		goToXY(x + 5, y + 3);
		cout << "        ";
		goToXY(x + 5, y + 4);
		cout << "  YES   ";
		goToXY(x + 5, y + 5);
		cout << "        ";


		TextColor(7);
		for (int i = 0;i < 7;i++)
		{
			goToXY(x + 18 + i, y + 3);
			cout << char(196);
			goToXY(x + 18 + i, y + 5);
			cout << char(196);
		}
		goToXY(x + 18, y + 4);
		cout << "   NO   ";
		goToXY(x + 18, y + 4);
		cout << char(179);
		goToXY(x + 25, y + 4);
		cout << char(179);


		goToXY(x + 18, y + 3);
		cout << char(218);
		goToXY(x + 25, y + 3);
		cout << char(191);
		goToXY(x + 18, y + 5);
		cout << char(192);
		goToXY(x + 25, y + 5);
		cout << char(217);
	}
	else
	{
		TextColor(176);
		goToXY(x + 18, y + 3);
		cout << "        ";
		goToXY(x + 18, y + 4);
		cout << "   NO   ";
		goToXY(x + 18, y + 5);
		cout << "        ";


		TextColor(7);
		for (int i = 0;i < 7;i++)
		{
			goToXY(x + 5 + i, y + 3);
			cout << char(196);
			goToXY(x + 5 + i, y + 5);
			cout << char(196);
		}
		goToXY(x + 5, y + 4);
		cout << "  YES  ";
		goToXY(x + 5, y + 4);
		cout << char(179);
		goToXY(x + 12, y + 4);
		cout << char(179);


		goToXY(x + 5, y + 3);
		cout << char(218);
		goToXY(x + 12, y + 3);
		cout << char(191);
		goToXY(x + 5, y + 5);
		cout << char(192);
		goToXY(x + 12, y + 5);
		cout << char(217);
	}

}

void drawButton_3(int choice)
{
	int x = 55;
	int y = 10;
	if (choice == 1)
	{
		TextColor(176);
		goToXY(x + 5, y + 3);
		cout << "        ";
		goToXY(x + 5, y + 4);
		cout << "  YES   ";
		goToXY(x + 5, y + 5);
		cout << "        ";


		TextColor(7);
		for (int i = 0;i < 7;i++)
		{
			goToXY(x + 18 + i, y + 3);
			cout << char(196);
			goToXY(x + 18 + i, y + 5);
			cout << char(196);
		}
		goToXY(x + 18, y + 4);
		cout << "   NO   ";
		goToXY(x + 18, y + 4);
		cout << char(179);
		goToXY(x + 25, y + 4);
		cout << char(179);


		goToXY(x + 18, y + 3);
		cout << char(218);
		goToXY(x + 25, y + 3);
		cout << char(191);
		goToXY(x + 18, y + 5);
		cout << char(192);
		goToXY(x + 25, y + 5);
		cout << char(217);
	}
	else
	{
		TextColor(176);
		goToXY(x + 18, y + 3);
		cout << "        ";
		goToXY(x + 18, y + 4);
		cout << "   NO   ";
		goToXY(x + 18, y + 5);
		cout << "        ";


		TextColor(7);
		for (int i = 0;i < 7;i++)
		{
			goToXY(x + 5 + i, y + 3);
			cout << char(196);
			goToXY(x + 5 + i, y + 5);
			cout << char(196);
		}
		goToXY(x + 5, y + 4);
		cout << "  YES  ";
		goToXY(x + 5, y + 4);
		cout << char(179);
		goToXY(x + 12, y + 4);
		cout << char(179);


		goToXY(x + 5, y + 3);
		cout << char(218);
		goToXY(x + 12, y + 3);
		cout << char(191);
		goToXY(x + 5, y + 5);
		cout << char(192);
		goToXY(x + 12, y + 5);
		cout << char(217);
	}

}

void drawBoxContinueGame()
{
	int x = 50;
	int y = 25;
	TextColor(10);
	for (int i = x;i < x + 30;i++)
	{
		goToXY(i, y);
		cout << char(205);
		goToXY(i, y + 7);
		cout << char(205);
	}
	for (int i = y + 1;i < y + 7;i++)
	{
		goToXY(x, i);
		cout << char(186);
		goToXY(x + 30, i);
		cout << char(186);
	}
	goToXY(x, y);
	cout << char(201);
	goToXY(x + 30, y);
	cout << char(187);
	goToXY(x, y + 7);
	cout << char(200);
	goToXY(x + 30, y + 7);
	cout << char(188);

	TextColor(14);
	goToXY(x + 2, y + 1);
	cout << "Do you want to play again?";

	TextColor(7);
}

void drawBoxPreviousGame()
{
	int x = 50;
	int y = 10;
	TextColor(10);
	for (int i = x;i < x + 40;i++)
	{
		goToXY(i, y);
		cout << char(205);
		goToXY(i, y + 7);
		cout << char(205);
	}
	for (int i = y + 1;i < y + 7;i++)
	{
		goToXY(x, i);
		cout << char(186);
		goToXY(x + 40, i);
		cout << char(186);
	}
	goToXY(x, y);
	cout << char(201);
	goToXY(x + 40, y);
	cout << char(187);
	goToXY(x, y + 7);
	cout << char(200);
	goToXY(x + 40, y + 7);
	cout << char(188);

	TextColor(14);
	goToXY(x + 4, y + 1);
	cout << "Do you want to play previous game?";

	TextColor(7);
}