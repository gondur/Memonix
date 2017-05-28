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



eFont *StartFontMan = 0;// Указатель на первый фонт в списке...
eFont *EndFontMan = 0;	// Указатель на последний фонт в списке...





//------------------------------------------------------------------------------------
// Освобождение памяти и удаление фонта
//------------------------------------------------------------------------------------
void vw_ReleaseFont(eFont* Font)
{
	// проверка входящих данных
	if (Font == 0) return;

	// отключаем фонт от менерджера текстур
	// переустанавливаем указатели...
	if (StartFontMan == Font) StartFontMan = Font->Next;
	if (EndFontMan == Font) EndFontMan = Font->Prev;


	if (Font->Next != 0) Font->Next->Prev = Font->Prev;
		else if (Font->Prev != 0) Font->Prev->Next = 0;
	if (Font->Prev != 0) Font->Prev->Next = Font->Next;
		else if (Font->Next != 0) Font->Next->Prev = 0;


	// освобождаем память
	if (Font->Texture != 0) vw_ReleaseTexture(Font->Texture);
	delete [] Font; Font = 0;
}












//------------------------------------------------------------------------------------
// Освобождение памяти
//------------------------------------------------------------------------------------
void vw_ReleaseAllFonts()
{
	if (StartFontMan != 0)
	{
		// Чистка памяти...
		eFont *Tmp;
		eFont *Tmp1;
		Tmp = StartFontMan;

		while (Tmp->Next != 0)
		{
			Tmp1 = Tmp->Next;
			vw_ReleaseFont(Tmp);
			Tmp = Tmp1;
		}
		vw_ReleaseFont(Tmp);
	}

	StartFontMan = 0;
	EndFontMan = 0;
}













//------------------------------------------------------------------------------------
// загрузка фонта и подключение его к менеджеру
//------------------------------------------------------------------------------------
eFont*	vw_CreateFont(int LoadAs, char *FontName, int FontSize, DWORD TextColor, DWORD BkColor)
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Cоздаем объект
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	eFont *Font;
	Font = new eFont;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// инициализация всех переменных
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Font->Size = FontSize;
	Font->Next = 0;
	Font->Prev = 0;
	Font->Texture = 0;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// загружаем текстуру
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Font->Texture != 0) vw_ReleaseTexture(Font->Texture);
	Font->Texture = vw_LoadTexture(FontName, LoadAs);



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// подключаем фонт к менеджеру
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// первый в списке...
	if (EndFontMan == 0)
	{
		Font->Prev = 0;
		Font->Next = 0;
		StartFontMan = Font;
		EndFontMan = Font;
	}
	else // продолжаем заполнение...
	{
		Font->Prev = EndFontMan;
		Font->Next = 0;
		EndFontMan->Next = Font;
		EndFontMan = Font;
	}

	return Font;
}













//------------------------------------------------------------------------------------
// печать текста
//------------------------------------------------------------------------------------
void vw_Print(eFont* Font, float X, float Y, float FlattenWidth, float MaxWidth, int CharSet, int Corner, float Transparent, const char *Text, ...)
{
// FlattenWidth - максимальная, ровнять по этой ширине
// MaxWidth - если больше этого значения - не выводить.

	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (Text == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, Text);									// Parses The String For Variables
	    vsprintf(text, Text, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);

	float Popr = 0;
	int tx1 =0, ty1=0, tx2=0, ty2=0;

	int SpaceCount = 0;//кол-во пробелов...
	float TextWidth = 0;//размер текста без пробелов..
	float Space = 0; // размер пробела...

	//	если нужно равнять - считаем значения пробелов...
	if (FlattenWidth != 0)
	{
		for (unsigned int i=0; i<strlen(text); i++)
			{
				float cx;
				float cy;
				if (CharSet)
				{
					cx= ((text[i]-32+128)%16)/16.0f;
					cy= ((text[i]-32+128)/16)/16.0f;
				}
				else
				{
					cx= ((text[i]-32)%16)/16.0f;
					cy= ((text[i]-32)/16)/16.0f;
				}
				tx1 = (int)(cx*Font->Texture->Width);
				ty1 = (int)((cy)*Font->Texture->Height);
				tx2 = (int)((cx+0.0625f)*Font->Texture->Width);
				ty2 = (int)((cy+0.0625f)*Font->Texture->Height);



				switch (text[i])
				{

				case ' ': SpaceCount++;break;
				case '.':
				case ',':
				case ':':
				case ';':
					//tx1 +=10;
					//tx2 -=3;
				default:
					TextWidth+= (int)(tx2-tx1+(Font->Size - Font->Texture->Width/16.0f) - Font->Size/3.0f);
				}

			}


		Space = (FlattenWidth - TextWidth)/SpaceCount;

	}
	else
	{
			{
				float cx;
				float cy;
				if (CharSet)
				{
					cx= ((' '-32+128)%16)/16.0f;
					cy= ((' '-32+128)/16)/16.0f;
				}
				else
				{
					cx= ((' '-32)%16)/16.0f;
					cy= ((' '-32)/16)/16.0f;
				}
				tx1 = (int)(cx*Font->Texture->Width);
				ty1 = (int)((cy)*Font->Texture->Height);
				tx2 = (int)((cx+0.0625f)*Font->Texture->Width);
				ty2 = (int)((cy+0.0625f)*Font->Texture->Height);


				Space = (tx2-tx1+(Font->Size - Font->Texture->Width/16.0f) - Font->Size/3.0f);

			}

	}






	for (unsigned int i=0; i<strlen(text); i++)
	{
		RECT DstRest;

		{
			float cx;
			float cy;
			if (CharSet)
			{
				cx= ((text[i]-32+128)%16)/16.0f;
				cy= ((text[i]-32+128)/16)/16.0f;
			}
			else
			{
				cx= ((text[i]-32)%16)/16.0f;
				cy= ((text[i]-32)/16)/16.0f;
			}
			tx1 = (int)(cx*Font->Texture->Width);
			ty1 = (int)((cy)*Font->Texture->Height);
			tx2 = (int)((cx+0.0625f)*Font->Texture->Width);
			ty2 = (int)((cy+0.0625f)*Font->Texture->Height);

			RECT SrcRest;
			SetRect(&SrcRest,tx1, ty1,tx2, ty2);
			SetRect(&DstRest,(int)(X+Popr), (int)Y, (int)(X+Popr+Font->Size), (int)Y+Font->Size);
			switch (text[i])
			{
				case '.':
				case ',':
				case ':':
				case ';':
					SetRect(&SrcRest,tx1+2, ty1, tx2-2, ty2);
					SetRect(&DstRest,(int)(X+Popr-2), (int)Y, (int)(X+Popr+Font->Size-5), (int)Y+Font->Size);
			}


			if (FlattenWidth != 0 && text[i]==' ')
			{
				Popr += Space;
			}
			else
			{
				if (MaxWidth!=0)//если есть ограничитель...
				{
					if (MaxWidth>=DstRest.right)
					vw_DrawTransparent(&DstRest, &SrcRest, Font->Texture, true, Transparent, 0, Corner);
				}
				else
					vw_DrawTransparent(&DstRest, &SrcRest, Font->Texture, true, Transparent, 0, Corner);

				switch (text[i])
				{
					case '.':
					case ',':
					case ':':
					case ';':
						Popr -= 6;
				}
				Popr += (int)(tx2-tx1+(Font->Size - Font->Texture->Width/16.0f) - Font->Size/3.0f);
			}
		}


//		Popr += (int)(tx2-tx1+(FSize - FontBase->Width/16.0f) - FSize/3.0f);
	}

}

