#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

char key_up;
char key_right;
char key_bottom;
char key_left;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0; // Reset the length of the tail
}

void Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}

void PlayGameOverSong() {
    Beep(1000, 500); // Beep to signal game over
}

void Input() {
    if (_kbhit()) {
        char key = _getch();
        if (key == key_left)
            dir = LEFT;
        else if (key == key_right)
            dir = RIGHT;
        else if (key == key_up)
            dir = UP;
        else if (key == key_bottom)
            dir = DOWN;
        else if (key == 'x')
            gameOver = true;
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += 10;
        // Play sound or make computer voice here
        Beep(700, 30); // Beep at 700 Hz for 30 milliseconds
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

void RestartTheGame() {
    PlayGameOverSong();
    while (gameOver) {
        cout << "Game over. [Press Enter key] to restart the game.";

        // Wait until the Enter key is pressed
        while (_getch() != '\r') {
            // Wait for the Enter key to be pressed
        }

        gameOver = false; // Reset gameOver flag to restart the game
        Setup(); // Call Setup to reset game state
    }
}



void InputSetting() {
    cout << "--------------Welcome To snake Game--------------" << "\n";
    cout << "Select UP key button : ";
    cin >> key_up;

    cout << "Select Right key button : ";
    cin >> key_right;

    cout << "Select Bottom key button : ";
    cin >> key_bottom;

    cout << "Select Left key button : ";
    cin >> key_left;
}

int main() {
    srand(time(0)); // Seed random number generator
    InputSetting();
    while (!gameOver) {
        Setup(); // Call Setup to initialize the game state
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(100); //sleep(10) on linux
        }
        RestartTheGame();
    }
    return 0;
}


// Made By omarker09 :)