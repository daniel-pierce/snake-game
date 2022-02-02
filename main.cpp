// ------------------------------------------------------
// Name: Daniel Pierce
// Date: 2/1/2022
// Reference: https://www.youtube.com/watch?v=E_-lMZDi7Uw
// ------------------------------------------------------

#include <iostream>
#include <conio.h>
#include <Windows.h>

// Global Variables
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
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
}

void Draw() {
	system("cls"); // clear and redraw screen after every Draw() call
	for (int i = 0; i < width+2; i++) {
		std::cout << "#";
	}

	std::cout << std::endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				std::cout << "#";
			if (i == y && j == x)
				std::cout << "O";
			else if (i == fruitY && j == fruitX) 
				std::cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						std::cout << "o";
						print = true;
					}
				}
				if (!print)
					std::cout << " ";
			}
			if (j == width - 1)
				std::cout << "#";
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < width+2; i++) {
		std::cout << "#";
	}

	std::cout << std::endl;
	std::cout << "Score: " << score << "\n";
}

void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
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

	// --Walls WILL hurt the player [START]--
	if (x > width || x < 0 || y > height || y < 0) // quit if you hit a wall
		gameOver = true;
	// --Walls WILL hurt the player [END]--

	// --Walls won't hurt the player [START]--
	/*
	if (x >= width)
		x = 0;
	else if (x < 0)
		x = width - 1;

	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;
	*/
	// --Walls won't hurt the player [END]--

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}
	if (x == fruitX && y == fruitY) {
		score += 10; // Add score after contact
		fruitX = rand() % width; // Move the fruit to random location after contact
		fruitY = rand() % height;
		nTail++; // Add another o to the tail
	}
}

int main() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(10); // 10 milliseconds
	}
	return 0;
}
