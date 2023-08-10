#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>



struct Animation
{
	const char* _Adress[4] = { NULL, };
	char* _Anim[4][50] = { NULL, };

	int _MaxIndex = 2;
	int _NowIndex = 0;
	int _playspeed = 50;
};
//�ؽ�Ʈ ������� 86*50;
//##XXxxx++....

int Init(char* _Idle[50], const char* adress);
void AnimUpdate(int x, int y);
void  PlayerAnimUpdate(int x, int y);
void Draw(int x, int y, Animation& _ani);
extern void Gotoxy(int x, int y, unsigned short text_Color = 15, unsigned short back_Color = 0);
void InitializeAnim(int tempo);
void PlayerDraw(int x, int y, Animation& _ani);
void SelectDraw(int x, int y, Animation& _ani);
void SelectAnimUpdate(int x, int y, int num);
void SelectAnimInit();


Animation Idle;
Animation hit;
Animation hit2;

Animation handhit1;
Animation handhit2;
Animation handIdle;

Animation Sans;
Animation kk;
Animation Mario;
int g_status = 0;
int g_playerstatus = 0;

//�ż����ؽ�Ʈ���� �迭�� ��ȯ �� �ʱ�ȭ �ִϸ��̼� ����ü �ۼ�..
void InitializeAnim(int tempo)
{
	float A = tempo / 60;
	Idle._Adress[0] = "Anim\\Idle1.txt";
	Idle._Adress[1] = "Anim\\Idle2.txt";
	Init(Idle._Anim[0], Idle._Adress[0]);
	Init(Idle._Anim[1], Idle._Adress[1]);
	Idle._MaxIndex = 2;
	Idle._playspeed = 250;
	//�ִϸ��̼� struct �ʱ�ȭ Idle
	hit._Adress[0] = "Anim\\hit1.txt";
	hit._Adress[1] = "Anim\\hit2.txt";
	hit._Adress[2] = "Anim\\hit3.txt";
	Init(hit._Anim[0], hit._Adress[0]);
	Init(hit._Anim[1], hit._Adress[1]);
	Init(hit._Anim[2], hit._Adress[2]);
	hit._playspeed = 100 / A;
	hit._MaxIndex = 3;
	//�ִϸ��̼� struct �ʱ�ȭ hit
	hit2._Adress[0] = "Anim\\hit2_1.txt";
	hit2._Adress[1] = "Anim\\hit2_2.txt";
	hit2._Adress[2] = "Anim\\hit2_3.txt";
	hit2._Adress[3] = "Anim\\hit2_4.txt";
	Init(hit2._Anim[0], hit2._Adress[0]);
	Init(hit2._Anim[1], hit2._Adress[1]);
	Init(hit2._Anim[2], hit2._Adress[2]);
	Init(hit2._Anim[3], hit2._Adress[3]);
	hit2._playspeed = 40 /A;
	hit2._MaxIndex = 4;
	//�ִϸ��̼� struct �ʱ�ȭ hit2
	handhit1._Adress[0] = "Anim\\handhit1_1.txt";
	handhit1._Adress[1] = "Anim\\handhit1_2.txt";
	handhit1._Adress[2] = "Anim\\handhit1_3.txt";
	Init(handhit1._Anim[0], handhit1._Adress[0]);
	Init(handhit1._Anim[1], handhit1._Adress[1]);
	Init(handhit1._Anim[2], handhit1._Adress[2]);
	handhit1._MaxIndex = 3;
	handhit1._playspeed = 100 / A;
	//hand �ִϸ��̼� �ʱ�ȭ.
	handhit2._Adress[0] = "Anim\\handhit2_1.txt";
	handhit2._Adress[1] = "Anim\\handhit2_2.txt";
	handhit2._Adress[2] = "Anim\\handhit2_3.txt";
	handhit2._Adress[3] = "Anim\\handhit2_4.txt";
	Init(handhit2._Anim[0], handhit2._Adress[0]);
	Init(handhit2._Anim[1], handhit2._Adress[1]);
	Init(handhit2._Anim[2], handhit2._Adress[2]);
	Init(handhit2._Anim[3], handhit2._Adress[3]);
	handhit2._playspeed = 40/A;
	handhit2._MaxIndex = 4;
	//hand �ִϸ��̼� �ʱ�ȭ.
	handIdle._Adress[0] = "Anim\\handIdle1.txt";
	handIdle._Adress[1] = "Anim\\handIdle2.txt";
	Init(handIdle._Anim[0], handIdle._Adress[0]);
	Init(handIdle._Anim[1], handIdle._Adress[1]);
	handIdle._MaxIndex = 2;
	handIdle._playspeed = 250;
	//hand �ִϸ��̼� �ʱ�ȭ.


}


//�ż��� ����ȭ�� �ִϸ��̼� �ʱ�ȭ
void SelectAnimInit()
{
	Sans._Adress[0] = "Anim\\Sans1.txt";
	Sans._Adress[1] = "Anim\\Sans2.txt";
	Sans._Adress[2] = "Anim\\Sans3.txt";
	Sans._Adress[3] = "Anim\\Sans4.txt";

	Init(Sans._Anim[0], Sans._Adress[0]);
	Init(Sans._Anim[1], Sans._Adress[1]);
	Init(Sans._Anim[2], Sans._Adress[2]);
	Init(Sans._Anim[3], Sans._Adress[3]);
	Sans._MaxIndex = 4;
	Sans._playspeed = 200;

	kk._Adress[0] = "Anim\\kk1.txt";
	kk._Adress[1] = "Anim\\kk2.txt";
	kk._Adress[2] = "Anim\\kk3.txt";

	Init(kk._Anim[0], kk._Adress[0]);
	Init(kk._Anim[1], kk._Adress[1]);
	Init(kk._Anim[2], kk._Adress[2]);
	kk._MaxIndex = 3;
	kk._playspeed = 200;

	Mario._Adress[0] = "Anim\\Mario.txt";
	Init(Mario._Anim[0], Mario._Adress[0]);
	Mario._MaxIndex = 1;
	Mario._playspeed = 200;

}
//�ż��� ����ȭ�� �ִϸ��̼� ������Ʈ
void SelectAnimUpdate(int x, int y, int num)
{

	switch (num)
	{
	case 0:
		//sans
		SelectDraw(x, y, Sans);
		break;
	case 1:
		//kkhouse
		SelectDraw(x, y, kk);
		break;
	case 2:
		SelectDraw(x, y, Mario);
	
		break;

	default:
		break;
	}

}

//�ż��� ����ȭ�� �ִϸ��̼� �׸���
void SelectDraw(int x, int y, Animation& _ani)
{

	static clock_t g_starttime = clock();
	clock_t _nowtime = clock();



	if (_ani._playspeed < _nowtime - g_starttime)
	{
		g_starttime = clock();
		for (int i = 0; i < 50; i++)
		{

			Gotoxy(x, i + y);
			printf("%s", _ani._Anim[_ani._NowIndex][i]);
		}
		_ani._NowIndex++;
	}
	if (_ani._NowIndex >= _ani._MaxIndex)
	{
		_ani._NowIndex = 0;

		if (g_status != 0)
			g_status = 3;
	}
}

//�ż��� �÷��̾� �ִϸ��̼� ����Լ�.(x��ǥ, y��ǥ)
void PlayerAnimUpdate(int x, int y)
{

	switch (g_playerstatus)
	{
	case 0:
		//idle
		PlayerDraw(x, y, handIdle);
		break;
	case 1:
		//hit
		PlayerDraw(x, y, handhit1);
		break;
	case 2:
		//hit2
		PlayerDraw(x, y, handhit2);
		break;

	default:
		break;
	}

}



//�ż��� ������ �ִϸ��̼� ����Լ�.(x��ǥ, y��ǥ)
void AnimUpdate(int x, int y)
{
	
	switch (g_status)
	{
	case 0:
		//idle
		Draw(x, y, Idle);

		break;
	case 1:
		//hit
		Draw(x, y, hit);

		break;
	case 2:
		//hit2
		Draw(x, y, hit2);

		break;
	case 3:
		//���
	default:
		break;
	}
}
//�ִϸ��̼� ȭ�鿡 �׸��� �Լ�. (x��ǥ ,  y��ǥ,  �ִϸ��̼� �迭,  �迭�� �ε���, �ִϸ��̼� �ӵ�)


//�ż��� ������ �ִϸ��̼� �׸���
void Draw(int x, int y, Animation& _ani)
{

	static clock_t g_starttime = clock();
	clock_t _nowtime = clock();

	

	if (_ani._playspeed < _nowtime - g_starttime)
	{
		g_starttime = clock();
		for (int i = 0; i < 50; i++)
		{

			Gotoxy(x, i + y);
			printf("%s", _ani._Anim[_ani._NowIndex][i]);
		}
		_ani._NowIndex++;
	}
	if (_ani._NowIndex >= _ani._MaxIndex)
	{
		_ani._NowIndex = 0;

		if(g_status != 0)
		g_status = 3;
	}
}

//�ż��� �÷��̾� �ִϸ��̼� �׸���
void PlayerDraw(int x, int y, Animation& _ani)
{

	static clock_t g_starttime = clock();
	clock_t _nowtime = clock();



	if (_ani._playspeed < _nowtime - g_starttime)
	{
		g_starttime = clock();
		for (int i = 0; i < 50; i++)
		{

			Gotoxy(x, i + y);
			printf("%s", _ani._Anim[_ani._NowIndex][i]);
		}
		_ani._NowIndex++;
	}
	if (_ani._NowIndex >= _ani._MaxIndex)
	{
		_ani._NowIndex = 0;
		g_playerstatus = 0;
	}
}

//�ż��� �ؽ�Ʈ�� �迭�� �����ϴ� �Լ�.(�ִϸ��̼� �迭, �ִϸ��̼� �ؽ�Ʈ �ּ�)
int Init(char* _Idle[50], const char* adress)
{
	char* Word = NULL;
	char print_temp[100];


	FILE* rfp;
	fopen_s(&rfp, adress, "r");

	if (rfp == NULL)
	{
		printf("����");
		return 0;
	}
	int i = 0;

	for (int i = 0; i < 50; i++)
	{

		Word = (char*)malloc(sizeof(char) * 88);
		if (Word != 0)
			fgets(Word, 88, rfp);
		_Idle[i] = Word;
		//printf("%s", _Idle[i]);

	}

	fclose(rfp);


	return 0;
}
