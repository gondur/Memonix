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


#include "Math.h"







//------------------------------------------------------------------------------------
// начальная установка
//------------------------------------------------------------------------------------
void Matrix44Identity(float Matrix44[16])
{
	Matrix44[0] = 1.0f;
	Matrix44[1] = 0.0f;
	Matrix44[2] = 0.0f;
	Matrix44[3] = 0.0f;

	Matrix44[4] = 0.0f;
	Matrix44[5] = 1.0f;
	Matrix44[6] = 0.0f;
	Matrix44[7] = 0.0f;

	Matrix44[8] = 0.0f;
	Matrix44[9] = 0.0f;
	Matrix44[10] = 1.0f;
	Matrix44[11] = 0.0f;

	Matrix44[12] = 0.0f;
	Matrix44[13] = 0.0f;
	Matrix44[14] = 0.0f;
	Matrix44[15] = 1.0f;
}





//------------------------------------------------------------------------------------
// Матрица, перемножение
//------------------------------------------------------------------------------------
void Matrix44Mult(float DstMatrix44[16], float SrcMatrix44[16])
{
	float tmp[16];
	memcpy(tmp, DstMatrix44, 16*sizeof(float));

	DstMatrix44[0] = SrcMatrix44[0]*tmp[0] + SrcMatrix44[1]*tmp[4] + SrcMatrix44[2]*tmp[8] + SrcMatrix44[3]*tmp[12];
	DstMatrix44[1] = SrcMatrix44[0]*tmp[1] + SrcMatrix44[1]*tmp[5] + SrcMatrix44[2]*tmp[9] + SrcMatrix44[3]*tmp[13];
	DstMatrix44[2] = SrcMatrix44[0]*tmp[2] + SrcMatrix44[1]*tmp[6] + SrcMatrix44[2]*tmp[10] + SrcMatrix44[3]*tmp[14];
	DstMatrix44[3] = SrcMatrix44[0]*tmp[3] + SrcMatrix44[1]*tmp[7] + SrcMatrix44[2]*tmp[11] + SrcMatrix44[3]*tmp[15];
	DstMatrix44[4] = SrcMatrix44[4]*tmp[0] + SrcMatrix44[5]*tmp[4] + SrcMatrix44[6]*tmp[8] + SrcMatrix44[7]*tmp[12];
	DstMatrix44[5] = SrcMatrix44[4]*tmp[1] + SrcMatrix44[5]*tmp[5] + SrcMatrix44[6]*tmp[9] + SrcMatrix44[7]*tmp[13];
	DstMatrix44[6] = SrcMatrix44[4]*tmp[2] + SrcMatrix44[5]*tmp[6] + SrcMatrix44[6]*tmp[10] + SrcMatrix44[7]*tmp[14];
	DstMatrix44[7] = SrcMatrix44[4]*tmp[3] + SrcMatrix44[5]*tmp[7] + SrcMatrix44[6]*tmp[11] + SrcMatrix44[7]*tmp[15];
	DstMatrix44[8] = SrcMatrix44[8]*tmp[0] + SrcMatrix44[9]*tmp[4] + SrcMatrix44[10]*tmp[8] + SrcMatrix44[11]*tmp[12];
	DstMatrix44[9] = SrcMatrix44[8]*tmp[1] + SrcMatrix44[9]*tmp[5] + SrcMatrix44[10]*tmp[9] + SrcMatrix44[11]*tmp[13];
	DstMatrix44[10] = SrcMatrix44[8]*tmp[2] + SrcMatrix44[9]*tmp[6] + SrcMatrix44[10]*tmp[10] + SrcMatrix44[11]*tmp[14];
	DstMatrix44[11] = SrcMatrix44[8]*tmp[3] + SrcMatrix44[9]*tmp[7] + SrcMatrix44[10]*tmp[11] + SrcMatrix44[11]*tmp[15];
	DstMatrix44[12] = SrcMatrix44[12]*tmp[0] + SrcMatrix44[13]*tmp[4] + SrcMatrix44[14]*tmp[8] + SrcMatrix44[15]*tmp[12];
	DstMatrix44[13] = SrcMatrix44[12]*tmp[1] + SrcMatrix44[13]*tmp[5] + SrcMatrix44[14]*tmp[9] + SrcMatrix44[15]*tmp[13];
	DstMatrix44[14] = SrcMatrix44[12]*tmp[2] + SrcMatrix44[13]*tmp[6] + SrcMatrix44[14]*tmp[10] + SrcMatrix44[15]*tmp[14];
	DstMatrix44[15] = SrcMatrix44[12]*tmp[3] + SrcMatrix44[13]*tmp[7] + SrcMatrix44[14]*tmp[11] + SrcMatrix44[15]*tmp[15];
}











//------------------------------------------------------------------------------------
// Матрица, перенос в точку Location
//------------------------------------------------------------------------------------
void Matrix44Translate(float Matrix44[16], VECTOR3D Location)
{
	Matrix44[12] += Location.x;
	Matrix44[13] += Location.y;
	Matrix44[14] += Location.z;
}







//------------------------------------------------------------------------------------
// Матрица, создаем матрицу поворота на углы Angle
//------------------------------------------------------------------------------------
void Matrix44CreateRotate(float Matrix44[16], VECTOR3D Angle)
{
	const float p180 = 0.0174532925f;

	// если угол только один - сюда идем
	if (Angle.z != 0.0f && Angle.x == 0.0f && Angle.y == 0.0f)
	{
		float a = Angle.z*p180;
		float c = cosf(a);
		float s = sinf(a);
		// ставим в нужные элементы
		Matrix44[0] = c;
		Matrix44[1] = -s;
		Matrix44[4] = s;
		Matrix44[5] = c;
		// делаем инициализацю, чтобы не вызывать функцию и не делать 4 лишних операции
		Matrix44[2] = Matrix44[3] = Matrix44[6] = Matrix44[7] = Matrix44[8] = Matrix44[9] = 0.0f;
		Matrix44[11] = Matrix44[12] = Matrix44[13] = Matrix44[14] = 0.0f;
		Matrix44[15] = Matrix44[10] = 1.0f;
		// выходим
		return;
	}

	if (Angle.y != 0.0f && Angle.x == 0.0f && Angle.z == 0.0f)
	{
		float a = Angle.y*p180;
		float c = cosf(a);
		float s = sinf(a);
		// ставим в нужные элементы
		Matrix44[0] = c;
		Matrix44[2] = s;
		Matrix44[8] = -s;
		Matrix44[10] = c;
		// делаем инициализацю, чтобы не вызывать функцию и не делать 4 лишних операции
		Matrix44[1] = Matrix44[3] = Matrix44[4] = Matrix44[6] = Matrix44[7] = 0.0f;
		Matrix44[9] = Matrix44[11] = Matrix44[12] = Matrix44[13] = Matrix44[14] = 0.0f;
		Matrix44[15] = Matrix44[5] = 1.0f;
		// выходим
		return;
	}

	if (Angle.x != 0.0f && Angle.y == 0.0f && Angle.z == 0.0f)
	{
		float a = Angle.x*p180;
		float c = cosf(a);
		float s = sinf(a);
		// ставим в нужные элементы
		Matrix44[5] = c;
		Matrix44[6] = -s;
		Matrix44[9] = s;
		Matrix44[10] = c;
		// делаем инициализацю, чтобы не вызывать функцию и не делать 4 лишних операции
		Matrix44[1] = Matrix44[2] = Matrix44[3] = Matrix44[4] = Matrix44[7] = 0.0f;
		Matrix44[8] = Matrix44[11] = Matrix44[12] = Matrix44[13] = Matrix44[14] = 0.0f;
		Matrix44[0] = Matrix44[15] = 1.0f;
		// выходим
		return;
	}


	// если 2 или более углов

	float a = Angle.x*p180;
	float A = cosf(a);
	float B = sinf(a);
	a = Angle.y*p180;
	float C = cosf(a);
	float D = sinf(a);
	a = Angle.z*p180;
	float E = cosf(a);
	float F = sinf(a);
	float AD = A * D;
	float BD = B * D;
	// эти формулы получили после оптимизации верхних 3-х преобразований
    Matrix44[0]  =   C * E;
    Matrix44[1]  =  -C * F;
    Matrix44[2]  =   D;
    Matrix44[4]  =  BD * E + A * F;
    Matrix44[5]  = -BD * F + A * E;
    Matrix44[6]  =  -B * C;
    Matrix44[8]  = -AD * E + B * F;
    Matrix44[9]  =  AD * F + B * E;
    Matrix44[10] =   A * C;
	// делаем инициализацю, чтобы не вызывать функцию и не делать 9 лишних операции
    Matrix44[3]  =  Matrix44[7] = Matrix44[11] = Matrix44[12] = Matrix44[13] = Matrix44[14] = 0.0f;
    Matrix44[15] =  1.0f;
}








//------------------------------------------------------------------------------------
// Получение обратной матрицы поворота
//------------------------------------------------------------------------------------
void Matrix44InverseRotate(float Matrix44[16])
{
	float tmp[16];
	memcpy(tmp, Matrix44, 16*sizeof(float));

	// транспонируем и вычисляем...

	Matrix44[0] = tmp[0];
	Matrix44[1] = tmp[4];
	Matrix44[2] = tmp[8];
//	elem[3] = tmp[0];- не трогаем, мы эту часть никогда не пересчитываем - нет проективных преобразований

	Matrix44[4] = tmp[1];
	Matrix44[5] = tmp[5];
	Matrix44[6] = tmp[9];
//	elem[7] = tmp[0];- не трогаем, мы эту часть никогда не пересчитываем - нет проективных преобразований

	Matrix44[8] = tmp[2];
	Matrix44[9] = tmp[6];
	Matrix44[10] = tmp[10];
//	elem[11] = tmp[0];- не трогаем, мы эту часть никогда не пересчитываем - нет проективных преобразований

	Matrix44[12] = -(tmp[12]*tmp[0]) - (tmp[13]*tmp[1]) - (tmp[14]*tmp[2 ]);
	Matrix44[13] = -(tmp[12]*tmp[4]) - (tmp[13]*tmp[5]) - (tmp[14]*tmp[6 ]);
	Matrix44[14] = -(tmp[12]*tmp[8]) - (tmp[13]*tmp[9]) - (tmp[14]*tmp[10]);
	Matrix44[15] = tmp[15];
}








//------------------------------------------------------------------------------------
// Получаем точку по матрице трансформаций
//------------------------------------------------------------------------------------
void Matrix44CalcPoint(VECTOR3D *Point, float Matrix44[16])
{
	VECTOR3D TmpPoint = *Point;
	Point->x = Matrix44[0]*TmpPoint.x + Matrix44[4]*TmpPoint.y + Matrix44[8]*TmpPoint.z + Matrix44[12];
	Point->y = Matrix44[1]*TmpPoint.x + Matrix44[5]*TmpPoint.y + Matrix44[9]*TmpPoint.z + Matrix44[13];
	Point->z = Matrix44[2]*TmpPoint.x + Matrix44[6]*TmpPoint.y + Matrix44[10]*TmpPoint.z + Matrix44[14];
}




