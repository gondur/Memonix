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











void vw_DrawRect(int X, int Y, int left, int top, int right, int bottom, const char *TexName, bool Alpha)
{
	RECT SrcRest;

	// прорисовка подложки главного меню...
	SetRect(&SrcRest, left,top,right,bottom);
	vw_Draw(X,Y,&SrcRest, vw_FindTextureByName(TexName), Alpha);

}










bool vw_Button2D(int X, int Y, RECT *MDetect, RECT *DrawON, RECT *DrawOFF, const char *TexName, bool ResetMouse, bool Alpha, bool LeftMouseBut)
{

	if (vw_OnRect(MDetect))
	{
		vw_Draw(X,Y, DrawON, vw_FindTextureByName(TexName), Alpha);
		// нажали...
		if (LeftMouseBut)
		{
			return vw_GetWindowLBMouse(ResetMouse);
		}
		else
		{
			return vw_GetWindowRBMouse(ResetMouse);
		}
	}
	else
	{
		vw_Draw(X,Y, DrawOFF, vw_FindTextureByName(TexName), Alpha);
	}

	// просто прорисовали...
	return false;
}









//------------------------------------------------------------------------------------
// вклеиваем одну текстуру в другую...
//------------------------------------------------------------------------------------
eTexture *vw_AddToTexture(const char *NameDst, const char *NameSrc, int DestX, int DestY, RECT *SrcRect)
{
	eTexture* res;

		char NameDst1[MAX_PATH];
		strcpy(NameDst1, NameDst);


		// получаем массивы пикселей
		eTexture *Dst = vw_FindTextureByName(NameDst1);
		int Dst_Width = Dst->Width;
		int Dst_Height = Dst->Height;

		BYTE *ImageDataDst = 0;
		ImageDataDst = new BYTE[Dst->Height*Dst->Width*4];
		// вытягиваем данные в RGBA, независимо от Dst->Bytes
		vw_GetTextureImage(Dst, ImageDataDst, 4);

		eTexture *Src = vw_FindTextureByName(NameSrc);
		BYTE *ImageDataSrc = 0;
		ImageDataSrc = new BYTE[Src->Height*Src->Width*4];
		// вытягиваем данные в RGBA, независимо от Src->Bytes
		vw_GetTextureImage(Src, ImageDataSrc, 4);


		// проверять, чтобы входило в размеры куда клеить, иначе - корректировать их
		if (DestY > Dst->Height) DestY = Dst->Height;
		if (DestX > Dst->Width) DestX = Dst->Width;
		if (DestY < 0) DestY = 0;
		if (DestX < 0) DestX = 0;
		if (SrcRect->bottom > Dst->Height) SrcRect->bottom = Dst->Height;
		if (SrcRect->right > Dst->Width) SrcRect->right = Dst->Width;
		if (SrcRect->top < 0) SrcRect->top = 0;
		if (SrcRect->left < 0) SrcRect->left = 0;


		// "вклеиваем" один поверх другого + складываем альфа канал
		for (int i=SrcRect->left; i<=SrcRect->right-1; i++)
		for (int j=SrcRect->top+1; j<=SrcRect->bottom; j++)
		{

			ImageDataDst[((i+DestX)+Dst->Width*(Dst->Height-j-DestY))*4] =  (BYTE)((ImageDataDst[((i+DestX)+Dst->Width*(Dst->Height-j-DestY))*4]/255.0f)*(255.0f-ImageDataSrc[(i+Src->Width*(Src->Height-j))*4+3]) + (ImageDataSrc[(i+Src->Width*(Src->Height-j))*4]/255.0f)*ImageDataSrc[(i+Src->Width*(Src->Height-j))*4+3]);
			ImageDataDst[((i+DestX)+Dst->Width*(Dst->Height-j-DestY))*4+1] = (BYTE)((ImageDataDst[((i+DestX)+Dst->Width*(Dst->Height-j-DestY))*4+1]/255.0f)*(255.0f-ImageDataSrc[(i+Src->Width*(Src->Height-j))*4+3]) + (ImageDataSrc[(i+Src->Width*(Src->Height-j))*4+1]/255.0f)*ImageDataSrc[(i+Src->Width*(Src->Height-j))*4+3]);
			ImageDataDst[((i+DestX)+Dst->Width*(Dst->Height-j-DestY))*4+2] = (BYTE)((ImageDataDst[((i+DestX)+Dst->Width*(Dst->Height-j-DestY))*4+2]/255.0f)*(255.0f-ImageDataSrc[(i+Src->Width*(Src->Height-j))*4+3]) + (ImageDataSrc[(i+Src->Width*(Src->Height-j))*4+2]/255.0f)*ImageDataSrc[(i+Src->Width*(Src->Height-j))*4+3]);
		}

		// создаем повторно текстуру NameDst
		vw_ReleaseTexture(vw_FindTextureByName(NameDst1));
		res = vw_LoadTextureMem(NameDst1, ImageDataDst, Dst_Width, Dst_Height, 4);
		if (0 == res) return 0;

		delete [] ImageDataDst;
		delete [] ImageDataSrc;



	return res;
}
