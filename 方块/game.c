#pragma once
#include"game.h"
//暂停
static void _Pause();
//获取方向
static void _HandleDirective(struct Game *pGame);
//产生新图形
static void ChanceShape(struct Game *pGame);
//确定新图形的样子
static void IsShape(int twist, struct Shape* shape);


struct Game *CreateGame()
{
	struct Game *pGame = (struct Game *)malloc(sizeof(struct Game));
	pGame->width = 10;
	pGame->height = 20;
	pGame->score = 0;
	pGame->direction = DOWN;
	pGame->status = GOOD;
	pGame->shape = (struct Shape*)malloc(sizeof(struct Shape));
	pGame->shape->postion = (pos *)malloc(sizeof(pos) * 4);
	pGame->shape->postion[0].x = 3;
	pGame->shape->postion[0].y = 0;
	pGame->shape->shapetype = SHAPE1;
	pGame->sleeptime = 500;
	pGame->twist = 0;
	return pGame;
}
static void ChanceShape(struct Game *pGame)
{
	pGame->sleeptime = 500;
	pGame->shape->shapetype = rand() % 6;//0-5
										 //pGame->shape->shapetype = 1;//0-5
	pGame->shape->postion[0].x = 3;
	pGame->shape->postion[0].y = 0;
	IsShape(pGame->twist, pGame->shape);
}
static void IsShape(int twist, struct Shape* shape)
{
	int x = shape->postion[0].x;
	int y = shape->postion[0].y;
	switch (shape->shapetype)
	{
	case SHAPE1:
	{
		//o o
		//o o
		shape->postion[1].x = x + 1;
		shape->postion[1].y = y;
		shape->postion[2].x = x;
		shape->postion[2].y = y + 1;
		shape->postion[3].x = x + 1;
		shape->postion[3].y = y + 1;
		break;
	}
	case SHAPE2:
	{
		if (twist == 0)
		{
			//o o o
			//o
			shape->postion[1].x = x + 1;
			shape->postion[1].y = y;
			shape->postion[2].x = x + 2;
			shape->postion[2].y = y;
			shape->postion[3].x = x;
			shape->postion[3].y = y + 1;
		}
		else if (twist == 3)
		{
			//0
			//0
			//0 0
			shape->postion[1].x = x;
			shape->postion[1].y = y + 1;
			shape->postion[2].x = x;
			shape->postion[2].y = y + 2;
			shape->postion[3].x = x + 1;
			shape->postion[3].y = y + 2;
		}
		else if (twist == 2)
		{
			//    0
			//0 0 0
			shape->postion[1].x = x;
			shape->postion[1].y = y + 1;
			shape->postion[2].x = x - 1;
			shape->postion[2].y = y + 1;
			shape->postion[3].x = x - 2;
			shape->postion[3].y = y + 1;
		}
		else if (twist == 1)
		{
			//0 0
			//  0
			//  0
			shape->postion[1].x = x + 1;
			shape->postion[1].y = y;
			shape->postion[2].x = x + 1;
			shape->postion[2].y = y + 1;
			shape->postion[3].x = x + 1;
			shape->postion[3].y = y + 2;
		}
		break;
	}
	case SHAPE3:
	{
		if (twist == 0 || twist == 2)
		{//o o o o
			shape->postion[1].x = x + 1;
			shape->postion[1].y = y;
			shape->postion[2].x = x + 2;
			shape->postion[2].y = y;
			shape->postion[3].x = x + 3;
			shape->postion[3].y = y;
		}
		else if (twist == 1 || twist == 3)
		{
			//0
			//0
			//0
			//0
			shape->postion[1].x = x;
			shape->postion[1].y = y + 1;
			shape->postion[2].x = x;
			shape->postion[2].y = y + 2;
			shape->postion[3].x = x;
			shape->postion[3].y = y + 3;
		}
		break;

	}
	case SHAPE4:
	{
		if (twist == 0 || twist == 2)
		{
			//o
			//o
			//o
			//o
			shape->postion[1].x = x;
			shape->postion[1].y = y + 1;
			shape->postion[2].x = x;
			shape->postion[2].y = y + 2;
			shape->postion[3].x = x;
			shape->postion[3].y = y + 3;
		}
		else if (twist == 1 || twist == 3)
		{
			//o o o o
			shape->postion[1].x = x + 1;
			shape->postion[1].y = y;
			shape->postion[2].x = x + 2;
			shape->postion[2].y = y;
			shape->postion[3].x = x + 3;
			shape->postion[3].y = y;
		}
		break;
	}
	case SHAPE5:
	{
		if (twist == 0)
		{
			//o o o
			//  o
			shape->postion[1].x = x + 1;
			shape->postion[1].y = y;
			shape->postion[2].x = x + 2;
			shape->postion[2].y = y;
			shape->postion[3].x = x + 1;
			shape->postion[3].y = y + 1;
		}
		else if (twist == 1)
		{
			//  0
			//0 0
			//  0
			shape->postion[1].x = x - 1;
			shape->postion[1].y = y + 1;
			shape->postion[2].x = x;
			shape->postion[2].y = y + 1;
			shape->postion[3].x = x;
			shape->postion[3].y = y + 2;
		}
		else if (twist == 2)
		{
			//  o
			//o o o
			shape->postion[1].x = x - 1;
			shape->postion[1].y = y + 1;
			shape->postion[2].x = x;
			shape->postion[2].y = y + 1;
			shape->postion[3].x = x + 1;
			shape->postion[3].y = y + 1;
		}
		else if (twist == 3)
		{
			//0
			//0 0
			//0
			shape->postion[1].x = x;
			shape->postion[1].y = y + 1;
			shape->postion[2].x = x + 1;
			shape->postion[2].y = y + 1;
			shape->postion[3].x = x;
			shape->postion[3].y = y + 2;
		}
		break;
	}
	case SHAPE6:
	{
		if (twist == 0 || twist == 2)
		{
			//o o
			//  o o
			shape->postion[1].x = x + 1;
			shape->postion[1].y = y;
			shape->postion[2].x = x + 1;
			shape->postion[2].y = y + 1;
			shape->postion[3].x = x + 2;
			shape->postion[3].y = y + 1;
		}
		else if (twist == 1 || twist == 3)
		{   //   0
			// 0 0
			// 0 
			shape->postion[1].x = x;
			shape->postion[1].y = y + 1;
			shape->postion[2].x = x - 1;
			shape->postion[2].y = y + 1;
			shape->postion[3].x = x - 1;
			shape->postion[3].y = y + 2;
		}

		break;
	}
	default:
		break;
	}
}
static int CanGoRight(int *a, struct Shape *shape, int width)
{
	if (shape->postion[0].x + 1 >= width || shape->postion[1].x + 1 >= width ||
		shape->postion[2].x + 1 >= width || shape->postion[3].x + 1 >= width)
		return 1;
	if (IsRightHaveShape(a, shape, width) == 1)
		return 1;
	return 0;
}
static int IsRightWell(int *a, struct Shape *shape, int width)
{
	if (shape->postion[0].x + 1 > width || shape->postion[1].x + 1 > width ||
		shape->postion[2].x + 1 > width || shape->postion[3].x + 1 > width)
		return 1;
	if (IsRightHaveShape(a, shape, width) == 1)
		return 1;
	return 0;
}
int CanGoLift(int *a, struct Game*pGame)
{
	if (pGame->shape->postion[0].x > 0 &&
		pGame->shape->postion[1].x > 0 &&
		pGame->shape->postion[2].x > 0 &&
		pGame->shape->postion[3].x > 0 &&
		IsLeftHaveShape(a, pGame->shape, pGame->width) == 0)
		return 0;
	else return 1;
}
int IsLiftWell(int *a, struct Game*pGame)
{
	if (pGame->shape->postion[0].x >= 0 &&
		pGame->shape->postion[1].x >= 0 &&
		pGame->shape->postion[2].x >= 0 &&
		pGame->shape->postion[3].x >= 0 &&
		IsLeftHaveShape(a, pGame->shape, pGame->width) == 0)
		return 0;
	else return 1;
}
static void GoNextPos(int *a, struct Game *pGame)
{
	if (pGame->direction == UP)
	{
		int cur = (pGame->twist + 1) % 4;
		IsShape(cur, pGame->shape);
		if (IsLiftWell(a, pGame) == 0 && IsRightWell(a, pGame->shape, pGame->width) == 0)
		{
			pGame->twist = cur;
		}
		else {
			pGame->direction = DOWN;
		}
		pGame->sleeptime = 500;
	}
	else if (pGame->direction == LEFT)
	{
		if (CanGoLift(a, pGame) == 0)
			pGame->shape->postion[0].x--;
		else pGame->direction = DOWN;
		pGame->sleeptime = 500;
		IsShape(pGame->twist, pGame->shape);

	}
	else if (pGame->direction == RIGHT)
	{
		if (CanGoRight(a, pGame->shape, pGame->width) == 0)
			pGame->shape->postion[0].x++;
		else pGame->direction = DOWN;
		pGame->sleeptime = 500;
		IsShape(pGame->twist, pGame->shape);

	}
	if (pGame->direction == DOWN)
	{
		pGame->shape->postion[0].y++;
		IsShape(pGame->twist, pGame->shape);

	}
	pGame->direction = DOWN;
}
static int IsShapeWELL(struct Game *pGame, int *a)
{
	int i = 0;
	for (i = 0; i < 4; i++)
	{
		if (pGame->shape->postion[i].y + 1 >= pGame->height)
			return 1;
	}
	for (i = 0; i < 4; i++)
	{
		int x = pGame->shape->postion[i].x;
		int y = pGame->shape->postion[i].y;
		int j = 0;
		for (j = 0; j < 4; j++)
		{
			if (i == j)
				continue;
			if (x == pGame->shape->postion[j].x && y + 1 == pGame->shape->postion[j].y)
				break;
		}
		if (j == 4 && a[x + (y + 1)*pGame->width] != 0)
			return 1;
	}
	return 0;
}

static int ThisShapeDown(struct Game *pGame, int *a)
{
	int x = pGame->shape->postion[0].x;
	int y = pGame->shape->postion[0].y;
	if (IsShapeWELL(pGame, a) == 1)
		return 1;
	return 0;
}
void StartGame(struct Game *pGame)
{
	struct UI* UI = UIInitialize(pGame->width, pGame->height);
	UIDisplayWizard(UI);
	UIDisplayGameWindow(UI, 0);
	ChanceShape(pGame);
	while (1) {
		if (IsGameOver(UI) == 1)
		{
			break;
		}
		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}
		else if (GetAsyncKeyState(VK_SPACE)) {
			_Pause();
		}
		UIDisplayBlock(UI, pGame->shape);
		_HandleDirective(pGame);

		Sleep(pGame->sleeptime);
		if (ThisShapeDown(pGame, UI->_a) == 1)
		{
			pGame->score += 10 * InsertScore(UI);
			UIDisplayScore(UI, pGame->score);
			ChanceShape(pGame);
		}
		else
		{
			UICleanBlock(UI, pGame->shape);
		}
		GoNextPos(UI->_a, pGame);
	}
	_CoordinatePosAtXY(UI, 3, 10);
	printf("游戏结束");
	_ResetCursorPosition(UI);
	UIDeinitialize(UI);
}
void DestoryGame(struct Game *pGame)
{
}

static void _Pause()
{
	while (1)
	{
		Sleep(300);
		if (GetAsyncKeyState(VK_SPACE))
		{
			break;
		}
	}
}
static void _HandleDirective(struct Game *pGame)
{
	if (GetAsyncKeyState(VK_UP)) {
		pGame->direction = UP;
	}
	else if (GetAsyncKeyState(VK_DOWN)) {
		pGame->direction = DOWN;
		if (pGame->sleeptime>100)
			pGame->sleeptime -= 100;
	}
	else if (GetAsyncKeyState(VK_LEFT)) {
		pGame->direction = LEFT;
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		pGame->direction = RIGHT;
	}
}
