#pragma once
#include"GameObject.h"
#include<vector>
#include"AmoObject.h"
#include"TextureManager.h"
#include<string>
#include<time.h>
class Enemy:public GameObject{
public:
	enum enemyEvent { UP, RIGHT, DOWN, LEFT, SHOOT, UNUP, UNRIGHT, UNDOWN, UNLEFT };
	Enemy() {};
	~Enemy() {};
	void handleEvents();
	void update() override;
	AmoObject* amo;
	Vector2D lastmove;
	int type = 6;
};
class EnemyObject
{
public:
	EnemyObject() {};
	~EnemyObject() {};
	void init(const char* path);
	void addEnemy(const char* path);
	void handleEvents();
	void update();
	void render();
	std::vector<Enemy*> enemyList;
	int quantity = 3;
	int start = 0;
};

