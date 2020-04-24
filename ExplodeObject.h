#pragma once
#include "GameObject.h"
class ExplodeObject:public GameObject{
public:
	void update() override {
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / frameSpeed) % frames);
		}
		srcRect.y = animIndex * 32;
		desRect.w = 128; desRect.h = 128;
		desRect.x = static_cast<int>(position.x-32);
		desRect.y = static_cast<int>(position.y-32);
	}
};

