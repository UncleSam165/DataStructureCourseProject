#include "Fighter.h"


Fighter::Fighter(int id, int arrTime, int d) :Enemy(id, arrTime, d) {
	Type = FIGHTER;
        K=1;
}


void Fighter::Move() {
	if(status==ACTV)
		DecrementDist();
}

void Fighter::Act(Castle &C) {
if ((int)(CurrentTimeStep - ArrvTime) % ((int)ReloadPeriod + 1) == 0) {
		double Damage = (K * Power) / Distance;
		C.DecrementHealth(Damage);
	}
}

	

void Fighter::UpdatePriority() {
	priority = Power * Health * ((double)static_cast<int>(GetStatus())) / (double)Distance;
}

double Fighter::GetPriority() {
	return priority;
}
