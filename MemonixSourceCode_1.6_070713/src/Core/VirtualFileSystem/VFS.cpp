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


#include "VFS.h"


// Структура записи в системе VFS (для v1.2)
typedef struct
{
	DWORD	NameLen;	// Кол-во байт в имени...
	char	*Name;		// Имя записи (имя файла)
	int		Offset;		// Смещение начала файла относительно начала файловой системы
	int		Length;		// Длина файла в системе
	int		RealLength;	// Длина файла после распаковки
} eVFS_Entry;




char *VFSFileName = 0;		// Имя файла VFS
SDL_RWops *VFSFile = 0;		// Указатель на файл виртуальной системы
BYTE *dstVFS = 0;			// данные для архивир/разарх
BYTE *srcVFS = 0;			// данные для архивир/разарх
int  dsizeVFS = 0;			// данные для архивир/разарх
int  ssizeVFS = 0;			// данные для архивир/разарх
int  DataStartOffsetVFS = 0;// смещение данных в структуре VFS (без 8 байт смещ табл)
int  HeaderOffsetVFS = 0;	// смещение таблицы данных в структуре VFS
int  HeaderLengthVFS = 0;	// Длина таблицы данный структуры VFS
int  NumberOfFilesVFS = 0;	// количество файлов в VFS
bool VFSFileOpen = false;	// Датчик открытой VFS
eVFS_Entry *VFSdirArray = 0;// Массив записей VFS
char *ArhKeyVFS = 0;		// Ключ-упаковки
eFILE *StartFileVFS = 0;	// Указатель на первый файл в списке...
eFILE *EndFileVFS = 0;		// Указатель на последний файл в списке...

int VFSversion = 2;



int vw_DATAtoRLE(void);
int vw_DATAtoHAFF(void);
int vw_RLEtoDATA(int size);
int vw_HAFFtoDATA(int size);
int FileDetect(char **FileName);
int GetFileIDbyName(const char *FileName);











//------------------------------------------------------------------------------------
// Открытие (подключение) VFS
//------------------------------------------------------------------------------------
int vw_OpenVFS(const char *Name, const char *nArhKey)
{

    int POS = 0; // указатель позиции в буфере.
	BYTE *buff = 0;

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// открываем файл VFS
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	VFSFile = SDL_RWFromFile(Name, "rb");
    if (VFSFile == NULL)
    {
        printf("Can't find VFS file %s\n", Name);
        return -1; // ERROR
    }


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// выделяем память для имени
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	VFSFileName = new char[strlen(Name)+1];
	strcpy(VFSFileName, Name);


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// выделяем память для ArhKeyVFS
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	ArhKeyVFS = new char[strlen(nArhKey)+1];
	strcpy(ArhKeyVFS, nArhKey);



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Проверяем сигнатуру "VFS_" - 4 байт
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	char Sign[4];
	if(SDL_RWread(VFSFile, &Sign, 4, 1) == -1)
	{
		// если файл меньше, значит ошибка
		printf("VFS file size error %s\n", Name);
		goto vw_OpenVFS_Error;
	}
	if (strncmp(Sign, "VFS_", 4) != 0)
	{
		// нет сигнатуры
		printf("VFS file header error %s\n", Name);
		goto vw_OpenVFS_Error;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Bерсия - 4 байт
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	char Version[4];
	if(SDL_RWread(VFSFile, &Version, 4, 1) == -1)
	{
		printf("VFS file has wrong version %s\n", Name);
		goto vw_OpenVFS_Error;
	}
	// "v1.2"
	if (Version[3]=='2')VFSversion = 2;
	// "v1.1"
	if (Version[3]=='1')VFSversion = 1;



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Находим и записываем (если нужно) арх. последоват.
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	BYTE Temp;
	SDL_RWread(VFSFile, &Temp, 1, 1);
	DataStartOffsetVFS = 4+4+1;
	if (Temp != 0)// Читаем последовательность... т.к. она есть
	{
		delete [] ArhKeyVFS; ArhKeyVFS = 0;
		ArhKeyVFS = new char[Temp+1];
		ArhKeyVFS[Temp] = 0;// последний символ всегда ноль - конец строки
		SDL_RWread(VFSFile, ArhKeyVFS, Temp, 1);
		DataStartOffsetVFS += Temp;
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// читаем смещение таблицы данных VFS - 4 байт
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	HeaderOffsetVFS = SDL_ReadLE32(VFSFile);


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// читаем длину таблицы данных VFS
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	HeaderLengthVFS = SDL_ReadLE32(VFSFile);



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Читаем в буфер всю таблицу
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SDL_RWseek(VFSFile, HeaderOffsetVFS, SEEK_SET);
	buff = new BYTE[HeaderLengthVFS];
	SDL_RWread(VFSFile, buff, HeaderLengthVFS, 1);




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Находим кол-во записей
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	NumberOfFilesVFS = 0;
	while (POS<HeaderLengthVFS)
	{
		if (VFSversion == 2)
			POS = POS + 2 + (buff[POS+1]*0x100+buff[POS]) + 4 + 4 + 4;
		if (VFSversion == 1)
			POS = POS + 2 + (buff[POS+1]*0x100+buff[POS]) + 4 + 4;
		NumberOfFilesVFS ++;
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Резервируем память
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	VFSdirArray = new eVFS_Entry[NumberOfFilesVFS];




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Заполняем таблицу
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SDL_RWseek(VFSFile, HeaderOffsetVFS, SEEK_SET);
	POS = 0;
	for (int i=0; i<NumberOfFilesVFS; i++)
	{
		SDL_RWseek(VFSFile, 2, SEEK_CUR);
		VFSdirArray[i].NameLen = buff[POS+1]*0x100+buff[POS];
		VFSdirArray[i].Name = new char[VFSdirArray[i].NameLen+1];
		VFSdirArray[i].Name[VFSdirArray[i].NameLen] = 0;// последний символ всегда ноль - конец строки
		SDL_RWread(VFSFile, VFSdirArray[i].Name, VFSdirArray[i].NameLen, 1);
		VFSdirArray[i].Offset = SDL_ReadLE32(VFSFile);
		VFSdirArray[i].Length = SDL_ReadLE32(VFSFile);
		if (VFSversion == 2)
		{
			VFSdirArray[i].RealLength = SDL_ReadLE32(VFSFile);
			POS = POS + 2 + VFSdirArray[i].NameLen + 4 + 4 + 4;
		}
		if (VFSversion == 1)
			POS = POS + 2 + VFSdirArray[i].NameLen + 4 + 4;
	}

	// Освобождаем память...
	delete [] buff; buff = 0;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// VFS подключен - можно работать
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	VFSFileOpen = true;


	// выходим, все хорошо
	printf("VFS file was opened %s\n", Name);
	return 0;


	// была ошибка
vw_OpenVFS_Error:
	SDL_RWclose(VFSFile);
	delete [] VFSFileName; VFSFileName = 0;
	delete [] ArhKeyVFS; ArhKeyVFS = 0;
	return -1;
}






//------------------------------------------------------------------------------------
// Закрываем VFS
//------------------------------------------------------------------------------------
void vw_CloseVFS(void)
{

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// если VFS файл открыт, закрываем его
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (VFSFileOpen)
	{
		SDL_RWclose(VFSFile);
		VFSFileOpen = false;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// даже если файла не, все равно освобождаем память
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	for (int j = 0; j<NumberOfFilesVFS; j++)
	{
		delete [] (VFSdirArray[j].Name);
		VFSdirArray[j].Name = 0;
	}
	if (VFSdirArray != 0)
	{ delete [] VFSdirArray; VFSdirArray = 0; }




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// освобождаем память в ArhKeyVFS
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (ArhKeyVFS != 0)
	{	delete [] ArhKeyVFS; ArhKeyVFS = 0;	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// установка значений в исходные состояния
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	HeaderOffsetVFS = 0;
	DataStartOffsetVFS = 0;
	HeaderLengthVFS = 0;
	NumberOfFilesVFS = 0;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// освобождаем пямять в VFSFileName и пишем сообщение о закрытии
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (VFSFileName != 0)
	{
		printf("VFS file was closed %s\n", VFSFileName);
		delete [] VFSFileName; VFSFileName = 0;
	}
}






//------------------------------------------------------------------------------------
// Завершаем работу с VFS
//------------------------------------------------------------------------------------
void vw_ShutdownVFS(void)
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// закрываем все открытые файлы
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (StartFileVFS != 0)
	{
		// берем указатель на первый файл
		eFILE *Tmp = StartFileVFS;
		// просматриваем все файлы
		while (Tmp != 0)
		{
			eFILE *Tmp1 = Tmp->Next;
			vw_fclose(Tmp);
			Tmp = Tmp1;
		}
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// устанавливаем указатели в исходное состояние
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	StartFileVFS = 0;
	EndFileVFS = 0;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Закрываем VFS
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	vw_CloseVFS();
}


























//------------------------------------------------------------------------------------
// поиск номера файла в таблице VFS по имени
//------------------------------------------------------------------------------------
int GetFileIDbyName(const char *FileName)
{

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Если VFS файл не открыт - нам тут делать нечего
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (!VFSFileOpen) return -1;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// перебираем все записи в VFSdirArray в поисках номера
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	for(int i=0;i<NumberOfFilesVFS; i++ )
	{
		char *tmpName = 0;
		tmpName = new char[strlen(VFSdirArray[i].Name)+1];
		strcpy(tmpName, VFSdirArray[i].Name);
		char *tmpNAME = 0;
		tmpNAME = new char[strlen(VFSdirArray[i].Name)+1];
		strcpy(tmpNAME, tmpName);

		delete [] tmpName; tmpName = 0;

		if(vw_strcmp(FileName, tmpNAME) == 0)
		{
			delete [] tmpNAME; tmpNAME = 0;
			// нашли, передаем номер
			return i;
		}
		delete [] tmpNAME; tmpNAME = 0;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// запись не найдена
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	return -1;
}









//------------------------------------------------------------------------------------
// Проверка наличия файла в VFS или FS
//------------------------------------------------------------------------------------
int FileDetect(const char **FileName)
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// поиск в VFS, если номер есть - файл соотв. тоже есть
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (GetFileIDbyName(*FileName) > -1) return VFS_FILE_VFS;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// поиск в FS
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SDL_RWops *temp = SDL_RWFromFile(*FileName, "rb");
	// смогли открыть файл
	if (temp != NULL)
	{
		SDL_RWclose(temp);
        return VFS_FILE_FS;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Файл не найден
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	printf("Can't find the file %s\n", *FileName);
	return -1;
}










//------------------------------------------------------------------------------------
// Открытие файла в VFS (или подгонка файла FS к классу VFS)
//------------------------------------------------------------------------------------
bool fopen_busy = false;
eFILE *vw_fopen(const char *FileName)
{

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// возможно используется многопоточность, смотрим чтобы не портить данные
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	while (fopen_busy) SDL_Delay(1);
	// говорим, что работаем с это процедурой
	fopen_busy = true;


    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// проверяем наличие файла в системе
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	int ResTMP = FileDetect(&FileName);
	if (ResTMP == -1) goto FOP_ERR;



    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// файл в FS , подготовка данных и передача указателя на структуру
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    if (ResTMP == VFS_FILE_FS)
	{
		// Начальная подготовка структуры списка...
		eFILE *Temp = 0;
		Temp = new eFILE;

		// первый в списке...
		if (EndFileVFS == 0)
		{
			Temp->Prev = 0;
			Temp->Next = 0;
			StartFileVFS = Temp;
			EndFileVFS = Temp;
		}
		else // продолжаем заполнение...
		{
			Temp->Prev = EndFileVFS;
			Temp->Next = 0;
			EndFileVFS->Next = Temp;
			EndFileVFS = Temp;
		}

		Temp->PackLength = 0;
		Temp->Pos = 0;
		Temp->RealLength = 0;
		Temp->VFS_Offset = 0;

		// заносим имя файла
		Temp->Name = 0;
		Temp->Name = new char[strlen(FileName)+1];
		strcpy(Temp->Name, FileName);

		// открываем физ. файл, проверка в детекте...
		SDL_RWops * fTEMP = SDL_RWFromFile(FileName, "rb");

		// получаем размер файла
		SDL_RWseek(fTEMP, 0, SEEK_END);
		Temp->RealLength = SDL_RWtell(fTEMP);
		Temp->PackLength = Temp->RealLength;
		SDL_RWseek(fTEMP, 0, SEEK_SET);

		// резервируем память
		Temp->Data = 0;
		Temp->Data = new BYTE[Temp->RealLength];

		// плолучаем данные...
		SDL_RWread(fTEMP, Temp->Data, 1, Temp->RealLength);
		SDL_RWclose(fTEMP);

		// передаем указатель на структуру...
		fopen_busy = false;
		return Temp;
	}


    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// файл в VFS , подготовка данных и передача указателя на структуру
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (ResTMP == VFS_FILE_VFS)
	{
		// получаем номер файла в таблице VFS
		int Numb = GetFileIDbyName(FileName);

		// Начальная подготовка структуры списка...
		eFILE *Temp;
		Temp = new eFILE;

		// первый в списке...
		if (EndFileVFS == 0)
		{
			Temp->Prev = 0;
			Temp->Next = 0;
			StartFileVFS = Temp;
			EndFileVFS = Temp;
		}
		else // продолжаем заполнение...
		{
			Temp->Prev = EndFileVFS;
			Temp->Next = 0;
			EndFileVFS->Next = Temp;
			EndFileVFS = Temp;
		}

		Temp->PackLength = 0;
		Temp->Pos = 0;
		Temp->RealLength = 0;
		Temp->VFS_Offset = 0;

		Temp->Name = 0;
		Temp->Name = new char[strlen(FileName)+1];
		strcpy(Temp->Name, FileName);

		Temp->PackLength = VFSdirArray[Numb].Length;
		Temp->VFS_Offset = VFSdirArray[Numb].Offset;

		// резервируем память
		Temp->Data = 0;
		Temp->Data = new BYTE[Temp->PackLength];

		// плолучаем данные...
		SDL_RWseek(VFSFile, Temp->VFS_Offset, SEEK_SET);
		SDL_RWread(VFSFile, Temp->Data, Temp->PackLength, 1);
		Temp->RealLength = Temp->PackLength;


		// используем сжатие?
		if (!((ArhKeyVFS[0]=='0')&(strlen(ArhKeyVFS)==1)))
		{
			for (unsigned int i=0; i<strlen(ArhKeyVFS);i++)
			{
				char S = ArhKeyVFS[i];
				unsigned int cur_i = (int)strlen(ArhKeyVFS)-1;

				if (S == VFS_DATA_ARH_RLE)
				{
					ssizeVFS = Temp->RealLength;
					srcVFS = Temp->Data;
					if (i == cur_i && VFSversion == 2)
						vw_RLEtoDATA(VFSdirArray[Numb].RealLength);
					else
						vw_RLEtoDATA(0);
					srcVFS = 0;
					Temp->RealLength = dsizeVFS;
					delete [] Temp->Data; Temp->Data = 0;
					Temp->Data = dstVFS;
					dstVFS = 0;
				}
				if (S == VFS_DATA_ARH_HAFF)
				{
					ssizeVFS = Temp->RealLength;
					srcVFS = Temp->Data;
					if (i == cur_i && VFSversion == 2)
						vw_HAFFtoDATA(VFSdirArray[Numb].RealLength);
					else
						vw_HAFFtoDATA(0);
					srcVFS = 0;
					Temp->RealLength = dsizeVFS;
					delete [] Temp->Data; Temp->Data = 0;
					Temp->Data = dstVFS;
					dstVFS = 0;
				}
			}
		}

		// передаем указатель на структуру...
		fopen_busy = false;
		return Temp;
	}



    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// в системе нет такого файла, или какие-то проблемы
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
FOP_ERR:
	fopen_busy = false;
	return 0;
}










//------------------------------------------------------------------------------------
// Закрытие файла в VFS
//------------------------------------------------------------------------------------
bool fclose_busy = false;
int vw_fclose(eFILE *stream)
{

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// возможно используется многопоточность, смотрим чтобы не портить данные
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	while (fclose_busy) SDL_Delay(1);
	// говорим, что работаем с это процедурой
	fclose_busy = true;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// файл не открыли...закрывать нечего...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (stream == 0)
	{
		fclose_busy = false;
		return -1;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Освобождаем память
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (stream->Data != 0) {delete [] stream->Data; stream->Data = 0;}
	if (stream->Name != 0) {delete [] stream->Name; stream->Name = 0;}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Устанавливаем все у начальное состояние
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    stream->PackLength = 0;
	stream->Pos = 0;
	stream->RealLength = 0;
	stream->VFS_Offset =0;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// переустанавливаем указатели
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (StartFileVFS == stream) StartFileVFS = stream->Next;
	if (EndFileVFS == stream) EndFileVFS = stream->Prev;

	if (stream->Next != 0) stream->Next->Prev = stream->Prev;
		else if (stream->Prev != 0) stream->Prev->Next = 0;
	if (stream->Prev != 0) stream->Prev->Next = stream->Next;
		else if (stream->Next != 0) stream->Next->Prev = 0;



	delete stream; stream = 0;
	fclose_busy = false;
	return 0;
}








//------------------------------------------------------------------------------------
// чтение блока данных из файла в VFS
//------------------------------------------------------------------------------------
int vw_fread(void *buffer, int size, int count, eFILE *stream)
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// проверки
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (buffer == 0) return -1;
	if (stream == 0) return -1;
	if (stream->Data == 0) return -1;

	// Кол-во успешно считанных раз
	int SecCount = 0;

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// считываем данные
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	for (int i=0; i<count; i++)
	{
		// если можем прочитать следующий блок size размера - читаем
		if (size <= stream->RealLength - stream->Pos)
		{
			// считываем байты
			memcpy((BYTE*)buffer + SecCount*size, stream->Data + stream->Pos, size);
			// передвигаем текущий указатель
			stream->Pos += size;
			// устанавливаем успешное чтение
			SecCount++;
		}
		// иначе, уже достигли конца файла - выходим из цикла
		else break;
	}

	return SecCount;
}






//------------------------------------------------------------------------------------
// поиск (установка текущей позиции)
//------------------------------------------------------------------------------------
int vw_fseek(eFILE *stream, long offset, int origin)
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// проверкa
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (stream == 0) return -1;

	// изменяем значение указателя, согласно origin...
	switch (origin)
	{
		case SEEK_CUR:
		{
			if (stream->Pos + offset > stream->RealLength) return -1;
			stream->Pos += offset;
			break;
		}
		case SEEK_END:
		{
			if (stream->RealLength-offset < 0) return -1;
			stream->Pos = stream->RealLength-offset;
			break;
		}
		case SEEK_SET:
		{
			if (offset < 0 || offset > stream->RealLength) return -1;
			stream->Pos = offset;
			break;
		}
	}

	return stream->Pos;
}




//------------------------------------------------------------------------------------
// получить текущую позицию указателя...
//------------------------------------------------------------------------------------
int vw_ftell(eFILE *stream)
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// проверкa
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (stream == 0) return -1;

	return stream->Pos;
}
