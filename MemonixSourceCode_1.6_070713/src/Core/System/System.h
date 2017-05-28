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



#ifndef CoreSystem_H
#define CoreSystem_H

#include "../../Core.h"




// открываем браузер
bool	vw_OpenBrouser(char *url);



// работа со временем
void 	vw_InitTime();
float 	vw_GetTime(int TimeThread = 0);
void 	vw_StopTime();
void 	vw_StartTime();
void 	vw_SetTimeThreadSpeed(int TimeThread=0, float NewSpeed=1.0f);
float 	vw_GetTimeThreadSpeed(int TimeThread=0);



// работа с клавиатурой
bool	vw_GetKeys(int Num);
void	vw_SetKeys(int Num, bool NewKeyStatus);
int 	GetMaxKeys();
char* 	vw_VirtualCodeName(int Num);
char 	vw_VirtualCodeCharEN(int Num);



// работа с мышкой
int		vw_GetMousePos(int *X, int *Y);
bool	vw_GetWindowLBMouse(bool ResetStatus);
bool	vw_GetWindowRBMouse(bool ResetStatus);
void	vw_SetWindowLBMouse(bool NewStatus);
void	vw_SetWindowRBMouse(bool NewStatus);
void	vw_SetMousePos(int X, int Y);
bool	vw_OnRect(RECT *MDetect);




#endif // CoreSystem_H
