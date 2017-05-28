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






bool wRBMouse = false;
bool wLBMouse = false;
int MouseX = 0;
int MouseY = 0;



//------------------------------------------------------------------------------------
// установка-получение статуса левой кнопки мышки
//------------------------------------------------------------------------------------
void vw_SetWindowLBMouse(bool NewStatus)
{
	wLBMouse = NewStatus;
}
bool vw_GetWindowLBMouse(bool ResetStatus)
{
	bool tmp = wLBMouse;
	if (ResetStatus) wLBMouse = false;
	return tmp;
}





//------------------------------------------------------------------------------------
// установка-получение статуса правой кнопки мышки
//------------------------------------------------------------------------------------
void vw_SetWindowRBMouse(bool NewStatus)
{
	wRBMouse = NewStatus;
}
bool vw_GetWindowRBMouse(bool ResetStatus)
{
	bool tmp = wRBMouse;
	if (ResetStatus) wRBMouse = false;
	return tmp;
}









//------------------------------------------------------------------------------------
// Получение данных положения курсора относительно клиентской области
//------------------------------------------------------------------------------------
void vw_SetMousePos(int X, int Y)
{
	MouseX = X;
	MouseY = Y;
}
int vw_GetMousePos(int *X, int *Y)
{
	// получаем размер клиентской области
	int buff[4];
	glGetIntegerv(GL_VIEWPORT, buff);
	float AWw = buff[2]*1.0f;
	float AHw = buff[3]*1.0f;

	float ARWidth;
	float ARHeight;
	bool ARFLAG = vw_GetAspectWH(&ARWidth, &ARHeight);

	*X = MouseX;
	*Y = MouseY;

	if (ARFLAG)
	{
		*X = (int)(MouseX * (ARWidth/AWw));
		*Y = (int)(MouseY * (ARHeight/AHw));
	}

	return 0;
}






//------------------------------------------------------------------------------------
// находится мышка в области или нет
//------------------------------------------------------------------------------------
bool vw_OnRect(RECT *MDetect)
{
	int MouseX, MouseY;
	vw_GetMousePos(&MouseX, &MouseY);


	if  (((MDetect->right  >= MouseX)&
		(MDetect->left<= MouseX)&
		(MDetect->bottom >= MouseY)&
		(MDetect->top<= MouseY)))
	{
		return true;
	}

	return false;
}





