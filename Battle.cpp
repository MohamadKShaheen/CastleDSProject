#include "Battle.h"
#include "DS\List.cpp"
#include<iostream>

Battle::Battle()
{
	EnemyCount = 0;
	A = BCastle.getA();
	B = BCastle.getB();
	C = BCastle.getC();
	D = BCastle.getD();

}

void Battle::ReadFile(GUI* PGUI)
{
	string FileName;
	Point p;
	PGUI->PrintMessage("Enter name");
	FileName = PGUI->GetString();
	FileName += ".txt";

	ifstream Input(FileName);

	//Check if the file is exist
	while (!Input.is_open())
	{
		PGUI->PrintMessage("File is Not Found ,Please Try Again");
		PGUI->GetPointClicked(p);
		PGUI->ClearStatusBar();
		FileName = PGUI->GetString();
		FileName += ".txt";
		Input.open(FileName);
	}

	//Read Information of Towers
	double InHealth;
	int Fire;
	int N;
	Input >> InHealth >> N >> Fire;
	BCastle.SetTowersHealth(InHealth);		//Set Initial Health of	Towers
	BCastle.SetTowersFire(Fire);			//Set the Fire Power of Towers
	BCastle.SetTowersNum(N);				//Set Number of Enemy that Tower Can Shot

											//Read Constants for Shielded Enemy
	double C1, C2, C3;
	Input >> C1 >> C2 >> C3;

	//Read Enemies
	int Id, Time, Type, Reload;
	double Health, FireP;
	string Region;
	bool flag = false;
	while (Input >> Id && Id != -1) {
		Input >> Type >> Time >> Health >> FireP >> Reload >> Region;

		Tower *t = NULL;
		if (Region == "A")
			t = A;
		else if (Region == "B")
			t = B;
		else if (Region == "C")
			t = C;
		else if (Region == "D")
			t = D;
		Enemy * E = NULL;
		switch (Type)
		{
		case 0:
			E = new Pavor(Region, t, Id, FireP, Time, Health, Reload);
			break;

		case 1:
			E = new Fighter(Region, t, Id, FireP, Time, Health, Reload);
			break;

		case 2:
			E = new Shielded(Region, t, Id, FireP, Time, Health, Reload);
			if (!flag) {
				E->setConsts(C1, C2, C3);
				flag = true;
			}
			break;
		case 3:
			E = new Grenade(Region, t, Id, FireP, Time, Health, 0);
			break;
		case 4:
			E = new Jumper(Region, t, Id, FireP, Time, Health, Reload);
		}
		EnemiesInactive.addItem(E);
	}
	TotalEnemy = EnemiesInactive.getCurrentSize();
	Input.close();
}

void Battle::modes(Actiontype Act, GUI* pGUI)
{
	Point p;
	switch (Act) {
	case 1:
		pGUI->GetPointClicked(p);
		break;
	case 3:
		Sleep(1000);
		break;
	}
}

void Battle::AddEnemy(Enemy* Ptr)
{
	if (EnemyCount < MaxEnemyCount)
		BEnemiesForDraw[EnemyCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It only makes the first free pointer in the array
	// points to what is pointed to by the passed pointer Ptr
}

void Battle::DrawEnemies(GUI * pGUI)
{
	pGUI->DrawEnemies(BEnemiesForDraw, EnemyCount);
}

Castle * Battle::GetCastle()
{
	return &BCastle;
}

void Battle::setActive(int time)
{
	EnemiesInactive.startLoop();
	Enemy*p = EnemiesInactive.getref();

	while (p != nullptr)
	{
		// check if enemy has arrived 
		if (p->Get_Arrival_time() == time)
		{
			// check which enemy region and setting this enemy in active or activeSH list in tower of the region
			p->GetTower()->setActive(p);
			EnemiesInactive.removeItem(p); // delete the enemy from inactive list
		}
		// get the next enemy
		EnemiesInactive.plus();
		p = EnemiesInactive.getref();
	}
}

void Battle::simBattle(GUI*pGUI,Actiontype Act)
{
	int Killedcount = 0;
	int KD = 0;
	int count = 0;
	double FD = 0;
	ofstream OutPut("OutPut.txt");
	Point P;
	int s = 0;			//variable to indicate if no more inactive enemies to end the game
	int i = 0;
	OutPut << "KTS		S		FD		KD		LT\n";
	pGUI->DrawCastle(A->getUnPaved(), B->getUnPaved(), C->getUnPaved(), D->getUnPaved());
	while (endGame() == 2)
	{
		modes(Act, pGUI);
		pGUI->ClearStatusBar();
		if (i == 4)
			i = 4;
		//if (EnemyCount != 0)
		//{
		//	if (EnemyCount <= 4) {		// if active enemies are less than or equal 4 kill all of them
		//		for (int j = 0; j < EnemyCount; j++)
		//		{
		//			BEnemiesForDraw[j]->set_health(0);
		//		}
		//	}
		//	else {
		//		for (int j = 0; j < 4; j++)		// if more than 4 kill first 4 enemies in active enemies 
		//		{
		//			BEnemiesForDraw[j]->set_health(0);
		//		}
		//	}
		//}
		setActive(i + 1);					//func to set active enemies every time step
		A->setKilled(i + 1, Killed);				// func to kill enemies whose health == 0 in reg A
		B->setKilled(i + 1, Killed);				// func to kill enemies whose health == 0 in reg B	
		C->setKilled(i + 1, Killed);				// func to kill enemies whose health == 0 in reg C
		D->setKilled(i + 1, Killed);				// func to kill enemies whose health == 0 in reg D
		Killed.Sort();

		A->getTowerActiveSh().Sort();		// func to sort shielded enemies w.r.t. Priority(not needed in phase 1 .. it is just a test) 
		B->getTowerActiveSh().Sort();
		C->getTowerActiveSh().Sort();
		D->getTowerActiveSh().Sort();
		setEnemiesArr(EnemyCount);			// setting active enemies in BEnemiesForDraw 

		for (int j = 0; j < EnemyCount; j++)
		{
			BEnemiesForDraw[j]->Fight(i + 1);
			BCastle.moveEnemies();
			//moveEnemies();
		}
		A->Tower_Fight(i + 1, FD, count);
		B->Tower_Fight(i + 1, FD, count);
		C->Tower_Fight(i + 1, FD, count);
		D->Tower_Fight(i + 1, FD, count);
		if (Act != Silent)
		{
			pGUI->ClearBattleArea();
			pGUI->DrawCastle(A->getUnPaved(), B->getUnPaved(), C->getUnPaved(), D->getUnPaved());
			DrawEnemies(pGUI);
			Print(pGUI, i+1);
		}
		//simPrint(pGUI);
		// s = 0 means there are more than 4 active enemies or there are inactive enemies
		// s = 1 means there are some active enemies who will all be killed next time step and there are no more inactive enemies
		// s = 2 means there are no more active or inactive enemies so it is time to end the game
		/*if (s == 1)
			s = 2;
		else if (s == 2)
			return;
		else if (EnemiesInactive.getCurrentSize() == 0 && EnemyCount <= 4)
			s = 1;*/
			//Deleting enemies before deleting nodes in DS
		Killed.startLoop();
		Enemy* p = Killed.getref();
		while (p) {
			
			OutPut << i + 1 << "		" << p->Get_ID() << "		" << p->get_First_shot() << "		" << p->get_Kill_Delay() << "		" << p->Get_Life_Time() << endl;
			KD += p->get_Kill_Delay();
			delete p;
			Killed.plus();
			p = Killed.getref();
		}
		Killedcount += Killed.getCurrentSize();
		// clear killed enemies every time step
		Killed.clear();
		i++;
	}
	OutPut << " T1_Total_Damage		T2_Total_Damage		T3_Total_Damage		T4_Total_Damage" << endl;
	for (int j = 0; j < 4; j++)
	{
		OutPut << BCastle.getDamage(j)<<"		";
	}
	OutPut << endl;
	OutPut << "R1_Unpaved_Dist		R2_Unpaved_Dist		R3_Unpaved_Dist		R4_Unpaved_Dist" << endl;
	for (int j = 0; j < 4; j++)
	{
		OutPut << BCastle.getUnpaved(j)<<"		";
	}
	OutPut << endl;
	if (endGame() == 0)
	{
		OutPut << "Game Win" << endl;
		pGUI->PrintMessage("Game Win");
	}
	else
	{
		OutPut << "Game Lose" << endl;
		pGUI->PrintMessage("Game Lose");
	}
	OutPut << "Total Enemies = " << TotalEnemy << endl;
	OutPut << "Average First-Shot Delay = " << FD / count << endl;
	OutPut << "Average Kill Delay = " << (double)KD / Killedcount << endl;
	OutPut.close();
	Clear(pGUI);
	modes(Act, pGUI);
	pGUI->ClearBattleArea();
	pGUI->DrawCastle(A->getUnPaved(), B->getUnPaved(), C->getUnPaved(), D->getUnPaved());
}

//void Battle::simPrint(GUI*pGUI)
//{
//	int Aactive = A->getTowerActive().getCurrentSize() + A->getTowerActiveSh().getCurrentSize();
//	int Bactive = B->getTowerActive().getCurrentSize() + B->getTowerActiveSh().getCurrentSize();
//	int Cactive = C->getTowerActive().getCurrentSize() + C->getTowerActiveSh().getCurrentSize();
//	int Dactive = D->getTowerActive().getCurrentSize() + D->getTowerActiveSh().getCurrentSize();
//	/*int Akilled = A->getTowerKilled().getCurrentSize();
//	int Bkilled = B->getTowerKilled().getCurrentSize();
//	int Ckilled = C->getTowerKilled().getCurrentSize();
//	int Dkilled = D->getTowerKilled().getCurrentSize();*/
//	pGUI->PrintMessage("A", "Region A:	Tower Health: " + to_string((int)A->GetHealth()) + "	Tower FirePower: " + to_string((int)A->Get_FirePower()), 1);
//	pGUI->PrintMessage("A", "Total # of Active in 'A': " + to_string(Aactive) + "	Total # of Killed in 'A': " + to_string(A->getNomTotalKilled()) + " Killed in current time step: " + to_string(Akilled), 2);
//	if (Aactive > 4) {
//		Aactive = 4;
//		Akilled = 0;
//	}
//	else if (Aactive + Akilled > 4) {
//		Akilled = 4 - Aactive;
//	}
//
//	A->getTowerActiveSh().startLoop();
//	Enemy*paA = A->getTowerActiveSh().getref();
//	int i = 0;
//	while (paA != nullptr&&i < Aactive) {
//		pGUI->PrintMessage("A", "Enemy(ACTIVE) # " + to_string(paA->Get_ID()) + "	Arrival time: " + to_string(paA->Get_Arrival_time()) + "	Health : " + to_string((int)paA->get_health()), i + 3, RED);
//		A->getTowerActiveSh().plus();
//		paA = A->getTowerActiveSh().getref();
//		i++;
//	}
//	A->getTowerActive().startLoop();
//	paA = A->getTowerActive().getref();
//	//i = 0;
//	while (paA != nullptr&&i < Aactive) {
//		pGUI->PrintMessage("A", "Enemy(ACTIVE) # " + to_string(paA->Get_ID()) + "	Arrival time: " + to_string(paA->Get_Arrival_time()) + "	Health : " + to_string((int)paA->get_health()), i + 3, RED);
//		A->getTowerActive().plus();
//		paA = A->getTowerActive().getref();
//		i++;
//	}
//	A->getTowerKilled().startLoop();
//	Enemy*paK = A->getTowerKilled().getref();
//	if (paK != nullptr) {
//		for (int i = 0; i < Akilled; i++)
//		{
//			if (paK != nullptr) {
//				pGUI->PrintMessage("A", "Enemy(KILLED) # " + to_string(paK->Get_ID()) + "	Arrival time:    " + to_string(paK->Get_Arrival_time()) + "	  Kill time: " + to_string(paK->Get_T_Killed()), i + Aactive + 3, BLUE);
//			}
//			A->getTowerKilled().plus();
//			paK = A->getTowerKilled().getref();
//		}
//	}
//	pGUI->PrintMessage("B", "Region B:	Tower Health: " + to_string((int)B->GetHealth()) + "	Tower FirePower: " + to_string((int)B->Get_FirePower()), 1);
//	pGUI->PrintMessage("B", "Total # of Active in 'B': " + to_string(Bactive) + "	Total # of Killed in 'B': " + to_string(B->getNomTotalKilled()) + " Killed in current time step: " + to_string(Bkilled), 2);
//	if (Bactive + Bkilled > 4) {
//		Bkilled = 4 - Bactive;
//	}
//	if (Bactive > 4) {
//		Bactive = 4;
//	}
//	i = 0;
//	B->getTowerActiveSh().startLoop();
//	if (Bactive > 4) {
//		Bactive = 4;
//		Bkilled = 0;
//	}
//	else if (Bactive + Bkilled > 4) {
//		Bkilled = 4 - Bactive;
//	}
//	Enemy*pbA = B->getTowerActiveSh().getref();
//	while (pbA != nullptr&&i < Bactive) {
//
//		if (pbA != nullptr) {
//			pGUI->PrintMessage("B", "Enemy(ACTIVE) # " + to_string(pbA->Get_ID()) + "	Arrival time: " + to_string(pbA->Get_Arrival_time()) + "	Health : " + to_string((int)pbA->get_health()), i + 3, RED);
//		}
//		B->getTowerActiveSh().plus();
//		pbA = B->getTowerActiveSh().getref();
//		i++;
//
//	}
//	B->getTowerActive().startLoop();
//	pbA = B->getTowerActive().getref();
//	while (pbA != nullptr&&i < Bactive) {
//		if (pbA != nullptr) {
//			pGUI->PrintMessage("B", "Enemy(ACTIVE) # " + to_string(pbA->Get_ID()) + "	Arrival time: " + to_string(pbA->Get_Arrival_time()) + "	Health : " + to_string((int)pbA->get_health()), i + 3, RED);
//		}
//		B->getTowerActive().plus();
//		pbA = B->getTowerActive().getref();
//		i++;
//
//	}
//	B->getTowerKilled().startLoop();
//	Enemy*pbK = B->getTowerKilled().getref();
//	if (pbK != nullptr) {
//		for (int i = 0; i < Bkilled; i++)
//		{
//			if (pbK != nullptr) {
//				pGUI->PrintMessage("B", "Enemy(KILLED) # " + to_string(pbK->Get_ID()) + "	Arrival time: " + to_string(pbK->Get_Arrival_time()) + "	Kill time: " + to_string(pbK->Get_T_Killed()), i + 3 + Bactive, BLUE);
//			}
//			B->getTowerKilled().plus();
//			pbK = B->getTowerKilled().getref();
//		}
//	}
//	pGUI->PrintMessage("C", "Region C:	Tower Health: " + to_string((int)C->GetHealth()) + "	Tower FirePower: " + to_string((int)C->Get_FirePower()), 150 / 24 + 1);
//	pGUI->PrintMessage("C", "Total # of Active in 'C': " + to_string(Cactive) + "	Total # of Killed in 'C': " + to_string(C->getNomTotalKilled()) + " Killed in current time step: " + to_string(Ckilled), 150 / 24 + 2);
//
//	i = 0;
//	C->getTowerActiveSh().startLoop();
//	Enemy*pca = C->getTowerActiveSh().getref();
//	while (pca != nullptr) {
//
//		if (pca != nullptr) {
//			pGUI->PrintMessage("C", "Enemy(ACTIVE) # " + to_string(pca->Get_ID()) + "	Arrival time: " + to_string(pca->Get_Arrival_time()) + "	Health : " + to_string((int)pca->get_health()), 150 / 24 + i + 3, RED);
//		}
//		C->getTowerActiveSh().plus();
//		pca = C->getTowerActiveSh().getref();
//		i++;
//	}
//	C->getTowerActive().startLoop();
//	pca = C->getTowerActive().getref();
//	while (pca != nullptr) {
//
//		if (pca != nullptr) {
//			pGUI->PrintMessage("C", "Enemy(ACTIVE) # " + to_string(pca->Get_ID()) + "	Arrival time: " + to_string(pca->Get_Arrival_time()) + "	Health : " + to_string((int)pca->get_health()), 150 / 24 + i + 3, RED);
//		}
//		C->getTowerActive().plus();
//		pca = C->getTowerActive().getref();
//		i++;
//	}
//	C->getTowerKilled().startLoop();
//	Enemy*pck = C->getTowerKilled().getref();
//	if (pck != nullptr) {
//		for (int i = 0; i < Ckilled; i++)
//		{
//			if (pck != nullptr) {
//				pGUI->PrintMessage("C", "Enemy(KILLED) # " + to_string(pck->Get_ID()) + "	Arrival time: " + to_string(pck->Get_Arrival_time()) + "	Kill time: " + to_string(pck->Get_T_Killed()), 150 / 24 + 3 + i + Cactive, BLUE);
//			}
//			C->getTowerKilled().plus();
//			pck = C->getTowerKilled().getref();
//		}
//	}
//	pGUI->PrintMessage("D", "Region D:	Tower Health: " + to_string((int)D->GetHealth()) + "	Tower FirePower: " + to_string((int)D->Get_FirePower()), 150 / 24 + 1);
//	pGUI->PrintMessage("D", "Total # of Active in 'D': " + to_string(Dactive) + "	Total # of Killed in 'D': " + to_string(D->getNomTotalKilled()) + " Killed in current time step: " + to_string(Dkilled), 150 / 24 + 2);
//
//	i = 0;
//	D->getTowerActiveSh().startLoop();
//	Enemy*pda = D->getTowerActiveSh().getref();
//	while (pda != nullptr) {
//
//		if (pda != nullptr) {
//			pGUI->PrintMessage("D", "Enemy(ACTIVE) # " + to_string(pda->Get_ID()) + "	Arrival time: " + to_string(pda->Get_Arrival_time()) + "	Health : " + to_string((int)pda->get_health()), 150 / 24 + 3 + i, RED);
//		}
//		D->getTowerActiveSh().plus();
//		pda = D->getTowerActiveSh().getref();
//		i++;
//
//	}
//	D->getTowerActive().startLoop();
//	pda = D->getTowerActive().getref();
//	while (pda != nullptr) {
//
//		if (pda != nullptr) {
//			pGUI->PrintMessage("D", "Enemy(ACTIVE) # " + to_string(pda->Get_ID()) + "	Arrival time: " + to_string(pda->Get_Arrival_time()) + "	Health : " + to_string((int)pda->get_health()), 150 / 24 + 3 + i, RED);
//		}
//		D->getTowerActive().plus();
//		pda = D->getTowerActive().getref();
//		i++;
//
//	}
//	D->getTowerKilled().startLoop();
//	Enemy*pdk = D->getTowerKilled().getref();
//	if (pdk != nullptr) {
//		for (int i = 0; i < Dkilled; i++)
//		{
//			if (pdk != nullptr) {
//				pGUI->PrintMessage("D", "Enemy(KILLED) # " + to_string(pdk->Get_ID()) + "	Arrival time: " + to_string(pdk->Get_Arrival_time()) + "	Kill time: " + to_string(pdk->Get_T_Killed()), 150 / 24 + 3 + i + Dactive, BLUE);
//			}
//			D->getTowerKilled().plus();
//			pdk = D->getTowerKilled().getref();
//		}
//	}
//}

void Battle::Print(GUI* pGUI, int t)
{
	pGUI->ClearStatusBar();
	pGUI->PrintMessage("Time Step = " + to_string(t),10 , 455);
	BCastle.Print(pGUI);
}

void Battle::setEnemiesArr(int& size)
{
	size = 0;

	A->getTowerActiveSh().AddToArr(BEnemiesForDraw, size, MaxEnemyCount);
	B->getTowerActiveSh().AddToArr(BEnemiesForDraw, size, MaxEnemyCount);
	C->getTowerActiveSh().AddToArr(BEnemiesForDraw, size, MaxEnemyCount);
	D->getTowerActiveSh().AddToArr(BEnemiesForDraw, size, MaxEnemyCount);
	A->getTowerActive().AddToArr(BEnemiesForDraw, size, MaxEnemyCount);
	B->getTowerActive().AddToArr(BEnemiesForDraw, size, MaxEnemyCount);
	C->getTowerActive().AddToArr(BEnemiesForDraw, size, MaxEnemyCount);
	D->getTowerActive().AddToArr(BEnemiesForDraw, size, MaxEnemyCount);
}

void Battle::Excuete(Actiontype ACTY, GUI * pGUI)
{
	switch (ACTY) {

	case Read:
		ReadFile(pGUI);
		pGUI->PrintMessage("Load Success");
		break;
	case Step:
		pGUI->PrintMessage("Interactive Mode : Click to play");
		simBattle(pGUI, ACTY);
		break;
	case Silent:
		pGUI->PrintMessage("Silent Mode : Only generating output file");
		simBattle(pGUI, ACTY);
		break;
	case Continue:
		pGUI->PrintMessage("Step By Step Mode : No need to click on mouse");
		simBattle(pGUI, ACTY);
		break;
	case EMPTY:
		pGUI->PrintMessage("Empty Area");
		break;

	}
}


void Battle::Clear(GUI*pGUI)
{
	EnemyCount = 0;
	//Deleting active enemies
	for (int i = 0; i < EnemyCount; i++) {
		if (BEnemiesForDraw[i]) {
			delete BEnemiesForDraw[i];
			BEnemiesForDraw[i] = NULL;
		}
	}
	for (int i = EnemyCount; i < 300 - EnemyCount; i++) {
		BEnemiesForDraw[i] = NULL;
	}
	//if the game end with some enemies still inactive deleting enemies before deleting node
	EnemiesInactive.startLoop();
	Enemy* ptr = EnemiesInactive.getref();
	while (ptr) {
		delete ptr;
		EnemiesInactive.plus();
		ptr = EnemiesInactive.getref();
	}

	A->getTowerActive().clear();
	B->getTowerActive().clear();
	C->getTowerActive().clear();

	D->getTowerActive().clear();
	A->getTowerActiveSh().clear();
	B->getTowerActiveSh().clear();
	C->getTowerActiveSh().clear();
	D->getTowerActiveSh().clear();
	EnemiesInactive.clear();
	A->setTotalKilled(0);
	B->setTotalKilled(0);
	C->setTotalKilled(0);
	D->setTotalKilled(0);
	A->setUnPaved(30);
	B->setUnPaved(30);
	C->setUnPaved(30);
	D->setUnPaved(30);

}

void Battle::EnemyFight()
{
}

int Battle::endGame()
{
	if (EnemyCount == 0 && EnemiesInactive.isEmpty())
	{
		return 0;
	}
	if (A->GetHealth() == 0 && B->GetHealth() == 0 && C->GetHealth() == 0 && D->GetHealth() == 0)
	{
		return 1;
	}
	return 2;
}


//void Battle::moveEnemies()
//{
//	if (!A->GetHealth())
//	{
//		B->getTowerActive().addList(A->getTowerActive());
//		B->getTowerActiveSh().addList(A->getTowerActiveSh());
//		A->getTowerActiveSh().startLoop();
//		Enemy* E = A->getTowerActiveSh().getref();
//		while (E)
//		{
//			E->setTower(B);
//			E->setReg(B_REG);
//			if (E->GetDistance() < E->GetTower()->getUnPaved())
//				E->SetDistance(E->GetTower()->getUnPaved() + 1);
//			A->getTowerActiveSh().plus();
//			E = A->getTowerActiveSh().getref();
//		}
//		A->getTowerActive().startLoop();
//		E = A->getTowerActive().getref();
//		while (E)
//		{
//			E->setTower(B);
//			E->setReg(B_REG);
//			if (E->GetDistance() < E->GetTower()->getUnPaved())
//				E->SetDistance(E->GetTower()->getUnPaved() + 1);
//			A->getTowerActive().plus();
//			E = A->getTowerActive().getref();
//		}
//		A->getTowerActive().clear();
//		A->getTowerActiveSh().clear();
//	}
//	if (!B->GetHealth())
//	{
//		C->getTowerActive().addList(B->getTowerActive());
//		C->getTowerActiveSh().addList(B->getTowerActiveSh());
//		B->getTowerActiveSh().startLoop();
//		Enemy* E = B->getTowerActiveSh().getref();
//		while (E)
//		{
//			E->setTower(C);
//			E->setReg(C_REG);
//			if (E->GetDistance() < E->GetTower()->getUnPaved())
//				E->SetDistance(E->GetTower()->getUnPaved() + 1);
//			B->getTowerActiveSh().plus();
//			E = B->getTowerActiveSh().getref();
//		}
//		B->getTowerActive().startLoop();
//		E = B->getTowerActive().getref();
//		while (E)
//		{
//			E->setTower(C);
//			E->setReg(C_REG);
//			if (E->GetDistance() < E->GetTower()->getUnPaved())
//				E->SetDistance(E->GetTower()->getUnPaved() + 1);
//			B->getTowerActive().plus();
//			E = B->getTowerActive().getref();
//		}
//		B->getTowerActive().clear();
//		B->getTowerActiveSh().clear();
//	}
//	if (!C->GetHealth())
//	{
//
//		D->getTowerActive().addList(C->getTowerActive());
//		D->getTowerActiveSh().addList(C->getTowerActiveSh());
//		C->getTowerActiveSh().startLoop();
//		Enemy* E = C->getTowerActiveSh().getref();
//		while (E)
//		{
//			E->setTower(D);
//			E->setReg(D_REG);
//			if (E->GetDistance() < E->GetTower()->getUnPaved())
//				E->SetDistance(E->GetTower()->getUnPaved() + 1);
//			C->getTowerActiveSh().plus();
//			E = C->getTowerActiveSh().getref();
//		}
//		C->getTowerActive().startLoop();
//		E = C->getTowerActive().getref();
//		while (E)
//		{
//			E->setTower(D);
//			E->setReg(D_REG);
//			if (E->GetDistance() < E->GetTower()->getUnPaved())
//				E->SetDistance(E->GetTower()->getUnPaved() + 1);
//			C->getTowerActive().plus();
//			E = C->getTowerActive().getref();
//		}
//		C->getTowerActive().clear();
//		C->getTowerActiveSh().clear();
//	}
//	if (!D->GetHealth())
//	{
//		if (A->GetHealth())
//		{
//			A->getTowerActive().addList(D->getTowerActive());
//			A->getTowerActiveSh().addList(D->getTowerActiveSh());
//			D->getTowerActiveSh().startLoop();
//			Enemy* E = D->getTowerActiveSh().getref();
//			while (E)
//			{
//
//				E->setTower(A);
//				E->setReg(A_REG);
//				if (E->GetDistance() < E->GetTower()->getUnPaved())
//					E->SetDistance(E->GetTower()->getUnPaved() + 1);
//				D->getTowerActiveSh().plus();
//				E = D->getTowerActiveSh().getref();
//			}
//			D->getTowerActive().startLoop();
//			E = D->getTowerActive().getref();
//			while (E)
//			{
//				E->setTower(A);
//				E->setReg(A_REG);
//				if (E->GetDistance() < E->GetTower()->getUnPaved())
//					E->SetDistance(E->GetTower()->getUnPaved() + 1);
//				D->getTowerActive().plus();
//				E = D->getTowerActive().getref();
//			}
//			D->getTowerActive().clear();
//			D->getTowerActiveSh().clear();
//		}
//	}
//}
