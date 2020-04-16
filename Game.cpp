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
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Game::Game() {};
Game::~Game() {};
void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullScreen) {
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
	player = new PlayerObject();
	player->init("assets/player_animation.png", 0, 0, true);
	enemy = new EnemyObject();
	enemy->init("assets/enemy_animation.png");
	explode = new ExplodeObject();
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
	std::cout << "GameOver";
	explode->init("assets/explosion.png", position.x, position.y, true);
	while (SDL_GetTicks() - explode->start <= 150) {
		explode->update();
		explode->render();
	}
}
void Game::update() {
	player->update();
	enemy->update();
}
void Game::render() {
	SDL_RenderClear(renderer);
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
		}
		if (enemyTmp->amo != NULL) {
			if (enemyTmp->amo->is_moving == true) {
				enemyTmp->amo->render();
				enemyTmp->amo->update();
			}
			if (CheckCollision(player->desRect, enemyTmp->amo->desRect)) {
				Game::Explode(player->desRect);
			}
		}
		for (int p_amo = 0; p_amo < player->amoList.size(); p_amo++) {
			if (player->amoList.at(p_amo)) {
				bool is_col = CheckCollision(player->amoList.at(p_amo)->desRect, enemyTmp->desRect);
				if (is_col) {
					Game::Explode(enemyTmp->desRect);
					std::cout << "Point!\n";
					player->amoList.erase(player->amoList.begin() + p_amo);
					enemy->enemyList.erase(enemy->enemyList.begin() + j);     
					enemy->start = SDL_GetTicks();
				}
			}
		}
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