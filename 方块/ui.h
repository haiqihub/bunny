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
	// ��Ե���
	int marginTop;
	int marginLeft;

	// ��Ϸ����ĸ���
	int gameWidth;
	int gameHeight;

	// �������ڴ�С���
	int windowWidth;
	int windowHeight;

	char *Block;    // ��ʾ��
	int blockWidth;     // ÿ����Ŀ�ȣ�ע�⣬���漸����Ŀ��Ҫ��ȣ�����ͶԲ�����
	int *_a;
};
struct Shape
{
	pos* postion;
	enum Shapetype shapetype;
};
// UI ��ʼ��
struct UI * UIInitialize(int width, int height);
void UICleanBlock(const struct UI *pUI, struct Shape*shape);

int InsertScore(struct UI *pUI);
// ��ʾ��Ϸ��
void UIDisplayWizard(const struct UI *pUI);
// ��ʾ��Ϸ���壬����ǽ���ұߵ���Ϣ
void UIDisplayGameWindow(const struct UI *pUI, int score);

void _CoordinatePosAtXY(const struct UI *pUI, int x, int y);

void _ResetCursorPosition(const struct UI *pUI);

void UIDisplayBlock(const struct UI *pUI, struct Shape *shape);
// ���x��y������ʾ��
void UICleanBlockAtY(const struct UI *pUI, int y);
// ��ʾ������Ϣ
void UIDisplayScore(const struct UI *pUI, int score);
// ���� UI ��Դ
void UIDeinitialize(struct UI *pUI);
int IsGameOver(const struct UI*pUI);
int IsRightHaveShape(const int *a, struct Shape *shape, int width);
int IsLeftHaveShape(const int *a, struct Shape*shape, int width);
#endif

