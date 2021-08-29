#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class GUI;
// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{
protected:
	const int ID;               //Each enemy has a unique ID (sequence number)
	const int ArrvTime;	        //arrival time (time it starts to join battle)
	static double HealthHeal;
	ENMY_STATUS status;	        //status of the enemy (inactive, inactive, frosted, killed)
	ENMY_TYPE Type;             //Type of the enemy (Fighter, Healer, Freezer)
	int Distance;	            //Horizontal distance between enemy & the tower of its region
	                            //Always positive (ranges from 2 to 60)

	double Health;	            //Enemy health
	double ReloadPeriod;        //Enemy reload period
	double Speed;               //Enemy Speed
	double Power;               //Enemy Power

	int FirstShot;              //The time of first shoot
	int TimeKilled;             //The time of being killed
	int FirstShotDelay;         //The time elapsed until an enemy is first shot by castle
	int KillDelay;              //The time elapsed between first time a castle shoots the enemy and its kill time
	int LifeTime;               //The total time an enemy stays alive until being killed
	int FreezingTime;
        double K;

public:
	Enemy(int id,int arrTime, int d = MaxDistance);
	virtual ~Enemy();

	int GetID() const;
	int GetArrvTime() const;

	ENMY_STATUS GetStatus() const;
	void SetStatus(ENMY_STATUS);

	ENMY_TYPE GetType()const;

	int GetDistance() const;
	void SetDistance(int );
	void DecrementDist();

	void SetHealth(double H);
	double GetHealth() const;
	void DecrementHealth();

	void SetReloadPeriod(double R);
	double GetReloadPeriod() const;

	void SetSpeed(double S);
	double GetSpeed() const;

	void SetPower(double P);
	double GetPower() const;

        void SetHealthHeal(double HH);
        double GetHealthHeal();

	void SetFreezingTime(int S);
	int GetFreezingTime() const;

	int GetFirstShot();
	int GetTimeKilled();
	int GetFirstShotDelay();         
	int GetKillDelay();              
	int GetLifeTime();


	// Virtual Functions: ----------------
        virtual void Move() = 0;	//All enemies can move
        virtual void Act() = 0;	//Acting means fighting or healing
        

	

};
