#pragma once
#include "Console.h"
#include "Cell_1.h"
#include "Graphic.h"
#include <time.h>
#include <iostream>
#include <conio.h>


bool first_check(point p1, point p2, CELL** board);

//I CHECK
bool checkColumn(int y1, int y2, int x, CELL** board);
bool checkRow(int x1, int x2, int y, CELL** board);
bool checkIMatching(point p1, point p2, CELL** board);

//Z & L CHECK
bool checkZ_LRow(point p1, point p2, CELL** board);
bool checkZ_LColumn(point p1, point p2, CELL** board);
bool checkZ_L_Matching(point p1, point p2, CELL** board);

//U CHECK
bool checkUColumn(point p1, point p2, CELL** board, int direction);
bool checkURow(point p1, point p2, CELL** board, int direction);
bool checkUMatching(point p1, point p2, CELL** board);

bool check_2_point(point p1, point p2, CELL** board);


bool checkValidMatrix(CELL** board, int m, int n, point& key1, point& key2, int occur[26]);
void renewMatrix(CELL** board, int m, int n, int occur[26]);
void moveSuggestion(CELL** board, point key1, point key2, int& lifeline);
bool check_draw(CELL** board, int m, int n, point& curr, point& posSelected1, point& posSelected2, int occur[26], char bg[16][40]);
void display(int occur[26]);