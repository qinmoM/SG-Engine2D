#include "RaylibTools.h"

Color RaylibTools::colorCircleLine = WHITE; // Ĭ�ϰ�ɫ

void RaylibTools::SetColor(Color color) // ����ȫ����ɫ
{
	RaylibTools::colorCircleLine = color; // Բ����ɫ
}

void RaylibTools::DrawCircleLine(int centerX, int centerY, float radius, int size, Color color)
{
	RaylibTools::colorCircleLine = color; // ����Ĭ����ɫ
	DrawRing(Vector2{ static_cast<float>(centerX), static_cast<float>(centerY) },
		radius - size / 2.0f, radius + size / 2.0f, 0.0f, 360.0f, static_cast<int>(radius * 0.35f) + 1, color);
}

void RaylibTools::DrawCircleLine(int centerX, int centerY, float radius, int size)
{
	RaylibTools::DrawCircleLine(centerX, centerY, radius, size, RaylibTools::colorCircleLine);
}

void RaylibTools::DrawTexture(Texture2D texture, float x, float y, float percent)
{
	float tw = static_cast<float>(texture.width) * percent; // ������������
	float th = static_cast<float>(texture.height) * percent; // ���������߶�
	DrawTexturePro(texture, Rectangle{ 0, 0, tw, th }, Rectangle{ x, y, tw, th }, Vector2{ 0, 0 }, 0, WHITE);
}