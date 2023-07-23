#include<iostream>
#include<Windows.h>
#include<conio.h>
#include "Login.h"
#include"Game.h"
void InputPassword(char password[]) {
	int size = 0;
	char key = _getch();
	while (key != 13) {// 13: ENTER
		if (key == 8) {// 8: BACKSPACE
			if (size > 0) {
				size--;
				cout << "\b \b";
				if (size == 0)
					key = _getch();
			}
			else {
				key = _getch();
			}
		}
		else if (key == 27) {// 27: ESC
			system("cls");
			exit(0);
		}
		// Chỉ cho phép nhập vào số và chữ cái in thường
		else if ((key >= '0' && key <= '9') || (key >= 'a' && key <= 'z')) {
			cout << key;
			password[size] = key;
			size++;
			Sleep(120);
			cout << "\b*";
		}
		key = _getch();
	}
	password[size] = '\0';
}

void InputUsername(char username[]) {
	int size = 0;
	char key = _getch();
	while (key != 13) {// 13: ENTER
		if (key == 8) {// 8: BACKSPACE
			if (size > 0) {
				size--;
				cout << "\b \b";
				if (size == 0)
					key = _getch();
			}
			else {
				key = _getch();
			}
		}
		else if (key == 27) {// 27: ESC
			system("cls");
			exit(0);
		}
		// Chỉ cho phép nhập vào số và chữ in thường
		else if ((key >= '0' && key <= '9') || (key >= 'a' && key <= 'z')) {
			cout << key;
			username[size] = key;
			size++;
		}
		key = _getch();
	}
	username[size] = '\0';
}

void Login(bool& check, int& playerPos) {
	char password[20];
	char username[30];
	PLAYER* player;
	int nP;
	check = false;

	cout << "USERNAME: ";
	InputUsername(username);
	cout << endl;
	cout << "PASSWORD: ";
	InputPassword(password);
	cout << endl;

	readAllPlayerInfo(player, nP);
	for (int i = 0; i < nP; i++) {
		if ((strcmp(player[i].name, username) == 0) 
			&& (strcmp(player[i].password, password) == 0)) 
		{
			cout << "LOGIN SUCCESSFULLY!" << endl;
			playerPos = i;
			check = true;
			break;
		}
	}

	if (check == false) {
		cout << "LOGIN FAILED!" << endl;
	}
}

void Register(bool& result, int& playerPos) {
	char password[7];
	char username[30];
	PLAYER* player;
	int nP;
	result = false;

	cout << "USERNAME: ";
	InputUsername(username);
	cout << endl;
	cout << "PASSWORD(6 characters): ";
	InputPassword(password);
	cout << endl;

	readAllPlayerInfo(player, nP);
	for (int i = 0; i < nP; i++) {
		if (strcmp(player[i].name, username) == 0)
		{
			cout << "Account has existed, please enter again!" << endl;
			return;
		}
	}

	if (strlen(password) != 6) {
		cout << "Password must have 6 characters, please enter again!" << endl;
		return;
	}

	result = true;
	PLAYER p;
	strcpy_s(p.name, 30, username);
	strcpy_s(p.password, 7 , password);
	p.normalMode.m = p.normalMode.n = 5;
	//ALLOCATE MATRIX
	p.normalMode.board = new CELL * [p.normalMode.m];
	for (int i = 0; i < p.normalMode.m; i++)
	{
		p.normalMode.board[i] = new CELL[p.normalMode.n];
		for (int j = 0; j < p.normalMode.n; j++)
		{
			p.normalMode.board[i][j].pos.x = j;
			p.normalMode.board[i][j].pos.y = i;
		}
	}

	p.diffMode.m = p.diffMode.n = 5;
	NODE** head = new NODE * [p.diffMode.m];

	for (int i = 0; i < p.diffMode.m; i++) {
		head[i] = NULL;

		for (int j = 0; j < p.diffMode.n; j++) {
			NODE* node = new NODE;
			node->pNext = NULL;
			node->pos.y = i;
			node->pos.x = j;
			addTail(head[i], node);
		}
	}

	p.diffMode.list = head;

	savePlayerInfo(p);
	playerPos = nP;

}

void LogOrRegis(int& playerPos) {
	// choose login or register: 1 - login 2 - register
	bool result;
	int choice = 1;
	bool check = 0;
	drawBoxLogorRegis();
	drawButton(choice);
	while (!check)
	{
		if (_kbhit())
		{
			char temp = _getch();
			if (temp == -32)
			{
				temp = _getch();
				if (temp == LEFT || temp == RIGHT)
				{
					if (choice == 1)
						choice = 2;
					else
						choice = 1;
					drawButton(choice);
				}
			}
			else if (temp == ENTER)
			{
				check = 1;
			}
		}
	}
	system("cls");
	if (choice == 1)
	{
		do {
			Login(result, playerPos);
			Sleep(1000);
			system("cls");
		} while (result == false);
	}
	else
	{
		do {
			Register(result, playerPos);
			Sleep(1000);
			system("cls");
		} while (result == false);
	}
}