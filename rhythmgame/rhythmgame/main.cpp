#include <Windows.h>

void InitSound();
void SetCursorview();
void InitConsole(int _fontsize);
extern void Startmenu();
extern void Soundsetup();
extern void EffectSoundsetup(); // 효과음 사운드 셋업
extern void SelectAnimInit();


int main() {
	InitConsole(10);
	InitSound();
	SelectAnimInit();
	Startmenu();
}


void InitConsole(int _fontsize) {

	// 콘솔의 폰트 사이즈를 조절하는 처리
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = _fontsize;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	// 콘솔의 창 사이즈 조절
	system("mode con cols=200 lines=90");
	SetCursorview();
}

// 게임 시작시 초기화
void InitSound() {
    // 음원 설정
    Soundsetup();
    // 효과음 설정
    EffectSoundsetup();
};

void SetCursorview() {
	CONSOLE_CURSOR_INFO _cursorinfo = { 0, };
	_cursorinfo.bVisible = false;
	_cursorinfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_cursorinfo);
}

