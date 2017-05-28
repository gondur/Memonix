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


extern	int tmpPrimCountGL;
extern	PFNGLCLIENTACTIVETEXTUREARBPROC	glClientActiveTexture_ARB;




extern int VertexIndexCount;
extern GLuint *VertexIndex;




////////////////////////////////////////////////////////////
// процедура передачи последовательности вертексов
////////////////////////////////////////////////////////////
void vw_SendVertices(int PrimitiveType, int NumVertices, int DataFormat, void *Data, int Stride)
{

	


        // обязательно в байты, т.к. делаем смещение в байтах!
		BYTE *TMP = (BYTE *)Data;

		// чтобы знать сколько отступать, кол-во ед. элементов, в нашем случае float
		int AddStride = 0;
		// кол-во текстур
		int TextQ = DataFormat & 0x000000F;

		// делаем установку поинтеров + ставим смещения для прорисовки
		if ((DataFormat & 0x105F000) == RI_3f_XYZ)
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, Stride, TMP + AddStride);
			AddStride += 3*sizeof(GLfloat);
		}

		if ((DataFormat & 0x105F000) == RI_2f_XYZ)
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(2, GL_FLOAT, Stride, TMP + AddStride);
			AddStride += 2*sizeof(GLfloat);
		}

		if ((DataFormat & 0x1050F00) == RI_3f_NORMAL)
		{
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, Stride, TMP + AddStride);
			AddStride += 3*sizeof(GLfloat);
		}

		if ((DataFormat & 0x10500F0) == RI_4f_COLOR)
		{
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_FLOAT, Stride, TMP + AddStride);
			AddStride += 4*sizeof(GLfloat);
		}

		if (TextQ > 0)// текстурные коорд. есть...
		{
			if (glClientActiveTexture_ARB == NULL)
            {
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glTexCoordPointer(2, GL_FLOAT,Stride, TMP + AddStride);
				AddStride += 2*sizeof(GLfloat);
            }
            else
            {
                for (int i=0; i<TextQ; i++)
                {
                    glClientActiveTexture_ARB(GL_TEXTURE0_ARB+i);
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                    glTexCoordPointer(2, GL_FLOAT, Stride, TMP + AddStride);
                    AddStride += 2*sizeof(GLfloat);
                }
            }
		



		// собираем если нужно массив индексов
		if (VertexIndexCount < NumVertices)
		{
			VertexIndexCount = NumVertices;
			VertexIndex = new GLuint[NumVertices];
			for (int i=0; i<NumVertices; i++) VertexIndex[i] = i;
		}



		// рисуем
		switch(PrimitiveType)
		{
			case RI_POINTS:
                		glDrawElements(GL_POINTS,NumVertices,GL_UNSIGNED_INT,VertexIndex);
				tmpPrimCountGL += NumVertices;
				break;

			case RI_LINES:
               			glDrawElements(GL_LINES,NumVertices,GL_UNSIGNED_INT,VertexIndex);
				tmpPrimCountGL += NumVertices/2;
				break;

			case RI_TRIANGLES:
				glDrawElements(GL_TRIANGLES,NumVertices,GL_UNSIGNED_INT,VertexIndex);
				tmpPrimCountGL += NumVertices/3;
				break;

			case RI_TRIANGLE_STRIP:
				glDrawElements(GL_TRIANGLE_STRIP,NumVertices,GL_UNSIGNED_INT,VertexIndex);
				tmpPrimCountGL += NumVertices-2;
				break;

			case RI_TRIANGLE_FAN:
				glDrawElements(GL_TRIANGLE_FAN,NumVertices,GL_UNSIGNED_INT,VertexIndex);
				tmpPrimCountGL += NumVertices-2;
				break;
		}





		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

        if (glClientActiveTexture_ARB != NULL)
        {
            for (int i=0; i<TextQ; i++)
            {
                glClientActiveTexture_ARB(GL_TEXTURE0_ARB+i);
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            }
            glClientActiveTexture_ARB(GL_TEXTURE0_ARB);
        }
        else
        	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}



}
