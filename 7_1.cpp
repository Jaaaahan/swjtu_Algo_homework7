/*
数独游戏是在9*9的方格中填放1~9的数字，要求每一行、每一列以及3*3的方格中的数字均不能相同，如下图所示。
1	4	3	6	2	8	5	7	9
5	7	2	1	3	9	4	6	8
9	8	6	7	5	4	2	3	1
3	9	1	5	4	2	7	8	6
4	6	8	9	1	7	3	5	2
7	2	5	8	6	3	9	1	4
2	3	7	4	8	1	6	9	5
6	1	9	2	7	5	8	4	3
8	5	4	3	9	6	1	2	7
现方格中某些数字为空缺（用0表示），希望你编写程序能够将空缺的数字补齐。
输入要求：
输入包含9行，每一行包含9个数字，对应每个方格中的数字，0表示该方格的数字为空。
输出要求：
输出为9行，每行9个数字，也就是补齐后的9*9的方格中的数字。
样例输入：
103000509
002109400
000704000
300502006
060000050
700803004
000401000
009205800
804000107
样例输出：
143628579
572139468
986754231
391542786
468917352
725863914
237481695
619275843
854396127

*/

#include <iostream>
#include <vector>

using namespace std;

bool isValid(const vector<vector<int>>& board, int row, int col, int num) {
    for (int x = 0; x < 9; x++) {
        if (board[row][x] == num 
        || board[x][col] == num 
        || board[3 * (row / 3) + x / 3][3 * (col / 3) + x % 3] == num) {
            return false;
        }
    }
    return true;
}

bool solveSudoku(vector<vector<int>>& board, int row, int col) {
    if (row == 9) {
        return true; // 如果到达了第9行，说明已经填完了所有的格子
    }
    if (col == 9) {
        return solveSudoku(board, row + 1, 0); // 换到下一行的第一个格子
    }
    if (board[row][col] != 0) {
        return solveSudoku(board, row, col + 1); // 跳过已经填好的格子
    }

    for (int num = 1; num <= 9; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num; // 尝试填入数字
            if (solveSudoku(board, row, col + 1)) {
                return true; // 如果成功填完，返回true
            }
            board[row][col] = 0; // 否则回溯
        }
    }
    return false; // 如果所有数字都不能填入，返回false
}

int main() {
    vector<vector<int>> board(9, vector<int>(9));
    char a;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> a;
            board[i][j] = a - '0';
        }
    }
    if (solveSudoku(board, 0, 0)) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << board[i][j];
            }
            cout << endl;
        }
    } else {
        cout << "No solution exists" << endl;
    }
    
    return 0;
}
