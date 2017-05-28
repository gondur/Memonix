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


#include "Core.h"
#include "memonix.h"





//------------------------------------------------------------------------------------
// переменные...глобальные...main.cpp
//------------------------------------------------------------------------------------
extern memSetup Setup;
extern memCursor GameCursor;
extern bool Quit;
extern char ProgrammDir[MAX_PATH];
extern char VFSFileNamePath[MAX_PATH];
void SaveGameData();
extern bool CanQuit;
extern status GameStatus;
extern bool NeedReCreate;


//------------------------------------------------------------------------------------
// переменные...глобальные...options.cpp
//------------------------------------------------------------------------------------
extern void Options();
extern void LoadMosaicPreset();
extern void LoadBuilderPreset();
extern void LoadThePairPreset();
extern void LoadJigSawPreset();
extern void SeekAddons();



//------------------------------------------------------------------------------------
// переменные...глобальные...menu.cpp
//------------------------------------------------------------------------------------
extern void SetMenu(int GameMenuStatus);
extern void DrawManualText(int X , int Y, const char * Text, int W, int Limit);
extern void MainMenu();
extern void Credits();
extern void TopScores();
extern void SetupProc();





//------------------------------------------------------------------------------------
// переменные...глобальные...game.cpp
//------------------------------------------------------------------------------------
extern bool TopScCheck;
extern int TopScCheckStop;
extern bool ErrorShow;
extern Uint32 ErrorShowTime;
extern bool RightShow;
extern Uint32 RightShowTime;
extern bool CheckList(int Check);
extern void Game();



//------------------------------------------------------------------------------------
// переменные...глобальные...game_start.cpp
//------------------------------------------------------------------------------------
extern int FieldData[8][8];
extern int FieldDataPair[8][8];
extern int SetFieldData[8][8];
extern Uint32 GameTime;
extern Uint32 GameTimeInit;
extern bool GameWin;
extern int StartPanelPos;
extern int EndPanelPos;
extern int SetPanelPos;
extern int SearchFor;
extern int CurentFoto;
extern int CurentFotoNum;
extern int lastgame;
extern void GameStart();
extern void GameStartDraw();
extern void ReleaseGameDate(int Game);
extern unsigned int ResetTickCount;
extern float ResetTransp;
extern bool ResetTranspOn;
extern int CurColor;






//------------------------------------------------------------------------------------
// переменные...глобальные...loading.cpp
//------------------------------------------------------------------------------------
extern void LoadAll();



//------------------------------------------------------------------------------------
// переменные...глобальные...loop_proc.cpp
//------------------------------------------------------------------------------------
extern void Loop_Proc();
extern eFont *Font2;
extern int ComBuffer;
extern Uint32 TimeDelay;
extern eFont *GameFont;



//------------------------------------------------------------------------------------
// переменные...глобальные...dialogs.cpp
//------------------------------------------------------------------------------------
extern void SetCurrentDialogBox(int DialogBox);
extern bool isDialogBoxDrawing();
extern void DrawDialogBox();
// описания для диалогов
#define QUIT_GAME				1
#define YOU_WINNER				2



//------------------------------------------------------------------------------------
// переменные...глобальные...proc_audio.cpp
//------------------------------------------------------------------------------------
void Audio_PlaySound(int SoundID);
void Audio_LoopProc();
void ShutdownAudio();
bool InitSound();
extern bool MusicIsPlaying;




//------------------------------------------------------------------------------------
// переменные...глобальные...system.cpp
//------------------------------------------------------------------------------------
bool OpenBrouser(char *url);






//------------------------------------------------------------------------------------
// переменные...глобальные...protect.cpp
//------------------------------------------------------------------------------------
#ifdef WIN32
	#include "asprotect\asprotect.h"
	#include "asprotect\aspr.h"
	extern int	TrialExLeft;
	extern char*	LocalHardwareID;
	extern bool ProtectEnvelopeCheck1();
	extern bool ProtectEnvelopeCheck2();
	extern bool ProtectEnvelopeCheck3();
#endif // WIN32



