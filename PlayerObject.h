#pragma once
#include"GameObject.h"
#include<vector>
#include"AmoObject.h"
#define OBJECT_HEIGHT 30
#define OBJECT_WIDTH 64
class PlayerObject:public GameObject{
public:
	void handleEvents();
	std::vector<AmoObject*> amoList;
	Vector2D lastmove;
};

