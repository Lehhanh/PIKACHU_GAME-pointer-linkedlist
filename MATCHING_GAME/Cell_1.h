#pragma once
#include "Console.h"
#include <time.h>
#include <iostream>
#include <string>
#include <conio.h>


#define ESC 27
#define ENTER 13
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

struct point {
	int x, y;
};


struct CELL {
	point pos;
	char c = ' ';
	bool isCurr = 0;
	bool isSelected = 0;
};



void initBoard_1(CELL**& board, int& m, int& n, int occur[26]);
void drawCell_1(CELL cell);
void drawSelectedCell_1(CELL cell, bool check);
void drawLifelineCell_1(CELL cell);
void deleteCell_1(CELL cell);
void displayBoard_1(CELL** board, int m, int n);
void deallocateBoard_1(CELL**& board, int m);
void move_1(CELL** board, int m, int n, point& curr, point& Prevcurr, point posSelected[], int& cnt_pos, int& status, bool& help);

