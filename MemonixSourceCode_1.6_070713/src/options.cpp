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





//------------------------------------------------------------------------------------
// переменные... локальные
//------------------------------------------------------------------------------------

//защелки...для авто + или - Countdown
bool plus = false;
bool minus = false;
// float счетчик для правильного (плавного) счета Countdown
float fCountdown1;

int CountAddonReposMAF;
char AddonReposMAF[100][MAX_PATH];
int CountAddonReposBAF;
char AddonReposBAF[100][MAX_PATH];
int CountAddonReposPAF;
char AddonReposPAF[100][MAX_PATH];
int CountAddonReposJAF;
char AddonReposJAF[100][MAX_PATH];
int CountAddonRepos;






















void SetCountAddonRepos()
{
	CountAddonRepos = -2;

	switch (Setup.Type)
	{
		case 0:
			if (CountAddonReposMAF >0 )
			{
				if (Setup.UseUserMosaicAddon)
				{
					// нет в репозитории, но он установлен
					CountAddonRepos = -1;
					for (int i=0; i<CountAddonReposMAF;i++)
					{	// ищем, может он из репозитория
						if (!strcmp(Setup.UserMosaicAddon, AddonReposMAF[i]))
							CountAddonRepos = i;
					}
				}// начинать с None
				else CountAddonRepos = -2;
			}
			else // если ничего нет в репозитории, но есть аддон
				if (Setup.UseUserMosaicAddon) CountAddonRepos = -1;

			break;

		case 1:
			if (CountAddonReposBAF >0 )
			{
				if (Setup.UseUserBuilderAddon)
				{
					// нет в репозитории, но он установлен
					CountAddonRepos = -1;
					for (int i=0; i<CountAddonReposBAF;i++)
					{	// ищем, может он из репозитория
						if (!strcmp(Setup.UserBuilderAddon, AddonReposBAF[i]))
							CountAddonRepos = i;
					}
				}// начинать с None
				else CountAddonRepos = -2;
			}
			else // если ничего нет в репозитории, но есть аддон
				if (Setup.UseUserBuilderAddon) CountAddonRepos = -1;
			break;

		case 2:
			if (CountAddonReposPAF >0 )
			{
				if (Setup.UseUserThePairAddon)
				{
					// нет в репозитории, но он установлен
					CountAddonRepos = -1;
					for (int i=0; i<CountAddonReposPAF;i++)
					{	// ищем, может он из репозитория
						if (!strcmp(Setup.UserThePairAddon, AddonReposPAF[i]))
							CountAddonRepos = i;
					}
				}// начинать с None
				else CountAddonRepos = -2;
			}
			else // если ничего нет в репозитории, но есть аддон
				if (Setup.UseUserThePairAddon) CountAddonRepos = -1;
			break;

		case 3:
			if (CountAddonReposJAF >0 )
			{
				if (Setup.UseUserJigSawAddon)
				{
					// нет в репозитории, но он установлен
					CountAddonRepos = -1;
					for (int i=0; i<CountAddonReposJAF;i++)
					{	// ищем, может он из репозитория
						if (!strcmp(Setup.UserJigSawAddon, AddonReposJAF[i]))
							CountAddonRepos = i;
					}
				}// начинать с None
				else CountAddonRepos = -2;
			}
			else // если ничего нет в репозитории, но есть аддон
				if (Setup.UseUserJigSawAddon) CountAddonRepos = -1;
			break;
	}

}












//------------------------------------------------------------------------------------
// поиск всех аддонов в репозитории игры (в каталоге игры)...
//------------------------------------------------------------------------------------
#ifdef __unix
    #include <dirent.h>
    #include <errno.h>
    #include <stdio.h>
#endif // unix
#ifdef WIN32
	#include <io.h> // нужно для _findfirst/_findnext
#endif // WIN32


void SeekAddons()
{
#ifdef __unix
	// ищем аддоны MAF
	CountAddonReposMAF = 0;

	// проверяем, если аддон есть, но не в репозитории, его ставим первым
	if (Setup.UseUserMosaicAddon)
	if (strncmp(ProgrammDir, Setup.UserMosaicAddon, strlen(ProgrammDir)))
	{
		strcpy(AddonReposMAF[CountAddonReposMAF], Setup.UserMosaicAddon);
		CountAddonReposMAF++;
	}

    DIR *pdir1;
    struct dirent *pfile1;

    // открываем директорию игры
    if (pdir1 = opendir(ProgrammDir))
    {
        errno=0; /*reset before calling readdir*/

        while(pfile1=readdir(pdir1))
        {
  //printf("%s\n",pfile1->d_name);
            if (strcmp(pfile1->d_name,".") && strcmp(pfile1->d_name,".."))
            if (!strcmp(pfile1->d_name+strlen(pfile1->d_name)-3,"maf"))
            {
				strcpy(AddonReposMAF[CountAddonReposMAF], ProgrammDir);
				strcat(AddonReposMAF[CountAddonReposMAF], pfile1->d_name);
 				CountAddonReposMAF++;
            }
        }
        if (errno==0) closedir(pdir1);
    }




	// ищем аддоны BAF
	CountAddonReposBAF = 0;

	// проверяем, если аддон есть, но не в репозитории, его ставим первым
	if (Setup.UseUserBuilderAddon)
	if (strncmp(ProgrammDir, Setup.UserBuilderAddon, strlen(ProgrammDir)))
	{
		strcpy(AddonReposBAF[CountAddonReposBAF], Setup.UserBuilderAddon);
		CountAddonReposBAF++;
	}

    DIR *pdir2;
    struct dirent *pfile2;

    // открываем директорию игры
    if (pdir2 = opendir(ProgrammDir))
    {
        errno=0; /*reset before calling readdir*/

        while(pfile2=readdir(pdir2))
        {
           // printf("%s\n",pfile->d_name);
            if (strcmp(pfile2->d_name,".") && strcmp(pfile2->d_name,".."))
            if (!strcmp(pfile2->d_name+strlen(pfile2->d_name)-3,"baf"))
            {
				strcpy(AddonReposBAF[CountAddonReposBAF], ProgrammDir);
				strcat(AddonReposBAF[CountAddonReposBAF], pfile2->d_name);
				CountAddonReposBAF++;
            }
        }
        if (errno==0) closedir(pdir2);
    }




	// ищем аддоны PAF
	CountAddonReposPAF = 0;

	// проверяем, если аддон есть, но не в репозитории, его ставим первым
	if (Setup.UseUserThePairAddon)
	if (strncmp(ProgrammDir, Setup.UserThePairAddon, strlen(ProgrammDir)))
	{
		strcpy(AddonReposPAF[CountAddonReposPAF], Setup.UserThePairAddon);
		CountAddonReposPAF++;
	}

    DIR *pdir3;
    struct dirent *pfile3;

    // открываем директорию игры
    if (pdir3 = opendir(ProgrammDir))
    {
        errno=0; /*reset before calling readdir*/

        while(pfile3=readdir(pdir3))
        {
            //printf("%s\n",pfile->d_name);
            if (strcmp(pfile3->d_name,".") && strcmp(pfile3->d_name,".."))
            if (!strcmp(pfile3->d_name+strlen(pfile3->d_name)-3,"paf"))
            {
				strcpy(AddonReposPAF[CountAddonReposPAF], ProgrammDir);
				strcat(AddonReposPAF[CountAddonReposPAF], pfile3->d_name);
 				CountAddonReposPAF++;
            }
        }
        if (errno==0) closedir(pdir3);
    }





	// ищем аддоны JAF
	CountAddonReposJAF = 0;

	// проверяем, если аддон есть, но не в репозитории, его ставим первым
	if (Setup.UseUserJigSawAddon)
	if (strncmp(ProgrammDir, Setup.UserJigSawAddon, strlen(ProgrammDir)))
	{
		strcpy(AddonReposJAF[CountAddonReposJAF], Setup.UserJigSawAddon);
		CountAddonReposJAF++;
	}

    DIR *pdir4;
    struct dirent *pfile4;

    // открываем директорию игры
    if (pdir4 = opendir(ProgrammDir))
    {
        errno=0; /*reset before calling readdir*/

        while(pfile4=readdir(pdir4))
        {
            //printf("%s\n",pfile->d_name);
            if (strcmp(pfile4->d_name,".") && strcmp(pfile4->d_name,".."))
            if (!strcmp(pfile4->d_name+strlen(pfile4->d_name)-3,"jaf"))
            {
				strcpy(AddonReposJAF[CountAddonReposJAF], ProgrammDir);
				strcat(AddonReposJAF[CountAddonReposJAF], pfile4->d_name);
 				CountAddonReposJAF++;
            }
        }
        if (errno==0) closedir(pdir4);
    }


#endif // unix

#ifdef WIN32
	// ищем аддоны MAF
	CountAddonReposMAF = 0;
	for (int i=0; i<100; i++)
	{
		ZeroMemory(AddonReposMAF[i], MAX_PATH);
	}

	// проверяем, если аддон есть, но не в репозитории, его ставим первым
	if (Setup.UseUserMosaicAddon)
	if (strncmp(ProgrammDir, Setup.UserMosaicAddon, strlen(ProgrammDir)))
	{
		strcpy(AddonReposMAF[CountAddonReposMAF], Setup.UserMosaicAddon);
		CountAddonReposMAF++;
	}

	char pszReadPath[MAX_PATH];
	ZeroMemory(pszReadPath, sizeof(pszReadPath));
	strcpy(pszReadPath,ProgrammDir);
	strcat(pszReadPath,"\\*.maf");

	struct _finddata_t c_file;
	intptr_t h_file = _findfirst(pszReadPath, &c_file);

	if(h_file != -1L )
	{
		do{
			if ( !((c_file.attrib & _A_HIDDEN) == _A_HIDDEN) &&
			!((c_file.attrib & _A_SYSTEM) == _A_SYSTEM) &&
			strcmp(c_file.name,".") &&
			strcmp(c_file.name,"..") )
			{
				if (((c_file.attrib & _A_SUBDIR) != _A_SUBDIR))
				{
					strcpy(AddonReposMAF[CountAddonReposMAF], ProgrammDir);
					strcat(AddonReposMAF[CountAddonReposMAF], c_file.name);
					CountAddonReposMAF++;
				}
			}
		}while(_findnext(h_file, &c_file) != -1);
		_findclose( h_file );
	}





	// ищем аддоны BAF
	CountAddonReposBAF = 0;
	for (int i=0; i<100; i++)
	{
		ZeroMemory(AddonReposBAF[i], MAX_PATH);
	}

	// проверяем, если аддон есть, но не в репозитории, его ставим первым
	if (Setup.UseUserBuilderAddon)
	if (strncmp(ProgrammDir, Setup.UserBuilderAddon, strlen(ProgrammDir)))
	{
		strcpy(AddonReposBAF[CountAddonReposBAF], Setup.UserBuilderAddon);
		CountAddonReposBAF++;
	}

	ZeroMemory(pszReadPath, sizeof(pszReadPath));
	strcpy(pszReadPath,ProgrammDir);
	strcat(pszReadPath,"\\*.baf");

	h_file = _findfirst(pszReadPath, &c_file);

	if(h_file != -1L )
	{
		do{
			if ( !((c_file.attrib & _A_HIDDEN) == _A_HIDDEN) &&
			!((c_file.attrib & _A_SYSTEM) == _A_SYSTEM) &&
			strcmp(c_file.name,".") &&
			strcmp(c_file.name,"..") )
			{
				if (((c_file.attrib & _A_SUBDIR) != _A_SUBDIR))
				{
					strcpy(AddonReposBAF[CountAddonReposBAF], ProgrammDir);
					strcat(AddonReposBAF[CountAddonReposBAF], c_file.name);
					CountAddonReposBAF++;
				}
			}
		}while(_findnext(h_file, &c_file) != -1);
		_findclose( h_file );
	}



	// ищем аддоны PAF
	CountAddonReposPAF = 0;
	for (int i=0; i<100; i++)
	{
		ZeroMemory(AddonReposPAF[i], MAX_PATH);
	}

	// проверяем, если аддон есть, но не в репозитории, его ставим первым
	if (Setup.UseUserThePairAddon)
	if (strncmp(ProgrammDir, Setup.UserThePairAddon, strlen(ProgrammDir)))
	{
		strcpy(AddonReposPAF[CountAddonReposPAF], Setup.UserThePairAddon);
		CountAddonReposPAF++;
	}

	ZeroMemory(pszReadPath, sizeof(pszReadPath));
	strcpy(pszReadPath,ProgrammDir);
	strcat(pszReadPath,"\\*.paf");

	h_file = _findfirst(pszReadPath, &c_file);

	if(h_file != -1L )
	{
		do{
			if ( !((c_file.attrib & _A_HIDDEN) == _A_HIDDEN) &&
			!((c_file.attrib & _A_SYSTEM) == _A_SYSTEM) &&
			strcmp(c_file.name,".") &&
			strcmp(c_file.name,"..") )
			{
				if (((c_file.attrib & _A_SUBDIR) != _A_SUBDIR))
				{
					strcpy(AddonReposPAF[CountAddonReposPAF], ProgrammDir);
					strcat(AddonReposPAF[CountAddonReposPAF], c_file.name);
					CountAddonReposPAF++;
				}
			}
		}while(_findnext(h_file, &c_file) != -1);
		_findclose( h_file );
	}





	// ищем аддоны JAF
	CountAddonReposJAF = 0;
	for (int i=0; i<100; i++)
	{
		ZeroMemory(AddonReposJAF[i], MAX_PATH);
	}

	// проверяем, если аддон есть, но не в репозитории, его ставим первым
	if (Setup.UseUserJigSawAddon)
	if (strncmp(ProgrammDir, Setup.UserJigSawAddon, strlen(ProgrammDir)))
	{
		strcpy(AddonReposJAF[CountAddonReposJAF], Setup.UserJigSawAddon);
		CountAddonReposJAF++;
	}

	ZeroMemory(pszReadPath, sizeof(pszReadPath));
	strcpy(pszReadPath,ProgrammDir);
	strcat(pszReadPath,"\\*.jaf");

	h_file = _findfirst(pszReadPath, &c_file);

	if(h_file != -1L )
	{
		do{
			if ( !((c_file.attrib & _A_HIDDEN) == _A_HIDDEN) &&
			!((c_file.attrib & _A_SYSTEM) == _A_SYSTEM) &&
			strcmp(c_file.name,".") &&
			strcmp(c_file.name,"..") )
			{
				if (((c_file.attrib & _A_SUBDIR) != _A_SUBDIR))
				{
					strcpy(AddonReposJAF[CountAddonReposJAF], ProgrammDir);
					strcat(AddonReposJAF[CountAddonReposJAF], c_file.name);
					CountAddonReposJAF++;
				}
			}
		}while(_findnext(h_file, &c_file) != -1);
		_findclose( h_file );
	}



#endif // WIN32



	SetCountAddonRepos();
}









// если нужно - переделываем меню preset
void LoadMosaicPreset()
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// прорисовка надписи Loading...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	vw_SetClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	vw_BeginRendering();
	vw_Start2DMode(-1,1);
		RECT SrcRest;
		SetRect(&SrcRest, 0, 0, 226, 120);
		vw_Draw(287,236,&SrcRest, vw_FindTextureByName("DATA\\LoadingPanel.bmp"), false);
	vw_End2DMode();
	vw_EndRendering();

	vw_BeginRendering();
	vw_Start2DMode(-1,1);
		SetRect(&SrcRest, 0, 0, 226, 120);
		vw_Draw(287,236,&SrcRest, vw_FindTextureByName("DATA\\LoadingPanel.bmp"), false);
	vw_End2DMode();
	vw_EndRendering();


	// для задержки, чтобы рисовать не менее 0.5 секунды
	Uint32 gettick;
	gettick = SDL_GetTicks();


	if (Setup.UseUserMosaicAddon)
	{
		vw_CloseVFS();
		if (0 != vw_OpenVFS(Setup.UserMosaicAddon, "1"))
		{
			vw_OpenVFS(VFSFileNamePath, "1");
			Setup.UseUserMosaicAddon = false;
		}
	}

	vw_SetTextureProp(RI_TEXTURE_NONE, RI_CLAMP, false);


	if (vw_FindTextureByName("DATA\\MOSAIC\\1_1.bmp") != 0)
	{
		ReleaseGameDate(0);
		lastgame = -1;
	}

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


	// для задержки, чтобы рисовать не менее 0.5 секунды
	Uint32 gettick2 = SDL_GetTicks();
	if (gettick+500 > gettick2) SDL_Delay(gettick+500-gettick2);
}
// если нужно - переделываем меню preset
void LoadBuilderPreset()
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// прорисовка надписи Loading...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	vw_SetClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	vw_BeginRendering();
	vw_Start2DMode(-1,1);
		RECT SrcRest;
		SetRect(&SrcRest, 0, 0, 226, 120);
		vw_Draw(287,236,&SrcRest, vw_FindTextureByName("DATA\\LoadingPanel.bmp"), false);
	vw_End2DMode();
	vw_EndRendering();

	vw_BeginRendering();
	vw_Start2DMode(-1,1);
		SetRect(&SrcRest, 0, 0, 226, 120);
		vw_Draw(287,236,&SrcRest, vw_FindTextureByName("DATA\\LoadingPanel.bmp"), false);
	vw_End2DMode();
	vw_EndRendering();

	// для задержки, чтобы рисовать не менее 0.5 секунды
	Uint32 gettick;
	gettick = SDL_GetTicks();

	if (Setup.UseUserBuilderAddon)
	{
		vw_CloseVFS();
		if (0 != vw_OpenVFS(Setup.UserBuilderAddon, "1"))
		{
			vw_OpenVFS(VFSFileNamePath, "1");
			Setup.UseUserBuilderAddon = false;
		}
	}

	vw_SetTextureProp(RI_TEXTURE_NONE, RI_CLAMP, false);


	if (vw_FindTextureByName("DATA\\BUILDER\\1_03\\17.bmp") != 0)
	{
		ReleaseGameDate(1);
		lastgame = -1;
	}

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

	// для задержки, чтобы рисовать не менее 0.5 секунды
	Uint32 gettick2 = SDL_GetTicks();
	if (gettick+500 > gettick2) SDL_Delay(gettick+500-gettick2);
}
// если нужно - переделываем меню preset
void LoadThePairPreset()
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// прорисовка надписи Loading...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	vw_SetClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	vw_BeginRendering();
	vw_Start2DMode(-1,1);
		RECT SrcRest;
		SetRect(&SrcRest, 0, 0, 226, 120);
		vw_Draw(287,236,&SrcRest, vw_FindTextureByName("DATA\\LoadingPanel.bmp"), false);
	vw_End2DMode();
	vw_EndRendering();

	vw_BeginRendering();
	vw_Start2DMode(-1,1);
		SetRect(&SrcRest, 0, 0, 226, 120);
		vw_Draw(287,236,&SrcRest, vw_FindTextureByName("DATA\\LoadingPanel.bmp"), false);
	vw_End2DMode();
	vw_EndRendering();

	// для задержки, чтобы рисовать не менее 0.5 секунды
	Uint32 gettick;
	gettick = SDL_GetTicks();

	if (Setup.UseUserThePairAddon)
	{
		vw_CloseVFS();
		if (0 != vw_OpenVFS(Setup.UserThePairAddon, "1"))
		{
			vw_OpenVFS(VFSFileNamePath, "1");
			Setup.UseUserThePairAddon = false;
		}
	}

	vw_SetTextureProp(RI_TEXTURE_NONE, RI_CLAMP, false);


	if (vw_FindTextureByName("DATA\\PAIR\\toys-067.bmp") != 0)
	{
		ReleaseGameDate(2);
		lastgame = -1;
	}

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

	// для задержки, чтобы рисовать не менее 0.5 секунды
	Uint32 gettick2 = SDL_GetTicks();
	if (gettick+500 > gettick2) SDL_Delay(gettick+500-gettick2);
}
// если нужно - переделываем меню preset
void LoadJigSawPreset()
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// прорисовка надписи Loading...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	vw_SetClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	vw_BeginRendering();
	vw_Start2DMode(-1,1);
		RECT SrcRest;
		SetRect(&SrcRest, 0, 0, 226, 120);
		vw_Draw(287,236,&SrcRest, vw_FindTextureByName("DATA\\LoadingPanel.bmp"), false);
	vw_End2DMode();
	vw_EndRendering();

	vw_BeginRendering();
	vw_Start2DMode(-1,1);
		SetRect(&SrcRest, 0, 0, 226, 120);
		vw_Draw(287,236,&SrcRest, vw_FindTextureByName("DATA\\LoadingPanel.bmp"), false);
	vw_End2DMode();
	vw_EndRendering();

	// для задержки, чтобы рисовать не менее 0.5 секунды
	Uint32 gettick;
	gettick = SDL_GetTicks();

	if (Setup.UseUserJigSawAddon)
	{
		vw_CloseVFS();
		if (0 != vw_OpenVFS(Setup.UserJigSawAddon, "1"))
		{
			vw_OpenVFS(VFSFileNamePath, "1");
			Setup.UseUserJigSawAddon = false;
		}
	}

	vw_SetTextureProp(RI_TEXTURE_NONE, RI_CLAMP, false);


	if (vw_FindTextureByName("DATA\\JIGSAW\\pic12.jpg") != 0)
	{
		ReleaseGameDate(3);
		lastgame = -1;
	}

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

	// для задержки, чтобы рисовать не менее 0.5 секунды
	Uint32 gettick2 = SDL_GetTicks();
	if (gettick+500 > gettick2) SDL_Delay(gettick+500-gettick2);
}








//------------------------------------------------------------------------------------
// Options
//------------------------------------------------------------------------------------
void Options()
{

	RECT MDetect;
	RECT DrawON;
	RECT DrawOFF;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// прорисовка подложки меню...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	vw_DrawRect(0,0,0,0,800,600,"DATA\\options.jpg");


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// прорисовка превью для каждой игры...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	vw_DrawRect(45,56,0,0,128,128,"DATA\\pr_m.bmp");
	vw_DrawRect(239,56,0,0,128,128,"DATA\\pr_b.bmp");
	vw_DrawRect(433,56,0,0,128,128,"DATA\\pr_p.bmp");
	vw_DrawRect(627,56,0,0,128,128,"DATA\\pr_j.bmp");




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка back...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 703, 524, 784, 565);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 1, 602, 80, 641);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(704, 525, &MDetect, &DrawON, &DrawOFF, "DATA\\options.jpg"))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		ComBuffer = GAME_START;
	}










	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка download...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 15, 524, 191, 565);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 247, 602, 421, 641);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(16, 525, &MDetect, &DrawON, &DrawOFF, "DATA\\options.jpg"))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		SDL_WM_IconifyWindow();
		vw_OpenBrouser("http://www.viewizard.com/memonix/addons.php");
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// выводим надпись что делать, чтобы добавить аддон
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	DrawManualText(210, 522, "Copy addons files into the game folder:", 0, 0);
	DrawManualText(210, 544, ProgrammDir, 0, 450);







	// mosaic
	SetRect(&MDetect, 45, 56, 172, 183);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 0, 0, 140, 140);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(45-6, 56-6, &MDetect, &DrawON, &DrawOFF, "DATA\\main_game.bmp", true, true))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		if (Setup.Type != 0 && lastgame != -1)
		{
			//сбрасываем, чтобы перегрузить текстуры...
			lastgame=-1;
			ReleaseGameDate(Setup.Type);
		}
		Setup.Type = 0;
		SetCountAddonRepos();
	}
	if (Setup.Type == 0)
		vw_DrawRect(45-6,56-6,0,0,140,140,"DATA\\main_game.bmp", true);


	// builder
	SetRect(&MDetect, 239, 56, 366, 183);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 0, 0, 140, 140);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(239-6, 56-6, &MDetect, &DrawON, &DrawOFF, "DATA\\main_game.bmp", true, true))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		if (Setup.Type != 1 && lastgame != -1)
		{
			//сбрасываем, чтобы перегрузить текстуры...
			lastgame=-1;
			ReleaseGameDate(Setup.Type);
		}
		Setup.Type = 1;
		SetCountAddonRepos();
	}
	if (Setup.Type == 1)
		vw_DrawRect(239-6, 56-6,0,0,140,140,"DATA\\main_game.bmp", true);



	// the pair
	SetRect(&MDetect, 433, 56, 560, 183);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 0, 0, 140, 140);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(433-6, 56-6, &MDetect, &DrawON, &DrawOFF, "DATA\\main_game.bmp", true, true))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		if (Setup.Type != 2 && lastgame != -1)
		{
			//сбрасываем, чтобы перегрузить текстуры...
			lastgame=-1;
			ReleaseGameDate(Setup.Type);
		}
		Setup.Type = 2;
		SetCountAddonRepos();
	}
	if (Setup.Type == 2)
		vw_DrawRect(433-6, 56-6,0,0,140,140,"DATA\\main_game.bmp", true);



	// jig-saw
	SetRect(&MDetect, 627, 56, 754, 183);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 0, 0, 140, 140);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(627-6, 56-6, &MDetect, &DrawON, &DrawOFF, "DATA\\main_game.bmp", true, true))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		if (Setup.Type != 3 && lastgame != -1)
		{
			//сбрасываем, чтобы перегрузить текстуры...
			lastgame=-1;
			ReleaseGameDate(Setup.Type);
		}
		Setup.Type = 3;
		SetCountAddonRepos();
	}
	if (Setup.Type == 3)
		vw_DrawRect(627-6, 56-6,0,0,140,140,"DATA\\main_game.bmp", true);




	bool AddonsPresent = false;
	switch (Setup.Type)
	{
		case 0:
			if (CountAddonReposMAF > 0) AddonsPresent = true;
			if (Setup.UseUserMosaicAddon) AddonsPresent = true;
			break;
		case 1:
			if (CountAddonReposBAF > 0) AddonsPresent = true;
			if (Setup.UseUserBuilderAddon) AddonsPresent = true;
			break;
		case 2:
			if (CountAddonReposPAF > 0) AddonsPresent = true;
			if (Setup.UseUserThePairAddon) AddonsPresent = true;
			break;
		case 3:
			if (CountAddonReposJAF > 0) AddonsPresent = true;
			if (Setup.UseUserJigSawAddon) AddonsPresent = true;
			break;
	}



	// вывод имени аддона
	if (AddonsPresent)
	{
		if (CountAddonRepos != -2)
		{
			char* s = NULL;
			char bn[30];
			strcpy(bn," ");
			switch (Setup.Type)
			{
				case 0:
                    s = NULL;
                    s = strrchr(Setup.UserMosaicAddon,'\\');
					if (s == NULL) s = strrchr(Setup.UserMosaicAddon,'/');
					break;
				case 1:
                    s = NULL;
                    s = strrchr(Setup.UserBuilderAddon,'\\');
					if (s == NULL) s = strrchr(Setup.UserBuilderAddon,'/');
					break;
				case 2:
                    s = NULL;
                    s = strrchr(Setup.UserThePairAddon,'\\');
					if (s == NULL) s = strrchr(Setup.UserThePairAddon,'/');
					break;
				case 3:
                    s = NULL;
                    s = strrchr(Setup.UserJigSawAddon,'\\');
					if (s == NULL) s = strrchr(Setup.UserJigSawAddon,'/');
					break;
			}
			strcat(bn, s+1);
			strcat(bn, " ");
			DrawManualText(490, 464, bn, 200,200);
		}
		else DrawManualText(530, 464, "Not in use",0,0);
	}
	else DrawManualText(505, 464, "Not connected",0,0);






	// аддон, стрелка <
	SetRect(&MDetect, 450, 461, 481, 490);
	if (isDialogBoxDrawing() || !AddonsPresent) SetRect(&MDetect, 0, 0, 0, 0);
	if (!AddonsPresent) SetRect(&DrawON, 0, 0, 0, 0);
	if (vw_OnRect(&MDetect))
	{
		GameCursor.Current=1;
		vw_DrawRect(453,462,127,104,153,132,"DATA\\options2.bmp");

		if (vw_GetWindowLBMouse(true))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);


			switch (Setup.Type)
			{
				case 0:
					if (CountAddonReposMAF > 0)
					{
						if (CountAddonRepos == -2)
						{
							CountAddonRepos = CountAddonReposMAF-1;
							Setup.UseUserMosaicAddon = true;
							strcpy(Setup.UserMosaicAddon, AddonReposMAF[CountAddonRepos]);
						}
						else
							if (CountAddonRepos == -1)
							{
								CountAddonRepos = -2;
								Setup.UseUserMosaicAddon = false;
							}
							else
								if (CountAddonRepos == 0)
								{
									CountAddonRepos = -2;
									Setup.UseUserMosaicAddon = false;
								}
								else
									if (CountAddonRepos > 0)
									{
										CountAddonRepos --;
										Setup.UseUserMosaicAddon = true;
										strcpy(Setup.UserMosaicAddon, AddonReposMAF[CountAddonRepos]);
									}

						ComBuffer = 201;
					}
					break;

				case 1:
					if (CountAddonReposBAF > 0)
					{
						if (CountAddonRepos == -2)
						{
							CountAddonRepos = CountAddonReposBAF-1;
							Setup.UseUserBuilderAddon = true;
							strcpy(Setup.UserBuilderAddon, AddonReposBAF[CountAddonRepos]);
						}
						else
							if (CountAddonRepos == -1)
							{
								CountAddonRepos = -2;
								Setup.UseUserBuilderAddon = false;
							}
							else
								if (CountAddonRepos == 0)
								{
									CountAddonRepos = -2;
									Setup.UseUserBuilderAddon = false;
								}
								else
									if (CountAddonRepos > 0)
									{
										CountAddonRepos --;
										Setup.UseUserBuilderAddon = true;
										strcpy(Setup.UserBuilderAddon, AddonReposBAF[CountAddonRepos]);
									}

						ComBuffer = 202;
					}
					break;

				case 2:
					if (CountAddonReposPAF > 0)
					{
						if (CountAddonRepos == -2)
						{
							CountAddonRepos = CountAddonReposPAF-1;
							Setup.UseUserThePairAddon = true;
							strcpy(Setup.UserThePairAddon, AddonReposPAF[CountAddonRepos]);
						}
						else
							if (CountAddonRepos == -1)
							{
								CountAddonRepos = -2;
								Setup.UseUserThePairAddon = false;
							}
							else
								if (CountAddonRepos == 0)
								{
									CountAddonRepos = -2;
									Setup.UseUserThePairAddon = false;
								}
								else
									if (CountAddonRepos > 0)
									{
										CountAddonRepos --;
										Setup.UseUserThePairAddon = true;
										strcpy(Setup.UserThePairAddon, AddonReposPAF[CountAddonRepos]);
									}
						ComBuffer = 203;
					}
					break;

				case 3:
					if (CountAddonReposJAF > 0)
					{
						if (CountAddonRepos == -2)
						{
							CountAddonRepos = CountAddonReposJAF-1;
							Setup.UseUserJigSawAddon = true;
							strcpy(Setup.UserJigSawAddon, AddonReposJAF[CountAddonRepos]);
						}
						else
							if (CountAddonRepos == -1)
							{
								CountAddonRepos = -2;
								Setup.UseUserJigSawAddon = false;
							}
							else
								if (CountAddonRepos == 0)
								{
									CountAddonRepos = -2;
									Setup.UseUserJigSawAddon = false;
								}
								else
									if (CountAddonRepos > 0)
									{
										CountAddonRepos --;
										Setup.UseUserJigSawAddon = true;
										strcpy(Setup.UserJigSawAddon, AddonReposJAF[CountAddonRepos]);
									}

						ComBuffer = 204;
					}
					break;
			}
		}
	}

	// аддон, стрелка >
	SetRect(&MDetect, 702, 461, 733, 490);
	if (isDialogBoxDrawing() || !AddonsPresent) SetRect(&MDetect, 0, 0, 0, 0);
	if (vw_OnRect(&MDetect))
	{
		GameCursor.Current=1;
		vw_DrawRect(704,463,155,105,181,130,"DATA\\options2.bmp");

		if (vw_GetWindowLBMouse(true))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);

			switch (Setup.Type)
			{
				case 0:
					if (CountAddonReposMAF > 0)
					{
						if (CountAddonRepos == -2)
						{
							CountAddonRepos = 0;
							Setup.UseUserMosaicAddon = true;
							strcpy(Setup.UserMosaicAddon, AddonReposMAF[CountAddonRepos]);
						}
						else
							if (CountAddonRepos == CountAddonReposMAF-1)
							{
								CountAddonRepos = -2;
								Setup.UseUserMosaicAddon = false;
							}
							else
								if (CountAddonRepos >= -1)
								{
									CountAddonRepos ++;
									Setup.UseUserMosaicAddon = true;
									strcpy(Setup.UserMosaicAddon, AddonReposMAF[CountAddonRepos]);
								}

						ComBuffer = 201;
					}
					break;

				case 1:
					if (CountAddonReposBAF > 0)
					{
 						if (CountAddonRepos == -2)
						{
							CountAddonRepos = 0;
							Setup.UseUserBuilderAddon = true;
							strcpy(Setup.UserBuilderAddon, AddonReposBAF[CountAddonRepos]);
						}
						else
							if (CountAddonRepos == CountAddonReposBAF-1)
							{
								CountAddonRepos = -2;
								Setup.UseUserBuilderAddon = false;
							}
							else
								if (CountAddonRepos >= -1)
								{
									CountAddonRepos ++;
									Setup.UseUserBuilderAddon = true;
									strcpy(Setup.UserBuilderAddon, AddonReposBAF[CountAddonRepos]);
								}

						ComBuffer = 202;
					}
					break;

				case 2:
					if (CountAddonReposPAF > 0)
					{
						if (CountAddonRepos == -2)
						{
							CountAddonRepos = 0;
							Setup.UseUserThePairAddon = true;
							strcpy(Setup.UserThePairAddon, AddonReposPAF[CountAddonRepos]);
						}
						else
							if (CountAddonRepos == CountAddonReposPAF-1)
							{
								CountAddonRepos = -2;
								Setup.UseUserThePairAddon = false;
							}
							else
								if (CountAddonRepos >= -1)
								{
									CountAddonRepos ++;
									Setup.UseUserThePairAddon = true;
									strcpy(Setup.UserThePairAddon, AddonReposPAF[CountAddonRepos]);
								}

						ComBuffer = 203;
					}
					break;

				case 3:
					if (CountAddonReposJAF > 0)
					{
						if (CountAddonRepos == -2)
						{
							CountAddonRepos = 0;
							Setup.UseUserJigSawAddon = true;
							strcpy(Setup.UserJigSawAddon, AddonReposJAF[CountAddonRepos]);
						}
						else
							if (CountAddonRepos == CountAddonReposJAF-1)
							{
								CountAddonRepos = -2;
								Setup.UseUserJigSawAddon = false;
							}
							else
								if (CountAddonRepos >= -1)
								{
									CountAddonRepos ++;
									Setup.UseUserJigSawAddon = true;
									strcpy(Setup.UserJigSawAddon, AddonReposJAF[CountAddonRepos]);
								}

						ComBuffer = 204;
					}
					break;
			}
		}
	}







	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// опция Difficulty...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Setup.Type == 2 || Setup.Type == 3)
	{
		// на тот случай, если где-то ставили большую сложность
		if (Setup.Difficult == 4) Setup.Difficult = 2;
		if (Setup.Difficult == 3) Setup.Difficult = 2;
	}


	SetRect(&MDetect, 284,61+160, 284+93, 61+160+30);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	if ((Setup.Type == 0) || (Setup.Type == 1))
	if (vw_OnRect(&MDetect))
	{
		GameCursor.Current=1;
		if (vw_GetWindowLBMouse(true))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			Setup.Difficult=0;
		}
		vw_DrawRect(284,225,0,0,93,22,"DATA\\options2.bmp");
	}

	SetRect(&MDetect, 380,61+160, 380+72, 61+160+30);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	if (vw_OnRect(&MDetect))
	{
		GameCursor.Current=1;
		if (vw_GetWindowLBMouse(true))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			Setup.Difficult=1;
			if (Setup.Type == 2 || Setup.Type == 3) Setup.Difficult=0;
		}
		vw_DrawRect(380,225,95,0,166,22,"DATA\\options2.bmp");
	}

	SetRect(&MDetect, 455,61+160, 455+102, 61+160+30);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	if (vw_OnRect(&MDetect))
	{
		GameCursor.Current=1;
		if (vw_GetWindowLBMouse(true))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			Setup.Difficult=2;
			if (Setup.Type == 2 || Setup.Type == 3) Setup.Difficult=1;
		}
		vw_DrawRect(453,225,0,24,108,46,"DATA\\options2.bmp");
	}

	SetRect(&MDetect, 560,61+160, 561+77, 61+160+30);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	if (vw_OnRect(&MDetect))
	{
		GameCursor.Current=1;
		if (vw_GetWindowLBMouse(true))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			Setup.Difficult=3;
			if (Setup.Type == 2 || Setup.Type == 3) Setup.Difficult=2;
		}
		vw_DrawRect(563,225,0,48,72,70,"DATA\\options2.bmp");
	}

	SetRect(&MDetect, 640,61+160, 640+93, 61+160+30);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	if ((Setup.Type == 0) || (Setup.Type == 1))
	if (vw_OnRect(&MDetect))
	{
		GameCursor.Current=1;
		if (vw_GetWindowLBMouse(true))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			Setup.Difficult=4;
		}
		vw_DrawRect(637,225,74,48,172,70,"DATA\\options2.bmp");
	}

	if (Setup.Type == 2 || Setup.Type == 3)
	{
		vw_DrawRect(304,61+2+160,0,0,56,25,"DATA\\setup_off.bmp", true);
		vw_DrawRect(660,61+2+160,0,0,56,25,"DATA\\setup_off.bmp", true);
		if (Setup.Difficult==0)
			vw_DrawRect(380,225,95,0,166,22,"DATA\\options2.bmp");
		if (Setup.Difficult==1)
			vw_DrawRect(453,225,0,24,108,46,"DATA\\options2.bmp");
		if (Setup.Difficult==2)
			vw_DrawRect(563,225,0,48,72,70,"DATA\\options2.bmp");
	}
	else
	{
		if (Setup.Difficult==0)
			vw_DrawRect(284,225,0,0,93,22,"DATA\\options2.bmp");
		if (Setup.Difficult==1)
			vw_DrawRect(380,225,95,0,166,22,"DATA\\options2.bmp");
		if (Setup.Difficult==2)
			vw_DrawRect(453,225,0,24,108,46,"DATA\\options2.bmp");
		if (Setup.Difficult==3)
			vw_DrawRect(563,225,0,48,72,70,"DATA\\options2.bmp");
		if (Setup.Difficult==4)
			vw_DrawRect(637,225,74,48,172,70,"DATA\\options2.bmp");
	}







	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// опция Size...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 394,61+240, 394+61, 61+240+30);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	if (vw_OnRect(&MDetect))
	{
		GameCursor.Current=1;
		if (vw_GetWindowLBMouse(true))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			Setup.Size=2;
		}
		vw_DrawRect(393,301,0,72,61,101,"DATA\\options2.bmp");
	}

	SetRect(&MDetect, 487,61+240, 487+61, 61+240+30);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	if (vw_OnRect(&MDetect))
	{
		GameCursor.Current=1;
		if (vw_GetWindowLBMouse(true))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			Setup.Size=4;
		}
		vw_DrawRect(486,301,63,72,125,101,"DATA\\options2.bmp");
	}

	SetRect(&MDetect, 579,61+240, 579+61, 61+240+30);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	if (vw_OnRect(&MDetect))
	{
		GameCursor.Current=1;
		if (vw_GetWindowLBMouse(true))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			Setup.Size=6;
		}
		vw_DrawRect(579,301,0,103,61,132,"DATA\\options2.bmp");
	}

	SetRect(&MDetect, 672,61+240, 672+61, 61+240+30);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	if (vw_OnRect(&MDetect))
	{
		GameCursor.Current=1;
		if (vw_GetWindowLBMouse(true))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			Setup.Size=8;
		}
		vw_DrawRect(672,301,63,103,125,132,"DATA\\options2.bmp");
	}


	if (Setup.Size==2)
		vw_DrawRect(393,301,0,72,61,101,"DATA\\options2.bmp");
	if (Setup.Size==4)
		vw_DrawRect(486,301,63,72,125,101,"DATA\\options2.bmp");
	if (Setup.Size==6)
		vw_DrawRect(579,301,0,103,61,132,"DATA\\options2.bmp");
	if (Setup.Size==8)
		vw_DrawRect(672,301,63,103,125,132,"DATA\\options2.bmp");




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// опция Countdown...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	char buffer[20];
	char buffer2[20];
	strcpy(buffer2, " ");
	itoa10(Setup.Countdown, buffer);
	strcat(buffer2, buffer);
	strcat(buffer2, " ");
	DrawManualText(530, 384, buffer2, 631-531, 0);

	// Countdown, стрелка <
	SetRect(&MDetect, 526, 381, 557, 410);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	if (vw_OnRect(&MDetect))
	{
		GameCursor.Current=1;

		if (vw_GetWindowLBMouse(true))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			Setup.Countdown--;
			if (Setup.Countdown<1) Setup.Countdown = 99;
		}
		vw_DrawRect(530,381,56,134,81,164,"DATA\\options2.bmp");
	}
	// Countdown, стрелка >
	SetRect(&MDetect, 606, 381, 637, 410);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	if (vw_OnRect(&MDetect))
	{
		GameCursor.Current=1;

		if (vw_GetWindowLBMouse(true))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			Setup.Countdown++;
			if (Setup.Countdown>99) Setup.Countdown = 1;
		}
		vw_DrawRect(612,381,83,134,107,164,"DATA\\options2.bmp");
	}


	SetRect(&MDetect, 432,61+320, 432+70, 61+320+30);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	if (vw_OnRect(&MDetect))
	{
		GameCursor.Current=1;
		if (vw_GetWindowLBMouse(true))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			Setup.CountdownSw = true;
		}
		vw_DrawRect(439,381,0,134,54,164,"DATA\\options2.bmp");
	}

	SetRect(&MDetect, 663,61+320, 663+70, 61+320+30);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	if (vw_OnRect(&MDetect))
	{
		GameCursor.Current=1;
		if (vw_GetWindowLBMouse(true))
		{
			if (Setup.SoundSw) Audio_PlaySound(1);
			Setup.CountdownSw = false;
		}
		vw_DrawRect(661,381,109,134,181,164,"DATA\\options2.bmp");
	}



	if (Setup.CountdownSw)
		vw_DrawRect(439,381,0,134,54,164,"DATA\\options2.bmp");
	else
		vw_DrawRect(661,381,109,134,181,164,"DATA\\options2.bmp");


}

