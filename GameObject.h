#pragma once
#include"Game.h"

#include "Animation.h"
#include<map>
#include"Vector2D.h"
#include"Sound.h"
class GameObject {

public:
	int animIndex = 0;
	std::map<const char*, Animation> animations;
	std::map<const char*, Sound> sounds;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	GameObject() {}
	~GameObject() {
		SDL_DestroyTexture(objectTexture);
		objectTexture = NULL;
	}
	void init(const char* texture, int x, int y, bool isAnimated);

	virtual void update();
	void render();

	void play(const char* animName, bool audio);


	bool animated = false;
	int frames = 0;
	int frameSpeed = 100;

	SDL_Texture* objectTexture;
	SDL_Texture* healthTexture;
	SDL_Rect srcRect, desRect;
	Vector2D position,velocity;
	int objectSpeed = 10;
	int start;
	int health=5;
};

