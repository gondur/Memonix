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


#ifndef Texture_H
#define Texture_H



// File types (for LoadAs parametre)
#define AUTO_FILE			0	// Detect by file extension
#define BMP_FILE			1	// BMP file
#define TGA_FILE			2	// TGA file
#define JPG_FILE			4	// JPG file

// Create alpha channel by image greyscale color
#define TX_ALPHA_GREYSC		0x0021
// Create alpha channel by equal Alpha color
#define TX_ALPHA_EQUAL		0x0022
// Create alpha channel by great or equal than Alpha color
#define TX_ALPHA_GEQUAL		0x0023
// Create alpha channel by less or equal Alpha color
#define TX_ALPHA_LEQUAL		0x0024
// Create alpha channel by great than Alpha color
#define TX_ALPHA_GREAT		0x0025
// Create alpha channel by less Alpha color
#define TX_ALPHA_LESS		0x0026

struct eTexture
{
	char*	Name;			// File name

	int		Filtering;		// Texture filtering mode (near, linear, ... )
	int		Address_Mode;	// Texture address mode (wrap, clamp)

	BYTE	ARed;			// Alpha channel red color
	BYTE	AGreen;			// Alpha channel green color
	BYTE	ABlue;			// Alpha channel blue color

	int		Width;			// Texture width
	int		Height;			// Texture height
	int		SrcWidth;		// Source image width
	int		SrcHeight;		// Source image height

	int		Bytes;			// Bytes Per Pixel

	// приоритет
	float	TexturePrior;

    void*	OffsetID;		// Pointer to the texture data in the memory

	eTexture*	Prev;		// Pointer to the previous loaded Texture in the memory
	eTexture*	Next;		// Pointer to the next loaded Texture in the memory
	int			Num;		// ID number
};


// eTexture functions
// Load texture from file
eTexture*	vw_LoadTexture(const char *TextureName, int LoadAs=AUTO_FILE, int NeedResizeW=0, int NeedResizeH=0);
// Load texture from memory
eTexture* vw_LoadTextureMem(const char *nName, BYTE *nDIB, int nWidth, int nHeight, int Colors);
// Release texture
void		vw_ReleaseTexture(eTexture* Texture);


// Texture manager functions

// Release all textures
void		vw_ReleaseAllTextures();
// Set textures properties
void		vw_SetTextureProp(int nFiltering, int nAddress_Mode, bool nAlpha = false, int nAFlag = TX_ALPHA_EQUAL, bool nMipMap = true);
// Set textures alpha color
void		vw_SetTextureAlpha(BYTE nARed, BYTE nAGreen, BYTE nABlue);

// Find texture by name
eTexture*	vw_FindTextureByName(const char *Name);
// Find texture by ID
eTexture*	vw_FindTextureByNum(int Num);

// Set texture by eTexture pointer
void		vw_SetTextureT(DWORD Stage, eTexture *Tex);

// проверка и установка правильного приоритета текстур
void 		vw_CheckTexturesPrior();


#endif // Texture_H
