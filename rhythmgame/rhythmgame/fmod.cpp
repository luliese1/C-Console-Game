#include <tchar.h>
#include <strsafe.h>
#include <Windows.h>
#include <fmod.hpp>
#include <conio.h>

using namespace FMOD;

enum Sounds
{
	SD_note = 0,
	SD_Megalovania,
	SD_KKHOUSE,
	SD_MARIO,
	SD_Talesweaver,
	SD_Size
};

System* g_pSystem;
Sound* g_pSound[SD_Size];
Channel* g_pChannel;
FMOD_RESULT result;

void Soundsetup()
{
	result = System_Create(&g_pSystem);
	result = g_pSystem->init(1, FMOD_INIT_NORMAL, 0);

	char str[128];
	for (int i = 0; i < SD_Size+1; i++) {
		sprintf_s(str, "Sounds/%d.wav", i);
		g_pSystem->createSound(str, FMOD_LOOP_OFF, 0, &g_pSound[i]);
	}
}

void Playsound(int soundnum) {
	g_pSystem->playSound(g_pSound[soundnum], 0, false, &g_pChannel);
}

void PauseMusic() {
	g_pChannel->setPaused(true);
}

void Releasesound() {
	g_pSystem->release();
}

unsigned int GetPlayPosition()
{
	unsigned int _playPosition = 0;
	g_pChannel->getPosition(&_playPosition, FMOD_TIMEUNIT_MS);
	return _playPosition;
}

unsigned int GetLength(int Num)
{
	unsigned int Result;
	g_pSound[Num]->getLength(&Result, FMOD_TIMEUNIT_MS);
	return Result;
}
