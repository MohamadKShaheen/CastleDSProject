#include "Battle.h"
#include "GUI\GUI.h"
//#include "DS\List.h"

int main()
{
	Battle* pGameBattle = new Battle;
	GUI * pGUI = new GUI;

	Actiontype ACTY;
	
	do {
		ACTY = pGUI->GetAction();
		pGameBattle->Excuete(ACTY,pGUI);
	} while (ACTY != Exit);
	
	/*pGameBattle->ReadFile(pGUI);
	pGameBattle->simBattle(pGUI);*/
	delete pGUI;
	delete pGameBattle;
	return 0;
}
