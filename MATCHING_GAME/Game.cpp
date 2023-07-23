#include"Game.h";
#include"Leaderboard.h"
#include"NormalMode.h"
#include"Check_Difficult.h"
#include"DifficultMode.h"

#pragma comment(lib,"winmm.lib")

// save board and mode after each time deleting
void copyGame(State source, State& des) {
	if (des.mode == NORMAL_MODE || source.mode == NORMAL_MODE) {
		// ALLOCATE BOARD
		des.board = new CELL * [source.m];
		for (int i = 0; i < source.m; i++)
		{
			des.board[i] = new CELL[source.n];
		}
		for (int i = 0; i < source.m; i++) {
			for (int j = 0; j < source.n; j++) {
				des.board[i][j].pos.y = source.board[i][j].pos.y;
				des.board[i][j].pos.x = source.board[i][j].pos.x;
				des.board[i][j].c = source.board[i][j].c;
				des.board[i][j].isCurr = source.board[i][j].isCurr;
				des.board[i][j].isSelected = 0;
			}
		}
	}
	else if (des.mode == DIFFICULT_MODE || source.mode == DIFFICULT_MODE) {
		//ALLOCATE ARRAY OF LINKED LIST
		des.list = new NODE * [source.m];
		for (int i = 0; i < source.m; i++) {
			des.list[i] = NULL;
			for (int j = 0; j < source.n; j++) {
				NODE* node = new NODE;
				node->pNext = NULL;
				node->pos.y = i;
				node->pos.x = j;
				addTail(des.list[i], node);
			}
		}

		for (int i = 0; i < source.m; i++) {
			NODE* temp1 = source.list[i];
			NODE* temp2 = des.list[i];
			while (temp1 && temp2){
				temp2->pos.y = temp1->pos.y;
				temp2->pos.x = temp1->pos.x;
				temp2->c = temp1->c;
				temp2->isCurr = temp1->isCurr;
				temp2->isSelected = 0;

				temp1 = temp1->pNext;
				temp2 = temp2->pNext;
			}
		}
	}

	des.m = source.m;
	des.n = source.n;

	// copy game
	des.game.life = source.game.life;
	des.game.score = source.game.score;
	des.game.playTime = time(0) - source.game.playTime;
	des.game.nLifeline = source.game.nLifeline;

	for (int i = 0; i < 26; i++) {
		des.occur[i] = source.occur[i];
	}
}

bool isEmptyBoard(CELL** board, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j].c != ' ') {
				return false;
			}
		}
	}

	return true;
}

bool isEmptyList(NODE** board, int m, int n) {
	for (int i = 0; i < m;  i++) {
		NODE* temp = board[i];
		while (temp != NULL) {
			if (temp->c != ' ') {
				return false;
			}
			temp = temp->pNext;
		}
	}
	return true;
}

void savePlayerInfo(PLAYER player) {
	ofstream ofs("players.dat", ios::app | ios::binary);
	ofs.write(player.name, 30);
	ofs.write(player.password, 7);

	ofs.write((char*)&player.normalMode.m, 4);
	ofs.write((char*)&player.normalMode.n, 4);
	for (int j = 0; j < player.normalMode.m; j++) {
		for (int k = 0; k < player.normalMode.n; k++) {
			ofs.write((char*)&j, 4);
			ofs.write((char*)&k, 4);
			ofs.write((char*)&player.normalMode.board[j][k].pos.y, 4);
			ofs.write((char*)&player.normalMode.board[j][k].pos.x, 4);
			ofs.write((char*)&player.normalMode.board[j][k].c, 1);
			ofs.write((char*)&player.normalMode.board[j][k].isCurr, 1);
			ofs.write((char*)&player.normalMode.board[j][k].isSelected, 1);

		}
	}
	char sth[5] = "";
	int remain1 = 64 * 19 - player.normalMode.m * player.normalMode.n * 19;
	ofs.write(sth, remain1);

	ofs.write((char*)&player.normalMode.game.life, 4);
	ofs.write((char*)&player.normalMode.game.score, 4);
	ofs.write((char*)&player.normalMode.game.playTime, 4);
	ofs.write((char*)&player.normalMode.game.nLifeline, 4);

	for (int i = 0; i < 26; i++) {
		ofs.write((char*)&player.normalMode.occur[i], 4);
	}

	ofs.write((char*)&player.diffMode.m, 4);
	ofs.write((char*)&player.diffMode.n, 4);
	for (int j = 0; j < player.diffMode.m; j++) {
		NODE* temp = player.diffMode.list[j];
		while (temp != NULL) {
			ofs.write((char*)&temp->pos.y, 4);
			ofs.write((char*)&temp->pos.x, 4);
			ofs.write((char*)&temp->c, 1);
			ofs.write((char*)&temp->isCurr, 1);
			ofs.write((char*)&temp->isSelected, 1);

			temp = temp->pNext;
		}
	}

	int remain2 = 64 * 11 - player.diffMode.m * player.diffMode.n * 11;
	ofs.write(sth, remain2);

	ofs.write((char*)&player.diffMode.game.life, 4);
	ofs.write((char*)&player.diffMode.game.score, 4);
	ofs.write((char*)&player.diffMode.game.playTime, 4);
	ofs.write((char*)&player.diffMode.game.nLifeline, 4);

	for (int i = 0; i < 26; i++) {
		ofs.write((char*)&player.diffMode.occur[i], 4);
	}

	ofs.close();
}

void saveAllPlayerInfo(PLAYER* player, int n) {
	ofstream ofs("players.dat", ios::binary);

	for (int q = 0; q < n; q++) {
		ofs.write(player[q].name, 30);
		ofs.write(player[q].password, 7);

		ofs.write((char*)&player[q].normalMode.m, 4);
		ofs.write((char*)&player[q].normalMode.n, 4);
		for (int j = 0; j < player[q].normalMode.m; j++) {
			for (int k = 0; k < player[q].normalMode.n; k++) {
				ofs.write((char*)&j, 4);
				ofs.write((char*)&k, 4);
				ofs.write((char*)&player[q].normalMode.board[j][k].pos.y, 4);
				ofs.write((char*)&player[q].normalMode.board[j][k].pos.x, 4);
				ofs.write((char*)&player[q].normalMode.board[j][k].c, 1);
				ofs.write((char*)&player[q].normalMode.board[j][k].isCurr, 1);
				ofs.write((char*)&player[q].normalMode.board[j][k].isSelected, 1);

			}
		}
		char sth[5] = "";
		int remain1 = 64 * 19 - player[q].normalMode.m * player[q].normalMode.n * 19;
		ofs.write(sth, remain1);

		ofs.write((char*)&player[q].normalMode.game.life, 4);
		ofs.write((char*)&player[q].normalMode.game.score, 4);
		ofs.write((char*)&player[q].normalMode.game.playTime, 4);
		ofs.write((char*)&player[q].normalMode.game.nLifeline, 4);

		for (int i = 0; i < 26; i++) {
			ofs.write((char*)&player[q].normalMode.occur[i], 4);
		}

		ofs.write((char*)&player[q].diffMode.m, 4);
		ofs.write((char*)&player[q].diffMode.n, 4);
		for (int j = 0; j < player[q].diffMode.m; j++) {
			NODE* temp = player[q].diffMode.list[j];
			while (temp != NULL) {
				ofs.write((char*)&temp->pos.y, 4);
				ofs.write((char*)&temp->pos.x, 4);
				ofs.write((char*)&temp->c, 1);
				ofs.write((char*)&temp->isCurr, 1);
				ofs.write((char*)&temp->isSelected, 1);

				temp = temp->pNext;
			}
		}

		int remain2 = 64 * 11 - player[q].diffMode.m * player[q].diffMode.n * 11;
		ofs.write(sth, remain2);

		ofs.write((char*)&player[q].diffMode.game.life, 4);
		ofs.write((char*)&player[q].diffMode.game.score, 4);
		ofs.write((char*)&player[q].diffMode.game.playTime, 4);
		ofs.write((char*)&player[q].diffMode.game.nLifeline, 4);

		for (int i = 0; i < 26; i++) {
			ofs.write((char*)&player[q].diffMode.occur[i], 4);
		}
	}
	ofs.close();
}

void readAllPlayerInfo(PLAYER*& player, int& n) {
	ifstream ifs("players.dat", ios::binary);
	ifs.seekg(0, ios::end);
	n = ifs.tellg() / 2213;
	int right = ifs.tellg() % 2213;
	ifs.seekg(0, ios::beg);
	player = new PLAYER[n];

	for (int q = 0; q < n; q++){
		ifs.read(player[q].name, 30);
		ifs.read(player[q].password, 7);
		ifs.read((char*)&player[q].normalMode.m, 4);
		ifs.read((char*)&player[q].normalMode.n, 4);

		// ALLOCATE BOARD
		player[q].normalMode.board = new CELL * [player[q].normalMode.m];
		for (int i = 0; i < player[q].normalMode.m; i++)
		{
			player[q].normalMode.board[i] = new CELL[player[q].normalMode.n];
		}

		int a, b;
		for (int i = 0; i < player[q].normalMode.m; i++) {
			for (int j = 0; j < player[q].normalMode.n; j++) {
				ifs.read((char*)&a, 4);
				ifs.read((char*)&b, 4);
				ifs.read((char*)&player[q].normalMode.board[a][b].pos.y, 4);
				ifs.read((char*)&player[q].normalMode.board[a][b].pos.x, 4);
				ifs.read((char*)&player[q].normalMode.board[a][b].c, 1);
				ifs.read((char*)&player[q].normalMode.board[a][b].isCurr, 1);
				ifs.read((char*)&player[q].normalMode.board[a][b].isSelected, 1);

			}
		}
		//max size of board
		int remain = 64 * 19 - player[q].normalMode.m * player[q].normalMode.n * 19;
		char sth[5] = "";
		ifs.read(sth, remain);

		ifs.read((char*)&player[q].normalMode.game.life, 4);
		ifs.read((char*)&player[q].normalMode.game.score, 4);
		ifs.read((char*)&player[q].normalMode.game.playTime, 4);
		ifs.read((char*)&player[q].normalMode.game.nLifeline, 4);

		for (int i = 0; i < 26; i++) {
			ifs.read((char*)&player[q].normalMode.occur[i], 4);
		}

		ifs.read((char*)&player[q].diffMode.m, 4);
		ifs.read((char*)&player[q].diffMode.n, 4);

		NODE** head = new NODE * [player[q].diffMode.m];

		for (int i = 0; i < player[q].diffMode.m; i++) {
			head[i] = NULL;

			for (int j = 0; j < player[q].diffMode.n; j++) {
				NODE* node = new NODE;
				node->pNext = NULL;
				addTail(head[i], node);
			}
		}

		player[q].diffMode.list = head;

		for (int j = 0; j < player[q].diffMode.m; j++) {
			NODE* temp = player[q].diffMode.list[j];
			while (temp != NULL) {
				ifs.read((char*)&temp->pos.y, 4);
				ifs.read((char*)&temp->pos.x, 4);
				ifs.read((char*)&temp->c, 1);
				ifs.read((char*)&temp->isCurr, 1);
				ifs.read((char*)&temp->isSelected, 1);

				temp = temp->pNext;
			}
		}

		int remain2 = 64 * 11 - player[q].diffMode.m * player[q].diffMode.n * 11;
		ifs.read(sth, remain2);

		ifs.read((char*)&player[q].diffMode.game.life, 4);
		ifs.read((char*)&player[q].diffMode.game.score, 4);
		ifs.read((char*)&player[q].diffMode.game.playTime, 4);
		ifs.read((char*)&player[q].diffMode.game.nLifeline, 4);

		for (int i = 0; i < 26; i++) {
			ifs.read((char*)&player[q].diffMode.occur[i], 4);
		}
	}

	ifs.close();

}

void gameFinishVerify(State& current, PLAYER* player, int nP, int playerPos, int& status) {
	bool end = false;
	PLAYER* pLeaderboard = new PLAYER[6];
	int nL = 0;
	if (current.mode == NORMAL_MODE) {
		if (current.game.life == 0) {
			current.game.playTime = time(0) - current.game.playTime;
			copyGame(current, player[playerPos].normalMode);
			saveAllPlayerInfo(player, nP);
			system("cls");
			drawEndGame(0, current);
			end = true;
			playSound(LOSE);
		}
		else if (isEmptyBoard(current.board, current.m, current.n)) {
			current.game.playTime = time(0) - current.game.playTime;
			copyGame(current, player[playerPos].normalMode);
			saveAllPlayerInfo(player, nP);
			readLeaderBoard(NORMAL_MODE, pLeaderboard, nL);
			addAndSortLeaderboard(pLeaderboard, nL, player[playerPos], current);
			saveDataToLeaderboard(NORMAL_MODE, pLeaderboard, nL);
			system("cls");
			drawEndGame(1, current);
			end = true;
			deallocateBoard_1(current.board, current.m);
			playSound(WIN);
		}
	}
	else if (current.mode = DIFFICULT_MODE) {
		if (current.game.life == 0) {
			copyGame(current, player[playerPos].diffMode);
			saveAllPlayerInfo(player, nP);
			system("cls");
			drawEndGame(1, current);
			end = true;
			playSound(LOSE);
		}
		else if (isEmptyList(current.list, current.m, current.n)) {
			current.game.playTime = time(0) - current.game.playTime;
			copyGame(current, player[playerPos].diffMode);
			saveAllPlayerInfo(player, nP);
			readLeaderBoard(DIFFICULT_MODE, pLeaderboard, nL);
			addAndSortLeaderboard(pLeaderboard, nL, player[playerPos], current);
			saveDataToLeaderboard(DIFFICULT_MODE, pLeaderboard, nL);
			system("cls");
			drawEndGame(1, current);
			end = true;
			deallocateBoard_2(current.list, current.m);
			playSound(WIN);
		}
	}

	if (end) {
		int choice = 1;
		bool check = 0;
		drawBoxContinueGame();
		drawButton_2(choice);
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
						drawButton_2(choice);
					}
				}
				else if (temp == ENTER)
				{
					check = 1;
				}
			}
		}
		if (current.mode == NORMAL_MODE) {
			if (choice == 1) {
				system("cls");
				NormalMode(playerPos);
				status = 2;
			}
			else if (choice == 0) {
				status = 2;
			}
		}
		else if (current.mode == DIFFICULT_MODE) {
			if (choice == 1) {
				system("cls");
				DifficultMode(playerPos);
				status = 2;
			}
			else if (choice == 0) {
				status = 2;
			}
		}
	}
}

void exitPlayingMode(PLAYER*& player, int nP, int playerPos, State& current) {
	if (current.mode == NORMAL_MODE) {
		copyGame(current, player[playerPos].normalMode);
		saveAllPlayerInfo(player, nP);
		deallocateBoard_1(current.board, current.m);
		system("cls");
	}
	else if (current.mode == DIFFICULT_MODE) {
		copyGame(current, player[playerPos].diffMode);
		saveAllPlayerInfo(player, nP);
		deallocateBoard_2(current.list, current.m);
		system("cls");
	}
}

void playSound(int i) {
	if (i == -1) {
		PlaySound(L"background.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
	else {
		const wchar_t* fileName[6] = { L"move.wav", L"matched.wav",L"wrong.wav", L"win.wav", L"lose.wav", L"select.wav" };
		PlaySound(fileName[i], NULL, SND_FILENAME | SND_ASYNC);
	}
}