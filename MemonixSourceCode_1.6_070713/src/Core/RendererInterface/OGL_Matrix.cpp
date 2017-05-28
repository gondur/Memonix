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








////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_LoadIdentity()
{
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_Translate(float fX, float fY, float fZ)
{
	//glMatrixMode(GL_MODELVIEW);
	glTranslatef(fX, fY, fZ);
}



////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_Rotate(float fX, float fY, float fZ)
{
	//glMatrixMode(GL_MODELVIEW);
	if (fX != 0) glRotatef(fX, 1, 0, 0);
	if (fY != 0) glRotatef(fY, 0, 1, 0);
	if (fZ != 0) glRotatef(fZ, 0, 0, 1);
}



////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_Scale(float fX, float fY, float fZ)
{
	//glMatrixMode(GL_MODELVIEW);
	glScalef(fX, fY, fZ);
}












////////////////////////////////////////////////////////////
// // получение матриц
////////////////////////////////////////////////////////////
void vw_GetMatrix(int pname, float *params)
{
	if (pname == RI_PROJECTION_MATRIX)
		glGetFloatv( GL_PROJECTION_MATRIX, params );

	if (pname == RI_MODELVIEW_MATRIX)
		glGetFloatv( GL_MODELVIEW_MATRIX, params );
}
void vw_SetMatrix(int pname, float *params)
{
	if (pname == RI_PROJECTION_MATRIX)
		glMatrixMode(GL_PROJECTION_MATRIX);

	if (pname == RI_MODELVIEW_MATRIX)
		glMatrixMode(GL_MODELVIEW_MATRIX);

	glLoadMatrixf(params);
}



////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_PushMatrix(void)
{
	//glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
}



////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_PopMatrix(void)
{
	//glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
