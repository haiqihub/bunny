#include"game.h"
#include<time.h>

int main()
{
	srand((unsigned int)time(NULL));
	struct Game* game;
	game = CreateGame();
	StartGame(game);
	system("pause");
}
