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



extern float fScreenWidthGL;
extern float fScreenHeightGL;





////////////////////////////////////////////////////////////
// Переход на 2D режима вывода
////////////////////////////////////////////////////////////
void vw_Start2DMode(float nZ1, float nZ2)
{
    // запоминаем состояние флагов
	glPushAttrib(GL_ENABLE_BIT);
    // и выключаем "ненужные"
	glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);


	int buff[4];
	glGetIntegerv(GL_VIEWPORT, buff);
	float AWw = fScreenWidthGL;
	float AHw = fScreenHeightGL;

	glMatrixMode(GL_PROJECTION);								//select the projection matrix
	glPushMatrix();												//store the projection matrix
	glLoadIdentity();											//reset the projection matrix

	float AW;
	float AH;
	bool ASpresent=false;
	ASpresent = vw_GetAspectWH(&AW, &AH);


	if (ASpresent)
		glOrtho(buff[0]*(AW/AWw), (buff[0]+buff[2])*(AW/AWw), buff[1]*(AH/AHw), (buff[1]+buff[3])*(AH/AHw), nZ1, nZ2);
	else
		glOrtho(0, AWw, 0, AHw, nZ1, nZ2);	//set up an ortho screen

	glMatrixMode(GL_MODELVIEW);									//select the modelview matrix
	glPushMatrix();
	glLoadIdentity();

}



////////////////////////////////////////////////////////////
// Возвращение в обычный (3D) режим вывода
////////////////////////////////////////////////////////////
void vw_End2DMode()
{
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);			//select the projection matrix
	glPopMatrix();							//restore the old projection matrix
	glMatrixMode(GL_MODELVIEW);				//select the modelview matrix
    // восстанавливаем флаги
	glPopAttrib();
}






////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_Draw(int X, int Y, RECT *SrcRest, eTexture *Tex, bool Alpha, float RotateAngle, int DrawCorner)
{
	if (Tex == 0) return;


	float AW;
	float AH;
	bool ASpresent=false;
	ASpresent = vw_GetAspectWH(&AW, &AH);

	int buff[4];
	glGetIntegerv(GL_VIEWPORT, buff);
	float AWw = buff[2]*1.0f;
	float AHw = buff[3]*1.0f;

	// Установка текстуры и ее свойств...
	vw_SetTextureV(0, Tex);
	vw_SetTexAlpha(Alpha, 0.01f);
	vw_SetTexAddressMode(0, RI_CLAMP);
	vw_SetTexBlend(RI_BLEND_SRCALPHA, RI_BLEND_INVSRCALPHA);

    // не можем ставить другое! если нет мипмапа
    vw_SetTexFiltering(0, RI_MAGFILTER_LINEAR | RI_MINFILTER_LINEAR | RI_MIPFILTER_NONE);


	// Вычисление поправки по У в зависимости от DrawCorner
	// - расположения угла начала координат
	float tmpPosY = 0;
	// изменяем только в случае RI_UL_CORNER
	if (DrawCorner == RI_UL_CORNER)
	{
		if (ASpresent) tmpPosY = (AH - Y - Y - (SrcRest->bottom - SrcRest->top));
		else tmpPosY = (AHw - Y - Y - (SrcRest->bottom - SrcRest->top));
	}


	float ImageHeight = Tex->Height*1.0f;
	float ImageWidth = Tex->Width*1.0f;

	float FrameHeight = (SrcRest->bottom*1.0f)/ImageHeight;
	float FrameWidth = (SrcRest->right*1.0f)/ImageWidth;

	float Yst = (SrcRest->top)/ImageHeight;
	float Xst = (SrcRest->left)/ImageWidth;


		// буфер для последовательности RI_TRIANGLE_STRIP
		// войдет RI_2f_XYZ | RI_2f_TEX
		float *tmp = 0;
		tmp = new float[(2+2)*4];
		int k=0;


		tmp[k++] = -(SrcRest->right - SrcRest->left)/2.0f;	// X
		tmp[k++] = (SrcRest->bottom - SrcRest->top)/2.0f;		// Y
		tmp[k++] = Xst;
		tmp[k++] = 1.0f-Yst;

		tmp[k++] = -(SrcRest->right - SrcRest->left)/2.0f;	// X
		tmp[k++] = -(SrcRest->bottom - SrcRest->top)/2.0f;		// Y
		tmp[k++] = Xst;
		tmp[k++] = 1.0f-FrameHeight;

		tmp[k++] = (SrcRest->right - SrcRest->left)/2.0f;	// X
		tmp[k++] = (SrcRest->bottom - SrcRest->top)/2.0f;		// Y
		tmp[k++] = FrameWidth;
		tmp[k++] = 1.0f-Yst;

		tmp[k++] = (SrcRest->right - SrcRest->left)/2.0f;	// X
		tmp[k++] = -(SrcRest->bottom - SrcRest->top)/2.0f;		// Y
		tmp[k++] = FrameWidth;
		tmp[k++] = 1.0f-FrameHeight;

		glPushMatrix();
		glTranslatef(X + (SrcRest->right - SrcRest->left)/2.0f,
			Y +tmpPosY +(SrcRest->bottom - SrcRest->top)/2.0f, 0.0f);
		glRotatef(RotateAngle, 0, 0, 1);

		vw_SendVertices(RI_TRIANGLE_STRIP, 4, RI_2f_XYZ | RI_2f_TEX, tmp, 4*sizeof(float));
		glPopMatrix();




	delete [] tmp;
    vw_SetTexAlpha(false, 0.5f);
	vw_SetTextureDef(0);
}





////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_DrawTransparent(RECT *DstRest, RECT *SrcRest, eTexture *Tex, bool Alpha, float Transp, float RotateAngle, int DrawCorner, float R, float G, float B)
{

	if (Tex == 0) return;


	float AW;
	float AH;
	bool ASpresent=false;
	ASpresent = vw_GetAspectWH(&AW, &AH);

	int buff[4];
	glGetIntegerv(GL_VIEWPORT, buff);
	float AWw = buff[2]*1.0f;
	float AHw = buff[3]*1.0f;

	int X = DstRest->left;
	int Y = DstRest->top;


	// Установка текстуры и ее свойств...
	vw_SetTextureV(0, Tex);
	vw_SetTexAlpha(Alpha, 0.01f);
	vw_SetTexAddressMode(0, RI_CLAMP);
	vw_SetTexBlend(RI_BLEND_SRCALPHA, RI_BLEND_INVSRCALPHA);

    // не можем ставить другое! если нет мипмапа
    vw_SetTexFiltering(0, RI_MAGFILTER_LINEAR | RI_MINFILTER_LINEAR | RI_MIPFILTER_NONE);


	// Вычисление поправки по У в зависимости от DrawCorner
	// - расположения угла начала координат
	float tmpPosY = 0;
	// изменяем только в случае OBJ2D_DRW_UL_CORNER
	if (DrawCorner == RI_UL_CORNER)
	{
		if (ASpresent) tmpPosY = (AH - Y - Y - (DstRest->bottom - DstRest->top));
		else tmpPosY = (AHw - Y - Y - (DstRest->bottom - DstRest->top));
	}



	float ImageHeight = Tex->Height*1.0f;
	float ImageWidth = Tex->Width*1.0f;

	float FrameHeight = (SrcRest->bottom*1.0f )/ImageHeight;
	float FrameWidth = (SrcRest->right*1.0f )/ImageWidth;

	float Yst = (SrcRest->top*1.0f)/ImageHeight;
	float Xst = (SrcRest->left*1.0f)/ImageWidth;


		// буфер для последовательности RI_TRIANGLE_STRIP
		// войдет RI_2f_XYZ | RI_2f_TEX | RI_4f_COLOR
		float *tmp = 0;
		tmp = new float[(2+4+2)*4];
		int k=0;
		if (Transp > 1.0f) Transp = 1.0f;
		if (Transp <= 0)
		{
			if (Tex != 0)
			{
				vw_SetTexAlpha(false, 0.5f);
				vw_SetTextureDef(0);
			}
			return;
		}


		tmp[k++] = -(DstRest->right - DstRest->left)/2.0f;	// X
		tmp[k++] = (DstRest->bottom - DstRest->top)/2.0f;	// Y
		tmp[k++] = R;
		tmp[k++] = G;
		tmp[k++] = B;
		tmp[k++] = Transp;
		tmp[k++] = Xst;
		tmp[k++] = 1.0f-Yst;

		tmp[k++] = -(DstRest->right - DstRest->left)/2.0f;	// X
		tmp[k++] = -(DstRest->bottom - DstRest->top)/2.0f;	// Y
		tmp[k++] = R;
		tmp[k++] = G;
		tmp[k++] = B;
		tmp[k++] = Transp;
		tmp[k++] = Xst;
		tmp[k++] = 1.0f-FrameHeight;

		tmp[k++] = (DstRest->right - DstRest->left)/2.0f;	// X
		tmp[k++] = (DstRest->bottom - DstRest->top)/2.0f;	// Y
		tmp[k++] = R;
		tmp[k++] = G;
		tmp[k++] = B;
		tmp[k++] = Transp;
		tmp[k++] = FrameWidth;
		tmp[k++] = 1.0f-Yst;

		tmp[k++] = (DstRest->right - DstRest->left)/2.0f;	// X
		tmp[k++] = -(DstRest->bottom - DstRest->top)/2.0f;	// Y
		tmp[k++] = R;
		tmp[k++] = G;
		tmp[k++] = B;
		tmp[k++] = Transp;
		tmp[k++] = FrameWidth;
		tmp[k++] = 1.0f-FrameHeight;


		glPushMatrix();
		glTranslatef(X + (DstRest->right - DstRest->left)/2.0f,
			Y +tmpPosY +(DstRest->bottom - DstRest->top)/2.0f, 0.0f);
		glRotatef(RotateAngle, 0, 0, 1);


		vw_SendVertices(RI_TRIANGLE_STRIP, 4, RI_2f_XYZ | RI_4f_COLOR | RI_2f_TEX, tmp, 8*sizeof(float));


        glPopMatrix();

		delete [] tmp;


	vw_SetTexAlpha(false, 0.5f);
    vw_SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	vw_SetTextureDef(0);

}
