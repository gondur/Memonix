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



#include "memonix_var.h"



Mix_Music *music1 = NULL;
Mix_Music *music2 = NULL;
Mix_Music *music3 = NULL;
eFILE *pFile1 = NULL;
SDL_RWops *RWFile1 = NULL;
eFILE *pFile2 = NULL;
SDL_RWops *RWFile2 = NULL;
eFILE *pFile3 = NULL;
SDL_RWops *RWFile3 = NULL;

int audio_rate = 44100;//22050;
Uint16 audio_format = MIX_DEFAULT_FORMAT;//AUDIO_S16; /* 16-bit stereo */
int audio_channels = 2;
int audio_buffers = 4096;

eFILE *pFileS1 = NULL;
eFILE *pFileS2 = NULL;
eFILE *pFileS3 = NULL;







bool InitSound()
{
	if (!Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
	{
		pFileS1 = vw_fopen("DATA\\SFX\\click.wav");
		pFileS2 = vw_fopen("DATA\\SFX\\error.wav");
		pFileS3 = vw_fopen("DATA\\SFX\\win.wav");
		return true;
	}

	return false;
}










void SoundFinished(int ChannelNum)
{
	Mix_Chunk *Chunk = Mix_GetChunk(ChannelNum);
	if (Chunk != NULL) Mix_FreeChunk(Chunk);
}




//------------------------------------------------------------------------------------
// установка звука на проигрывание...
//------------------------------------------------------------------------------------
void Audio_PlaySound(int SoundID)
{
	if (!Setup.SoundSw) return;

	SDL_RWops *RWFile;
	Mix_Chunk *sound;


	switch (SoundID)
	{
		case 1:
			RWFile = SDL_RWFromConstMem(pFileS1->Data, pFileS1->RealLength);
			sound = Mix_LoadWAV_RW(RWFile, 1);
			if (sound == NULL)
			{
				printf("Could not open sound!\n");
				return;
			}
			Mix_PlayChannel(-1, sound, 0);
			break;

		case 2:
			RWFile = SDL_RWFromConstMem(pFileS2->Data, pFileS2->RealLength);
			sound = Mix_LoadWAV_RW(RWFile, 1);
			if (sound == NULL)
			{
				printf("Could not open sound!\n");
				return;
			}
			Mix_PlayChannel(-1, sound, 0);
			break;

		case 3:
			RWFile = SDL_RWFromConstMem(pFileS3->Data, pFileS3->RealLength);
			sound = Mix_LoadWAV_RW(RWFile, 1);
			if (sound == NULL)
			{
				printf("Could not open sound!\n");
				return;
			}


			Mix_PlayChannel(-1, sound, 0);
			break;
	}


	// установка процедуры перехвата
	Mix_ChannelFinished(SoundFinished);
}







bool isMenu()
{
	// сейчас будем переключать
	switch (ComBuffer)
	{
		case GAME_START:
			return false;
		case GAME:
			return false;
	}

	switch(GameStatus)
	{
		case REGISTRATION:
			return true;
		case MAIN_MENU:
			return true;
		case CREDITS:
			return true;
		case TOP_SCORES:
			return true;
		case SETUP:
			return true;
	}

	return false;
}




bool MusicIsPlaying = false;
void musicFinished()
{
	MusicIsPlaying = false;
}





//------------------------------------------------------------------------------------
// основной цикл проигрывания звука
//------------------------------------------------------------------------------------
void Audio_LoopProc()
{
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// загрузка звука... если он включен, или его включили в игре...
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if (Setup.MusicSw || Setup.MusicSw_Game)
		{

			if (music1 == NULL)
			{
				pFile1 = vw_fopen("DATA\\MUSIC\\music1.ogg");
				RWFile1 = SDL_RWFromConstMem(pFile1->Data, pFile1->RealLength);
				music1 = Mix_LoadMUS_RW(RWFile1);
				if (music1 == NULL)
				{
					Setup.MusicSw = false;
					Setup.MusicSw_Game = false;
					Setup.Music_check = false;
					printf("Could not open music1!\n");
				}
			}
			if (music2 == NULL)
			{
				pFile2 = vw_fopen("DATA\\MUSIC\\music2.ogg");
				RWFile2 = SDL_RWFromConstMem(pFile2->Data, pFile2->RealLength);
				music2 = Mix_LoadMUS_RW(RWFile2);
				if (music2 == NULL)
				{
					Setup.MusicSw = false;
					Setup.MusicSw_Game = false;
					Setup.Music_check = false;
					printf("Could not open music2!\n");
				}
			}
			if (music3 == NULL)
			{
				pFile3 = vw_fopen("DATA\\MUSIC\\music4.ogg");
				RWFile3 = SDL_RWFromConstMem(pFile3->Data, pFile3->RealLength);
				music3 = Mix_LoadMUS_RW(RWFile3);
				if (music3 == NULL)
				{
					Setup.MusicSw = false;
					Setup.MusicSw_Game = false;
					Setup.Music_check = false;
					printf("Could not open music3!\n");
				}
			}
		}


		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// проигрываем фоновую музыку
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if ((Setup.MusicSw && isMenu()) || (Setup.MusicSw_Game && !isMenu()))
		{
			if (music1 && music2 && music3)
			if (!MusicIsPlaying) // если уже не играем
			{
				switch(Setup.MusicCount)
				{
					case 1:
						Mix_PlayMusic(music1, 1);
						break;
					case 2:
						Mix_PlayMusic(music2, 1);
						break;
					case 3:
						Mix_PlayMusic(music3, 1);
						break;
				}

				MusicIsPlaying = true;
				Mix_HookMusicFinished(musicFinished);
				Setup.MusicCount++;
				if (Setup.MusicCount>3) Setup.MusicCount=1;
			}
		}



		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// выключаем звуки (т.к. его отключили в меню)
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if (!Setup.SoundSw && Setup.Sound_check)
		{
			Mix_HaltChannel(-1);
		}
		if ((!Setup.MusicSw && isMenu() && Setup.Music_check)
			|| (!Setup.MusicSw_Game && !isMenu() && Setup.Music_check))
		{
				MusicIsPlaying = false;
				Mix_HaltMusic();
		}


}






void ShutdownAudio()
{
	MusicIsPlaying = false;


	Mix_HaltChannel(-1);
	Mix_HaltMusic();

	if (music1 != NULL) Mix_FreeMusic(music1);
	music1 = NULL;
	if (music2 != NULL) Mix_FreeMusic(music2);
	music2 = NULL;
	if (music3 != NULL) Mix_FreeMusic(music3);
	music3 = NULL;

	// эти файлы уже закрыли в Mix_FreeMusic!, так что просто правим на NULL
	RWFile1 = NULL;
	RWFile2 = NULL;
	RWFile3 = NULL;

	if (pFile1 != NULL) vw_fclose(pFile1);
	pFile1 = NULL;
	if (pFile2 != NULL) vw_fclose(pFile2);
	pFile2 = NULL;
	if (pFile3 != NULL) vw_fclose(pFile3);
	pFile3 = NULL;

	if (pFileS1 != NULL) vw_fclose(pFileS1);
	pFileS1 = NULL;
	if (pFileS2 != NULL) vw_fclose(pFileS2);
	pFileS2 = NULL;
	if (pFileS3 != NULL) vw_fclose(pFileS3);
	pFileS3 = NULL;

	Mix_CloseAudio();

}
