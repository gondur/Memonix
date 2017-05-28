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
void vw_Lighting(bool param)
{
	if (param) glEnable(GL_LIGHTING);
		else glDisable(GL_LIGHTING);

}




////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
bool vw_GetLighting(void)
{
	if (glIsEnabled(GL_LIGHTING)) return true;
	return false;
}



////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_LightEnable(int light, bool param)
{
	if (param) glEnable(GL_LIGHT0+light);
	else glDisable(GL_LIGHT0+light);
}



////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
bool vw_GetLightEnable(int light)
{
	if (glIsEnabled(GL_LIGHT0+light)) return true;
	return false;
}



////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_SetLight(int light, int pname, float param)
{
	int tmpPNAME=0;

	switch (pname)
	{
		case RI_SPOT_EXPONENT:
			tmpPNAME = GL_SPOT_EXPONENT;
			break;

		case RI_SPOT_CUTOFF:
			tmpPNAME = GL_SPOT_CUTOFF;
			break;

		case RI_CONSTANT_ATTENUATION:
			tmpPNAME = GL_CONSTANT_ATTENUATION;
			break;

		case RI_LINEAR_ATTENUATION:
			tmpPNAME = GL_LINEAR_ATTENUATION;
			break;

		case RI_QUADRATIC_ATTENUATION:
			tmpPNAME = GL_QUADRATIC_ATTENUATION;
			break;
 	}

	glLightf(GL_LIGHT0+light, tmpPNAME, param);
}



////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_SetLightV(int light, int pname, const float *param)
{
	int tmpPNAME=0;

	switch (pname)
	{
		case RI_SPOT_EXPONENT:
			tmpPNAME = GL_SPOT_EXPONENT;
			break;

		case RI_SPOT_CUTOFF:
			tmpPNAME = GL_SPOT_CUTOFF;
			break;

		case RI_CONSTANT_ATTENUATION:
			tmpPNAME = GL_CONSTANT_ATTENUATION;
			break;

		case RI_LINEAR_ATTENUATION:
			tmpPNAME = GL_LINEAR_ATTENUATION;
			break;

		case RI_QUADRATIC_ATTENUATION:
			tmpPNAME = GL_QUADRATIC_ATTENUATION;
			break;

		case RI_AMBIENT:
			tmpPNAME = GL_AMBIENT;
			break;

		case RI_DIFFUSE:
			tmpPNAME = GL_DIFFUSE;
			break;

		case RI_SPECULAR:
			tmpPNAME = GL_SPECULAR;
			break;

		case RI_POSITION:
			tmpPNAME = GL_POSITION;
			break;

		case RI_DIRECTION:
			tmpPNAME = GL_SPOT_DIRECTION;
			break;
	}

	glLightfv(GL_LIGHT0+light, tmpPNAME, param);
}



////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_GetLightV(int light, int pname, float *param)
{
	int tmpPNAME=0;

	switch (pname)
	{
		case RI_SPOT_EXPONENT:
			tmpPNAME = GL_SPOT_EXPONENT;
			break;

		case RI_SPOT_CUTOFF:
			tmpPNAME = GL_SPOT_CUTOFF;
			break;

		case RI_CONSTANT_ATTENUATION:
			tmpPNAME = GL_CONSTANT_ATTENUATION;
			break;

		case RI_LINEAR_ATTENUATION:
			tmpPNAME = GL_LINEAR_ATTENUATION;
			break;

		case RI_QUADRATIC_ATTENUATION:
			tmpPNAME = GL_QUADRATIC_ATTENUATION;
			break;

		case RI_AMBIENT:
			tmpPNAME = GL_AMBIENT;
			break;

		case RI_DIFFUSE:
			tmpPNAME = GL_DIFFUSE;
			break;

		case RI_SPECULAR:
			tmpPNAME = GL_SPECULAR;
			break;

		case RI_POSITION:
			tmpPNAME = GL_POSITION;
			break;

		case RI_DIRECTION:
			tmpPNAME = GL_SPOT_DIRECTION;
			break;
	}

	glGetLightfv(GL_LIGHT0+light, tmpPNAME, param);
}





////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_MaterialV(int pname, const float *param)
{
	int tmpPNAME=0;

	switch (pname)
	{
		case RI_AMBIENT:
			tmpPNAME = GL_AMBIENT;
			break;

		case RI_DIFFUSE:
			tmpPNAME = GL_DIFFUSE;
			break;

		case RI_SPECULAR:
			tmpPNAME = GL_SPECULAR;
			break;

		case RI_EMISSION:
			tmpPNAME = GL_EMISSION;
			break;

		case RI_SHININESS:
			tmpPNAME = GL_SHININESS;
			break;

	}

	glMaterialfv(GL_FRONT_AND_BACK, tmpPNAME, param);
}



////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////
void vw_GetMaterialV(int pname, float *param)
{
	int tmpPNAME=0;

	switch (pname)
	{
		case RI_AMBIENT:
			tmpPNAME = GL_AMBIENT;
			break;

		case RI_DIFFUSE:
			tmpPNAME = GL_DIFFUSE;
			break;

		case RI_SPECULAR:
			tmpPNAME = GL_SPECULAR;
			break;

		case RI_EMISSION:
			tmpPNAME = GL_EMISSION;
			break;

		case RI_SHININESS:
			tmpPNAME = GL_SHININESS;
			break;
	}

	glGetMaterialfv(GL_FRONT_AND_BACK, tmpPNAME, param);
}




