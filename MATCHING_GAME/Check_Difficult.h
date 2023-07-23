#pragma once
#include "Console.h"
#include "Cell_2.h"
#include <time.h>
#include <iostream>
#include <conio.h>

bool first_check(point p1, point p2, NODE** board);


bool checkColList(int y1, int y2, int x, NODE** board);
bool checkRowList(int x1, int x2, int y, NODE** board);
bool checkIList(point p1, point p2, NODE** board);


bool checkZ_LRowList(point p1, point p2, NODE** board);
bool checkZ_LColList(point p1, point p2, NODE** board);
bool checkZ_L_List(point p1, point p2, NODE** board);


bool checkUColList(point p1, point p2, NODE** board, int direction);
bool checkURowList(point p1, point p2, NODE** board, int direction);
bool checkUList(point p1, point p2, NODE** board);


bool check_2_pointList(point p1, point p2, NODE** board);


void deleteNode(NODE**& board, int y, int x);
void checkAndDeleteNode(NODE**& board, int m, int n, point p1, point p2);

bool checkValidMatrix_2(NODE** board, int m, int n, point& key1, point& key2, int occur[26]);
void renewMatrix_2(NODE** board, int m, int n, int occur[26]);
void moveSuggestion_2(NODE** board, point key1, point key2, int& lifeline);
bool check_draw_2(NODE** board, int m, int n, point& posSelected1, point& posSelected2, int occur[26], point& curr);