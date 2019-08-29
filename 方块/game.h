#pragma once
#ifndef GAME
#define GAME
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include"UI.h"

enum Status
{
	QUIT,
	OVER,
	GOOD
};
enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};


struct Game
{
	int width;
	int height;
	int score;
	enum Direction direction;
	enum Status status;
	struct Shape *shape;
	int sleeptime;
	int twist;
};
struct Game *CreateGame();
void StartGame(struct Game *pGame);
void DestoryGame(struct Game *pGame);
#endif // !Game
