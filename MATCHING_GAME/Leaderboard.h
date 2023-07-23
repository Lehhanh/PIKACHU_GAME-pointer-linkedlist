#pragma once
#include "Graphic.h"
#include"Game.h"

#define MAX_RANKED_PLAYER 5

// if finish
void saveDataToLeaderboard(int mode, PLAYER* pLeaderboard, int n);

void readLeaderBoard(int mode, PLAYER*& pLeaderboard, int& n);

void swapPlayer(PLAYER& p1, PLAYER& p2, int mode);

void addAndSortLeaderboard(PLAYER*& pLeaderboard, int& n, PLAYER p, State current);
// FIX do hoa
void printLeaderboard();