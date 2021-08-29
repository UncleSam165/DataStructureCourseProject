#pragma once
#include "Enemy.h"
#include "..\Castle\Castle.h"

class Fighter :public Enemy {
private:
	double priority;
public:
	Fighter(int id, int arrTime, int d = MaxDistance);

	void Move();
	void Act(Castle &C);
	void UpdatePriority();
	double GetPriority();
};
