#ifndef __UI_H__
#define __UI_H__

typedef struct pos
{
	int x;
	int y;
}pos;


enum Shapetype
{
	SHAPE1 = 0,
	SHAPE2,
	SHAPE3,
	SHAPE4,
	SHAPE5,
	SHAPE6
};
struct UI {
	// 边缘宽度
	int marginTop;
	int marginLeft;

	// 游戏区域的个数
	int gameWidth;
	int gameHeight;

	// 整个窗口大小宽度
	int windowWidth;
	int windowHeight;

	char *Block;    // 显示块
	int blockWidth;     // 每个块的宽度，注意，上面几个块的宽度要相等，否则就对不齐了
	int *_a;
};
struct Shape
{
	pos* postion;
	enum Shapetype shapetype;
};
// UI 初始化
struct UI * UIInitialize(int width, int height);
void UICleanBlock(const struct UI *pUI, struct Shape*shape);

int InsertScore(struct UI *pUI);
// 显示游戏向导
void UIDisplayWizard(const struct UI *pUI);
// 显示游戏整体，包括墙、右边的信息
void UIDisplayGameWindow(const struct UI *pUI, int score);

void _CoordinatePosAtXY(const struct UI *pUI, int x, int y);

void _ResetCursorPosition(const struct UI *pUI);

void UIDisplayBlock(const struct UI *pUI, struct Shape *shape);
// 清空x，y处的显示块
void UICleanBlockAtY(const struct UI *pUI, int y);
// 显示分数信息
void UIDisplayScore(const struct UI *pUI, int score);
// 销毁 UI 资源
void UIDeinitialize(struct UI *pUI);
int IsGameOver(const struct UI*pUI);
int IsRightHaveShape(const int *a, struct Shape *shape, int width);
int IsLeftHaveShape(const int *a, struct Shape*shape, int width);
#endif

