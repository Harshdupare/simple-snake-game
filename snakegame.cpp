#include<iostream>
#include<windows.h>
using namespace std;

const int WIDTH = 50;
const int HEIGHT = 30;

enum Direction { STOP = 0, UP, DOWN, LEFT, RIGHT };

class SnakeGame {
private:
    bool snakeGame;
    enum GameState { MAIN, START };
    GameState mode;
    int menu;
    
    // User variables
    int x, y, spd;
    int tailX[100], tailY[100], tailLength;
    
    // Target variables
    int targetX, targetY;
    
    // Game variables
    int score;
    Direction dir;

public:
    SnakeGame() {
        snakeGame = true;
        mode = MAIN;
        menu = 0;
        spd = 1;
        dir = STOP;
        score = 0;
        tailLength = 0;
        x = rand() % WIDTH;
        y = rand() % HEIGHT;
        targetX = rand() % WIDTH;
        targetY = rand() % HEIGHT;

        while (x == targetX && y == targetY) {
            x = rand() % WIDTH;
            y = rand() % HEIGHT;
            targetX = rand() % WIDTH;
            targetY = rand() % HEIGHT;
        }
    }

    void runGame() {
        while (snakeGame) {
            if (mode == MAIN) {
                mainMenu();
            }
            else if (mode == START) {
                normalSetup();

                while (mode == START) {
                    gameWindow();
                    gameInput();
                    gameProgram();
                    Sleep(70);
                }
            }
        }
    }

private:
    void gameOver() {
        tailLength = 0;
        score = 0;
        mode = MAIN;
    }

    void normalSetup() {
        dir = STOP;
        x = rand() % WIDTH;
        y = rand() % HEIGHT;
        targetX = rand() % WIDTH;
        targetY = rand() % HEIGHT;

        while (x == targetX && y == targetY) {
            x = rand() % WIDTH;
            y = rand() % HEIGHT;
            targetX = rand() % WIDTH;
            targetY = rand() % HEIGHT;
        }

        score = 0;
    }

    void mainMenu() {
        system("cls");
        cout << "This is the main menu" << endl;

        if (menu == 0) {
            cout << ">> Play the Game." << endl;
            cout << "Options" << endl;
            cout << "End Game" << endl;
        }
        else if (menu == 1) {
            cout << "Play the Game." << endl;
            cout << ">> Options" << endl;
            cout << "End Game" << endl;
        }
        else if (menu == 2) {
            cout << "Play the Game." << endl;
            cout << "Options" << endl;
            cout << ">> End Game" << endl;
        }

        if (GetAsyncKeyState(VK_RETURN)) {
            switch (menu) {
            case 0:
                mode = START;
                break;
            case 1:
                return;
                break;
            case 2:
                exit(0);
                break;
            }
        }
        else if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))) {
            dir = STOP;
        }
        else if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))) {
            dir = STOP;
        }
        else if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))) {
            dir = STOP;
            menu++;
            Sleep(80);
        }
        else if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))) {
            dir = STOP;
            menu--;
            Sleep(80);
        }

        if (menu <= -1) {
            menu = 2;
        }
        else if (menu >= 3) {
            menu = 0;
        }
    }

    void gameWindow() {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });

        // Top border
        for (int i = 0; i < WIDTH; i++) {
            cout << "#";
        }
        cout << endl;

        // Body
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (j == 0 || j == WIDTH - 1) {
                    cout << "#";
                }
                else if (i == y && j == x) {
                    cout << "0";
                }
                else if (i == targetY && j == targetX) {
                    cout << "&";
                }
                else {
                    bool tail = false;
                    for (int k = 0; k < tailLength; k++) {
                        if (j == tailX[k] && i == tailY[k]) {
                            cout << "0";
                            tail = true;
                        }
                    }
                    if (!tail) {
                        cout << " ";
                    }
                }
            }
            cout << endl;
        }

        // Bottom border
        for (int i = 0; i < WIDTH; i++) {
            cout << "#";
        }
        cout << endl;

        cout << "score : " << score;
    }

    void gameInput() {
        if (mode == START) {
            if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) && dir != RIGHT) {
                dir = LEFT;
            }
            else if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) && dir != LEFT) {
                dir = RIGHT;
            }
            else if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) && dir != UP) {
                dir = DOWN;
            }
            else if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) && dir != DOWN) {
                dir = UP;
            }
            else if (GetAsyncKeyState(VK_RETURN)) {
                return;
            }
        }
    }

    void gameProgram() {
        int fposX, fposY, sposX, sposY;

        // Tail
        fposX = tailX[0];
        fposY = tailY[0];
        tailX[0] = x;
        tailY[0] = y;

        for (int i = 1; i < tailLength; i++) {
            sposX = tailX[i];
            sposY = tailY[i];
            tailX[i] = fposX;
            tailY[i] = fposY;
            fposX = sposX;
            fposY = sposY;

            while (tailX[i] == targetX && tailY[i] == targetY) {
                targetX = rand() % WIDTH;
                targetY = rand() % HEIGHT;
            }
        }

        // Move the snake
        switch (dir) {
        case LEFT:
            x -= spd;
            break;
        case UP:
            y -= spd;
            break;
        case DOWN:
            y += spd;
            break;
        case RIGHT:
            x += spd;
            break;
        }

        // Check if snake hits border
        if (x <= 0 || x >= WIDTH - 1 || y < 0 || y > HEIGHT - 1) {
            gameOver();
        }

        // Check if snake hits tail
        for (int i = 0; i < tailLength; i++) {
            if (x == tailX[i] && y == tailY[i]) {
                gameOver();
            }
        }

        // Check if snake hits target
        if (x == targetX && y == targetY) {
            targetX = rand() % WIDTH;
            targetY = rand() % HEIGHT;
            score++;
            tailLength++;
        }
    }
};

int main() {
    SnakeGame game;
    game.runGame();

    return 0;
}
