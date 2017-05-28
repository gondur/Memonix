/*

Memonix ver 1.6
Copyright (c) 2003-2006 Michael Kurinnoy, Viewizard Games
All Rights Reserved.

Memonix game source codes available under "dual licensing" model.
The licensing options available are:

* Commercial Licensing. This is the appropriate option if you are creating proprietary
applications and you are not prepared to distribute and share the source code of your application.
Contact us for pricing at viewizard@viewizard.com

* Open Source Licensing. This is the appropriate option if you want to share the source code of
your application with everyone you distribute it to, and you also want to give them the right to share who uses it.
You should have received a copy of the GNU General Public License version 3 with this source codes. If not, see <http://www.gnu.org/licenses/>.

*/


#include "memonix_var.h"




//------------------------------------------------------------------------------------
// переменные... локальные
//------------------------------------------------------------------------------------

bool DialogBoxDrag = false;
int DialogBoxDragX = 0;
int DialogBoxDragY = 0;

// начальные положения диалогов
int DialogBoxXY[5][2] =
{{200,200},
{200,200},
{200,200},
{200,200},
{200,200}};

// текущий приросовываемый диалог
int CurrentDialogBox = -1;
int CurrentDialogBoxH;
int CurrentDialogBoxW;








//------------------------------------------------------------------------------------
// прорисовка DialogBox
//------------------------------------------------------------------------------------
void SetCurrentDialogBox(int DialogBox)
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// если что-то рисуем - продолжаем рисовать...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (CurrentDialogBox != -1) return;

	DialogBoxDrag = false;
	CurrentDialogBox = DialogBox;

	CurrentDialogBoxH = 200;
	CurrentDialogBoxW = 400;
}





//------------------------------------------------------------------------------------
// запрос, прорисовываем что-то?
//------------------------------------------------------------------------------------
bool isDialogBoxDrawing()
{
	if (CurrentDialogBox == -1) return false;
	else return true;
}





//------------------------------------------------------------------------------------
// рисуем DrawDialogBox, если он установлен
//------------------------------------------------------------------------------------
void DrawDialogBox()
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// если что-то есть - рисуем
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (CurrentDialogBox == -1) return;

	RECT MDetect;
	RECT DrawOFF;
	RECT DrawON;



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// получаем координаты прорисовки диалога
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	int X = DialogBoxXY[CurrentDialogBox-1][0];
	int Y = DialogBoxXY[CurrentDialogBox-1][1];


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// рисуем диалоги 400 на 200
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (CurrentDialogBoxH == 200)
	{ // 400x200
		vw_DrawRect(X,Y,0,0,CurrentDialogBoxW,CurrentDialogBoxH,"DATA\\box.jpg");


		// надпись на диалоге
		switch(CurrentDialogBox)
		{
			case QUIT_GAME:
				vw_Print(Font2, X*1.0f,Y+55.0f, 400, 0, 0, RI_UL_CORNER, 1.0f, "  Are you sure you  ");
				vw_Print(Font2, X*1.0f,Y+95.0f, 400, 0, 0, RI_UL_CORNER, 1.0f, "  want to quit?  ");
				break;
			case YOU_WINNER:
				vw_Print(Font2, X*1.0f,Y+40.0f, 400, 0, 0, RI_UL_CORNER, 1.0f, "  Congratulations!  ");
				vw_Print(Font2, X*1.0f,Y+75.0f, 400, 0, 0, RI_UL_CORNER, 1.0f, "  You are our  ");
				vw_Print(Font2, X*1.0f,Y+110.0f, 400, 0, 0, RI_UL_CORNER, 1.0f, "  Winner!  ");
				break;
		}


		// 1-я кнопка
		SetRect(&MDetect, X+57, Y+155, X+173, Y+185);
		SetRect(&DrawOFF, 0, 0, 0, 0);
		SetRect(&DrawON, 41, 204, 165, 242);
		if (vw_OnRect(&MDetect)) GameCursor.Current=1;
		if (vw_Button2D(X+53,Y+151, &MDetect, &DrawON, &DrawOFF, "DATA\\box.jpg"))
		{
			// действия для 1-й кнопки
			switch(CurrentDialogBox)
			{
				case QUIT_GAME:
					CurrentDialogBox = -1;
					CanQuit = true;
					Quit = true;
					break;
				case YOU_WINNER:
					if (Setup.SoundSw) Audio_PlaySound(1);
					CurrentDialogBox = -1;
					GameStart();
					break;

			}

		}
		// надпись на 1-й кнопке
		switch(CurrentDialogBox)
		{
			case QUIT_GAME:
				DrawManualText(X+57, Y+155+3, " YES ", 173-57, 0);
				break;
			case YOU_WINNER:
				DrawManualText(X+57, Y+155+3, " New ", 173-57, 0);
				break;
		}




		// 2-я кнопка
		SetRect(&MDetect, X+226, Y+155, X+342, Y+185);
		SetRect(&DrawOFF, 0, 0, 0, 0);
		SetRect(&DrawON, 41, 204, 165, 242);
		if (vw_OnRect(&MDetect)) GameCursor.Current=1;
		if (vw_Button2D(X+222,Y+151, &MDetect, &DrawON, &DrawOFF, "DATA\\box.jpg"))
		{
			// действия для 2-й кнопки
			switch(CurrentDialogBox)
			{
				case QUIT_GAME:
					if (Setup.SoundSw) Audio_PlaySound(1);
					CurrentDialogBox = -1;
					break;
				case YOU_WINNER:
					if (Setup.SoundSw) Audio_PlaySound(1);
					ComBuffer = MAIN_MENU;
					CurrentDialogBox = -1;
					break;
			}
		}
		// надпись на 2-й кнопке
		switch(CurrentDialogBox)
		{
			case QUIT_GAME:
				DrawManualText(X+226, Y+155+3, " NO ", 342-226, 0);
				break;
			case YOU_WINNER:
				DrawManualText(X+226, Y+155+3, " Menu ", 342-226, 0);
				break;
		}



		// кнопка X
		SetRect(&MDetect, X+373, Y+6, X+390, Y+22);
		SetRect(&DrawOFF, 0, 0, 0, 0);
		SetRect(&DrawON, 4, 204, 30, 228);
		if (vw_OnRect(&MDetect)) GameCursor.Current=1;
		if (vw_Button2D(X+369,Y+2, &MDetect, &DrawON, &DrawOFF, "DATA\\box.jpg"))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			CurrentDialogBox = -1;
		}
	}
}
