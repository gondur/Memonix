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

#include "../../Core.h"
#include "Texture.h"


extern int FilteringTexMan;
extern int Address_ModeTexMan;
extern BYTE ARedTexMan;
extern BYTE AGreenTexMan;
extern BYTE ABlueTexMan;

extern bool MipMap;
extern int  AFlagTexMan;
extern bool AlphaTexMan;
void CreateAlpha(BYTE **DIBRESULT, eTexture *Texture, int AlphaFlag);
void Resize(BYTE **DIB, eTexture *Texture);
void AttachTexture(eTexture* Texture);






//------------------------------------------------------------------------------------
// Переход на создание текстуры из DIB массива...
//------------------------------------------------------------------------------------
eTexture* vw_LoadTextureMem(const char *nName, BYTE *nDIB, int nWidth, int nHeight, int Colors)
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Cоздаем объект
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	eTexture *Texture;
	Texture = new eTexture;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Начальные установки текстуры
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Texture->ARed = ARedTexMan;
	Texture->AGreen = AGreenTexMan;
	Texture->ABlue = ABlueTexMan;
	Texture->Prev = 0;
	Texture->Next = 0;
	Texture->Num = 0;
	Texture->Name = 0;
	Texture->OffsetID = 0;
	Texture->Filtering = FilteringTexMan;
	Texture->Address_Mode = Address_ModeTexMan;
	Texture->Bytes = Colors;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Сохраняем имя текстуры
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Texture->Name = new char[strlen(nName)+1];
	strcpy(Texture->Name, nName);


	Texture->Width = nWidth;
	Texture->Height = nHeight;
	Texture->SrcWidth = Texture->Width;
	Texture->SrcHeight = Texture->Height;
	// временно, для создания текстуры
	BYTE *DIB = 0;

	if (Texture->Bytes == 4)
	{
		DIB = new BYTE[Texture->Width*Texture->Height*4];
		memcpy( DIB, nDIB, Texture->Width*Texture->Height*4);

		// исключительный случай, альфа есть, но она не нужна
		if (!AlphaTexMan)
		for(int i = 0; i < Texture->Width*Texture->Height; i++)
		{
			DIB[i*4+3] = 255;
		}
	}

	// если 24 битная картинка...
	if (Texture->Bytes == 3)
	{
		DIB = new BYTE[Texture->Width*Texture->Height*3];
		memcpy( DIB, nDIB, Texture->Width*Texture->Height*3);

		if (AlphaTexMan)
			CreateAlpha(&DIB, Texture, AFlagTexMan);
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Делаем подгонку по размерам, с учетом необходимости железа
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Resize(&DIB, Texture);


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Создаем текстуру
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Texture->OffsetID = vw_CreateTexture(DIB, Texture->Width, Texture->Height, MipMap, 4);


	// удаляем массив, если можно...
	delete [] DIB; DIB = 0;

	// присоединяем текстуру к менеджеру текстур
	AttachTexture(Texture);

	return Texture;
}

