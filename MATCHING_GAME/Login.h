#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Graphic.h"
#include "Game.h"
void InputPassword(char password[]);

void InputUsername(char username[]);

void Login(bool& check, int& playerPos);

void Register(bool& result, int& playerPos);

void LogOrRegis(int& playerPos);