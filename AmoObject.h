#pragma once
#include"GameObject.h"
class AmoObject:public GameObject{
public:
	enum AmoType { NONE, AMO };
	AmoObject();
	~AmoObject();
	void update() override;
	bool is_moving;
	AmoType amotype;
};

