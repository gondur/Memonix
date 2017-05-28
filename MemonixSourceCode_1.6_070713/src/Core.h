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


#ifndef Core_H
#define Core_H



#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#define _CRT_SECURE_NO_DEPRECATE // выключаем задалбывание с безопасными функциями
	#include <windows.h>
#endif

#if defined(__APPLE__) && defined(__MACH__)
	#include <OpenGL/gl.h>	// Header File For The OpenGL32 Library
	#include <OpenGL/glu.h>	// Header File For The GLu32 Library
#else
	#define __glext_h_  // Don't let gl.h include glext.h
	#include <GL/gl.h>	// Header File For The OpenGL32 Library
	#include <GL/glu.h>	// Header File For The GLu32 Library
	#undef __glext_h_
#endif

#include <stdlib.h> // rand, ...
#include <math.h> // math for core Math


#include "GLext.h"
#include "SDL/SDL.h"
#include "SDL/SDL_syswm.h"
#include "SDL/SDL_endian.h" // для VFS, чтобы правильно считывать таблицу файлов + хранение данных игры
#include "SDL/SDL_image.h"
// иначе не будет наботать Mix_LoadMUS_RW, c версии 1.2.10 это по умолчанию и в винде включено
// но пока делаем руками...
#define USE_RWOPS
#include "SDL/SDL_mixer.h"



// декларируем типы данных, которых можен не быть
#ifndef BYTE
	#define BYTE Uint8
#endif
#ifndef DWORD
	#define DWORD Uint32
#endif
#ifndef BOOL
	#define BOOL bool
#endif


inline void itoa10(int val, char* res)
{
    // http://www.cplusplus.com/ref/cstdio/sprintf.html
    // если нужны не 10-ки
    sprintf(res,"%i",val);
}



#ifdef __unix
	struct RECT
	{
		int left;
		int top;
		int right;
		int bottom;
	};
	inline void SetRect(RECT *rect, int left, int top, int right, int bottom)
	{
		rect->right = right;
		rect->top = top;
		rect->left = left;
		rect->bottom =bottom;
	}


	#include <valarray> // memcpy
	#include <stdarg.h> // va_start

	#include <sys/stat.h> // mkdir
	#include <sys/types.h> // mkdir

	#define MAX_PATH 1024

#endif // unix








#include "Core/System/System.h"
#include "Core/Math/Math.h"
#include "Core/VirtualFileSystem/VFS.h"
#include "Core/Texture/Texture.h"
#include "Core/RendererInterface/RendererInterface.h"





#endif // Core_H
