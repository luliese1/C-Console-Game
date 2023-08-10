#include <Windows.h>

void InitSound();
void SetCursorview();
void InitConsole(int _fontsize);
extern void Startmenu();
extern void Soundsetup();
extern void EffectSoundsetup(); // ȿ���� ���� �¾�
extern void SelectAnimInit();


int main() {
	InitConsole(10);
	InitSound();
	SelectAnimInit();
	Startmenu();
}


void InitConsole(int _fontsize) {

	// �ܼ��� ��Ʈ ����� �����ϴ� ó��
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = _fontsize;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	// �ܼ��� â ������ ����
	system("mode con cols=200 lines=90");
	SetCursorview();
}

// ���� ���۽� �ʱ�ȭ
void InitSound() {
    // ���� ����
    Soundsetup();
    // ȿ���� ����
    EffectSoundsetup();
};

void SetCursorview() {
	CONSOLE_CURSOR_INFO _cursorinfo = { 0, };
	_cursorinfo.bVisible = false;
	_cursorinfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_cursorinfo);
}

