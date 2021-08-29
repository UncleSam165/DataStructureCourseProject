#pragma once

#include "Castle\Castle.h"
#include "Enemies/Fighter.h"
#include "Enemies/Freezer.h"
#include "Enemies/Healer.h"
#include "Generic_DS\Queue.h"
#include "Generic_DS/PriorityQ.h"
#include "Generic_DS/Stack.h"
#include "GUI\GUI.h"
#include <time.h>
#include "ReadInputFile.h"
#include <fstream>
#include <string>

// it is the controller of the project
class Battle
{
private:
	GUI* pGUI;
	Castle BCastle;
	int EnemyCount;	//the actual number of enemies in the game
	int ActiveCount, ActiveFighters, ActiveHealers, ActiveFreezers, 
	FrostedCount,FrostedFighters,FrostedHealers,FrostedFreezers,
	KilledCount,KilledFighters,KilledHealers,KilledFreezers,
		CastleDefreezeTimeStep;	//no. of enemies (Active, Frosted, killed so far)
	Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function

	GAME_RESULT result;
	Queue<Enemy*> Q_Inactive;		//Queue of inactive enemies
	PriorityQ<Enemy*,double> Q_ActiveFighter;
	Stack<Enemy*> Q_ActiveHealer;
	Queue<Enemy*> Q_ActiveFreezer;
	Queue<Enemy*> Q_KilledEnemies;
	PriorityQ<Enemy*,int> Q_FrozenEnemies;


	
public:
	
	Battle();
	void AddAllListsToDrawingList();		//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
	
	Castle * GetCastle();
	void RunSimulation();
	void ActivateEnemies();		//check the inactive list and activate all enemies that has arrived
	void Move();
	void Fight();
	void DeleteKilledEnemy();
	void AddEnemy(Enemy* Ptr);		//Add Enemy to the  queue of enemies 
	void Interactive();
	void Kill(Enemy*& E);
	void CastleAttack();
	void CastleFreeze();
	void RestoreFrozen();
	GAME_RESULT BattleCheck();
	void Save();
	void EnemyAct();
	void ActivateCastle();
	void DefrostEnemies();
	void StepByStep();
	void Silent();
	void FreezeCastle();
};
 

