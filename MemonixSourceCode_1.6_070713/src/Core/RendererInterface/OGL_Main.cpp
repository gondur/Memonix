/*

Memonix, Viewizard Game Core ver 2.0
Copyright (c) 2001-2006 Michael Kurinnoy, Viewizard Games
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



#include "RendererInterface.h"






//------------------------------------------------------------------------------------
// переменные...
//------------------------------------------------------------------------------------
eDevCaps OpenGL_DevCaps;

float fClearRedGL = 0.0f;
float fClearGreenGL = 0.0f;
float fClearBlueGL = 0.0f;
float fClearAlphaGL = 1.0f;

float fNearClipGL = 1.0f;
float fFarClipGL = 1000.0f;
float fAngleGL = 45.0f;

// aspect ration
float ARWidthGL;
float ARHeightGL;
bool ARFLAGGL = false;

// переменные для просчета кол-ва прорисовываемых примитивов...
int tmpPrimCountGL=0;
int PrimCountGL=0;


PFNGLACTIVETEXTUREARBPROC		glActiveTexture_ARB	= NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC	glClientActiveTexture_ARB = NULL;
PFNGLLOCKARRAYSEXTPROC glLockArraysEXT = NULL;
PFNGLUNLOCKARRAYSEXTPROC glUnlockArraysEXT = NULL;


bool anisotropic_filterGL = false;
int anisotropic_angleGL = 0;

float CurrentGammaGL = 1.0f;
float CurrentContrastGL = 1.0f;
float CurrentBrightnessGL = 1.0f;

float fScreenWidthGL = 0.0f;
float fScreenHeightGL = 0.0f;

//int AA[] = {2, 4, 8, 16};
//int AAcount = sizeof (AA)/ sizeof (int);


int VertexIndexCount = 0;
GLuint *VertexIndex = 0;











//------------------------------------------------------------------------------------
// установка окна на середину
//------------------------------------------------------------------------------------
void CenterWindow()
{
    SDL_Surface *GameScreen = SDL_GetVideoSurface();
    SDL_SysWMinfo info;

    SDL_VERSION(&info.version);
    if ( SDL_GetWMInfo(&info) > 0 )
	{
		#ifdef __unix
            if ( info.subsystem == SDL_SYSWM_X11 )
			{
                info.info.x11.lock_func();
                int w = DisplayWidth(info.info.x11.display,
                                 DefaultScreen(info.info.x11.display));
                int h = DisplayHeight(info.info.x11.display,
                                 DefaultScreen(info.info.x11.display));
                int x = (w - GameScreen->w)/2;
                int y = (h - GameScreen->h)/2;
                XMoveWindow(info.info.x11.display, info.info.x11.wmwindow, x, y);
                info.info.x11.unlock_func();
            }
        #endif // unix
        #ifdef WIN32
            {
				RECT rc;
				HWND hwnd = info.window;
				int w=GetSystemMetrics(SM_CXSCREEN);
				int h=GetSystemMetrics(SM_CYSCREEN);
				GetWindowRect(hwnd, &rc);
				int x = (w - (rc.right-rc.left))/2;
				int y = (h - (rc.bottom-rc.top))/2;
				SetWindowPos(hwnd, NULL, x, y, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
            }
        #endif // WIN32
    }

	printf("SDL version: %i.%i.%i\n", info.version.major, info.version.minor, info.version.patch);
}





//------------------------------------------------------------------------------------
// получение поддерживаемых устройством расширений
//------------------------------------------------------------------------------------
bool ExtensionSupported( const char *Extension)
{
	char *extensions;
	extensions=(char *) glGetString(GL_EXTENSIONS);
	// если можем получить указатель, значит это расширение есть
	if (strstr(extensions, Extension) != NULL) return true;
	return false;
}













//------------------------------------------------------------------------------------
// инициализация Open_GL
//------------------------------------------------------------------------------------
bool vw_InitRenderer(char* Title, int Width, int Height, int *Bits, BOOL FullScreenFlag, int *FSAA)
{

if (*FSAA > OpenGL_DevCaps.MaxMultiSampleType) *FSAA = OpenGL_DevCaps.MaxMultiSampleType;

/*

	// если поддерживаем антиалиасинг, нужно выяснить до скольки можем держать
//	if (ExtensionSupported("GL_ARB_multisample"))
	{
//		if (GL_ARB_multisampleTEST)
		{
		//	vw_ShutdownRenderer();

			for (int i=0; i<AAcount; i++)
			{
				SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
				SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, AA[i]);
				if (SDL_SetVideoMode(640, 480, 0, SDL_OPENGL) != NULL)
				{
					int Buffers=0;
					int Samples=0;
					glGetIntegerv( GL_SAMPLE_BUFFERS_ARB, & Buffers ) ;
					glGetIntegerv( GL_SAMPLES_ARB, & Samples ) ;
					vw_ShutdownRenderer();
					if (!Buffers || !Samples)
					{
						fprintf(stderr, "AA--- %i, %i\n", Buffers, Samples);
						goto end;
					}
					else
					{
						fprintf(stderr, "AA+++ %i, %i\n", Buffers, Samples);
						OpenGL_DevCaps.MaxMultiSampleType = AA[i];
					}
				}
				else
				{
				//	goto end;
				}

			}

end:

			if (*FSAA > OpenGL_DevCaps.MaxMultiSampleType) *FSAA = OpenGL_DevCaps.MaxMultiSampleType;

		}
	}

*/
















	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// устанавливаем режим и делаем окно
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Uint32 Flags = SDL_OPENGL;

	// установка только для акселерации в железе, работает только с 1.2.10
	// иначе даже скомпилить не сможем
#if SDL_MAJOR_VERSION>1 || SDL_MINOR_VERSION>2 || SDL_PATCHLEVEL>=10
    // если на этой машине нужная версия
	if (SDL_VERSION_ATLEAST(1,2,10))
	{
		Flags |= SDL_GL_ACCELERATED_VISUAL;
	}
#endif

	// если иним в первый раз, тут ноль и нужно взять что-то подходящее
	if (*Bits == 0) *Bits = SDL_GetVideoInfo()->vfmt->BitsPerPixel;
	if (*Bits < 8) *Bits = 8;
	int WBits = *Bits;

	if (FullScreenFlag)
	{
		Flags |= SDL_FULLSCREEN;
	}
	else
	{	// для окна не нужно ставить глубину принудительно
		WBits = SDL_GetVideoInfo()->vfmt->BitsPerPixel;
		Flags |= SDL_ANYFORMAT; // чтобы для оконного взял лучший режим сам
	}


	// пытаемся поставить FSAA, тут все равно что сейчас ставим... потом разберемся
	if (*FSAA > 0)
	{
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, *FSAA);
	}




	// не работает на Win32
#ifndef WIN32
	putenv("SDL_VIDEO_CENTERED=1");
#endif // unix


	// устанавливаем атрибуты
	switch (WBits)
	{
		case 8:
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 3);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 3);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 2);
			break;
		 case 15:
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
			break;
		case 16:
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
			break;
		default:
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
			break;
	}

	// ставим максимальный, он сам найдет ближайший возможный
	// иначе не будет fsaa
//	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	// естественно просим 2-ю буферизацию
//	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);



	// создаем окно
	if (SDL_SetVideoMode(Width, Height, WBits, Flags)  == NULL)
	{
		fprintf(stderr, "Can't set video mode %i x %i x %i\n", Width, Height, WBits);
		return false;
	}



	// центровка для винды
	CenterWindow();
	// ставим название класса окна
	SDL_WM_SetCaption(Title, "Viewizard Game");


	// если полноэкранный режим, смотрим сколько действительно поставили bpp и запоминаем
	if (FullScreenFlag) *Bits = SDL_GetVideoInfo()->vfmt->BitsPerPixel;

	printf("Set video mode: %i x %i x %i\n", Width, Height, *Bits);




/*
SDL_Rect **modes;
modes=SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE);

  fprintf(stderr, "Available Modes\n");
  for(int i=0;modes[i];++i)
    printf("  %d x %d\n", modes[i]->w, modes[i]->h);
*/



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// установка параметров прорисовки
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (OpenGL_DevCaps.MaxMultiSampleType > 0) glEnable(GL_MULTISAMPLE);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	vw_SetClearColor(fClearRedGL, fClearGreenGL, fClearBlueGL, fClearAlphaGL);
	glClearStencil(0);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glEnable(GL_TEXTURE_2D);							//Enable two dimensional texture mapping
	glEnable(GL_DEPTH_TEST);							//Enable depth testing
	glShadeModel(GL_SMOOTH);							//Enable smooth shading (so you can't see the individual polygons of a primitive, best shown when drawing a sphere)
	glClearDepth(1.0);									//Depth buffer setup
	glDepthFunc(GL_LEQUAL);								//The type of depth testing to do (LEQUAL==less than or equal to)
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	//The nicest perspective look
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);


	vw_ResizeScene(fAngleGL, (Width*1.0f)/(Height*1.0f), fNearClipGL, fFarClipGL);


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// получаем возможности железа
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	OpenGL_DevCaps.VidMemTotal = SDL_GetVideoInfo()->video_mem;
	printf("\n");
	printf("Vendor     : %s\n", glGetString(GL_VENDOR));
	printf("Renderer   : %s\n", glGetString(GL_RENDERER));
	printf("Version    : %s\n", glGetString(GL_VERSION));
	printf("\n");
	printf("Video memory: %i kB\n", OpenGL_DevCaps.VidMemTotal);

	OpenGL_DevCaps.MaxMultTextures = 1;
	OpenGL_DevCaps.MaxTextureHeight = 256;
	OpenGL_DevCaps.MaxTextureWidth = 256;
    if (ExtensionSupported("GL_ARB_multitexture"))
	{
		glActiveTexture_ARB = (PFNGLACTIVETEXTUREARBPROC) SDL_GL_GetProcAddress("glActiveTextureARB");
		glClientActiveTexture_ARB = (PFNGLCLIENTACTIVETEXTUREARBPROC) SDL_GL_GetProcAddress("glClientActiveTextureARB");
		glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &OpenGL_DevCaps.MaxMultTextures);
		printf("GL_ARB_multitexture supported: %i textures.\n", OpenGL_DevCaps.MaxMultTextures);
	}
	else
	{
		printf("GL_ARB_multitexture not supported!\n");
		return false;
	}

	glLockArraysEXT = (PFNGLLOCKARRAYSEXTPROC)SDL_GL_GetProcAddress("glLockArraysEXT");
	glUnlockArraysEXT = (PFNGLUNLOCKARRAYSEXTPROC)SDL_GL_GetProcAddress("glUnlockArraysEXT");


	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &OpenGL_DevCaps.MaxTextureHeight);
	printf("Max texture height: %i \n", OpenGL_DevCaps.MaxTextureHeight);
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &OpenGL_DevCaps.MaxTextureWidth);
	printf("Max texture width: %i \n", OpenGL_DevCaps.MaxTextureWidth);
	glGetIntegerv(GL_MAX_LIGHTS, &OpenGL_DevCaps.MaxActiveLights);
	printf("Max lights: %i \n", OpenGL_DevCaps.MaxActiveLights);
	if (!ExtensionSupported("GL_ARB_multisample")) printf("GL_ARB_multisample not supported!\n");
	printf("Set FSAA: %i \n", *FSAA);

	if (!ExtensionSupported("GL_EXT_texture_filter_anisotropic"))
	{
		// анизотропная фильтрация не поддерживается
		anisotropic_filterGL = true;
		printf("Anisotropic filter not supported.\n");
	}
	else
	{
		// есть поддержка анизотропной фильтрации
		// получим максимально доступный угол анизотропии...
		anisotropic_filterGL = true;
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT,&anisotropic_angleGL);
		printf("Anisotropic filter supported.\n");
		printf("Max anisotropy: %i\n", anisotropic_angleGL);
	}
	printf("\n");



	// получаем и выводим все поддерживаемые расширения
	char *extensions;
	int i, len;
	extensions = (char *)glGetString(GL_EXTENSIONS);
	len = (int)strlen(extensions);
	for (i=0; i<len; i++) // меняем разделитель
		if (extensions[i]==' ') extensions[i]='\n';

	printf("Supported GL extensions:\n%s\n", extensions);
	printf("\n");


	VertexIndexCount = 0;
	VertexIndex = 0;


	// выключаем вертикальную синхронизацию в винде, она тут не нужна, а нам нужно как можно
	// больше фпс
#ifdef WIN32
	typedef void (APIENTRY * WGLSWAPINTERVALEXT) (int);
	WGLSWAPINTERVALEXT wglSwapIntervalEXT = (WGLSWAPINTERVALEXT)
	wglGetProcAddress("wglSwapIntervalEXT");
	if (wglSwapIntervalEXT)
	   wglSwapIntervalEXT(0); // disable vertical synchronisation
#endif // WIN32



	return true;
}






//------------------------------------------------------------------------------------
// получение возможностей железа...
//------------------------------------------------------------------------------------
void vw_GetDevCaps(eDevCaps *DevCaps)
{
	*DevCaps = OpenGL_DevCaps;
}





//------------------------------------------------------------------------------------
// получение кол-ва прорисованных примитивов...
//------------------------------------------------------------------------------------
int vw_GetPrimCount(void)
{
	return PrimCountGL;
}






//------------------------------------------------------------------------------------
// Завершение работы с OpenGL'м
//------------------------------------------------------------------------------------
void vw_ShutdownRenderer()
{

	SDL_Surface *GameScreen = SDL_GetVideoSurface();
	if (GameScreen != NULL)
		SDL_FreeSurface(GameScreen);

	if (VertexIndex != 0)
	{
		delete [] VertexIndex;
		VertexIndex = 0;

	}
	VertexIndexCount = 0;
}






//------------------------------------------------------------------------------------
// Изменение области вывода...
//------------------------------------------------------------------------------------
void vw_ResizeScene(float nfAngle, float AR, float nfNearClip, float nfFarClip)
{
	fAngleGL = nfAngle;

	if(nfNearClip==0 && nfFarClip==0)
		;
	else
	{
		fNearClipGL = nfNearClip;
		fFarClipGL = nfFarClip;
	}


	glMatrixMode(GL_PROJECTION);								//Select the projection matrix
	glLoadIdentity();											//Reset the projection matrix

	gluPerspective(fAngleGL, AR, fNearClipGL, fFarClipGL);


	glMatrixMode(GL_MODELVIEW);									//Select the modelview matrix
	glLoadIdentity();											//Reset The modelview matrix
}







//------------------------------------------------------------------------------------
// Изменение области вывода...
//------------------------------------------------------------------------------------
void vw_ChangeSize(int nWidth, int nHeight)
{

	vw_ResizeScene(fAngleGL, (nWidth*1.0f)/(nHeight*1.0f), fNearClipGL, fFarClipGL);

	// скорее всего сдвинули немного изображение, из-за разницы в осях с иксами
	int buff[4];
	glGetIntegerv(GL_VIEWPORT, buff);
	// перемещаем его вверх
	glViewport(buff[0], nHeight - buff[3], buff[2], buff[3]);
}








//------------------------------------------------------------------------------------
// начало прорисовки
//------------------------------------------------------------------------------------
void vw_BeginRendering()
{
	int buff[4];
	glGetIntegerv(GL_VIEWPORT, buff);
	fScreenWidthGL = buff[2]*1.0f;
	fScreenHeightGL = buff[3]*1.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glMatrixMode(GL_MODELVIEW);									//Select the modelview matrix
	glLoadIdentity();											//Reset The modelview matrix


	tmpPrimCountGL = 0;
}







//------------------------------------------------------------------------------------
// завершение прорисовки
//------------------------------------------------------------------------------------
void vw_EndRendering()
{
//-	glFinish(); // сильно тормозит
//	glFlush();
	SDL_GL_SwapBuffers();

	PrimCountGL = tmpPrimCountGL;

	// проверка приоритета
	vw_CheckTexturesPrior();
}








//------------------------------------------------------------------------------------
// Установка Aspect Ration
//------------------------------------------------------------------------------------
void vw_SetAspectRation(float nWidth, float nHeight, bool Value)
{
	if (Value)
	{
		ARWidthGL = nWidth;
		ARHeightGL = nHeight;
		ARFLAGGL = true;
	}
	else
		ARFLAGGL=false;
}








//------------------------------------------------------------------------------------
// Получение данных aspect ration
//------------------------------------------------------------------------------------
bool vw_GetAspectWH(float *ARWidth, float *ARHeight)
{
	*ARWidth = ARWidthGL;
	*ARHeight = ARHeightGL;
	return ARFLAGGL;
}











//------------------------------------------------------------------------------------
// установка гаммы...
//------------------------------------------------------------------------------------
void vw_SetGammaRamp(float Gamma, float Contrast, float Brightness)
{
	CurrentGammaGL = Gamma;
	CurrentContrastGL = Contrast;
	CurrentBrightnessGL = Brightness;

	Uint16 *ramp = 0;

	ramp = new Uint16[256*3];

	float angle = CurrentContrastGL;
	float offset = (CurrentBrightnessGL-1)*256;
	for (int i = 0; i < 256; i++)
	{
		float k = i/256.0f;
		k = (float)pow(k, 1.f/CurrentGammaGL);
		k = k*256;
		float value = k*angle*256+offset*256;
		if (value > 65535)	value = 65535;
		if (value < 0)		value = 0;

		ramp[i]		= (Uint16) value;
		ramp[i+256]	= (Uint16) value;
		ramp[i+512]	= (Uint16) value;
	}

	SDL_SetGammaRamp(ramp, ramp+256, ramp+512);

	delete [] ramp;
}






//------------------------------------------------------------------------------------
// получение гаммы...
//------------------------------------------------------------------------------------
void vw_GetGammaRamp(float *Gamma, float *Contrast, float *Brightness)
{
	*Gamma = CurrentGammaGL;
	*Contrast = CurrentContrastGL;
	*Brightness = CurrentBrightnessGL;
}








//------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------
void vw_SetViewport(int x, int y, int width, int height, float znear, float zfar, int Corner)
{
	if (Corner == RI_UL_CORNER)
		y = (int)(fScreenHeightGL - y - height);

	glViewport(x, y, width, height);
	glDepthRange(znear, zfar);
}


//------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------
void vw_GetViewport(int *x, int *y, int *width, int *height, float *znear, float *zfar)
{
	int buff[4];
	glGetIntegerv(GL_VIEWPORT, buff);
	*x = buff[0];
	*y = buff[1];
	*width = buff[2];
	*height = buff[3];
	float buff2[2];
	glGetFloatv(GL_DEPTH_RANGE, buff2);
	*znear = buff2[0];
	*zfar = buff2[1];
}







////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_PolygonMode(int mode)
{
	switch (mode)
	{
		case RI_POINT:
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			break;
		case RI_LINE:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case RI_FILL:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
	}
}




////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_CullFace(int face)
{
	glEnable(GL_CULL_FACE);

	switch (face)
	{
		case RI_BACK:
			glCullFace(GL_BACK);
			break;
		case RI_FRONT:
			glCullFace(GL_FRONT);
			break;
		case RI_NONE:
			glDisable(GL_CULL_FACE);
			break;
	}
}




////////////////////////////////////////////////////////////
// установка цвета очистки буфера
////////////////////////////////////////////////////////////
void vw_SetClearColor(float nRed, float nGreen, float nBlue, float nAlpha)
{
	fClearRedGL = nRed;
	fClearGreenGL = nGreen;
	fClearBlueGL = nBlue;
	fClearAlphaGL = nAlpha;
	glClearColor(nRed, nGreen, nBlue, nAlpha);
}





////////////////////////////////////////////////////////////
// установка цвета
////////////////////////////////////////////////////////////
void vw_SetColor(float nRed, float nGreen, float nBlue, float nAlpha)
{
	glColor4f(nRed, nGreen, nBlue, nAlpha);
}




////////////////////////////////////////////////////////////
// управление буфером глубины...
////////////////////////////////////////////////////////////
void vw_DepthTest(bool mode, int funct)
{
	if (mode)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	if (funct>=1 && funct<=8)
	{
		GLenum fun = GL_NEVER;
		switch(funct)
		{
			case 1: fun = GL_NEVER; break;
			case 2: fun = GL_LESS; break;
			case 3: fun = GL_EQUAL; break;
			case 4: fun = GL_LEQUAL; break;
			case 5: fun = GL_GREATER; break;
			case 6: fun = GL_NOTEQUAL; break;
			case 7: fun = GL_GEQUAL; break;
			case 8: fun = GL_ALWAYS; break;
		}
		glDepthFunc(fun);
	}
}

