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
// переменные... глобальные
//------------------------------------------------------------------------------------

eFont *Font2;
// командный буфер
int ComBuffer = 0;
// тукущее состояние для прорисовки и обхода
status GameStatus = MAIN_MENU;
eFont *GameFont;

// делаем, чтобы было 30 кадров в секунду
Uint32 TimeDelay;






//------------------------------------------------------------------------------------
// зацикленная процедура работы программы...
//------------------------------------------------------------------------------------
void Loop_Proc()
{


	// делаем задержку
	if (TimeDelay + 25 <= SDL_GetTicks())
	{
		TimeDelay = SDL_GetTicks();


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// инициализация курсора
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		GameCursor.Current = 0;

		// начало прорисовки...
		vw_BeginRendering();

		// для перехода в 2Д режим (нужно для 3Д рендереров)
		vw_Start2DMode(-1,1);

		switch(GameStatus)
		{
			case MAIN_MENU:
				MainMenu();
				break;
			case CREDITS:
				Credits();
				break;
			case TOP_SCORES:
				TopScores();
				break;
			case SETUP:
				SetupProc();
				break;
			case GAME_START:
				GameStartDraw();
				break;
			case GAME:
				Game();
				break;
			case OPTIONS:
				Options();
				break;
		}

		// вывод всех диалогов...
		DrawDialogBox();


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// рисуем курсор...
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		RECT SrcRest, DstRest;
		int mX,mY;
		vw_GetMousePos(&mX,&mY);
		SetRect(&SrcRest,0,0,40,40 );
		SetRect(&DstRest,mX-5,mY-3,mX+40-5,mY+40-3 );

		if (GameCursor.Current==0)
			vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA\\cur.tga"), true, 0.99f);//1.0f
		if (GameCursor.Current==1)
		{
			SetRect(&SrcRest,0+GameCursor.Frame*40,0,40+GameCursor.Frame*40,40 );
			vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA\\cur1.tga"), true, 0.99f);//1.0f
			if (GameCursor.Delay > 1)
			{
				GameCursor.Delay = 0;
				GameCursor.Frame++;
				if (GameCursor.Frame>7) GameCursor.Frame=0;
			}
			else GameCursor.Delay+=1.0f;//8.0f/vw_GetFPS(false);
		}
		if (GameCursor.Current==2)
		{
			SetRect(&SrcRest,0+GameCursor.Frame*40,0,40+GameCursor.Frame*40,40 );
			vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA\\cur2.tga"), true, 0.99f);//1.0f
			if (GameCursor.Delay > 1)
			{
				GameCursor.Delay = 0;
				GameCursor.Frame++;
				if (GameCursor.Frame>7) GameCursor.Frame=0;
			}
			else GameCursor.Delay+=1.0f;//8.0f/vw_GetFPS(false);
		}
		if (GameCursor.Current==3)
		{
			// рисуем то,что тянем...
			RECT SrcRest2, DstRest2;
			SetRect(&SrcRest2,0,0,64,64 );
			SetRect(&DstRest2,mX-32,mY-32,mX+32,mY+32 );
			//vw_DrawTransparent(&DstRest2, &SrcRest2, vw_FindTextureByNum(GameCursor.text), false, 1.0f);
			vw_Draw(mX-32,mY-32,&SrcRest2, vw_FindTextureByNum(GameCursor.text), false);
			//vw_DrawTransparent(&DstRest2, &SrcRest2, vw_FindTextureByName("DATA\\drop.bmp"), true, 1.0f);
			SetRect(&SrcRest2,0,0,68,68 );
			vw_Draw(mX-32-2,mY-32-2,&SrcRest2, vw_FindTextureByName("DATA\\drop.bmp"), true);
			SetRect(&SrcRest,0,0,40,40 );
			vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA\\cur3.tga"), true, 0.99f);//1.0f
		}



		vw_End2DMode();
		vw_EndRendering();


	}
	else SDL_Delay(10);




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// основной цикл проигрывания звука
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Audio_LoopProc();




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// выполняем то, что есть в буфере команд, если там что-то есть
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (ComBuffer != 0)
	{
		switch(ComBuffer)
		{
			case MAIN_MENU:
				SetMenu(MAIN_MENU);
				break;
			case CREDITS:
				SetMenu(CREDITS);
				break;
			case TOP_SCORES:
				SetMenu(TOP_SCORES);
				break;
			case SETUP:
				SetMenu(SETUP);
				break;
			case GAME_START:
				GameStart();
				break;
			case GAME:
				GameStatus = GAME;
				break;
			case OPTIONS:
				SetMenu(OPTIONS);
				break;



			case 201:
				LoadMosaicPreset();
				break;
			case 202:
				LoadBuilderPreset();
				break;
			case 203:
				LoadThePairPreset();
				break;
			case 204:
				LoadJigSawPreset();
				break;


			case 912:
				CanQuit = false;
				Quit = true;
				break;

		}

		ComBuffer = 0;
	}




}
