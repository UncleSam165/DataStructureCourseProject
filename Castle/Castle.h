#pragma once
#include "..\Enemies\Enemy.h"
#include <cstdlib>

class Castle
{
	int NumberOfEnemies;			//Number of enemies can be killed in time step
	double Health;                   //Health of the Castle
	double MaxHealth;
	double Power;                    //Power of the Castle
	double AccomultedIce;
	ENMY_STATUS status;

public:
	bool isDestroyed();

	int GetNumberOfEnemies();
	void SetNumberOfEnemies(int N);

	double GetHealth() const;
	void SetHealth(double h);
	void DecrementHealth(double damage);

	double GetPower() const;
	void SetPower(double P);

	void SetStatus(ENMY_STATUS S);
	ENMY_STATUS GetStatus() const;
	void Damage(Enemy* &E);
	void SetAccumulatedIce(double d);
	double GetAccumulatedIce();
	void SetMaxHealth(double CH);
	double GetMaxHealth();
};
 
