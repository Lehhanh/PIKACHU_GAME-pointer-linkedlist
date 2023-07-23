#pragma once
#include "Console.h"
#include "Cell_1.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>


#define MenuX 55
#define MenuY 10

void drawTitleMenu();
void drawBox(int y);
void drawCurrBox(int y);
void moveMenu(int& curr, int& prev, int& statusMenu);
void drawLoadingBar();
void drawTitle();
void drawPikachu();
void intro();
int statusMenu();