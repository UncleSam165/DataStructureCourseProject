#pragma once
#include "Enemy.h"
#include "..\Castle\Castle.h"
class Healer :public Enemy {
	private:
	int direction;
	double HealthHeal;
public:
	Healer(int id, int arrTime, int d = MaxDistance);

	void Move();
	void Act(Enemy*& E);
};
