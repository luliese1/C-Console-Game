#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


void Gotoxy(int x, int y, unsigned short text_Color = 15, unsigned short back_Color = 0);
void PrintNumber(int x, int y, int Num);
int loadscore();
void ShowScore();
void PrintScoreTEXT(int x, int y);
void PrintHighScoreTEXT(int x, int y);
void PrintNickName(int x, int y, int* name);
void PrintChar(int x, int y, int _char);

//0~9    세로    가로    

extern int g_Score;
int g_Nickname[3] = {0,0,0};
char g_number[10][7][13] = { {

{"   ## ##    "},
{"  ##   ##   "},
{"  ##   ##   "},
{"  ##   ##   "},
{"  ##   ##   "},
{"  ##   ##   "},
{"   ## ##    "}, },
{
{"    ##      "},
{"   ###      "},
{"    ##      "},
{"    ##      "},
{"    ##      "},
{"    ##      "},
{"   ####     "}, },
{
{"   ## ##    "},
{"   ##  ##   "},
{"      ##    "},
{"     ##     "},
{"    ##      "},
{"   #   ##   "},
{"  ######    "},},

{
{"   ## ##    "},
{"  ##   ##   "},
{"      ##    "},
{"    ###     "},
{"      ##    "},
{"  ##   ##   "},
{"   ## ##    "}, },

{
{ "     ##    " },
{ "    # ##   " },
{ "   ## ##   " },
{ "  ##  ##   " },
{ "  ### ###  " },
{ "      ##   " },
{ "      ##   " }, },

{
{ "  ######   " },
{ "  ##       " },
{ "  ## ##    " },
{ "      ##   " },
{ "  ##  ##   " },
{ "  ##  ##   " },
{ "    ###    " }, },

{
{ "   #####   " },
{ "  ##   ##  " },
{ "  ##       " },
{ "  ## ###   " },
{ "  ##   ##  " },
{ "  ##   ##  " },
{ "   ## ##   " }, },

{
{ "  ######   " },
{ "  ##   #   " },
{ "     ##    " },
{ "    ##     " },
{ "    ##     " },
{ "    ##     " },
{ "    ##     " }, },

{
{ "   ## ##   " },
{ "  ##   ##  " },
{ "  ##   ##  " },
{ "   ## ##   " },
{ "  ##   ##  " },
{ "  ##   ##  " },
{ "   ## ##   " }, },
{
{ "   ## ##   " },
{ "  #    ##  " },
{ "  ##   ##  " },
{ "   ## ###  " },
{ "       ##  " },
{ "  ##   ##  " },
{ "    ## ##  " }, }


};
char g_ScoreText[7][36] =
{
{" _____  _____  _____ ______  _____"},
{"/  ___|/  __ l|  _  || ___ l|  ___|"},
{"l `--. | /  l/| | | || |_/ /| |__  "},
{" `--. l| |    | | | ||    / |  __| "},
{"/l__/ /| l__/ll l_/ /| |l l | |___ "},
{"l____/  l____/ l___/ l_| l_|l____/ "},
};

char g_HighScoreText[6][69] =
{
{" _   _  _____  _____  _   _   _____  _____  _____ ______  _____"},
{"| | | ||_   _||  __ l| | | | /  ___|/  __ l|  _  || ___ l|  ___|"},
{"| |_| |  | |  | |  l/| |_| | l `--. | /  l/| | | || |_/ /| |__  "},
{"|  _  |  | |  | | __ |  _  |  `--. l| |    | | | ||    / |  __| "},
{"| | | | _| |_ | |_l l| | | | /l__/ /| l__/ll l_/ /| |l l | |___ "},
{"l_| |_/ l___/  l____/l_| |_/ l____/  l____/ l___/ l_| l_|l____/ "},

};
const char* g_Alphabet[26][5] =
{
	{
	{"  ,---.   "},
	{" /  O  l  "},
	{"|  .-.  | "},
	{"|  | |  | "},
	{"`--' `--' "},
	},
	{
	{",-----.   "},
	{"|  |) /_  "},
	{"|  .-.  l "},
	{"|  '--' / "},
	{"`------'  "},
	},
	{
	{" ,-----. "},
	{"'  .--./ "},
	{"|  |     "},
	{"'  '--'l "},
	{" `-----' "},
	},
	{
	{",------.   "},
	{"|  .-.  l  "},
	{"|  |  l  : "},
	{"|  '--'  / "},
	{"`-------'  "},
	},
	{
	{",------. "},
	{"|  .---' "},
	{"|  `--,  "},
	{"|  `---. "},
	{"`------' "},
	},

	{
	{",------. "},
	{"|  .---' "},
	{"|  `--,  "},
	{"|  |`    "},
	{"`--'     "},
	},

	{
	{" ,----.    "},
	{"'  .-./    "},
	{"|  | .---. "},
	{"'  '--'  | "},
	{" `------'  "},
	},

	{
	{",--.  ,--. "},
	{"|  '--'  | "},
	{"|  .--.  | "},
	{"|  |  |  | "},
	{"`--'  `--' "},
	},

	{
	{",--. "},
	{"|  | "},
	{"|  | "},
	{"|  | "},
	{"`--' "},
	},

	{
	{"     ,--."},
	{"     |  |"},
	{",--. |  |"},
	{"|  '-'  /"},
	{" `-----' "},
	},
	{
	{",--. ,--. "},
	{"|  .'   / "},
	{"|  .   '  "},
	{"|  |l   l "},
	{"`--' '--' "},
	},
	{
	{",--.    "},
	{"|  |    "},
	{"|  |    "},
	{"|  '--. "},
	{"`-----' "},
	},
	{
	{",--.  ,--. "},
	{"|  ,'.|  | "},
	{"|  |' '  | "},
	{"|  | `   | "},
	{"`--'  `--' "},
	},
	{
	{",--.   ,--. "},
	{"|   `.'   | "},
	{"|  |'.'|  | "},
	{"|  |   |  | "},
	{"`--'   `--' "},
	},
	{
	{" ,-----.  "},
	{"'  .-.  ' "},
	{"|  | |  | "},
	{"'  '-'  ' "},
	{" `-----'  "},
	},
	{
	{",------.  "},
	{"|  .--. ' "},
	{"|  '--' | "},
	{"|  | --'  "},
	{"`--'      "},
	},
	{
	{" ,-----.   "},
	{"'  .-.  '  "},
	{"|  | |  |  "},
	{"'  '-'  '-."},
	{" `-----'--'"},
	},
	{
	{",------.  "},
	{"|  .--. ' "},
	{"|  '--'.' "},
	{"|  |l  l  "},
	{"`--' '--' "},
	},
	{
	{" ,---.   "},
	{"'   .-'  "},
	{"`.  `-.  "},
	{".-'    | "},
	{"`-----'  "},
	},
	{
	{",--------. "},
	{"'--.  .--' "},
	{"   |  |    "},
	{"   |  |    "},
	{"   `--'    "},
	},
	{
	{",--. ,--. "},
	{"|  | |  | "},
	{"|  | |  | "},
	{"'  '-'  ' "},
	{" `-----'  "},
	},
	{
	{",--.   ,--. "},
	{" l  `.'  /  "},
	{"  l     /   "},
	{"   l   /    "},
	{"    `-'     "},
	},
	{
	{",--.   ,--. "},
	{"|  |   |  | "},
	{"|  |.'.|  | "},
	{"|   ,'.   | "},
	{"'--'   '--' "},
	},
	{
	{",--.   ,--. "},
	{" l  `.'  /  "},
	{"  .'    l   "},
	{" /  .'.  l  "},
	{"'--'   '--' "},
	},
	{
	{",--.   ,--. "},
	{" l  `.'  /  "},
	{"  '.    /   "},
	{"    |  |    "},
	{"    `--'    "},
	},
	{
	{",-------. "},
	{"`--.   /  "},
	{"  /   /   "},
	{" /   `--. "},
	{"`-------' "},
	},
};
            
                                                                                                                                                                                                                                                                                                                                                                   
                                        
                                        
                                        
                                        
                                        
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
//x좌표 y좌표 점수 입력, 더 할 점수
void PrintNumber(int x , int y, int Num)
{
	g_Score += Num;
	Num = g_Score;
	int A = 0;
	int Count = 0;
	int Max = 100000;
	
	while (Max != 0)
	{
		A = Num / Max;
		Num = Num % Max;
		if (A < 10)
		{
			for (int i = 0; i < 7; i++)
			{
				Gotoxy(x + Count * 12, y + i);
				for (int j = 0; j < 13; j++)
				{

					printf("%c", g_number[A][i][j]);

				}

			}
			Count++;
			Max = Max * 0.1;
		}
		else
		{

		}
	}
}
//원하는 숫자 출력

void PrintScoreTEXT(int x ,int y)
{

	for (int i = 0; i < 7; i++)
	{
		
		for (int j = 0; j < 36; j++)
		{
			Gotoxy(x+j, y + i);
			printf("%c", g_ScoreText[i][j]);
		}

	}
}

//신성현 highscore텍스트 출력함수.
void PrintHighScoreTEXT(int x, int y)
{

	for (int i = 0; i < 6; i++)
	{

		for (int j = 0; j < 69; j++)
		{
			Gotoxy(x + j, y + i);
			printf("%c", g_HighScoreText[i][j]);
		}

	}
}

//신성현 숫자와 좌표 입력시 숫자 출력함수.
void ShowNumber(int x, int y, int Num)
{
	int A = 0;
	int Count = 0;
	int Max = 100000;
	while (Max != 0)
	{
		A = Num / Max;
		Num = Num % Max;
		if (A < 10)
		{
			for (int i = 0; i < 7; i++)
			{
				Gotoxy(x + Count * 12, y + i);
				for (int j = 0; j < 13; j++)
				{

					printf("%c", g_number[A][i][j]);

				}

			}
			Count++;
			Max = Max * 0.1;
		}
		else
		{

		}
	}
}

//신성현 저장된 하이스코어 출력 함수.
int loadscore()
{
	FILE* fp;
	fopen_s(&fp, "Score.txt", "r");
	int score = 0;
	if (fp != NULL)
	{
		fscanf_s(fp, "%d %d %d %d", &score, &g_Nickname[0], &g_Nickname[1], &g_Nickname[2]);
		fclose(fp);
	}
	return score;
}

//신성현 하이스코어 저장 함수.
void savescore()
{
	FILE* fp;
	fopen_s(&fp, "Score.txt", "w");
	if (fp != NULL)
	{
		fprintf(fp, "%d %d %d %d\n", g_Score, g_Nickname[0], g_Nickname[1], g_Nickname[2]);
		fclose(fp);
	}
}
//게임 종료후 최종 스코어 발표.
void ShowScore()
{
	int highScorex = 67;
	int highscorey = 3;
	int myscorex = 65;
	int myscorey = 40;
	int Nickx = 29;
	int Nicky = 10;
	system("cls");
	
	//현재 점수
	PrintScoreTEXT(myscorex + 18, myscorey - 9);
	PrintNumber(myscorex, myscorey, 0);
	//최고점수
	PrintHighScoreTEXT(highScorex, highscorey);
	ShowNumber(highScorex -4, highscorey +7, loadscore());

	PrintNickName(highScorex+16, highscorey+ 17, g_Nickname);
	
	if (loadscore() < g_Score)
	{
		

		int i = 0;
		int count = 0;
		PrintChar(myscorex + count * Nickx, myscorey + Nicky, i);
		for (int j = 0; j < 3; j++)
		{
			Gotoxy(myscorex - 2 + j * Nickx, myscorey + Nicky + 6, 10);
			printf("_____________");
		}
		while (count < 3)
		{

			if (GetAsyncKeyState(VK_UP) & 1 && i < 25)
			{
				i++;
				PrintChar(myscorex + count * Nickx, myscorey + Nicky, i);
			}
			else if (GetAsyncKeyState(VK_DOWN) & 1 && i > 0)
			{
				i--;
				PrintChar(myscorex + count * Nickx, myscorey + Nicky, i);
			}
			else if (GetAsyncKeyState(VK_RETURN) & 1)
			{
				g_Nickname[count] = i;
				count++;
				i = 0;
				PrintChar(myscorex + count * Nickx, myscorey + Nicky, i);

			}

		}
		savescore();
	}
	else
	{
		int i = 0;
		int count = 0;
		PrintChar(myscorex + count * Nickx, myscorey + Nicky, i);
		for (int j = 0; j < 3; j++)
		{
			Gotoxy(myscorex - 2 + j * Nickx, myscorey + Nicky + 6, 10);
			printf("_____________");
		}
		while (count < 3)
		{

			if (GetAsyncKeyState(VK_UP) & 1 && i < 25)
			{
				i++;
				PrintChar(myscorex + count * Nickx, myscorey + Nicky, i);
			}
			else if (GetAsyncKeyState(VK_DOWN) & 1 && i > 0)
			{
				i--;
				PrintChar(myscorex + count * Nickx, myscorey + Nicky, i);
			}
			else if (GetAsyncKeyState(VK_RETURN) & 1)
			{
				g_Nickname[count] = i;
				count++;
				i = 0;
				PrintChar(myscorex + count * Nickx, myscorey + Nicky, i);

			}

		}
	}

	
	system("cls");
}

//3글자 문자열을 출력
void PrintNickName(int x, int y, int* name)
{

	int Count = 0;
	while (Count < 3)
	{
			for (int i = 0; i < 5; i++)
			{
				Gotoxy(x + Count * 12, y + i);
					printf("%s", g_Alphabet[name[Count]][i]);

			}
			Count++;
	}
}

//알파벳 문자를 출력 a~z (x좌표, y좌표, 0~25 (a~z))
void PrintChar(int x, int y, int _char)
{
	for (int i = 0; i < 5; i++)
	{
		Gotoxy(x, y + i);
		printf("              ");

	}
	for (int i = 0; i < 5; i++)
	{
		Gotoxy(x , y + i);
		printf("%s", g_Alphabet[_char][i]);

	}
}