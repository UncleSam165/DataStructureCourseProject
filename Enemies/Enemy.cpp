#include "Enemy.h"
#include <cstdlib>

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


void Enemy::SetFreezingTime(int S)
{
	if (dynamic_cast<Fighter*>(this) || dynamic_cast<Freezer*>(this))
	{
		FreezingTime = ceil(2 * (1 / Distance) * S);   // Assuming that the castle freezing power = 5
	}
	else
	{
		FreezingTime = ceil((1 / Distance) * S);
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

void Enemy::SetMaxHealth(double H) {
	MaxHealth = H;
}

double Enemy::GetMaxHealth() {
	return MaxHealth;
}

void Enemy::DecrementFreeze() {
	FreezingTime--;
}