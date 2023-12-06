#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include<string>
class Tower;
// Enemy is the base class of each type of enemy
// Enemy is an abstract class.
class Enemy
{

protected:
	int ID;				//Each enemy has a unique ID (sequence number)
	color Clr;			//Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	REGION Region;		//Region of this enemy
	int Distance;		//Horizontal distance between enemy & the tower of its region
						//Always positive (ranges from 2 to 60)
	double Health;		//Enemy health
	int Firepower;	//Enemy power
	int Arrival;		//Arrival Time
	int Period;		//Reload time period
	string region;	//the recived region from the list
	double Damage;  //damage by tower
	int T_First;//check after each time step if(-1) && is shot now so set T_First = time step 
	int First_shoot;
	int T_Killed;//if health = 0 T_Killed = time step
	int Kill_Delay;
	int Life_time;
	int remaining_to_shoot;
	static double C1, C2, C3;
	Tower* t;

public:
	Enemy(string R,Tower* A, int id, int FP, int T, double health, int p);
	virtual ~Enemy();

	color GetColor() const;
	REGION GetRegion() const;
	void set_health(double H);
	double get_health();
	virtual void DecrementDist()=0;
	void set_Arrival_time(int time);
	int Get_Arrival_time();
	void SetDistance(int d);
	int GetDistance() const;
	void setregion(string R);
	void set_reload_time(int t);
	int get_reload_time();
	void set_fire_power(double fp);
	double get_fire_power();
	void set_ID(int id);
	int Get_ID();
	void Set_T_First(int F);
	int Get_T_First();
	void Set_First_shot();//is called when T_First != -1
	int get_First_shot();
	void Set_T_Killed(int k);
	int Get_T_Killed();
	void Set_Kill_Delay();//is called when killed only 
	int get_Kill_Delay();
	void Set_Life_Time();// is called when killed only
	int Get_Life_Time();
	void setConsts(double x, double y, double z);
	virtual int Get_K()=0;
	// Virtual Functions: ----------------

	//virtual void Move() = 0;	    //All enemies can move
	//virtual void Attack() = 0;	//All enemies can attack (attacking is paving or shooting)
	virtual void Damage_to_Enemy(int fire_power_tower)=0;
	virtual double PSE() = 0;
	//
	// TODO: Add More Member Functions As Needed
	//
    int set_remaining();
	virtual bool isShielded() = 0;
	virtual void Fight(int TimeStep) = 0;
	Tower* &GetTower();
	void setTower(Tower * g);
	void setReg(REGION o);
	
};

