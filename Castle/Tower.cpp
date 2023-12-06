#include "Tower.h"
#include"../DS/List.cpp"

Tower::Tower()
{
	totalKilled = 0;
	UnPaved = 30;
}

void Tower::SetHealth(double h)
{
	if (h > 0)
		Health = h;
	else
		Health = 0; // killed
}


double Tower::GetHealth() const
{
	return Health;
}

void Tower::SetN(int N)
{
	MaxN = (N >= 0) ? N : 0;
}

void Tower::SetFirePower(double FP)
{
	if (FP < 0)
		FP = -FP;
	Firepower = FP;
}

double Tower::Get_FirePower()
{
	return Firepower;
}

//void Tower::Damage_Tower(int DIS, int FP, int k)
//{
//	Damage_to_tower = (k / DIS)*FP;
//	Health -= Damage_to_tower;
//	if (Health < 0)
//	{
//		Health = 0;
//	}
//}
void Tower::setActive(Enemy * E)
{

	if (E->isShielded())//check if the enemy shielded
		activeSh.addItem(E, E->PSE());//adding enemy and its priority (priority for sorting list)
	else
		active.addItem(E);//adding enemy in normal active if it is not shielded
}

void Tower::setKilled(int n,PList<Enemy*>& Killed)
{
	active.startLoop();
	Enemy * p;
	p = active.getref();
	while (p != nullptr)// loop on active (fighter & paver enemies only)
	{
		if (p->get_health() == 0)// check if health = 0 so kill that enemy 
		{
			p->Set_T_Killed(n);//set killed time
			Killed.addItem(p, p->get_First_shot());//adding enemy in killed list 
			active.removeItem(p);// removing enemy from active list
			totalKilled++;
		}
		active.plus();
		p = active.getref();
	}
	activeSh.startLoop();
	
	p = activeSh.getref();
	if (p != nullptr) {
		p->Set_T_Killed(n);
	}
	while (p != nullptr)// loop on active(Shielded) enemies
	{
		if (p->get_health() == 0)
		{
			p->Set_T_Killed(n);//set killed time
			Killed.addItem(p, p->get_First_shot());//adding enemy in killed list 
			activeSh.removeItem(p);// removing enemy from active list
			totalKilled++;
		}
	
		activeSh.plus();
		p = activeSh.getref();
	}
}

List<Enemy*>& Tower::getTowerActive()
{
	return active;
}

PList<Enemy*>& Tower::getTowerActiveSh()
{
	return activeSh;
}



int Tower::getNomTotalKilled()
{
	return totalKilled;
}

void Tower::setTotalKilled(int x)
{
	totalKilled = x;
}

void Tower::Tower_Fight(int t,double& FD,int& count)
{
	if (MaxN > activeSh.getCurrentSize())
	{
		activeSh.startLoop();
		Enemy* E = activeSh.getref();
		while (E != NULL)
		{
			E->Damage_to_Enemy(Firepower);
			if (E->Get_T_First() == 0)
			{
				E->Set_T_First(t);
				E->Set_First_shot();
				FD += E->get_First_shot();
				count++;
			}
			activeSh.plus();
			E = activeSh.getref();
		}
		int n = MaxN - activeSh.getCurrentSize();
		E = NULL;
		active.startLoop();
		E = active.getref();
		for (int i = 0;i < n, E != NULL;i++)
		{
			E->Damage_to_Enemy(Firepower);
			if (E->Get_T_First() == 0)
			{
				E->Set_T_First(t);
				E->Set_First_shot();
				FD += E->get_First_shot();
				count++;
			}
			active.plus();
			E = active.getref();
		}
	}
	else
	{
		activeSh.startLoop();
		Enemy* E = activeSh.getref();
		for(int i=0;i<MaxN;i++)
		{
			E->Damage_to_Enemy(Firepower);
			if (E->Get_T_First() == 0)
			{
				E->Set_T_First(t);
				E->Set_First_shot();
				FD += E->get_First_shot();
				count++;
			}
			activeSh.plus();
			E = activeSh.getref();
		}
	}
}

int Tower::getUnPaved()
{
	return UnPaved;
}
void Tower::setUnPaved(int y)
{

	if (y < 2)
		y = 1;
	UnPaved = y;
}

void Tower::setReg(REGION r)
{
	reg = r;
}

string Tower::getRegstring()
{
	switch (reg) {
	case 0 :
		return "A";
		break;
	case 1:
		return "B";
		break;
	case 2: 
		return "C";
		break;
	case 3:
		return "D";
		break;
	}
}

REGION Tower::getRegenum()
{
	return reg;
}

void Tower::Print(GUI * pGUI, int ind)
{
	ind = (ind == 2 || ind == 3) ? 6 : 0;
	if (Health != 0)
	{
		pGUI->PrintMessage(reg, "Region "+getRegstring(), 2 + ind, DARKRED);
		pGUI->PrintMessage(reg, "	Tower Health = " + to_string(Health), 3 + ind);
		pGUI->PrintMessage(reg, "	No. Active Enemies = " + to_string(active.getCurrentSize() + activeSh.getCurrentSize()), 4 + ind);
		pGUI->PrintMessage(reg, "	No. Killed Enemies = " + to_string(totalKilled), 5 + ind);
		pGUI->PrintMessage(reg, "	UnPaved Distance = " + to_string(UnPaved), 6 + ind);
	}
}

