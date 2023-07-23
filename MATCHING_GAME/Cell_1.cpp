#include "Cell_1.h"
#include "Game.h"
using namespace std;

//INITIALIZE MATRIX
void initBoard_1(CELL**& board, int& m, int& n, int occur[26])
{
	//SIZE OF MATRIX
	do {
		cout << "Enter the rows of maxtrix:";
		cin >> m;
		cout << "Enter the colunms of matrix:";
		cin >> n;
		if (m < 0 || n < 0 || (m * n) % 2 != 0)
			cout << "not valid" << endl;
	} while (m < 0 || n < 0 || (m * n) % 2 != 0);

	m = m + 2;
	n = n + 2;
	//ALLOCATE MATRIX
	board = new CELL * [m];
	for (int i = 0;i < m;i++)
	{
		board[i] = new CELL[n];
		for (int j = 0;j < n;j++)
		{
			board[i][j].pos.x = j;
			board[i][j].pos.y = i;
		}
	}

	int total = ((m - 2) * (n - 2)) / 2;  //TOTAL OF CHARACTER
	while (total > 0)
	{
		char s = rand() % 26 + 65; //RAMDOM CHARACTER
		occur[int(s) - 65] += 2;
		int check = 2;
		while (check > 0)
		{
			int i = rand() % (m * n); //RAMDOM INDEX
			int m1 = i / n;
			int n1 = i % n;
			if (m1 != 0 && m1 != m - 1 && n1 != 0 && n1 != n - 1 && board[m1][n1].c == ' ')
			{
				board[m1][n1].c = s;
				check--;
			}
		}
		total--;
	}
	board[1][1].isCurr = 1;
}

//PRINT A CELL IN MATRIX
void drawCell_1(CELL cell)
{

	if (cell.c == ' ')
		return;
	//DRAW BOX
	goToXY(cell.pos.x * 8, cell.pos.y * 4);
	cout << " ------- ";
	goToXY(cell.pos.x * 8, cell.pos.y * 4 + 1);
	cout << "|       |";
	goToXY(cell.pos.x * 8, cell.pos.y * 4 + 2);
	cout << "|       |";
	goToXY(cell.pos.x * 8, cell.pos.y * 4 + 3);
	cout << "|       |";
	goToXY(cell.pos.x * 8, cell.pos.y * 4 + 4);
	cout << " ------- ";
	if (cell.isCurr || cell.isSelected) //CURRENT POSITION OR SELECTED CELL
	{
		TextColor(112);
		for (int i = 0;i < 3;i++)
		{
			goToXY(cell.pos.x * 8 + 1, cell.pos.y * 4 + 1 + i);
			cout << "       ";
		}
		goToXY(cell.pos.x * 8 + 4, cell.pos.y * 4 + 2);
		cout << cell.c;
		TextColor(7);
	}
	else
	{
		goToXY(cell.pos.x * 8 + 4, cell.pos.y * 4 + 2);
		cout << cell.c;
	}
	TextColor(7);
}


void drawSelectedCell_1(CELL cell, bool check) //AFTER CHECK-MATCHING, 2 CELLS SELECTED ARE MATCH OR NOT
{
	if (check)
		TextColor(160);
	else
		TextColor(192);
	for (int i = 0; i < 3;i++)
	{
		goToXY(cell.pos.x * 8 + 1, cell.pos.y * 4 + 1 + i);
		cout << "       ";
	}
	goToXY(cell.pos.x * 8 + 4, cell.pos.y * 4 + 2);
	cout << cell.c;
	TextColor(7);
}


void drawLifelineCell_1(CELL cell)//WHEN USER PRESS M TO GET MOVE SUGGESTION, 2 KEY CELLS ARE HIGHLIGHTED
{
	TextColor(224);
	for (int i = 0;i < 3;i++)
	{
		goToXY(cell.pos.x * 8 + 1, cell.pos.y * 4 + 1 + i);
		cout << "       ";
	}
	goToXY(cell.pos.x * 8 + 4, cell.pos.y * 4 + 2);
	cout << cell.c;
	TextColor(7);
}


void deleteCell_1(CELL cell)//MATCHING PAIR DISAPPEAR
{
	for (int i = 0;i < 5;i++)
	{
		goToXY(cell.pos.x * 8, cell.pos.y * 4 + i);
		cout << "         ";
	}
}





//PRINT MATRIX
void displayBoard_1(CELL** board, int m, int n)
{
	for (int i = 1;i < m - 1;i++)
	{
		for (int j = 1;j < n - 1;j++)
		{
			drawCell_1(board[i][j]);
		}
	}
}

//DEALLOCATE MATRIX
void deallocateBoard_1(CELL**& board, int m)
{
	for (int i = 0;i < m;i++)
	{
		delete[] board[i];
	}
	delete[] board;
}



void move_1(CELL** board, int m, int n, point& curr, point& Prevcurr, point posSelected[], int& cnt_pos, int& status, bool& help)
{
	char temp = _getch();
	if (temp == -32)//ARROW KEY
	{
		temp = _getch();
		Prevcurr = curr;
		board[curr.y][curr.x].isCurr = 0;
		bool check = 0;
		//FIND THE CELL NEAREST THAT IS NOT A BLANK CELL
		if (temp == UP)
		{
			for (int i = curr.y - 1;i > 0;i--)
			{
				if (board[i][curr.x].c != ' ')
				{
					curr.y = i;
					check = 1;
					break;
				}
			}
			int left = curr.x - 1;
			int right = curr.x + 1;
			while ((left > 0 || right < n - 1) && !check)
			{
				for (int i = curr.y - 1;i > 0;i--)
				{
					if (left > 0 && board[i][left].c != ' ')
					{
						curr.y = i;
						curr.x = left;
						check = 1;
						break;
					}
					else if (right < n - 1 && board[i][right].c != ' ')
					{
						curr.y = i;
						curr.x = right;
						check = 1;
						break;
					}
				}
				left--;
				right++;
			}
			if (!check)
			{
				for (int i = m - 2;i > curr.y;i--)
				{
					if (board[i][curr.x].c != ' ')
					{
						curr.y = i;
						check = 1;
						break;
					}
				}
			}
			left = curr.x - 1;
			right = curr.x + 1;
			while ((left > 0 || right < n - 1) && !check)
			{
				for (int i = m - 2;i >= curr.y;i--)
				{
					if (left > 0 && board[i][left].c != ' ')
					{
						curr.y = i;
						curr.x = left;
						check = 1;
						break;
					}
					else if (right < n - 1 && board[i][right].c != ' ')
					{
						curr.y = i;
						curr.x = right;
						check = 1;
						break;
					}
				}
				left--;
				right++;
			}
		}
		else if (temp == DOWN)
		{
			for (int i = curr.y + 1;i < m - 1;i++)
			{
				if (board[i][curr.x].c != ' ')
				{
					curr.y = i;
					check = 1;
					break;
				}
			}
			int left = curr.x - 1;
			int right = curr.x + 1;
			while ((left > 0 || right < n - 1) && !check)
			{
				for (int i = curr.y + 1;i < m - 1;i++)
				{
					if (left > 0 && board[i][left].c != ' ')
					{
						curr.y = i;
						curr.x = left;
						check = 1;
						break;
					}
					else if (right < n - 1 && board[i][right].c != ' ')
					{
						curr.y = i;
						curr.x = right;
						check = 1;
						break;
					}
				}
				left--;
				right++;
			}
			if (!check)
			{
				for (int i = 1;i < curr.y;i++)
				{
					if (board[i][curr.x].c != ' ')
					{
						curr.y = i;
						check = 1;
						break;
					}
				}
			}
			left = curr.x - 1;
			right = curr.x + 1;
			while ((left > 0 || right < n - 1) && !check)
			{
				for (int i = 1;i <= curr.y;i++)
				{
					if (left > 0 && board[i][left].c != ' ')
					{
						curr.y = i;
						curr.x = left;
						check = 1;
						break;
					}
					else if (right < n - 1 && board[i][right].c != ' ')
					{
						curr.y = i;
						curr.x = right;
						check = 1;
						break;
					}
				}
				left--;
				right++;
			}
		}
		else if (temp == LEFT)
		{
			for (int i = curr.x - 1;i > 0;i--)
			{
				if (board[curr.y][i].c != ' ')
				{
					curr.x = i;
					check = 1;
					break;
				}
			}
			int up = curr.y - 1;
			int down = curr.y + 1;
			while ((up > 0 || down < m - 1) && !check)
			{
				for (int i = curr.x - 1;i > 0;i--)
				{
					if (up > 0 && board[up][i].c != ' ')
					{
						curr.x = i;
						curr.y = up;
						check = 1;
						break;
					}
					else if (down < m - 1 && board[down][i].c != ' ')
					{
						curr.x = i;
						curr.y = down;
						check = 1;
						break;
					}
				}
				up--;
				down++;
			}
			if (!check)
			{
				for (int i = n - 2;i > curr.x;i--)
				{
					if (board[curr.y][i].c != ' ')
					{
						curr.x = i;
						check = 1;
						break;
					}
				}
			}
			up = curr.y - 1;
			down = curr.y + 1;
			while ((up > 0 || down < m - 1) && !check)
			{
				for (int i = n - 2;i >= curr.x;i--)
				{
					if (up > 0 && board[up][i].c != ' ')
					{
						curr.x = i;
						curr.y = up;
						check = 1;
						break;
					}
					else if (down < m - 1 && board[down][i].c != ' ')
					{
						curr.x = i;
						curr.y = down;
						check = 1;
						break;
					}
				}
				up--;
				down++;
			}
		}
		else
		{
			for (int i = curr.x + 1;i < n - 1;i++)
			{
				if (board[curr.y][i].c != ' ')
				{
					curr.x = i;
					check = 1;
					break;
				}
			}
			int up = curr.y - 1;
			int down = curr.y + 1;
			while ((up > 0 || down < m - 1) && !check)
			{
				for (int i = curr.x + 1;i < n - 1;i++)
				{
					if (up > 0 && board[up][i].c != ' ')
					{
						curr.x = i;
						curr.y = up;
						check = 1;
						break;
					}
					else if (down < m - 1 && board[down][i].c != ' ')
					{
						curr.x = i;
						curr.y = down;
						check = 1;
						break;
					}
				}
				up--;
				down++;
			}
			if (!check)
			{
				for (int i = 1;i < curr.x;i++)
				{
					if (board[curr.y][i].c != ' ')
					{
						curr.x = i;
						check = 1;
						break;
					}
				}
			}
			up = curr.y - 1;
			down = curr.y + 1;
			while ((up > 0 || down < m - 1) && !check)
			{
				for (int i = 1;i <= curr.x;i++)
				{
					if (up > 0 && board[up][i].c != ' ')
					{
						curr.x = i;
						curr.y = up;
						check = 1;
						break;
					}
					else if (down < m - 1 && board[down][i].c != ' ')
					{
						curr.x = i;
						curr.y = down;
						check = 1;
						break;
					}
				}
				up--;
				down++;
			}
		}
		board[curr.y][curr.x].isCurr = 1;
		drawCell_1(board[curr.y][curr.x]);
		drawCell_1(board[Prevcurr.y][Prevcurr.x]);
		playSound(MOVE);
	}
	else if (temp == ENTER) //SELECT CELL
	{
		if (cnt_pos < 2)
		{
			posSelected[cnt_pos].x = curr.x;
			posSelected[cnt_pos].y = curr.y;
			board[curr.y][curr.x].isSelected = 1;
			cnt_pos++;
		}
		playSound(SELECTED);

	}
	else if (temp == ESC) //EXIT
	{
		status = 2;
		playSound(MOVE);
	}
	else if (temp == 'm' || temp == 'M')//USER WANTS TO GET MOVE SUGGESTION
	{
		help = 1;
		playSound(MOVE);
	}
}


