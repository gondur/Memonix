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


// временные переменные, для проверки были ли изменения и нужна ли перегрузка рендерера
bool	nFullscrSw;
int		nWindowsBPP;
int		nDifficult;
bool	nMusicSw;
bool	nMusicSw_Game;
bool	nSoundSw;


// переменные для кнопок
RECT MDetect;
RECT DrawON;
RECT DrawOFF;
//защелки...для авто + или - Countdown
bool plus1 = false;
bool minus1 = false;

// мерцания
int CountFlash = 0;
bool CountFlashW = true;


// topscores
int TopScoresCurrent = 0;












//------------------------------------------------------------------------------------
// инициализация нужного подменю
//------------------------------------------------------------------------------------
void SetMenu(int GameMenuStatus)
{
	switch(GameMenuStatus)
	{
		case REGISTRATION:
			GameStatus = REGISTRATION;
			break;
		case MAIN_MENU:
			GameStatus = MAIN_MENU;
			break;
		case CREDITS:
			GameStatus = CREDITS;
			break;
		case TOP_SCORES:
			GameStatus = TOP_SCORES;
			break;
		case SETUP:
			nFullscrSw = Setup.FullscrSw;
			nWindowsBPP = Setup.WindowsBPP;
			nMusicSw = Setup.MusicSw;
			nMusicSw_Game = Setup.MusicSw_Game;
			nSoundSw = Setup.SoundSw;
			GameStatus = SETUP;
			break;
		case OPTIONS:
			SeekAddons();
			GameStatus = OPTIONS;
			break;
	}

}











//------------------------------------------------------------------------------------
// прорисовка текста
//------------------------------------------------------------------------------------
void DrawManualText(int X , int Y, const char * Text, int W, int Limit)
{
// W - какую ширину хотим...

	RECT DstRest, SrcRest;
	int Xpos = 0;
	float Xposf = 0;
	int XsmDop = 0;
	int XsmDopCount = 1;
	unsigned int i;

	if (W !=0)
	{
		XsmDopCount = 0;
		for (i=0; i<strlen(Text); i++)
		{
			switch (Text[i])
			{
				case 'A':SetRect(&SrcRest,2,3,24,26);break;
				case 'B':SetRect(&SrcRest,26,3,45,26 );break;
				case 'C':SetRect(&SrcRest,47,3,68,26 );break;
				case 'D':SetRect(&SrcRest,71,3,91,26 );break;
				case 'E':SetRect(&SrcRest,94,3,113,26 );break;
				case 'F':SetRect(&SrcRest,116,3,134,26 );break;
				case 'G':SetRect(&SrcRest,136,3,157,26 );break;
				case 'H':SetRect(&SrcRest,161,3,180,26 );break;
				case 'I':SetRect(&SrcRest,184,3,194,26 );break;
				case 'J':SetRect(&SrcRest,197,3,213,26 );break;
				case 'K':SetRect(&SrcRest,216,3,236,26 );break;
				case 'L':SetRect(&SrcRest,238,3,255,26 );break;
				case 'M':SetRect(&SrcRest,258,3,280,26 );break;

				case 'N':SetRect(&SrcRest,4,33,24,56 );break;
				case 'O':SetRect(&SrcRest,27,33,48,56 );break;
				case 'P':SetRect(&SrcRest,51,33,70,56 );break;
				case 'Q':SetRect(&SrcRest,73,33,94,56 );break;
				case 'R':SetRect(&SrcRest,97,33,118,56 );break;
				case 'S':SetRect(&SrcRest,120,33,139,56 );break;
				case 'T':SetRect(&SrcRest,141,33,161,56 );break;
				case 'U':SetRect(&SrcRest,163,33,183,56 );break;
				case 'V':SetRect(&SrcRest,184,33,206,56 );break;
				case 'W':SetRect(&SrcRest,206,33,234,56 );break;
				case 'X':SetRect(&SrcRest,234,33,255,56 );break;
				case 'Y':SetRect(&SrcRest,255,33,277,56 );break;
				case 'Z':SetRect(&SrcRest,278,33,297,56 );break;


				case 'a':SetRect(&SrcRest,3,63,21,86);break;
				case 'b':SetRect(&SrcRest,24,63,41,86 );break;
				case 'c':SetRect(&SrcRest,43,63,60,86 );break;
				case 'd':SetRect(&SrcRest,61,63,78,86 );break;
				case 'e':SetRect(&SrcRest,81,63,99,86 );break;
				case 'f':SetRect(&SrcRest,100,63,114,86 );break;
				case 'g':SetRect(&SrcRest,115,63,132,90 );break;
				case 'h':SetRect(&SrcRest,135,63,152,86 );break;
				case 'i':SetRect(&SrcRest,155,63,165,86 );break;
				case 'j':SetRect(&SrcRest,165,63,177,90 );break;
				case 'k':SetRect(&SrcRest,180,63,197,86 );break;
				case 'l':SetRect(&SrcRest,199,63,209,86 );break;
				case 'm':SetRect(&SrcRest,212,63,234,86 );break;

				case '0':SetRect(&SrcRest,251,63,269,86 );break;
				case '1':SetRect(&SrcRest,271,63,285,86 );break;
				case '2':SetRect(&SrcRest,290,63,308,86 );break;
				case '3':SetRect(&SrcRest,310,63,328,86 );break;
				case '4':SetRect(&SrcRest,329,63,347,86 );break;
				case '5':SetRect(&SrcRest,349,63,367,86 );break;
				case '6':SetRect(&SrcRest,369,63,387,86 );break;
				case '7':SetRect(&SrcRest,388,63,406,86 );break;
				case '8':SetRect(&SrcRest,408,63,426,86 );break;
				case '9':SetRect(&SrcRest,428,63,445,86 );break;


				case 'n':SetRect(&SrcRest,4,93,21,116 );break;
				case 'o':SetRect(&SrcRest,23,93,41,116 );break;
				case 'p':SetRect(&SrcRest,43,93,60,120 );break;
				case 'q':SetRect(&SrcRest,62,93,80,120 );break;
				case 'r':SetRect(&SrcRest,83,93,97,116 );break;
				case 's':SetRect(&SrcRest,97,93,114,116 );break;
				case 't':SetRect(&SrcRest,115,93,129,116 );break;
				case 'u':SetRect(&SrcRest,131,93,147,116 );break;
				case 'v':SetRect(&SrcRest,149,93,167,116 );break;
				case 'w':SetRect(&SrcRest,167,93,190,116 );break;
				case 'x':SetRect(&SrcRest,191,93,209,116 );break;
				case 'y':SetRect(&SrcRest,209,93,227,120 );break;
				case 'z':SetRect(&SrcRest,228,93,245,116 );break;

				case '-':SetRect(&SrcRest,261,93,275,116 );break;
				case '@':SetRect(&SrcRest,276,93,303,116 );break;
				case '$':SetRect(&SrcRest,305,93,323,116 );break;
				case ',':SetRect(&SrcRest,325,93,335,116 );break;
				case '.':SetRect(&SrcRest,340,93,350,116 );break;
				case ':':SetRect(&SrcRest,354,94,364,116 );break;
				case ';':SetRect(&SrcRest,368,94,378,116 );break;
				case '\'':SetRect(&SrcRest,382,94,390,106 );break;
				case '/':SetRect(&SrcRest,383+11,93,394+13,118 );break;
				case '\\':SetRect(&SrcRest,408,93,408+13,118 );break;

				default:
						SetRect(&SrcRest,0,0,0,0 );XsmDop+=15;
						XsmDopCount++;
						break;
			}

			XsmDop+=SrcRest.right - SrcRest.left - 4;
		}
	}

	// второй проход - рисуем...
	for (i=0; i<strlen(Text); i++)
	{
		switch (Text[i])
		{
			case 'A':SetRect(&SrcRest,2,3,24,26);break;
			case 'B':SetRect(&SrcRest,26,3,45,26 );break;
			case 'C':SetRect(&SrcRest,47,3,68,26 );break;
			case 'D':SetRect(&SrcRest,71,3,91,26 );break;
			case 'E':SetRect(&SrcRest,94,3,113,26 );break;
			case 'F':SetRect(&SrcRest,116,3,134,26 );break;
			case 'G':SetRect(&SrcRest,136,3,157,26 );break;
			case 'H':SetRect(&SrcRest,161,3,180,26 );break;
			case 'I':SetRect(&SrcRest,184,3,194,26 );break;
			case 'J':SetRect(&SrcRest,197,3,213,26 );break;
			case 'K':SetRect(&SrcRest,216,3,236,26 );break;
			case 'L':SetRect(&SrcRest,238,3,255,26 );break;
			case 'M':SetRect(&SrcRest,258,3,280,26 );break;

			case 'N':SetRect(&SrcRest,4,33,24,56 );break;
			case 'O':SetRect(&SrcRest,27,33,48,56 );break;
			case 'P':SetRect(&SrcRest,51,33,70,56 );break;
			case 'Q':SetRect(&SrcRest,73,33,94,56 );break;
			case 'R':SetRect(&SrcRest,97,33,118,56 );break;
			case 'S':SetRect(&SrcRest,120,33,139,56 );break;
			case 'T':SetRect(&SrcRest,141,33,161,56 );break;
			case 'U':SetRect(&SrcRest,163,33,183,56 );break;
			case 'V':SetRect(&SrcRest,184,33,206,56 );break;
			case 'W':SetRect(&SrcRest,206,33,234,56 );break;
			case 'X':SetRect(&SrcRest,234,33,255,56 );break;
			case 'Y':SetRect(&SrcRest,255,33,277,56 );break;
			case 'Z':SetRect(&SrcRest,278,33,297,56 );break;


			case 'a':SetRect(&SrcRest,3,63,21,86);break;
			case 'b':SetRect(&SrcRest,24,63,41,86 );break;
			case 'c':SetRect(&SrcRest,43,63,60,86 );break;
			case 'd':SetRect(&SrcRest,61,63,78,86 );break;
			case 'e':SetRect(&SrcRest,81,63,99,86 );break;
			case 'f':SetRect(&SrcRest,100,63,114,86 );break;
			case 'g':SetRect(&SrcRest,115,63,132,90 );break;
			case 'h':SetRect(&SrcRest,135,63,152,86 );break;
			case 'i':SetRect(&SrcRest,155,63,165,86 );break;
			case 'j':SetRect(&SrcRest,165,63,177,90 );break;
			case 'k':SetRect(&SrcRest,180,63,197,86 );break;
			case 'l':SetRect(&SrcRest,199,63,209,86 );break;
			case 'm':SetRect(&SrcRest,212,63,234,86 );break;

			case '0':SetRect(&SrcRest,251,63,269,86 );break;
			case '1':SetRect(&SrcRest,271,63,285,86 );break;
			case '2':SetRect(&SrcRest,290,63,308,86 );break;
			case '3':SetRect(&SrcRest,310,63,328,86 );break;
			case '4':SetRect(&SrcRest,329,63,347,86 );break;
			case '5':SetRect(&SrcRest,349,63,367,86 );break;
			case '6':SetRect(&SrcRest,369,63,387,86 );break;
			case '7':SetRect(&SrcRest,388,63,406,86 );break;
			case '8':SetRect(&SrcRest,408,63,426,86 );break;
			case '9':SetRect(&SrcRest,428,63,445,86 );break;


			case 'n':SetRect(&SrcRest,4,93,21,116 );break;
			case 'o':SetRect(&SrcRest,23,93,41,116 );break;
			case 'p':SetRect(&SrcRest,43,93,60,120 );break;
			case 'q':SetRect(&SrcRest,62,93,80,120 );break;
			case 'r':SetRect(&SrcRest,83,93,97,116 );break;
			case 's':SetRect(&SrcRest,97,93,114,116 );break;
			case 't':SetRect(&SrcRest,115,93,129,116 );break;
			case 'u':SetRect(&SrcRest,131,93,147,116 );break;
			case 'v':SetRect(&SrcRest,149,93,167,116 );break;
			case 'w':SetRect(&SrcRest,167,93,190,116 );break;
			case 'x':SetRect(&SrcRest,191,93,209,116 );break;
			case 'y':SetRect(&SrcRest,209,93,227,120 );break;
			case 'z':SetRect(&SrcRest,228,93,245,116 );break;

			case '-':SetRect(&SrcRest,261,93,275,116 );break;
			case '@':SetRect(&SrcRest,276,93,303,116 );break;
			case '$':SetRect(&SrcRest,305,93,323,116 );break;
			case ',':SetRect(&SrcRest,325,93,335,116 );break;
			case '.':SetRect(&SrcRest,340,93,350,116 );break;
			case ':':SetRect(&SrcRest,354,94,364,116 );break;
			case ';':SetRect(&SrcRest,368,94,378,116 );break;
			case '\'':SetRect(&SrcRest,382,94,390,106 );break;
			case '/':SetRect(&SrcRest,383+11,93,394+13,118 );break;
			case '\\':SetRect(&SrcRest,408,93,408+13,118 );break;

			default: SetRect(&SrcRest,0,0,0,0 );
					if (W !=0)
					{
						if (XsmDop<W) Xposf+=15 + (W-XsmDop)/(XsmDopCount*1.0f);
							else Xposf+=15;
					}
						else Xposf+=15;
					break;

		}


		Xpos = (int)Xposf;
		SetRect(&DstRest,X+Xpos, Y, X+Xpos+(SrcRest.right - SrcRest.left), Y + (SrcRest.bottom - SrcRest.top) );

		if (Limit !=0)
		{
			if (Limit >= Xpos)
				vw_Draw(DstRest.left,DstRest.top,&SrcRest, vw_FindTextureByName("DATA\\FONT\\text.tga"), true);
		}
		else
			vw_Draw(DstRest.left,DstRest.top,&SrcRest, vw_FindTextureByName("DATA\\FONT\\text.tga"), true);

		Xposf+=SrcRest.right - SrcRest.left - 4;
	}



}









//------------------------------------------------------------------------------------
// MainMenu
//------------------------------------------------------------------------------------
void MainMenu()
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// прорисовка подложки главного меню
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	vw_DrawRect(0,0,0,0,800,600,"DATA\\mainmenu.jpg");

#ifdef WIN32
	if (!ProtectEnvelopeCheck2())
	{
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\mainmenu.jpg"));
	}
#endif // WIN32

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// прорисовка превью для каждой игры...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	vw_DrawRect(56,255,0,0,128,128,"DATA\\pr_m.bmp");
	vw_DrawRect(176,66,0,0,128,128,"DATA\\pr_b.bmp");
	vw_DrawRect(496,66,0,0,128,128,"DATA\\pr_p.bmp");
	vw_DrawRect(616,255,0,0,128,128,"DATA\\pr_j.bmp");




	bool StartNewGame = false;

	// mosaic
	SetRect(&MDetect, 56, 255, 56+128, 255+128);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 0, 0, 140, 140);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(56-6, 255-6, &MDetect, &DrawON, &DrawOFF, "DATA\\main_game.bmp", true, true))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		Setup.Type = 0;
		StartNewGame = true;
	}
	// builder
	SetRect(&MDetect, 176, 66, 176+128, 66+128);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 0, 0, 140, 140);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(176-6, 66-6, &MDetect, &DrawON, &DrawOFF, "DATA\\main_game.bmp", true, true))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		Setup.Type = 1;
		StartNewGame = true;
	}
	// pair
	SetRect(&MDetect, 496, 66, 496+128, 66+128);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 0, 0, 140, 140);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(496-6, 66-6, &MDetect, &DrawON, &DrawOFF, "DATA\\main_game.bmp", true, true))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		Setup.Type = 2;
		StartNewGame = true;
	}
	// jigsaw
	SetRect(&MDetect, 616, 255, 616+128, 255+128);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 0, 0, 140, 140);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(616-6, 255-6, &MDetect, &DrawON, &DrawOFF, "DATA\\main_game.bmp", true, true))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		Setup.Type = 3;
		StartNewGame = true;
	}





	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// новая игра
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (StartNewGame)
	{
		ComBuffer = GAME_START;
	}



#ifdef WIN32
	if (!ProtectEnvelopeCheck3())
	{
		vw_ReleaseAllTextures();
	}
#endif // WIN32



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка SETUP...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 10, 474, 208, 515);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 1, 603, 197, 641);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(11,476, &MDetect, &DrawON, &DrawOFF, "DATA\\mainmenu.jpg"))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		ComBuffer = SETUP;
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка TOP_SCORES...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 591, 474, 789, 515);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 200, 602, 396, 641);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(592, 475, &MDetect, &DrawON, &DrawOFF, "DATA\\mainmenu.jpg"))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		ComBuffer = TOP_SCORES;
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка CREDITS...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 10, 524, 208, 565);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 1, 644, 197, 683);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(11,525, &MDetect, &DrawON, &DrawOFF, "DATA\\mainmenu.jpg"))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		ComBuffer = CREDITS;
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка quit...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 591, 524, 789, 565);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 200, 644, 396, 683);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(592, 525, &MDetect, &DrawON, &DrawOFF, "DATA\\mainmenu.jpg"))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		SetCurrentDialogBox(1);
	}

}













//------------------------------------------------------------------------------------
// Credits
//------------------------------------------------------------------------------------
void Credits()
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// прорисовка подложки главного меню...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	vw_DrawRect(0,0,0,0,800,600,"DATA\\credits.jpg");




// кнопку DONATE показываем только для линукса, гда игра freeware
#ifdef __unix
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка DONATE
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 313, 524, 489, 565);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 83, 602, 257, 641);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(314, 525, &MDetect, &DrawON, &DrawOFF, "DATA\\credits.jpg"))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		// нужно свернуть игру, запустить броузер и выйти в основное меню
		SDL_WM_IconifyWindow();
		vw_OpenBrouser("https://www.plimus.com/jsp/buynow.jsp?contractId=1659221");
	}
#endif // unix
#ifdef WIN32
	vw_DrawRect(311,522,437,601,619,649,"DATA\\credits.jpg");
#endif // WIN32


#ifdef WIN32
	USER_POLYBUFFER
#endif // WIN32


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка viewizard.com
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 508, 524, 684, 565);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 260, 602, 434, 641);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(509, 525, &MDetect, &DrawON, &DrawOFF, "DATA\\credits.jpg"))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		SDL_WM_IconifyWindow();
		vw_OpenBrouser("http://www.viewizard.com/");
	}







	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка back...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 703, 524, 784, 565);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 1, 602, 80, 641);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(704, 525, &MDetect, &DrawON, &DrawOFF, "DATA\\credits.jpg"))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		ComBuffer = MAIN_MENU;
	}
}





















//------------------------------------------------------------------------------------
// TopScores
//------------------------------------------------------------------------------------
void TopScores()
{

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// прорисовка подложки главного меню...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	vw_DrawRect(0,0,0,0,800,600,"DATA\\topscores.jpg");




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка best...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (TopScoresCurrent != 0)
	{
		SetRect(&MDetect, 277, 524, 358, 565);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		SetRect(&DrawOFF, 0, 0, 0, 0);
		SetRect(&DrawON, 165-82, 644, 234-82, 683);
		if (vw_OnRect(&MDetect)) GameCursor.Current=1;
		if (vw_Button2D(278, 525, &MDetect, &DrawON, &DrawOFF, "DATA\\topscores.jpg"))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			TopScoresCurrent = 0;
		}
	}
	else
		vw_DrawRect(278,525,165-82,602,234-82,641,"DATA\\topscores.jpg");




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка 2x2...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (TopScoresCurrent != 2)
	{
		SetRect(&MDetect, 367, 524, 438, 565);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		SetRect(&DrawOFF, 0, 0, 0, 0);
		SetRect(&DrawON, 165, 644, 234, 683);
		if (vw_OnRect(&MDetect)) GameCursor.Current=1;
		if (vw_Button2D(368, 525, &MDetect, &DrawON, &DrawOFF, "DATA\\topscores.jpg"))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			TopScoresCurrent = 2;
		}
	}
	else
		vw_DrawRect(368,525,165,602,234,641,"DATA\\topscores.jpg");





	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка 4x4...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (TopScoresCurrent != 4)
	{
		SetRect(&MDetect, 449, 524, 520, 565);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		SetRect(&DrawOFF, 0, 0, 0, 0);
		SetRect(&DrawON, 165+72, 644, 234+72, 683);
		if (vw_OnRect(&MDetect)) GameCursor.Current=1;
		if (vw_Button2D(450, 525, &MDetect, &DrawON, &DrawOFF, "DATA\\topscores.jpg"))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			TopScoresCurrent = 4;
		}
	}
	else
		vw_DrawRect(450,525,165+72,602,234+72,641,"DATA\\topscores.jpg");





	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка 6x6...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (TopScoresCurrent != 6)
	{
		SetRect(&MDetect, 531, 524, 602, 565);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		SetRect(&DrawOFF, 0, 0, 0, 0);
		SetRect(&DrawON, 165+72*2, 644, 234+72*2, 683);
		if (vw_OnRect(&MDetect)) GameCursor.Current=1;
		if (vw_Button2D(532, 525, &MDetect, &DrawON, &DrawOFF, "DATA\\topscores.jpg"))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			TopScoresCurrent = 6;
		}
	}
	else
		vw_DrawRect(532,525,165+72*2,602,234+72*2,641,"DATA\\topscores.jpg");




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка 8x8...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (TopScoresCurrent != 8)
	{
		SetRect(&MDetect, 613, 524, 684, 565);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		SetRect(&DrawOFF, 0, 0, 0, 0);
		SetRect(&DrawON, 165+72*3, 644, 234+72*3, 683);
		if (vw_OnRect(&MDetect)) GameCursor.Current=1;
		if (vw_Button2D(614, 525, &MDetect, &DrawON, &DrawOFF, "DATA\\topscores.jpg"))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			TopScoresCurrent = 8;
		}
	}
	else
		vw_DrawRect(614,525,165+72*3,602,234+72*3,641,"DATA\\topscores.jpg");







	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// вывод данных
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	int TopScor[16];

	switch(TopScoresCurrent)
	{
		case 0: memcpy(TopScor, Setup.Time, sizeof(TopScor)); break;
		case 2: memcpy(TopScor, Setup.Time2x2, sizeof(TopScor)); break;
		case 4: memcpy(TopScor, Setup.Time4x4, sizeof(TopScor)); break;
		case 6: memcpy(TopScor, Setup.Time6x6, sizeof(TopScor)); break;
		case 8: memcpy(TopScor, Setup.Time8x8, sizeof(TopScor)); break;
	}



	int k=94;
	int i;

	char buffer[20];
	char buffer2[20];
	for (i=0; i<5; i++)
	{
		itoa10(TopScor[i], buffer);
		if (strlen(buffer)<5)
		{
			if (strlen(buffer)==1) strcpy(buffer2, "0000");
			if (strlen(buffer)==2) strcpy(buffer2, "000");
			if (strlen(buffer)==3) strcpy(buffer2, "00");
			if (strlen(buffer)==4) strcpy(buffer2, "0");
			strcat(buffer2, buffer);
			DrawManualText(308+k*i, 110, buffer2, 0, 0);
		}
		else
			DrawManualText(308+k*i, 110, buffer, 0, 0);
	}
	for (i=5; i<10; i++)
	{
		itoa10(TopScor[i], buffer);
		if (strlen(buffer)<5)
		{
			if (strlen(buffer)==1) strcpy(buffer2, "0000");
			if (strlen(buffer)==2) strcpy(buffer2, "000");
			if (strlen(buffer)==3) strcpy(buffer2, "00");
			if (strlen(buffer)==4) strcpy(buffer2, "0");
			strcat(buffer2, buffer);
			DrawManualText(308+k*(i-5), 110+120, buffer2,0, 0);
		}
		else
			DrawManualText(308+k*(i-5), 110+120, buffer,0, 0);
	}
	for (i=10; i<13; i++)
	{
		itoa10(TopScor[i], buffer);
		if (strlen(buffer)<5)
		{
			if (strlen(buffer)==1) strcpy(buffer2, "0000");
			if (strlen(buffer)==2) strcpy(buffer2, "000");
			if (strlen(buffer)==3) strcpy(buffer2, "00");
			if (strlen(buffer)==4) strcpy(buffer2, "0");
			strcat(buffer2, buffer);
			DrawManualText(308+k*(1+i-10), 110+240, buffer2,0, 0);
		}
		else
			DrawManualText(308+k*(1+i-10), 110+240, buffer,0, 0);
	}
	for (i=13; i<16; i++)
	{
		itoa10(TopScor[i], buffer);
		if (strlen(buffer)<5)
		{
			if (strlen(buffer)==1) strcpy(buffer2, "0000");
			if (strlen(buffer)==2) strcpy(buffer2, "000");
			if (strlen(buffer)==3) strcpy(buffer2, "00");
			if (strlen(buffer)==4) strcpy(buffer2, "0");
			strcat(buffer2, buffer);
			DrawManualText(308+k*(1+i-13), 110+360, buffer2,0, 0);
		}
		else
			DrawManualText(308+k*(1+i-13), 110+360, buffer,0, 0);
	}


#ifdef WIN32
	USER_POLYBUFFER
#endif // WIN32

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка back...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 703, 524, 784, 565);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 1, 602, 80, 641);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(704, 525, &MDetect, &DrawON, &DrawOFF, "DATA\\topscores.jpg"))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		ComBuffer = MAIN_MENU;
	}
}














//------------------------------------------------------------------------------------
// Setup
//------------------------------------------------------------------------------------
void SetupProc()
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// прорисовка подложки меню...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	vw_DrawRect(0,0,0,0,800,600,"DATA\\setup.jpg");



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка back...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 703, 524, 784, 565);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 1, 602, 80, 641);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(704, 525, &MDetect, &DrawON, &DrawOFF, "DATA\\setup.jpg"))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		ComBuffer = MAIN_MENU;
	}






	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка Apply...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 603, 524, 684, 565);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 83, 602, 162, 641);
	if ((nFullscrSw != Setup.FullscrSw) ||
		(nWindowsBPP != Setup.WindowsBPP)||
		(nMusicSw != Setup.MusicSw)||
		(nMusicSw_Game != Setup.MusicSw_Game)||
		(nSoundSw != Setup.SoundSw))
	{
		if (vw_OnRect(&MDetect)) GameCursor.Current=1;
		if (vw_Button2D(604, 525, &MDetect, &DrawON, &DrawOFF, "DATA\\setup.jpg"))
		{

			ComBuffer = MAIN_MENU;
		//	if (Setup.SoundSw) Audio_PlaySound(1);
			Setup.SoundSw = nSoundSw;
			Setup.MusicSw = nMusicSw;
			Setup.MusicSw_Game = nMusicSw_Game;


			if ((nFullscrSw != Setup.FullscrSw) ||
				(nWindowsBPP != Setup.WindowsBPP))
			{
				Setup.FullscrSw = nFullscrSw;
				Setup.WindowsBPP = nWindowsBPP;
				NeedReCreate = true;
				ComBuffer = 912;
			}
		}
	}
	else
		vw_DrawRect(604, 525, 165,602,244,641,"DATA\\setup.jpg");







	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// опция music....
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Setup.Music_check)
	{
		SetRect(&MDetect, 608,61, 608+70, 61+30);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		if (vw_OnRect(&MDetect))
		{
			GameCursor.Current=1;
			if (vw_GetWindowLBMouse(true))
			{
				if (Setup.SoundSw) Audio_PlaySound(1);
				nMusicSw = true;
			}
			vw_DrawRect(614,60,0,0,57,31,"DATA\\setup2.bmp");
		}

		SetRect(&MDetect, 693,61, 693+70, 61+30);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		if (vw_OnRect(&MDetect))
		{
			GameCursor.Current=1;
			if (vw_GetWindowLBMouse(true))
			{
				if (Setup.SoundSw) Audio_PlaySound(1);
				nMusicSw = false;
			}
			vw_DrawRect(689,60,59,0,131,31,"DATA\\setup2.bmp");
		}
	}
	else
		vw_DrawRect(608+7,61+2,0,0,56,25,"DATA\\setup_off.bmp", true);


	if (nMusicSw)
		vw_DrawRect(614,60,0,0,57,31,"DATA\\setup2.bmp");
	else
		vw_DrawRect(689,60,59,0,131,31,"DATA\\setup2.bmp");







	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// опция music_Game....
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Setup.Music_check)
	{
		SetRect(&MDetect, 608,61+80, 608+70, 61+80+30);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		if (vw_OnRect(&MDetect))
		{
			GameCursor.Current=1;
			if (vw_GetWindowLBMouse(true))
			{
				if (Setup.SoundSw) Audio_PlaySound(1);
				nMusicSw_Game = true;
			}
			vw_DrawRect(614,140,0,32,57,63,"DATA\\setup2.bmp");
		}

		SetRect(&MDetect, 693,61+80, 693+70, 61+80+30);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		if (vw_OnRect(&MDetect))
		{
			GameCursor.Current=1;
			if (vw_GetWindowLBMouse(true))
			{
				if (Setup.SoundSw) Audio_PlaySound(1);
				nMusicSw_Game = false;
			}
			vw_DrawRect(689,140,59,32,131,63,"DATA\\setup2.bmp");
		}
	}
	else
		vw_DrawRect(608+7,61+2+80,0,0,56,25,"DATA\\setup_off.bmp", true);


	if (nMusicSw_Game)
		vw_DrawRect(614,140,0,32,57,63,"DATA\\setup2.bmp");
	else
		vw_DrawRect(689,140,59,32,131,63,"DATA\\setup2.bmp");




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// опция sound...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Setup.Sound_check)
	{
		SetRect(&MDetect, 608,61+160, 608+70, 61+160+30);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		if (vw_OnRect(&MDetect))
		{
			GameCursor.Current=1;
			if (vw_GetWindowLBMouse(true))
			{
				if (Setup.SoundSw) Audio_PlaySound(1);
				nSoundSw = true;
			}
			vw_DrawRect(614,220,0,64,57,95,"DATA\\setup2.bmp");
		}

		SetRect(&MDetect, 693,61+160, 693+70, 61+160+30);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		if (vw_OnRect(&MDetect))
		{
			GameCursor.Current=1;
			if (vw_GetWindowLBMouse(true))
			{
				if (Setup.SoundSw) Audio_PlaySound(1);
				nSoundSw = false;
			}
			vw_DrawRect(689,220,59,64,131,95,"DATA\\setup2.bmp");
		}
	}
	else
		vw_DrawRect(608+7,61+2+160,0,0,56,25,"DATA\\setup_off.bmp", true);

	if (nSoundSw)
		vw_DrawRect(614,220,0,64,57,95,"DATA\\setup2.bmp");
	else
		vw_DrawRect(689,220,59,64,131,95,"DATA\\setup2.bmp");







	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// опция WindowStatus...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 608,61+240, 608+70, 61+240+30);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	if (vw_OnRect(&MDetect))
	{
		GameCursor.Current=1;
		if (vw_GetWindowLBMouse(true))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			nFullscrSw = true;
		}
		vw_DrawRect(614,300,0,96,57,127,"DATA\\setup2.bmp");
	}

	SetRect(&MDetect, 693,61+240, 693+70, 61+240+30);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	if (vw_OnRect(&MDetect))
	{
		GameCursor.Current=1;
		if (vw_GetWindowLBMouse(true))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			nFullscrSw = false;
			// возвращаем в текущее состояние глубину
			nWindowsBPP = Setup.WindowsBPP;
		}
		vw_DrawRect(689,300,59,96,131,127,"DATA\\setup2.bmp");
	}


	if (nFullscrSw)
		vw_DrawRect(614,300,0,96,57,127,"DATA\\setup2.bmp");
	else
		vw_DrawRect(689,300,59,96,131,127,"DATA\\setup2.bmp");








	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// опция bpp... работает только в полноэкранном режиме!
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef WIN32	// для win32 делаем переключения 16-32
	if (nFullscrSw)
	{
		SetRect(&MDetect, 608,61+320, 608+70, 61+320+30);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		if (vw_OnRect(&MDetect))
		{
			GameCursor.Current=1;
			if (vw_GetWindowLBMouse(true))
			{
				if (Setup.SoundSw) Audio_PlaySound(1);
				nWindowsBPP = 16;
			}
			vw_DrawRect(614,380,0,128,57,159,"DATA\\setup2.bmp");
		}

		SetRect(&MDetect, 693,61+320, 693+70, 61+320+30);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		if (vw_OnRect(&MDetect))
		{
			GameCursor.Current=1;
			if (vw_GetWindowLBMouse(true))
			{
				if (Setup.SoundSw) Audio_PlaySound(1);
				nWindowsBPP = 32;
			}
			vw_DrawRect(689,380,59,128,131,159,"DATA\\setup2.bmp");
		}
	}

	if (nWindowsBPP==16)
		vw_DrawRect(614,380,0,128,57,159,"DATA\\setup2.bmp");
	else
		vw_DrawRect(689,380,59,128,131,159,"DATA\\setup2.bmp");
#endif // WIN32
#ifdef __unix
	// рисуем 24 по верх 32
	vw_DrawRect(689+12,383,59-57,128+34,131-57,159+30,"DATA\\setup2.bmp");
	// для линукса делаем переключение 16-24
	if (nFullscrSw)
	{
		SetRect(&MDetect, 608,61+320, 608+70, 61+320+30);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		if (vw_OnRect(&MDetect))
		{
			GameCursor.Current=1;
			if (vw_GetWindowLBMouse(true))
			{
				if (Setup.SoundSw) Audio_PlaySound(1);
				nWindowsBPP = 16;
			}
			vw_DrawRect(614,380,0,128,57,159,"DATA\\setup2.bmp");
		}

		SetRect(&MDetect, 693,61+320, 693+70, 61+320+30);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		if (vw_OnRect(&MDetect))
		{
			GameCursor.Current=1;
			if (vw_GetWindowLBMouse(true))
			{
				if (Setup.SoundSw) Audio_PlaySound(1);
				nWindowsBPP = 24;
			}
			vw_DrawRect(689,380,59,128+33,131,159+33,"DATA\\setup2.bmp");
		}
	}

	if (nWindowsBPP==16)
		vw_DrawRect(614,380,0,128,57,159,"DATA\\setup2.bmp");
	else
		vw_DrawRect(689,380,59,128+33,131,159+33,"DATA\\setup2.bmp");
#endif // unix

}
