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

// считаем, сколько нужно загрузить шт и кб
int TotalCount;
int TotalKB;
// счетчик, сколько загрузили уже в кбайтах
int CerrentKB;







//------------------------------------------------------------------------------------
// процедура прорисовки процента загрузки данных
//------------------------------------------------------------------------------------
void DrawLoading()
{

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// рисуем проценты загрузки
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	vw_BeginRendering();
	vw_Start2DMode(-1,1);

		RECT SrcRest;
		RECT DstRest;
		SetRect(&SrcRest, 0,0,800,600);
		vw_Draw(0,0,&SrcRest, vw_FindTextureByName("DATA\\loading.jpg"), false);

		if (CerrentKB>=0)
		{
			SetRect(&SrcRest, 11,10,33,31);
			SetRect(&DstRest, 330, 469, 330+33-11, 469+31-10);
			vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA\\load.tga"), true, 0.99f);
		}
		if (CerrentKB>=(TotalKB/10))
		{
			SetRect(&SrcRest, 39,9,62,33);
			SetRect(&DstRest, 346, 458, 346+62-39, 458+33-9);
			vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA\\load.tga"), true, 0.99f);
		}
		if (CerrentKB>=(TotalKB/10)*2)
		{
			SetRect(&SrcRest, 66,8,92,34);
			SetRect(&DstRest, 363, 450, 363+92-66, 450+34-8);
			vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA\\load.tga"), true, 0.99f);
		}
		if (CerrentKB>=(TotalKB/10)*3)
		{
			SetRect(&SrcRest, 103,7,130,34);
			SetRect(&DstRest, 384, 446, 384+130-103, 446+34-7);
			vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA\\load.tga"), true, 0.99f);
		}
		if (CerrentKB>=(TotalKB/10)*4)
		{
			SetRect(&SrcRest, 140,6,169,36);
			SetRect(&DstRest, 407, 448, 407+169-140, 448+36-6);
			vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA\\load.tga"), true, 0.99f);
		}
		if (CerrentKB>=(TotalKB/10)*5)
		{
			SetRect(&SrcRest, 180,6,210,36);
			SetRect(&DstRest, 431, 457, 431+210-180, 457+36-6);
			vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA\\load.tga"), true, 0.99f);
		}
		if (CerrentKB>=(TotalKB/10)*6)
		{
			SetRect(&SrcRest, 6,60,38,92);
			SetRect(&DstRest, 452, 470, 452+38-6, 470+92-60);
			vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA\\load.tga"), true, 0.99f);
		}
		if (CerrentKB>=(TotalKB/10)*7)
		{
			SetRect(&SrcRest,51,59,85,94);
			SetRect(&DstRest, 469, 489, 469+85-51, 489+94-59);
			vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA\\load.tga"), true, 0.99f);
		}
		if (CerrentKB>=(TotalKB/10)*8)
		{
			SetRect(&SrcRest,106,58,142,94);
			SetRect(&DstRest, 481, 514, 481+142-106, 514+94-58);
			vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA\\load.tga"), true, 0.99f);
		}
		if (CerrentKB>=(TotalKB/10)*9)
		{
			SetRect(&SrcRest,160,56,200,97);
			SetRect(&DstRest, 486, 542, 486+200-160, 542+97-56);
			vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByName("DATA\\load.tga"), true, 0.99f);
		}

	vw_End2DMode();
	vw_EndRendering();


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// даем управление на окно...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SDL_Event event;
	while ( SDL_PollEvent(&event) )
	{
		switch (event.type)
		{
			case SDL_QUIT:
				Quit = true;
				break;
			default:
				break;
		}
	}
	SDL_Delay(1);
}








//------------------------------------------------------------------------------------
// загрузка данных
//------------------------------------------------------------------------------------
void LoadAll()
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// структура для загрузки
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	struct memLoad
	{
		// имя файла
		char	FileName[MAX_PATH];
		// тип файла (1-текстура, 2 - звук, 3 - музыка)
		int		FileType;
		// приоритетная загрузка (загружать сразу... и не считать этот файл)
		bool Priority;
		// размер файла (примерно)
		int		Size;
		// альфа канал, если нужно
		bool	Alpha;
		// цвет альфа канала
		BYTE Red, Green, Blue;
		// режим создания альфа канала
		int		AlphaMode;

		int		LoadAs;

	};



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кол-во текстур в списке (1 = одна текстура)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	const int ListCountAll = 34;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// список файлов для загрузки
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	memLoad ListLoad[ListCountAll]=
	{{"DATA\\loading.jpg",		1, true,  113,	false,	255,255,255, TX_ALPHA_EQUAL, JPG_FILE},
	{"DATA\\load.tga",			1, true,  131,	true,	255,255,255, TX_ALPHA_EQUAL, TGA_FILE},
	{"DATA\\cur.tga",			1, false, 6,	true,	255,255,255, TX_ALPHA_EQUAL, TGA_FILE},
	{"DATA\\cur1.tga",			1, false, 51,	true,	255,255,255, TX_ALPHA_EQUAL, TGA_FILE},
	{"DATA\\cur2.tga",			1, false, 51,	true,	255,255,255, TX_ALPHA_EQUAL, TGA_FILE},
	{"DATA\\cur3.tga",			1, false, 6,	true,	255,255,255, TX_ALPHA_EQUAL, TGA_FILE},
	{"DATA\\start.jpg",			1, false, 81,	false,	255,255,255, TX_ALPHA_EQUAL, JPG_FILE},
	{"DATA\\start2.jpg",		1, false, 23,	false,	255,255,255, TX_ALPHA_EQUAL, JPG_FILE},
	{"DATA\\start3.jpg",		1, false, 8,	false,	255,255,255, TX_ALPHA_EQUAL, JPG_FILE},
	{"DATA\\mainmenu.jpg",		1, false, 247,	false,	255,255,255, TX_ALPHA_EQUAL, JPG_FILE},
	{"DATA\\FONT\\text.tga",	1, false, 262,	true,	255,255,255, TX_ALPHA_EQUAL, TGA_FILE},
	{"DATA\\error3.bmp",		1, false, 5,	true,	255,255,255, TX_ALPHA_EQUAL, BMP_FILE},
	{"DATA\\error2.bmp",		1, false, 5,	true,	0,0,0, TX_ALPHA_EQUAL, BMP_FILE},
	{"DATA\\PAIR\\0.bmp",		1, false, 12,	false,	255,255,255, TX_ALPHA_EQUAL, BMP_FILE},
	{"DATA\\BUILDER\\0.bmp",	1, false, 12,	true,	255,255,255, TX_ALPHA_EQUAL, BMP_FILE},
	{"DATA\\LoadingPanel.bmp",	1, false, 87,	true,	255,255,255, TX_ALPHA_EQUAL, BMP_FILE},
	{"DATA\\error.bmp",			1, false, 12,	true,	255,255,255, TX_ALPHA_EQUAL, BMP_FILE},
	{"DATA\\drop.bmp",			1, false, 12,	true,	255,255,255, TX_ALPHA_EQUAL, BMP_FILE},
	{"DATA\\box.jpg",			1, false, 16,	false,	0,0,0, TX_ALPHA_EQUAL, JPG_FILE},
	{"DATA\\game.jpg",			1, false, 78,	false,	0,0,0, TX_ALPHA_EQUAL, JPG_FILE},
	{"DATA\\game2.bmp",			1, false, 575,	false,	0,0,0, TX_ALPHA_EQUAL, BMP_FILE},
	{"DATA\\game3.bmp",			1, false, 200,	true,	0,0,0, TX_ALPHA_EQUAL, BMP_FILE},
	{"DATA\\main_game.bmp",		1, false, 55,	true,	0,0,0, TX_ALPHA_EQUAL, BMP_FILE},
	{"DATA\\pr_b.bmp",			1, false, 50,	false,	0,0,0, TX_ALPHA_EQUAL, BMP_FILE},
	{"DATA\\pr_j.bmp",			1, false, 50,	false,	0,0,0, TX_ALPHA_EQUAL, BMP_FILE},
	{"DATA\\pr_m.bmp",			1, false, 50,	false,	0,0,0, TX_ALPHA_EQUAL, BMP_FILE},
	{"DATA\\pr_p.bmp",			1, false, 50,	false,	0,0,0, TX_ALPHA_EQUAL, BMP_FILE},
	{"DATA\\setup2.bmp",		1, false, 101,	false,	255,255,255, TX_ALPHA_EQUAL, BMP_FILE},
	{"DATA\\options2.bmp",		1, false, 90,	false,	255,255,255, TX_ALPHA_EQUAL, BMP_FILE},
	{"DATA\\setup_off.bmp",		1, false, 4,	true,	255,255,255, TX_ALPHA_EQUAL, BMP_FILE},
	{"DATA\\options.jpg",		1, false, 160,	false,	255,255,255, TX_ALPHA_EQUAL, JPG_FILE},
	{"DATA\\setup.jpg",			1, false, 164,	false,	255,255,255, TX_ALPHA_EQUAL, JPG_FILE},
	{"DATA\\topscores.jpg",		1, false, 106,	false,	255,255,255, TX_ALPHA_EQUAL, JPG_FILE},
	{"DATA\\credits.jpg",		1, false, 220,	false,	255,255,255, TX_ALPHA_EQUAL, JPG_FILE},
	};// проверь кол-во и поставь в ListCount!

	// если нужно - грузим все и сразу
	int ListCount = ListCountAll;



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// считаем, сколько нужно загрузить шт и кб
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	TotalCount = 0;
	TotalKB = 0;
	for (int i=0; i<ListCount; i++)
	{
		if (ListLoad[i].FileType == 1)
		{
			TotalCount++;
			TotalKB += ListLoad[i].Size;
		}
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// загружаем
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	CerrentKB = 0;
	for (int i=0; i<ListCount; i++)
	{
		// текстура
		if (ListLoad[i].FileType == 1)
		{
			CerrentKB += ListLoad[i].Size;
			// установки параметров
			vw_SetTextureAlpha(ListLoad[i].Red, ListLoad[i].Green, ListLoad[i].Blue);
			vw_SetTextureProp(RI_TEXTURE_NONE, RI_CLAMP, ListLoad[i].Alpha, ListLoad[i].AlphaMode, false);
			eTexture *T=vw_LoadTexture(ListLoad[i].FileName, ListLoad[i].LoadAs);
		}


		// подсчет когда и что рисовать...
		// если не приоритетная, значит уже можем рисовать
		if (!ListLoad[i].Priority)	DrawLoading();
	}




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// дорабатываем меню prestart ... вклейка мозаики
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Setup.UseUserMosaicAddon)
	{
		vw_CloseVFS();
		if (0 != vw_OpenVFS(Setup.UserMosaicAddon, "1"))
		{
			vw_OpenVFS(VFSFileNamePath, "1");
			Setup.UseUserMosaicAddon = false;
			fprintf(stderr, "--1\n");
		}

		vw_SetTextureProp(RI_TEXTURE_NONE, RI_CLAMP, false);

		vw_LoadTexture("DATA\\MOSAIC\\1_1.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\1_2.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\1_7.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\1_8.bmp", BMP_FILE);

		RECT SrcRect;
		SetRect(&SrcRect, 0, 0, 64, 64);
		vw_AddToTexture("DATA\\pr_m.bmp",
			"DATA\\MOSAIC\\1_1.bmp", 0, 0, &SrcRect);
		vw_AddToTexture("DATA\\pr_m.bmp",
			"DATA\\MOSAIC\\1_2.bmp", 64, 0, &SrcRect);
		vw_AddToTexture("DATA\\pr_m.bmp",
			"DATA\\MOSAIC\\1_8.bmp", 0, 64, &SrcRect);
		vw_AddToTexture("DATA\\pr_m.bmp",
			"DATA\\MOSAIC\\1_7.bmp", 64, 64, &SrcRect);

		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\1_1.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\1_2.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\1_7.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\1_8.bmp"));


		if (Setup.UseUserMosaicAddon)
		{
			vw_CloseVFS();
			vw_OpenVFS(VFSFileNamePath, "1");
		}
	}





	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// дорабатываем меню prestart ... вклейка билдера...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Setup.UseUserBuilderAddon)
	{
		vw_CloseVFS();
		if (0 != vw_OpenVFS(Setup.UserBuilderAddon, "1"))
		{
			vw_OpenVFS(VFSFileNamePath, "1");
			Setup.UseUserBuilderAddon = false;
		}

		vw_SetTextureProp(RI_TEXTURE_NONE, RI_CLAMP, false);

		vw_LoadTexture("DATA\\BUILDER\\1_03\\17.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_05_50\\a-06.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\68.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\2_05_50\\a-07.bmp", BMP_FILE);

		RECT SrcRect;
		SetRect(&SrcRect, 0, 0, 64, 64);
		vw_AddToTexture("DATA\\pr_b.bmp",
			"DATA\\BUILDER\\12_03\\68.bmp", 0, 0, &SrcRect);
		vw_AddToTexture("DATA\\pr_b.bmp",
			"DATA\\BUILDER\\2_05_50\\a-07.bmp", 64, 0, &SrcRect);
		vw_AddToTexture("DATA\\pr_b.bmp",
			"DATA\\BUILDER\\1_03\\17.bmp", 0, 64, &SrcRect);
		vw_AddToTexture("DATA\\pr_b.bmp",
			"DATA\\BUILDER\\1_05_50\\a-06.bmp", 64, 64, &SrcRect);

		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_03\\17.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_05_50\\a-06.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\68.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\2_05_50\\a-07.bmp"));

		if (Setup.UseUserBuilderAddon)
		{
			vw_CloseVFS();
			vw_OpenVFS(VFSFileNamePath, "1");
		}
	}




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// дорабатываем меню prestart ... вклейка the pair...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Setup.UseUserThePairAddon)
	{
		vw_CloseVFS();
		if (0 != vw_OpenVFS(Setup.UserThePairAddon, "1"))
		{
			vw_OpenVFS(VFSFileNamePath, "1");
			Setup.UseUserThePairAddon = false;
		}

		vw_SetTextureProp(RI_TEXTURE_NONE, RI_CLAMP, false);

		vw_LoadTexture("DATA\\PAIR\\toys-067.bmp", BMP_FILE);

		RECT SrcRect;
		SetRect(&SrcRect, 0, 0, 64, 64);

		vw_AddToTexture("DATA\\pr_p.bmp",
			"DATA\\PAIR\\toys-067.bmp", 0, 0, &SrcRect);
		vw_AddToTexture("DATA\\pr_p.bmp",
			"DATA\\PAIR\\toys-067.bmp", 64, 64, &SrcRect);

		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-067.bmp"));


		if (Setup.UseUserThePairAddon)
		{
			vw_CloseVFS();
			vw_OpenVFS(VFSFileNamePath, "1");
		}
	}




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// дорабатываем меню prestart ... вклейка jig-saw...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Setup.UseUserJigSawAddon)
	{
		vw_CloseVFS();
		if (0 != vw_OpenVFS(Setup.UserJigSawAddon, "1"))
		{
			vw_OpenVFS(VFSFileNamePath, "1");
			Setup.UseUserJigSawAddon = false;
		}

		vw_SetTextureProp(RI_TEXTURE_NONE, RI_CLAMP, false);
		vw_LoadTexture("DATA\\JIGSAW\\pic12.jpg", JPG_FILE, 128, 128);
		RECT SrcRect;
		SetRect(&SrcRect, 0, 0, 128, 128);
		vw_AddToTexture("DATA\\pr_j.bmp",
			"DATA\\JIGSAW\\pic12.jpg", 0, 0, &SrcRect);
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\JIGSAW\\pic12.jpg"));

		if (Setup.UseUserJigSawAddon)
		{
			vw_CloseVFS();
			vw_OpenVFS(VFSFileNamePath, "1");
		}
	}




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// загружаем шрифты
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	vw_SetTextureAlpha(255,255,255);
	vw_SetTextureProp(RI_TEXTURE_NONE, RI_CLAMP, true, TX_ALPHA_EQUAL, false);
	GameFont = vw_CreateFont(JPG_FILE, "DATA\\FONT\\font.jpg", 16);
	Font2 = vw_CreateFont(JPG_FILE, "DATA\\FONT\\font2.jpg", 32);




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// убираем текстуру (освобожд. 3 метра...)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	vw_ReleaseTexture(vw_FindTextureByName("DATA\\loading.jpg"));
	vw_ReleaseTexture(vw_FindTextureByName("DATA\\load.tga"));

}
