#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

extern void Gotoxy(int x, int y, unsigned short text_Color = 15, unsigned short back_Color = 0);

void Startmenu() {
	static int _selectnum=0;
	int _lownum = 0;
	int _maxnum = 2;

	Gotoxy(75, 21, 15, 0);
	printf("시작");
	Gotoxy(75, 22, 15, 0);
	printf("나가기");
	Gotoxy(75, 23, 15, 0);
	printf("제작자");

	while (1) {

		if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
			Gotoxy(71, 21 + _selectnum, 15, 0);
			printf("  ");
			if (_selectnum == _maxnum) {
			}
			else {
				_selectnum++;
			}
		}
		else if (GetAsyncKeyState(VK_UP) & 0x0001) {
				Gotoxy(71, 21 + _selectnum, 15, 0);
				printf("  ");
			if (_selectnum == _lownum) {
			}
			else {
				_selectnum--;
			}

		}
		else if (GetAsyncKeyState(VK_RETURN) & 0x0001){
			if (_selectnum == 0) {
				break;
			}
			else if (_selectnum == 1) {
				exit(0);
			}
			else if (_selectnum == 2) {

			}
		}

		Gotoxy(71, 21 + _selectnum, 15, 0);
		printf("▶");
	}

}
