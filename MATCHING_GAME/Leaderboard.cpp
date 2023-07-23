#include"Game.h"
#include"Leaderboard.h"

// if finish
void saveDataToLeaderboard(int mode, PLAYER* pLeaderboard, int n) {
	if (mode == NORMAL_MODE) {
		ofstream ofs("normalLeaderboard.dat", ios::binary);

		for (int i = 0; i < n; i++) {
			ofs.write(pLeaderboard[i].name, 30);
			ofs.write((char*)&pLeaderboard[i].norRec.score, 4);
			ofs.write((char*)&pLeaderboard[i].norRec.playTime, 4);
		}

		ofs.close();
	}
	else if (mode == DIFFICULT_MODE) {
		ofstream ofs("difficultLeaderboard.dat", ios::binary);
		for (int i = 0; i < n; i++) {
			ofs.write(pLeaderboard[i].name, 30);
			ofs.write((char*)&pLeaderboard[i].diffRec.score, 4);
			ofs.write((char*)&pLeaderboard[i].diffRec.playTime, 4);
		}

		ofs.close();
	}
}

void readLeaderBoard(int mode, PLAYER*& pLeaderboard, int& n) {
	if (mode == NORMAL_MODE) {
		ifstream ifs("normalLeaderboard.dat", ios::binary);
		ifs.seekg(0, ios::end);
		n = ifs.tellg() / 38;
		ifs.seekg(0, ios::beg);

		for (int i = 0; i < n; i++) {
			ifs.read(pLeaderboard[i].name, 30);
			ifs.read((char*)&pLeaderboard[i].norRec.score, 4);
			ifs.read((char*)&pLeaderboard[i].norRec.playTime, 4);
		}

		ifs.close();
	}
	else if (mode == DIFFICULT_MODE) {
		ifstream ifs("difficultLeaderboard.dat", ios::binary);

		ifs.seekg(0, ios::end);
		n = ifs.tellg() / 38;
		ifs.seekg(0, ios::beg);

		for (int i = 0; i < n; i++) {
			ifs.read(pLeaderboard[i].name, 30);
			ifs.read((char*)&pLeaderboard[i].diffRec.score, 4);
			ifs.read((char*)&pLeaderboard[i].diffRec.playTime, 4);
		}

		ifs.close();
	}
}

void swapPlayer(PLAYER& p1, PLAYER& p2, int mode) {
	PLAYER temp;
	strcpy_s(temp.name, strlen(p1.name) + 1, p1.name);
	if (mode == NORMAL_MODE) {
		temp.norRec.mode = p1.norRec.mode;
		temp.norRec.score = p1.norRec.score;
		temp.norRec.playTime = p1.norRec.playTime;

		strcpy_s(p1.name, strlen(p2.name) + 1, p2.name);
		p1.norRec.mode = p2.norRec.mode;
		p1.norRec.score = p2.norRec.score;
		p1.norRec.playTime = p2.norRec.playTime;

		strcpy_s(p2.name, strlen(temp.name) + 1, temp.name);
		p2.norRec.mode = temp.norRec.mode;
		p2.norRec.score = temp.norRec.score;
		p2.norRec.playTime = temp.norRec.playTime;
	}
	else if (mode == DIFFICULT_MODE) {
		temp.diffRec.mode = p1.diffRec.mode;
		temp.diffRec.score = p1.diffRec.score;
		temp.diffRec.playTime = p1.diffRec.playTime;

		strcpy_s(p1.name, 30, p2.name);
		p1.diffRec.mode = p2.diffRec.mode;
		p1.diffRec.score = p2.diffRec.score;
		p1.diffRec.playTime = p2.diffRec.playTime;

		strcpy_s(p2.name, 30, temp.name);
		p2.diffRec.mode = temp.diffRec.mode;
		p2.diffRec.score = temp.diffRec.score;
		p2.diffRec.playTime = temp.diffRec.playTime;
	}
}

void addAndSortLeaderboard(PLAYER*& pLeaderboard, int& n, PLAYER p, State current) {
	if (current.mode == NORMAL_MODE) {
		strcpy_s(pLeaderboard[n].name, 30, p.name);
		pLeaderboard[n].norRec.mode = current.mode;
		pLeaderboard[n].norRec.score = current.game.score;
		pLeaderboard[n].norRec.playTime = current.game.playTime;

		// sort by score and time
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n + 1; j++) {
				if (pLeaderboard[i].norRec.score < pLeaderboard[j].norRec.score) {
					swapPlayer(pLeaderboard[j], pLeaderboard[i], current.mode);
				}
				else if ((pLeaderboard[i].norRec.score == pLeaderboard[j].norRec.score)
					&& (pLeaderboard[i].norRec.playTime >= pLeaderboard[j].norRec.playTime)) {
					swapPlayer(pLeaderboard[j], pLeaderboard[i], current.mode);
				}
			}
		}
	}
	else if (current.mode == DIFFICULT_MODE) {
		// p is the 6th player in leader board
		strcpy_s(pLeaderboard[n].name, 30, p.name);
		pLeaderboard[n].diffRec.mode = current.mode;
		pLeaderboard[n].diffRec.score = current.game.score;
		pLeaderboard[n].diffRec.playTime = current.game.playTime;
	
		// sort by score and time
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n + 1; j++) {
				if (pLeaderboard[i].diffRec.score < pLeaderboard[j].diffRec.score) {
					swapPlayer(pLeaderboard[j], pLeaderboard[i], current.mode);
				}
				else if ((pLeaderboard[i].diffRec.score == pLeaderboard[j].diffRec.score)
					&& (pLeaderboard[i].diffRec.playTime >= pLeaderboard[j].diffRec.playTime)) {
					swapPlayer(pLeaderboard[i], pLeaderboard[i], current.mode);
				}
			}
		}
	}
	// leaderboard only have 5 players with highest score(each mode)
	if (n < MAX_RANKED_PLAYER)
		n++;
}




void printLeaderboard() {
	PLAYER* pNormal = new PLAYER[5];
	int nNormal = 0;
	readLeaderBoard(NORMAL_MODE, pNormal, nNormal);
	title_Leaderboard();
	drawLeaderBoard(1, pNormal);


	PLAYER* pDiff = new PLAYER[6];
	int nDiff = 0;
	readLeaderBoard(DIFFICULT_MODE, pDiff, nDiff);
	drawLeaderBoard(2, pDiff);
	goToXY(50, 33);
	TextColor(12);
	cout << "--------PRESS ESC TO EXIT--------";
	TextColor(7);
	while (1)
	{
		if (_kbhit())
		{
			char temp = _getch();
			if (temp == ESC)
				break;
		}
	}
	

}

