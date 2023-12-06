#pragma once
#include "Castle\Castle.h"
#include "Enemies\Fighter.h"
#include "Enemies\Pavor.h"
#include "Enemies\Shielded.h"
#include "Enemies\Grenade.h"
#include "Enemies\Jumper.h"
#include "DS\List.h"
#include "DS\PList.h"
#include <fstream>
#include<iostream>
// it is the controller of the project
class Battle
{
private:
	int TotalEnemy;
	Castle BCastle;
	List <Enemy*> EnemiesInactive;
	int EnemyCount;	//the actual number of enemies in the game
	Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
	PList <Enemy*> Killed;							  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy ///////pointers. 
										 	// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function

	//
	// TODO: Add More Data Members As Needed
	//
	//Double
	Tower* A;
	Tower* B;
	Tower* C;
	Tower* D;
	





	//endDouble
public:
	
	Battle();
	void ReadFile(GUI*);
	void modes(Actiontype, GUI* pGUI);
	
	void AddEnemy(Enemy* Ptr);
	void DrawEnemies(GUI * pGUI);
	Castle * GetCastle();
	void setActive(int time);// func to move recent active enemies from inactive list to appropriate active list 
	void simBattle(GUI*pGUI,Actiontype);// func to simulate battle
	//void simPrint(GUI*pGUI);// func to print on status bar in simulation
	void Print(GUI* pGUI, int t);
	void setEnemiesArr(int &size);//func to set enemies in BEnemiesForDraw

	void Excuete(Actiontype, GUI * pGUI);//func to execute a certain action after clicking on an icon
	void Clear(GUI*pGUI);// func to clear all lists 
	void EnemyFight();
	int endGame();			//if return 0 game win
							//if return 1 game lose
							//if return 2 continue
	//void moveEnemies();
};

