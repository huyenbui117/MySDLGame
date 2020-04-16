#pragma once
#include "GameObject.h"
class ExplodeObject:public GameObject{
public:
	void update() override {
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / frameSpeed) % frames);
		}
		srcRect.y = animIndex * 32;
		desRect.w = 64; desRect.h = 64;
		desRect.x = static_cast<int>(position.x);
		desRect.y = static_cast<int>(position.y);
	}
};

