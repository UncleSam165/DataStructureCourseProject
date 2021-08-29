#include "Fighter.h"


Fighter::Fighter(int id, int arrTime, int d) :Enemy(id, arrTime, d) {
	Type = FIGHTER;
        K=1;
}


void Fighter::Move() {
	DecrementDist();
}

void Fighter::Act(Enemy* E) {
if ((int)(CurrentTimeStep - ArrvTime) % ((int)ReloadPeriod + 1) == 0) {
		double Damage = (K * Power) / Distance;
		NewCastle->DecrementHealth(Damage);
	}


       if (dynamic_cast<Healer*>(E)){
		if ((E->GetDistance() - this->Distance)<= 2){
			if (status != KILD) {
				Health += GetHealthHeal();
			}
		}
	}

}

	

void Fighter::UpdatePriority() {
	priority = Power * Health * ((double)static_cast<int>(GetStatus())) / (double)Distance;
}

double Fighter::GetPriority() {
	return priority;
}
