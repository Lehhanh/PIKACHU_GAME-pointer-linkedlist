#include "Check_Normal.h"

using namespace std;
bool first_check(point p1, point p2, CELL** board)
{
    if ((p1.x == p2.x && p1.y == p2.y) || board[p1.y][p1.x].c != board[p2.y][p2.x].c) //same position or different character
        return false;
    return true;
}


bool checkColumn(int y1, int y2, int x, CELL** board) 
{
    int min = y1;
    int max = y2;

    if (y1 > y2) {
        min = y2;
        max = y1;
    }

    for (int y = min; y < max; y++) {
        if (y > min && board[y][x].c != ' ') {
            return false;
        }
    }

    return true;
}

bool checkRow(int x1, int x2, int y, CELL** board) 
{
    int min = x1;
    int max = x2;

    if (x1 > x2) {
        min = x2;
        max = x1;
    }

    for (int x = min; x < max; x++) {
        if (x > min && board[y][x].c != ' ') {
            return false;
        }
    }

    return true;
}



bool checkIMatching(point p1, point p2, CELL** board) 
{
    if (p1.x == p2.x) {     // same column
        return checkColumn(p1.y, p2.y, p1.x, board);
    }
    else if (p1.y == p2.y) {    // same row
        return checkRow(p1.x, p2.x, p1.y, board);
    }

    return false;
}


bool checkZ_LRow(point p1, point p2, CELL** board) //HORIZONTALLY
{
    point min = p1;
    point max = p2;
    if (p1.x > p2.x)
    {
        min = p2;
        max = p1;
    }

    for (int i = min.x;i <= max.x;i++)
    {
        if (i > min.x && board[min.y][i].c != ' ')
            return false;
        if ((i < max.x && board[max.y][i].c == ' ') || i == max.x)
        {
            if (checkColumn(min.y, max.y, i, board) && checkRow(i, max.x, max.y, board))
                return true;
        }
    }
    return false;
}

bool checkZ_LColumn(point p1, point p2, CELL** board) //VERTICALLY
{
    point min = p1;
    point max = p2;
    if (p1.y > p2.y)
    {
        min = p2;
        max = p1;
    }

    for (int i = min.y;i <= max.y;i++)
    {
        if (i > min.y && board[i][min.x].c != ' ')
            return false;
        if ((i < max.y && board[i][max.x].c == ' ') || i == max.y)
        {
            if (checkRow(min.x, max.x, i, board) && checkColumn(i, max.y, max.x, board))
                return true;
        }
    }
    return false;
}

bool checkZ_L_Matching(point p1, point p2, CELL** board)
{
    if (checkZ_LRow(p1, p2, board) || checkZ_LColumn(p1, p2, board))
        return true;
    return false;
}


// direction = 1 is check right, direction  = -1 is check left
bool checkUColumn(point p1, point p2, CELL** board, int direction) 
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

    if (direction == -1) {
        col = min.x + direction;
        row = max.y;
        endCol = min.x;
    }

    if ((board[row][endCol].c == ' ' || min.x == max.x)
        && checkRow(min.x, max.x, row, board)) {
        while (board[min.y][col].c == ' ' && board[max.y][col].c == ' ') 
        {
            if (checkColumn(min.y, max.y, col, board)) 
            {
                return true;
            }
            col += direction;
        }
    }

    return false;
}

// direction = 1 is check down, direction  = -1 is check up
bool checkURow(point p1, point p2, CELL** board, int direction) 
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

    if ((board[endRow][col].c == ' ' || min.y == max.y)
        && checkColumn(min.y, max.y, col, board)) {
        while (board[row][min.x].c == ' ' && board[row][max.x].c == ' ') 
        {
            if (checkRow(min.x, max.x, row, board)) 
            {
                return true;
            }
            row += direction;
        }
    }

    return false;
}

bool checkUMatching(point p1, point p2, CELL** board) {

    if (checkUColumn(p1, p2, board, 1)
        || checkUColumn(p1, p2, board, -1)
        || checkURow(p1, p2, board, 1)
        || checkURow(p1, p2, board, -1)) {
        return true;
    }

    return false;
}
bool check_2_point(point p1, point p2, CELL** board)
{
    if (!first_check(p1, p2, board))
        return false;
    if (checkIMatching(p1, p2, board))
        return true;
    if (checkZ_L_Matching(p1, p2, board))
        return true;
    if (checkUMatching(p1, p2, board))
        return true;
    return false;
}




bool checkValidMatrix(CELL** board, int m, int n, point& key1, point& key2, int occur[26])
{
    key1 = { -1, -1 };
    key2 = { -1, -1 };
    for (int k = 0;k < 26;k++)
    {
        if (occur[k] != 0)
        {
            point* posCheck = new point[occur[k]];
            int count = 0;
            for (int i = 1;i < m - 1;i++)
            {
                for (int j = 1;j < n - 1;j++)
                {
                    if (board[i][j].c != ' ' && (int)board[i][j].c == 65 + k)
                    {
                        posCheck[count].x = board[i][j].pos.x;
                        posCheck[count].y = board[i][j].pos.y;
                        count++;
                    }
                }
            }
            for (int i = 0;i < count - 1;i++)
            {
                for (int j = i + 1;j < count;j++)
                {
                    if (check_2_point(posCheck[i], posCheck[j], board))
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

//SHUFFLE MATRIX
void renewMatrix(CELL** board, int m, int n, int occur[26])
{
    int temp[26];
    for (int i = 0;i < 26;i++)
    {
        temp[i] = occur[i];
    }
    for (int i = 1;i < m - 1;i++)
    {
        for (int j = 1; j < n - 1;j++)
        {
            if (board[i][j].c != ' ')
            {
                while (1)
                {
                    int index = rand() % 26;
                    if (temp[index] != 0)
                    {
                        board[i][j].c = (char)(index + 65);
                        temp[index] --;
                        break;
                    }
                }
            }
        }
    }
}

void moveSuggestion(CELL** board, point key1, point key2, int& lifeline)
{
    if (key1.x > 0 && key1.y > 0 && key2.x > 0 && key2.y > 0)
    {
        if (lifeline)
        {
            drawLifelineCell_1(board[key1.y][key1.x]);
            drawLifelineCell_1(board[key2.y][key2.x]);
            Sleep(500);
            drawCell_1(board[key1.y][key1.x]);
            drawCell_1(board[key2.y][key2.x]);
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



bool findNearest_Cell(CELL** board, int m, int n, point& curr)
{
    int up = curr.y - 1;
    int down = curr.y + 1;
    int left = curr.x - 1;
    int right = curr.x + 1;
    while (up > 0 || down < m - 1 || left > 0 || right < n - 1)
    {
        if (up > 0 && board[up][curr.x].c != ' ')
        {
            curr.y = up;
            return 1;
        }
        if (down < m - 1 && board[down][curr.x].c != ' ')
        {
            curr.y = down;
            return 1;
        }
        if (left > 0 && board[curr.y][left].c != ' ')
        {
            curr.x = left;
            return 1;
        }
        if (right < n - 1 && board[curr.y][right].c != ' ')
        {
            curr.x = right;
            return 1;
        }

        for (int i = up; i <= down;i++)
        {
            if (i != curr.y && i > 0 && i < m - 1)
            {
                if (board[i][left].c != ' ')
                {
                    curr.y = i;
                    curr.x = left;
                    return 1;
                }
                else if (board[i][right].c != ' ')
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
                if (board[up][i].c != ' ')
                {
                    curr.x = i;
                    curr.y = up;
                    return 1;
                }
                else if (board[down][i].c != ' ')
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
bool check_draw(CELL** board, int m, int n, point& curr, point& posSelected1, point& posSelected2, int occur[26], char bg[16][40])
{
    bool check = false;
    if (check_2_point(posSelected1, posSelected2, board))
    {
        occur[(int)board[posSelected1.y][posSelected1.x].c - 65] -= 2;
        drawSelectedCell_1(board[posSelected1.y][posSelected1.x], 1);
        drawSelectedCell_1(board[posSelected2.y][posSelected2.x], 1);
        Sleep(200);
        board[posSelected1.y][posSelected1.x].c = ' ';
        board[posSelected2.y][posSelected2.x].c = ' ';
        board[posSelected1.y][posSelected1.x].isSelected = 0;
        board[posSelected2.y][posSelected2.x].isSelected = 0;
        deleteCell_1(board[posSelected1.y][posSelected1.x]);
        deleteCell_1(board[posSelected2.y][posSelected2.x]);
        board[curr.y][curr.x].isCurr = 0;
        if (findNearest_Cell(board, m, n, curr))
        {
            board[curr.y][curr.x].isCurr = 1;
            drawCell_1(board[curr.y][curr.x]);
        }
        else
        {
            curr.x = -1;
            curr.y = -1;
        }

        if (posSelected1.x <= 5 && posSelected1.y <= 4)
            displayBG(bg, posSelected1.x, posSelected1.y);
        if (posSelected2.x <= 5 && posSelected2.y <= 4)
            displayBG(bg, posSelected2.x, posSelected2.y);


        if (posSelected1.x + 1 < n - 1 && board[posSelected1.y][posSelected1.x + 1].c != ' ')
            drawCell_1(board[posSelected1.y][posSelected1.x + 1]);
        if (posSelected1.x - 1 > 0 && board[posSelected1.y][posSelected1.x - 1].c != ' ')
            drawCell_1(board[posSelected1.y][posSelected1.x - 1]);
        if (posSelected1.y + 1 < m - 1 && board[posSelected1.y + 1][posSelected1.x].c != ' ')
            drawCell_1(board[posSelected1.y + 1][posSelected1.x]);
        if (posSelected1.y - 1 > 0 && board[posSelected1.y - 1][posSelected1.x].c != ' ')
            drawCell_1(board[posSelected1.y - 1][posSelected1.x]);



        if (posSelected2.x + 1 < n - 1 && board[posSelected2.y][posSelected2.x + 1].c != ' ')
            drawCell_1(board[posSelected2.y][posSelected2.x + 1]);
        if (posSelected2.x - 1 > 0 && board[posSelected2.y][posSelected2.x - 1].c != ' ')
            drawCell_1(board[posSelected2.y][posSelected2.x - 1]);
        if (posSelected2.y + 1 < m - 1 && board[posSelected2.y + 1][posSelected2.x].c != ' ')
            drawCell_1(board[posSelected2.y + 1][posSelected2.x]);
        if (posSelected2.y - 1 > 0 && board[posSelected2.y - 1][posSelected2.x].c != ' ')
            drawCell_1(board[posSelected2.y - 1][posSelected2.x]);

        check = true;
    }
    else
    {
        drawSelectedCell_1(board[posSelected1.y][posSelected1.x], 0);
        drawSelectedCell_1(board[posSelected2.y][posSelected2.x], 0);
        Sleep(200);
        board[posSelected1.y][posSelected1.x].isSelected = 0;
        board[posSelected2.y][posSelected2.x].isSelected = 0;
        drawCell_1(board[posSelected1.y][posSelected1.x]);
        drawCell_1(board[posSelected2.y][posSelected2.x]);

        check = false;
    }
    posSelected1 = { -1,-1 };
    posSelected2 = { -1,-1 };

    return check;
}