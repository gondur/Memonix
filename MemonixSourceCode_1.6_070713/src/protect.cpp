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

#ifdef WIN32




char*	LocalHardwareID		= NULL;
char*	UserName			= NULL;







//------------------------------------------------------------------------------------
// получение из энвелопера данных
//------------------------------------------------------------------------------------
void __declspec(dllexport) GetHardwareID(char*	HardwareID)
{
    LocalHardwareID = HardwareID;
}
//------------------------------------------------------------------------------------
// получение из энвелопера данных
//------------------------------------------------------------------------------------
void __declspec(dllexport) __stdcall GetRegistrationInformation(char* NewUserName)
{
	UserName = NewUserName;
}












bool ProtectEnvelopeCheck1()
{
	#include "asprotect\CppEnvelopeCheckFunc.inc"

	return true;
}




// Проверка присутствия защиты...
bool ProtectEnvelopeCheck2()
{
	if (LocalHardwareID==NULL) return false;
	// для версии 1.31 всегда 12... на всякий случай - 10...
	if (strlen(LocalHardwareID)<10) return false;

	return true;
}





bool ProtectEnvelopeCheck3()
{
REG_CRYPT_BEGIN
	// только для проверки в зарегистрированном состоянии...
	if (UserName==NULL) return false;
	// поставить считывание на рег имя.
	// если менее 10 букв - бред...
	if (strlen(UserName)<10) return false;
REG_CRYPT_END

	return true;
}







#endif // WIN32
