#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE] = {{' ', ' ', ' ',}, {' ', ' ', ' ',}, {' ', ' ', ' '}  };
char currentPlayer = 'X';
int playerXWins = 0;
int playerOWins = 0;
int draws = 0;
bool isAI = true; // Set to false for two-player mode
stack<pair<int, int>> moves;

void displayBoard() {
    cout << "Current board:\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j];
            if (j < SIZE - 1) cout << " | ";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "---------\n";
    }
}

bool checkWin() {
    for (int i = 0; i < SIZE; ++i) {
        if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer ) return true;
        if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer  ) return true;
    }
    if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer ) return true;
    if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer ) return true;

    return false;
}

bool checkDraw() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

void updateScore() {
    if (checkWin()) {
        if (currentPlayer == 'X') playerXWins++;
        else playerOWins++;
    } else if (checkDraw()) {
        draws++;
    }
}

void displayScore() {
    cout << "Scores:\n";
    cout << "Player X: " << playerXWins << endl;
    cout << "Player O: " << playerOWins << endl;
    cout << "Draws: " << draws << endl;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void aiMove() {
    srand(time(0));
    int row, col;
    while (true) {
        row = rand() % SIZE;
        col = rand() % SIZE;
        if (board[row][col] == ' ') {
            board[row][col] = currentPlayer;
            moves.push({row, col});
            break;
        }
    }
}

void makeMove() {
    if (isAI && currentPlayer == 'O') {
        aiMove();
    } else {
        int row, col;
        while (true) {
            cout << "Player " << currentPlayer << ", enter row and column (0, 1, 2, 3): ";
            cin >> row >> col;
            if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') {
                board[row][col] = currentPlayer;
                moves.push({row, col});
                break;
            } else {
                cout << "Invalid move. Try again." << endl;
            }
        }
    }
}

void undoMove() {
    if (!moves.empty()) {
        pair<int, int> lastMove = moves.top();
        moves.pop();
        board[lastMove.first][lastMove.second] = ' ';
        switchPlayer();
    } else {
        cout << "No moves to undo!" << endl;
    }
}

int main() {
    cout << "Welcome to Tic-Tac-Toe!\n";
    while (true) {
        displayBoard();
        displayScore();
        makeMove();
        if (checkWin()) {
            displayBoard();
            updateScore();
            cout << "Player " << currentPlayer << " wins!\n";
            break;
        }
        if (checkDraw()) {
            displayBoard();
            updateScore();
            cout << "The game is a draw!\n";
            break;
        }
        switchPlayer();
    }
    return 0;
}
