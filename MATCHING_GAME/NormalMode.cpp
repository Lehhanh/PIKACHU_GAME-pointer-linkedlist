#include "NormalMode.h"


void NormalMode(int playerPos)
{
	PLAYER* player;
	int nP;
	State cur;
	cur.board = NULL;
	cur.mode = 1;

	readAllPlayerInfo(player, nP);
	system("cls");
	if (isEmptyBoard(player[playerPos].normalMode.board, player[playerPos].normalMode.m, player[playerPos].normalMode.n)
		|| player[playerPos].normalMode.game.life == 0) {
		srand(time(0));
		initBoard_1(cur.board, cur.m, cur.n, cur.occur);
		cur.game.playTime = time(0);
		system("cls");
	}
	else {
		//cout << "Do you want to continue previous game?" << endl;
		int choice = 1;
		bool check = 0;
		drawBoxPreviousGame();
		drawButton_3(choice);
		while (!check)
		{
			if (_kbhit())
			{
				char temp = _getch();
				if (temp == -32)
				{
					temp = _getch();
					if (temp == LEFT || temp == RIGHT)
					{
						if (choice == 1)
							choice = 0;
						else
							choice = 1;
						drawButton_3(choice);
					}
				}
				else if (temp == ENTER)
				{
					check = 1;
				}
			}
		}
		system("cls");
		if (choice == 1) {
			copyGame(player[playerPos].normalMode, cur);
		}
		else if (choice == 0) {
			srand(time(0));
			initBoard_1(cur.board, cur.m, cur.n, cur.occur);
			cur.game.playTime = time(0);
			system("cls");
		}
	}

	point curr = { 1,1 };//con tro chuot dang tai o dau tien
	point Prevcurr = { -1, -1 };
	int status = 0; // 0 - IS PLAYING
	// 1 - WIN OR LOSE 
	// 2 - EXIT
	point posSelected[2] = { {-1,-1}, {-1,-1} }; //toa do hai diem da chon
	int cnt_pos = 0; //dem so o da chon
	bool check = 0; //KIEM TRA NGUOI DUNG CO NHAP GI VAO KHONG
	point key[2] = { {-1, -1} , {-1, -1} };
	bool help = 0;
	char bg[16][40];

	for (int i = 0; i < cur.m; i++) {
		for (int j = 0; j < cur.n; j++) {
			if (cur.board[i][j].isCurr == 1) {
				curr.y = i;
				curr.x = j;
			}
		}
	}

	drawBG(bg);
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			if (i < cur.m - 1 && j < cur.n - 1)
			{
				if (cur.board[i][j].c == ' ')
					displayBG(bg, j, i);
			}
		}
	}
	displayBoard_1(cur.board, cur.m, cur.n);
	drawBorder(cur.m, cur.n);
	drawBoxPlayer(cur.n * 8 + 10, 5);

	goToXY(cur.n * 8 + 10 + 3 + 6, 5 + 3);
	cout << player[playerPos].name;
	goToXY(cur.n * 8 + 10 + 3 + 7, 5 + 4);
	cout << cur.game.score;
	goToXY(cur.n * 8 + 10 + 3 + 6, 5 + 5);
	cout << cur.game.life;
	goToXY(cur.n * 8 + 10 + 3 + 17, 5 + 6);
	cout << cur.game.nLifeline;

	while (!status)
	{
		if (check)
		{
			displayBoard_1(cur.board, cur.m, cur.n);
			check = 0;
		}
		bool CheckValidMatrix = checkValidMatrix(cur.board, cur.m, cur.n, key[0], key[1], cur.occur);
		if (!CheckValidMatrix)
		{
			renewMatrix(cur.board, cur.m, cur.n, cur.occur);
			check = 1;
		}
		if (_kbhit())
		{
			move_1(cur.board, cur.m, cur.n, curr, Prevcurr, posSelected, cnt_pos, status, help);
			if (status == 2) {
				exitPlayingMode(player, nP, playerPos, cur);
				system("cls");
			}
			if (cnt_pos == 2)
			{
				bool matched = check_draw(cur.board, cur.m, cur.n, curr, posSelected[0], posSelected[1], cur.occur, bg);
				cnt_pos = 0;

				if (matched) {
					cur.game.score += 10;
					goToXY(cur.n * 8 + 10 + 3 + 7, 5 + 4);
					cout << "         ";
					goToXY(cur.n * 8 + 10 + 3 + 7, 5 + 4);
					cout << cur.game.score;
					playSound(MATCHED);
				}
				else {
					cur.game.score -= 5;
					cur.game.life--;
					goToXY(cur.n * 8 + 10 + 3 + 7, 5 + 4);
					cout << "         ";
					goToXY(cur.n * 8 + 10 + 3 + 7, 5 + 4);
					cout << cur.game.score;
					goToXY(cur.n * 8 + 10 + 3 + 6, 5 + 5);
					cout << "         ";
					goToXY(cur.n * 8 + 10 + 3 + 6, 5 + 5);
					cout << cur.game.life;
					playSound(WRONG);
				}
				gameFinishVerify(cur, player, nP, playerPos, status);
			}
		}
		if (help)
		{
			moveSuggestion(cur.board, key[0], key[1], cur.game.nLifeline);
			goToXY(cur.n * 8 + 10 + 3 + 17, 5 + 6);
			cout << cur.game.nLifeline;
			help = 0;
		}
	}
	system("cls");
}

