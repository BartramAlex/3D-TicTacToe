
// File for all the AI decision functions

bool checkPriority12(int winner, int x, int y, int mainBoard[3][3][3]) { // returns true if priority is 1, false if not

    int board[3][3][3];
    for (int i=2; i>-1; i--) {
        for (int j=0; j<3; j++) {
            for (int k=0; k<3; k++) {
                board[i][j][k] = mainBoard[i][j][k];
            }
        }
    }

    int z;
    if (board[x][y][0] == 0) {z = 0;}
    else if (board[x][y][1] == 0) {z = 1;}
    else {z = 2;}
    board[x][y][z] = winner;

    int in_a_row = 0;
    // check win in x direction
    for (int i = 0; i < 3; i++) {
        if (board[i][y][z] == winner)
            ++in_a_row;
    }
    if (in_a_row == 3) return true;
    // check win in y direction
    in_a_row = 0;
    for (int i = 0; i < 3; i++) {
        if (board[x][i][z] == winner)
            ++in_a_row;
    }
    if (in_a_row == 3) return true;
    in_a_row = 0;
    // check win in y direction
    for (int i = 0; i < 3; i++) {
        if (board[x][y][i] == winner)
            ++in_a_row;
    }
    if (in_a_row == 3) return true;
    in_a_row = 0;
    // check win in xy diagonals if spot is on that diagonal
    if (x == y) { // if on first diagonal
        for (int i = 0; i < 3; i++) {
            if (board[i][i][z] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return true;
        in_a_row = 0;
    }
    if (x + y == 2) { // if on the second diagonal
        for (int i = 0; i < 3; i++) {
            if (board[i][2-i][z] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return true;
        in_a_row = 0;
    }
    // check win in xz diagonals if spot is on that diagonal
    if (x == z) { // if on first diagonal
        for (int i = 0; i < 3; i++) {
            if (board[i][y][i] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return true;
        in_a_row = 0;
    }
    if (x + z == 2) { // if on the second diagonal
        for (int i = 0; i < 3; i++) {
            if (board[i][y][2-i] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return true;
        in_a_row = 0;
    }
    // check win in yz diagonals if spot is on that diagonal
    if (y == z) { // if on first diagonal
        for (int i = 0; i < 3; i++) {
            if (board[x][i][i] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return true;
        in_a_row = 0;
    }
    if (y + z == 2) { // if on the second diagonal
        for (int i = 0; i < 3; i++) {
            if (board[x][2-i][i] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return true;
        in_a_row = 0;
    }
    // check win in the 4 xyz diagonals, if on those diagonals
    if (x == y && x == z) { // if on the (0,0,0) to (2,2,2) diagonal
        for (int i = 0; i < 3; i++) {
            if (board[i][i][i] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return true;
        in_a_row = 0;
    }
    if (x + y == 2 && y == z) { // if on the (2,0,0) to (0,2,2) diagonal
        for (int i = 0; i < 3; i++) {
            if (board[2-i][i][i] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return true;
        in_a_row = 0;
    }
    if (x + y == 2 && x == z) { // if on the (0,2,0) to (2,0,2) diagonal
        for (int i = 0; i < 3; i++) {
            if (board[i][2-i][i] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return true;
        in_a_row = 0;
    }
    if (x + z == 2 && x == y) { // if on the (0,0,2) to (2,2,0) diagonal
        for (int i = 0; i < 3; i++) {
            if (board[i][i][2-i] == winner)
                ++in_a_row;
        }
        if (in_a_row == 3) return true;
    }
    return false;
}
