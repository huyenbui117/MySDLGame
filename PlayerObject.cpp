#include "PlayerObject.h"

void PlayerObject::handleEvents() {
	if (Game::event.type == SDL_KEYDOWN) {
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_UP:
			velocity.y = -1;
			if (lastmove.x == -1)
				flip = SDL_FLIP_HORIZONTAL;
			else
				flip = SDL_FLIP_NONE;
			play("Walk",true);
			break;
		case SDLK_DOWN:
			velocity.y = 1;
			if (lastmove.x == -1)
				flip = SDL_FLIP_HORIZONTAL;
			else
				flip = SDL_FLIP_NONE;
			play("Walk",true);
			break;
		case SDLK_LEFT:
			velocity.x = -1;
			lastmove = velocity;
			flip = SDL_FLIP_HORIZONTAL;

			play("Walk",true);
			break;
		case SDLK_RIGHT:
			velocity.x = 1;
			lastmove = velocity;

			play("Walk",true);
			break;

		default:
			play("Idle", false);
				break;
		case SDLK_SPACE:
			AmoObject* amo=new AmoObject();
			amo->init("assets/amo.png", position.x, position.y, false);
			amo->is_moving = true;

			amo->velocity = Vector2D(lastmove.x,0);
			if (lastmove == Vector2D(0, 0)) amo->velocity = Vector2D(1, 0);
			if (amo->velocity.x == -1) amo->flip = SDL_FLIP_HORIZONTAL;
			else amo->flip = SDL_FLIP_NONE;

			amo->update();
			amoList.push_back(amo);
			break;
		}
	}
	if (Game::event.type == SDL_KEYUP) {
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_UP:
			velocity.y = 0;
			play("Idle",false);
			break;
		case SDLK_DOWN:
			velocity.y = 0;
			play("Idle",false);
			break;
		case SDLK_LEFT:
			velocity.x = 0;
			play("Idle",false);
			flip = SDL_FLIP_NONE;
			break;
		case SDLK_RIGHT:
			velocity.x = 0;
			play("Idle",false);
			break;
		case SDLK_SPACE:
			play("Idle", false);
		}
	}
}
