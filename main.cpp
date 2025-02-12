#include "Game.h"
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;
Game* game = nullptr;

int main(int argc, char* argv[]) {
	const int FPS = 60;
	const int frameDelay = 1800 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("MySDLGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
	while (game->running()) {
		game->setup();
		while (game->menuDisplay) {
			game->Menu();
		}
		while (!game->gameOver&&game->running())
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
	}

	game->clean();
	return 0;
}