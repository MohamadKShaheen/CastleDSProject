#pragma once
#include"../DS/List.h"
#include "../Enemies/Enemy.h"
#include"../DS/PList.cpp"
#include "../GUI/GUI.h"

class Tower
{
	double Health;
	int MaxN;
	int Firepower;
	double Damage_to_tower;
	int totalKilled;
	int UnPaved;
	REGION reg;
	
	//Double
	List<Enemy*> active;
	PList<Enemy*>activeSh;
	// we are gonna make listof killed for each tower not for all towers because getting killed then pushing them to battle killed list is big O ( N ^ 2 ) 
	// but if every tower have his own list O(N)








	//end Double
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Tower();
	void SetHealth(double h);
	double GetHealth() const;
	void SetN(int N);				//To set the max number of shooted Enemy
	void SetFirePower(double FP); 	//To set the fire power of the tower
	double Get_FirePower();
	//void Damage_Tower(int DIS, int FP,int k);
	void setActive(Enemy*E);
	void setKilled(int n,PList<Enemy*>& Killed);// func to set enemies whose health = 0 to killed list and removing them from active list
	List<Enemy*>& getTowerActive();
	PList<Enemy*>& getTowerActiveSh();
	int getNomTotalKilled();
	void setTotalKilled(int x);
	void Tower_Fight(int t,double& FD,int& count);
	int getUnPaved();
	void setUnPaved(int y);
	void setReg(REGION r);
	string getRegstring();
	REGION getRegenum();

	void Print(GUI* pGUI, int indx);
	// TODO: Add More Member Functions As Needed
	//

};

