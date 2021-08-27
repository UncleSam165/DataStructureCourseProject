#pragma once

#include "Enemy.h"

class Freezer :public Enemy {
public:
	Freezer(int id, int arrTime, int d = MaxDistance);

	void Move();
	void Act();



};
