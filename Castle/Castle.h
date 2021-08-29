#pragma once
#include "..\Defs.h"
#include "..\Generic_DS\PriorityQ.h"
#include "..\Generic_DS\Queue.h"
#include "..\Generic_DS\Stack.h"
#include "..\Enemies\Fighter.h"
#include "..\Enemies\Healer.h"
#include "..\Enemies\Freezer.h"
#include <cstdlib>

class Castle
{
	int NumberOfEnemies;             //Number of enemies can be killed in time step
	double Health;                   //Health of the Castle
	double Power;                    //Power of the Castle
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
};
 
