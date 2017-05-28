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

// настройки игры...
memSetup Setup;
// состояние курсора
memCursor GameCursor;
// защелка на выход, когда нужно перегрузить, а когда просто поменять режим
bool Quit = false;
bool NeedReCreate = false;
// выходим или нет..
bool CanQuit = true;
// полное путь к программе
char ProgrammDir[MAX_PATH];
char VFSFileNamePath[MAX_PATH];
// возможности железа, получаем через рендерер
eDevCaps CAPS;
// полное имя для файла с данными о игре
char DatFileName[MAX_PATH];



// данные для определения папки пользователя
#ifdef WIN32
#define SD_APPDATA                   0x001a
typedef BOOL (WINAPI *SHGETSPECIALFOLDERPATH)(HWND hwndOwner, LPTSTR lpszPath, int nFolder, BOOL fCreate);
SHGETSPECIALFOLDERPATH pSHGetSpecialFolderPath = 0;
#endif // WIN32



//------------------------------------------------------------------------------------
// сохранение данных
//------------------------------------------------------------------------------------
void SaveGameData()
{
	SDL_RWops *SetupF = SDL_RWFromFile(DatFileName, "wb+");
	if (SetupF != NULL) //файл есть! - пишем...
	{
		SDL_RWseek(SetupF, 0, SEEK_SET);
		SDL_RWwrite(SetupF, &Setup, 1, sizeof(memSetup));
		SDL_RWclose(SetupF);
	}
}







//------------------------------------------------------------------------------------
// основная процедура...
//------------------------------------------------------------------------------------
int main( int argc, char **argv )
{


#ifdef WIN32
	// иним пути для винды
	ZeroMemory(ProgrammDir, sizeof(ProgrammDir));
	GetModuleFileName(NULL, ProgrammDir, MAX_PATH);
	char* s = strrchr(ProgrammDir,'\\');
	if (s) s[0]=0x0;
	const char *Fi = "\\";
	strcat( ProgrammDir, Fi );

	ZeroMemory(DatFileName, sizeof(DatFileName));
	ZeroMemory(VFSFileNamePath, sizeof(VFSFileNamePath));

	// Получаем данные, где папка пользователя
	bool InitWithoutDLL = true;
	HMODULE hShellDLL = LoadLibrary("shell32.dll");
	if (hShellDLL)
	{
		pSHGetSpecialFolderPath = (SHGETSPECIALFOLDERPATH) GetProcAddress(hShellDLL, "SHGetSpecialFolderPathA");
		char UserPath[MAX_PATH];
		ZeroMemory(UserPath, sizeof(UserPath));

		if (pSHGetSpecialFolderPath != NULL)
		if(SUCCEEDED(pSHGetSpecialFolderPath(NULL,
								UserPath,
								SD_APPDATA, //CSIDL_APPDATA
								true)))
		{
			strcat(UserPath, "\\Memoinix\\");
			CreateDirectory(UserPath, NULL);

			strcpy(DatFileName, UserPath);
			strcat(DatFileName, "memwin.dat");

			// уже проинили, дальше не нужно
			InitWithoutDLL = false;
		}
	}
	// освобождаем библиотеку
	FreeLibrary(hShellDLL);


	// иним, если старая винда, или была ошибка
	if (InitWithoutDLL)
	{
		strcpy(DatFileName, ProgrammDir);
		strcat(DatFileName, "amwin.dat");
	}

	strcpy(VFSFileNamePath, ProgrammDir);
	strcat(VFSFileNamePath, "gamedata.vfs");

	// делаем вывод в консоль, фактически вообще убираем вывод
	// или потом поставить в файлы, которые нужны
	freopen( "CON", "w", stdout );
	freopen( "CON", "w", stderr );
#elif __unix
	// иним пути для юникса-линукса
	// если передали параметр-путь

	const char* key = "HOME";
	const char* homeval = getenv(key);

	bool dirpresent = false;
	for (int i=1; i<argc; i++)
	{
		if (!strncmp(argv[i], "--dir=", sizeof("--dir")))
		{
			dirpresent = true;
			// если передали относительный путь в папку пользователя с тильдой
			if (argv[i][6] != '~')
				strncpy(ProgrammDir, argv[i]+strlen("--dir="), strlen(argv[i])-strlen("--dir=")+1);
			else
			{
				strcpy(ProgrammDir, homeval);// -1, это тильда... а в кол-ве нет, т.к. /0 там должен остаться
				strncat(ProgrammDir, argv[i]+strlen("--dir=")+1, strlen(argv[i])-strlen("--dir="));
			}
			// если в конце нет слеша - ставим его
			if (ProgrammDir[strlen(ProgrammDir)-1] != '/')
				strncat(ProgrammDir, "/", strlen("/"));

		}
	}
	if (!dirpresent) strcpy(ProgrammDir, "./");

	strcpy(VFSFileNamePath, ProgrammDir);
	strcat(VFSFileNamePath, "gamedata.vfs");

	// укладываем в нужном месте (где 100% дають создавать) файл с настройками
	strcpy(DatFileName, homeval);
	strcat(DatFileName, "/.memonix");
	mkdir(DatFileName, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	strcat(DatFileName, "/memlin.dat");

#endif // unix


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// работа с файлом данных...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// нужно переинициализировать
	bool ReinitFile = false;
	// нужно создать
	bool InitFile = false;


	SDL_RWops *SetupF = SDL_RWFromFile(DatFileName, "rb");
	if (SetupF != NULL) //файл есть! - читаем...
	{
		SDL_RWseek(SetupF, 0, SEEK_END);
		if (SDL_RWtell(SetupF) != sizeof(memSetup))
		{
			ReinitFile = true;
		}
		else
		{
			SDL_RWseek(SetupF, 0, SEEK_SET);
			SDL_RWread(SetupF,&Setup,1,sizeof(memSetup));

			// Смотрим, чтобы настройки были правильными...
			// только те, что нужны...
			if (Setup.MusicCount<1 || Setup.MusicCount>3) Setup.MusicCount = 1;

		//	if (Setup.WindowsBPP!= 16 && Setup.WindowsBPP!=32) Setup.WindowsBPP=16;
			if (Setup.Countdown<0) Setup.Countdown = 30;
			if (Setup.Size!=2 && Setup.Size!=4 &&
				Setup.Size!=6 && Setup.Size!=8) Setup.Size = 8;
			if (Setup.Type<0 || Setup.Type>3) Setup.Type = 1;
			if (Setup.Difficult<0 || Setup.Difficult>4) Setup.Difficult = 0;
			for (int i=0; i<16;i++)
			{
				if (Setup.Time[i]<0) Setup.Time[i] = 99999;
				if (Setup.Time2x2[i]<0) Setup.Time2x2[i] = 99999;
				if (Setup.Time4x4[i]<0) Setup.Time4x4[i] = 99999;
				if (Setup.Time6x6[i]<0) Setup.Time6x6[i] = 99999;
				if (Setup.Time8x8[i]<0) Setup.Time8x8[i] = 99999;
			}

		}
		SDL_RWclose(SetupF);
	}
	else InitFile = true;

	// если нужно - пересоздаем файл данных
	if (ReinitFile || InitFile)
	{
		SetupF = SDL_RWFromFile(DatFileName,"wb+");

		// установка всех данных по умолчанию!!!
		Setup.MusicSw = true;
		Setup.MusicSw_Game = false;
		Setup.Music_check = true;
		Setup.MusicCount = 1;
		Setup.SoundSw = true;
		Setup.Sound_check = true;
		Setup.FullscrSw = true;

		// по умолчанию - пусть возьмет наилучший режим сам
		Setup.WindowsBPP = 0;

		Setup.CountdownSw = true;
		Setup.Countdown = 30;
		Setup.Size = 4;
		Setup.Type = 0;
		Setup.Difficult = 0;

		for (int i=0; i<16;i++)
		{
			Setup.Time[i] = 99999;
			Setup.Time2x2[i] = 99999;
			Setup.Time4x4[i] = 99999;
			Setup.Time6x6[i] = 99999;
			Setup.Time8x8[i] = 99999;
		}


		Setup.UseUserMosaicAddon = false;
  		Setup.UseUserBuilderAddon = false;
		Setup.UseUserThePairAddon = false;
		Setup.UseUserJigSawAddon = false;

		if (SetupF != NULL)
		{
			SDL_RWwrite(SetupF,&Setup,1,sizeof(memSetup));
			SDL_RWclose(SetupF);
		}
	}



ReCreate:

#ifdef WIN32 // временно, пока этого нет в SDL для WIN32 ставим частоту в полноэкр. режиме
// 1- получаем частоту
	int Freq = 0;
	if (Setup.FullscrSw) // только для полноэкранного режима!
	{
		DEVMODE dmScreenSettings;
		ZeroMemory (&dmScreenSettings, sizeof (DEVMODE));
		dmScreenSettings.dmSize	= sizeof (DEVMODE);
		// если успешно, у нас в Freq текущая частота экрана
		if(EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmScreenSettings))
			Freq = dmScreenSettings.dmDisplayFrequency;
	}
#endif // WIN32


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// иним SDL
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if ( SDL_WasInit(SDL_INIT_VIDEO) == 0 )
	{
		printf("Couldn't init SDL: %s\n", SDL_GetError());
		return 1;
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// подключаем VFS
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (vw_OpenVFS(VFSFileNamePath, "1") != 0)
	{
		printf("gamedata.vfs file not found.\n");
		SDL_Quit();
		return 0;
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// делаем окно
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	int FSAA = 0;
	if (!vw_InitRenderer("Memonix", 800, 600, &Setup.WindowsBPP, Setup.FullscrSw, &FSAA))
	{
		SDL_Quit();
		return 0;									// Quit If Window Was Not Created
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// установка иконки окна приложения
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	eFILE *pFile = vw_fopen("DATA\\icon.bmp");
	if (pFile != NULL)
	{
		SDL_RWops *RWFile = SDL_RWFromConstMem(pFile->Data, pFile->RealLength);
		if (RWFile != NULL)
		{
			SDL_Surface *image = IMG_LoadBMP_RW(RWFile);
			if (image != NULL)
			{
				SDL_WM_SetIcon(image, NULL);
				SDL_FreeSurface(image);
			}
			SDL_RWclose(RWFile);
		}
		vw_fclose(pFile);
	}




#ifdef WIN32 // временно, пока этого нет в SDL для WIN32 ставим частоту в полноэкр. режиме
// 2- ставим частоту (тут мы уже знаем глубину на 100%
	bool NeedRestoreResol = false;
	if (Freq > 60)// если есть смысл, пытаемся поставить
	{
		DEVMODE dmScreenSettings;
		ZeroMemory (&dmScreenSettings, sizeof (DEVMODE));
		dmScreenSettings.dmSize	= sizeof (DEVMODE);
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
		dmScreenSettings.dmPelsWidth		= 800;
		dmScreenSettings.dmPelsHeight		= 600;
		dmScreenSettings.dmBitsPerPel		= Setup.WindowsBPP;
		dmScreenSettings.dmDisplayFrequency	= Freq;
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL)
		{
			NeedRestoreResol = true;
		}
	}
#endif // WIN32




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// скрываем системный курсор
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SDL_ShowCursor(SDL_DISABLE);


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// загрузка текстур согласно моделе загрузки
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	LoadAll();



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// установка звука
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	bool sndIsInit = false;
	if ( SDL_WasInit(SDL_INIT_AUDIO) == 0 )
	{
		Setup.MusicSw = false;
		Setup.MusicSw_Game = false;
		Setup.SoundSw = false;
		Setup.Music_check = false;
		Setup.Sound_check = false;
		printf("Could not init SDL audio!\n");
		fprintf(stderr, "Could not init SDL audio!\n");
	}
	else
	{
		if(!InitSound())
		{
			printf("Unable to open audio!\n");
			fprintf(stderr, "Unable to open audio!\n");
			Setup.MusicSw = false;
			Setup.MusicSw_Game = false;
			Setup.SoundSw = false;
			Setup.Music_check = false;
			Setup.Sound_check = false;
		}
	}

	// отмена внутренних счетчиков для зарегистрированной игры
	Setup.UserFileForJigSawLoadCount = 0;
	// если жигсов - меняем картинку, чтобы не повторяться (выбор из 13-ти)
	if (Setup.Type==3) CurentFotoNum = 1+(int)fmodf(vw_Rand(),12);


#ifdef WIN32
	if (!ProtectEnvelopeCheck1())
	{
		vw_ShutdownRenderer();
	}
#endif // WIN32

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// установка процедуры... основного цикла и переход на нее
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	CanQuit = false;
	GameStatus = MAIN_MENU;
	TimeDelay = SDL_GetTicks();

	// первоначальная установка курсора
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	vw_SetMousePos(mouse_x, mouse_y);



loop:


	Quit = false;
	NeedReCreate = false;
	bool NeedLoop = true;

	while(!Quit)
	{
		SDL_Event event;
		while ( SDL_PollEvent(&event) )
		{
			switch (event.type)
			{
				// если нажали закрыть окно
				case SDL_QUIT:
					Quit = true;
					break;

				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) Quit = true;
					break;


				// работаем с движением мышки
				case SDL_MOUSEMOTION:
                    vw_SetMousePos(event.motion.x, event.motion.y);
					break;

				// обрабатываем кнопки мыши
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
						vw_SetWindowLBMouse(true);
					if (event.button.button ==  SDL_BUTTON_RIGHT)
						vw_SetWindowRBMouse(true);
					break;

				case SDL_MOUSEBUTTONUP:
					if (event.button.button ==  SDL_BUTTON_LEFT)
						vw_SetWindowLBMouse(false);
					if (event.button.button ==  SDL_BUTTON_RIGHT)
						vw_SetWindowRBMouse(false);
					break;

				case SDL_ACTIVEEVENT:
					if(event.active.state & SDL_APPACTIVE)
					{
						// iconified
						if( event.active.gain == 0 ) NeedLoop = false;
						// restored
						if( event.active.gain == 1 )  NeedLoop = true;
					}
					if(event.active.state & SDL_APPINPUTFOCUS)
					{
						// input focus was lost
						if( event.active.gain == 0 ) NeedLoop = false;
						// input focus was gained
						if( event.active.gain == 1 )  NeedLoop = true;
					}
					break;


				default:
					break;
			}
		}


		// если окно видемое - рисуем
		if (NeedLoop)
		{
			Loop_Proc();
		}
		else
		{
			if (MusicIsPlaying)
			{
				MusicIsPlaying = false;
				Mix_HaltMusic();
			}
			SDL_Delay(100);
		}


	}

	// если не выходим...
	if (!NeedReCreate)
	if (!CanQuit && Quit)
	{
		SetCurrentDialogBox(1);
		goto loop;
	}






	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// заверщение, освобождение памяти...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (SDL_WasInit(SDL_INIT_AUDIO) != 0)
	{
		ShutdownAudio();
	}





	SDL_ShowCursor(SDL_ENABLE);


	lastgame=-1;
	vw_ReleaseAllFonts();
	vw_ReleaseAllTextures();
	vw_ShutdownRenderer();
	vw_ShutdownVFS();
	SDL_Quit();


#ifdef WIN32 // временно, пока этого нет в SDL для WIN32 ставим частоту в полноэкр. режиме
// 3- восстанавливаем первоначальное разрешение
	if (NeedRestoreResol) // восстанавливаем разрешение, если нужно
	{
		ChangeDisplaySettings(NULL, 0);
	}
#endif // WIN32


	if (NeedReCreate) goto ReCreate;

	SaveGameData();


	// уходим из программы...
	return 0;



//fprintf(stderr, "Unable to load %s\n", nName);

}
