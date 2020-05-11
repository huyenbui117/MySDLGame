#include "Game.h"
#include"GameObject.h"
#include"TextureManager.h"	
#include "PlayerObject.h"
#include"AmoObject.h"
#include"EnemyObject.h"
#include"ExplodeObject.h"
EnemyObject* enemy;
PlayerObject* player;
ExplodeObject* explode;
GameObject* background;
GameObject* menu;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Game::Game() {};
Game::~Game() {};
void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullScreen) {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1){
		printf("%s\n", Mix_GetError());
	}
	int flags = 0;
	if (fullScreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		printf("Subsystem initialized\n");
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window) {
			printf("Window created\n");
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			printf("Renderer created\n");
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}
	menu = new GameObject();
	player = new PlayerObject();
	background = new GameObject();
	enemy = new EnemyObject();
	explode = new ExplodeObject();
}
void Game::setup(){
	menuDisplay = true;
	gameOver = false;
	menu->init("assets/menu.png", 0, 0, false);
	background->init("assets/background.png", 0, 0, false);
	background->srcRect = { 0,0,1026,1077 };
	background->desRect = { 0,0,Game::SCREEN_WIDTH,Game::SCREEN_HEIGHT };
	player->init("assets/player_animation.png", 0, 0, true);
	player->health = 5;
	while (enemy->enemyList.size()>0)
	{
		enemy->enemyList.pop_back();
	}
	enemy->init("assets/enemy2_animation.png");

	explode->health = -1;
}

void Game::handleEvents() {
	SDL_PollEvent(&event);
	
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
	player->handleEvents();
	enemy->handleEvents();
}
void Game::Menu() {
	int x=0, y=0;
	menu->health = -1;
	menu->srcRect = { 0,0,800,600 };
	menu->desRect = { 0,0,800,600 };
	SDL_RenderClear(renderer);
	menu->render();
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		menuDisplay = false;
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		x = event.button.x;
		y = event.button.y;
		menu->play("Hit", true);
		break;
	case SDL_MOUSEBUTTONUP:
		x = 0; y = 0;
	}
	if (x > 300 && x < 500) {
		if (y > 280 && y < 330) menuDisplay = false;
		if (y > 450 && y < 500) {
			menuDisplay = false;
			isRunning = false;
		}
	}
}
bool Game::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
	int left_a = object1.x;
	int right_a = object1.x + object1.w;
	int top_a = object1.y;
	int bottom_a = object1.y + object1.h;

	int left_b = object2.x;
	int right_b = object2.x + object2.w;
	int top_b = object2.y;
	int bottom_b = object2.y + object2.h;
	if (left_a > left_b && left_a < right_b) {
		if (top_a > top_b && top_a < bottom_b) {
			return true;
		}
	}

	if (left_a > left_b && left_a < right_b) {
		if (bottom_a > top_b && bottom_a < bottom_b) {
			return true;
		}
	}
	if (right_a > left_b && right_a < right_b) {
		if (top_a > top_b && top_a < bottom_b) {
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b) {
		if (bottom_a > top_b && bottom_a < bottom_b) {
			return true;
		}
	}
	if (left_b > left_a && left_b < right_a) {
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}
	if (left_b > left_a && left_b < right_a) {
		if (bottom_b > top_a && bottom_b < bottom_a) {
			return true;
		}
	}
	if (right_b > left_a && right_b < right_a) {
		if (top_b > top_a && top_b < bottom_a) {
			return true;
		}
	}
	if (right_b > left_a && right_b < right_a) {
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}
	if (top_a == top_b && right_a == right_b && bottom_a == bottom_b) {
		return true;
	}
	return false;
}
void Game::Explode(SDL_Rect position) {
	explode->init("assets/explosion.png", position.x, position.y, true);

	while (SDL_GetTicks() - explode->start <= 150) {
		explode->update();
		explode->render();
	}

	explode->play("Point", true);
}
void Game::update() {
	player->update();
	enemy->update();
}
void Game::render() {
	
	SDL_RenderClear(renderer);
	background->render();
	player->render();
	if (player->amoList.size() != 0) {
		for (int i = 0; i < player->amoList.size(); i++) {
			if (player->amoList.at(i) != NULL) {
				if (player->amoList.at(i)->is_moving == true) {
					player->amoList.at(i)->render();
					player->amoList.at(i)->update();
				}
				else{
					delete player->amoList.at(i);
					player->amoList.erase(player->amoList.begin() + i);
				}
			}
		}
	}
	for (int j = 0; j < enemy->enemyList.size(); j++) {
		enemy->enemyList.at(j)->render();
		Enemy* enemyTmp = enemy->enemyList.at(j);
		if (CheckCollision(player->desRect, enemyTmp->desRect)) {
			Game::Explode(player->desRect); 
			gameOver = true;
		}
		for (int i = 0; i < enemyTmp->amoList.size(); i++) {
			if (enemyTmp->amoList.at(i) != NULL) {
				if (enemyTmp->amoList.at(i)->is_moving == true) {
					enemyTmp->amoList.at(i)->render();
					enemyTmp->amoList.at(i)->update();
				}
				if (CheckCollision(player->desRect, enemyTmp->amoList.at(i)->desRect)) {
					player->health--;
					Game::Explode(player->desRect);
					player->play("Hit", true);
					enemyTmp->amoList.erase(enemyTmp->amoList.begin() + i);
				}
			}
		}
		for (int p_amo = 0; p_amo < player->amoList.size(); p_amo++) {
			if (player->amoList.at(p_amo)) {
				bool is_col = CheckCollision(player->amoList.at(p_amo)->desRect, enemyTmp->desRect);
				if (is_col) {
					player->amoList.erase(player->amoList.begin() + p_amo);
					enemyTmp->health--;
				}
			}
		}
		if (enemyTmp->health == 0) {
			Game::Explode(enemyTmp->desRect);
			enemy->enemyList.erase(enemy->enemyList.begin() + j);
			enemy->start = SDL_GetTicks();
		}
	}
	if (player->health == 0) {
		Game::Explode(player->desRect);
		gameOver = true;
	}
	if (enemy->enemyList.size() < enemy->quantity) {
		if (SDL_GetTicks()-enemy->start>=1000)
		enemy->addEnemy("assets/enemy2_animation.png");
	}
}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Game cleaned");
}
bool Game::running() {
	return isRunning;
}