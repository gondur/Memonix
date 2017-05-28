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



#ifndef RendererInterface_H
#define RendererInterface_H


#include "../../Core.h"


struct eDevCaps
{
	// Max multtextures
	int MaxMultTextures;
	// Max texture width
	int MaxTextureWidth;
	// Max texture height
	int MaxTextureHeight;
	// Total video memory
	int VidMemTotal;
	// макс. кол-во одновременно обрабатываемых источников света
	int MaxActiveLights;
	// макс. уровень антиалиасинга, 0-нет, 2+ - есть
	int MaxMultiSampleType;
};


// Max possible texture count
#define MAX_TEX_COUNT						8
// Device type
#define RI_DEVTYPE_HARDW					0x100A
#define RI_DEVTYPE_SOFTW					0x100B

// Point 0-0 in the upper left corner
#define RI_UL_CORNER						0x1011
// Point 0-0 in the bottom left corner
#define RI_BL_CORNER						0x1012



// Common functions

// Initialization renderer
bool vw_InitRenderer(char* Title, int Width, int Height, int *Bits, BOOL FullScreenFlag, int *FSAA);
// Shutdown renderer dll
void vw_ShutdownRenderer(void);
// Get device capability
void vw_GetDevCaps(eDevCaps *DevCaps);

void vw_SetAspectRation(float nWidth, float nHeight, bool Value);
bool vw_GetAspectWH(float *ARWidth, float *ARHeight);





// Set viewport data
void vw_SetViewport(int x, int y, int width, int height, float znear, float zfar, int Corner = RI_UL_CORNER);
// Get viewport data
void vw_GetViewport(int *x, int *y, int *width, int *height, float *znear, float *zfar);
// Resize scene
void vw_ResizeScene(float nfAngle, float AR, float nfNearClip, float nfFarClip);
// Function for window WM_SIZE message only
void vw_OnChangeSize(int nWidth, int nHeight);



// Basic rendering functions

// Begin rendering
void vw_BeginRendering(void);
// End rendering
void vw_EndRendering(void);
// Start 2D rendering mode
void vw_Start2DMode(float nZ1, float nZ2);
// End 2D rendering mode
void vw_End2DMode(void);
// Set scene clear color
void vw_SetClearColor(float nRed, float nGreen, float nBlue, float nAlpha);





// Texture functions

// Set texture by void pointer
void vw_SetTextureV(DWORD Stage, eTexture *Texture);
// Create texture
void *vw_CreateTexture(BYTE *ustDIB, int Width, int Height, bool MipMap, int Bytes);
// Delete texture
void vw_DeleteTexture(void *nOffsetID);

// Texture filtering modes
#define RI_MAGFILTER_POINT					0x103000
#define RI_MAGFILTER_LINEAR					0x103100
#define RI_MAGFILTER_ANISOTROPIC			0x103200
#define RI_MINFILTER_POINT					0x103000
#define RI_MINFILTER_LINEAR					0x103010
#define RI_MINFILTER_ANISOTROPIC			0x103020
#define RI_MIPFILTER_NONE					0x103000
#define RI_MIPFILTER_POINT					0x103001
#define RI_MIPFILTER_LINEAR					0x103002
// Basic filters
#define RI_TEXTURE_NONE			RI_MAGFILTER_POINT | RI_MINFILTER_POINT | RI_MIPFILTER_NONE
#define RI_TEXTURE_BILINEAR		RI_MAGFILTER_LINEAR | RI_MINFILTER_LINEAR | RI_MIPFILTER_POINT
#define RI_TEXTURE_TRILINEAR	RI_MAGFILTER_LINEAR | RI_MINFILTER_LINEAR | RI_MIPFILTER_LINEAR
#define RI_TEXTURE_ANISOTROPIC	RI_MAGFILTER_ANISOTROPIC | RI_MINFILTER_ANISOTROPIC | RI_MIPFILTER_LINEAR
// Set texture filtering mode
void vw_SetTexFiltering(DWORD Stage, int nFiltering);

// Texture address modes
#define RI_WRAP_U							0x10410
#define RI_WRAP_V							0x10401
#define RI_CLAMP							0x10400
// Set texture address mode
void vw_SetTexAddressMode(DWORD Stage, int nAddressMode);

// Set texture Alpha value that specifies a reference alpha value against which pixels are tested
void vw_SetTexAlpha(bool Flag, float Value);

// Texture blending factors
// Blend factor is (0, 0, 0, 0).
#define RI_BLEND_ZERO						0x1070
// Blend factor is (1, 1, 1, 1).
#define RI_BLEND_ONE						0x1071
// Blend factor is (Rs, Gs, Bs, As).
#define RI_BLEND_SRCCOLOR					0x1072
// Blend factor is (1–Rs, 1–Gs, 1–Bs, 1–As).
#define RI_BLEND_INVSRCCOLOR				0x1073
// Blend factor is (As, As, As, As).
#define RI_BLEND_SRCALPHA					0x1074
// Blend factor is (1–As, 1–As, 1–As, 1–As).
#define RI_BLEND_INVSRCALPHA				0x1075
// Blend factor is (Ad, Ad, Ad, Ad).
#define RI_BLEND_DESTALPHA					0x1076
// Blend factor is (1–Ad, 1–Ad, 1–Ad, 1–Ad).
#define RI_BLEND_INVDESTALPHA				0x1077
// Blend factor is (Rd, Gd, Bd, Ad).
#define RI_BLEND_DESTCOLOR					0x1078
// Blend factor is (1–Rd, 1–Gd, 1–Bd, 1–Ad).
#define RI_BLEND_INVDESTCOLOR				0x1079
// Blend factor is (f, f, f, 1); f = min(As, 1–Ad).
#define RI_BLEND_SRCALPHASAT				0x107A
// Set texture blending factor
void vw_SetTexBlend(int Src, int Dst);

// Reset texture blending and alpha
void vw_SetTextureDef(DWORD Stage);
// Set texture priority
void vw_SetPrioritizeTextures(void *nOffsetID, float Prior);
// Get texture priority
void vw_GetPrioritizeTextures(void *nOffsetID, float *Prior);

// Texture blending modes
// Parametre name
#define RI_TBLEND_COLOROP					0x103051
#define RI_TBLEND_ALPHAOP					0x103052
#define RI_TBLEND_ALPHAARG1					0x103053
#define RI_TBLEND_ALPHAARG2					0x103054
#define RI_TBLEND_ALPHAARG3					0x103055
#define RI_TBLEND_COLORARG1					0x103056
#define RI_TBLEND_COLORARG2					0x103057
#define RI_TBLEND_COLORARG3					0x103058
// Parametre
#define RI_TBLEND_SOURCE1					0x103061
#define RI_TBLEND_SOURCE2					0x103062
#define RI_TBLEND_MODULATE					0x103063
#define RI_TBLEND_MODULATE2X				0x103064
#define RI_TBLEND_MODULATE4X				0x103065
#define RI_TBLEND_ADD						0x103066
#define RI_TBLEND_ADDSMOOTH					0x103067
#define RI_TBLEND_ADD_SIGNED				0x103068
#define RI_TBLEND_SUBTRACT					0x103069
#define RI_TBLEND_DIFFUSE_ALPHA				0x103070
#define RI_TBLEND_TEXTURE_ALPHA				0x103071
#define RI_TBLEND_CURRENT_ALPHA				0x103072
#define RI_TBLEND_DOTPRODUCT				0x103073
#define RI_TBLEND_CURRENT					0x103080
#define RI_TBLEND_TEXTURE					0x103081
#define RI_TBLEND_CONSTANT					0x103082
#define RI_TBLEND_DIFFUSE					0x103083
#define RI_TBLEND_SPECULAR					0x103084
// Set texture blending mode
void vw_SetTextureBlendMode(DWORD stage, int pname, int param);



// 3D rendering functions

// Primitives types
#define RI_POINTS							0x1020
#define RI_LINES							0x1021
#define RI_TRIANGLES						0x1022
#define RI_TRIANGLE_STRIP					0x1023
#define RI_TRIANGLE_FAN						0x1024
// Data format
#define RI_3f_XYZ							0x1051000
#define RI_2f_XYZ							0x1052000
#define RI_3f_NORMAL						0x1050100
#define RI_4f_COLOR							0x1050010
#define RI_2f_TEX							0x1050001
#define RI_4f_TEX							0x1050002
#define RI_6f_TEX							0x1050003
#define RI_8f_TEX							0x1050004
#define RI_10f_TEX							0x1050005
#define RI_12f_TEX							0x1050006
#define RI_14f_TEX							0x1050007
#define RI_16f_TEX							0x1050008
// Send (draw) vertices
void vw_SendVertices(int PrimitiveType, int NumVertices, int DataFormat, void *Data, int Stride);

// Set color
void vw_SetColor(float nRed, float nGreen, float nBlue, float nAlpha);

// Polygon Mode
#define RI_POINT							0x10B1
#define RI_LINE								0x10B2
#define RI_FILL								0x10B3
// Set polygon rasterization mode
void vw_PolygonMode(int mode);

// Cull Face
#define RI_NONE								0x10C1
#define RI_BACK								0x10C2
#define RI_FRONT							0x10C3
// Set what facets can be culled
void vw_CullFace(int face);

// Set depth buffer status
 /* NEVER                = 1,
    LESS                 = 2,
    EQUAL                = 3,
    LESSEQUAL            = 4,
    GREATER              = 5,
    NOTEQUAL             = 6,
    GREATEREQUAL         = 7,
    ALWAYS               = 8,
*/
void vw_DepthTest(bool mode, int funct);

// Loads identity in the current matrix
void vw_LoadIdentity(void);
// Determines the product of the current matrix and the computed translation matrix determined by the given factors
void vw_Translate(float fX, float fY, float fZ);
// Determines the product of the current matrix and the computed rotation matrix
void vw_Rotate(float fX, float fY, float fZ);
// Determines the product of the current matrix and the computed scale matrix composed from the given point
void vw_Scale(float fX, float fY, float fZ);
// Adds a matrix to the stack
void vw_PushMatrix(void);
// Removes the current matrix from the top of the stack
void vw_PopMatrix(void);

// Matrix types
#define RI_PROJECTION_MATRIX				0x1080
#define RI_MODELVIEW_MATRIX					0x1081
// Get matrix
void vw_GetMatrix(int pname, float *params);
void vw_SetMatrix(int pname, float *params);


// Set lighting status
void vw_Lighting(bool param);
// Get lighting status
bool vw_GetLighting(void);
// Enable light
void vw_LightEnable(int light, bool param);
// Get light status
bool vw_GetLightEnable(int light);

// Light parametres
#define RI_SPOT_EXPONENT					0x1090
#define RI_SPOT_CUTOFF						0x1091
#define RI_CONSTANT_ATTENUATION				0x1092
#define RI_LINEAR_ATTENUATION				0x1093
#define RI_QUADRATIC_ATTENUATION			0x1094
#define RI_AMBIENT							0x1095
#define RI_DIFFUSE							0x1096
#define RI_SPECULAR							0x1097
#define RI_POSITION							0x1098
#define RI_DIRECTION						0x1099
#define RI_EMISSION							0x109A
#define RI_SHININESS						0x109B


// Set light parametre by float
void vw_SetLight(int light, int pname, float param);
// Set light parametre by vector
void vw_SetLightV(int light, int pname, const float *param);
// Get light parametre by vector
void vw_GetLightV(int light, int pname, float *param);
// Set matirial parametre by vector
void vw_MaterialV(int pname, const float *param);
// Get matirial parametre by vector
void vw_GetMaterialV(int pname, float *param);




// Get rendered primitives count
int vw_GetPrimCount(void);

// Set gamma ramp
void vw_SetGammaRamp(float Gamma, float Contrast, float Brightness);
// Get gamma ramp
void vw_GetGammaRamp(float *Gamma, float *Contrast, float *Brightness);

// Get texture image bitmap (RGBA) by void pointer
void vw_GetTextureImage(eTexture *Texture, void *bits, int BPP);







// 2D rendering functions

// Draw
void vw_Draw(int X, int Y, RECT *SrcRest, eTexture *Tex, bool Alpha, float RotateAngle=0, int DrawCorner = RI_UL_CORNER);
// Draw transparent
void vw_DrawTransparent(RECT *DstRest, RECT *SrcRest, eTexture *Tex, bool Alpha, float Transp, float RotateAngle=0, int DrawCorner = RI_UL_CORNER, float R=1.0f, float G=1.0f, float B=1.0f);










void vw_DrawRect(int X, int Y, int left, int top, int right, int bottom, const char *TexName, bool Alpha = false);
bool vw_Button2D(int X, int Y, RECT *MDetect, RECT *DrawON, RECT *DrawOFF, const char *TexName, bool ResetMouse = true, bool Alpha = false, bool LeftMouseBut = true);

eTexture *vw_AddToTexture(const char *NameDst, const char *NameSrc, int DestX, int DestY, RECT *SrcRect);







// Font

struct eFont
{
	int		Size;					// Font size
	eTexture *Texture;				// Texture
	int		TexCoords[128-32][4];	// Texture coords

	eFont*	Prev;		// Pointer to the previous loaded font in the memory
	eFont*	Next;		// Pointer to the next loaded font in the memory
};

// Create font
eFont*	vw_CreateFont(int LoadAs=AUTO_FILE, char *FontName = NULL, int FontSize = 0, DWORD TextColor = 0x00FFFFFF, DWORD BkColor = 0x00000000);
// Release font
void	vw_ReleaseFont(eFont* Font);
// Release all fonts
void	vw_ReleaseAllFonts();
// Print text
void	vw_Print(eFont* Font, float X, float Y, float FlattenWidth, float MaxWidth, int CharSet, int Corner, float Transparent, const char *Text, ...);










#endif // RendererInterface_H
