#include "Castle.h"
#include "..\DS\List.cpp"

Castle::Castle()
{
	A = Towers[0];
	B = Towers[1];
	C = Towers[2];
	D = Towers[3];
	Towers[0].setReg(A_REG);
	Towers[1].setReg(B_REG);
	Towers[2].setReg(C_REG);
	Towers[3].setReg(D_REG);
}

void Castle::SetTowersHealth(double h)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetHealth(h);
	}
	initialHealth = h;
}

double Castle::getDamage(int i)
{
	return initialHealth - Towers[i].GetHealth();
}

int Castle::getUnpaved(int i)
{
	return Towers[i].getUnPaved();
}

void Castle::SetTowersFire(double F)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetFirePower(F);
	}
}

void Castle::SetTowersNum(int N)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetN(N);
	}
}

void Castle::Print(GUI * pGUI)
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].Print(pGUI,i);
	}
}

Tower * Castle::getA()
{
	return& Towers[0];
}

Tower * Castle::getB()
{
	return&Towers[1];
}

Tower * Castle::getC()
{
	return &Towers[2];
}

Tower *Castle::getD()
{
	return &Towers[3];
}

void Castle::moveEnemies()
{
	if (!Towers[0].GetHealth() && !Towers[1].GetHealth() && !Towers[2].GetHealth() && !Towers[3].GetHealth())
		return;
	for (int i = 0; i < 4; i++)
	{
		int o = i + 1;
		if (i == 3)
			o = 0;
		if (!Towers[i].GetHealth())
		{
			Towers[o].getTowerActive().addList(Towers[i].getTowerActive());
			Towers[o].getTowerActiveSh().addList(Towers[i].getTowerActiveSh());
				Towers[i].getTowerActiveSh().startLoop();
				Enemy* E = Towers[i].getTowerActiveSh().getref();
				while (E)
				{

					E->setTower(&Towers[o]);
					E->setReg(Towers[o].getRegenum());
					if (E->GetDistance() < E->GetTower()->getUnPaved())
						E->SetDistance(E->GetTower()->getUnPaved() + 1);
					Towers[i].getTowerActiveSh().plus();
					E = Towers[i].getTowerActiveSh().getref();
				}
				Towers[i].getTowerActive().startLoop();
				E = Towers[i].getTowerActive().getref();
				while (E)
				{
					E->setTower(&Towers[o]);
					E->setReg(Towers[o].getRegenum());
					if (E->GetDistance() < E->GetTower()->getUnPaved())
						E->SetDistance(E->GetTower()->getUnPaved() + 1);
					Towers[i].getTowerActive().plus();
					E = Towers[i].getTowerActive().getref();
				}
				Towers[i].getTowerActive().clear();
				Towers[i].getTowerActiveSh().clear();
			
		}
	}
}
