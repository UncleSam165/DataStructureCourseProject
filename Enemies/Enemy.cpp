#include "Enemy.h"


Enemy::Enemy(int id, int arrTime, int d):ID(id),ArrvTime(arrTime)
{
	SetDistance(d);
}

Enemy::~Enemy()
{
}

int Enemy::GetID() const
{
	return ID;
}


void Enemy::SetStatus(ENMY_STATUS s)
{
	status = s;
}


ENMY_STATUS Enemy::GetStatus() const
{
	return status;
}


void Enemy::DecrementDist()
{
	if (Distance-Speed+1 > MinDistance)
		Distance-= Speed;
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const
{
	return Distance;
}

int Enemy::GetArrvTime() const
{
	return ArrvTime;
}

void Enemy::SetHealth(double h)
{
	if (h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Enemy::GetHealth() const
{
	return Health;
}

void Enemy::DecrementHealth() {

}

void Enemy::SetReloadPeriod(double R) {
	ReloadPeriod = R;
}

double Enemy::GetReloadPeriod()const{
	return ReloadPeriod;
}

void Enemy::SetSpeed(double S) {
	Speed = S;
}

double Enemy::GetSpeed()const{
	return Speed;
}


void Enemy::SetPower(double P) {
	Power = P;
}

double Enemy::GetPower()const {
	return Power;
}

void Enemy::SetHealthHeal(double HH) {
         HealthHeal=HH;
} 

double Enemy::GetHealthHeal(){
          return HealthHeal;
} 

void Enemy::SetFreezingTime(int S)
{
	if (GetType() == FIGHTER || GetType() == HEALER)
	{
		FreezingTime = 2 * (1 / S) * 5;   // Assuming that the castle freezing power = 5
	}
	else
	{
		FreezingTime = (1 / S) * 5;
	}
}

int Enemy::GetFreezingTime() const
{
	return FreezingTime;
}

int Enemy::GetFirstShot(){
	return FirstShot;
}

int Enemy::GetTimeKilled() {
	return TimeKilled;
}

int Enemy::GetFirstShotDelay() {
	return FirstShotDelay;
}

int Enemy::GetKillDelay() {
	return KillDelay;
}

int Enemy::GetLifeTime() {
	return LifeTime;
}

ENMY_TYPE Enemy::GetType() const {
	return Type;
}
