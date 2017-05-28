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

// защелка - проверяли вхождения в рекорды в этой игре или нет
bool TopScCheck = false;
// задержка на 2 прохода (иначе не усп.прорисов.)
int TopScCheckStop = 2;
// для пары
bool ErrorShow = false;// показ ошибочной, перед закрытием...
Uint32 ErrorShowTime = 0; // показываем минуту, потом закрываем все...
bool RightShow = false;// показ ошибочной, перед закрытием...
Uint32 RightShowTime = 0; // показываем минуту, потом закрываем все...
int ErrorShowX, ErrorShowY;






















//------------------------------------------------------------------------------------
// просчет победы...
//------------------------------------------------------------------------------------
void CheckGameWin()
{
	for (int i=0; i<8; i++)
	for (int j=0; j<8; j++)
	{
		if (SetFieldData[i][j] != FieldData[i][j]) return;
	}

	// иначе - выиграли...
	GameWin = true;
	// выводим диалог
	SetCurrentDialogBox(YOU_WINNER);
}


//------------------------------------------------------------------------------------
// SetTopScores
//------------------------------------------------------------------------------------
void SetTopScores(int num)
{
	int PosGameTime = (int)(GameTime/1000.0f);
	if (Setup.Time[num] > PosGameTime) Setup.Time[num] = PosGameTime;
	switch(Setup.Size)
	{
		case 2: if (Setup.Time2x2[num] > PosGameTime) Setup.Time2x2[num] = PosGameTime;break;
		case 4: if (Setup.Time4x4[num] > PosGameTime) Setup.Time4x4[num] = PosGameTime;break;
		case 6: if (Setup.Time6x6[num] > PosGameTime) Setup.Time6x6[num] = PosGameTime;break;
		case 8: if (Setup.Time8x8[num] > PosGameTime) Setup.Time8x8[num] = PosGameTime;break;
	}
}





//------------------------------------------------------------------------------------
// проверяем, можно ли показывать этот элемент,
// 1 - он должен быть на начальном рисунке
// 2 - он НЕ должен быть установлен (если не один = -1)
//------------------------------------------------------------------------------------
bool CheckList(int Check)
{
	int present = 0;

	for (int i=0; i<8; i++)
	for (int j=0; j<8; j++)
	{
		if (FieldData[i][j] == Check) present ++;
		if (SetFieldData[i][j] == Check) present --;
	}

	if (GameCursor.ExCurrent == 3 && GameCursor.text == Check) present --;
	// только если есть еще не открытые такие...
	if (present > 0) return true;

	return false;
}







//------------------------------------------------------------------------------------
// оснавная процедура игры
//------------------------------------------------------------------------------------
void Game()
{

	RECT MDetect;
	RECT DrawON;
	RECT DrawOFF;
	RECT SrcRest;
	SetRect(&SrcRest, 0, 0, 64, 64);



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// если нажали левой кнопкой на поле - установка текущего...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	int X,Y;
	vw_GetMousePos(&X, &Y);



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// прорисовка подложки ...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	vw_DrawRect(0,0,0,0,800,600,"DATA\\game.jpg");



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// прорисовка на поле элементов...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	for (int i=0; i<8; i++)
	for (int j=0; j<8; j++)
	{
		if (SetFieldData[i][j] == -1)
			vw_Draw(44+i*64,44+j*64,&SrcRest, vw_FindTextureByName("DATA\\BUILDER\\0.bmp"), true);
		else
		{
			if (SetFieldData[i][j] != 0)
			{
					vw_Draw(44+i*64,44+j*64,&SrcRest, vw_FindTextureByNum(SetFieldData[i][j]), false);

			}
			else
			{
				if (Setup.Type == 0 || Setup.Type == 1 || Setup.Type == 3)
					vw_Draw(44+i*64,44+j*64,&SrcRest, vw_FindTextureByName("DATA\\BUILDER\\0.bmp"), true);
				else
					if (FieldData[i][j] != 0)
					vw_Draw(44+i*64,44+j*64,&SrcRest, vw_FindTextureByName("DATA\\PAIR\\0.bmp"), false);
					else
						vw_Draw(44+i*64,44+j*64,&SrcRest, vw_FindTextureByName("DATA\\BUILDER\\0.bmp"), true);


				// прорисовываем "бордюр" для всех, кроме 8на8
				if (Setup.Type != 2)
				if (FieldData[i][j] == 0)
					vw_Draw(44+i*64,44+j*64,&SrcRest, vw_FindTextureByName("DATA\\error3.bmp"), true);
			}
		}
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// тащить с выбора...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (!GameWin)
	if (!isDialogBoxDrawing())
	if (Setup.Type == 0 || Setup.Type == 1 || Setup.Type == 3)
	if ((X>601 && Y>212) && (X<601+64 && Y<212+64))
	{
		int curtext = SetPanelPos;
		// если есть элемент с низу - по умолчанию, можем его тащить...
		if (curtext!=0) GameCursor.Current = 2;

		// кнопка нажата - нужно отработать...
		if (vw_GetWindowLBMouse(false))
		{
			// если до этого захвата не было - захватываем, если есть что...
			if (GameCursor.ExCurrent!=3 && curtext!=0)
			{
				// для билдера и jig-saw
				if (Setup.Type == 1 || Setup.Type == 3)
				if (CheckList(SetPanelPos))
				{
					GameCursor.text = curtext;
					GameCursor.X = 0;
					GameCursor.Y = 0;
					GameCursor.Current = 3;
					GameCursor.ExCurrent = 3;

					if (!CheckList(SetPanelPos))
					{
						int stop = SetPanelPos;// если всего один элемент...
						bool rot=false;
						while (!CheckList(SetPanelPos))
						{
							SetPanelPos --;
							if (SetPanelPos<StartPanelPos) {SetPanelPos = EndPanelPos;rot=true;}
							if (rot && stop == SetPanelPos) break;
						}
					}
				}
				else GameCursor.Current=0;

				if (Setup.Type == 0)
				{
					GameCursor.text = curtext;
					GameCursor.X = 0;
					GameCursor.Y = 0;
					GameCursor.Current = 3;
					GameCursor.ExCurrent = 3;
				}
			}
			// если уже что-то тянем - ставим нужный курсор...
			if (GameCursor.ExCurrent==3)
			{
				GameCursor.Current=3;
			}
		}
		else
		{
			// если тут отпустили...
			if (GameCursor.ExCurrent==3)
			{
				GameCursor.ExCurrent = 2;
				GameCursor.Current = 2;

				// проверка в списке оставшихся элементов...
				// для билдера и jig-saw
				if (Setup.Type == 1 || Setup.Type == 3)
				if (CheckList(SetPanelPos))
				{
					if (!CheckList(SetPanelPos))
					{
						int stop = SetPanelPos;// если всего один элемент...
						bool rot=false;
						while (!CheckList(SetPanelPos))
						{
							SetPanelPos --;
							if (SetPanelPos<StartPanelPos) {SetPanelPos = EndPanelPos;rot=true;}
							if (rot && stop == SetPanelPos) break;
						}
					}
				}
			}
			else
			// для билдера и jig-saw - если нечего выбирать - не показываем курсор "тянуть"
			if (Setup.Type == 1 || Setup.Type == 3)
				if (!CheckList(SetPanelPos)) GameCursor.Current=0;
		}
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// на поле...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (!GameWin)
	if (!isDialogBoxDrawing())
	if (Setup.Type == 0 || Setup.Type == 1 || Setup.Type == 3)
	if ((X>44 && Y>44) && (X<44+512 && Y<44+512))
	{
		// получаем текущий квадрат...
		int curx = (int)((X-44)/64);
		int cury = (int)((Y-44)/64);
		int curtext = SetFieldData[curx][cury];

		// если есть элемент с низу - по умолчанию, можем его тащить...
		if (curtext!=0) GameCursor.Current = 2;

		// кнопка нажата - нужно отработать...
		if (vw_GetWindowLBMouse(false))
		{
			// если до этого захвата не было - захватываем, если есть что...
			if (GameCursor.ExCurrent!=3 && curtext!=0)
			{
				GameCursor.text = curtext;
				GameCursor.X = curx;
				GameCursor.Y = cury;
				GameCursor.Current = 3;
				GameCursor.ExCurrent = 3;
				SetFieldData[curx][cury] = 0;
			}
			// если уже что-то тянем - ставим нужный курсор...
			if (GameCursor.ExCurrent==3)
			{
				GameCursor.Current=3;
			}
		}
		else
			// если тут отпустили...
			if (GameCursor.ExCurrent==3)
			{
				SetFieldData[curx][cury] = GameCursor.text;
				GameCursor.ExCurrent = 2;
				GameCursor.Current = 2;

				// проверка в списке оставшихся элементов...
				// если перетянули на какой-то элемент...
				// для билдера и jig-saw
				if (Setup.Type == 1 || Setup.Type == 3)
				{
					if (!CheckList(SetPanelPos))
					{
						int stop = SetPanelPos;// если всего один элемент...
						bool rot=false;
						while (!CheckList(SetPanelPos))
						{
							SetPanelPos --;
							if (SetPanelPos<StartPanelPos) {SetPanelPos = EndPanelPos;rot=true;}
							if (rot && stop == SetPanelPos) break;
						}
					}
				}

				CheckGameWin();
			}


		if (vw_GetWindowRBMouse(true))
		{

			int tmp = SetFieldData[(int)((X-44)/64)][(int)((Y-44)/64)];
			SetFieldData[(int)((X-44)/64)][(int)((Y-44)/64)] = 0;

			// если пустой текущий - проверяем, чтобы его заполнить...
			if (Setup.Type == 1)
			if (!CheckList(SetPanelPos))
			{
				int stop = SetPanelPos;// если всего один элемент...
				bool rot=false;
				while (!CheckList(SetPanelPos))
				{
					SetPanelPos --;
					if (SetPanelPos<StartPanelPos) {SetPanelPos = EndPanelPos;rot=true;}
					if (rot && stop == SetPanelPos) break;
				}
			}

			if (Setup.Type == 3)
			{
				// если тут что-то было - ставим его текущим
				if (tmp!=0)	SetPanelPos = tmp;
			}

			CheckGameWin();
		}
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// вне поля...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (!GameWin)
	if (Setup.Type == 0 || Setup.Type == 1 || Setup.Type == 3)
	if (!((X>44 && Y>44) && (X<44+512 && Y<44+512)))
	{
		// кнопка нажата - нужно отработать...
		if (vw_GetWindowLBMouse(false))
		{
			// если уже что-то тянем - ставим нужный курсор...
			if (GameCursor.ExCurrent==3)
			{
				GameCursor.Current=3;
			}
		}
		else
			// если тут отпустили...
			if (GameCursor.ExCurrent==3)
			{
				GameCursor.ExCurrent = 0;
				GameCursor.Current = 0;

				//изменение в списке...
				// если пустой текущий - проверяем, чтобы его заполнить...
				if (Setup.Type == 1)
				if (!CheckList(SetPanelPos))
				{
					int stop = SetPanelPos;// если всего один элемент...
					bool rot=false;
					while (!CheckList(SetPanelPos))
					{
						SetPanelPos --;
						if (SetPanelPos<StartPanelPos) {SetPanelPos = EndPanelPos;rot=true;}
						if (rot && stop == SetPanelPos) break;
					}
				}

				if (Setup.Type == 3)
				{
					SetPanelPos = GameCursor.text;
				}
			}
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// на поле....пара...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (!GameWin)
	if (!isDialogBoxDrawing())
	if (Setup.Type == 2 && !ErrorShow && !RightShow)
	{
		if ((X>44 && Y>44) && (X<44+512 && Y<44+512))
		{
			if (vw_GetWindowLBMouse(true))
			if (FieldData[(int)((X-44)/64)][(int)((Y-44)/64)] != -1 && FieldData[(int)((X-44)/64)][(int)((Y-44)/64)] != 0)// не открыто еще
			{
				if (SearchFor==0)
				{
					if (FieldData[(int)((X-44)/64)][(int)((Y-44)/64)]!=-1)
						SearchFor = SetFieldData[(int)((X-44)/64)][(int)((Y-44)/64)] = FieldData[(int)((X-44)/64)][(int)((Y-44)/64)];
				}
				else
				{
					if (SearchFor != FieldData[(int)((X-44)/64)][(int)((Y-44)/64)])
					{
						SetFieldData[(int)((X-44)/64)][(int)((Y-44)/64)]=FieldData[(int)((X-44)/64)][(int)((Y-44)/64)];
						ErrorShow = true;
						ErrorShowTime = SDL_GetTicks();
					}
					else
					{
						if (SetFieldData[(int)((X-44)/64)][(int)((Y-44)/64)]==0)
						{
							SetFieldData[(int)((X-44)/64)][(int)((Y-44)/64)]=FieldData[(int)((X-44)/64)][(int)((Y-44)/64)];
							RightShow = true;
							RightShowTime = SDL_GetTicks();
						}
					}
				}

				CheckGameWin();
			}

			if (FieldData[(int)((X-44)/64)][(int)((Y-44)/64)] != 0 && SetFieldData[(int)((X-44)/64)][(int)((Y-44)/64)]==0 )
				GameCursor.Current = 1;//показываем, что можем нажать
		}
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// автозакрытие для пары...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (ErrorShow)
	if (ErrorShowTime+500 < SDL_GetTicks())
	{
		for (int i=0; i<8; i++)
		for (int j=0; j<8; j++)
		{
			if (SetFieldData[i][j] != -1) SetFieldData[i][j]=0;

			// если сложность большая - все закрыть...
			if (Setup.Difficult == 2)
			{
				FieldData[i][j]=FieldDataPair[i][j];
				SetFieldData[i][j] = 0;
			}
		}
		SearchFor = 0;
		ErrorShow = false;

	}
	// автоудаление с задержкой для пары...
	if (RightShow)
	if (RightShowTime+500 < SDL_GetTicks())
	{
		for (int i=0; i<8; i++)
		for (int j=0; j<8; j++)
		if (SearchFor == SetFieldData[i][j])
		{
			SetFieldData[i][j]=-1;
			FieldData[i][j]=-1;
		}
		SearchFor = 0;
		RightShow = false;
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// панель выбора - кнопки мазаики
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Setup.Type == 0 /*&& Setup.Difficult == 2*/)
	{
		vw_DrawRect(578,124,431,602-600,637,843-600,"DATA\\game2.bmp");

		// кнопка красные...
		if (StartPanelPos != vw_FindTextureByName("DATA\\MOSAIC\\1_1.bmp")->Num)
		{
			SetRect(&MDetect, 716,124,776,165);
			if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
			SetRect(&DrawOFF, 0, 0, 0, 0);
			SetRect(&DrawON, 654,605-600,690,638-600);
			// работает только если ничего не тянем...
			if (GameCursor.Current!=3)
			{
				if (vw_OnRect(&MDetect)) GameCursor.Current=1;
				if (vw_Button2D(728,127, &MDetect, &DrawON, &DrawOFF, "DATA\\game2.bmp",true))
				{
					if (Setup.SoundSw) Audio_PlaySound(1);
					SetPanelPos = SetPanelPos-StartPanelPos;
					StartPanelPos = vw_FindTextureByName("DATA\\MOSAIC\\1_1.bmp")->Num;
					EndPanelPos = vw_FindTextureByName("DATA\\MOSAIC\\1_0.bmp")->Num;
					SetPanelPos += StartPanelPos;
				}
			}
		}
		else
		{
			// рисуем, что нажать нельзя...
			RECT SrcRest;
			SetRect(&SrcRest, 0+148, 0+26, 228-13, 294-220);
			vw_Draw(566+148,97+26,&SrcRest, vw_FindTextureByName("DATA\\game3.bmp"), true);
		}


		// кнопка голубые...
		if (StartPanelPos != vw_FindTextureByName("DATA\\MOSAIC\\2_1.bmp")->Num)
		{
			SetRect(&MDetect, 716,124+49,776,165+49);
			if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
			SetRect(&DrawOFF, 0, 0, 0, 0);
			SetRect(&DrawON, 654,605+49-600,690,638+49-600);
			// работает только если ничего не тянем...
			if (GameCursor.Current!=3)
			{
				if (vw_OnRect(&MDetect)) GameCursor.Current=1;
				if (vw_Button2D(728,127+49, &MDetect, &DrawON, &DrawOFF, "DATA\\game2.bmp",true))
				{
					if (Setup.SoundSw) Audio_PlaySound(1);
					SetPanelPos = SetPanelPos-StartPanelPos;
					StartPanelPos = vw_FindTextureByName("DATA\\MOSAIC\\2_1.bmp")->Num;
					EndPanelPos = vw_FindTextureByName("DATA\\MOSAIC\\2_0.bmp")->Num;
					SetPanelPos += StartPanelPos;
				}
			}
		}
		else
		{
			// рисуем, что нажать нельзя...
			RECT SrcRest;
			SetRect(&SrcRest, 0+148, 0+26+49, 228-13, 294-220+49);
			vw_Draw(566+148,97+26+49,&SrcRest, vw_FindTextureByName("DATA\\game3.bmp"), true);
		}


		// кнопка зеленые...
		if (StartPanelPos != vw_FindTextureByName("DATA\\MOSAIC\\3_1.bmp")->Num)
		{
			SetRect(&MDetect, 716,124+49+49,776,165+49+49);
			if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
			SetRect(&DrawOFF, 0, 0, 0, 0);
			SetRect(&DrawON, 654,605+49+49-600,690,638+49+49-600);
			// работает только если ничего не тянем...
			if (GameCursor.Current!=3)
			{
				if (vw_OnRect(&MDetect)) GameCursor.Current=1;
				if (vw_Button2D(728,127+49+49, &MDetect, &DrawON, &DrawOFF, "DATA\\game2.bmp",true))
				{
					if (Setup.SoundSw) Audio_PlaySound(1);
					SetPanelPos = SetPanelPos-StartPanelPos;
					StartPanelPos = vw_FindTextureByName("DATA\\MOSAIC\\3_1.bmp")->Num;
					EndPanelPos = vw_FindTextureByName("DATA\\MOSAIC\\3_0.bmp")->Num;
					SetPanelPos += StartPanelPos;
				}
			}
		}
		else
		{
			// рисуем, что нажать нельзя...
			RECT SrcRest;
			SetRect(&SrcRest, 0+148, 0+26+49*2, 228-13, 294-220+49*2);
			vw_Draw(566+148,97+26+49*2,&SrcRest, vw_FindTextureByName("DATA\\game3.bmp"), true);
		}


		// кнопка сиреневый...
		if (StartPanelPos != vw_FindTextureByName("DATA\\MOSAIC\\4_1.bmp")->Num)
		{
			SetRect(&MDetect, 716,124+49+49+49,776,165+49+49+49);
			if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
			SetRect(&DrawOFF, 0, 0, 0, 0);
			SetRect(&DrawON, 654,605+49+49+49-600,690,638+49+49+49-600);
			// работает только если ничего не тянем...
			if (GameCursor.Current!=3)
			{
				if (vw_OnRect(&MDetect)) GameCursor.Current=1;
				if (vw_Button2D(728,127+49+49+49, &MDetect, &DrawON, &DrawOFF, "DATA\\game2.bmp",true))
				{
					if (Setup.SoundSw) Audio_PlaySound(1);
					SetPanelPos = SetPanelPos-StartPanelPos;
					StartPanelPos = vw_FindTextureByName("DATA\\MOSAIC\\4_1.bmp")->Num;
					EndPanelPos = vw_FindTextureByName("DATA\\MOSAIC\\4_0.bmp")->Num;
					SetPanelPos += StartPanelPos;
				}
			}
		}
		else
		{
			// рисуем, что нажать нельзя...
			RECT SrcRest;
			SetRect(&SrcRest, 0+148, 0+26+49*3, 228-13, 294-220+49*3);
			vw_Draw(566+148,97+26+49*3,&SrcRest, vw_FindTextureByName("DATA\\game3.bmp"), true);
		}


		// кнопка синий...
		if (StartPanelPos != vw_FindTextureByName("DATA\\MOSAIC\\5_1.bmp")->Num)
		{
			SetRect(&MDetect, 716,124+49+49+49+49,776,165+49+49+49+49);
			if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
			SetRect(&DrawOFF, 0, 0, 0, 0);
			SetRect(&DrawON, 654,605+49+49+49+49-600,690,638+49+49+49+49-600);
			// работает только если ничего не тянем...
			if (GameCursor.Current!=3)
			{
				if (vw_OnRect(&MDetect)) GameCursor.Current=1;
				if (vw_Button2D(728,127+49+49+49+49, &MDetect, &DrawON, &DrawOFF, "DATA\\game2.bmp",true))
				{
					if (Setup.SoundSw) Audio_PlaySound(1);
					SetPanelPos = SetPanelPos-StartPanelPos;
					StartPanelPos = vw_FindTextureByName("DATA\\MOSAIC\\5_1.bmp")->Num;
					EndPanelPos = vw_FindTextureByName("DATA\\MOSAIC\\5_0.bmp")->Num;
					SetPanelPos += StartPanelPos;
				}
			}
		}
		else
		{
			// рисуем, что нажать нельзя...
			RECT SrcRest;
			SetRect(&SrcRest, 0+148, 0+26+49*4, 228-13, 294-220+49*4);
			vw_Draw(566+148,97+26+49*4,&SrcRest, vw_FindTextureByName("DATA\\game3.bmp"), true);
		}
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// панель выбора - кнопки части дома для builder'a
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Setup.Type == 1)
	{
		vw_DrawRect(578,144,163,602-600,365,804-600,"DATA\\game2.bmp");

		// кнопка окна...
		if (StartPanelPos != vw_FindTextureByName("DATA\\BUILDER\\12_03\\61.bmp")->Num)
		{
			SetRect(&MDetect, 716,144,776,185);
			if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
			SetRect(&DrawOFF, 0, 0, 0, 0);
			SetRect(&DrawON, 381,603-600,416,637-600);
			// только если ничего уже не тянем...
			if (GameCursor.Current!=3)
			{
				if (vw_OnRect(&MDetect)) GameCursor.Current=1;
				if (vw_Button2D(729,147, &MDetect, &DrawON, &DrawOFF, "DATA\\game2.bmp",true))
				{
					if (Setup.SoundSw) Audio_PlaySound(1);
					StartPanelPos = vw_FindTextureByName("DATA\\BUILDER\\12_03\\61.bmp")->Num;
					EndPanelPos = vw_FindTextureByName("DATA\\BUILDER\\2_03\\75.bmp")->Num;
					SetPanelPos = StartPanelPos+1;

					// корректировка SetPanelPos
					int stop = SetPanelPos;// если всего один элемент...
					bool rot=false;
					while (!CheckList(SetPanelPos))
					{
						SetPanelPos --;
						if (SetPanelPos<StartPanelPos) {SetPanelPos = EndPanelPos;rot=true;}
						if (rot && stop == SetPanelPos) break;
					}
				}
			}
		}
		else
		{
			// рисуем, что нажать нельзя...
			RECT SrcRest;
			SetRect(&SrcRest, 0+148, 0+46, 228-15, 294-202);
			vw_Draw(567+148,97+46,&SrcRest, vw_FindTextureByName("DATA\\game3.bmp"), true);
		}

		// кнопка стены...
		if (StartPanelPos != vw_FindTextureByName("DATA\\BUILDER\\1_01_50\\a-09.bmp")->Num)
		{
			SetRect(&MDetect, 716,144+52,776,185+52);
			if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
			SetRect(&DrawOFF, 0, 0, 0, 0);
			SetRect(&DrawON, 381,603+41-600,416,637+41-600);
			// только если ничего уже не тянем...
			if (GameCursor.Current!=3)
			{
				if (vw_OnRect(&MDetect)) GameCursor.Current=1;
				if (vw_Button2D(729,147+52, &MDetect, &DrawON, &DrawOFF, "DATA\\game2.bmp",true))
				{
					if (Setup.SoundSw) Audio_PlaySound(1);
					StartPanelPos = vw_FindTextureByName("DATA\\BUILDER\\1_01_50\\a-09.bmp")->Num;
					EndPanelPos = vw_FindTextureByName("DATA\\BUILDER\\2_05_50\\11.bmp")->Num;
					SetPanelPos = StartPanelPos+1;
					// корректировка SetPanelPos
					int stop = SetPanelPos;// если всего один элемент...
					bool rot=false;
					while (!CheckList(SetPanelPos))
					{
						SetPanelPos --;
						if (SetPanelPos<StartPanelPos) {SetPanelPos = EndPanelPos;rot=true;}
						if (rot && stop == SetPanelPos) break;
					}
				}
			}
		}
		else
		{
			// рисуем, что нажать нельзя...
			RECT SrcRest;
			SetRect(&SrcRest, 0+148, 0+46+52, 228-15, 294-202+52);
			vw_Draw(567+148,97+46+52,&SrcRest, vw_FindTextureByName("DATA\\game3.bmp"), true);
		}

		// кнопка двери...
		if (StartPanelPos != vw_FindTextureByName("DATA\\BUILDER\\1_02_30\\19.bmp")->Num)
		{
			SetRect(&MDetect, 716,144+52+52,776,185+52+52);
			if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
			SetRect(&DrawOFF, 0, 0, 0, 0);
			SetRect(&DrawON, 381,603+41+41-600,416,637+41+41-600);
			// только если ничего уже не тянем...
			if (GameCursor.Current!=3)
			{
				if (vw_OnRect(&MDetect)) GameCursor.Current=1;
				if (vw_Button2D(729,147+52+52, &MDetect, &DrawON, &DrawOFF, "DATA\\game2.bmp",true))
				{
					if (Setup.SoundSw) Audio_PlaySound(1);
					StartPanelPos = vw_FindTextureByName("DATA\\BUILDER\\1_02_30\\19.bmp")->Num;
					EndPanelPos = vw_FindTextureByName("DATA\\BUILDER\\1_04_30\\18.bmp")->Num;
					SetPanelPos = StartPanelPos+1;
					// корректировка SetPanelPos
					int stop = SetPanelPos;// если всего один элемент...
					bool rot=false;
					while (!CheckList(SetPanelPos))
					{
						SetPanelPos --;
						if (SetPanelPos<StartPanelPos) {SetPanelPos = EndPanelPos;rot=true;}
						if (rot && stop == SetPanelPos) break;
					}
				}
			}
		}
		else
		{
			// рисуем, что нажать нельзя...
			RECT SrcRest;
			SetRect(&SrcRest, 0+148, 0+46+52*2, 228-15, 294-202+52*2);
			vw_Draw(567+148,97+46+52*2,&SrcRest, vw_FindTextureByName("DATA\\game3.bmp"), true);
		}

		// кнопка крыша...
		if (StartPanelPos != vw_FindTextureByName("DATA\\BUILDER\\3_01_50\\35.bmp")->Num)
		{
			SetRect(&MDetect, 716,144+52+52+52,776,185+52+52+52);
			if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
			SetRect(&DrawOFF, 0, 0, 0, 0);
			SetRect(&DrawON, 381,603+41+41+41-600,416,637+41+41+41-600);
			// только если ничего уже не тянем...
			if (GameCursor.Current!=3)
			{
				if (vw_OnRect(&MDetect)) GameCursor.Current=1;
				if (vw_Button2D(729,147+52+52+52, &MDetect, &DrawON, &DrawOFF, "DATA\\game2.bmp",true))
				{
					if (Setup.SoundSw) Audio_PlaySound(1);
					StartPanelPos = vw_FindTextureByName("DATA\\BUILDER\\3_01_50\\35.bmp")->Num;
					EndPanelPos = vw_FindTextureByName("DATA\\BUILDER\\4_04\\b-05.bmp")->Num;
					SetPanelPos = StartPanelPos+1;
					// корректировка SetPanelPos
					int stop = SetPanelPos;// если всего один элемент...
					bool rot=false;
					while (!CheckList(SetPanelPos))
					{
						SetPanelPos --;
						if (SetPanelPos<StartPanelPos) {SetPanelPos = EndPanelPos;rot=true;}
						if (rot && stop == SetPanelPos) break;
					}
				}
			}
		}
		else
		{
			// рисуем, что нажать нельзя...
			RECT SrcRest;
			SetRect(&SrcRest, 0+148, 0+46+52*3, 228-15, 294-202+52*3);
			vw_Draw(567+148,97+46+52*3,&SrcRest, vw_FindTextureByName("DATA\\game3.bmp"), true);
		}
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// установка "части дома" для jig-saw - прорисовка выбора элемента...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Setup.Type == 3)
	{
		vw_DrawRect(578,144,163,602-600,280,804-600,"DATA\\game2.bmp");
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// показ элементов для выбора...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (!GameWin)
	if (Setup.Type == 0 || Setup.Type == 1 || Setup.Type == 3)
	{
		int St=SetPanelPos-1;
		int En=SetPanelPos+1;
		if (St<StartPanelPos) St = EndPanelPos;
		if (En>EndPanelPos) En = StartPanelPos;

		SetRect(&SrcRest, 0, 0, 64, 64);

		if (Setup.Type == 1 || Setup.Type == 3)
		if (SetPanelPos != 0 && CheckList(SetPanelPos))
			vw_Draw(602,212,&SrcRest, vw_FindTextureByNum(SetPanelPos), false);

		if (Setup.Type == 0)
		if (SetPanelPos != 0)
			vw_Draw(602,212,&SrcRest, vw_FindTextureByNum(SetPanelPos), false);

		// для жигсов - свое
		if (Setup.Type == 3)
		if (!CheckList(SetPanelPos))
			DrawManualText(592 , 232, "EMPTY", 0, 0);

		// для билдера
		if (Setup.Type == 1)
		if (!CheckList(SetPanelPos))
			DrawManualText(592 , 232, "EMPTY", 0, 0);
	}




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// вывод счет времени...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (!GameWin) GameTime = SDL_GetTicks() - GameTimeInit;

	int TimeTEMP = (int)(GameTime/1000.0f);
	while (TimeTEMP>999)
	{
		TimeTEMP -= 1000;
	}
	int tmp100=(int)(TimeTEMP/100);
	int tmp10=(int)(TimeTEMP/10 - tmp100*10);
	int tmp1=(int)(TimeTEMP - tmp10*10 - tmp100*100);
	// сотни
	vw_DrawRect(688,50, 3+69*tmp100, 601, 24+(tmp100*69), 601+28,"DATA\\game.jpg");
	// десятки
	vw_DrawRect(688+21,50, 24+69*tmp10, 601, 45+(tmp10*69), 601+28,"DATA\\game.jpg");
	// еденицы
	vw_DrawRect(688+42,50, 45+69*tmp1, 601, 66+(tmp1*69), 601+28,"DATA\\game.jpg");






	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// если в панеле выбора один или ноль эл-тов - не даем стрелки
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	bool OnlyOne = false;
	bool Zerro = false;
	if (Setup.Type == 1 || Setup.Type == 3)
	{
		// взять от StartPanelPos до EndPanelPos
		// и проверить, сколько типов не нарисовано...
		int one_count = 0;
		for (int i=StartPanelPos; i<EndPanelPos; i++)
		{
			if (CheckList(i)) one_count++;
		}
		if (one_count==1) OnlyOne = true;

		// подсчет, все вытянули или нет...
		if (!CheckList(SetPanelPos)) Zerro = true;

		if (OnlyOne || Zerro)
		{
			// рисуем, что нажать нельзя...
			RECT SrcRest;
			SetRect(&SrcRest, 0, 0+40, 228-100, 294-200);
			vw_Draw(566,97+40,&SrcRest, vw_FindTextureByName("DATA\\game3.bmp"), true);

			SetRect(&SrcRest, 0, 0+200, 228-100, 294-40);
			vw_Draw(566,97+200,&SrcRest, vw_FindTextureByName("DATA\\game3.bmp"), true);
		}
	}





	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// показываеть стрелки и выбор всегда, кроме пары...
	// и если нужно рисовать, и если не тянем ничего...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Setup.Type != 2 && !OnlyOne && GameCursor.Current!=3 && !Zerro)
	{
		// стрелка вверх...
		SetRect(&MDetect, 580, 144, 686, 185);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		SetRect(&DrawOFF, 0, 0, 0, 0);
		SetRect(&DrawON, 2, 725-600, 51, 751-600);
		if (vw_OnRect(&MDetect)) GameCursor.Current=1;
		if (vw_Button2D(610, 151, &MDetect, &DrawON, &DrawOFF, "DATA\\game2.bmp", true))
		{
			// если билдер или жигсов...
			if (Setup.Type == 1 || Setup.Type == 3)
			{
				SetPanelPos --;

				int stop = SetPanelPos;// если всего один элемент...
				bool rot=false;
				while (!CheckList(SetPanelPos))
				{
					SetPanelPos --;
					if (SetPanelPos<StartPanelPos) {SetPanelPos = EndPanelPos;rot=true;}
					if (rot && stop == SetPanelPos) break;
				}
			}

			// мозайка
			if (Setup.Type == 0)
			{
				SetPanelPos --;
				if (SetPanelPos<StartPanelPos) {SetPanelPos = EndPanelPos;}
			}
		}


		// стрелка вниз...
		SetRect(&MDetect, 580, 301, 686, 342);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		SetRect(&DrawOFF, 0, 0, 0, 0);
		SetRect(&DrawON, 2, 755-600, 51, 782-600);
		if (vw_OnRect(&MDetect)) GameCursor.Current=1;
		if (vw_Button2D(611, 307, &MDetect, &DrawON, &DrawOFF, "DATA\\game2.bmp", true))
		{
			// если билдер или жигсов...
			if (Setup.Type == 1 || Setup.Type == 3)
			{
				SetPanelPos ++;

				int stop = SetPanelPos;// если всего один элемент...
				bool rot=false;
				while (!CheckList(SetPanelPos))
				{
					SetPanelPos ++;
					if (SetPanelPos>EndPanelPos) {SetPanelPos = StartPanelPos;rot=true;}
					if (rot && stop == SetPanelPos) break;
				}
			}

			// мозайка
			if (Setup.Type == 0)
			{
				SetPanelPos ++;
				if (SetPanelPos>EndPanelPos) {SetPanelPos = StartPanelPos;}
			}
		}
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// проверка на попадание в рекорды...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (GameWin && !TopScCheck && TopScCheckStop<0)
	{
		TopScCheck = true;// уже проверили в этой игре...

		// звук - выиграли...
		if (Setup.SoundSw)
			Audio_PlaySound(3);

		// проверка для каждой игры и каждого уровня сложности...
		if (Setup.Type == 0)
		{
			if (Setup.Difficult == 0)	SetTopScores(0);
			if (Setup.Difficult == 1)	SetTopScores(1);
			if (Setup.Difficult == 2)	SetTopScores(2);
			if (Setup.Difficult == 3)	SetTopScores(3);
			if (Setup.Difficult == 4)	SetTopScores(4);
		}
		if (Setup.Type == 1)
		{
			if (Setup.Difficult == 0)	SetTopScores(5);
			if (Setup.Difficult == 1)	SetTopScores(6);
			if (Setup.Difficult == 2)	SetTopScores(7);
			if (Setup.Difficult == 3)	SetTopScores(8);
			if (Setup.Difficult == 4)	SetTopScores(9);
		}
		if (Setup.Type == 2)
		{
			if (Setup.Difficult == 0)	SetTopScores(10);
			if (Setup.Difficult == 1)	SetTopScores(11);
			if (Setup.Difficult == 2)	SetTopScores(12);
		}
		if (Setup.Type == 3)
		{
			if (Setup.Difficult == 0)	SetTopScores(13);
			if (Setup.Difficult == 1)	SetTopScores(14);
			if (Setup.Difficult == 2)	SetTopScores(15);
		}
	}
	if (GameWin && !TopScCheck) TopScCheckStop--;



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// высокая сложность, если "промазали" - нужно вывести звук и сбросить все на ноль...
	// показываем ошибку пол секунды, потом сброс...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if ((Setup.Type==0 && Setup.Difficult > 3) ||
		(Setup.Type==1 && Setup.Difficult > 3) ||
		(Setup.Type==3 && Setup.Difficult == 2))
	{

		if (!ErrorShow)
		{
			for (int i=0; i<8; i++)
			for (int j=0; j<8; j++)
			{
				if (SetFieldData[i][j] != 0)
				if (SetFieldData[i][j] != FieldData[i][j])
				{
					ErrorShow = true;
					ErrorShowX = i;
					ErrorShowY = j;
					ErrorShowTime = SDL_GetTicks();
					// звук...
					if (Setup.SoundSw)
						Audio_PlaySound(2);
				}
			}
		}

		if (ErrorShow)
		{
			// задержка с прорисовкой ошибки...
			if (ErrorShowTime+500 > SDL_GetTicks())
			{
				vw_Draw(44+ErrorShowX*64,44+ErrorShowY*64,&SrcRest, vw_FindTextureByName("DATA\\error2.bmp"), true);
				vw_Draw(44+ErrorShowX*64,44+ErrorShowY*64,&SrcRest, vw_FindTextureByName("DATA\\error.bmp"), true);
			}
			else
			{
				ErrorShow = false;

				// сброс...
				for (int i=0; i<8; i++)
				for (int j=0; j<8; j++)
				{
					SetFieldData[i][j]=0;
				}
			}
		}
	}








	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка mist...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 590, 401, 766, 442);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);

	// если не нужно выводить - делаем пустое место...
	if ((Setup.Type==2) ||
		(Setup.Type==0 && Setup.Difficult > 2) ||
		(Setup.Type==1 && Setup.Difficult > 2) ||
		(Setup.Type==3 && Setup.Difficult >= 1))
	{
		vw_DrawRect(588,391, 0, 212, 182, 270,"DATA\\game2.bmp");
	}
	else
		if (!GameWin)
		// работает только если ничего не тянем...
		if (GameCursor.Current!=3)
		if (vw_OnRect(&MDetect))
		{
			GameCursor.Current=1;
			vw_DrawRect(599,408,1, 608-600, 159, 634-600,"DATA\\game2.bmp");

			for (int i=0; i<8; i++)
			for (int j=0; j<8; j++)
			{
				if (SetFieldData[i][j] != FieldData[i][j] && SetFieldData[i][j] != 0)
				{
					vw_Draw(44+i*64,44+j*64,&SrcRest, vw_FindTextureByName("DATA\\error2.bmp"), true);
					vw_Draw(44+i*64,44+j*64,&SrcRest, vw_FindTextureByName("DATA\\error.bmp"), true);
				}
			}
		}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка reset...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// работает только если ничего не тянем...
	if (GameCursor.Current!=3)
	{
		SetRect(&MDetect, 590, 458, 766, 499);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		SetRect(&DrawOFF, 0, 0, 0, 0);
		SetRect(&DrawON, 7, 647-600, 151, 677-600);
		if (vw_OnRect(&MDetect)) GameCursor.Current=1;
		if (vw_Button2D(605, 406+57, &MDetect, &DrawON, &DrawOFF, "DATA\\game2.bmp"))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			if (Setup.Type == 3) Setup.UseUserFileForJigSaw = false;
			ComBuffer = GAME_START;
		}
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка меню...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// работает только если ничего не тянем...
	if (GameCursor.Current!=3)
	{

		SetRect(&MDetect, 590, 458+57, 766, 499+57);
		if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
		SetRect(&DrawOFF, 0, 0, 0, 0);
		SetRect(&DrawON, 5, 86, 156, 121);
		if (vw_OnRect(&MDetect)) GameCursor.Current=1;
		if (vw_Button2D(603, 518, &MDetect, &DrawON, &DrawOFF, "DATA\\game2.bmp"))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			ComBuffer = MAIN_MENU;
		}
	}






}
