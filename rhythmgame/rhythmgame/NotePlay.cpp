#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#pragma region defines

#define PERPECT 30
#define GREAT 100
#define GOOD 150

#define cols 15 //����
#define rows 62 //����
#define INPUT_SIZE 30

#define playerX 100 
#define playerY 0
#define monkeyX 10 
#define monkeyY 0 

#define PlayerboardX 20
#define PlayerboardY 55
#define boardxplus 5
#define hitColor 3 
#define hit2Color 9

#define ScoreX 110
#define ScoreY 60

#pragma endregion


extern int g_status;
extern int g_playerstatus;
long g_playetime = 0;
int g_Score = 0;
int g_BreakTime = 0;;
void Printboard(); //ȭ�� Ʋ ���
void Printnote(int arrayIndex, int(*countindex)[INPUT_SIZE], int(*keyIndex)[INPUT_SIZE], int _bpm); // ��ǻ���� �ù����
void Printplayernote(int* countindex, int pageindex, int* keyIndex);
void GetPlayersKey(int arrayIndex, int(*countindex)[INPUT_SIZE], int(*keyIndex)[INPUT_SIZE]); // �÷��̾��� �Է�
void Resetnote(); //��Ʈ �����
void Gotoxy(int x, int y, unsigned short text_Color = 15, unsigned short back_Color = 0); //Ŀ�� ��ǥ �̵� �� ���� ����.
int Keyinput(); // Ű �Է� Ȯ��.
void SetCursorview();
void PlayMusic(int musicnum, int(*_keyInput)[INPUT_SIZE], int(*_Musicnotes)[INPUT_SIZE], int _Musicsize, int _bpm);
void Ready(int tempo);
void KeyGuide(int x, int y);
extern void Playsound(int soundnum);
extern void EffectPlaysound(int soundnum); // ȿ���� ��� �Լ�
extern unsigned int GetPlayPosition(); // ���� ��� ��ġ�� ��ȯ�ϴ� �Լ�
extern void AnimUpdate(int x, int y);
extern void PlayerAnimUpdate(int x, int y);
extern void Releasesound();
extern void PrintNumber(int x, int y, int Num);
extern void InitializeAnim(int tempo);
extern int loadscore(); //���� �ҷ�����
extern void ShowScore(); //���� Ŭ���� �� ���� ���
extern void PrintScoreTEXT(int x, int y);
extern  unsigned int GetLength(int Num);

void PlayMusic(int musicnum, int(*_keyInput)[INPUT_SIZE], int(*_Musicnotes)[INPUT_SIZE], int _Musicsize, int _bpm) {
	

	int _ArrayIndex = 0;
	Ready(_bpm);

	g_BreakTime = GetLength(musicnum + 1);
	Playsound(musicnum + 1);

	while (true) {

		Resetnote();
 		Printnote(_ArrayIndex, _Musicnotes, _keyInput, _bpm); //musicnote �迭�� ��Ʈ index , _musicnote
		GetPlayersKey(_ArrayIndex, _Musicnotes, _keyInput);

		_ArrayIndex++;

		if (_ArrayIndex == _Musicsize || g_BreakTime <= GetPlayPosition())
		{
			system("cls");
			break;
		}
	}
	ShowScore();


}
void Printboard() {
	//�ٱ� �ܺλ簢��

	for (int j = 0; j < rows; j++)//����
	{
		Gotoxy(PlayerboardX + j, PlayerboardY);
		printf("��");
	}
	for (int j = 0; j < rows; j++)//����
	{
		Gotoxy(PlayerboardX + j, PlayerboardY + cols - 1);
		printf("��");
	}
	for (int i = 0; i < cols; i++)//����
	{
		if (i == 0)
		{
			Gotoxy(PlayerboardX, PlayerboardY + i);
			printf("��");
			Gotoxy(PlayerboardX + rows, PlayerboardY + i);
			printf("��");
		}
		else if (i == cols - 1)
		{
			Gotoxy(PlayerboardX, PlayerboardY + i);
			printf("��");
			Gotoxy(PlayerboardX + rows, PlayerboardY + i);
			printf("��");
		}
		else
		{
			Gotoxy(PlayerboardX + rows, PlayerboardY + i);
			printf("��");
			Gotoxy(PlayerboardX, PlayerboardY + i);
			printf("��");
		}
	}
	//��Ʈ �г�
	for (int ylength = 0; ylength < 2; ylength++) {
		for (int length = 0; length < 5; length++) {

			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 6; j++) {
					if ((i == 0 || i == 5) && (j >= 0 && j <= 5)) {
						Gotoxy(PlayerboardX + 2 + j * 2 + 12 * length, PlayerboardY + 2 + i + 6 * ylength);
						if (j == 0) {
							if (i == 0) {
								printf("������");
							}
							else {
								printf("������");
							}
						}
						else if (j == 5) {
							if (i == 0) {
								printf("��");
							}
							else {
								printf("��");
							}
						}
						else {
							printf("����");
						}
					}
					else if ((i >= 0 && i <= 5) && (j == 0 || j == 5)) {
						Gotoxy(PlayerboardX + 2 + j * 2 + 12 * length, PlayerboardY + 2 + i + 6 * ylength);
						printf("��");
					}
					else {
						printf("  ");
					}
				}
			}
		}
	}
}
void Resetnote() {
	int _maxbuttonsize = 10;
	int _printxcount = 0;
	int _printycount = 0;

	while (_printxcount < _maxbuttonsize) {

		Gotoxy(PlayerboardX + boardxplus + _printxcount * 12, PlayerboardY + 3 + 6 * _printycount);
		printf("       ");
		Gotoxy(PlayerboardX + boardxplus + _printxcount * 12, PlayerboardY + 4 + 6 * _printycount);
		printf("       ");
		Gotoxy(PlayerboardX + boardxplus + _printxcount * 12, PlayerboardY + 5 + 6 * _printycount);
		printf("       ");
		Gotoxy(PlayerboardX + boardxplus + _printxcount * 12, PlayerboardY + 6 + 6 * _printycount);
		printf("       ");
		_printxcount++;

		if (_printxcount == 5) {
			_printycount++;
			_maxbuttonsize -= 5;
			_printxcount = 0;
		}
	}
}
void Printnote(int arrayIndex, int(*countindex)[INPUT_SIZE], int(*keyIndex)[INPUT_SIZE], int _bpm) {

	//1 == 0.001��
	//1000 = 1��

	bool _islastbitplay = false;
	bool _isnoteplay = true;
	int _xPositioncount = 0;
	int _yPositioncount = 0;
	int _pagePositioncount = 0;
	int _pageNotecount = 0;
	int _count = 0;
	clock_t _timer = GetPlayPosition();

	int _sizeofnote[INPUT_SIZE / 10] = { 0 };
	for (int j = 0; j < INPUT_SIZE / 10; j++) {
		for (int i = 0; i < 10; i++) {
			if (countindex[arrayIndex][i + j * 10] != 0) {
				_sizeofnote[j]++;
				_timer += abs(countindex[arrayIndex][i + j * 10]);
			}
		}
	}

	int _lastbittiming = _timer - 30000 / _bpm; // ������������ 1/8���� 30000/bpm

	while (g_BreakTime > GetPlayPosition()) {
		Keyinput();
		AnimUpdate(monkeyX, monkeyY);
		PlayerAnimUpdate(playerX, playerY);

		if (_count == INPUT_SIZE) {
			if (_timer < GetPlayPosition()) {
				break;
			}
		}
		else {
			//������ �ӽ� ��� �Լ�(��Ʈ ���� �ε���)
			//system("cls");
			//printf("arrayIndex: %d / count: %d\n", arrayIndex + 1, _count + 1);
			if (GetPlayPosition() >= _lastbittiming && !_islastbitplay) {
				EffectPlaysound(3);
				_islastbitplay = true;
			}

			if (0 < countindex[arrayIndex][_count] && _isnoteplay)
			{
				g_status = keyIndex[arrayIndex][_count];
				_pageNotecount++;

				if (g_status == 1)
				{
					Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 5 + 6 * _yPositioncount, hitColor);
					printf("����");
					EffectPlaysound(2);
				}
				else if (g_status == 2)
				{
					Gotoxy(PlayerboardX + 2 + boardxplus + _xPositioncount * 12, PlayerboardY + 4 + 6 * _yPositioncount, hit2Color);
					printf("��");
					Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 5 + 6 * _yPositioncount, hit2Color);
					printf("���");
					EffectPlaysound(1);
				}
				else
				{
					Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 4 + 6 * _yPositioncount);
					printf("��");
					EffectPlaysound(1);
				}
 				_isnoteplay = false;
				g_playetime += abs(countindex[arrayIndex][_count]);
			}
			if (0 > countindex[arrayIndex][_count] && _isnoteplay)
			{
				_pageNotecount++;
				_isnoteplay = false;
				g_playetime += abs(countindex[arrayIndex][_count]);

			}
			if (g_playetime <= GetPlayPosition())
			{
				_xPositioncount++;
				_count++;
				_isnoteplay = true;

				if (_xPositioncount == 5) {
					_yPositioncount++;
					_xPositioncount = 0;
					if (_sizeofnote[_pagePositioncount] == _pageNotecount && _yPositioncount == 2) {
						Resetnote();
						_pageNotecount = 0;
						_pagePositioncount++;
						_xPositioncount = 0;
						_yPositioncount = 0;
					}
				}
			}
		}
	}

	g_status = 0;
}
void Printplayernote(int* countindex, int pageindex, int* keyIndex) {

	int _count = 0;
	int _xPositioncount = 0;

	int _yPositioncount = 0;

	while (_count < INPUT_SIZE / 3) {
		if (countindex[_count + 10 * pageindex] > 0)
		{
			if (keyIndex[_count + 10 * pageindex] == 1)
			{
				Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 5 + 6 * _yPositioncount, hitColor);
				printf("����");
			}
			else if (keyIndex[_count + 10 * pageindex] == 2)
			{
				Gotoxy(PlayerboardX + 2 + boardxplus + _xPositioncount * 12, PlayerboardY + 4 + 6 * _yPositioncount, hit2Color);
				printf("��");
				Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 5 + 6 * _yPositioncount, hit2Color);
				printf("���");
			}
			else
			{
				Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 4 + 6 * _yPositioncount);
				printf("��");
			}

		}

		_xPositioncount++;
		_count++;

		if (_xPositioncount == 5) {
			_yPositioncount++;
			_xPositioncount = 0;
		}
	}
}
void GetPlayersKey(int arrayIndex, int(*countindex)[INPUT_SIZE], int(*keyIndex)[INPUT_SIZE]) {
	Resetnote();

	int _xPositioncount = 0;
	int _yPositioncount = 0;
	int _playercount = 0;
	int _timer = g_playetime; //�Լ� ����ð�.

	bool _isprinted = false;
	int _pagePositioncount = 0;
	int _pageNotecount = 0;
	int _sizeofnote[INPUT_SIZE / 10] = { 0 };

	for (int j = 0; j < INPUT_SIZE / 10; j++) {
		for (int i = 0; i < 10; i++) {
			if (countindex[arrayIndex][i + j * 10] != 0) {
				_sizeofnote[j]++;
				_timer += abs(countindex[arrayIndex][i + j * 10]);
			}
		}
	}

  	while (g_BreakTime > GetPlayPosition())
	{
		int _inputcheck = Keyinput();
		AnimUpdate(monkeyX, monkeyY);
		PlayerAnimUpdate(playerX, playerY);

		if (_playercount == INPUT_SIZE)
		{
			if (_timer < GetPlayPosition()) {
				break;
			}
		}
		else
		{
			if (_isprinted == false) {
				Printplayernote(countindex[arrayIndex], _pagePositioncount, keyIndex[arrayIndex]);

				_isprinted = true;
			}

			if (countindex[arrayIndex][_playercount] > 0) // ���Ʈ, ��ǥ, �ð��� ��� ��Ʈ ó�� 
			{

				if (g_playetime + GOOD < GetPlayPosition()) // ����ð��� + 0.1�� ������� ����ó��
				{

					Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 3 + 6 * _yPositioncount);
					printf("       ");
					Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 4 + 6 * _yPositioncount, 0, 4);
					printf("   X   ");
					Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 5 + 6 * _yPositioncount, 0, 4);
					printf("   X   ");
					Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 6 + 6 * _yPositioncount);
					printf("       ");
					_pageNotecount++;
					_xPositioncount++;

					if (_xPositioncount == 5)
					{
						_yPositioncount += 1;
						_xPositioncount = 0;
						if (_sizeofnote[_pagePositioncount] == _pageNotecount && _yPositioncount == 2) {
							Resetnote();
							_pageNotecount = 0;
							_pagePositioncount++;
							_xPositioncount = 0;
							_yPositioncount = 0;
							_isprinted = false;
						}
					}
					g_playetime += abs(countindex[arrayIndex][_playercount]);
					_playercount++;
					

				}
				else if (_inputcheck != 0) //Ű�Է�
				{

					if (_inputcheck == keyIndex[arrayIndex][_playercount])
					{
						long _hittime = g_playetime - GetPlayPosition();


						if (_hittime < PERPECT && _hittime > -PERPECT)
						{
							Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 3 + 6 * _yPositioncount, 0, 10);
							printf("       ");
							Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 4 + 6 * _yPositioncount, 0, 10);
							printf("   ��  ");
							Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 5 + 6 * _yPositioncount, 0, 10);
							printf("   ��  ");
							Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 6 + 6 * _yPositioncount, 0, 10);
							printf("       ");

							PrintNumber(ScoreX, ScoreY, 100);

						}
						else if (_hittime < GREAT && _hittime > -GREAT)
						{
							Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 3 + 6 * _yPositioncount);
							printf("       ");
							Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 4 + 6 * _yPositioncount, 6);
							printf(" Great ");
							Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 5 + 6 * _yPositioncount, 6);
							printf(" Great ");
							Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 6 + 6 * _yPositioncount);
							printf("       ");
							PrintNumber(ScoreX, ScoreY, 50);

						}
						else if (_hittime < GOOD && _hittime > -GOOD)
						{
							Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 3 + 6 * _yPositioncount, 6);
							printf("       ");
							Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 4 + 6 * _yPositioncount, 6);
							printf(" GOOD  ");
							Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 5 + 6 * _yPositioncount, 6);
							printf(" GOOD  ");
							Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 6 + 6 * _yPositioncount);
							printf("       ");
							PrintNumber(ScoreX, ScoreY, 10);

						}
						else
						{
							Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 3 + 6 * _yPositioncount);
							printf("       ");
							Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 4 + 6 * _yPositioncount, 0, 4);
							printf("   X   ");
							Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 5 + 6 * _yPositioncount, 0, 4);
							printf("   X   ");
							Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 6 + 6 * _yPositioncount);
							printf("       ");

						}
					}
					else
					{
						Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 3 + 6 * _yPositioncount);
						printf("       ");
						Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 4 + 6 * _yPositioncount, 0, 4);
						printf("   X   ");
						Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 5 + 6 * _yPositioncount, 0, 4);
						printf("   X   ");
						Gotoxy(PlayerboardX + boardxplus + _xPositioncount * 12, PlayerboardY + 6 + 6 * _yPositioncount);
						printf("       ");
					}

					_pageNotecount++;
					_xPositioncount += 1;

					if (_xPositioncount == 5)
					{
						_yPositioncount += 1;
						_xPositioncount = 0;
						if (_sizeofnote[_pagePositioncount] == _pageNotecount && _yPositioncount == 2) {
							Resetnote();
							_pageNotecount = 0;
							_pagePositioncount++;
							_xPositioncount = 0;
							_yPositioncount = 0;
							_isprinted = false;
						}
					}
					g_playetime += abs(countindex[arrayIndex][_playercount]);
					_playercount++;
				
				}
			}
			else if (countindex[arrayIndex][_playercount] < 0) {
				if (g_playetime < GetPlayPosition()) {
					_pageNotecount++;
					_xPositioncount++;
					if (_xPositioncount == 5)
					{
						_yPositioncount++;
						_xPositioncount = 0;
						if (_sizeofnote[_pagePositioncount] == _pageNotecount && _yPositioncount == 2) {
							Resetnote();
							_pageNotecount = 0;
							_pagePositioncount++;
							_xPositioncount = 0;
							_yPositioncount = 0;
							_isprinted = false;
						}
					}
					g_playetime += abs(countindex[arrayIndex][_playercount]);
					_playercount++;
					
				}
			}
			else
			{
				_xPositioncount += 1;
				if (_xPositioncount == 5)
				{
					_yPositioncount += 1;
					_xPositioncount = 0;
					if (_sizeofnote[_pagePositioncount] == _pageNotecount && _yPositioncount == 2) {
						Resetnote();
						_pageNotecount = 0;
						_pagePositioncount++;
						_xPositioncount = 0;
						_yPositioncount = 0;
						_isprinted = false;
					}
				}
				g_playetime += abs(countindex[arrayIndex][_playercount]);
				_playercount++;
				
			}
		}
	}
}

//�ż��� Ŀ�� ��ǥ �� ���� ��ȯ �Լ�.
void Gotoxy(int x, int y, unsigned short text_Color, unsigned short back_Color) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text_Color | back_Color << 4);
}

//�ż��� �ӵ��� ���� �ִϸ��̼� ���� �Լ�.
void Ready(int tempo)
{
	system("cls");
	Printboard();
	g_playetime = 0;
	g_Score = 0;
	g_BreakTime = 0;
	PrintScoreTEXT(ScoreX + 18, ScoreY - 9);
	PrintNumber(ScoreX, ScoreY, 0);
	KeyGuide(20, 80);
	clock_t _start = clock();
	clock_t _now = clock();
	int i = 0;
	InitializeAnim(tempo);
	g_status = 0;
	g_playerstatus = 0;

	while (i < 5)
	{
		AnimUpdate(monkeyX, monkeyY);
		PlayerAnimUpdate(playerX, playerY);
		_now = clock();
		if (1000 / (tempo / 60) < _now - _start)
		{
			if (i != 4)
				EffectPlaysound(3);
			_start = clock();
			i++;
		}
	}
}
//���ڻ�	����
//����  0	
//��ο� �Ķ�1
//��ο� �ʷ� 2
//��ο� �ϴ� 3
//��ο� ���� 4
//��ο� ���� 5
//��ο� ��� 6
//ȸ�� 7
//��ο� ȸ�� 8
//�Ķ� 9
//�ʷ� 10
//�ϴ� 11
//���� 12
//���� 13
//��� 14
//�Ͼ� 15
int Keyinput() {
	int g_input = 0;
	// 1  spacebare
	// 2 Enter

	//�����̽��� �Է�
	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		Gotoxy(0, 0);
		
		printf("%d   ", GetPlayPosition() - g_playetime);

		g_playerstatus = 1;
		g_input = 1;
		EffectPlaysound(2); // ���� �Է� �� ����� ȿ����
	}
	//���� �Է�
	else if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		g_playerstatus = 2;
		g_input = 2;
		EffectPlaysound(1); // �����̽� �Է� �� ����� ȿ����
	}
	return g_input;
}

//�ż��� ���� �÷����� ���ھ� ��������ִ� �Լ�.
void UpdateScore(int _setscore)
{
	g_Score += _setscore;
}

//�ż��� ���� �÷��� �� �ϴܿ� Ű ���� ����Ʈ �Լ�. 
void KeyGuide(int x, int y)
{
	int hit2x = 90;
	const char* str[8] = {
		{" _____                            _                  "},
		{"/  ___|                          | |                 "},
		{"l `--.  _ __    __ _   ___   ___ | |__    __ _  _ __ "},
		{" `--. l| '_ l  / _` | / __| / _ l| '_ l  / _` || '__|"},
		{"/l__/ /| |_) || (_| || (__ |  __/| |_) || (_| || |   "},
		{"l____/ | .__/  l__,_| l___| l___||_.__/  l__,_||_|   "},
		{"       | |                                           "},
		{"       |_|                                           "},

	};

	const char* str2[6] = {
		{" _____         _               "},
		{"|  ___|       | |              "},
		{"| |__   _ ___ | |_   ___  _ __ "},
		{"|  __| | '_  l| __| / _ l| '__|"},
		{"| |___ | | | || |_ |  __/| |   "},
		{"l____/ |_| |_|l___| l___||_|   "},
	};


	//�����̽���
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Gotoxy(x + j + k * 5, y + i, hitColor, hitColor);
				printf("��");
			}
		}
	}

	for (int i = 0; i < 8; i++)
	{
		Gotoxy(x+20, y + i -3);
		printf("%s", str[i]);
	}


	//����Ű
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Gotoxy(x + j + k * 5 + hit2x, y + i, hit2Color, hit2Color);
				printf("��");
			}
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Gotoxy(x + j + 5 + hit2x, y + i - 3, hit2Color, hit2Color);
			printf("��");
		}
	}

	for (int i = 0; i < 6; i++)
	{
		Gotoxy(x + 20+ hit2x, y + i - 3);
		printf("%s", str2[i]);
	}

	


}