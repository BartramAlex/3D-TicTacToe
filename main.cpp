#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int board[3][3][3] = {0};
void displayBoard();
bool getTurn() {return true;}
void getPlayerMove();
bool validate(int x, int y);
void getAImove();

int main()
{
    srand (time(NULL));
    cout << "Welcome to 3D tic-tac-toe\n";
    displayBoard();
    if (getTurn()) {
        getPlayerMove();
        displayBoard();
    }
    bool cont = true;
    do {
        getAImove();
        displayBoard();
        getPlayerMove();
        displayBoard();
    }
    while (cont);

    cout << "Hello world!" << endl;
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
    int x, y;
    cin >> x;
    cin >> y;
    while (!validate(x,y)) {
        cout << "Invalid play, try again:";
        cin >> x;
        cin >> y;
    }
    --x;
    --y;
    if (board[x][y][0] == 0) {board[x][y][0] = 1;}
    else if (board[x][y][1] == 0) {board[x][y][1] = 1;}
    else {board[x][y][2] = 1;}
}

bool validate(int x, int y) {
    if (board[x-1][y-1][2] != 0) return false; // if spot all full, return false
    return (x == 1 || x == 2 || x == 3) && (y == 1 || y == 2 || y == 3);
}

void getAImove() {
    int x = rand() % 3;
    int y = rand() % 3;
    if (!validate(x,y)) {
        int x = rand() % 3;
        int y = rand() % 3;
    }
    if (board[x][y][0] == 0) {board[x][y][0] = 2;}
    else if (board[x][y][1] == 0) {board[x][y][1] = 2;}
    else {board[x][y][2] = 2;}
}
