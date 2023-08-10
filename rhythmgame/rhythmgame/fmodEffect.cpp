#include <tchar.h>
#include <strsafe.h>
#include <Windows.h>
#include <time.h>
#include <fmod.hpp>
#include <conio.h>

using namespace FMOD;

/// <summary>
/// ȿ���� ������(���� �̸�)
/// </summary>
enum EffectSounds
{
    SD_Effectnote = 0,
    SD_Drum, // �巳 ���׾�: e_1.wav
    SD_Hihat, // �巳 ������: e_2.wav
    SD_Monkey, // �� ��ȯ ������ ȿ����: e_3.wav
    SD_Success, // �÷��̾� ���� ȿ����: e_4.wav
    SD_Fail, // �÷��̾� ���� ȿ����(������): e_5.wav
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
