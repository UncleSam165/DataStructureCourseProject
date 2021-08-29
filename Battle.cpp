#include "Battle.h"
#include <time.h>
#include "ReadInputFile.h"
#include "./Defs.h"
#include <fstream>
#include <string>

Battle::Battle()
{
	EnemyCount = 0;
	KilledCount = 0;
	ActiveCount = 0;
	ActiveFighters = 0;
	ActiveFreezers = 0;
	ActiveHealers = 0;
	FrostedCount = 0;
	FrostedFighters = 0;
	FrostedFreezers = 0;
	FrostedHealers = 0;
	KilledFighters = 0;
	KilledHealers = 0;
	KilledFreezers = 0;
	CurrentTimeStep = 0;
	CastleDefreezeTimeStep = 0;
	pGUI = NULL;
	BCastle.SetStatus(ACTV);
}

void Battle::AddEnemy(Enemy* Ptr)
{
	if(Ptr->GetType() == FIGHTER){
		Q_ActiveFighter.enqueue(Ptr, Ptr->GetPower() * Ptr->GetHealth() * (static_cast<double>(Ptr->GetStatus()) / (double)Ptr->GetDistance()));
		ActiveFighters++;
	}else if(Ptr->GetType() == HEALER){
		Q_ActiveHealer.push(Ptr);
		ActiveHealers++;
	}else if(Ptr->GetType() == FREEZER){
		Q_ActiveFreezer.enqueue(Ptr);
		ActiveFreezers++;
	}
}



Castle * Battle::GetCastle()
{
	return &BCastle;
}


void Battle::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		Interactive();
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	

	}

	delete pGUI;
	
}

//check the inactive list and activate all enemies that has arrived
void Battle::ActivateEnemies()
{
	Enemy* pE;
	while (Q_Inactive.peekFront(pE))	//as long as there are more inactive enemies
	{
		if (pE->GetArrvTime() > CurrentTimeStep)	//no more arrivals at current time
			return;

		Q_Inactive.dequeue(pE);	//remove enemy from the queue
		pE->SetStatus(ACTV);	//make status active
		EnemyCount++;
		ActiveCount++;
		AddEnemy(pE);		//move it to Enemy List
	}

}

void Battle::Move()
{
	Enemy* const * FighterList = Q_ActiveFighter.toArray(ActiveFighters);
	for (int i = 0; i < ActiveFighters; i++) {
		FighterList[i]->Move();
	}
	Enemy* const * HealerList = Q_ActiveHealer.toArray(ActiveHealers);
	for (int i = 0; i < ActiveHealers; i++) {
		HealerList[i]->Move();
	}
	Enemy* const * FreezerList = Q_ActiveFreezer.toArray(ActiveFreezers);
	for (int i = 0; i < ActiveFreezers; i++) {
		FreezerList[i]->Move();
	}
}

void Battle::Fight()
{
	ActivateCastle();
	DefrostEnemies();
	RestoreFrozen();
	CastleAttack();
}

void Battle::DeleteKilledEnemy()
{
	Enemy* E;
	while (!Q_KilledEnemies.isEmpty())
	{
		Q_KilledEnemies.dequeue(E);
		delete E;
	}
}

//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
void Battle::AddAllListsToDrawingList()
{	
	//Add inactive queue to drawing list
	int InactiveCount;
	Enemy* const * EnemyList = Q_Inactive.toArray(InactiveCount);
	for(int i=0; i<InactiveCount; i++)
		pGUI->AddToDrawingList(EnemyList[i]);

	int FighterCount;
	Enemy* const * EnemyList1 = Q_ActiveFighter.toArray(FighterCount);
	for(int i=0; i<FighterCount; i++)
		pGUI->AddToDrawingList(EnemyList1[i]);


	int HealerCount;
	Enemy* const * EnemyList2 = Q_ActiveHealer.toArray(HealerCount);
	for(int i=0; i<HealerCount; i++)
		pGUI->AddToDrawingList(EnemyList2[i]);


	int FreezerCount;
	Enemy* const * EnemyList3 = Q_ActiveFreezer.toArray(FreezerCount);
	for(int i=0; i<FreezerCount; i++)
		pGUI->AddToDrawingList(EnemyList3[i]);

	int FrostedCount;
	Enemy* const* EnemyList4 = Q_FrozenEnemies.toArray(FrostedCount);
	for (int i = 0; i < FrostedCount; i++)
		pGUI->AddToDrawingList(EnemyList4[i]);

	int KilledCount;
	Enemy* const* EnemyList5 = Q_KilledEnemies.toArray(KilledCount);
	for (int i = 0; i < KilledCount; i++)
		pGUI->AddToDrawingList(EnemyList5[i]);
}

void Battle::Interactive(){
	pGUI->PrintMessage("Interactive Mode Selected ... Please Enter the input file Name and Destination:");
	string FileName = pGUI->GetString().c_str();	//get user input as a string then convert to integer

	pGUI->PrintMessage("Enemies is being loaded from the file...CLICK to continue");
	pGUI->waitForClick();

	CurrentTimeStep = 0;
	ReadInputFile(FileName, Q_Inactive, BCastle);
	cout << BCastle.GetHealth() << endl;;
	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.GetStatus(), ActiveCount, ActiveFighters, ActiveHealers, ActiveFreezers,
		FrostedCount, FrostedFighters, FrostedHealers, FrostedFreezers,
		KilledCount, KilledFighters, KilledHealers, KilledFreezers);	//upadte interface to show the initial case where all enemies are still inactive

	pGUI->waitForClick();

	while (&BCastle && (!Q_Inactive.isEmpty() || !Q_ActiveFighter.isEmpty() || !Q_ActiveFreezer.isEmpty() || !Q_ActiveHealer.isEmpty() || !Q_FrozenEnemies.isEmpty()))	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();

		Fight();

		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep, BCastle.GetHealth(), BCastle.GetStatus(), ActiveCount, ActiveFighters, ActiveHealers, ActiveFreezers,
			FrostedCount, FrostedFighters, FrostedHealers, FrostedFreezers,
			KilledCount, KilledFighters, KilledHealers, KilledFreezers);
		pGUI->waitForClick();
	}

}



void Battle::Kill(Enemy* &E) {
	KilledCount++;
	if (E->GetStatus() == ACTV) {
		if (dynamic_cast<Fighter*>(E)) {
			ActiveFighters--;
			ActiveCount--;
			KilledFighters++;
		}
		else if (dynamic_cast<Healer*>(E)) {
			ActiveHealers--;
			ActiveCount--;
			KilledHealers++;
		}
		else if (dynamic_cast<Freezer*>(E)) {
			ActiveFreezers--;
			ActiveCount--;
			KilledFreezers++;
		}
	}
	else if (E->GetStatus() == FRST) {
		if (dynamic_cast<Fighter*>(E)) {
			FrostedCount--;
			FrostedFighters--;
			KilledFighters++;
		}
		else if (dynamic_cast<Healer*>(E)) {
			FrostedCount--;
			FrostedHealers--;
			KilledHealers++;
		}
		else if (dynamic_cast<Freezer*>(E)) {
			FrostedFreezers--;
			FrostedCount--;
			KilledFreezers++;
		}
	}
	E->SetStatus(KILD);
	Q_KilledEnemies.enqueue(E);
}

void Battle::CastleAttack()
{
	if (BCastle.GetStatus() != FRST) {
		Enemy* E; Queue<Enemy*> Q_DamagedEnemies;
		for (int i = 0; i < BCastle.GetNumberOfEnemies(); i++) {
			if (!Q_ActiveFighter.isEmpty())
			{
				Q_ActiveFighter.dequeue(E);
				BCastle.Damage(E);
				Q_DamagedEnemies.enqueue(E);
			}
			else {
				if (!Q_ActiveHealer.isEmpty()) {
					Q_ActiveHealer.pop(E);
					BCastle.Damage(E);
					Q_DamagedEnemies.enqueue(E);
				}
				else {
					if (!Q_ActiveFreezer.isEmpty()) {
						Q_ActiveFreezer.dequeue(E);
						BCastle.Damage(E);
						Q_DamagedEnemies.enqueue(E);
					}
					else {
						if (!Q_FrozenEnemies.isEmpty()) {
							Q_FrozenEnemies.dequeue(E);
							BCastle.Damage(E);
							Q_DamagedEnemies.enqueue(E);
						}
					}
				}
			}
		}
		for (int i = 0; i < BCastle.GetNumberOfEnemies(); i++) {
			Q_DamagedEnemies.dequeue(E);
			if (E->GetHealth() == 0) {
				Kill(E);
			}
			else {
				if (dynamic_cast<Fighter*>(E)) {
					dynamic_cast<Fighter*>(E)->UpdatePriority();
					Q_ActiveFighter.enqueue(E, dynamic_cast<Fighter*>(E)->GetPriority());
				}
				else if (dynamic_cast<Healer*>(E)) {
					Q_ActiveHealer.push(E);
				}
				else if (dynamic_cast<Freezer*>(E)) {
					Q_ActiveFreezer.enqueue(E);
				}
			}
		}
	}
}

void Battle::CastleFreeze() {
	Enemy* E;
	for (int i = 0; i < BCastle.GetNumberOfEnemies(); i++) {
		if (!Q_ActiveFighter.isEmpty()){
			Q_ActiveFighter.dequeue(E);
			ActiveFighters--;
			FrostedFighters++;
			E->SetFreezingTime(BCastle.GetPower());
			E->SetStatus(FRST);
			Q_FrozenEnemies.enqueue(E,E->GetFreezingTime());
		}
		else {
			if (!Q_ActiveHealer.isEmpty()) {
				Q_ActiveHealer.pop(E);
				ActiveHealers--;
				FrostedHealers++;
				E->SetFreezingTime(BCastle.GetPower());
				E->SetStatus(FRST);
				Q_FrozenEnemies.enqueue(E, E->GetFreezingTime());
			}
			else {
				if (!Q_ActiveFreezer.isEmpty()) {
					Q_ActiveFreezer.dequeue(E);
					ActiveFreezers--;
					FrostedFreezers++;
					E->SetFreezingTime(BCastle.GetPower());
					E->SetStatus(FRST);
					Q_FrozenEnemies.enqueue(E, E->GetFreezingTime());
				}
			}
		}
	}
}

void Battle::DefrostEnemies() {
	Enemy* E; Queue<Enemy*> Temp;
	while (!Q_FrozenEnemies.isEmpty())	//as long as there are more inactive enemies
	{
		Q_FrozenEnemies.dequeue(E);
		E->DecrementFreeze();
		Temp.enqueue(E);
	}
	while (!Temp.isEmpty())
	{
		Temp.dequeue(E);
		Q_FrozenEnemies.enqueue(E, E->GetFreezingTime());
	}
}

void Battle::RestoreFrozen()
{
	Enemy* E;
	while(Q_FrozenEnemies.peekFront(E))
	{
		if (E->GetFreezingTime() <= 0)
		{
			Q_FrozenEnemies.dequeue(E);
			E->SetStatus(ACTV);
			if (dynamic_cast<Fighter*>(E))
			{
				Q_ActiveFighter.enqueue(E,dynamic_cast<Fighter*>(E)->GetPriority());
				ActiveFighters++;
				FrostedFighters--;
			}
			else if (dynamic_cast<Healer*>(E))
			{
				Q_ActiveHealer.push(E);
				ActiveHealers++;
				FrostedHealers--;
			}
			else if (dynamic_cast<Freezer*>(E))
			{
				Q_ActiveFreezer.enqueue(E);
				ActiveFreezers++;
				FrostedFreezers--;
			}		
		}
	}
}



void Battle::Save()
{
	ofstream myfile;
	myfile.open("example.txt");

	if (BattleCheck() == WIN)
		myfile << "Game Is WIN.\n";
	else if (BattleCheck() == LOSS)
		myfile << "Game Is LOSS.\n";
	else
		myfile << "Game Is DRAWN.\n";

	myfile << "KTS\t ID\t FD\t KD\t LT\n";

	myfile.close();
}

GAME_RESULT Battle::BattleCheck() {

}

void Battle::EnemyAct() {
	Queue<Enemy*> Q_Temp; Stack<Enemy*> S; Enemy* E,*P;
	while (!Q_ActiveFighter.isEmpty()) {
		Q_ActiveFighter.dequeue(E);
		dynamic_cast<Fighter*>(E)->Act(BCastle);
		Q_Temp.enqueue(E);
	}
	while (!Q_Temp.isEmpty()) {
		Q_Temp.dequeue(E);
		Q_ActiveFighter.enqueue(E, dynamic_cast<Fighter*>(E)->GetPriority());
	}
	while (!Q_ActiveFreezer.isEmpty()) {
		Q_ActiveFreezer.dequeue(E);
		dynamic_cast<Freezer*>(E)->Act(BCastle);
		Q_Temp.enqueue(E);
	}
	while (!Q_Temp.isEmpty()) {
		Q_Temp.dequeue(E);
		Q_ActiveFreezer.enqueue(E);
	}

	while (!Q_ActiveHealer.isEmpty()) {
		Q_ActiveHealer.pop(E);
		while (!Q_ActiveFighter.isEmpty())
		{
			Q_ActiveFighter.dequeue(P);
			dynamic_cast<Healer*>(E)->Act(P);
			dynamic_cast<Fighter*>(P)->UpdatePriority();
			Q_Temp.enqueue(P);
		}
		while (!Q_Temp.isEmpty()) {
			Q_Temp.dequeue(P);
			Q_ActiveFighter.enqueue(P, dynamic_cast<Fighter*>(P)->GetPriority());
		}
		while (!Q_ActiveFreezer.isEmpty()) {
			Q_ActiveFreezer.dequeue(P);
			dynamic_cast<Healer*>(E)->Act(P);
			Q_Temp.enqueue(P);
		}
		while (!Q_Temp.isEmpty()) {
			Q_Temp.dequeue(P);
			Q_ActiveFreezer.enqueue(P);
		}
		S.push(E);
	}
	while (!S.isEmpty())
	{
		S.pop(E);
		Q_ActiveHealer.push(E);
	}

}

void Battle::ActivateCastle() {
	if (CurrentTimeStep >= CastleDefreezeTimeStep)
		BCastle.SetStatus(ACTV);
}

