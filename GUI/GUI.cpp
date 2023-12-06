#include "GUI.h"

//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
	pWind = new window(WindWidth + 15, WindHeight, 0, 0);
	pWind->ChangeTitle("The Castle Game");

	DrawMenu();

	ClearStatusBar();
	ClearBattleArea();
	DrawCastle(30, 30, 30, 30);

}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ====================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::GetPointClicked(Point &P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////
string GUI::GetString() const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;

		PrintMessage(Label);
	}
}

Actiontype GUI::GetAction()
{
	int x, y;
	pWind->WaitMouseClick(x, y);
	if (y >= 0 && y < MenuBarHeight)
	{
		int ClickedItemOrder = (x / MenuItemWidth);
		switch (ClickedItemOrder)
		{
		case MENU_LOAD:		return Read;
		case MENU_CLICK:	return Step;
		case MENU_STOP:		return Silent;
		case MENU_CONTINUE: return Continue;
		case MENU_EXIT:		return Exit;
		default: return EMPTY;	//A click on empty place in desgin toolbar
		}
	}
	return EMPTY;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(REGION Kind, string msg, int x, color c) const	//Prints a message on status bar
{
	//no clear to status bar
	//kind for printing on different places on status bar w.r.t. region

	int start, end;
	if (Kind == A_REG)
	{
		start = 10;
		end = (WindHeight - (int)(StatusBarHeight)) + 13 * x;
	}
	else if (Kind == B_REG)
	{
		start = WindWidth / 2 + 10;
		end = (WindHeight - (int)(StatusBarHeight)) + 13 * x;
	}
	else if (Kind == C_REG)
	{
		start = WindWidth / 2 + 10;
		end = (WindHeight - (int)(StatusBarHeight)) + 13 * x ;
	}
	else if (Kind == D_REG)
	{
		start = 10;
		end = (WindHeight - (int)(StatusBarHeight)) + 13 * x ;
	}

	pWind->SetPen(c);
	pWind->SetFont(16, BOLD, BY_NAME, "Arial");
	pWind->DrawString(start, end, msg);
	// line to split status bar
	pWind->SetPen(BLACK, 1);
	pWind->DrawLine(0, WindHeight - StatusBarHeight / 2 - 15 + 13, WindWidth - 200, WindHeight - StatusBarHeight / 2 - 15 + 13);

}

void GUI::PrintMessage(string msg, int x, int y) const
{
	if (y == WindHeight - (int)(StatusBarHeight / 1.5)) {
		ClearStatusBar();	//First clear the status bar
	}

	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD, BY_NAME, "Arial");
	pWind->DrawString(x, y, msg);
	image sword = "images\\MenuItems\\sword3.jpg";
	pWind->DrawImage(sword, WindWidth - 200, WindHeight - StatusBarHeight + 5, 200, 200);

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD, BY_NAME, "Arial");
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawMenu() const
{
	//You can draw the menu icons any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in enum MenuItem
	string MenuItemImages[MENU_ITM_COUNT];
	MenuItemImages[MENU_LOAD] = "images\\MenuItems\\uploadnew.jpg";
	MenuItemImages[MENU_CLICK] = "images\\MenuItems\\clicknew.jpg";
	MenuItemImages[MENU_STOP] = "images\\MenuItems\\stopnew.jpg";
	MenuItemImages[MENU_EXIT] = "images\\MenuItems\\exitnew.jpg";
	MenuItemImages[MENU_CONTINUE] = "images\\MenuItems\\play.jpg";



	//Draw menu item one image at a time
	for (int i = 0; i<MENU_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);

	//Draw a line under the menu bar
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, MenuBarHeight, WindWidth, MenuBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	pWind->SetPen(WHITE, 3);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight, WindWidth, WindHeight - StatusBarHeight);


}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearBattleArea() const
{
	// Clearing the battle area
	pWind->SetPen(KHAKI, 3);
	pWind->SetBrush(KHAKI);
	pWind->DrawRectangle(10, MenuBarHeight, WindWidth - 10, WindHeight - StatusBarHeight);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawCastle(int disA, int disB, int disC, int disD) const
{

	int L = CastleWidth / 2;

	// 1- Drawing the BLACK square of the castle
	pWind->SetPen(BLACK);
	pWind->SetBrush(BLACK);
	//pWind->DrawRectangle(CastleStartX, CastleStartY, CastleEndX, CastleEndY);
	pWind->SetPen(GOLDENROD);
	pWind->SetBrush(GOLDENROD);
	pWind->DrawRectangle(CastleStartX - (7 * disA), 50, CastleStartX, YHalfBattleArea);
	pWind->DrawRectangle(CastleEndX, 50, (CastleEndX + (7 * disB)), YHalfBattleArea);
	pWind->DrawRectangle(CastleEndX, YHalfBattleArea, (CastleEndX + (7 * disC)), WindHeight - StatusBarHeight);
	pWind->DrawRectangle(CastleStartX - (7 * disD), YHalfBattleArea, CastleStartX, WindHeight - StatusBarHeight);
	// 2- Drawing the 2 BLACK crossed lines (for making 4 regions)
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, YHalfBattleArea, WindWidth, YHalfBattleArea);
	pWind->DrawLine(WindWidth / 2, MenuBarHeight, WindWidth / 2, WindHeight - StatusBarHeight);


	pWind->SetPen(BLACK);
	pWind->DrawLine(CastleStartX - MaxDistance * EnemyWidth - MaxDistance - 1, MenuBarHeight,
		CastleStartX - MaxDistance * EnemyWidth - MaxDistance - 1, WindHeight - StatusBarHeight);
	pWind->DrawLine(CastleEndX + MaxDistance * EnemyWidth + MaxDistance + 1, MenuBarHeight,
		CastleEndX + MaxDistance * EnemyWidth + MaxDistance + 1, WindHeight - StatusBarHeight);
	image cas = "images\\MenuItems\\castlenew.jpg";
	pWind->DrawImage(cas, CastleStartX, CastleStartY, 216, 216);
	image sword = "images\\MenuItems\\sword3.jpg";
	pWind->DrawImage(sword, WindWidth - 200, WindHeight - StatusBarHeight + 5, 200, 200);
	// 5- Writing the letter of each region (A, B, C, D)
	pWind->SetPen(BLACK);
	pWind->SetFont(25, BOLD, BY_NAME, "Arial");
	pWind->DrawString(CastleStartX + 15, CastleStartY + 15, "A");
	pWind->DrawString(CastleStartX + 15, CastleEndY - 35, "D");
	pWind->DrawString(CastleStartX + 180, CastleStartY + 15, "B");
	pWind->DrawString(CastleStartX + 180, CastleEndY - 35, "C");

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawEnemy(const Enemy & E, int YPos) const       // It's a private function
{
	color clr = E.GetColor();
	REGION Region = E.GetRegion();
	int Distance = E.GetDistance();

	int x, y, refX, refY;
	//First calculate x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	switch (Region)
	{
	case A_REG:
		refX = (WindWidth / 2 - CastleWidth / 2);
		refY = YHalfBattleArea - 1 - EnemyWidth; //
		x = refX - Distance * EnemyWidth - Distance; //(Distance)
		y = refY - YPos * EnemyHeight - YPos; // YPos
		break;
	case B_REG:
		refX = (WindWidth / 2 + CastleWidth / 2);
		refY = YHalfBattleArea - 1 - EnemyWidth; //
		x = refX + (Distance - 1)*EnemyWidth + Distance; //(Distance)
		y = refY - YPos * EnemyHeight - YPos; // YPos
		break;
	case C_REG:
		refX = (WindWidth / 2 + CastleWidth / 2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX + (Distance - 1)*EnemyWidth + Distance; //(Distance)
		y = refY + (YPos - 1)*EnemyHeight + YPos; // YPos
		break;
	case D_REG:
		refX = (WindWidth / 2 - CastleWidth / 2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX - Distance * EnemyWidth - Distance; //(Distance)
		y = refY + (YPos - 1)*EnemyHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the enemy
	pWind->SetPen(clr);
	pWind->SetBrush(clr);
	pWind->DrawRectangle(x, y, x + EnemyWidth, y + EnemyHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
/* A function to draw a list of enemies and ensure there is no overflow in the drawing*/
// To use this function, you must prepare its input parameters as specified
// [Input Parameters]:
//    enemies [ ] : array of enemy pointers (ALL enemies from all regions in one array)
//    size : the size of the array (total no. of enemies)
void GUI::DrawEnemies(Enemy* enemies[], int size) const
{
	//draw enemies at each region 
	for (int region = A_REG; region <= D_REG; region++)
	{
		int CountEnemies = 0;	// count Enemies at the same distance to draw them vertically if they are <= 15 enemy 
								// else print number of enemy in the region
		bool draw = true;
		for (int distance = MaxDistance; distance >= MinDistance; distance--)
		{
			CountEnemies = 0;

			for (int i = 0; i < size; i++)
			{
				if (enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region)
				{
					CountEnemies++;
				}
			}
			if (CountEnemies > 15)
			{
				draw = false;
				break;
			}
		}
		if (draw)
		{
			for (int distance = MaxDistance; distance > 1; distance--)
			{
				CountEnemies = 0;

				for (int i = 0; i < size; i++)
				{
					if (enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region)
					{
						DrawEnemy(*(enemies[i]), CountEnemies + 1);
						CountEnemies++;
					}
				}
			}
		}
		else // print message maximum reached in this region
		{
			PrintMessage("Cannot Draw Enemies of region " + to_string(region + 1) +
				"! More than" + to_string(MaxVerticaEnemies) + " enemies are in the same region and distance..");
			Sleep(1000); // because may be more than one region has drawing overflow
		}
	}
}
