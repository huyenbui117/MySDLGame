#include "EnemyObject.h"
void Enemy::handleEvents(){
	srand(SDL_GetTicks());
	type = rand() % 50;
	int tmpx = position.x + static_cast<int>(velocity.x * objectSpeed);
	if (tmpx > 0 && tmpx < Game::SCREEN_WIDTH - desRect.x);
	else
	{
		if (tmpx <= 0) type = RIGHT;
		if (tmpx >= Game::SCREEN_WIDTH - desRect.x)type = LEFT;
	}
	int tmpy = position.y + static_cast<int>(velocity.y * objectSpeed);
	if (tmpy > 0 && tmpy < Game::SCREEN_HEIGHT - desRect.y);
	else {
		if (tmpy <= 0) type = DOWN;
		if (tmpy >= Game::SCREEN_HEIGHT - desRect.y)type = UP;
	}
	//std::cout<<type << " Type\n";
	switch (type)
	{
	case UP:
		velocity.y = -1;
		if (lastmove.x == -1)
			flip = SDL_FLIP_HORIZONTAL;
		else
			flip = SDL_FLIP_NONE;
		play("Walk",false);
		break;
	case RIGHT:
		velocity.x = 1;
		lastmove = velocity;
		play("Walk",false);
		break;
	case DOWN:
		velocity.y = 1;
		if (lastmove.x == -1)
			flip = SDL_FLIP_HORIZONTAL;
		else
			flip = SDL_FLIP_NONE;
		play("Walk",false);
		break;
	case LEFT:
		velocity.x = -1;
		lastmove = velocity;
		play("Walk",false);
		break;
	case UNUP:
		if (velocity.x!=0)
		velocity.y = 0;
		play("Idle",false);
		break;
	case UNRIGHT:
		if (velocity.y != 0)
		velocity.x = 0;
		play("Idle",false);
		break;
	case UNDOWN:
		if (velocity.x != 0) velocity.y = 0;
		play("Idle",false);
		break;
	case UNLEFT:
		if (velocity.y != 0) velocity.x = 0;
		play("Idle",false);
		break;
	case SHOOT:
		AmoObject *amo = new AmoObject();
		amo->init("assets/amo.png", position.x, position.y, false);
		amo->objectSpeed = 30;
		amo->position.x += 20;
		amo->is_moving = true;

		amo->velocity = Vector2D(lastmove.x, 0);
		if (lastmove == Vector2D(0, 0)) amo->velocity = Vector2D(1, 0);
		if (amo->velocity.x == -1) amo->flip = SDL_FLIP_HORIZONTAL;
		else amo->flip = SDL_FLIP_NONE;

		amo->update();
		amoList.push_back(amo);
		break;
	}
}
void Enemy::update() {
	int tmpx = position.x + static_cast<int>(velocity.x * objectSpeed);
	if (tmpx > 0 && tmpx < Game::SCREEN_WIDTH - 64) position.x = tmpx;
	int tmpy = position.y + static_cast<int>(velocity.y * objectSpeed);
	if (tmpy > 0 && tmpy < Game::SCREEN_HEIGHT - 64) position.y = tmpy;
	if (animated) {
		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / frameSpeed) % frames);
	}
	srcRect.y = animIndex * 32;

	desRect.x = static_cast<int>(position.x);
	desRect.y = static_cast<int>(position.y);


	std::string path = "assets/" + std::to_string(health) + ".png";
	healthTexture = TextureManager::LoadTexture(path.c_str());
	//std::cout << desRect.x << " " << desRect.y << "\n";
}

void EnemyObject::init(const char* path){
	Enemy* enemy = new Enemy();
	int x = rand() % ((Game::SCREEN_WIDTH-64)/2)+ (Game::SCREEN_WIDTH - 64) / 2, y = rand() % ((Game::SCREEN_HEIGHT-64)/2)+ (Game::SCREEN_HEIGHT - 64) / 2;
	enemy->init(path,x,y, true);
	enemy->objectSpeed = 2;
	enemy->velocity = Vector2D(1, 1);
	enemy->desRect.w = 32; enemy->desRect.h = 32;
	enemyList.push_back(enemy);
}

void EnemyObject::addEnemy(const char* path) {
	
	Enemy* enemy = new Enemy();
	int x = rand() % ((Game::SCREEN_WIDTH - 64) / 2) + (Game::SCREEN_WIDTH - 64) / 2, y = rand() % ((Game::SCREEN_HEIGHT - 64) / 2) + (Game::SCREEN_HEIGHT - 64) / 2;
	enemy->init(path, x, y, true);
	enemy->objectSpeed = 2;
	enemy->velocity = Vector2D(1, 1);
	enemy->desRect.w = 32; enemy->desRect.h = 32;
	enemyList.push_back(enemy);
}
void EnemyObject::handleEvents(){
	for (int i=0;i<enemyList.size();i++){
		enemyList.at(i)->handleEvents();
		//std::cout << "Handled\n";
	}
}

void EnemyObject::update(){ 
	for (int i = 0; i < enemyList.size(); i++) {
		enemyList.at(i)->update();

	}

	quantity = rand() % 10 + 1;
}

void EnemyObject::render()
{
	for (int i = 0; i < enemyList.size(); i++) {
		enemyList.at(i)->render();
	}
}
