#pragma once
#include "Enemy.h"
#include "..\Castle\Castle.h"
class Freezer :public Enemy {
public:
	Freezer(int id, int arrTime, int d = MaxDistance);

	void Move();
	void Act(Castle& C);
};
