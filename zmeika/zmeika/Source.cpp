#include<iostream>
#include<conio.h>
#include<Windows.h>

using namespace std;

bool gameover;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score; //(x;y) - положение змейки 
int tailX[100], tailY[100];      //fruitXY - положение фрукта
int ntail;
enum Direction{ STOP = 0,LEFT,RIGHT,UP,DOWN};
Direction dir;
void Setup() {
	gameover = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
/*void setcur(int x, int y) //установка курсора на позицию  x y 
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};*/

void Draw() {
	system("cls");
	//setcur(0, 0);
	for (int i = 0; i < width + 1; i++) 
		cout << "#";
	
		cout << endl;
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) 
				cout << "#";
			if (i == y && j == x) {
				cout << "0";
			}
			else if (i == fruitY && j == fruitX) {
				cout << "F";
			}
			else {
				bool print = false;
				for (int k = 0; k < ntail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "o";
					}
				} if (!print) 
				cout << " ";
			
			}
		}
		cout << endl;
		}

	for (int i = 0; i < width + 1; i++) 
		cout << "#";
			cout << endl;

			cout << "SCORE:" << score << endl;
	
}

void Input() {  //Ввод клавиш

	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'w':
			dir = UP;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameover = true;
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
	for (int i = 1; i < ntail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
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
	}
	if (x >= width - 1) {
		x = 0;
	}
	else if (x < 0) {
		x = width - 2;
	}

	if (y >= height) {
		y = 0;
	}
	else if (y < 0) {
		y = height - 1;
	}

	for (int i = 0; i < ntail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameover = true;
		}
	}

	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		ntail++;
	}
	

}

int main() {
	Setup();
	while (!gameover) {
		Draw();
		Input();
		Logic();
	}
	return 0;
}

