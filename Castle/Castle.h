#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\DS\List.h"
#include "Tower.h"


class Castle
{
	Tower Towers[NoOfRegions];
	Tower A;
	Tower B;
	Tower C;
	Tower D;
	double initialHealth;

	//
	// TODO: Add More Data Members As Needed
	//
	
public:

	Castle();
	void SetTowersHealth(double h);
	double getDamage(int i);
	int getUnpaved(int i);
	void SetTowersFire(double F);
	void SetTowersNum(int N);
	void Print(GUI* pGUI);
	Tower* getA();
	Tower* getB();
	Tower* getC();
	Tower* getD();
	void moveEnemies();
	//
	// TODO: Add More Member Functions As Needed
	//
};
