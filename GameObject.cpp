#include "GameObject.h"
#include"TextureManager.h"
#define OBJECT_HEIGHT 64
#define OBJECT_WIDTH 64
void GameObject::init(const char* path, int x, int y, bool isAnimated) {
	objectTexture = TextureManager::LoadTexture(path);
	position = Vector2D(x, y);
	velocity = Vector2D(0, 0);
	srcRect = { 0,0,32,32 };
	desRect = { 0,0,64,64 };

	animated = isAnimated;
	Animation idle = Animation(0, 3, 100);
	Animation walk = Animation(1, 4, 100);

	Sound idlesound = Sound("sound/idle.wav");
	Sound walksound = Sound("sound/walk.wav");
	Sound shootsound = Sound("sound/shoot.wav");

	animations.emplace("Idle", idle);
	animations.emplace("Walk", walk);

	sounds.emplace("Idle", idlesound);
	sounds.emplace("Walk", walksound);
	sounds.emplace("Shoot", shootsound);


	play("Idle",false);
	objectTexture = TextureManager::LoadTexture(path);
	start = SDL_GetTicks();
}
void GameObject::update() {
	int tmpx = position.x + static_cast<int>(velocity.x * objectSpeed);
	if (tmpx > 0 && tmpx < Game::SCREEN_WIDTH - OBJECT_WIDTH) position.x = tmpx;
	int tmpy = position.y + static_cast<int>(velocity.y * objectSpeed);
	if (tmpy > 0 && tmpy < Game::SCREEN_HEIGHT - OBJECT_HEIGHT) position.y = tmpy;

	if (animated) {
		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / frameSpeed) % frames);
	}
	srcRect.y = animIndex * 32;

	desRect.x = static_cast<int>(position.x);
	desRect.y = static_cast<int>(position.y);
}

void GameObject::render() {

	TextureManager::Draw(objectTexture, srcRect, desRect,flip);
	SDL_RenderPresent(Game::renderer);
}
void GameObject::play(const char* animName, bool audio) {
	frames = animations[animName].frames;
	animIndex = animations[animName].index;
	frameSpeed = animations[animName].speed;
	sound = sounds[animName].sound;
	
	if (audio) {
		Mix_HaltChannel(-1);
		Mix_PlayChannel(-1, sound,0);
		std::cout << animName << "\n";
	}
}