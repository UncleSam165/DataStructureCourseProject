#include "Castle.h"
#include<cstdlib>


bool Castle::isDestroyed()
{
	if (Health < 0)
		return true;
	else
		return false;
}

int Castle::GetNumberOfEnemies()
{
	return NumberOfEnemies;
}

void Castle::SetNumberOfEnemies(int N)
{
	if (N > 0)
		NumberOfEnemies = N;
	else
		NumberOfEnemies = 10;         //Set the number of enemies with avaible number
}

double Castle::GetHealth() const
{
	return Health;
}

void Castle::SetHealth(double h)
{
	if (h > 0)
		Health = h;
	else
		Health = 0; // killed
}

void Castle::DecrementHealth()
{
}

void Castle::SetPower(double P) {
	if (P > 0)
		Power = P;
	else
		Power = 10;     //Set the power with avaiable number
}

double Castle::GetPower() const {
	return Power;
}

void Castle::SetStatus(ENMY_STATUS S) {
	status = S;
}

ENMY_STATUS Castle::GetStatus() const {
	return status;
}


void Castle::Damage(Enemy* &E) {
	double damage, distance = (double)E->GetDistance(), K;
	if (dynamic_cast<Healer*>(E)) { K = 2; }
	else { K = 1; }
	damage = (1 / distance) * Power * (1 / K);
	E->SetHealth(min(0,E->GetHealth() - damage));	
}
