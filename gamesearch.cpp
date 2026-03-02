#include <iostream>
#include <limits.h>
using namespace std;

char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

char AI = 'X';
char HUMAN = 'O';

void printBoard() {
    cout << "\n";
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            cout << board[i][j];
            if(j<2) cout << " | ";
        }
        cout << "\n";
        if(i<2) cout << "--+---+--\n";
    }
    cout << "\n";
}

bool isMovesLeft() {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]==' ')
                return true;
    return false;
}

int evaluate() {
    // Rows
    for(int row=0; row<3; row++) {
        if(board[row][0]==board[row][1] &&
           board[row][1]==board[row][2]) {
            if(board[row][0]==AI) return 10;
            if(board[row][0]==HUMAN) return -10;
        }
    }

    // Columns
    for(int col=0; col<3; col++) {
        if(board[0][col]==board[1][col] &&
           board[1][col]==board[2][col]) {
            if(board[0][col]==AI) return 10;
            if(board[0][col]==HUMAN) return -10;
        }
    }

    // Diagonals
    if(board[0][0]==board[1][1] &&
       board[1][1]==board[2][2]) {
        if(board[0][0]==AI) return 10;
        if(board[0][0]==HUMAN) return -10;
    }

    if(board[0][2]==board[1][1] &&
       board[1][1]==board[2][0]) {
        if(board[0][2]==AI) return 10;
        if(board[0][2]==HUMAN) return -10;
    }

    return 0;
}

int minimax(bool isMax) {
    int score = evaluate();

    if(score == 10 || score == -10)
        return score;

    if(!isMovesLeft())
        return 0;

    if(isMax) {
        int best = INT_MIN;

        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(board[i][j]==' ') {
                    board[i][j] = AI;
                    best = max(best, minimax(false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;

        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(board[i][j]==' ') {
                    board[i][j] = HUMAN;
                    best = min(best, minimax(true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

void findBestMove() {
    int bestVal = INT_MIN;
    int bestRow = -1, bestCol = -1;

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(board[i][j]==' ') {
                board[i][j] = AI;
                int moveVal = minimax(false);
                board[i][j] = ' ';

                if(moveVal > bestVal) {
                    bestRow = i;
                    bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    board[bestRow][bestCol] = AI;
}

int main() {
    int row, col;

    while(true) {
        printBoard();

        cout << "Enter row and column (0-2): ";
        cin >> row >> col;

        if(board[row][col] == ' ')
            board[row][col] = HUMAN;
        else {
            cout << "Invalid move!\n";
            continue;
        }

        if(evaluate() == -10 || !isMovesLeft())
            break;

        findBestMove();

        if(evaluate() == 10 || !isMovesLeft())
            break;
    }

    printBoard();

    int finalScore = evaluate();
    if(finalScore == 10)
        cout << "AI Wins!\n";
    else if(finalScore == -10)
        cout << "Human Wins!\n";
    else
        cout << "Draw!\n";

    return 0;
}