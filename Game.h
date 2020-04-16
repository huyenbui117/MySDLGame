#ifndef Game_h
#define Game_h
#include <stdio.h>
#include<SDL.h>
#include<SDL_image.h>
class Game
{
public:
	Game();
	~Game();
	void init(const char* title, int xPos, int yPos, int width, int height, bool fullScreen);

	void handleEvents();
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	void Explode(SDL_Rect position);
	void update();
	void render();
	void clean();

	static SDL_Renderer* renderer;
	static SDL_Event event;
	bool running();

	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 640;
private:

	bool isRunning;
	SDL_Window* window;
};

#endif