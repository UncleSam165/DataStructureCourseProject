#pragma once
#include<iostream>
#include<fstream>
#include"Castle/Castle.h"
#include"Battle.h"

using namespace std;
void ReadInputFile(string filename, Queue<Enemy*> &Q_Inactive, Castle &BCastle)
{
	
	fstream inputFile("D:\\Study\\Summer21\\Data Structure\\testfile.txt");  	// read data from the file
	if (inputFile.is_open()) // checking if the file has been opened or not
	{
		cout << "The input file has been opened successfully!" << endl;
	}
	else
	{
		cout << "Error! the input file cannot be opened successfully!" << endl;
	}
	int CH, N, CP; // CH stands for castle health, N stands for number of enemies the castle could attack at each time step, CP stands for castle power 
	inputFile >> CH >> N >> CP;
	cout << "CASTLE HEALTH IS " << CH << " " << "N is " << N << " " << "CASTLE POWER is " << CP << endl; // print Castle Data on the conselo
	BCastle.SetHealth(CH);
	BCastle.SetMaxHealth(CH);
	BCastle.SetNumberOfEnemies(N);
	BCastle.SetPower(CP);
	cout << BCastle.GetHealth() << "HIIII" << BCastle.GetNumberOfEnemies() << "     " << BCastle.GetPower() << endl;

	int M; // M stands for number of enemies
	inputFile >> M;
	cout << M << " ";
	int ID, TYP, AT, H, POW, RLD, SPD; // stands for Enemy ID
	Enemy* pE = NULL;
	for (int i = 0; i < M; i++)
	{
		while (!inputFile.eof())
		{
			inputFile >> ID;
			cout << "ID" << "   " << ID << endl;
			inputFile >> TYP;
			cout << "TYP" << "      " << TYP << endl;
			inputFile >> AT;
			cout << "AT" << "    " << AT << endl;
			if(TYP == 0){
				pE = new Fighter(ID, AT);
			}else if(TYP == 1){
				pE = new Healer(ID, AT);
			}else if(TYP == 2){
				pE = new Freezer(ID, AT);
			}
			inputFile >> H;
			pE->SetHealth(H);
			pE->SetMaxHealth(H);
			cout << "H" << "       " << H << endl;
			inputFile >> POW;
			pE->SetPower(POW);
			cout << "POW" << "         " << POW << endl;
			inputFile >> RLD;
			pE->SetReloadPeriod(RLD);
			cout << "RLD" << "           " << RLD << endl;
			inputFile >> SPD;
			pE->SetSpeed(SPD);
			cout << "SPD" << "         " << SPD << endl;
			pE->SetStatus(INAC); //initiall all enemies are inactive
			Q_Inactive.enqueue(pE);
			if (inputFile.eof()) break;
		}





	}
	inputFile.close();
	cout << "Closed!" << endl;
}