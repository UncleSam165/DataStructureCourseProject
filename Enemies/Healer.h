#pragma once
#include "Enemy.h"

class Healer :public Enemy {
	private:
	int direction;
	double HealthHeal;
public:
	Healer(int id, int arrTime, int d = MaxDistance);

	void Move();
	void Act();
	void Act(Enemy* &E);



};
