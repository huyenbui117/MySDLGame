#include "AmoObject.h"

AmoObject::AmoObject(){
	position = Vector2D(0, 0);
	is_moving = false;
	objectSpeed = 30;
}
AmoObject::~AmoObject() {}


void AmoObject::update() {
	srcRect = { 0,0,20,14};
	desRect.w = 40; desRect.h = 28;
	position.x += static_cast<int>(velocity.x * objectSpeed);
	position.y += static_cast<int>(velocity.y * objectSpeed);
	if (position.y > Game::SCREEN_HEIGHT || position.y<0 || position.x>Game::SCREEN_WIDTH || position.x < 0) is_moving = false;


	if (animated) {
		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / frameSpeed) % frames);
	}
	srcRect.y = animIndex * 32;

	desRect.x = static_cast<int>(position.x);
	desRect.y = static_cast<int>(position.y);
}
