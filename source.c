#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

void moveBoard(int* x, int* y);
void drawBlock(struct block * grp);
void setting();
void bounceBall(int* ballX, int* ballY, int boardX, int boardY, int* angle);
void drawBall(int ballX, int ballY, int angle);
int CrashWRock();

typedef struct block {
	int pt;
	int x, y;
}Block;
Block blk[50] = { {0,0,0} };
int cnt;

int main()
{
	int kb = 0;
	int gridX = 17, gridY = 20;
	int ballX = 20, ballY = 19;
	int angle = 0;

	int bX = 0, bY = 0;
	for (int i = 0; i < 50; i++) {
		blk[i].pt = 1;
		blk[i].x = bX;
		blk[i].y = bY;

		if (bX >= 40) {
			bX = 0;
			bY += 2;
		}
		else
			bX += 2;
	}

	/*COORD Pos;
	Pos.X = 50;
	Pos.Y = 3;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	for (int i = 0; i < 50; i++)
	{
		Pos.X = 50;
		Pos.Y = 3 + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		printf("%d : x - %d, y - %d\n", i, blk[i].x, blk[i].y);
	}*/

	setting();


	while (1) {
		system("cls");
		bounceBall(&ballX, &ballY, gridX, gridY, &angle);

		drawBall(ballX, ballY, angle);
		moveBoard(&gridX, &gridY);


		if (_kbhit()) {
			if (_kbhit()) {
				kb = _getch();
				if (kb == 224)
				{
					kb = _getch();
					switch (kb)
					{
						case 75:
							gridX -= 1;
							moveBoard(&gridX, &gridY);
							break;
						case 77:
							gridX += 1;
							moveBoard(&gridX, &gridY);
							break;
					}
				}
			}	
		}

		if (ballY > 20)
		{
			COORD Pos;
			Pos.X = 17; Pos.Y = 10;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
			printf("GAMEOVER");
			
			Pos.X = 17; Pos.Y = 25;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

			drawBall(ballX, ballY, angle);
			return 0;
		}
	}

	return 0;
}


void setting()
{
	drawBlock(blk);
	
	COORD Pos;
	Pos.X = 17;
	Pos.Y = 20;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	printf("忙式式式式式忖");

	Pos.X = 20;
	Pos.Y = 19;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	printf("∞");
}
void moveBoard(int* x, int* y)
{
	if (*x < 0) {
		*x += 2;
		return;
	}		
	else if (*x >= 36) {
		*x -= 2;
		return;
	}
	drawBlock(blk);

	COORD Pos;
	Pos.X = *x;
	Pos.Y = *y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	
	printf("忙式式式式式忖\n %d %d", *x, *y);		//醞褕擎 x + 2 || x + 3
}


void drawBlock(struct block * grp)
{
	for (int i = 0; i < 50; i++) {
		if ((grp + i)->pt != 1)
			continue;


		COORD Pos;
		Pos.X = (grp + i)->x;
		Pos.Y = (grp + i)->y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		printf("仃");
	}
}

void bounceBall(int* ballX, int* ballY, int boardX, int boardY, int* angle)
{
	
	if (*ballY == 19 && *ballX >= boardX && *ballX <= boardX + 6)
	{
		int k = (*ballX) - boardX;

		switch (k)
		{
		case 0:
			*angle = 30;
			(*ballX) -= 2;
			(*ballY)--;
			break;
		case 1:
		case 2:
			*angle = 45;
			(*ballY)--;
			(*ballX)--;
			break;
		/*case 2:
			*angle = 60;

			if (cnt == 1) {
				cnt = 0;
				break;
			}
			cnt++;

			(*ballX)--;
			(*ballY) -= 2;
			break;*/
		case 3:
		case 4:
			*angle = 90;
			(*ballY)--;
			break;
		/*case 4:
			*angle = 120;
			
			if (cnt == 1) {
				cnt = 0;
				break;
			}
			cnt++;

			(*ballX)++;
			(*ballY) -= 2;
			break;*/
		case 5:
			*angle = 135;
			(*ballY)--;
			(*ballX)++;
			break;
		case 6 :
			*angle = 150;
			(*ballX) += 2;
			(*ballY)--;
			break;
		}

		
	}
	
	//漁給婁 睡詠??
	if (*ballY <= 6 && CrashWRock(*ballX, *ballY)) 
	{
		(*angle) = 360 - (*angle);
		cnt = 0;
	}
	else if (*ballY < 1) {
		(*angle) = 360 - (*angle);
		cnt = 0;
	}

	//掘⑷餌о 0. 頂溥螃朝 (*ballY)++ 掘⑷ж晦 陝紫朝 憮薹擊 晦遽戲煎 0紫檜晦 陽僥縑 熱霜 ж鬼擎 270紫檜棻 
	//  1. 漁給婁 蜃棻戲賊 x蹴渠蘆檜 檜瘀雖貊 頂溥螞棻
	//2. 漁婁 湊戲賊 y蹴 渠蘆檜 檜瘀雖貊 檜翕и棻					(ж鬼й陽曖 y蹴 渠蘆紫 橾欽 掘⑷л (*angle) > 180 橾陽)							諫猿~!!!!!
	//3. 漁給婁 蜃棻戲賊 漁給檜 梟霞棻


	//謝辦 漁婁 醱給
	if (*ballX >= 40)														//謝辦漁婁 醱給
	{
		//y蹴 渠蘆
		if (*angle < 180)
			*angle = 180 - *angle;
		else
			*angle = 360 - ((*angle) - 180);
	}																					
	else if (*ballX <= 0)
	{
		//y蹴渠蘆
		if (*angle < 180)
			*angle = 180 - *angle;
		else
			*angle = 360 - ((*angle) - 180);	//營匐饜陛 в蹂м棲棻.
	}

	//陝紫縑 評艇 霞ч
	switch (*angle) {														//謝辦漁婁 醱給
	case 30 :
		(*ballX) -= 2;
		(*ballY)--;
		break;
	case 45 :
		(*ballY)--;
		(*ballX)--;
		break;
	/*case 60 :
		if (cnt == 1) {
			cnt = 0;
			break;
		}
		cnt++;

		(*ballX)--;
		(*ballY) -= 2;
		break;*/
	case 90 :
		(*ballY)--;
		break;
	/*case 120 :
		if (cnt == 1) {
			cnt = 0;
			break;
		}
		cnt++;

		(*ballX)++;
		(*ballY) -= 2;
		break;*/
	case 135 :
		(*ballY)--;
		(*ballX)++;
		break;
	case 150 :
		(*ballX) += 2;
		(*ballY)--;
		break;
	case 210 :
		(*ballX) += 2;
		(*ballY)++;
		break;
	case 225 :
		(*ballX)++;
		(*ballY)++;
		break;
	/*case 240 :
		if (cnt == 1) {
			cnt = 0;
			break;
		}
		cnt++;

		(*ballX)++;
		(*ballY) += 2;
		break;*/
	case 270 :
		(*ballY)++;
		break;
	/*case 300 :
		if (cnt == 1) {
			cnt = 0;
			break;
		}
		cnt++;										

		(*ballX)--;
		(*ballY) += 2;
		break;*/
	case 315 :
		(*ballX)--;
		(*ballY)++;
		break;
	case 330 :
		(*ballX) -= 2;
		(*ballY)++;
		break;
	}																		

	

}

void drawBall(int ballX, int ballY, int angle)
{
	COORD Pos;
	Pos.X = ballX;
	Pos.Y = ballY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	printf("∞ %d %d %d ", ballX, ballY, angle);
}

int CrashWRock(int ballX, int ballY)
{
	for (int i = 0; i < 50; i++)
	{
		if (blk[i].pt == 1 && blk[i].x == ballX && blk[i].y == ballY - 1)
		{
			blk[i].pt = 0;

			return 1;
		}
	}

	return 0;
}