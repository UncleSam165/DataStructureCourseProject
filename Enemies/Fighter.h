#pragma once
#include "Enemy.h"

class Fighter :public Enemy {
private:
	double priority;
public:
	Fighter(int id, int arrTime, int d = MaxDistance);

	void Move();
	void Act();
	void Act(Castle &E);
	void UpdatePriority();
	double GetPriority();
};
