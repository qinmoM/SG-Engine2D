#ifndef __RAYLIBTOOLS_HPP__
#define __RAYLIBTOOLS_HPP__

#include <raylib.h>

class RaylibTools
{
public:
	// Ĭ��Բ����ɫ
	static Color colorCircleLine;
public:
	// ����ȫ����ɫ// color: ȫ����ɫ
	static void SetColor(Color color);

	// ����һ��Բ��// centerX, centerY: Բ��x,y���� radius: Բ���뾶 size: Բ���������� color: Բ����ɫ
	static void DrawCircleLine(int centerX, int centerY, float radius, int size, Color color);
	// ������ͬ��ɫԲ��// centerX, centerY: Բ��x,y���� radius: Բ���뾶 size: Բ����������
	static void DrawCircleLine(int centerX, int centerY, float radius, int size);

	// ��������ͼ��// texture: �������� x, y: ����λ�� percent: ���ű���
	static void DrawTexture(Texture2D texture, float x, float y, float percent);
};

#endif // __RAYLIBTOOLS_HPP__