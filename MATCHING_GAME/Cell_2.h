#pragma once
#include "Cell_1.h"


struct NODE {
	point pos;
	char c = ' ';
	bool isCurr = 0;
	bool isSelected = 0;
	NODE* pNext;
};


NODE* findNode(NODE** board, int y, int x);
void addTail(NODE*& pHead, NODE* node);
void initBoard_2(NODE**& board, int& m, int& n, int occur[26]);
void drawCell_2(NODE* node);
void drawSelectedCell_2(NODE* node, bool check);
void drawLifelineCell_2(NODE* node);
void displayBoard_2(NODE** board, int m, int n);
void deleteCell_2(NODE* node);
void deallocateBoard_2(NODE**& board, int m);
void move_2(NODE** board, int m, int n, point& curr, point& Prevcurr, point posSelected[], int& cnt_pos, int& status, bool& help);