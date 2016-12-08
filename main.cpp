// Written by Lydia White and Alex Bartram

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "AI.hpp"
#include <omp.h>

using namespace std;

const int SIZE = 3;
const int threadNum = 3;

int board[SIZE*SIZE*SIZE] = {0};
/* NOTE: I started this program using a 3D array for board,
** but had to change to a 1D array so I could easily change the size.
** This is why I have x,y,z instead of just one value, 
** though it makes getting values from the board confusing */
int x, y, z; // hold the last place played
void displayBoard();
void getPlayerMove();
void getAImove();
bool validate();
int checkWin();

int main()
{
    srand (time(NULL));
    cout << "Welcome to 3D tic-tac-toe\n";
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
    for (int i=0; i<SIZE*SIZE*SIZE; i++) {
        if (board[i] == 1) cout << " X ";
        else if (board[i] == 2) cout << " O ";
        else cout << "   ";
        if (i%SIZE<SIZE-1) cout << '|';
        else if (i%(SIZE*SIZE)<SIZE*SIZE-1) {
            cout << endl << "---";
            for (int j=0; j<SIZE-1; j++)
                cout << "+---";
            cout << endl;
        }
        else cout << endl << endl;
    }
    cout << "~~~~~~~~~~~~~~~~~~\n";
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
    z = 0;
    for (int i = SIZE-1; i>0; i--) {
        if (board[x+SIZE*(y+SIZE*i)] == 0) {z = i; break;}
    }
    board[x+SIZE*(y+SIZE*z)] = 1;
}

bool validate() {
    if (board[x-1+SIZE*(y-1)] != 0) return false; // if spot all full, return false
    return (x > 0 && x <= SIZE) && (y > 0 && y <= SIZE);
}

void getAImove() {
    // get priorities for each spot and record the highest priority
    int p = 7; // which priority is highest
    int n = 0; // how many of that priority there is
    int priorities[SIZE*SIZE];

    // time decisions
    clock_t startTime, endTime;
    startTime = clock();

    # pragma omp parallel for num_threads(threadNum)
	for (int j=0; j<SIZE*SIZE; j++) {
		priorities[j] = getPriority(j%SIZE, j/SIZE, board, SIZE);
		if (priorities[j] < p) {
			p = priorities[j];
			n = 1;
		}
		else if (priorities[j] == p) ++n;
	}
	
    endTime = clock();
    cout << "Time: " << (double)(endTime - startTime)/CLOCKS_PER_SEC << endl;

    int choice = rand() % n; // choose randomly between spots of the highest priority
    for (int i=0; i<SIZE*SIZE; i++) {
        if (priorities[i] == p) {
            if (choice == 0) {
                x = i%SIZE;
                y = i/SIZE;
                break;
            }
            else --choice;
        }
    }

    // place choice on board;
    z = 0;
    for (int i = SIZE-1; i>0; i--) {
        if (board[x+SIZE*(y+SIZE*i)] == 0) {z = i; break;}
    }
    board[x+SIZE*(y+SIZE*z)] = 2;
}

int checkWin() { // returns 0 for no win, 1 for player, 2 for AI, (and 3 for board full?)
    int in_a_row = 0;
    int winner = board[x+SIZE*(y+SIZE*z)]; // winner will be 1 or 2
    // check win in x direction
    for (int i = 0; i < SIZE; i++) {
        if (board[i+SIZE*(y+SIZE*z)] == winner)
            ++in_a_row;
    }
    if (in_a_row == SIZE) return winner;
    // check win in y direction
    in_a_row = 0;
    for (int i = 0; i < SIZE; i++) {
        if (board[x+SIZE*(i+SIZE*z)] == winner)
            ++in_a_row;
    }
    if (in_a_row == SIZE) return winner;
    in_a_row = 0;
    // check win in y direction
    for (int i = 0; i < SIZE; i++) {
        if (board[x+SIZE*(y+SIZE*i)] == winner)
            ++in_a_row;
    }
    if (in_a_row == SIZE) return winner;
    in_a_row = 0;
    // check win in xy diagonals if spot is on that diagonal
    if (x == y) { // if on first diagonal
        for (int i = 0; i < SIZE; i++) {
            if (board[i+SIZE*(i+SIZE*z)] == winner)
                ++in_a_row;
        }
        if (in_a_row == SIZE) return winner;
        in_a_row = 0;
    }
    if (x + y == SIZE-1) { // if on the second diagonal
        for (int i = 0; i < SIZE; i++) {
            if (board[i+SIZE*(SIZE-1-i+SIZE*z)] == winner)
                ++in_a_row;
        }
        if (in_a_row == SIZE) return winner;
        in_a_row = 0;
    }
    // check win in xz diagonals if spot is on that diagonal
    if (x == z) { // if on first diagonal
        for (int i = 0; i < SIZE; i++) {
            if (board[i+SIZE*(y+SIZE*i)] == winner)
                ++in_a_row;
        }
        if (in_a_row == SIZE) return winner;
        in_a_row = 0;
    }
    if (x + z == SIZE-1) { // if on the second diagonal
        for (int i = 0; i < SIZE; i++) {
            if (board[i+SIZE*(y+SIZE*(SIZE-1-i))] == winner)
                ++in_a_row;
        }
        if (in_a_row == SIZE) return winner;
        in_a_row = 0;
    }
    // check win in yz diagonals if spot is on that diagonal
    if (y == z) { // if on first diagonal
        for (int i = 0; i < SIZE; i++) {
            if (board[x+SIZE*(i+SIZE*i)] == winner)
                ++in_a_row;
        }
        if (in_a_row == SIZE) return winner;
        in_a_row = 0;
    }
    if (y + z == SIZE-1) { // if on the second diagonal
        for (int i = 0; i < SIZE; i++) {
            if (board[x+SIZE*(SIZE-1-i+SIZE*(SIZE-1-i))] == winner)
                ++in_a_row;
        }
        if (in_a_row == SIZE) return winner;
        in_a_row = 0;
    }
    // check win in the 4 xyz diagonals, if on those diagonals
    if (x == y && x == z) { // if on the (0,0,0) to (2,2,2) diagonal
        for (int i = 0; i < SIZE; i++) {
            if (board[i+SIZE*(i+SIZE*i)] == winner)
                ++in_a_row;
        }
        if (in_a_row == SIZE) return winner;
        in_a_row = 0;
    }
    if (x + y == SIZE-1 && y == z) { // if on the (2,0,0) to (0,2,2) diagonal
        for (int i = 0; i < SIZE; i++) {
            if (board[SIZE-1-i+SIZE*(i+SIZE*i)] == winner)
                ++in_a_row;
        }
        if (in_a_row == SIZE) return winner;
        in_a_row = 0;
    }
    if (x + y == SIZE-1 && x == z) { // if on the (0,2,0) to (2,0,2) diagonal
        for (int i = 0; i < SIZE; i++) {
            if (board[i+SIZE*(SIZE-1-i+SIZE*i)] == winner)
                ++in_a_row;
        }
        if (in_a_row == SIZE) return winner;
        in_a_row = 0;
    }
    if (x + z == SIZE-1 && x == y) { // if on the (0,0,2) to (2,2,0) diagonal
        for (int i = 0; i < SIZE; i++) {
            if (board[i+SIZE*(i+SIZE*(SIZE-1-i))] == winner)
                ++in_a_row;
        }
        if (in_a_row == SIZE) return winner;
    }
    return 0;
}
