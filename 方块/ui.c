#define _CRT_SECURE_NO_WARNINGS

#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// �ƶ���굽x��y�������������Ļ
static void _SetPos(int x, int y);
// ��ʾǽ
static void _DisplayWall(const struct UI *pUI);
// ��ʾ�Ҳ���Ϣ
static void _DisplayDesc(const struct UI *pUI);
// ����Ϸ�̵�x��y����ת��Ϊ���������Ļ��x��y
void _CoordinatePosAtXY(const struct UI *pUI, int x, int y);
// ���ù�굽��Ļ�·�����Ҫ��Ϊ����ʾ������
void _ResetCursorPosition(const struct UI *pUI);
//������������
void GetDown(int i, int *a, int width);
//��ʾ������ͼ��
static void  _DisplayShape(const struct UI *pUI, struct Shape*shape);
static void  _ClearShape(const struct UI *pUI, struct Shape *shape);

//���õ�����ɫ
void SetColor(unsigned short ForeColor, unsigned short BackGroundColor)
{
	//forecolor ������ɫbackgroundcolor��ɫ
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, (ForeColor % 16) | (BackGroundColor % 16 * 16));
}
struct UI * UIInitialize(int width, int height)
{
	const int left = 2;
	const int top = 2;
	const int blockWidth = 2;   
	const int descWidth = 50;

	struct UI *pUI = (struct UI *)malloc(sizeof(struct UI));
	pUI->gameWidth = width;
	pUI->gameHeight = height;
	pUI->marginLeft = left;
	pUI->marginTop = top;
	pUI->windowWidth = left + (width + 2) * blockWidth + descWidth;
	pUI->windowHeight = top + height + 2 + 3;
	pUI->Block = "��";
	pUI->blockWidth = strlen(pUI->Block);
	pUI->_a = (int *)malloc(sizeof(int)*(pUI->gameHeight)*(pUI->gameWidth));
	memset(pUI->_a, 0, sizeof(int)*(pUI->gameHeight)*(pUI->gameWidth));
	char modeCommand[1024];
	sprintf(modeCommand, "mode con cols=%d lines=%d", pUI->windowWidth, pUI->windowHeight);
	system(modeCommand);

	return pUI;
}

void UIDisplayWizard(const struct UI *pUI)
{
	int i;
	const char *messages[3] = {
		"��ӭ��������˹����С��Ϸ XD",
		"�á���ת�� �����ƶ��������١�",
		"���ٽ��ܵõ����ߵķ�����"
	};

	i = 0;
	_SetPos(pUI->windowWidth / 2 - strlen(messages[i]) / 2, pUI->windowHeight / 2);
	printf("%s\n", messages[i]);
	_SetPos(pUI->windowWidth / 2 - strlen(messages[i]) / 2, pUI->windowHeight / 2 + 2);
	system("pause");
	system("cls");

	i = 1;
	_SetPos(pUI->windowWidth / 2 - strlen(messages[i]) / 2, pUI->windowHeight / 2);
	printf("%s\n", messages[i]);

	i = 2;
	_SetPos(pUI->windowWidth / 2 - strlen(messages[i]) / 2, pUI->windowHeight / 2 + 2);
	printf("%s\n", messages[i]);
	_SetPos(pUI->windowWidth / 2 - strlen(messages[i]) / 2, pUI->windowHeight / 2 + 4);
	system("pause");
	system("cls");
}

void UIDisplayGameWindow(const struct UI *pUI, int score)
{
	_DisplayWall(pUI);
	UIDisplayScore(pUI, score);
	_DisplayDesc(pUI);

	_ResetCursorPosition(pUI);
}
//��ʾͼ�ο�
void UIDisplayBlock(const struct UI *pUI, struct Shape* shape)
{
	//��ͬ��״
	_DisplayShape(pUI, shape);
	_ResetCursorPosition(pUI);
}
//����һ�еĿ�
void UICleanBlockAtY(const struct UI *pUI, int y)
{
	_CoordinatePosAtXY(pUI, 0, y);
	int i;
	for (i = 0; i < pUI->gameWidth; i++) {
		printf("  ");
	}

	_ResetCursorPosition(pUI);
}
//����ͼ�ο�
void UICleanBlock(const struct UI *pUI, struct Shape*shape)
{
	_ClearShape(pUI, shape);
	_ResetCursorPosition(pUI);
}
void UIDisplayScore(const struct UI *pUI, int score)

{
	int blockWidth = strlen(pUI->Block);
	int left = pUI->marginLeft + (pUI->gameWidth + 2) * blockWidth + 2;
	_SetPos(left, pUI->marginTop + 8);
	printf("�÷�: %3d", score);

	_ResetCursorPosition(pUI);
}

void UIDeinitialize(struct UI *pUI)
{
	free(pUI);
}

static void _DisplayWall(const struct UI *pUI)
{
	int left = pUI->marginLeft;
	int top = pUI->marginTop;
	int width = pUI->gameWidth;
	int height = pUI->gameHeight;
	int blockWidth = pUI->blockWidth;
	int i;

	// ��
	_SetPos(left, top);
	for (i = 0; i < width + 2; i++) {
		printf("%s", pUI->Block);
	}

	// ��
	_SetPos(left, top + 1 + height);
	for (i = 0; i < width + 2; i++) {
		printf("%s", pUI->Block);
	}

	// ��
	for (i = 0; i < height + 2; i++) {
		_SetPos(left, top + i);
		printf("%s", pUI->Block);
	}

	// ��
	for (i = 0; i < height + 2; i++) {
		_SetPos(left + (1 + width) * blockWidth, top + i);
		printf("%s", pUI->Block);
	}
}

static void _DisplayDesc(const struct UI *pUI)
{
	int left = pUI->marginLeft + (pUI->gameWidth + 2) * pUI->blockWidth + 2;
	const char *messages[] = {
		"������ת��",
		"�������١�",
		"�� �� �� �ֱ���Ʒ�����ƶ���",
		"ESC �˳���Ϸ, SPACE ��ͣ��Ϸ��",
	};
	int i;

	for (i = 0; i < sizeof(messages) / sizeof(char *); i++) {
		_SetPos(left, pUI->marginTop + 10 + i);
		printf("%s\n", messages[i]);
	}
}

static void _SetPos(int x, int y)
{
	COORD position = { x, y };
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hOutput, position);
}

void _CoordinatePosAtXY(const struct UI *pUI, int x, int y)
{
	_SetPos(pUI->marginLeft + (1 + x) * pUI->blockWidth,
		pUI->marginTop + 1 + y);
}
void _ResetCursorPosition(const struct UI *pUI)
{
	_SetPos(0, pUI->windowHeight - 1);
}
//��ʾһ��
static void  _DisplayY(const struct UI *pUI, int j)
{
	char *s = pUI->Block;
	int i = 0;
	int coust = 0;
	for (; j > 0; j--) {
		for (i = 0; i < pUI->gameWidth; i++)
		{
			int b = pUI->_a[j*pUI->gameWidth + i];
			_CoordinatePosAtXY(pUI, i, j);
			if (b == 0)
			{
				SetColor(7, 0);
				printf("  ");
			}
			else {
				coust = 1;
				SetColor(b, 0);
				printf(pUI->Block);
				SetColor(7, 0);
			}

		}
		if (coust == 0)break;
	}
}
static void  _DisplayShape(const struct UI *pUI, struct Shape*shape)
{
	SetColor(shape->shapetype + 1, 0);
	char *s = pUI->Block;
	int i = 0;
	for (i = 0; i < 4; i++)
	{
		_CoordinatePosAtXY(pUI, shape->postion[i].x, shape->postion[i].y);
		pUI->_a[shape->postion[i].x + shape->postion[i].y*pUI->gameWidth] = shape->shapetype + 1;
		printf(pUI->Block);
	}
	SetColor(7, 0);
}
static void  _ClearShape(const struct UI *pUI, struct Shape *shape)
{
	SetColor(7, 0);
	int i = 0;
	for (i = 0; i < 4; i++)
	{
		pUI->_a[shape->postion[i].x + shape->postion[i].y*pUI->gameWidth] = 0;
		_CoordinatePosAtXY(pUI, shape->postion[i].x, shape->postion[i].y);
		printf("  ");
	}
}
//�ж���Ϸ����
int IsGameOver(const struct UI*pUI)
{
	int x = pUI->gameWidth;
	int i = 0;
	for (i = 0; i < pUI->gameWidth; i++)
	{
		if (pUI->_a[i + x] != 0)
			return 1;
	}
	return 0;
}
//�����û��ͼ���Ƿ��������
int IsRightHaveShape(const int *a, struct Shape *shape, int width)
{
	if (a[shape->postion[3].x + 1 + shape->postion[3].y*width] != 0 ||
		a[shape->postion[2].x + 1 + shape->postion[2].y*width] != 0 ||
		a[shape->postion[1].x + 1 + shape->postion[1].y*width] != 0 ||
		a[shape->postion[0].x + 1 + shape->postion[0].y*width] != 0)
		return 1;
	return 0;
}
//�Ƿ��������
int IsLeftHaveShape(const int *a, struct Shape*shape, int width)
{
	if (a[shape->postion[3].x - 1 + shape->postion[3].y*width] != 0 ||
		a[shape->postion[2].x - 1 + shape->postion[2].y*width] != 0 ||
		a[shape->postion[1].x - 1 + shape->postion[1].y*width] != 0 ||
		a[shape->postion[0].x - 1 + shape->postion[0].y*width] != 0)
		return 1;
	return 0;
}
//�ӷ�������ʾ
int InsertScore(struct UI *pUI)
{
	int i = 0;
	int cur = 0;
	for (i = pUI->gameHeight - 1; i >0; i--)
	{
		int j = 0;
		for (j = 0; j < pUI->gameWidth; j++)
		{
			if (pUI->_a[i*pUI->gameWidth + j] == 0)
				break;
		}
		if (j == pUI->gameWidth)
		{
			cur++;
			UICleanBlockAtY(pUI, i);
			GetDown(i, pUI->_a, pUI->gameWidth);
			_DisplayY(pUI, i);
			i++;
		}
	}
	return cur;
}
void GetDown(int i, int *a, int width)
{
	int j = 0;
	for (j = i; j > 0; j--)
	{
		int m = 0;
		for (m = 0; m < width; m++)
		{
			a[j*width + m] = a[(j - 1)*width + m];
		}
	}
}
