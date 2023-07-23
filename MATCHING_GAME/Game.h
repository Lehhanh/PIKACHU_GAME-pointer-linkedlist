#pragma once
#include<ctime>
#include<fstream>
#include"Cell_1.h"
#include"Cell_2.h"



using namespace std;

#define NORMAL_MODE 1
#define DIFFICULT_MODE 2

#define BACKGROUND -1
#define MOVE 0
#define MATCHED 1
#define WRONG 2
#define WIN 3
#define LOSE 4
#define SELECTED 5

struct GAME {
	int life = 3;
	int score = 0;
	int playTime = 0;
	int nLifeline = 2;
};

struct State {
	int mode;
	int m = 0;
	int n = 0;
	int occur[26]{};
	CELL** board;
	NODE** list;
	GAME game;
};

struct Record {
	// mode = 1: normal mode, 2: difficult mode
	int mode;
	int score = 0;
	int playTime = 0;
};

struct PLAYER {
	char name[30];
	char password[7];
	Record norRec;
	Record diffRec;
	State diffMode;
	State normalMode;
};


// save board and mode after each time deleting
void copyGame(State source, State& des);

bool isEmptyBoard(CELL** board, int m, int n);

void savePlayerInfo(PLAYER player);

void saveAllPlayerInfo(PLAYER* player, int n);

void readAllPlayerInfo(PLAYER*& player, int& n);

void gameFinishVerify(State& current, PLAYER* player, int nP, int playerPos, int& status);

void exitPlayingMode(PLAYER*& player, int nP, int playerPos, State& current);

bool isEmptyList(NODE** board, int m, int n);

void playSound(int i);