#include "Freezer.h"


Freezer::Freezer(int id, int arrTime, int d ) :Enemy(id, arrTime, d) {
	Type = FREEZER;
};

void Freezer::Move() {
	DecrementDist();
}

void Freezer::Act() {

if (status != KILD) {
		Health += GetHealthHeal();
	}
}
