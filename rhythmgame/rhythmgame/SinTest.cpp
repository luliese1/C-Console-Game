#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#pragma region keydatas

#define key_Q 0x51
#define key_W 0x57
#define key_E 0x45
#define key_R 0x52
#define key_A 0x41
#define key_S 0x53
#define key_D 0x44
#define key_F 0x46
#define INPUT_SIZE 10

#pragma endregion

#define PERPECT 20
#define GREAT 100
#define GOOD 200
#define OUT 200

#define cols 75
#define rows 40

void Printboard(); //화면 틀 출력
void Printnote(int arrayIndex, int(*countindex)[INPUT_SIZE]); // 컴퓨터의 시범노드
void GetPlayersKey(int arrayIndex, int(*countindex)[INPUT_SIZE]); // 플레이어의 입력
void Resetnote(); //노트 지우기
void Gotoxy(int x, int y, unsigned short text_Color = 15, unsigned short back_Color = 0); //커서 좌표 이동 및 색깔 변경.
bool Keyinput(); // 키 입력 확인.
void SetCursorview();
extern void Startmenu();
extern void Soundsetup();
extern void Playsound(int soundnum);

void Init() {
	system("mode con cols=150 lines=40");
	SetCursorview();
	Soundsetup();
};

//beep음 발생시 발생 시간만큼 프로그램 정지됨.
int main() {
	Init();

	Startmenu();
	Printboard();

	int _ArrayIndex = 0;
	int countIndex[2][INPUT_SIZE] =
	{
		{ 300, 600, 150, 300, 300, 150, 300, 150, 300, -1 },
		{ 150, -1, 300, 150, -1, 150, -1, 300, 150, -1 }
	};
	// -1은 값 없음 건너뛰기.

	//나비보벳따우 bpm 122 4/4박자 https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=sptjjang&logNo=220121229830
	// 1비트(4분음표)에 492 1마디에 1968 8/246 16/123
	int tkhouse[10][INPUT_SIZE] = {
		{369,369,-1,492,-1,246,246,123,123,-1},
		{369,369,-1,492,-1,246,246,123,123,-1},
		{369,369,-1,492,-1,246,246,123,123,-1},
		{-1,-1722,-1,-1,-1,-1,-1,123,123,-1},
		{246,246,123,246,123,246,123,246,123,246},
		{246,246,123,246,123,246,123,246,123,246},
		{246,246,123,246,123,246,123,246,123,246},
		{246,246,123,246,123,246,123,246,123,246},
		{246,246,123,246,123,246,123,246,123,246},
		{246,246,123,246,123,246,123,246,123,246},

	};

	Playsound(1);

	while (1) {
		Resetnote();
		Printnote(_ArrayIndex, tkhouse);
		GetPlayersKey(_ArrayIndex, tkhouse);
		_ArrayIndex++;

		if (_ArrayIndex == 10)
		{
			_ArrayIndex = 0;
		}
	}


}

void Printboard() {

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			if ((i == 20 || i == 34) && (j >= 21 && j <= 53)) {
				printf("■");
			}
			else if ((i >= 20 && i < 34) && (j == 21 || j == 53)) {
				printf("■");
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}


	for (int length = 0; length < 5; length++) {

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if ((i == 0 || i == 4) && (j >= 0 && j <= 4)) {
					Gotoxy(46 + j * 2 + 12 * length, 21 + i);
					printf("★");
				}
				else if ((i >= 0 && i <= 4) && (j == 0 || j == 4)) {
					Gotoxy(46 + j * 2 + 12 * length, 21 + i);
					printf("★");
				}
				else {
					printf("  ");
				}
			}
		}
	}

	for (int length = 0; length < 5; length++) {

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if ((i == 0 || i == 4) && (j >= 0 && j <= 4)) {
					Gotoxy(46 + j * 2 + 12 * length, 27 + i);
					printf("★");
				}
				else if ((i >= 0 && i <= 4) && (j == 0 || j == 4)) {
					Gotoxy(46 + j * 2 + 12 * length, 27 + i);
					printf("★");
				}
				else {
					printf("  ");
				}
			}
		}
	}

}

void Printnote(int arrayIndex, int(*countindex)[INPUT_SIZE]) {

	//1 == 0.001초
	//1000 = 1초

	clock_t _starttime = clock();
	clock_t _nowtime;

	bool _isnoteplay = true;
	int _printxcount = 0;
	int _printycount = 0;
	int _count = 0;

	while (_count < INPUT_SIZE) {

		_nowtime = clock();
		long _time = _nowtime - _starttime;

		if (0 < countindex[arrayIndex][_count] && _isnoteplay)
		{
			Gotoxy(50 + 12 * _printxcount, 23 + 6 * _printycount);
			printf("■");
			_isnoteplay = false;
		}
		if (0 > countindex[arrayIndex][_count] && _isnoteplay)
		{
			clock_t _starttime2 = clock();
			clock_t _nowtime2;
			_isnoteplay = false;

			while (true)
			{
				_nowtime2 = clock();
				if (countindex[arrayIndex][_count] > _starttime2 - _nowtime2)
					break;
			}
		}
		if (_time >= countindex[arrayIndex][_count])
		{
			_starttime = clock();
			_printxcount++;
			_count++;
			_isnoteplay = true;
			if (_printxcount == 5) {
				_printycount++;
				_printxcount = 0;
			}
		}
	}
}
void Resetnote() {
	int _maxbuttonsize = 10;
	int _printxcount = 0;
	int _printycount = 0;

	while (_printxcount < _maxbuttonsize) {

		Gotoxy(48 + 12 * _printxcount, 23 + 6 * _printycount);
		printf("      ");

		_printxcount++;

		if (_printxcount == 5) {
			_printycount++;
			_maxbuttonsize -= 5;
			_printxcount = 0;
		}
	}
}


void GetPlayersKey(int arrayIndex, int(*countindex)[INPUT_SIZE]) {

	clock_t _starttime = clock();
	clock_t _nowtime;

	int _xPositioncount = 0;
	int _yPositioncount = 0;
	int _playercount = 0;
	int _timer = 0; //함수 종료시간.

	int _hittime = 0;
	int _correctime = _starttime;

	while (1) //마디의 첫박자 연산
	{
		_nowtime = clock();

	

		if (countindex[arrayIndex][_playercount] > 0) // 빈노트, 쉼표, 시간과 벗어난 노트 처리 
		{
			if (_correctime + GREAT < _nowtime) // 정답시간과 + 0.1초 벗어났을때 실패처리
			{
				Gotoxy(48 + 12 * _xPositioncount, 23 + 6 * _yPositioncount, 0, 4);
				printf(" bad ");

				_xPositioncount += 1;
				if (_xPositioncount == 5)
				{
					_yPositioncount += 1;
					_xPositioncount = 0;
				}
				_correctime += abs(countindex[arrayIndex][_playercount]);
				_playercount++;
				break;
			}
			else if (Keyinput()) //키입력
			{
				_hittime = _correctime - _nowtime;

				if (_hittime < PERPECT && _hittime > -PERPECT)
				{
					Gotoxy(48 + 12 * _xPositioncount, 23 + 6 * _yPositioncount, 0, 10);
					printf("  ★  ");

				}
				else if (_hittime < GREAT && _hittime > -GREAT)
				{
					Gotoxy(48 + 12 * _xPositioncount, 23 + 6 * _yPositioncount, 6);
					printf("Great");
				}
				else if (_hittime < GOOD && _hittime > -GOOD)
				{
					Gotoxy(48 + 12 * _xPositioncount, 23 + 6 * _yPositioncount);
					printf("Good");
				}
				else
				{
					Gotoxy(48 + 12 * _xPositioncount, 23 + 6 * _yPositioncount, 0, 4);
					printf(" bad ");
				}

				_xPositioncount += 1;
				if (_xPositioncount == 5)
				{
					_yPositioncount += 1;
					_xPositioncount = 0;
				}
				_correctime += countindex[arrayIndex][_playercount];
				_playercount++;

				break;
			}
		}
		else if (countindex[arrayIndex][_playercount] < 0) {
			if (_correctime < _nowtime) {
				_xPositioncount += 1;
				if (_xPositioncount == 5)
				{
					_yPositioncount += 1;
					_xPositioncount = 0;
				}
				_correctime += abs(countindex[arrayIndex][_playercount]);
				_playercount++;
				break;
			}
		}


	}


	while (1)
	{
		if (_playercount == INPUT_SIZE)// 완료시 탈출
		{
			break;
		}

		_nowtime = clock();

		

		if (countindex[arrayIndex][_playercount] > 0) // 빈노트, 쉼표, 시간과 벗어난 노트 처리 
		{
			if (_correctime + GREAT < _nowtime) // 정답시간과 + 0.1초 벗어났을때 실패처리
			{

				Gotoxy(48 + 12 * _xPositioncount, 23 + 6 * _yPositioncount, 0, 4);
				printf(" bad ");

				_xPositioncount += 1;
				if (_xPositioncount == 5)
				{
					_yPositioncount += 1;
					_xPositioncount = 0;
				}
				_correctime += abs(countindex[arrayIndex][_playercount]);
				_playercount++;
			}
			else if (Keyinput()) //키입력
			{

				_hittime = _correctime - _nowtime;

				if (_hittime < PERPECT && _hittime > -PERPECT)
				{
					Gotoxy(48 + 12 * _xPositioncount, 23 + 6 * _yPositioncount, 0, 10);
					printf("  ★  ");


				}
				else if (_hittime < GREAT && _hittime > -GREAT)
				{
					Gotoxy(48 + 12 * _xPositioncount, 23 + 6 * _yPositioncount, 6);
					printf("Great");
				}
				else if (_hittime < GOOD && _hittime > -GOOD)
				{
					Gotoxy(48 + 12 * _xPositioncount, 23 + 6 * _yPositioncount);
					printf("Good");
				}
				else
				{
					Gotoxy(48 + 12 * _xPositioncount, 23 + 6 * _yPositioncount, 0, 4);
					printf(" bad ");
				}

				_xPositioncount += 1;
				if (_xPositioncount == 5)
				{
					_yPositioncount += 1;
					_xPositioncount = 0;
				}
				_correctime += countindex[arrayIndex][_playercount];
				_playercount++;

			}
		}
		else if (countindex[arrayIndex][_playercount] < 0) {
			if (_correctime < _nowtime) {
				_xPositioncount += 1;
				if (_xPositioncount == 5)
				{
					_yPositioncount += 1;
					_xPositioncount = 0;
				}
				_correctime += abs(countindex[arrayIndex][_playercount]);
				_playercount++;
			}
		}
		else
		{
			_xPositioncount += 1; //
			if (_xPositioncount == 5)
			{
				_yPositioncount += 1;
				_xPositioncount = 0;
			}

			_playercount++;
		}




	}

}


void Gotoxy(int x, int y, unsigned short text_Color, unsigned short back_Color)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text_Color | back_Color << 4);
}

//글자색	배경색
//검정  0	
//어두운 파랑1
//어두운 초록 2
//어두운 하늘 3
//어두운 빨강 4
//어두운 보라 5
//어두운 노랑 6
//회색 7
//어두운 회색 8
//파랑 9
//초록 10
//하늘 11
//빨강 12
//보라 13
//노랑 14
//하양 15


bool Keyinput() {
	bool _input = false;

	if (GetAsyncKeyState(VK_SPACE) & 0x0001) {
		_input = true;
	}

	return _input;
}

void SetCursorview() {
	CONSOLE_CURSOR_INFO _cursorinfo = { 0, };
	_cursorinfo.bVisible = false;
	_cursorinfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_cursorinfo);
}