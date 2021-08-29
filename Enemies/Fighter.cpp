#include "Fighter.h"


Fighter::Fighter(int id, int arrTime, int d) :Enemy(id, arrTime, d) {
	Type = FIGHTER;
}


void Fighter::Move() {
	DecrementDist();
}

void Fighter::Act() {
if ((int)(CurrentTimeStep - ArrvTime) % ((int)ReloadPeriod + 1) == 0) {
		double Damage = (K * Power) / Distance;
		NewCastle->DecrementHealth(Damage);
	}

}

void Fighter::Heal() {
	if (status != KILD) {
		Health += GetHealthHeal();
	}
}

void Fighter::UpdatePriority() {
	priority = Power * Health * ((double)static_cast<int>(GetStatus())) / (double)Distance;
}

double Fighter::GetPriority() {
	return priority;
}
