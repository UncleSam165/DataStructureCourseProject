#include "Healer.h"


Healer::Healer(int id, int arrTime, int d) :Enemy(id, arrTime, d) {
	Type = HEALER;
	direction = 1;
};

void Healer::Move() {
	if(direction==1){
		DecrementDist();
		if (this->GetDistance()-Speed < MinDistance)
		{
			direction = 0;
			Distance += Speed;
		}
	}
	else if(direction == 0){
		if (Distance+Speed <= MaxDistance)
			Distance+= Speed;
		if (Distance+Speed > MaxDistance)
		{
			direction = 1;
			Distance -= Speed;
		}
	}	
}

void Healer::Act(Enemy*& E) {
	if ((int)(CurrentTimeStep - ArrvTime) % ((int)ReloadPeriod + 1) == 0) {
		if ((direction == 1 && (E->GetDistance() <= Distance && E->GetDistance() >= Distance - 5)) || (direction == 0 && (E->GetDistance() >= Distance && E->GetDistance() <= Distance + 5))) {
			HealthHeal = (Health / MaxHealth) * Power * 2 * (E->GetMaxHealth() / 100);
			E->SetHealth(E->GetHealth() + HealthHeal);
		}
	}
}
