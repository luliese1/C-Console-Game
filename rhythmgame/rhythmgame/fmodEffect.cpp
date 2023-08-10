#include <tchar.h>
#include <strsafe.h>
#include <Windows.h>
#include <time.h>
#include <fmod.hpp>
#include <conio.h>

using namespace FMOD;

/// <summary>
/// 효과음 열거형(파일 이름)
/// </summary>
enum EffectSounds
{
    SD_Effectnote = 0,
    SD_Drum, // 드럼 스네어: e_1.wav
    SD_Hihat, // 드럼 하이햇: e_2.wav
    SD_Monkey, // 턴 전환 원숭이 효과음: e_3.wav
    SD_Success, // 플레이어 성공 효과음: e_4.wav
    SD_Fail, // 플레이어 실패 효과음(개구리): e_5.wav
    SD_EffectSize
};

System* g_pEffectSystem;
Sound* g_pEffectSound[SD_EffectSize];
Channel* g_pEffectChannel;
FMOD_RESULT resultEffect;
Channel* g_pEffectChannel2;

void EffectSoundsetup()
{
    resultEffect = System_Create(&g_pEffectSystem);
    resultEffect = g_pEffectSystem->init(5, FMOD_INIT_NORMAL, 0);

    char str[128];
    for (int i = 0; i < SD_EffectSize; i++) {
        sprintf_s(str, "Sounds/e_%d.wav", i);
        g_pEffectSystem->createSound(str, FMOD_LOOP_OFF, 0, &g_pEffectSound[i]);
    }
}

void EffectPlaysound(int soundnum)
{
	if (soundnum == 3 || soundnum == 4)
    {
		g_pEffectSystem->playSound(g_pEffectSound[soundnum], 0, false, &g_pEffectChannel2);
	}
	else
	{
        g_pEffectSystem->update();
		g_pEffectSystem->playSound(g_pEffectSound[soundnum], 0, false, &g_pEffectChannel);
	}
}

void ReleaseEffectSound()
{
    g_pEffectSystem->release();
}
