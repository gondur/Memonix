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




//------------------------------------------------------------------------------------
// переменные... глобальные
//------------------------------------------------------------------------------------

// счетчик времени в игре
Uint32 GameTime;
Uint32 GameTimeInit;

// защелка победы
bool GameWin;
// поле, которое выводим...
int FieldData[8][8];
int FieldDataPair[8][8];
int SetFieldData[8][8];
int StartPanelPos;
int EndPanelPos;
int SetPanelPos;
int SearchFor = 0;// для панели - вывод
// для пазла
int CurentFoto=0;
int CurentFotoNum=1;
// чтобы знать, что было перед этим, и удалить..
int lastgame=-1;
void ReleaseGameDate(int Game);

// чтобы делать сброс не чаще раза в 0.3с
Uint32 ResetTickCount = 0;
float ResetTransp = 1.0f;
bool ResetTranspOn = false;

// текущий цвет в мазаике
int CurColor = 0;





//------------------------------------------------------------------------------------
// переменные... локальные
//------------------------------------------------------------------------------------

// начальное время для обратного отсчета
Uint32 GameStartTimeInit;
// текущие позиции в панели выбора и установку...
int GameMask=0;













void ReleaseGameDate(int Game)
{
	if (Game == 0)
	{
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\1_1.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\1_2.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\1_3.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\1_4.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\1_5.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\1_6.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\1_7.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\1_8.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\1_9.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\1_0.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\2_1.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\2_2.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\2_3.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\2_4.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\2_5.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\2_6.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\2_7.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\2_8.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\2_9.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\2_0.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\3_1.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\3_2.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\3_3.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\3_4.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\3_5.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\3_6.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\3_7.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\3_8.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\3_9.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\3_0.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\4_1.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\4_2.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\4_3.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\4_4.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\4_5.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\4_6.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\4_7.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\4_8.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\4_9.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\4_0.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\5_1.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\5_2.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\5_3.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\5_4.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\5_5.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\5_6.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\5_7.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\5_8.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\5_9.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\MOSAIC\\5_0.bmp"));

	}
	if (Game == 1)
	{

		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\61.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\62.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\63.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\64.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\65.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\66.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\67.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\68.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\70.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\71.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\72.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\73.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\74.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\76.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\77.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\78.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\79.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\80.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\81.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\83.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\2_03\\60.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\2_03\\75.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_01_50\\a-09.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_01_50\\a-17.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_02_30\\a-15.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_03\\a-01.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_03\\a-03.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_03\\a-04.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_03\\a-12.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_03\\a-13.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_03\\a-14.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_05_50\\a-06.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_01_50\\a-02.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_02_30\\a-11.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_03\\a-19.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_04_30\\a-10.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_05_50\\a-05.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\12_05_50\\a-16.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\2_01_50\\a-08.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\2_01_50\\10.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\2_02_30\\08.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\2_03\\01.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\2_03\\02.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\2_03\\03.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\2_03\\04.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\2_03\\05.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\2_03\\06.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\2_03\\07.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\2_04_30\\09.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\2_05_50\\a-07.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\2_05_50\\11.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_02_30\\19.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_03\\13.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_03\\14.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_03\\15.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_03\\16.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_03\\17.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_03\\20.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_03\\21.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_03\\a-18.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\1_04_30\\18.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\3_01_50\\35.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\3_01_50\\39.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\3_02_30\\41.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\3_03\\32.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\3_04_30\\40.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\3_05_50\\37.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\3_05_50\\38.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_02\\34.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_02\\46.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_02\\50.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_02\\b-04.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_03\\33.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_03\\42.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_03\\43.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_03\\44.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_03\\47.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_03\\48.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_03\\49.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_03\\b-01.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_03\\b-02.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_03\\b-03.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_03\\b-06.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_04\\36.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_04\\45.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_04\\51.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\BUILDER\\4_04\\b-05.bmp"));

	}
	if (Game == 2)
	{

		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-001.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-002.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-003.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-004.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-005.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-006.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-007.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-008.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-009.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-010.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-011.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-012.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-013.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-014.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-016.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-017.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-018.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-019.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-020.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-021.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-022.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-023.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-024.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-025.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-026.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-027.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-028.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-029.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-030.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-031.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-032.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-033.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-034.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-035.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-036.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-037.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-038.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-039.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-040.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-041.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-042.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-043.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-044.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-045.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-046.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-047.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-048.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-049.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-050.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-051.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-052.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-053.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-054.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-055.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-056.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-057.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-058.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-059.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-060.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-061.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-062.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-063.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-064.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-065.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-066.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-067.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-068.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-069.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-070.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-071.bmp"));
		vw_ReleaseTexture(vw_FindTextureByName("DATA\\PAIR\\toys-072.bmp"));

	}
	if (Game == 3)
	{

		// если повторная генерация - удаляем предыдущие...
		vw_ReleaseTexture(vw_FindTextureByNum(CurentFoto));
		vw_ReleaseTexture(vw_FindTextureByName("00"));
		vw_ReleaseTexture(vw_FindTextureByName("01"));
		vw_ReleaseTexture(vw_FindTextureByName("02"));
		vw_ReleaseTexture(vw_FindTextureByName("03"));
		vw_ReleaseTexture(vw_FindTextureByName("04"));
		vw_ReleaseTexture(vw_FindTextureByName("05"));
		vw_ReleaseTexture(vw_FindTextureByName("06"));
		vw_ReleaseTexture(vw_FindTextureByName("07"));
		vw_ReleaseTexture(vw_FindTextureByName("10"));
		vw_ReleaseTexture(vw_FindTextureByName("11"));
		vw_ReleaseTexture(vw_FindTextureByName("12"));
		vw_ReleaseTexture(vw_FindTextureByName("13"));
		vw_ReleaseTexture(vw_FindTextureByName("14"));
		vw_ReleaseTexture(vw_FindTextureByName("15"));
		vw_ReleaseTexture(vw_FindTextureByName("16"));
		vw_ReleaseTexture(vw_FindTextureByName("17"));
		vw_ReleaseTexture(vw_FindTextureByName("20"));
		vw_ReleaseTexture(vw_FindTextureByName("21"));
		vw_ReleaseTexture(vw_FindTextureByName("22"));
		vw_ReleaseTexture(vw_FindTextureByName("23"));
		vw_ReleaseTexture(vw_FindTextureByName("24"));
		vw_ReleaseTexture(vw_FindTextureByName("25"));
		vw_ReleaseTexture(vw_FindTextureByName("26"));
		vw_ReleaseTexture(vw_FindTextureByName("27"));
		vw_ReleaseTexture(vw_FindTextureByName("30"));
		vw_ReleaseTexture(vw_FindTextureByName("31"));
		vw_ReleaseTexture(vw_FindTextureByName("32"));
		vw_ReleaseTexture(vw_FindTextureByName("33"));
		vw_ReleaseTexture(vw_FindTextureByName("34"));
		vw_ReleaseTexture(vw_FindTextureByName("35"));
		vw_ReleaseTexture(vw_FindTextureByName("36"));
		vw_ReleaseTexture(vw_FindTextureByName("37"));
		vw_ReleaseTexture(vw_FindTextureByName("40"));
		vw_ReleaseTexture(vw_FindTextureByName("41"));
		vw_ReleaseTexture(vw_FindTextureByName("42"));
		vw_ReleaseTexture(vw_FindTextureByName("43"));
		vw_ReleaseTexture(vw_FindTextureByName("44"));
		vw_ReleaseTexture(vw_FindTextureByName("45"));
		vw_ReleaseTexture(vw_FindTextureByName("46"));
		vw_ReleaseTexture(vw_FindTextureByName("47"));
		vw_ReleaseTexture(vw_FindTextureByName("50"));
		vw_ReleaseTexture(vw_FindTextureByName("51"));
		vw_ReleaseTexture(vw_FindTextureByName("52"));
		vw_ReleaseTexture(vw_FindTextureByName("53"));
		vw_ReleaseTexture(vw_FindTextureByName("54"));
		vw_ReleaseTexture(vw_FindTextureByName("55"));
		vw_ReleaseTexture(vw_FindTextureByName("56"));
		vw_ReleaseTexture(vw_FindTextureByName("57"));
		vw_ReleaseTexture(vw_FindTextureByName("60"));
		vw_ReleaseTexture(vw_FindTextureByName("61"));
		vw_ReleaseTexture(vw_FindTextureByName("62"));
		vw_ReleaseTexture(vw_FindTextureByName("63"));
		vw_ReleaseTexture(vw_FindTextureByName("64"));
		vw_ReleaseTexture(vw_FindTextureByName("65"));
		vw_ReleaseTexture(vw_FindTextureByName("66"));
		vw_ReleaseTexture(vw_FindTextureByName("67"));
		vw_ReleaseTexture(vw_FindTextureByName("70"));
		vw_ReleaseTexture(vw_FindTextureByName("71"));
		vw_ReleaseTexture(vw_FindTextureByName("72"));
		vw_ReleaseTexture(vw_FindTextureByName("73"));
		vw_ReleaseTexture(vw_FindTextureByName("74"));
		vw_ReleaseTexture(vw_FindTextureByName("75"));
		vw_ReleaseTexture(vw_FindTextureByName("76"));
		vw_ReleaseTexture(vw_FindTextureByName("77"));

	}

}













//------------------------------------------------------------------------------------
// загрузка нужного для конкретной игры...+ удаление лишнего...
//------------------------------------------------------------------------------------
void LoadGameData()
{
	// для задержки, чтобы рисовать не менее 0.5 секунды
	Uint32 gettick;
	if (lastgame!=Setup.Type) gettick = SDL_GetTicks();


	if (lastgame == 0 && Setup.Type != 0)
	{
		ReleaseGameDate(0);
	}
	if (Setup.Type == 0 && lastgame != 0)
	{

		if (Setup.UseUserMosaicAddon)
		{
			vw_CloseVFS();
			if (0 != vw_OpenVFS(Setup.UserMosaicAddon, "1"))
			{
				vw_OpenVFS(VFSFileNamePath, "1");
				Setup.UseUserMosaicAddon = false;
			}
		}

		vw_SetClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		vw_BeginRendering();
		vw_Start2DMode(-1,1);
			RECT SrcRest;
			SetRect(&SrcRest, 0, 0, 226, 120);
			vw_Draw(287,236,&SrcRest, vw_FindTextureByName("DATA\\LoadingPanel.bmp"), false);
		vw_End2DMode();
		vw_EndRendering();

		vw_BeginRendering();
		vw_Start2DMode(-1,1);
			SetRect(&SrcRest, 0, 0, 226, 120);
			vw_Draw(287,236,&SrcRest, vw_FindTextureByName("DATA\\LoadingPanel.bmp"), false);
		vw_End2DMode();
		vw_EndRendering();

		vw_SetTextureProp(RI_TEXTURE_NONE, RI_CLAMP, false, TX_ALPHA_EQUAL, false);

		vw_LoadTexture("DATA\\MOSAIC\\1_1.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\1_2.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\1_3.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\1_4.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\1_5.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\1_6.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\1_7.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\1_8.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\1_9.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\1_0.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\2_1.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\2_2.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\2_3.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\2_4.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\2_5.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\2_6.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\2_7.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\2_8.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\2_9.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\2_0.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\3_1.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\3_2.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\3_3.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\3_4.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\3_5.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\3_6.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\3_7.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\3_8.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\3_9.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\3_0.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\4_1.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\4_2.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\4_3.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\4_4.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\4_5.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\4_6.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\4_7.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\4_8.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\4_9.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\4_0.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\5_1.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\5_2.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\5_3.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\5_4.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\5_5.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\5_6.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\5_7.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\5_8.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\5_9.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\MOSAIC\\5_0.bmp", BMP_FILE);

		if (Setup.UseUserMosaicAddon)
		{
			vw_CloseVFS();
			vw_OpenVFS(VFSFileNamePath, "1");
		}

	}

	if (lastgame == 1 && Setup.Type != 1)
	{
		ReleaseGameDate(1);
	}
	if (Setup.Type == 1 && lastgame != 1)
	{

		if (Setup.UseUserBuilderAddon)
		{
			vw_CloseVFS();
			if (0 != vw_OpenVFS(Setup.UserBuilderAddon, "1"))
			{
				vw_OpenVFS(VFSFileNamePath, "1");
				Setup.UseUserBuilderAddon = false;
			}
		}

		vw_SetClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		vw_BeginRendering();
		vw_Start2DMode(-1,1);
			RECT SrcRest;
			SetRect(&SrcRest, 0, 0, 226, 120);
			vw_Draw(287,236,&SrcRest, vw_FindTextureByName("DATA\\LoadingPanel.bmp"), false);
		vw_End2DMode();
		vw_EndRendering();

		vw_BeginRendering();
		vw_Start2DMode(-1,1);
			SetRect(&SrcRest, 0, 0, 226, 120);
			vw_Draw(287,236,&SrcRest, vw_FindTextureByName("DATA\\LoadingPanel.bmp"), false);
		vw_End2DMode();
		vw_EndRendering();

		vw_SetTextureProp(RI_TEXTURE_NONE, RI_CLAMP, false, TX_ALPHA_EQUAL, false);

		// окна...
		vw_LoadTexture("DATA\\BUILDER\\12_03\\61.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\62.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\63.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\64.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\65.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\66.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\67.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\68.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\70.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\71.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\72.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\73.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\74.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\76.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\77.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\78.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\79.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\80.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\81.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\83.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\2_03\\60.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\2_03\\75.bmp", BMP_FILE);
		// стены...
		vw_LoadTexture("DATA\\BUILDER\\1_01_50\\a-09.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_01_50\\a-17.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_02_30\\a-15.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_03\\a-01.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_03\\a-03.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_03\\a-04.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_03\\a-12.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_03\\a-13.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_03\\a-14.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_05_50\\a-06.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_01_50\\a-02.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_02_30\\a-11.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_03\\a-19.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_04_30\\a-10.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_05_50\\a-05.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\12_05_50\\a-16.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\2_01_50\\a-08.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\2_01_50\\10.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\2_02_30\\08.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\2_03\\01.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\2_03\\02.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\2_03\\03.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\2_03\\04.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\2_03\\05.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\2_03\\06.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\2_03\\07.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\2_04_30\\09.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\2_05_50\\a-07.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\2_05_50\\11.bmp", BMP_FILE);
		// двери...
		vw_LoadTexture("DATA\\BUILDER\\1_02_30\\19.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_03\\13.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_03\\14.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_03\\15.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_03\\16.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_03\\17.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_03\\20.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_03\\21.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_03\\a-18.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\1_04_30\\18.bmp", BMP_FILE);
		// крыша...
		vw_LoadTexture("DATA\\BUILDER\\3_01_50\\35.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\3_01_50\\39.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\3_02_30\\41.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\3_03\\32.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\3_04_30\\40.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\3_05_50\\37.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\3_05_50\\38.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_02\\34.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_02\\46.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_02\\50.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_02\\b-04.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_03\\33.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_03\\42.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_03\\43.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_03\\44.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_03\\47.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_03\\48.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_03\\49.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_03\\b-01.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_03\\b-02.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_03\\b-03.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_03\\b-06.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_04\\36.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_04\\45.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_04\\51.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\BUILDER\\4_04\\b-05.bmp", BMP_FILE);

		if (Setup.UseUserBuilderAddon)
		{
			vw_CloseVFS();
			vw_OpenVFS(VFSFileNamePath, "1");
		}

	}

	if (lastgame == 2 && Setup.Type != 2)
	{
		ReleaseGameDate(2);
	}
	if (Setup.Type == 2 && lastgame != 2)
	{


		if (Setup.UseUserThePairAddon)
		{
			vw_CloseVFS();
			if (0 != vw_OpenVFS(Setup.UserThePairAddon, "1"))
			{
				vw_OpenVFS(VFSFileNamePath, "1");
				Setup.UseUserThePairAddon = false;
			}
		}

		vw_SetClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		vw_BeginRendering();
		vw_Start2DMode(-1,1);
			RECT SrcRest;
			SetRect(&SrcRest, 0, 0, 226, 120);
			vw_Draw(287,236,&SrcRest, vw_FindTextureByName("DATA\\LoadingPanel.bmp"), false);
		vw_End2DMode();
		vw_EndRendering();

		vw_BeginRendering();
		vw_Start2DMode(-1,1);
			SetRect(&SrcRest, 0, 0, 226, 120);
			vw_Draw(287,236,&SrcRest, vw_FindTextureByName("DATA\\LoadingPanel.bmp"), false);
		vw_End2DMode();
		vw_EndRendering();

		vw_SetTextureProp(RI_TEXTURE_NONE, RI_CLAMP, false, TX_ALPHA_EQUAL, false);
		vw_LoadTexture("DATA\\PAIR\\toys-001.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-002.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-003.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-004.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-005.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-006.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-007.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-008.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-009.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-010.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-011.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-012.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-013.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-014.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-016.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-017.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-018.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-019.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-020.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-021.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-022.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-023.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-024.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-025.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-026.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-027.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-028.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-029.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-030.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-031.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-032.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-033.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-034.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-035.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-036.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-037.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-038.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-039.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-040.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-041.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-042.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-043.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-044.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-045.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-046.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-047.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-048.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-049.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-050.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-051.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-052.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-053.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-054.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-055.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-056.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-057.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-058.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-059.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-060.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-061.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-062.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-063.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-064.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-065.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-066.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-067.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-068.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-069.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-070.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-071.bmp", BMP_FILE);
		vw_LoadTexture("DATA\\PAIR\\toys-072.bmp", BMP_FILE);

		if (Setup.UseUserThePairAddon)
		{
			vw_CloseVFS();
			vw_OpenVFS(VFSFileNamePath, "1");
		}


	}

	if (lastgame == 3)
	{
		ReleaseGameDate(3);
	}
	if (Setup.Type == 3)
	{

		vw_SetClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		vw_BeginRendering();
		vw_Start2DMode(-1,1);
			RECT SrcRest;
			SetRect(&SrcRest, 0, 0, 226, 120);
			vw_Draw(287,236,&SrcRest, vw_FindTextureByName("DATA\\LoadingPanel.bmp"), false);
		vw_End2DMode();
		vw_EndRendering();

		vw_BeginRendering();
		vw_Start2DMode(-1,1);
			SetRect(&SrcRest, 0, 0, 226, 120);
			vw_Draw(287,236,&SrcRest, vw_FindTextureByName("DATA\\LoadingPanel.bmp"), false);
		vw_End2DMode();
		vw_EndRendering();

		vw_SetTextureProp(RI_TEXTURE_NONE, RI_CLAMP, false, TX_ALPHA_EQUAL, false);

		{

			if (Setup.UseUserJigSawAddon)
			{
				vw_CloseVFS();
				if (0 != vw_OpenVFS(Setup.UserJigSawAddon, "1"))
				{
					vw_OpenVFS(VFSFileNamePath, "1");
					Setup.UseUserJigSawAddon = false;
				}
			}

			// смотрим, сколько всего рисунков
			int PicCount = 0;
			eFILE *num_file;
			num_file = vw_fopen("DATA\\JIGSAW\\num.txt");
			if (num_file != 0)
			{
				char ch1;
				vw_fread(&ch1, 1, 1, num_file);
				char ch2;
				vw_fread(&ch2, 1, 1, num_file);
				// смотрим, сколько там написано...
				PicCount = (ch1-48)*10+ch2-48;
				vw_fclose(num_file);
			}
			else PicCount = 13;

			// берем следующий рисунок...
			CurentFotoNum++;
			if (CurentFotoNum>PicCount) CurentFotoNum=1;

			// "собираем" название файла...
			char PicFileName[MAX_PATH];
			strcpy(PicFileName, "DATA\\JIGSAW\\pic");
			char buffer[65];
			itoa10(CurentFotoNum, buffer);
			strcat(PicFileName, buffer);
			strcat(PicFileName, ".jpg");
			CurentFoto = vw_LoadTexture(PicFileName, JPG_FILE, Setup.Size*64, Setup.Size*64)->Num;

			// делаем 512 на 512 из диба...
			BYTE *tmpDib;
			tmpDib = new BYTE[512*512*4];

			memset(tmpDib, 255, 512*512*4);
			// вклеиваем как нужно ум. копию рисунка
			int forDelete = CurentFoto;
			CurentFoto = vw_LoadTextureMem("ttt", tmpDib, 512, 512, 4)->Num;

			RECT SrcRect1;
			SetRect(&SrcRect1, 0, 0, Setup.Size*64, Setup.Size*64);
			CurentFoto = vw_AddToTexture(vw_FindTextureByNum(CurentFoto)->Name,
				vw_FindTextureByNum(forDelete)->Name,
				256-Setup.Size*32, 256-Setup.Size*32, &SrcRect1)->Num;

			// удаляем вклеиваемую копию
			vw_ReleaseTexture(vw_FindTextureByNum(forDelete));
			// удаляем диб
			delete [] tmpDib;



			if (Setup.UseUserJigSawAddon)
			{
				// пишем поверх рекламу...
				vw_SetTextureProp(RI_TEXTURE_NONE, RI_CLAMP, true, TX_ALPHA_EQUAL, false);
				vw_LoadTexture("DATA\\top.tga", TGA_FILE);
				vw_LoadTexture("DATA\\bottom.tga", TGA_FILE);
				vw_SetTextureProp(RI_TEXTURE_NONE, RI_CLAMP, false, TX_ALPHA_EQUAL, false);
				RECT SrcRect;

				SetRect(&SrcRect, 0, 0, 512, 32);
				CurentFoto = vw_AddToTexture(vw_FindTextureByNum(CurentFoto)->Name, "DATA\\top.tga", 0, (8-Setup.Size)*32, &SrcRect)->Num;
				SetRect(&SrcRect, 0, 0, 512, 32);
				CurentFoto = vw_AddToTexture(vw_FindTextureByNum(CurentFoto)->Name, "DATA\\bottom.tga", 0, 512-(8-Setup.Size)*32-32, &SrcRect)->Num;

				vw_ReleaseTexture(vw_FindTextureByName("DATA\\top.tga"));
				vw_ReleaseTexture(vw_FindTextureByName("DATA\\bottom.tga"));

				vw_CloseVFS();
				vw_OpenVFS(VFSFileNamePath, "1");
			}

		}


	}


	// для задержки, чтобы рисовать не менее 0.5 секунды
	if (lastgame!=Setup.Type)
	{
		Uint32 gettick2 = SDL_GetTicks();
		if (gettick+500 > gettick2) SDL_Delay(gettick+500-gettick2);
	}

}






//------------------------------------------------------------------------------------
// прорисовка и обработка подменю начала игры
//------------------------------------------------------------------------------------
void GameStart()
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// делаем предустановку игры...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	GameStatus = GAME_START;
	GameStartTimeInit = SDL_GetTicks();
	GameTime = 0;
	GameTimeInit = 0;
	StartPanelPos = 0;
	EndPanelPos = 0;
	SetPanelPos = 0;
	SearchFor = 0;
	GameWin = false;
	TopScCheck = false;
	TopScCheckStop = 2;
	GameWin = false;
	ErrorShow = false;
	RightShow = false;
	ErrorShowTime = 0;
	RightShowTime = 0;



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// счет, по размеру...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	int Size1=4-Setup.Size/2;
	int Size2=4+Setup.Size/2;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// загружаем/освобождаем...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	LoadGameData();
	lastgame = Setup.Type;


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// обнуляем исходный массив...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	for (int i=0; i<8; i++)
		for (int j=0; j<8; j++)
		{
			FieldData[i][j]=0;
			SetFieldData[i][j]=0;
		}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// мазайка...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Setup.Type == 0)
	{

		// находим первый номер текстуры...+50
		int StartNum = vw_FindTextureByName("DATA\\MOSAIC\\1_1.bmp")->Num;

		// заполняем массив
		for (int i=Size1; i<Size2; i++)
		for (int j=Size1; j<Size2; j++)
		{
			int test;
			test = StartNum+(int)fmodf(vw_Rand(),50);
			FieldData[i][j] = test;
		}

		StartPanelPos = StartNum;
		SetPanelPos = StartNum+1;
		EndPanelPos = StartNum+9;//49;

		// если у нас - средняя сложность или простая - делаем все в одном цвете...
		if (Setup.Difficult < 2)
		{
			// какой цвет?
			CurColor ++;
			if (CurColor>4) CurColor = 0;
			int color = CurColor;//(int)fmodf(vw_Rand(),5);


			for (int i=Size1; i<Size2; i++)
			for (int j=Size1; j<Size2; j++)
			{
				if ((FieldData[i][j]-StartNum)>color*10+9)
					while ((FieldData[i][j]-StartNum)>color*10+9)
						FieldData[i][j] -=10;

				if ((FieldData[i][j]-StartNum)<color*10)
					while ((FieldData[i][j]-StartNum)<color*10)
						FieldData[i][j] +=10;
			}

			StartPanelPos = color*10+StartNum;
			SetPanelPos = color*10+StartNum+1;
			EndPanelPos = color*10+9+StartNum;
			color++;//-просто пустое..
		}

		if (Setup.Difficult < 1)
		{
			// если симметрично...
			for (int i=0; i<4; i++)
			for (int j=0; j<8; j++)
			{
				FieldData[i][j] = FieldData[7-i][j];
			}
		}


		int MosaicMask[4][8][8]=
		{
			{{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1}},

			{{0,0,0,1,1,0,0,0},
			{0,0,1,1,1,1,0,0},
			{0,1,1,1,1,1,1,0},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{0,1,1,1,1,1,1,0},
			{0,0,1,1,1,1,0,0},
			{0,0,0,1,1,0,0,0}},

			{{0,0,1,1,1,1,0,0},
			{0,0,1,1,1,1,0,0},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1},
			{0,0,1,1,1,1,0,0},
			{0,0,1,1,1,1,0,0}},

			{{1,1,1,0,0,1,1,1},
			{1,1,1,0,0,1,1,1},
			{1,1,1,1,1,1,1,1},
			{0,0,1,1,1,1,0,0},
			{0,0,1,1,1,1,0,0},
			{1,1,1,1,1,1,1,1},
			{1,1,1,0,0,1,1,1},
			{1,1,1,0,0,1,1,1}},
		};

		if (Setup.Size >= 6)
		{
			int test = (int)fmodf(vw_Rand(),4);

			for (int i=0; i<8; i++)
			for (int j=0; j<8; j++)
			{
				if (MosaicMask[test][i][j] == 0)
					FieldData[i][j] = 0;
			}
		}

	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// builder...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Setup.Type == 1)
	{

		int housedata[11][8][8]=
		{
			{{402,403,403,403,403,403,403,404},
			{30230,303,303,303,303,303,303,30430},
			{20230,203,203,203,203,203,203,20430},
			{20230,203,203,203,203,203,203,20430},
			{20230,203,203,203,203,203,203,20430},
			{20230,203,203,203,203,203,203,20430},
			{20230,203,203,203,203,203,203,20430},
			{10230,103,103,103,103,103,103,10430}},

			{{203,0,0,0,0,0,0,0},
			{203,203,0,0,0,0,0,0},
			{203,203,203,0,0,0,0,0},
			{203,203,203,203,0,0,0,0},
			{203,203,203,203,203,0,0,0},
			{203,203,203,203,203,203,0,0},
			{203,203,203,203,203,203,203,0},
			{103,103,103,103,103,103,103,103}},

			{{0,0,0,0,0,0,20230,203},
			{403,404,0,0,0,0,20230,203},
			{303,30430,402,403,403,404,20230,203},
			{203,20430,30230,303,303,30430,20230,203},
			{203,20430,20230,203,203,20430,20230,203},
			{203,20430,20230,203,203,20430,20230,203},
			{203,20430,20230,203,203,20430,20230,203},
			{103,10430,10230,103,103,10430,10230,103}},

			{{402,403,403,403,403,403,403,404},
			{30150,303,303,303,303,303,303,30550},
			{20150,203,203,203,203,203,203,20550},
			{20150,203,203,203,203,203,203,20550},
			{20150,203,203,203,203,203,203,20550},
			{20150,203,203,203,203,203,203,20550},
			{20150,203,203,203,203,203,203,20550},
			{10150,103,103,103,103,103,103,10550}},

			{{0,   0,  402,403,403,404,0,  0},
			{0,    0,  303,303,303,303,0,  0},
			{402,  403,203,203,203,203,403,404},
			{30150,203,203,203,203,203,203,30550},
			{20150,203,203,203,203,203,203,20550},
			{20150,203,203,203,203,203,203,20550},
			{20150,203,203,203,203,203,203,20550},
			{10150,103,103,103,103,103,103,10550}},

			{{403,403,403,404,0,0,0,0},
			{303,303, 303,30550,0,402,403,403},
			{203,203,203,20550,0,30230,303,303},
			{203,203,203,20550,0,20230,203,203},
			{203,203,203,20550,0,20230,203,203},
			{203,203,203,20550,0,20230,203,203},
			{203,203,203,20550,0,20230,203,203},
			{103,103,103,10550,0,10230,103,103}},

			{{403,403,403,403,403,403,403,403},
			{303,303,303,303,303,303,303,303},
			{203,203,203,203,203,203,203,203},
			{203,203,203,203,203,203,203,203},
			{203,203,203,203,203,203,203,203},
			{203,203,203,203,203,203,203,203},
			{203,203,203,203,203,203,203,203},
			{103,103,103,103,103,103,103,103}},

			{{0,0,0,0,0,0,20230,203},
			{402,403,403,403,404,0,20230,203},
			{30230,303,303,303,30430,0,20230,203},
			{20230,203,203,203,20430,0,20230,203},
			{20230,203,203,203,20430,0,20230,203},
			{20230,203,203,203,20430,0,20230,203},
			{20230,203,203,203,20430,0,20230,203},
			{10230,103,103,103,10430,0,10230,103}},

			{{0,0,0,0,403,403,403,403},
			{0,0,0,0,303,303,303,303},
			{403,403,403,403,203,203,203,203},
			{303,303,303,303,203,203,203,203},
			{203,203,203,203,203,203,203,203},
			{203,203,203,203,203,203,203,203},
			{203,203,203,203,203,203,203,203},
			{103,103,103,103,103,103,103,103}},

			{{403,403,403,403,0,0,0,0},
			{303,303,303,303,0,0,0,0},
			{203,203,203,203,403,403,403,403},
			{203,203,203,203,303,303,303,303},
			{203,203,203,203,203,203,203,203},
			{203,203,203,203,203,203,203,203},
			{203,203,203,203,203,203,203,203},
			{103,103,103,103,103,103,103,103}},

			// новые
			{{0,0,0,0,0,0,0,203},
			{0,0,0,0,0,0,203,203},
			{0,0,0,0,0,203,203,203},
			{0,0,0,0,203,203,203,203},
			{0,0,0,203,203,203,203,203},
			{0,0,203,203,203,203,203,203},
			{0,203,203,203,203,203,203,203},
			{103,103,103,103,103,103,103,103}},

		};

		// переменные для левой и правой трубы водост...
		bool Ltr = false;
		bool Rtr = false;
		int El103 = -1;
		int El103_2 = -1;
		int El103_3 = -1;
		int El203 = -1;
		int El203_2 = -1;
		int El203_3 = -1;
		int El403 = -1;
		int El403_2 = -1;
		int El403_3 = -1;

		int MaskT = GameMask;
		while (GameMask==MaskT) {GameMask = (int)fmodf(vw_Rand(),11);}


		// заполняем массив
		for (int i=7; i>=0; i--)
		for (int j=7; j>=0; j--)
		{
			switch (housedata[GameMask][j][i])
			{
				case 0:// ничего нет...
					{
						FieldData[i][j] = 0;
						break;
					}
				case 10150:
					{
						int test =(int)fmodf(vw_Rand(),1.0f+Setup.Difficult);
						while (test>2) test = test-2;
						if (test == 0)
						{
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_01_50\\a-09.bmp")->Num;
							Ltr = true;
						}
						if (test == 1)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_01_50\\a-17.bmp")->Num;
						if (test == 2)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_01_50\\a-02.bmp")->Num;
						break;
					}
				case 10230:
					{
						int test =(int)fmodf(vw_Rand(),1.0f+Setup.Difficult);
						while (test>2) test = test-2;
						if (test == 0)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_02_30\\a-11.bmp")->Num;
						if (test == 1)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_02_30\\19.bmp")->Num;
						if (test == 2)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_02_30\\a-15.bmp")->Num;
						break;
					}
				case 103:
					{

						// 1 - находим какова вероятность, что это первый
						// чем проще уровень сложности, тем она выше...
						int first = (int)fmodf(vw_Rand(), 100.0f);

						if (first <= 60.0f - Setup.Difficult*10)
						{
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\a-19.bmp")->Num;
							break;
						}
						// иначе - ищем что-то другое
						int test;
						if (Setup.Difficult==0)
						if (El103==-1)
						{
							test =1+(int)fmodf(vw_Rand(), 34.0f);
							El103= test;
						}
						else test = El103;

						if (Setup.Difficult==1)
						{
							if (El103==-1)
							{
								test =1+(int)fmodf(vw_Rand(), 34.0f);
								El103= test;
							}
							else
							{
								if (El103_2==-1)
								{
									test =1+(int)fmodf(vw_Rand(), 34.0f);
									El103_2= test;
								}
								else
								{
									if (El103_3==-1)
									{
										test =1+(int)fmodf(vw_Rand(), 34.0f);
										El103_3= test;
									}
									else
									{
										int test1 =1+(int)fmodf(vw_Rand(), 2.0f);
										if (test1==0) test = El103;
										if (test1==1) test = El103_2;
										if (test1==2) test = El103_3;
									}
								}
							}
						}

						if (Setup.Difficult>=2)
							test =1+(int)fmodf(vw_Rand(), 34.0f);

						while (test>34) test = test-34;

						//if (test == 0)
						//	FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\a-19.bmp")->Num;
						if (test == 1)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_03\\a-03.bmp")->Num;
						if (test == 2)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_03\\a-04.bmp")->Num;
						if (test == 3)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_03\\13.bmp")->Num;
						if (test == 4)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_03\\14.bmp")->Num;
						if (test == 5)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_03\\a-14.bmp")->Num;
						if (test == 6)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\78.bmp")->Num;
						if (test == 7)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\70.bmp")->Num;
						if (test == 8)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\71.bmp")->Num;
						if (test == 9)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_03\\17.bmp")->Num;
						if (test == 10)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_03\\a-12.bmp")->Num;
						if (test == 11)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_03\\a-13.bmp")->Num;
						if (test == 12)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_03\\15.bmp")->Num;
						if (test == 13)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_03\\16.bmp")->Num;
						if (test == 14)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_03\\20.bmp")->Num;
						if (test == 15)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_03\\21.bmp")->Num;
						if (test == 16)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_03\\a-01.bmp")->Num;
						if (test == 17)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_03\\a-18.bmp")->Num;
						if (test == 18)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\61.bmp")->Num;
						if (test == 19)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\62.bmp")->Num;
						if (test == 20)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\63.bmp")->Num;
						if (test == 21)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\64.bmp")->Num;
						if (test == 22)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\65.bmp")->Num;
						if (test == 23)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\66.bmp")->Num;
						if (test == 24)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\67.bmp")->Num;
						if (test == 25)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\68.bmp")->Num;
						if (test == 26)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\72.bmp")->Num;
						if (test == 27)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\73.bmp")->Num;
						if (test == 28)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\74.bmp")->Num;
						if (test == 29)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\76.bmp")->Num;
						if (test == 30)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\77.bmp")->Num;
						if (test == 31)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\79.bmp")->Num;
						if (test == 32)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\80.bmp")->Num;
						if (test == 33)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\81.bmp")->Num;
						if (test == 34)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\83.bmp")->Num;
						break;
					}
				case 10430:
					{
						int test =(int)fmodf(vw_Rand(),1.0f+Setup.Difficult);
						if (test>1) test=0;
						if (test == 0)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_04_30\\a-10.bmp")->Num;
						if (test == 1)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_04_30\\18.bmp")->Num;
						break;
					}
				case 10550:
					{
						int test =(int)fmodf(vw_Rand(),1.0f+Setup.Difficult);
						while (test>2) test = test-2;
						if (test == 0)
						{
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\1_05_50\\a-06.bmp")->Num;
							Rtr = true;
						}
						if (test == 1)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_05_50\\a-05.bmp")->Num;
						if (test == 2)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_05_50\\a-16.bmp")->Num;
						break;
					}
				case 20150:
					{
						int test =(int)fmodf(vw_Rand(),1.0f+Setup.Difficult);
						if (test>1) test = 0;
						if (Ltr)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\2_01_50\\a-08.bmp")->Num;
						else
						{
							if (test == 0)
								FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_01_50\\a-02.bmp")->Num;
							if (test == 1)
								FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\2_01_50\\10.bmp")->Num;
						}
						break;
					}
				case 20230:
					{
						int test =(int)fmodf(vw_Rand(),1.0f+Setup.Difficult);
						if (test>1) test = 0;
						if (test == 0)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_02_30\\a-11.bmp")->Num;
						if (test == 1)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\2_02_30\\08.bmp")->Num;
						break;
					}
				case 203:
					{
						// 1 - находим какова вероятность, что это первый
						// чем проще уровень сложности, тем она выше...
						int first = (int)fmodf(vw_Rand(), 100.0f);

						if (first <= 60.0f - Setup.Difficult*10)
						{
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\a-19.bmp")->Num;
							break;
						}
						// иначе - ищем что-то другое

						int test;
						if (Setup.Difficult==0)
						if (El203==-1)
						{
							test =1+(int)fmodf(vw_Rand(), 29.0f);
							El203= test;
						}
						else test = El203;

						if (Setup.Difficult==1)
						{
							if (El203==-1)
							{
								test =1+(int)fmodf(vw_Rand(), 29.0f);
								El203= test;
							}
							else
							{
								if (El203_2==-1)
								{
									test =1+(int)fmodf(vw_Rand(), 29.0f);
									El203_2= test;
								}
								else
								{
									if (El203_3==-1)
									{
										test =1+(int)fmodf(vw_Rand(), 29.0f);
										El203_3= test;
									}
									else
									{
										int test1 =1+(int)fmodf(vw_Rand(), 2.0f);
										if (test1==0) test = El203;
										if (test1==1) test = El203_2;
										if (test1==2) test = El203_3;
									}
								}
							}
						}

						if (Setup.Difficult>=2)
							test =1+(int)fmodf(vw_Rand(), 29.0f);

						while (test>29) test = test-29;

						//if (test == 0)
						//	FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\a-19.bmp")->Num;
						if (test == 1)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\70.bmp")->Num;
						if (test == 2)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\71.bmp")->Num;
						if (test == 3)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\2_03\\01.bmp")->Num;
						if (test == 4)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\2_03\\02.bmp")->Num;
						if (test == 5)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\2_03\\03.bmp")->Num;
						if (test == 6)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\2_03\\04.bmp")->Num;
						if (test == 7)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\2_03\\05.bmp")->Num;
						if (test == 8)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\2_03\\06.bmp")->Num;
						if (test == 9)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\2_03\\07.bmp")->Num;
						if (test == 10)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\2_03\\60.bmp")->Num;
						if (test == 11)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\2_03\\75.bmp")->Num;
						if (test == 12)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\61.bmp")->Num;
						if (test == 13)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\62.bmp")->Num;
						if (test == 14)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\63.bmp")->Num;
						if (test == 15)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\64.bmp")->Num;
						if (test == 16)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\65.bmp")->Num;
						if (test == 17)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\66.bmp")->Num;
						if (test == 18)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\67.bmp")->Num;
						if (test == 19)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\68.bmp")->Num;
						if (test == 20)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\72.bmp")->Num;
						if (test == 21)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\73.bmp")->Num;
						if (test == 22)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\74.bmp")->Num;
						if (test == 23)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\76.bmp")->Num;
						if (test == 24)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\77.bmp")->Num;
						if (test == 25)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\78.bmp")->Num;
						if (test == 26)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\79.bmp")->Num;
						if (test == 27)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\80.bmp")->Num;
						if (test == 28)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\81.bmp")->Num;
						if (test == 29)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_03\\83.bmp")->Num;
						break;
					}
				case 20430:
					{
						int test =(int)fmodf(vw_Rand(),1.0f+Setup.Difficult);
						if (test>1) test = 0;
						if (test == 0)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_04_30\\a-10.bmp")->Num;
						if (test == 1)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\2_04_30\\09.bmp")->Num;
						break;
					}
				case 20550:
					{
						int test =(int)fmodf(vw_Rand(),1.0f+Setup.Difficult);
						while (test>2) test = test-2;
						if (Rtr)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\2_05_50\\a-07.bmp")->Num;
						else
						{
							if (test == 0)
								FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_05_50\\a-05.bmp")->Num;
							if (test == 1)
								FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\2_05_50\\11.bmp")->Num;
							if (test == 2)
								FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\12_05_50\\a-16.bmp")->Num;
						}
						break;
					}
				case 30150:
					{
						if (Ltr)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\3_01_50\\39.bmp")->Num;
						else
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\3_01_50\\35.bmp")->Num;
						break;
					}
				case 30230:
					{
						FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\3_02_30\\41.bmp")->Num;

						break;
					}
				case 303:
					{
						FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\3_03\\32.bmp")->Num;
						break;
					}
				case 30430:
					{
						FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\3_04_30\\40.bmp")->Num;
						break;
					}
				case 30550:
					{
						if (Rtr)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\3_05_50\\38.bmp")->Num;
						else
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\3_05_50\\37.bmp")->Num;
						break;
					}
				case 402:
					{
						int test =(int)fmodf(vw_Rand(),2.0f+Setup.Difficult);
						while (test>3) test = test-3;
						if (test == 0)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_02\\34.bmp")->Num;
						if (test == 1)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_02\\46.bmp")->Num;
						if (test == 2)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_02\\50.bmp")->Num;
						if (test == 3)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_02\\b-04.bmp")->Num;
						break;
					}
				case 403:
					{
						// 1 - находим какова вероятность, что это первый
						// чем проще уровень сложности, тем она выше...
						int first = (int)fmodf(vw_Rand(), 100.0f);

						if (first <= 60.0f - Setup.Difficult*10)
						{
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_03\\33.bmp")->Num;
							break;
						}
						// иначе - ищем что-то другое

						int test;
						if (Setup.Difficult==0)
						if (El403==-1)
						{
							test =1+(int)fmodf(vw_Rand(), 10.0f);
							El403= test;
						}
						else test = El403;

						if (Setup.Difficult==1)
						{
							if (El403==-1)
							{
								test =1+(int)fmodf(vw_Rand(), 6.0f);
								El403= test;
							}
							else
							{
								if (El403_2==-1)
								{
									test =1+(int)fmodf(vw_Rand(), 6.0f);
									El403_2= test;
								}
								else
								{
									if (El403_3==-1)
									{
										test =1+(int)fmodf(vw_Rand(), 6.0f);
										El403_3= test;
									}
									else
									{
										int test1 =1+(int)fmodf(vw_Rand(), 2.0f);
										if (test1==0) test = El403;
										if (test1==1) test = El403_2;
										if (test1==2) test = El403_3;
									}
								}
							}
						}

						if (Setup.Difficult>=2)
							test =1+(int)fmodf(vw_Rand(), 10.0f);

						while (test>10) test = test-10;
						//if (test == 0)
						//	FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_03\\33.bmp")->Num;
						if (test == 1)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_03\\42.bmp")->Num;
						if (test == 2)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_03\\43.bmp")->Num;
						if (test == 3)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_03\\44.bmp")->Num;
						if (test == 4)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_03\\47.bmp")->Num;
						if (test == 5)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_03\\48.bmp")->Num;
						if (test == 6)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_03\\49.bmp")->Num;
						if (test == 7)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_03\\b-01.bmp")->Num;
						if (test == 8)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_03\\b-02.bmp")->Num;
						if (test == 9)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_03\\b-03.bmp")->Num;
						if (test == 10)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_03\\b-06.bmp")->Num;
						break;
					}
				case 404:
					{
						int test =(int)fmodf(vw_Rand(),2.0f+Setup.Difficult);
						while (test>3) test = test-3;
						if (test == 0)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_04\\36.bmp")->Num;
						if (test == 1)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_04\\45.bmp")->Num;
						if (test == 2)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_04\\51.bmp")->Num;
						if (test == 3)
							FieldData[i][j]=vw_FindTextureByName("DATA\\BUILDER\\4_04\\b-05.bmp")->Num;
						break;
					}
			}
		}

		StartPanelPos = vw_FindTextureByName("DATA\\BUILDER\\12_03\\61.bmp")->Num;
		EndPanelPos = vw_FindTextureByName("DATA\\BUILDER\\2_03\\75.bmp")->Num;
		SetPanelPos = StartPanelPos+1;

		if (Setup.Size<8)
		{
			for (int i=0; i<8; i++)
			for (int j=0; j<8; j++)
			{
				if (i < 4-Setup.Size/2 || i > 3+Setup.Size/2
					|| j < 4-Setup.Size/2 || j > 3+Setup.Size/2)
				FieldData[i][j]=0;
			}
		}

		// корректировка SetPanelPos
		int stop = SetPanelPos;// если всего один элемент...
		bool rot=false;
		while (!CheckList(SetPanelPos))
		{
			SetPanelPos --;
			if (SetPanelPos<StartPanelPos) {SetPanelPos = EndPanelPos;rot=true;}
			if (rot && stop == SetPanelPos) break;
		}

	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// пара...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Setup.Type == 2)
	{

		// находим первый номер текстуры...+71 - все номера игрушек...
		int StartNum = vw_FindTextureByName("DATA\\PAIR\\toys-001.bmp")->Num;
		// массив 32 элементов, которые будем использовать...
		int PosNum[32];
		int PosNumCount = 0; // указатель на следующий незаполн.эл. табл.

		// заполняем массив
		while (PosNumCount< (Setup.Size*Setup.Size) / 2)
		{
			int test;
			test = StartNum+(int)fmodf(vw_Rand(),71);

			bool Net=true;
			for (int i=0; PosNumCount>i; i++)
				if (test==PosNum[i]) {Net=false;break;}

			if (Net)
			{
				PosNum[PosNumCount] = test;
				PosNumCount++;
			}
		}

		int FieldDataCount=0;
		PosNumCount=0;// последовательно берем все элементы...
		if (Setup.Difficult == 0 && Setup.Size>2)
		{
			// самая простая сложность, делаем 4 штуки...
			while (FieldDataCount<(Setup.Size*Setup.Size) / 4)
			{
				int count = 4;
                int X;
                int Y;
				while (count>0)
				{

					X=Size1+vw_iRandNum(Setup.Size-1);
					Y=Size1+vw_iRandNum(Setup.Size-1);
                    while (FieldData[X][Y]!=0)
                    {
                        X=Size1+vw_iRandNum(Setup.Size-1);
						Y=Size1+vw_iRandNum(Setup.Size-1);
                    }

					if (FieldData[X][Y]==0)
					{
						FieldData[X][Y] = PosNum[PosNumCount];
						count--;
					}
				}
				FieldDataCount++;
				PosNumCount++;
			}
		}
		else
		{
			while (FieldDataCount<(Setup.Size*Setup.Size) / 2)
			{
				int count = 2;
				while (count>0)
				{
					int X=X=Size1+vw_iRandNum(Setup.Size-1);
					int Y=X=Size1+vw_iRandNum(Setup.Size-1);

					Y=Size1+vw_iRandNum(Setup.Size-1);
					if (FieldData[X][Y]==0)
					{
						FieldData[X][Y] = PosNum[PosNumCount];
						count--;
					}
				}
				FieldDataCount++;
				PosNumCount++;
			}
		}

		// копируем все в резервный буфер...
		memcpy(FieldDataPair, FieldData, sizeof(FieldData));

	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// собираем пазл...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Setup.Type == 3)
	{
		//из исходника формируем 64 элемента 64на64...

		// получение пикселей из текстуры...
		BYTE *ImageData;
		ImageData = new BYTE[512*512*4];
		vw_GetTextureImage(vw_FindTextureByNum(CurentFoto), ImageData, 4);

		BYTE *SubImageData;
		SubImageData = new BYTE[512*512*4];
		int count=0;
		// в цикле создаем 64 текстуры...
		for (int x=0; x<8; x++)
		for (int y=0; y<512; y++)
		{
			memcpy(SubImageData+count, ImageData+x*64*4+512*4*y, 4*64);
			count+=64*4;
		}



		FieldData[0][7]=vw_LoadTextureMem("00", SubImageData, 64, 64, 4)->Num;
		FieldData[0][6]=vw_LoadTextureMem("10", SubImageData+64*64*4, 64, 64, 4)->Num;
		FieldData[0][5]=vw_LoadTextureMem("20", SubImageData+64*64*4*2, 64, 64, 4)->Num;
		FieldData[0][4]=vw_LoadTextureMem("30", SubImageData+64*64*4*3, 64, 64, 4)->Num;
		FieldData[0][3]=vw_LoadTextureMem("40", SubImageData+64*64*4*4, 64, 64, 4)->Num;
		FieldData[0][2]=vw_LoadTextureMem("50", SubImageData+64*64*4*5, 64, 64, 4)->Num;
		FieldData[0][1]=vw_LoadTextureMem("60", SubImageData+64*64*4*6, 64, 64, 4)->Num;
		FieldData[0][0]=vw_LoadTextureMem("70", SubImageData+64*64*4*7, 64, 64, 4)->Num;

		FieldData[1][7]=vw_LoadTextureMem("01", SubImageData+64*64*4*8, 64, 64, 4)->Num;
		FieldData[1][6]=vw_LoadTextureMem("11", SubImageData+64*64*4*9, 64, 64, 4)->Num;
		FieldData[1][5]=vw_LoadTextureMem("21", SubImageData+64*64*4*10, 64, 64, 4)->Num;
		FieldData[1][4]=vw_LoadTextureMem("31", SubImageData+64*64*4*11, 64, 64, 4)->Num;
		FieldData[1][3]=vw_LoadTextureMem("41", SubImageData+64*64*4*12, 64, 64, 4)->Num;
		FieldData[1][2]=vw_LoadTextureMem("51", SubImageData+64*64*4*13, 64, 64, 4)->Num;
		FieldData[1][1]=vw_LoadTextureMem("61", SubImageData+64*64*4*14, 64, 64, 4)->Num;
		FieldData[1][0]=vw_LoadTextureMem("71", SubImageData+64*64*4*15, 64, 64, 4)->Num;

		FieldData[2][7]=vw_LoadTextureMem("02", SubImageData+64*64*4*16, 64, 64, 4)->Num;
		FieldData[2][6]=vw_LoadTextureMem("12", SubImageData+64*64*4*17, 64, 64, 4)->Num;
		FieldData[2][5]=vw_LoadTextureMem("22", SubImageData+64*64*4*18, 64, 64, 4)->Num;
		FieldData[2][4]=vw_LoadTextureMem("32", SubImageData+64*64*4*19, 64, 64, 4)->Num;
		FieldData[2][3]=vw_LoadTextureMem("42", SubImageData+64*64*4*20, 64, 64, 4)->Num;
		FieldData[2][2]=vw_LoadTextureMem("52", SubImageData+64*64*4*21, 64, 64, 4)->Num;
		FieldData[2][1]=vw_LoadTextureMem("62", SubImageData+64*64*4*22, 64, 64, 4)->Num;
		FieldData[2][0]=vw_LoadTextureMem("72", SubImageData+64*64*4*23, 64, 64, 4)->Num;

		FieldData[3][7]=vw_LoadTextureMem("03", SubImageData+64*64*4*24, 64, 64, 4)->Num;
		FieldData[3][6]=vw_LoadTextureMem("13", SubImageData+64*64*4*25, 64, 64, 4)->Num;
		FieldData[3][5]=vw_LoadTextureMem("23", SubImageData+64*64*4*26, 64, 64, 4)->Num;
		FieldData[3][4]=vw_LoadTextureMem("33", SubImageData+64*64*4*27, 64, 64, 4)->Num;
		FieldData[3][3]=vw_LoadTextureMem("43", SubImageData+64*64*4*28, 64, 64, 4)->Num;
		FieldData[3][2]=vw_LoadTextureMem("53", SubImageData+64*64*4*29, 64, 64, 4)->Num;
		FieldData[3][1]=vw_LoadTextureMem("63", SubImageData+64*64*4*30, 64, 64, 4)->Num;
		FieldData[3][0]=vw_LoadTextureMem("73", SubImageData+64*64*4*31, 64, 64, 4)->Num;

		FieldData[4][7]=vw_LoadTextureMem("04", SubImageData+64*64*4*32, 64, 64, 4)->Num;
		FieldData[4][6]=vw_LoadTextureMem("14", SubImageData+64*64*4*33, 64, 64, 4)->Num;
		FieldData[4][5]=vw_LoadTextureMem("24", SubImageData+64*64*4*34, 64, 64, 4)->Num;
		FieldData[4][4]=vw_LoadTextureMem("34", SubImageData+64*64*4*35, 64, 64, 4)->Num;
		FieldData[4][3]=vw_LoadTextureMem("44", SubImageData+64*64*4*36, 64, 64, 4)->Num;
		FieldData[4][2]=vw_LoadTextureMem("54", SubImageData+64*64*4*37, 64, 64, 4)->Num;
		FieldData[4][1]=vw_LoadTextureMem("64", SubImageData+64*64*4*38, 64, 64, 4)->Num;
		FieldData[4][0]=vw_LoadTextureMem("74", SubImageData+64*64*4*39, 64, 64, 4)->Num;

		FieldData[5][7]=vw_LoadTextureMem("05", SubImageData+64*64*4*40, 64, 64, 4)->Num;
		FieldData[5][6]=vw_LoadTextureMem("15", SubImageData+64*64*4*41, 64, 64, 4)->Num;
		FieldData[5][5]=vw_LoadTextureMem("25", SubImageData+64*64*4*42, 64, 64, 4)->Num;
		FieldData[5][4]=vw_LoadTextureMem("35", SubImageData+64*64*4*43, 64, 64, 4)->Num;
		FieldData[5][3]=vw_LoadTextureMem("45", SubImageData+64*64*4*44, 64, 64, 4)->Num;
		FieldData[5][2]=vw_LoadTextureMem("55", SubImageData+64*64*4*45, 64, 64, 4)->Num;
		FieldData[5][1]=vw_LoadTextureMem("65", SubImageData+64*64*4*46, 64, 64, 4)->Num;
		FieldData[5][0]=vw_LoadTextureMem("75", SubImageData+64*64*4*47, 64, 64, 4)->Num;

		FieldData[6][7]=vw_LoadTextureMem("06", SubImageData+64*64*4*48, 64, 64, 4)->Num;
		FieldData[6][6]=vw_LoadTextureMem("16", SubImageData+64*64*4*49, 64, 64, 4)->Num;
		FieldData[6][5]=vw_LoadTextureMem("26", SubImageData+64*64*4*50, 64, 64, 4)->Num;
		FieldData[6][4]=vw_LoadTextureMem("36", SubImageData+64*64*4*51, 64, 64, 4)->Num;
		FieldData[6][3]=vw_LoadTextureMem("46", SubImageData+64*64*4*52, 64, 64, 4)->Num;
		FieldData[6][2]=vw_LoadTextureMem("56", SubImageData+64*64*4*53, 64, 64, 4)->Num;
		FieldData[6][1]=vw_LoadTextureMem("66", SubImageData+64*64*4*54, 64, 64, 4)->Num;
		FieldData[6][0]=vw_LoadTextureMem("76", SubImageData+64*64*4*55, 64, 64, 4)->Num;

		FieldData[7][7]=vw_LoadTextureMem("07", SubImageData+64*64*4*56, 64, 64, 4)->Num;
		FieldData[7][6]=vw_LoadTextureMem("17", SubImageData+64*64*4*57, 64, 64, 4)->Num;
		FieldData[7][5]=vw_LoadTextureMem("27", SubImageData+64*64*4*58, 64, 64, 4)->Num;
		FieldData[7][4]=vw_LoadTextureMem("37", SubImageData+64*64*4*59, 64, 64, 4)->Num;
		FieldData[7][3]=vw_LoadTextureMem("47", SubImageData+64*64*4*60, 64, 64, 4)->Num;
		FieldData[7][2]=vw_LoadTextureMem("57", SubImageData+64*64*4*61, 64, 64, 4)->Num;
		FieldData[7][1]=vw_LoadTextureMem("67", SubImageData+64*64*4*62, 64, 64, 4)->Num;
		FieldData[7][0]=vw_LoadTextureMem("77", SubImageData+64*64*4*63, 64, 64, 4)->Num;

		StartPanelPos=FieldData[0][7];
		EndPanelPos = FieldData[7][0];
		SetPanelPos = StartPanelPos+1;

		delete [] ImageData;
		delete [] SubImageData;

		// перемешиваем последовательность
		int cycle=50;//(int)fmodf(vw_Rand(),100);

		for (int i=0; i<cycle;i++)
		{
			int X=(int)fmodf(vw_Rand(),8);
			int Y=(int)fmodf(vw_Rand(),8);
			int X2=(int)fmodf(vw_Rand(),8);
			int Y2=(int)fmodf(vw_Rand(),8);

			int tmp = vw_FindTextureByNum(FieldData[X][Y])->Num;
			int tmp2 = vw_FindTextureByNum(FieldData[X2][Y2])->Num;
			void * tmpO = vw_FindTextureByNum(FieldData[X][Y])->OffsetID;
			void * tmpO2 = vw_FindTextureByNum(FieldData[X2][Y2])->OffsetID;

			vw_FindTextureByNum(FieldData[X][Y])->OffsetID = tmpO2;
			vw_FindTextureByNum(FieldData[X2][Y2])->OffsetID = tmpO;
			FieldData[X][Y] = tmp2;
			FieldData[X2][Y2] = tmp;
		}

		if (Setup.Size<8)
		{
			for (int i=0; i<8; i++)
			for (int j=0; j<8; j++)
			{
				if (i < 4-Setup.Size/2 || i > 3+Setup.Size/2
					|| j < 4-Setup.Size/2 || j > 3+Setup.Size/2)
				FieldData[i][j]=0;
			}
		}

		// корректировка SetPanelPos
		int stop = SetPanelPos;// если всего один элемент...
		bool rot=false;
		while (!CheckList(SetPanelPos))
		{
			SetPanelPos --;
			if (SetPanelPos<StartPanelPos) {SetPanelPos = EndPanelPos;rot=true;}
			if (rot && stop == SetPanelPos) break;
		}

	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// если долго инили...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	GameStartTimeInit = SDL_GetTicks();


	vw_SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}











//------------------------------------------------------------------------------------
// рисуем
//------------------------------------------------------------------------------------
void GameStartDraw()
{

	RECT MDetect;
	RECT DrawON;
	RECT DrawOFF;

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// прорисовка подложки ....
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	vw_DrawRect(0,0,0,0,800,600,"DATA\\start.jpg");


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// прорисовка на поле элементов...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (ResetTranspOn)
	{
		if (ResetTickCount+300 > SDL_GetTicks())
		{
			ResetTransp = ((SDL_GetTicks()-ResetTickCount)/300.0f);
			if (ResetTransp >= 1.0f) ResetTranspOn = false;
		}
		else ResetTranspOn = false;
	}

	for (int i=0; i<8; i++)
	for (int j=0; j<8; j++)
	{
		RECT SrcRest;
		SetRect(&SrcRest, 0, 0, 64, 64);
		if (FieldData[i][j] != 0)
		{
			if (ResetTranspOn)
			{
				RECT DstRest;
				SetRect(&DstRest, 44+i*64, 44+j*64, 44+i*64+64, 44+j*64+64);
				vw_DrawTransparent(&DstRest, &SrcRest, vw_FindTextureByNum(FieldData[i][j]), false, ResetTransp);
			}
			else
			{
				vw_Draw(44+i*64,44+j*64,&SrcRest, vw_FindTextureByNum(FieldData[i][j]), false);
			}

		}
		else
		{
			vw_Draw(44+i*64,44+j*64,&SrcRest, vw_FindTextureByName("DATA\\BUILDER\\0.bmp"), true);
		}
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// вывод счет времени... если нужно...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (Setup.CountdownSw)
	{
		vw_DrawRect(586,35,0,0,181,81,"DATA\\start3.jpg");

		int GameStartTime = (int)((SDL_GetTicks() - GameStartTimeInit)/1000.0f);

		int tmp100=(int)((Setup.Countdown-GameStartTime)/100);
		int tmp10=(int)((Setup.Countdown-GameStartTime)/10 - tmp100*10);
		int tmp1=(int)((Setup.Countdown-GameStartTime) - tmp10*10 - tmp100*100);
		// сотни
		vw_DrawRect(690-58,112, 61-58, 2+(tmp100*36), 90-58, 36+(tmp100*36),"DATA\\start2.jpg");
		// десятки
		vw_DrawRect(690-29,112, 61-29, 2+(tmp10*36), 90-29, 36+(tmp10*36),"DATA\\start2.jpg");
		// еденицы
		vw_DrawRect(690,112, 61, 2+(tmp1*36), 90, 36+(tmp1*36),"DATA\\start2.jpg");

		if (GameStartTime >= Setup.Countdown)
		{ //принудительный старт игры
			GameStatus = GAME;
			GameTime = 0;
			GameTimeInit = SDL_GetTicks();
			return;
		}
	}















	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка start...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 590, 344, 766, 385);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 3, 603, 147, 633);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(606, 406-57, &MDetect, &DrawON, &DrawOFF, "DATA\\start.jpg"))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		ComBuffer = GAME;
		GameTime = 0;
		GameTimeInit = SDL_GetTicks();
	}




	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка reset...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 590, 401, 766, 442);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 154, 603, 298, 633);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(606, 406, &MDetect, &DrawON, &DrawOFF, "DATA\\start.jpg"))
	{
		if (ResetTickCount+300 <= SDL_GetTicks())
		{
			ResetTransp = 0.0f;
			ResetTranspOn = true;
			ResetTickCount = SDL_GetTicks();
			if (Setup.SoundSw) Audio_PlaySound(1);
			if (Setup.Type == 3) Setup.UseUserFileForJigSaw = false;
			ComBuffer = GAME_START;
		}
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка options
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 590, 458, 766, 499);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 303, 603, 450, 634);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(604, 406+57, &MDetect, &DrawON, &DrawOFF, "DATA\\start.jpg"))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		ComBuffer = OPTIONS;
	}


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// кнопка меню...
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SetRect(&MDetect, 590, 458+57, 766, 499+57);
	if (isDialogBoxDrawing()) SetRect(&MDetect, 0, 0, 0, 0);
	SetRect(&DrawOFF, 0, 0, 0, 0);
	SetRect(&DrawON, 454, 602, 601, 634);
	if (vw_OnRect(&MDetect)) GameCursor.Current=1;
	if (vw_Button2D(604, 519, &MDetect, &DrawON, &DrawOFF, "DATA\\start.jpg"))
	{
		if (Setup.SoundSw) Audio_PlaySound(1);
		ComBuffer = MAIN_MENU;
	}



}
