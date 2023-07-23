#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "Console.h"
#include "Game.h"
using namespace std;


void drawBorder(int m, int n);
void drawBoxPlayer(int x, int y);
void drawBG(char bg[16][40]);
void displayBG(char bg[16][40], int x, int y);

void drawTitle();
void drawPikachu();
void drawLoadingBar();
void intro();

void drawHowtoPlayBox();
void HowToPlay();

void title_Leaderboard();
void drawLeaderBoard(int mode, PLAYER* player);

void drawBoxLogorRegis();
void drawButton(int choice);


void drawEndGame(int result, State curr);
void drawButton_2(int choice);
void drawButton_3(int choice);
void drawBoxContinueGame();
void drawBoxPreviousGame();