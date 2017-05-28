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


#include "Core.h"









// возможные состояния... для прорисовки и обхода
enum status
{
	MAIN_MENU = 1,
	NEW_GAME = 2,
	REGISTRATION = 3,
	TOP_SCORES = 4,
	SETUP = 5,
	CREDITS = 6,
	QUIT = 8,
	GAME_START = 9,
	GAME = 10,
	OPTIONS = 11,
	GAME_START_EVAL = 12
};






//структура файла с настройками...
//все в куче, для удобства...
struct memSetup
{
	// вкл/откл музыки
	bool	MusicSw;
	bool	MusicSw_Game;
	bool	Music_check; // вообще можем-не можем играть музыку
	// указатель на текущую музыку...
	int		MusicCount;
	// вкл/откл SFX
	bool	SoundSw;
	bool	Sound_check; // вообще можем-не можем играть sfx
	// статус оконный/полноэкранный режимы
	bool	FullscrSw;
	// глубина цвета (!только для полноэкранного режима, в оконном исп.глубина рабочего стола)
	int		WindowsBPP;


	bool	CountdownSw;
	int		Countdown;
	int		Size;
	int		Type;
	int		Difficult;


	// информация о лучших результатах
	int		Time[16];
	int		Time2x2[16];
	int		Time4x4[16];
	int		Time6x6[16];
	int		Time8x8[16];

	// загрузка в jig-saw картинки...
	char	UserFileForJigSaw[MAX_PATH];
	bool	UseUserFileForJigSaw;
	int		UserFileForJigSawLoadCount;

	// Addons
	char	UserMosaicAddon[MAX_PATH];
	bool	UseUserMosaicAddon;

	char	UserBuilderAddon[MAX_PATH];
	bool	UseUserBuilderAddon;

	char	UserThePairAddon[MAX_PATH];
	bool	UseUserThePairAddon;

	char	UserJigSawAddon[MAX_PATH];
	bool	UseUserJigSawAddon;

};




// структура для курсора
struct memCursor
{
	// текущий курсор
	// 0- обычный
	// 1- можно нажать (кнопка)
	// 2- можно перетянуть
	// 3- тянем
	int Current;

	// прошлый текущий (для проверки сброс/захват)
	int ExCurrent;


	// номер кадра прорисовки
	int Frame;

	// задержка для прорисовки анимации
	float Delay;


	// место откуда взяли...
	int X;
	int Y;

	// номер элемента текстуры, которую тянем. если нет - 0
	int text;
};

