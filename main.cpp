#include <iostream>
#include <cstdlib>
#include <time.h>
#include "AI.hpp"

using namespace std;

int board[3][3][3] = {0};
int x, y, z; // hold the last place played
void displayBoard();
bool getTurn() {return true;}
void getPlayerMove();
void getAImove();
bool validate();
int checkWin();

int main()
{
    srand (time(NULL));
    cout << "Welcome to 3D tic-tac-toe\n";
    displayBoard();
    if (getTurn()) {
        getPlayerMove();
        displayBoard();
    }
    int cont = 0;
    do {
        getAImove();
        displayBoard();
        cont = checkWin();
        if (cont == 2) {
            cout << "AI won.\n";
            break; // breaks from the do while
        }
        getPlayerMove();
        displayBoard();
        cont = checkWin();
        if (cont == 1) {
            cout << "You won!\n";
        }
    }
    while (cont == 0);

    return 0;
}


void displayBoard() {
    for (int i=2; i>-1; i--) {
        for (int j=0; j<3; j++) {
            for (int k=0; k<3; k++) {
                cout << board[k][j][i];
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << "-----------\n";
}
void getPlayerMove() {
    cout << "Enter 2 numbers to pick a spot:";
    cin >> x;
    cin >> y;
    while (!validate()) {
        cout << "Invalid play, try again:";
        cin >> x;
        cin >> y;
    }
    --x;
    --y;
    if (board[x][y][0] == 0) {z = 0;}
    else if (board[x][y][1] == 0) {z = 1;}
    else {z = 2;}
    board[x][y][z] = 1;
}

bool validate() {
    if (board[x-1][y-1][2] != 0) return false; // if spot all full, return false
    return (x == 1 || x == 2 || x == 3) && (y == 1 || y == 2 || y == 3);
}

void getAImove() {
    bool brk = false;
    // check priority 1
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (checkPriority12(2,i,j,board)) {
                x = i;
                y = j;
                brk = true;
                break; // break from inner loop
            }
        }
        if (brk) break; // break from outer loop
    }
    if (!brk) { // if no 1s, check priority 2
        brk = false;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (checkPriority12(1,i,j,board)) {
                    x = i;
                    y = j;
                    brk = true;
                    break; // break from inner loop
                }
            }
            if (brk) break; // break from outer loop
        }
    }
    if (!brk) { // if no 2s, check priority 3 and 4
        brk = false;
        int set_ups = 0;
        int pri3[2] = {-1,-1};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                set_ups = checkPriority34(i,j,board);
                if (set_ups > 1) { // if priority 3, break put of loops
                    x = i;
                    y = j;
                    brk = true;
                    break; // break from inner loop
                }
                if (set_ups == 1) { // if priority 4, save it and continue to look for a priority 3
                    pri3[0] = i;
                    pri3[1] = j;
                }
            }
            if (brk) break; // break from outer loop
        }
        if (!brk) { // if no 3s, check priority 4
            if (pri3[0] != -1) {
                x = pri3[0];
                y = pri3[1];
                brk = true;
            }
        }
    }
    if (!brk) { // if no priorities 1-4, choose a random spot
        x = rand() % 3;
        y = rand() % 3;
        while (board[x][y][2] != 0) {
            x = rand() % 3;
            y = rand() % 3;
        }
    }
    if (board[x][y][0] == 0) {z = 0;}
    else if (board[x][y][1] == 0) {z = 1;}
    else {z = 2;}
    board[x][y][z] = 2;
}

int checkWin() { // returns 0 for no win, 1 for player, 2 for AI, (and 3 for board full?)
    int in_a_row = 0;
    int winner = board[x][y][z]; // winner will be 1 or 2
    // check win in x direction
    for (int i = 0; i < 3; i++) {
        if (board[i][y][z] == winner)
            ++in_a_row;
    }
    if (in_a_row == 3) return winner;
    // check win in y direction
    in_a_row = 0;
    for (int i = 0; i < 3; i++) {
        if (board[x][i][z] == winner)
            ++in_a_row;
    }
    if (in_a_row == 3) return winner;
    in_a_row = 0;
    // check win in y direction
    for (int i = 0; i < 3; i++) {
        if (board[x][y][i] == winner)
            ++in_a_row;
    }
    if (in_a_row == 3) return winner;
    in_a_row = 0;
    // check win in xy diagonals if spot is on that diagonal
    if (x == y) { // if on first diagonal
        for (int i = 0; i < 3; i++) {
            if (board[i][i][z] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return winner;
        in_a_row = 0;
    }
    if (x + y == 2) { // if on the second diagonal
        for (int i = 0; i < 3; i++) {
            if (board[i][2-i][z] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return winner;
        in_a_row = 0;
    }
    // check win in xz diagonals if spot is on that diagonal
    if (x == z) { // if on first diagonal
        for (int i = 0; i < 3; i++) {
            if (board[i][y][i] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return winner;
        in_a_row = 0;
    }
    if (x + z == 2) { // if on the second diagonal
        for (int i = 0; i < 3; i++) {
            if (board[i][y][2-i] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return winner;
        in_a_row = 0;
    }
    // check win in yz diagonals if spot is on that diagonal
    if (y == z) { // if on first diagonal
        for (int i = 0; i < 3; i++) {
            if (board[x][i][i] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return winner;
        in_a_row = 0;
    }
    if (y + z == 2) { // if on the second diagonal
        for (int i = 0; i < 3; i++) {
            if (board[x][2-i][i] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return winner;
        in_a_row = 0;
    }
    // check win in the 4 xyz diagonals, if on those diagonals
    if (x == y && x == z) { // if on the (0,0,0) to (2,2,2) diagonal
        for (int i = 0; i < 3; i++) {
            if (board[i][i][i] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return winner;
        in_a_row = 0;
    }
    if (x + y == 2 && y == z) { // if on the (2,0,0) to (0,2,2) diagonal
        for (int i = 0; i < 3; i++) {
            if (board[2-i][i][i] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return winner;
        in_a_row = 0;
    }
    if (x + y == 2 && x == z) { // if on the (0,2,0) to (2,0,2) diagonal
        for (int i = 0; i < 3; i++) {
            if (board[i][2-i][i] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return winner;
        in_a_row = 0;
    }
    if (x + z == 2 && x == y) { // if on the (0,0,2) to (2,2,0) diagonal
        for (int i = 0; i < 3; i++) {
            if (board[i][i][2-i] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return winner;
    }
    return 0;
}
