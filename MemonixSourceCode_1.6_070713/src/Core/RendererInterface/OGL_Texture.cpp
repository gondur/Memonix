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




extern	bool anisotropic_filterGL;
extern	int anisotropic_angleGL;
extern	PFNGLACTIVETEXTUREARBPROC glActiveTexture_ARB;







////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void *vw_CreateTexture(BYTE *ustDIB, int Width, int Height, bool MipMap, int Bytes)
{
	// Alpha канал должен быть сформирован до этого...+ nAlpha=true
	GLuint *res = 0;
	res = new GLuint;
	if (res == 0) return 0;

	glGenTextures(1, res);
    glBindTexture(GL_TEXTURE_2D, *res);


	if (MipMap)
	{
		if (Bytes == 4)
			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, Width, Height,
					 GL_RGBA, GL_UNSIGNED_BYTE, ustDIB);
		else
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, Width, Height,
					 GL_RGB, GL_UNSIGNED_BYTE, ustDIB);
	}
	else
	{
		if (Bytes == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, 4, Width, Height,
						 0, GL_RGBA, GL_UNSIGNED_BYTE, ustDIB);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, 3, Width, Height,
						 0, GL_RGB, GL_UNSIGNED_BYTE, ustDIB);
	}


	return res;
}



////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_DeleteTexture(void *nOffsetID)
{
	if (nOffsetID == 0) return;
	GLuint *tmp = (GLuint *)nOffsetID;

	glDeleteTextures(1, tmp);
	// удаляем именно через указатель! void в gcc удалить нельзя
	delete tmp;
}





////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_SetTextureV(DWORD Stage, eTexture *Texture)
{
	if (Texture == 0) return;
	GLuint *tmp = (GLuint *)Texture->OffsetID;


	Texture->TexturePrior = 1.0f;

    if (glActiveTexture_ARB == NULL)
    {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, *tmp);
    }
    else
    {
        glActiveTexture_ARB(GL_TEXTURE0_ARB + Stage);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, *tmp);

        glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);

        if (Stage > 0)
        {
            // данные для смешение цвета - добавляем к существ.
            glTexEnvi (GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_ADD_SIGNED_EXT);
            glTexEnvi (GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT, GL_TEXTURE);
            glTexEnvi (GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, GL_PREVIOUS_EXT);
            // данные для смешение альфы - всегда 1-й слой...
            glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, GL_ADD);
            glTexEnvf (GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT, GL_TEXTURE);
            glTexEnvf (GL_TEXTURE_ENV, GL_OPERAND0_ALPHA_EXT, GL_SRC_ALPHA);
            glTexEnvf (GL_TEXTURE_ENV, GL_SOURCE1_ALPHA_EXT, GL_PREVIOUS_EXT);
            glTexEnvf (GL_TEXTURE_ENV, GL_OPERAND1_ALPHA_EXT, GL_SRC_ALPHA);
        }
        else
        {
            // первая текстура, нужно заменить все
            glTexEnvi (GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_MODULATE);
            glTexEnvi (GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT, GL_TEXTURE);
            glTexEnvi (GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, GL_PREVIOUS_EXT);

            glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, GL_MODULATE);
            glTexEnvf (GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT, GL_TEXTURE);
            glTexEnvf (GL_TEXTURE_ENV, GL_OPERAND0_ALPHA_EXT, GL_SRC_ALPHA);
            glTexEnvf (GL_TEXTURE_ENV, GL_SOURCE1_ALPHA_EXT, GL_PREVIOUS_EXT);
            glTexEnvf (GL_TEXTURE_ENV, GL_OPERAND1_ALPHA_EXT, GL_SRC_ALPHA);
        }
    }
}



////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_SetTextureBlendMode(DWORD stage, int pname, int param)
{
	GLenum  cmd;
	GLenum  arg;

	switch (pname)
	{
		case RI_TBLEND_COLOROP:
			cmd = GL_COMBINE_RGB;
			break;
		case RI_TBLEND_ALPHAOP:
			cmd = GL_COMBINE_ALPHA;
			break;
		case RI_TBLEND_ALPHAARG1:
			cmd = GL_OPERAND0_ALPHA;
			break;
		case RI_TBLEND_ALPHAARG2:
			cmd = GL_OPERAND1_ALPHA;
			break;
		case RI_TBLEND_ALPHAARG3:
			cmd = GL_OPERAND2_ALPHA;
			break;
		case RI_TBLEND_COLORARG1:
			cmd = GL_SOURCE0_RGB;
			break;
		case RI_TBLEND_COLORARG2:
			cmd = GL_SOURCE1_RGB;
			break;
		case RI_TBLEND_COLORARG3:
			cmd = GL_SOURCE2_RGB;
			break;
	}

	switch (param)
	{
		case RI_TBLEND_SOURCE1:
			arg = GL_REPLACE;
			break;
		case RI_TBLEND_SOURCE2:
			arg = GL_REPLACE;
			break;
		case RI_TBLEND_MODULATE:
			arg = GL_MODULATE;
			break;
		case RI_TBLEND_MODULATE2X:
			arg = GL_MODULATE;
			break;
		case RI_TBLEND_MODULATE4X:
			arg = GL_MODULATE;
			break;
		case RI_TBLEND_ADD:
			arg = GL_ADD;
			break;
		case RI_TBLEND_ADDSMOOTH:
			arg = GL_ADD;
			break;
		case RI_TBLEND_ADD_SIGNED:
			arg = GL_ADD_SIGNED;
			break;
		case RI_TBLEND_SUBTRACT:
			arg = GL_SUBTRACT;
			break;
		case RI_TBLEND_DIFFUSE_ALPHA:
		case RI_TBLEND_TEXTURE_ALPHA:
		case RI_TBLEND_CURRENT_ALPHA:
			arg = GL_INTERPOLATE;
			break;
		case RI_TBLEND_DOTPRODUCT:
			arg = GL_DOT3_RGB;
			break;

		case RI_TBLEND_CURRENT:
			arg = GL_PREVIOUS;
			break;
		case RI_TBLEND_TEXTURE:
			arg = GL_TEXTURE;
			break;
		case RI_TBLEND_CONSTANT:
			arg = GL_CONSTANT;
			break;
		case RI_TBLEND_DIFFUSE:
			arg = GL_PRIMARY_COLOR;
			break;
		case RI_TBLEND_SPECULAR: // ---
			arg = 0;
			break;
	}


    if (glActiveTexture_ARB != NULL)
    {
        glActiveTexture_ARB(GL_TEXTURE0_ARB + stage);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
    }

	// работаем с MODULATE
	switch (param)
	{
		case RI_TBLEND_MODULATE2X:
			if (pname == RI_TBLEND_COLOROP) glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE, 2);
			else glTexEnvi(GL_TEXTURE_ENV, 	GL_ALPHA_SCALE , 2);
			break;
		case RI_TBLEND_MODULATE4X:
			if (pname == RI_TBLEND_COLOROP) glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE, 4);
			else glTexEnvi(GL_TEXTURE_ENV, 	GL_ALPHA_SCALE , 4);
			break;
		default:
			if (pname == RI_TBLEND_COLOROP) glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE, 1);
			else glTexEnvi(GL_TEXTURE_ENV, 	GL_ALPHA_SCALE , 1);
			break;
	}


	glTexEnvi(GL_TEXTURE_ENV, cmd, arg);
}




////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_SetTexFiltering(DWORD Stage, int nFiltering)
{
    if (glActiveTexture_ARB != NULL)
        glActiveTexture_ARB(GL_TEXTURE0_ARB + Stage);

	// перебираем по мип-меп фильтру
	switch (nFiltering & 0x00000F)
	{
		case 0: // RI_MIPFILTER_NONE
			if ((nFiltering & 0x1030F0) == RI_MINFILTER_POINT)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			if ((nFiltering & 0x1030F0) == RI_MINFILTER_LINEAR)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			if ((nFiltering & 0x1030F0) == RI_MINFILTER_ANISOTROPIC)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			break;
		case 1: // RI_MIPFILTER_POINT
			if ((nFiltering & 0x1030F0) == RI_MINFILTER_POINT)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			if ((nFiltering & 0x1030F0) == RI_MINFILTER_LINEAR)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			if ((nFiltering & 0x1030F0) == RI_MINFILTER_ANISOTROPIC)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			break;
		case 2: // RI_MIPFILTER_LINEAR
			if ((nFiltering & 0x1030F0) == RI_MINFILTER_POINT)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			if ((nFiltering & 0x1030F0) == RI_MINFILTER_LINEAR)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			if ((nFiltering & 0x1030F0) == RI_MINFILTER_ANISOTROPIC)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			break;

	}


	// ставим MAG фильтр
	if ((nFiltering & 0x103F00) == RI_MAGFILTER_POINT)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	if ((nFiltering & 0x103F00) == RI_MAGFILTER_LINEAR)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if ((nFiltering & 0x103F00) == RI_MAGFILTER_ANISOTROPIC) // лучшее + анизотропия
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	// ставим ANISOTROPY
	if (((nFiltering & 0x103F00) == RI_MAGFILTER_ANISOTROPIC)||
		((nFiltering & 0x1030F0) == RI_MINFILTER_ANISOTROPIC))
	{
		if (anisotropic_filterGL)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropic_angleGL);
	}
	else
	{
		if (anisotropic_filterGL)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
	}

}



////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_SetTexAddressMode(DWORD Stage, int nAddressMode)
{
    if (glActiveTexture_ARB != NULL)
        glActiveTexture_ARB(GL_TEXTURE0_ARB + Stage);

	if ((nAddressMode & 0x10410) == RI_WRAP_U)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	else
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);

	if ((nAddressMode & 0x10401) == RI_WRAP_V)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	else
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}



////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_SetTexAlpha(bool Flag, float Value)
{
	if (Flag)
	{
		glAlphaFunc(GL_GREATER, Value);
		glEnable(GL_ALPHA_TEST);
	}
	else
	{
		glAlphaFunc(GL_GREATER, 1.0f);
		glDisable(GL_ALPHA_TEST);
	}
}



////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_SetTexBlend(int Src, int Dst)
{
	int tmpSRC,tmpDST;

	switch(Src)
	{
		case RI_BLEND_ZERO:
			tmpSRC = GL_ZERO;
			break;
		case RI_BLEND_ONE:
			tmpSRC = GL_ONE;
			break;
		case RI_BLEND_SRCCOLOR:
			tmpSRC = GL_SRC_COLOR;
			break;
		case RI_BLEND_INVSRCCOLOR:
			tmpSRC = GL_ONE_MINUS_SRC_COLOR;
			break;
		case RI_BLEND_INVSRCALPHA:
			tmpSRC = GL_ONE_MINUS_SRC_ALPHA;
			break;
		case RI_BLEND_DESTALPHA:
			tmpSRC = GL_DST_ALPHA;
			break;
		case RI_BLEND_INVDESTALPHA:
			tmpSRC = GL_ONE_MINUS_DST_ALPHA;
			break;
		case RI_BLEND_SRCALPHA:
			tmpSRC = GL_SRC_ALPHA;
			break;
		case RI_BLEND_DESTCOLOR:
			tmpSRC = GL_DST_COLOR;
			break;
		case RI_BLEND_INVDESTCOLOR:
			tmpSRC = GL_ONE_MINUS_DST_COLOR;
			break;
		case RI_BLEND_SRCALPHASAT:
			tmpSRC = GL_SRC_ALPHA_SATURATE;
			break;
		default:
			tmpSRC = GL_ONE;
			break;
	}
	switch(Dst)
	{
		case RI_BLEND_ZERO:
			tmpDST = GL_ZERO;
			break;
		case RI_BLEND_ONE:
			tmpDST = GL_ONE;
			break;
		case RI_BLEND_SRCCOLOR:
			tmpDST = GL_SRC_COLOR;
			break;
		case RI_BLEND_INVSRCCOLOR:
			tmpDST = GL_ONE_MINUS_SRC_COLOR;
			break;
		case RI_BLEND_INVSRCALPHA:
			tmpDST = GL_ONE_MINUS_SRC_ALPHA;
			break;
		case RI_BLEND_DESTALPHA:
			tmpDST = GL_DST_ALPHA;
			break;
		case RI_BLEND_INVDESTALPHA:
			tmpDST = GL_ONE_MINUS_DST_ALPHA;
			break;
		case RI_BLEND_SRCALPHA:
			tmpDST = GL_SRC_ALPHA;
			break;
		case RI_BLEND_DESTCOLOR:
			tmpDST = GL_DST_COLOR;
			break;
		case RI_BLEND_INVDESTCOLOR:
			tmpDST = GL_ONE_MINUS_DST_COLOR;
			break;
		case RI_BLEND_SRCALPHASAT:
			tmpDST = GL_SRC_ALPHA_SATURATE;
			break;
		default:
			tmpDST = GL_ZERO;
			break;
	}

	glEnable(GL_BLEND);
	glBlendFunc(tmpSRC, tmpDST);

}



////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_SetTextureDef(DWORD Stage)
{
    vw_SetColor(1.0f, 1.0f, 1.0f, 1.0f);

    if (glActiveTexture_ARB == NULL)
    {
  		if (anisotropic_filterGL)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);

		glDisable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ZERO);
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_TEXTURE_2D);

    }
    else
    {
        glActiveTexture_ARB(GL_TEXTURE0_ARB + Stage);

  		if (anisotropic_filterGL)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);

        glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
        // данные для смешение цвета - заменяем...
		glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE);

        if (Stage > 0)
        {
            // данные для смешение цвета - добавляем к существ.
            glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_ADD);
            // данные для смешение альфы - всегда 1-й слой...
            glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, GL_ADD);
        }

        glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, GL_MODULATE);
        glTexEnvf (GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT, GL_TEXTURE);
        glTexEnvf (GL_TEXTURE_ENV, GL_OPERAND0_ALPHA_EXT, GL_SRC_ALPHA);
        glTexEnvf (GL_TEXTURE_ENV, GL_SOURCE1_ALPHA_EXT, GL_RGB);
        glTexEnvf (GL_TEXTURE_ENV, GL_OPERAND1_ALPHA_EXT, GL_SRC_ALPHA);

        glDisable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ZERO);
        glDisable(GL_ALPHA_TEST);
        glDisable(GL_TEXTURE_2D);
        glActiveTexture_ARB(GL_TEXTURE0_ARB);
    }

}







////////////////////////////////////////////////////////////
// получение GL_RGBA-GL_RGB набора из текстуры...
////////////////////////////////////////////////////////////
void vw_GetTextureImage(eTexture *Texture, void *bits, int BPP)
{
	if (Texture == 0) return;
	GLuint *tmp = (GLuint *)Texture->OffsetID;

	glBindTexture(GL_TEXTURE_2D, *tmp);
	if (BPP == 4)
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, bits);
	else
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, bits);
}



////////////////////////////////////////////////////////////
// установка приоритета текстуры 0-1
////////////////////////////////////////////////////////////
void vw_SetPrioritizeTextures(void *nOffsetID, float Prior)
{
	if (nOffsetID == 0) return;
	GLuint *tmp = (GLuint *)nOffsetID;

	glPrioritizeTextures( 1, tmp, &Prior);
}



////////////////////////////////////////////////////////////
// получение текущего приоритета
////////////////////////////////////////////////////////////
void vw_GetPrioritizeTextures(void *nOffsetID, float *Prior)
{
	if (nOffsetID == 0) return;
	GLuint *tmp = (GLuint *)nOffsetID;

	glBindTexture(GL_TEXTURE_2D, *tmp);
	glGetTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_PRIORITY, Prior);
}




