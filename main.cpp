#include <iostream>
#include <limits>
using namespace std;

char board[5][7];

void ClearBoard() {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 7; j++)
            board[i][j] = '0';
}

void DisplayBoard() {
    cout << "\n===============================\n";
    for (int i = 0; i < 7; i++) {
        cout << " | " <<  i + 1;
    }

    cout << " |\n===============================\n";
    for (int i = 0; i < 5; i++) {
        cout << " | ";
        for (int j = 0; j < 7; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n";
    } 
    cout << "===============================\n";
}

bool validateInput() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input. please try again.. \n";
        return false;
    }
    return true;
}

class Player {
    public:
        char color;
        int column;

        Player(char c) : color (c), column(-1) {}
        
        int chooseColumn() {
            do {
                cout << "\nEnter your column (1-7): ";
                cin >> column;
                if (!validateInput()) continue;
            } while (column < 1 || column > 7 || board[0][column - 1] != '0');
            return column - 1;
        }

        void makeMove() {
            int col = chooseColumn();
            for (int i = 4; i >= 0; i--) {
                if (board[i][col] == '0') {
                    board[i][col] = color;
                    break;
                }
            }
        }
};

class Computer {
    public:
        char color;

        Computer(char c) : color (c) {}

        void makeMove() {
            int col;
            do {
                col = rand() % 7;
            } while (board[0][col] != '0');

            for (int i = 4; i >= 0; i--) {
                if (board[i][col] == '0') {
                    board[i][col] = color;
                    break;
                }
            }
            cout << "\nComputer placed a piece in column " << col + 1 << "\n";
        }
};

class Game {
    Player player;
    Computer computer;

    bool checkWin(char color) {
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 4; j++)
                if (board[i][j] == color && board[i][j + 1] == color && board[i][j + 2] == color && board[i][j + 3] == color)
                    return true;
        
        for (int j = 0; j < 7; j++)
            for (int i = 0; i < 2; i++)
                if (board[i][j] == color && board[i + 1][j] == color && board[i + 2][j] == color && board[i + 3][j] == color)
                    return true;
        
        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 4; j++)
                if (board[i][j] == color && board[i + 1][j + 1] == color && board[i + 2][j + 2] == color && board[i + 3][j + 3] == color)
                    return true;
        
        for (int i = 3; i < 5; i++)
            for (int j = 0; j < 4; j++)
                if (board[i][j] == color && board[i - 1][j + 1] == color && board[i - 2][j + 2] == color && board[i - 3][j + 3] == color)
                    return true;
        
        return false;
    }

    bool boardFull() {
        for (int i = 0; i < 7; i++)
            if (board[0][i] == '0') return false;
        return true;
    }

    public:
        Game() : player('R'), computer('Y') {}
    
    void play() {
        bool gameOver = false;
        ClearBoard();
        DisplayBoard();

        while (!gameOver) {
            player.makeMove();
            DisplayBoard();
            if (checkWin(player.color)) {
                cout << "\nCongrats! Player wins!\n";
                break;
            }
            if (boardFull()) {
                cout << "\nIt's a draw!\n";
                break;
            }

            computer.makeMove();
            DisplayBoard();
            if (checkWin(computer.color)) {
                cout << "\nComputer wins!\n";
                break;
            }
            if (boardFull()) {
                cout << "\nIt's a draw!\n";
                break;
            }
        }
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));

    cout << "\nWelcome to Connect Four!\n";

    char again;
    do {
        Game game;
        game.play();
        cout << "\nDo you want to play again? ";
        cin >> again;
    } while (again == 'y' || again == 'Y');

    cout << "\nThanks for playing!\n";
    return 0;
}