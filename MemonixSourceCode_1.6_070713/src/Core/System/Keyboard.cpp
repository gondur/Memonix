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


#include "System.h"





int MaxKeyCount = 0;


//------------------------------------------------------------------------------------
// установка-получение статуса нажатых кнопок на клавиатуре
//------------------------------------------------------------------------------------
bool vw_GetKeys(int Num)
{
	Uint8 *keystate = SDL_GetKeyState(&MaxKeyCount);
	if (keystate[Num]) return true;
	return false;
}
void vw_SetKeys(int Num, bool NewKeyStatus)
{
	Uint8 *keystate = SDL_GetKeyState(&MaxKeyCount);
	keystate[Num] = NewKeyStatus;
}

int GetMaxKeys()
{
	return MaxKeyCount;
}






// название кнопок
char * vw_VirtualCodeName(int Num)
{
	switch (Num)
	{
		case SDLK_1: return "1";
		case SDLK_2: return "2";
		case SDLK_3: return "3";
		case SDLK_4: return "4";
		case SDLK_5: return "5";
		case SDLK_6: return "6";
		case SDLK_7: return "7";
		case SDLK_8: return "8";
		case SDLK_9: return "9";
		case SDLK_0: return "0";
		case SDLK_MINUS: return "Minus";
		case SDLK_EQUALS: return "Equals";
		case SDLK_BACKSPACE: return "BackSpace";
		case SDLK_TAB: return "Tab";
		case SDLK_q: return "Q";
		case SDLK_w: return "W";
		case SDLK_e: return "E";
		case SDLK_r: return "R";
		case SDLK_t: return "T";
		case SDLK_y: return "Y";
		case SDLK_u: return "U";
		case SDLK_i: return "I";
		case SDLK_o: return "O";
		case SDLK_p: return "P";
		case SDLK_LEFTBRACKET: return "[";
		case SDLK_RIGHTBRACKET: return "]";
		case SDLK_RETURN: return "Enter";
		case SDLK_LCTRL: return "LeftCtrl";
		case SDLK_a: return "A";
		case SDLK_s: return "S";
		case SDLK_d: return "D";
		case SDLK_f: return "F";
		case SDLK_g: return "G";
		case SDLK_h: return "H";
		case SDLK_j: return "J";
		case SDLK_k: return "K";
		case SDLK_l: return "L";
		case SDLK_SEMICOLON: return "Semicolon";
		case SDLK_QUOTE: return "Quote";
		case SDLK_QUOTEDBL: return "Quotedbl";
		case SDLK_BACKQUOTE: return "BackQuote";
		case SDLK_LSHIFT: return "LeftShift";
		case SDLK_BACKSLASH: return "BackSlash";
		case SDLK_z: return "Z";
		case SDLK_x: return "X";
		case SDLK_c: return "C";
		case SDLK_v: return "V";
		case SDLK_b: return "B";
		case SDLK_n: return "N";
		case SDLK_m: return "M";
		case SDLK_COMMA: return "Comma";
		case SDLK_PERIOD: return "Period";
		case SDLK_SLASH: return "Slash";
		case SDLK_RSHIFT: return "RightShift";
		case SDLK_ASTERISK: return "Asterisk";
		case SDLK_LALT: return "LeftAlt";
		case SDLK_SPACE: return "Space";
		case SDLK_CAPSLOCK: return "CapsLock";
		case SDLK_NUMLOCK: return "NumLock";
		case SDLK_SCROLLOCK: return "Scroll";
		case SDLK_KP7: return "NumPad 7";
		case SDLK_KP8: return "NumPad 8";
		case SDLK_KP9: return "NumPad 9";
		case SDLK_KP_MINUS: return "Minus";
		case SDLK_KP_MULTIPLY: return "Multiply";
		case SDLK_KP4: return "NumPad 4";
		case SDLK_KP5: return "NumPad 5";
		case SDLK_KP6: return "NumPad 6";
		case SDLK_KP_PLUS: return "Plus";
		case SDLK_KP1: return "NumPad 1";
		case SDLK_KP2: return "NumPad 2";
		case SDLK_KP3: return "NumPad 3";
		case SDLK_KP0: return "NumPad 0";
		case SDLK_KP_PERIOD: return "Period";
		case SDLK_KP_ENTER: return "Enter";
		case SDLK_RCTRL: return "RightCtrl";
		case SDLK_KP_DIVIDE: return "Divide";
		case SDLK_RALT: return "RightAlt";
		case SDLK_PAUSE: return "Pause";
		case SDLK_HOME: return "Home";
		case SDLK_UP: return "Up";
		case SDLK_PAGEUP: return "PgUp";
		case SDLK_LEFT: return "Left";
		case SDLK_RIGHT: return "Right";
		case SDLK_END: return "End";
		case SDLK_DOWN: return "Down";
		case SDLK_PAGEDOWN: return "PgDn";
		case SDLK_INSERT: return "Insert";
		case SDLK_DELETE: return "Delete";
		case SDLK_LSUPER: return "LeftWin";
		case SDLK_RSUPER: return "RightWin";

		// забой... чтобы не показывать, пока ищем
		case 0: return "?";
	}

	return 0;
}






// значения кнопок клавиатуры



char VirtualCodeChar1(int Num)
{

	switch (Num)
	{
		case SDLK_BACKQUOTE: return '~';
		case SDLK_1: return '!';
		case SDLK_2: return '@';
		case SDLK_3: return '#';
		case SDLK_4: return '$';
		case SDLK_5: return '%';
		case SDLK_6: return '^';
		case SDLK_7: return '&';
		case SDLK_8: return '*';
		case SDLK_9: return '(';
		case SDLK_0: return ')';
		case SDLK_MINUS: return '_';
		case SDLK_EQUALS: return '+';
		case SDLK_q: return 'Q';
		case SDLK_w: return 'W';
		case SDLK_e: return 'E';
		case SDLK_r: return 'R';
		case SDLK_t: return 'T';
		case SDLK_y: return 'Y';
		case SDLK_u: return 'U';
		case SDLK_i: return 'I';
		case SDLK_o: return 'O';
		case SDLK_p: return 'P';
		case SDLK_LEFTBRACKET: return '{';
		case SDLK_RIGHTBRACKET: return '}';
		case SDLK_BACKSLASH: return '|';
		case SDLK_a: return 'A';
		case SDLK_s: return 'S';
		case SDLK_d: return 'D';
		case SDLK_f: return 'F';
		case SDLK_g: return 'G';
		case SDLK_h: return 'H';
		case SDLK_j: return 'J';
		case SDLK_k: return 'K';
		case SDLK_l: return 'L';
		case SDLK_SEMICOLON: return ':';
		case SDLK_QUOTE: return '"';
		case SDLK_z: return 'Z';
		case SDLK_x: return 'X';
		case SDLK_c: return 'C';
		case SDLK_v: return 'V';
		case SDLK_b: return 'B';
		case SDLK_n: return 'N';
		case SDLK_m: return 'M';
		case SDLK_COMMA: return '<';
		case SDLK_PERIOD: return '>';
		case SDLK_SLASH: return '?';
		case SDLK_ASTERISK: return '*';
		case SDLK_SPACE: return ' ';

		case SDLK_KP7: return '7';
		case SDLK_KP8: return '8';
		case SDLK_KP9: return '9';
		case SDLK_KP_MINUS: return '-';
		case SDLK_KP4: return '4';
		case SDLK_KP5: return '5';
		case SDLK_KP6: return '6';
		case SDLK_KP_PLUS: return '+';
		case SDLK_KP_MULTIPLY: return '*';
		case SDLK_KP1: return '1';
		case SDLK_KP2: return '2';
		case SDLK_KP3: return '3';
		case SDLK_KP0: return '0';
		case SDLK_KP_PERIOD: return '.';
		case SDLK_KP_DIVIDE: return '/';
	}

	return 0;
}

char VirtualCodeChar2(int Num)
{

	switch (Num)
	{
		case SDLK_BACKQUOTE: return '`';
		case SDLK_1: return '1';
		case SDLK_2: return '2';
		case SDLK_3: return '3';
		case SDLK_4: return '4';
		case SDLK_5: return '5';
		case SDLK_6: return '6';
		case SDLK_7: return '7';
		case SDLK_8: return '8';
		case SDLK_9: return '9';
		case SDLK_0: return '0';
		case SDLK_MINUS: return '-';
		case SDLK_EQUALS: return '=';
		case SDLK_q: return 'q';
		case SDLK_w: return 'w';
		case SDLK_e: return 'e';
		case SDLK_r: return 'r';
		case SDLK_t: return 't';
		case SDLK_y: return 'y';
		case SDLK_u: return 'u';
		case SDLK_i: return 'i';
		case SDLK_o: return 'o';
		case SDLK_p: return 'p';
		case SDLK_LEFTBRACKET: return '[';
		case SDLK_RIGHTBRACKET: return ']';
		case SDLK_BACKSLASH: return '\\';
		case SDLK_a: return 'a';
		case SDLK_s: return 's';
		case SDLK_d: return 'd';
		case SDLK_f: return 'f';
		case SDLK_g: return 'g';
		case SDLK_h: return 'h';
		case SDLK_j: return 'j';
		case SDLK_k: return 'k';
		case SDLK_l: return 'l';
		case SDLK_SEMICOLON: return ';';
		case SDLK_QUOTE: return '"';
		case SDLK_z: return 'z';
		case SDLK_x: return 'x';
		case SDLK_c: return 'c';
		case SDLK_v: return 'v';
		case SDLK_b: return 'b';
		case SDLK_n: return 'n';
		case SDLK_m: return 'm';
		case SDLK_COMMA: return ',';
		case SDLK_PERIOD: return '.';
		case SDLK_SLASH: return '/';
		case SDLK_ASTERISK: return '*';
		case SDLK_SPACE: return ' ';

		case SDLK_KP7: return '7';
		case SDLK_KP8: return '8';
		case SDLK_KP9: return '9';
		case SDLK_KP_MINUS: return '-';
		case SDLK_KP4: return '4';
		case SDLK_KP5: return '5';
		case SDLK_KP6: return '6';
		case SDLK_KP_PLUS: return '+';
		case SDLK_KP_MULTIPLY: return '*';
		case SDLK_KP1: return '1';
		case SDLK_KP2: return '2';
		case SDLK_KP3: return '3';
		case SDLK_KP0: return '0';
		case SDLK_KP_PERIOD: return '.';
		case SDLK_KP_DIVIDE: return '/';
	}

	return 0;
}

char VirtualCodeChar3(int Num)
{

	switch (Num)
	{
		case SDLK_BACKQUOTE: return '`';
		case SDLK_1: return '1';
		case SDLK_2: return '2';
		case SDLK_3: return '3';
		case SDLK_4: return '4';
		case SDLK_5: return '5';
		case SDLK_6: return '6';
		case SDLK_7: return '7';
		case SDLK_8: return '8';
		case SDLK_9: return '9';
		case SDLK_0: return '0';
		case SDLK_MINUS: return '-';
		case SDLK_EQUALS: return '=';
		case SDLK_q: return 'Q';
		case SDLK_w: return 'W';
		case SDLK_e: return 'E';
		case SDLK_r: return 'R';
		case SDLK_t: return 'T';
		case SDLK_y: return 'Y';
		case SDLK_u: return 'U';
		case SDLK_i: return 'I';
		case SDLK_o: return 'O';
		case SDLK_p: return 'P';
		case SDLK_LEFTBRACKET: return '[';
		case SDLK_RIGHTBRACKET: return ']';
		case SDLK_BACKSLASH: return '\\';
		case SDLK_a: return 'A';
		case SDLK_s: return 'S';
		case SDLK_d: return 'D';
		case SDLK_f: return 'F';
		case SDLK_g: return 'G';
		case SDLK_h: return 'H';
		case SDLK_j: return 'J';
		case SDLK_k: return 'K';
		case SDLK_l: return 'L';
		case SDLK_SEMICOLON: return ';';
		case SDLK_QUOTE: return '"';
		case SDLK_z: return 'Z';
		case SDLK_x: return 'X';
		case SDLK_c: return 'C';
		case SDLK_v: return 'V';
		case SDLK_b: return 'B';
		case SDLK_n: return 'N';
		case SDLK_m: return 'M';
		case SDLK_COMMA: return ',';
		case SDLK_PERIOD: return '.';
		case SDLK_SLASH: return '/';
		case SDLK_ASTERISK: return '*';
		case SDLK_SPACE: return ' ';

		case SDLK_KP7: return '7';
		case SDLK_KP8: return '8';
		case SDLK_KP9: return '9';
		case SDLK_KP_MINUS: return '-';
		case SDLK_KP4: return '4';
		case SDLK_KP5: return '5';
		case SDLK_KP6: return '6';
		case SDLK_KP_PLUS: return '+';
		case SDLK_KP_MULTIPLY: return '*';
		case SDLK_KP1: return '1';
		case SDLK_KP2: return '2';
		case SDLK_KP3: return '3';
		case SDLK_KP0: return '0';
		case SDLK_KP_PERIOD: return '.';
		case SDLK_KP_DIVIDE: return '/';
	}

	return 0;
}



char VirtualCodeChar4(int Num)
{

	switch (Num)
	{
		case SDLK_BACKQUOTE: return '~';
		case SDLK_1: return '!';
		case SDLK_2: return '@';
		case SDLK_3: return '#';
		case SDLK_4: return '$';
		case SDLK_5: return '%';
		case SDLK_6: return '^';
		case SDLK_7: return '&';
		case SDLK_8: return '*';
		case SDLK_9: return '(';
		case SDLK_0: return ')';
		case SDLK_MINUS: return '_';
		case SDLK_EQUALS: return '+';
		case SDLK_q: return 'q';
		case SDLK_w: return 'w';
		case SDLK_e: return 'e';
		case SDLK_r: return 'r';
		case SDLK_t: return 't';
		case SDLK_y: return 'y';
		case SDLK_u: return 'u';
		case SDLK_i: return 'i';
		case SDLK_o: return 'o';
		case SDLK_p: return 'p';
		case SDLK_LEFTBRACKET: return '{';
		case SDLK_RIGHTBRACKET: return '}';
		case SDLK_BACKSLASH: return '|';
		case SDLK_a: return 'a';
		case SDLK_s: return 's';
		case SDLK_d: return 'd';
		case SDLK_f: return 'f';
		case SDLK_g: return 'g';
		case SDLK_h: return 'h';
		case SDLK_j: return 'j';
		case SDLK_k: return 'k';
		case SDLK_l: return 'l';
		case SDLK_SEMICOLON: return ':';
		case SDLK_QUOTE: return '"';
		case SDLK_z: return 'z';
		case SDLK_x: return 'x';
		case SDLK_c: return 'c';
		case SDLK_v: return 'v';
		case SDLK_b: return 'b';
		case SDLK_n: return 'n';
		case SDLK_m: return 'm';
		case SDLK_COMMA: return '<';
		case SDLK_PERIOD: return '>';
		case SDLK_SLASH: return '?';
		case SDLK_ASTERISK: return '*';
		case SDLK_SPACE: return ' ';

		case SDLK_KP7: return '7';
		case SDLK_KP8: return '8';
		case SDLK_KP9: return '9';
		case SDLK_KP_MINUS: return '-';
		case SDLK_KP4: return '4';
		case SDLK_KP5: return '5';
		case SDLK_KP6: return '6';
		case SDLK_KP_PLUS: return '+';
		case SDLK_KP_MULTIPLY: return '*';
		case SDLK_KP1: return '1';
		case SDLK_KP2: return '2';
		case SDLK_KP3: return '3';
		case SDLK_KP0: return '0';
		case SDLK_KP_PERIOD: return '.';
		case SDLK_KP_DIVIDE: return '/';
	}

	return 0;
}









char vw_VirtualCodeCharEN(int Num)
{
	// нажат CapsLock
	bool CapsLockOn = false;
	// делаем немного "сложно", чтобы избежать перфоменс варнинга на MSVC
	if((SDL_GetModState() & KMOD_CAPS) > 0) CapsLockOn = true;

	// нажат LeftShift или LeftShift
	if (SDL_GetModState() & KMOD_SHIFT)
	{
		if (VirtualCodeChar1(Num) != 0)
		{
			if (!CapsLockOn)
				return VirtualCodeChar1(Num);
			else
				return VirtualCodeChar4(Num);
		}
	}
	else
	{
		if (VirtualCodeChar2(Num) != 0)
		{
			if (!CapsLockOn)
				return VirtualCodeChar2(Num);
			else
				return VirtualCodeChar3(Num);
		}
	}

	return 0;
}












