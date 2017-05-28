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
void AttachTexture(eTexture* Texture);
void DetachTexture(eTexture* Texture);







//------------------------------------------------------------------------------------
// Освобождение памяти и удаление текстуры
//------------------------------------------------------------------------------------
void vw_ReleaseTexture(eTexture* Texture)
{
	// проверка входящих данных
	if (Texture == 0) return;

	// отключаем текстуру от менерджера текстур
	DetachTexture(Texture);

	// освобождаем память
	if (Texture->OffsetID != 0) {vw_DeleteTexture(Texture->OffsetID);Texture->OffsetID=0;};
	if (Texture->Name != 0) {delete [] Texture->Name; Texture->Name = 0;}
	delete Texture; Texture = 0;
}






//------------------------------------------------------------------------------------
// Переработка размеров...    ближайшая, большая четная или степень 2
//------------------------------------------------------------------------------------
static int power_of_two(int Num)
{
	int value = 1;

	while (value < Num)
	{
		value <<= 1;
	}
	return value;
}
void Resize(BYTE **DIB, eTexture *Texture)
{
	// берем размеры к которым нужно "подгонять"
	int powWidth = power_of_two(Texture->Width);
	int powHeight = power_of_two(Texture->Height);

	// нужно ли обрабатывать вообще?
	if (powWidth==Texture->Width && powHeight==Texture->Height) return;

	BYTE *DIBtemp = *DIB;
	*DIB = 0;
	*DIB = new BYTE[powWidth*powHeight*Texture->Bytes];

	// делаем все по цвету-прозначности + ставим все прозрачным
	BYTE ColorF[4];
	ColorF[0] = Texture->ARed;
	ColorF[1] = Texture->AGreen;
	ColorF[2] = Texture->ABlue;
	ColorF[3] = 0;//если Texture->Bytes == 4, его возьмем
	for (int i=0; i<powWidth*powHeight*Texture->Bytes; i+=Texture->Bytes)
	{
		memcpy(*DIB+i, ColorF, Texture->Bytes);
	}


	// находим отступ между строчками
	int stride = Texture->Width * Texture->Bytes;
	// должен быть приведен к DWORD построчно (чтобы не было проблем с нечетными данными)
	while((stride % 4) != 0) stride++;


	// вставляем исходный рисунок
	for (int y=0; y<Texture->Height; y++)
	{
		int st1 = (y*(powWidth))*Texture->Bytes;
		int st2 = (y*(stride));
		memcpy(*DIB+st1, DIBtemp+st2, stride);
	}



	// меняем значения текстуры
	Texture->Width = powWidth;
	Texture->Height = powHeight;
	// освобождаем память
	delete [] DIBtemp;
}











//------------------------------------------------------------------------------------
// Растягивание картинки, нужно устанавливать дополнительно...
//------------------------------------------------------------------------------------
void ResizeImage(int width, int height, BYTE **DIB, eTexture *Texture)
{
	if (width == Texture->Width && height == Texture->Height) return;

	int		i, j, x, y, offset_y, offset_x;

	// переносим во временный массив данные...
	BYTE *src = *DIB;
	BYTE *dst = 0;
	dst = new BYTE[width*height*Texture->Bytes];
	if (dst == 0) return;

	// растягиваем исходный массив (или сжимаем)
	for (j=0; j<height; j++)
	{
		y = (j * Texture->Height) / height;
		offset_y = y * Texture->Width;

		for (i=0; i<width; i++)
		{
			x = (i * Texture->Width) / width;
			offset_x = (offset_y + x) * Texture->Bytes;

			dst[(i+j*width)*Texture->Bytes] = src[(x+y*Texture->Width)*Texture->Bytes];
			dst[(i+j*width)*Texture->Bytes+1] = src[(x+y*Texture->Width)*Texture->Bytes+1];
			dst[(i+j*width)*Texture->Bytes+2] = src[(x+y*Texture->Width)*Texture->Bytes+2];
			if (Texture->Bytes == 4)
				dst[(i+j*width)*Texture->Bytes+3] = src[(x+y*Texture->Width)*Texture->Bytes+3];
		}
	}

	// меняем значения текстуры
	Texture->Width = width;
	Texture->Height = height;
	// освобождаем память
	delete [] src;
	// устанавливаем указатель на новый блок памяти
	*DIB = dst;
}









//------------------------------------------------------------------------------------
// Создание альфа канала
//------------------------------------------------------------------------------------
void CreateAlpha(BYTE **DIBRESULT, eTexture *Texture, int AlphaFlag)
{
	// находим отступ между строчками
	int stride = Texture->Width * 3;
	while((stride % 4) != 0) stride++;
	int stride2 = Texture->Width * 4;
	while((stride2 % 4) != 0) stride2++;

	// сохраняем во временном указателе
	BYTE *DIBtemp  = *DIBRESULT;
	BYTE *DIB = new BYTE[stride2*Texture->Height];

	int k1=0;
	int k2=0;

	// Формируем данные по цветам...
	BYTE GreyRedC = (BYTE)(((float)Texture->ARed / 255) * 76);
	BYTE GreyGreenC = (BYTE)(((float)Texture->AGreen / 255) * 150);
	BYTE GreyBlueC = (BYTE)(((float)Texture->ABlue / 255) * 28);
	BYTE GreyC = GreyBlueC+GreyGreenC+GreyRedC;

	for(int j1 = 0; j1 < Texture->Height;j1++)
	{

		k1 = stride*j1;// делаем правильное смещение при переходе
		k2 = stride2*j1;

		for(int j2 = 0; j2 < Texture->Width;j2++)
		{
			DIB[k2] = DIBtemp[k1];
			DIB[k2 + 1] = DIBtemp[k1 + 1];
			DIB[k2 + 2] = DIBtemp[k1 + 2];

			switch(AlphaFlag)
			{
				case TX_ALPHA_GREYSC:
				{
					// Формируем данные по цветам...
					BYTE GreyRed = (BYTE)(((float)DIB[k2+2] / 255) * 76);
					BYTE GreyGreen = (BYTE)(((float)DIB[k2+1] / 255) * 150);
					BYTE GreyBlue = (BYTE)(((float)DIB[k2] / 255) * 28);
					DIB[k2 + 3] = GreyBlue+GreyGreen+GreyRed;
					break;
				}
				case TX_ALPHA_EQUAL:
				{
					if ((Texture->ABlue==DIB[k2])&(Texture->AGreen==DIB[k2+1])&(Texture->ARed==DIB[k2+2])) DIB[k2+3] = 0;//Alpha
						else DIB[k2 + 3] = 255;
					break;
				}
				case TX_ALPHA_GEQUAL:
				{
					// Формируем данные по цветам...
					BYTE GreyRed = (BYTE)(((float)DIB[k2+2] / 255) * 76);
					BYTE GreyGreen = (BYTE)(((float)DIB[k2+1] / 255) * 150);
					BYTE GreyBlue = (BYTE)(((float)DIB[k2] / 255) * 28);
					BYTE Grey = GreyBlue+GreyGreen+GreyRed;

					if (GreyC >= Grey) DIB[k2+3] = 0;//Alpha
						else DIB[k2 + 3] = 255;
					break;
				}
				case TX_ALPHA_LEQUAL:
				{
					// Формируем данные по цветам...
					BYTE GreyRed = (BYTE)(((float)DIB[k2+2] / 255) * 76);
					BYTE GreyGreen = (BYTE)(((float)DIB[k2+1] / 255) * 150);
					BYTE GreyBlue = (BYTE)(((float)DIB[k2] / 255) * 28);
					BYTE Grey = GreyBlue+GreyGreen+GreyRed;

					if (GreyC <= Grey) DIB[k2+3] = 0;//Alpha
						else DIB[k2 + 3] = 255;
					break;
				}
				case TX_ALPHA_GREAT:
				{
					// Формируем данные по цветам...
					BYTE GreyRed = (BYTE)(((float)DIB[k2+2] / 255) * 76);
					BYTE GreyGreen = (BYTE)(((float)DIB[k2+1] / 255) * 150);
					BYTE GreyBlue = (BYTE)(((float)DIB[k2] / 255) * 28);
					BYTE Grey = GreyBlue+GreyGreen+GreyRed;

					if (GreyC > Grey) DIB[k2+3] = 0;//Alpha
						else DIB[k2 + 3] = 255;
					break;
				}
				case TX_ALPHA_LESS:
				{
					// Формируем данные по цветам...
					BYTE GreyRed = (BYTE)(((float)DIB[k2+2] / 255) * 76);
					BYTE GreyGreen = (BYTE)(((float)DIB[k2+1] / 255) * 150);
					BYTE GreyBlue = (BYTE)(((float)DIB[k2] / 255) * 28);
					BYTE Grey = GreyBlue+GreyGreen+GreyRed;

					if (GreyC < Grey) DIB[k2+3] = 0;//Alpha
						else DIB[k2 + 3] = 255;
					break;
				}
				default:
				{
					DIB[k2 + 3] = 255;
					break;
				}

			}

			k2 += 4;
			k1 += 3;
		}
	}

	delete [] DIBtemp;
	*DIBRESULT = DIB;
	Texture->Bytes = 4;
}





//------------------------------------------------------------------------------------
// Удаляем альфа канал
//------------------------------------------------------------------------------------
void DeleteAlpha(BYTE **DIBRESULT, eTexture *Texture)
{

	// находим отступ между строчками
	int stride = Texture->Width * 3;
	while((stride % 4) != 0) stride++;
	int stride2 = Texture->Width * 4;
	while((stride2 % 4) != 0) stride2++;

	// сохраняем во временном указателе
	BYTE *DIBtemp  = *DIBRESULT;
	BYTE *DIB = new BYTE[stride*Texture->Height];

	int k1=0;
	int k2=0;

	for(int j1 = 0; j1 < Texture->Height;j1++)
	{
		k1 = stride*j1;
		k2 = stride2*j1;

		for(int j2 = 0; j2 < Texture->Width;j2++)
		{
			DIB[k1] = DIBtemp[k2];
			DIB[k1 + 1] = DIBtemp[k2 + 1];
			DIB[k1 + 2] = DIBtemp[k2 + 2];

			k2 += 4;
			k1 += 3;
		}
	}

	delete [] DIBtemp;
	*DIBRESULT = DIB;
	Texture->Bytes = 3;
}












//------------------------------------------------------------------------------------
// проверка расширения файла
//------------------------------------------------------------------------------------
inline const char* TestFileExtension(const char *name, char *extension)
{
	if(name==0||extension==0) return 0;
	int LengthName=(int)strlen(name),LengthString=(int)strlen(extension);
	if(LengthName<LengthString) return 0;
	for(int i=LengthName-1;i>=0;i--)
		if(name[i]=='.')
			if(!strcmp(&name[i+1],extension)) return &name[i+1];
			else return 0;
	return 0;
}






//------------------------------------------------------------------------------------
// загрузка текстуры их файла и подключение к менеджеру текстур
//------------------------------------------------------------------------------------
eTexture* vw_LoadTexture(const char *nName, int LoadAs, int NeedResizeX, int NeedResizeY)
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
	Texture->Width = 0;
	Texture->Height = 0;
	Texture->TexturePrior = 0;

	// временно, файл текстуры
	eFILE *pFile = 0;
	// временно, получаем данные текстуры
	SDL_Surface *image;
	// временно, файл для работы
	SDL_RWops *RWFile = 0;
	// режим генерации текстуры
	int Mode = 0;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Сохраняем имя текстуры
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Texture->Name = new char[strlen(nName)+1];
	strcpy(Texture->Name, nName);


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Открываем файл
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	pFile = vw_fopen(Texture->Name);
	RWFile = SDL_RWFromConstMem(pFile->Data, pFile->RealLength);


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Ищем как грузить текстуру по расширению
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (LoadAs == AUTO_FILE)
	{
		if( TestFileExtension( nName, "tga" ) || TestFileExtension( nName, "TGA" ))
			LoadAs = TGA_FILE;
		if( TestFileExtension( nName, "bmp" ) || TestFileExtension( nName, "BMP" ))
			LoadAs = BMP_FILE;
		if( TestFileExtension( nName, "jpg" ) || TestFileExtension( nName, "JPG" ))
			LoadAs = JPG_FILE;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Загружаем текстуру
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	switch(LoadAs)
	{
		case BMP_FILE:
			image = IMG_LoadBMP_RW(RWFile);
			break;

		case TGA_FILE:
			image = IMG_LoadTGA_RW(RWFile);
			break;

		case JPG_FILE:
			image = IMG_LoadJPG_RW(RWFile);
			break;

		default:
			return 0;
			break;
	}
	if ( image == NULL )
	{
		printf("Unable to load %s: %s\n", nName, SDL_GetError());
		return 0;
	}




	// ставим правильный порядок цветов для генерации текстуры
	if (image->format->Rshift == 16 && image->format->Gshift == 8)
	{
		// order = BGR; BMP, TGA ...
		// нужно сделать RGB

		// находим отступ между строчками
		int stride = image->w * image->format->BytesPerPixel;
		// должен быть приведен к DWORD построчно (чтобы не было проблем с нечетными данными)
		while((stride % 4) != 0) stride++;

		BYTE *im_data = (BYTE *)image->pixels;
		BYTE tmp_data;

		int SM=0;
		for(int j=0; j<image->h; j++)
		{
			for(int i=0; i<image->w; i++)
			{
				tmp_data = im_data[SM + i*image->format->BytesPerPixel];
				im_data[SM + i*image->format->BytesPerPixel] = im_data[SM + i*image->format->BytesPerPixel+2];
				im_data[SM + i*image->format->BytesPerPixel+2] = tmp_data;
			}
			SM += stride;
		}

	}


	// вот теперь все готово, идем дальше
	Texture->Width = image->w;
	Texture->Height = image->h;
	Texture->Bytes = image->format->BytesPerPixel;

	// все, файлы нам больше не нужны
	SDL_RWclose(RWFile);
	vw_fclose(pFile);


	// находим отступ между строчками
	int stride = image->w * image->format->BytesPerPixel;
	// должен быть приведен к DWORD построчно (чтобы не было проблем с нечетными данными)
	while((stride % 4) != 0) stride++;

	// нам нужно разрушать-создавать этот массив, по этому выносим его отдельно!
	// иначе будут эксепшены, нельзя освободить память, зарезерв. в длл-ке
	BYTE *tmp_image;
	tmp_image = new BYTE[stride*Texture->Height];
	memcpy(tmp_image, image->pixels, stride*Texture->Height);
	SDL_FreeSurface(image);



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Делаем альфа канал
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Texture->Bytes == 4)
	{
		if (!AlphaTexMan)
			DeleteAlpha(&tmp_image, Texture);

	}
	if (Texture->Bytes == 3)
	{
		if (AlphaTexMan)
			CreateAlpha(&tmp_image, Texture, AFlagTexMan);
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Растягиваем, если есть запрос
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (NeedResizeX!=0 && NeedResizeY!=0)
		ResizeImage(NeedResizeX, NeedResizeY, &tmp_image, Texture);


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Сохраняем размеры картинки
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Texture->SrcWidth = Texture->Width;
	Texture->SrcHeight = Texture->Height;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Делаем подгонку по размерам, с учетом необходимости железа
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Resize(&tmp_image, Texture);



	// нужно перевернуть
	unsigned int iLineSize = sizeof(unsigned char) * Texture->Width * Texture->Bytes;
	unsigned char *pLine1  = 0;
	unsigned char *pLine2  = 0;
	unsigned char *pTemp   = 0;
	pTemp = new unsigned char[Texture->Width * Texture->Bytes];
	for (int i=0; i<Texture->Height / 2; i++)
	{
		// Set pointers to the lines that should be flipped
		pLine1 = tmp_image + Texture->Width * Texture->Bytes * i;
		pLine2 = tmp_image + Texture->Width * Texture->Bytes * (Texture->Height - i - 1);
		// Copy Line1 into Temp
		memcpy(pTemp, pLine1, iLineSize);
		// Copy Line2 into Line1
		memcpy(pLine1, pLine2, iLineSize);
		// Copy Temp into into Line2
		memcpy(pLine2, pTemp, iLineSize);
	}
	delete [] pTemp;



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Создаем текстуру
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Texture->OffsetID = vw_CreateTexture(tmp_image, Texture->Width, Texture->Height, MipMap, Texture->Bytes);





////////////////
/*
// проверка, что имеем...
	FILE *f = fopen("123.bmp", "wb");


	BITMAPINFOHEADER bih;
	BITMAPFILEHEADER bfh;

	int size = Texture->Width * Texture->Height * Texture->Bytes + sizeof(bfh) + sizeof(bih);

	memset((void*)&bfh, 0, sizeof(bfh));
	bfh.bfType = 'B'+('M'<<8);
	bfh.bfSize = size;
	bfh.bfOffBits = sizeof(bfh) + sizeof(bih);

	memset((void*)&bih, 0, sizeof(bih));
	bih.biSize = sizeof(bih);
	bih.biWidth = Texture->Width;
	bih.biHeight = Texture->Height;
	bih.biPlanes = 1;
	bih.biBitCount = (unsigned short)(Texture->Bytes * 8);
	bih.biCompression = BI_RGB;


	fwrite(&bfh, sizeof(bfh), 1, f);
	fwrite(&bih, sizeof(bih), 1, f);
	fwrite(tmp_image, Texture->Width * Texture->Height * Texture->Bytes, 1, f);

*/
	/*

if (!strcmp("DATA\\MODELS\\EARTHFIGHTER\\sf-illum01.tga", nName))
{
		FILE *f = fopen("123.tga", "wb");

	unsigned char tgaHeader[18];
	memset(tgaHeader, 0, sizeof(tgaHeader));
	tgaHeader[2] = 2;
	tgaHeader[12] = (unsigned char)Texture->Width;
	tgaHeader[13] = (unsigned char)((unsigned long)Texture->Width >> 8);
	tgaHeader[14] = (unsigned char)Texture->Height;
	tgaHeader[15] = (unsigned char)((unsigned long)Texture->Height >> 8);
	tgaHeader[16] = Texture->Bytes*8;

	int size = Texture->Width * Texture->Height * Texture->Bytes + 18;
	fwrite(&tgaHeader, 18, 1, f);
	fwrite(tmp_image, size, 1, f);


	fclose(f);
}*/

////////////////



	// освобождаем память
	delete [] tmp_image;

	// присоединяем текстуру к менеджеру текстур
	AttachTexture(Texture);
	printf("Ok ... %s\n", Texture->Name);
	return Texture;
}







//------------------------------------------------------------------------------------
// быстрая установка текстуры и ее параметров
//------------------------------------------------------------------------------------
void vw_SetTextureT(DWORD Stage, eTexture *Tex)
{
	if (Tex == 0) return;

	vw_SetTextureV(Stage, Tex);
	vw_SetTexFiltering(Stage, Tex->Filtering);
	vw_SetTexAddressMode(Stage, Tex->Address_Mode);
	vw_SetTexAlpha(true, 0.1f);
}
