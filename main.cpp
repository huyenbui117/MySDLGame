#include "Game.h"
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;
Game* game = nullptr;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*bool GameOver, Continue = 1;
const int Height = 20;
const int Width = 20;
int SnakeX, SnakeY, FruitX, FruitY, Scores, CntTail = 0, t = 300;
int TailX[Height * Width + 1] = {}, TailY[Height * Width + 1] = {};

____________________________________________________________
void Setup() {
	GameOver = 0;
	SnakeX = Width / 2;
	SnakeY = Height / 2;
	dir = STOP;
	FruitX = rand() % Width;
	FruitY = rand() % Height;
	Scores = 0;
	TailX[Height * Width + 1] = {}, TailY[Height * Width + 1] = {};
}
void Draw() {
	system("cls");
	for (int i = 0; i <= Width + 1; i++) printWall();
	cout << endl;
	for (int i = 0; i <= Height - 1; i++) {
		for (int j = 0; j <= Width + 1; j++) {
			if (j == 0 || j == Width + 1) printWall();
			else
				if (j == SnakeX && i == SnakeY) printSnakeHead();
				else
					if (j == FruitX && i == FruitY) printFruit();
					else {
						bool print = 0;
						for (int k = 1; k <= CntTail; k++) {
							if (TailX[k] == j && TailY[k] == i) {
								printTail();
								print = 1;
							}
						}
						if (!print && j <= Width) cout << " ";


					}
		}
		cout << endl;
	}
	for (int i = 0; i <= Width + 1; i++) printWall();
	cout << endl;
}
void Update() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			GameOver = 1;
			break;
		default:
			Continue = 0;
			break;
		case 'p':
			while (!_kbhit()) {
				Sleep(1);
			}
			_getch();
			break;
			//case 'c':

		}
	}
}
void Process() {
	TailX[0] = SnakeX;
	TailY[0] = SnakeY;
	int tmpX = TailX[0], tmp1X, tmpY = TailY[0], tmp1Y;
	for (int i = 1; i <= CntTail; i++) {
		tmp1X = TailX[i];//tail1
		TailX[i] = tmpX;//tail1=tail0
		tmpX = tmp1X;//tmp=tail1
		tmp1Y = TailY[i];//tail1
		TailY[i] = tmpY;//tail1=tail0
		tmpY = tmp1Y;//tmp=tail1
	}
	if (SnakeX == FruitX && SnakeY == FruitY) {
		Scores += 10;
		FruitX = rand() % Width;
		FruitY = rand() % Height;
		CntTail++;
		if (t > 30)t -= 30;
	}
	if (SnakeX > Width || SnakeX<0 || SnakeY>Height || SnakeY < 0)
		GameOver = 1;
	for (int i = 1; i <= CntTail; i++)
		if (SnakeX == TailX[i] && SnakeY == TailY[i])
			GameOver = 1;
}*/
int main(int argc, char* argv[]) {/*
	while (Continue) {
		Setup();
		while (!GameOver) {
			Draw();
			Update();
			Process();
			cout << "Scores: " << Scores << endl;
			Sleep(t);
		}
		cout << "Continue? [Y] [N] ";
		for (int i = 5; i >= 1; i--) {
			Sleep(1000);
			cout << i << "...";
			if (_kbhit()) {
				if (_getch() == 'y') {
					Continue = 1;
					GameOver = 0;
					cout << endl << "Choi tiep nhe!";
				}
				else Continue = 0;
				break;
			}
		}
		//WaitForSingleObject(cin,100000);
	}*/
	const int FPS = 60;
	const int frameDelay = 1800 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("BirchEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
	while (game->running())
	{

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}

	}
	game->clean();
	return 0;
}