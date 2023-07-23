#include "Cell_2.h"
#include "Game.h"
using namespace std;

//ACCESS THE NODE 
NODE* findNode(NODE** board, int y, int x) 
{
	if (y < 0 || x < 0) return NULL;

	NODE* temp = board[y];
	for (int i = 0; i < x; i++) {
		temp = temp->pNext;
	}

	return temp;
}


void addTail(NODE*& pHead, NODE* node) 
{
	NODE* pCurrent = pHead;

	if (pCurrent == NULL) {
		node->pNext = pCurrent;
		pHead = node;
		return;
	}

	// traverse till the the last node
	while (pCurrent->pNext != NULL) {
		pCurrent = pCurrent->pNext;
	}

	pCurrent->pNext = node;
}

//INITIALIZE MATRIX
void initBoard_2(NODE**& board, int& m, int& n, int occur[26])
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

	//ALLOCATE ARRAY OF LINKED LIST
	NODE** head = new NODE * [m];

	for (int i = 0; i < m; i++) {
		head[i] = NULL;

		for (int j = 0; j < n; j++) {
			NODE* node = new NODE;
			node->pNext = NULL;
			node->pos.y = i;
			node->pos.x = j;
			addTail(head[i], node);
		}
	}

	board = head;

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
			if (m1 != 0 && m1 != m - 1 && n1 != 0 && n1 != n - 1)
			{
				NODE* node = findNode(board, m1, n1);
				if (node->c == ' ') {
					node->c = s;
					check--;
				}
			}
		}
		total--;
	}

	NODE* tmp = findNode(board, 1, 1);
	tmp->isCurr = 1;
}


//DRAW A CELL IN THE BOARD
void drawCell_2(NODE* node)
{
	if (node->c != 32)
	{
		//DRAW BOX
		goToXY(node->pos.x * 8, node->pos.y * 4);
		cout << " ------- ";
		goToXY(node->pos.x * 8, node->pos.y * 4 + 1);
		cout << "|       |";
		goToXY(node->pos.x * 8, node->pos.y * 4 + 2);
		cout << "|       |";
		goToXY(node->pos.x * 8, node->pos.y * 4 + 3);
		cout << "|       |";
		goToXY(node->pos.x * 8, node->pos.y * 4 + 4);
		cout << " ------- ";
		if (node->isCurr || node->isSelected)
		{
			TextColor(112);
			for (int i = 0;i < 3;i++)
			{
				goToXY(node->pos.x * 8 + 1, node->pos.y * 4 + 1 + i);
				cout << "       ";
			}
			goToXY(node->pos.x * 8 + 4, node->pos.y * 4 + 2);
			cout << node->c;
			TextColor(7);
		}
		else
		{
			goToXY(node->pos.x * 8 + 4, node->pos.y * 4 + 2);
			cout << node->c;
		}
	}
	TextColor(7);
}

void drawSelectedCell_2(NODE* node, bool check) //AFTER CHECK-MATCHING, 2 CELLS SELECTED ARE MATCH OR NOT
{
	if (check)
		TextColor(160);
	else
		TextColor(192);
	for (int i = 0; i < 3;i++)
	{
		goToXY(node->pos.x * 8 + 1, node->pos.y * 4 + 1 + i);
		cout << "       ";
	}
	goToXY(node->pos.x * 8 + 4, node->pos.y * 4 + 2);
	cout << node->c;
	TextColor(7);
}



void drawLifelineCell_2(NODE* node)//WHEN USER PRESS M TO GET MOVE SUGGESTION, 2 KEY CELLS ARE HIGHLIGHTED
{
	TextColor(224);
	for (int i = 0;i < 3;i++)
	{
		goToXY(node->pos.x * 8 + 1, node->pos.y * 4 + 1 + i);
		cout << "       ";
	}
	goToXY(node->pos.x * 8 + 4, node->pos.y * 4 + 2);
	cout << node->c;
	TextColor(7);
}


//PRINT BOARD
void displayBoard_2(NODE** board, int m, int n)
{
	for (int i = 1; i < m - 1;i++)
	{
		NODE* temp = board[i]->pNext;
		for (int j = 1;j < n - 1;j++)
		{
			drawCell_2(temp);
			temp = temp->pNext;
		}
	}
}

void deleteCell_2(NODE* node)//MATCHING PAIR DISAPPEAR
{
	for (int i = 0;i < 5;i++)
	{
		goToXY(node->pos.x * 8, node->pos.y * 4 + i);
		cout << "         ";
	}
}

//DEALLOCATE MATRIX
void deallocateBoard_2(NODE**& board, int m)
{
	for (int i = 0;i < m;i++)
	{
		NODE* curr = board[i];
		while (board[i])
		{
			curr = board[i]->pNext;
			delete board[i];
			board[i] = curr;
		}
	}
	delete[] board;
}


void move_2(NODE** board, int m, int n, point& curr, point& Prevcurr, point posSelected[], int& cnt_pos, int& status, bool& help)
{
	char temp = _getch();
	if (temp == -32)//ARROW KEY
	{
		temp = _getch();
		NODE* node = findNode(board, curr.y, curr.x);
		node->isCurr = 0;
		Prevcurr = curr;
		bool check = 0;
		//FIND THE CELL NEAREST THAT IS NOT A BLANK CELL
		if (temp == UP)
		{
			for (int i = curr.y - 1;i > 0;i--)
			{
				node = findNode(board, i, curr.x);
				if (node->c != ' ')
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
					if (left > 0)
					{
						node = findNode(board, i, left);
						if (node->c != ' ')
						{
							curr.y = i;
							curr.x = left;
							check = 1;
							break;
						}
					}
					else if (right < n - 1)
					{
						node = findNode(board, i, right);
						if (node->c != ' ')
						{
							curr.y = i;
							curr.x = right;
							check = 1;
							break;
						}
					}
				}
				left--;
				right++;
			}
			if (!check)
			{
				for (int i = m - 2;i > curr.y;i--)
				{
					node = findNode(board, i, curr.x);
					if (node->c != ' ')
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
					if (left > 0)
					{
						node = findNode(board, i, left);
						if (node->c != ' ')
						{
							curr.y = i;
							curr.x = left;
							check = 1;
							break;
						}
					}
					if (right < n - 1)
					{
						node = findNode(board, i, right);
						if (node->c != ' ')
						{
							curr.y = i;
							curr.x = right;
							check = 1;
							break;
						}
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
				node = findNode(board, i, curr.x);
				if (node->c != ' ')
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
					if (left > 0)
					{
						node = findNode(board, i, left);
						if (node->c != ' ')
						{
							curr.y = i;
							curr.x = left;
							check = 1;
							break;
						}
					}
					if (right < n - 1)
					{
						node = findNode(board, i, right);
						if (node->c != ' ')
						{
							curr.y = i;
							curr.x = right;
							check = 1;
							break;
						}
					}
				}
				left--;
				right++;
			}
			if (!check)
			{
				for (int i = 1;i < curr.y;i++)
				{
					node = findNode(board, i, curr.x);
					if (node->c != ' ')
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
					if (left > 0)
					{
						node = findNode(board, i, left);
						if (node->c != ' ')
						{
							curr.y = i;
							curr.x = left;
							check = 1;
							break;
						}
					}
					else if (right < n - 1)
					{
						node = findNode(board, i, right);
						if (node->c != ' ')
						{
							curr.y = i;
							curr.x = right;
							check = 1;
							break;
						}
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
				node = findNode(board, curr.y, i);
				if (node->c != ' ')
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
					if (up > 0)
					{
						node = findNode(board, up, i);
						if (node->c != ' ')
						{
							curr.x = i;
							curr.y = up;
							check = 1;
							break;
						}
					}
					if (down < m - 1)
					{
						node = findNode(board, down, i);
						if (node->c != ' ')
						{
							curr.x = i;
							curr.y = down;
							check = 1;
							break;
						}
					}
				}
				up--;
				down++;
			}
			if (!check)
			{
				for (int i = n - 2;i > curr.x;i--)
				{
					node = findNode(board, curr.y, i);
					if (node->c != ' ')
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
					if (up > 0)
					{
						node = findNode(board, up, i);
						if (node->c != ' ')
						{
							curr.x = i;
							curr.y = up;
							check = 1;
							break;
						}
					}
					if (down < m - 1)
					{
						node = findNode(board, down, i);
						if (node->c != ' ')
						{
							curr.x = i;
							curr.y = down;
							check = 1;
							break;
						}
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
				node = findNode(board, curr.y, i);
				if (node->c != ' ')
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
					if (up > 0)
					{
						node = findNode(board, up, i);
						if (node->c != ' ')
						{
							curr.x = i;
							curr.y = up;
							check = 1;
							break;
						}

					}
					if (down < m - 1)
					{
						node = findNode(board, down, i);
						if (node->c != ' ')
						{
							curr.x = i;
							curr.y = down;
							check = 1;
							break;
						}
					}
				}
				up--;
				down++;
			}
			if (!check)
			{
				for (int i = 1;i < curr.x;i++)
				{
					node = findNode(board, curr.y, i);
					if (node->c != ' ')
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
					if (up > 0)
					{
						node = findNode(board, up, i);
						if (node->c != ' ')
						{
							curr.x = i;
							curr.y = up;
							check = 1;
							break;
						}
					}
					if (down < m - 1)
					{
						node = findNode(board, down, i);
						if (node->c != ' ')
						{
							curr.x = i;
							curr.y = down;
							check = 1;
							break;
						}
					}
				}
				up--;
				down++;
			}
		}
		node = findNode(board, curr.y, curr.x);
		node->isCurr = 1;
		drawCell_2(node);
		node = findNode(board, Prevcurr.y, Prevcurr.x);
		drawCell_2(node);
		playSound(MOVE);
	}
	else if (temp == ENTER)
	{
		if (cnt_pos < 2)
		{
			posSelected[cnt_pos].x = curr.x;
			posSelected[cnt_pos].y = curr.y;
			NODE* node = findNode(board, curr.y, curr.x);
			node->isSelected = 1;
			cnt_pos++;
		}
		playSound(SELECTED);
	}
	else if (temp == ESC)
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