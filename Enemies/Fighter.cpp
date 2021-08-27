#include "Fighter.h"


Fighter::Fighter(int id, int arrTime, int d) :Enemy(id, arrTime, d) {
	Type = FIGHTER;
}


void Fighter::Move() {
	DecrementDist();
}

void Fighter::Act() {

}

void Fighter::UpdatePriority() {
	priority = Power * Health * ((double)static_cast<int>(GetStatus())) / (double)Distance;
}

double Fighter::GetPriority() {
	return priority;
}