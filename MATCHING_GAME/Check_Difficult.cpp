#include "Check_Difficult.h"
using namespace std;

bool first_check(point p1, point p2, NODE** board)
{
	NODE* node1 = findNode(board, p1.y, p1.x);
	NODE* node2 = findNode(board, p2.y, p2.x);
	if ((p1.x == p2.x && p1.y == p2.y)
		|| (node1->c != node2->c)) {  //same position or different character
		return false;
	}
	return true;
}


bool checkColList(int y1, int y2, int x, NODE** board) 
{
	int min = y1;
	int max = y2;

	if (y1 > y2) {
		min = y2;
		max = y1;
	}

	for (int y = min; y < max; y++) {
		NODE* node = findNode(board, y, x);
		if (y > min && node->c != ' ') {
			return false;
		}
	}

	return true;
}

bool checkRowList(int x1, int x2, int y, NODE** board) 
{
	int min = x1;
	int max = x2;

	if (x1 > x2) {
		min = x2;
		max = x1;
	}

	for (int x = min; x < max; x++) 
	{
		NODE* node = findNode(board, y, x);
		if (x > min && node->c != ' ') 
		{
			return false;
		}
	}

	return true;
}


bool checkIList(point p1, point p2, NODE** board) 
{
	if (p1.x == p2.x) {     // same column
		return checkColList(p1.y, p2.y, p1.x, board);
	}
	else if (p1.y == p2.y) {    // same row
		return checkRowList(p1.x, p2.x, p1.y, board);
	}

	return false;
}

bool checkZ_LRowList(point p1, point p2, NODE** board) //HORIZONTALLY
{
	point min = p1;
	point max = p2;
	if (p1.x > p2.x)
	{
		min = p2;
		max = p1;
	}

	for (int i = min.x; i <= max.x; i++)
	{
		NODE* node = findNode(board, min.y, i);
		if (i > min.x && node->c != ' ') {
			return false;
		}
		node = findNode(board, max.y, i);
		if ((i < max.x && node->c == ' ') || (i == max.x))
		{
			if (checkColList(min.y, max.y, i, board) == true
				&& checkRowList(i, max.x, max.y, board) == true) 
			{
				return true;
			}
		}
	}
	return false;
}

bool checkZ_LColList(point p1, point p2, NODE** board) //VERTICALLY
{
	point min = p1;
	point max = p2;
	if (p1.y > p2.y)
	{
		min = p2;
		max = p1;
	}

	for (int i = min.y; i <= max.y; i++)
	{
		NODE* node = findNode(board, i, min.x);
		if (i > min.y && node->c != ' ') //gap vat can
			return false;
		node = findNode(board, i, max.x);
		if ((i < max.y && node->c == ' ') || (i == max.y))
		{
			if (checkRowList(min.x, max.x, i, board) && checkColList(i, max.y, max.x, board)) 
			{
				return true;
			}
		}
	}
	return false;
}

bool checkZ_L_List(point p1, point p2, NODE** board)
{
	if (checkZ_LRowList(p1, p2, board) == true || checkZ_LColList(p1, p2, board) == true) 
	{
		return true;
	}
	return false;
}

// direction = 1 is check right, direction  = -1 is check left
bool checkUColList(point p1, point p2, NODE** board, int direction) 
{
	point min = p1, max = p2;
	if (p1.x > p2.x)
	{
		min = p2;
		max = p1;
	}

	int col = max.x + direction;
	int row = min.y;
	int endCol = max.x;

	if (direction == -1) 
	{
		col = min.x + direction;
		row = max.y;
		endCol = min.x;
	}

	NODE* node = findNode(board, row, endCol);
	if ((node->c == ' ' || min.x == max.x) && checkRowList(min.x, max.x, row, board))
	{
		NODE* node1 = findNode(board, min.y, col);
		NODE* node2 = findNode(board, max.y, col);

		while (node1->c == ' ' && node2->c == ' ') {
			if (checkColList(min.y, max.y, col, board)) 
			{
				return true;
			}

			col += direction;
			node1 = findNode(board, min.y, col);
			node2 = findNode(board, max.y, col);
		}
	}

	return false;
}

// direction = 1 is check down, direction  = -1 is check up
bool checkURowList(point p1, point p2, NODE** board, int direction) 
{
	point min = p1, max = p2;
	if (p1.y > p2.y)
	{
		min = p2;
		max = p1;
	}

	int row = max.y + direction;
	int col = min.x;
	int endRow = max.y;

	if (direction == -1) {
		row = min.y + direction;
		col = max.x;
		endRow = min.y;
	}

	NODE* node = findNode(board, endRow, col);
	if ((node->c == ' ' || min.y == max.y)
		&& checkColList(min.y, max.y, col, board))
	{
		NODE* node1 = findNode(board, row, min.x);
		NODE* node2 = findNode(board, row, max.x);

		while (node1->c == ' ' && node2->c == ' ')
		{
			if (checkRowList(min.x, max.x, row, board)) 
			{
				return true;
			}

			row += direction;
			NODE* node1 = findNode(board, row, min.x);
			NODE* node2 = findNode(board, row, max.x);
		}
	}

	return false;
}

bool checkUList(point p1, point p2, NODE** board) 
{

	if (checkUColList(p1, p2, board, 1)
		|| checkUColList(p1, p2, board, -1)
		|| checkURowList(p1, p2, board, 1)
		|| checkURowList(p1, p2, board, -1)) {
		return true;
	}

	return false;
}

bool check_2_pointList(point p1, point p2, NODE** board)
{
	if (!first_check(p1, p2, board)) 
		return false;
	if (checkIList(p1, p2, board)) 
		return true;
	if (checkZ_L_List(p1, p2, board))
		return true;
	if (checkUList(p1, p2, board))
		return true;
	return false;
}



void deleteNode(NODE**& board, int y, int x) 
{
	NODE* node = findNode(board, y, x);
	if (node->pNext->pNext == NULL) 
	{
		node->c = ' ';
	}
	else {

		NODE* next = node->pNext;
		while (node->pNext->c != ' ') 
		{
			node->c = next->c;
			node->isCurr = next->isCurr;
			node->isSelected = next->isSelected;
			node = node->pNext;
			next = next->pNext;
		}
	}
	node->c = ' ';
	node->isCurr = node->pNext->isCurr;
	node->isSelected = node->pNext->isSelected;
	deleteCell_2(node);
}

void checkAndDeleteNode(NODE**& board, int m, int n, point p1, point p2) 
{
	if (p1.x == p2.x)
	{
		int min = p1.y;
		int max = p2.y;

		if (p1.y > p2.y)
		{
			min = p2.y;
			max = p1.y;
		}

		deleteNode(board, max, p1.x);
		deleteNode(board, min, p2.x);
	}
	else if (p1.y == p2.y)
	{
		int min = p1.x;
		int max = p2.x;

		if (p1.x > p2.x)
		{
			min = p2.x;
			max = p1.x;
		}

		deleteNode(board, p1.y, max);
		deleteNode(board, p2.y, min);
	}
	else {
		deleteNode(board, p1.y, p1.x);
		deleteNode(board, p2.y, p2.x);
	}
}


bool checkValidMatrix_2(NODE** board, int m, int n, point& key1, point& key2, int occur[26])
{
	key1 = { -1, -1 };
	key2 = { -1, -1 };
	for (int k = 0;k < 26;k++)
	{
		//CHARACTER IN THE BOARD
		if (occur[k] != 0)
		{
			point* posCheck = new point[occur[k]];
			int count = 0;
			for (int i = 1; i < m - 1;i++)
			{
				for (int j = 1;j < n - 1;j++)
				{
					NODE* node = findNode(board, i, j);
					if (node->c != ' ' && (int)node->c == 65 + k)
					{
						posCheck[count].x = node->pos.x;
						posCheck[count].y = node->pos.y;
						count++;
					}
				}
			}
			for (int i = 0;i < count - 1;i++)
			{
				for (int j = i + 1;j < count;j++)
				{
					if (check_2_pointList(posCheck[i], posCheck[j], board))
					{
						key1 = posCheck[i];
						key2 = posCheck[j];
						delete[] posCheck;
						return true;
					}
				}
			}
			delete[] posCheck;
		}
	}
	return false;
}


void renewMatrix_2(NODE** board, int m, int n, int occur[26])
{
	int temp[26];
	for (int i = 0;i < 26;i++)
	{
		temp[i] = occur[i];
	}
	for (int i = 1;i < m - 1;i++)
	{
		for (int j = 1;j < n - 1;j++)
		{
			NODE* node = findNode(board, i, j);
			if (node->c != ' ')
			{
				while (1)
				{
					int index = rand() % 26;
					if (temp[index] != 0)
					{
						node->c = (char)(index + 65);
						temp[index]--;
						break;
					}
				}
			}
		}
	}
}

void moveSuggestion_2(NODE** board, point key1, point key2, int& lifeline)
{
	if (key1.x > 0 && key1.y > 0 && key2.x > 0 && key2.y > 0)
	{
		if (lifeline)
		{
			NODE* pos1 = findNode(board, key1.y, key1.x);
			NODE* pos2 = findNode(board, key2.y, key2.x);
			drawLifelineCell_2(pos1);
			drawLifelineCell_2(pos2);
			Sleep(500);
			drawCell_2(pos1);
			drawCell_2(pos2);
			lifeline--;
		}
		else
		{
			TextColor(12);
			goToXY(20, 2);
			cout << "You have used all lifelines";
			Sleep(1000);
			TextColor(7);
			goToXY(20, 2);
			cout << "                           ";
		}
	}
}

bool findNearest_Cell_2(NODE** board, int m, int n, point& curr)
{
	int up = curr.y - 1;
	int down = curr.y + 1;
	int left = curr.x - 1;
	int right = curr.x + 1;
	while (up > 0 || down < m - 1 || left > 0 || right < n - 1)
	{
		NODE* node = NULL;
		if (up > 0)
		{
			node = findNode(board, up, curr.x);
			if (node->c != ' ')
			{
				curr.y = up;
				return 1;
			}
		}
		if (down < m - 1)
		{
			node = findNode(board, down, curr.x);
			if (node->c != ' ')
			{
				curr.y = down;
				return 1;
			}
		}
		if (left > 0)
		{
			node = findNode(board, curr.y, left);
			if (node->c != ' ')
			{
				curr.x = left;
				return 1;
			}
		}
		if (right < n - 1 && board[curr.y][right].c != ' ')
		{
			node = findNode(board, curr.y, right);
			if (node->c != ' ')
			{
				curr.x = right;
				return 1;
			}
		}

		for (int i = up; i <= down;i++)
		{
			if (i != curr.y && i > 0 && i < m - 1)
			{
				node = findNode(board, i, left);
				if (node->c != ' ')
				{
					curr.y = i;
					curr.x = left;
					return 1;
				}
				node = findNode(board, i, right);
				if (node->c != ' ')
				{
					curr.y = i;
					curr.x = right;
					return 1;
				}
			}
		}
		for (int i = left;i <= right;i++)
		{
			if (i != curr.x && i > 0 && i < n - 1)
			{
				node = findNode(board, up, i);
				if (node->c != ' ')
				{
					curr.x = i;
					curr.y = up;
					return 1;
				}
				node = findNode(board, down, i);
				if (node->c != ' ')
				{
					curr.x = i;
					curr.y = down;
					return 1;
				}
			}
		}
		if (up > 0) up--;
		if (down < m - 1) down++;
		if (left > 0) left--;
		if (right < n - 1) right++;
	}
	return 0;
}

bool check_draw_2(NODE** board, int m, int n, point& posSelected1, point& posSelected2, int occur[26], point& curr)
{
	bool check = false;
	if (check_2_pointList(posSelected1, posSelected2, board))
	{
		NODE* pos1 = findNode(board, posSelected1.y, posSelected1.x);
		drawSelectedCell_2(pos1, 1);
		NODE* pos2 = findNode(board, posSelected2.y, posSelected2.x);
		drawSelectedCell_2(pos2, 1);
		occur[(int)pos1->c - 65] -= 2;
		Sleep(200);
		checkAndDeleteNode(board, m, n, posSelected1, posSelected2);
		NODE* node = findNode(board, curr.y, curr.x);
		if (node->c != ' ')
		{
			node->isCurr = 1;
			drawCell_2(node);
		}
		else
		{
			if (findNearest_Cell_2(board, m, n, curr))
			{
				node = findNode(board, curr.y, curr.x);
				node->isCurr = 1;
				drawCell_2(node);
			}
			else
			{
				curr.x = -1;
				curr.y = -1;
			}
		}
		
		check = true;
	}
	else
	{
		NODE* pos1 = findNode(board, posSelected1.y, posSelected1.x);
		drawSelectedCell_2(pos1, 0);
		NODE* pos2 = findNode(board, posSelected2.y, posSelected2.x);
		drawSelectedCell_2(pos2, 0);
		Sleep(200);
		pos1->isSelected = 0;
		pos2->isSelected = 0;
		drawCell_2(pos1);
		drawCell_2(pos2);
		check = false;
	}
	posSelected1 = { -1,-1 };
	posSelected2 = { -1,-1 };

	return check;
}