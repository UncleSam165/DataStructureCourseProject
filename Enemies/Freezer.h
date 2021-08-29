#pragma once
#include"../Castle/Castle.h"
#include "Enemy.h"

class Freezer :public Enemy {
public:
	Freezer(int id, int arrTime, int d = MaxDistance);

	void Move();
	void Act();
	void Act(Castle &C) ;
       


};
