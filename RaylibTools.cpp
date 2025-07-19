#include "RaylibTools.h"

bool RaylibTools::isSetRand = false; // is if set seed
Color RaylibTools::colorCircleLine = WHITE; // Default color is white
Color RaylibTools::colorLine = WHITE; // Default color is white
int RaylibTools::sizeLine = 1; // Default size is 1
int RaylibTools::lengthLine  = 1; // Default length is 1


int RaylibTools::Random(int min, int max)
{
	if (!isSetRand)
	{
		srand(static_cast<unsigned int>(time(NULL)));
		isSetRand = true;
	}
	if (min > max)
	{
		min = max + min;
		max = min - max;
		min = min - max;
	}
	return rand() % (max - min + 1) + min;
}

Color RaylibTools::RandomColor()
{
	unsigned char r = Random(0, 255);
	unsigned char g = Random(0, 255);
	unsigned char b = Random(0, 255);
	return Color{ r, g, b, 255 };
}

Color RaylibTools::RandomColorAlpha(int minAlpha, int maxAlpha)
{
	Color color = RandomColor();
	unsigned char a = Random(minAlpha, maxAlpha);
	color.a = a;
	return color;
}

Color RaylibTools::RandomColourless(int min, int max)
{
	unsigned char all = Random(min, max);
	Color color = { all, all, all, 255 };
	return color;
}

Color RaylibTools::RandomColourlessAlpha(int minAlpha, int maxAlpha, int min, int max)
{
	Color color = RandomColourless(min, max);
	color.a = Random(minAlpha, maxAlpha);
	return color;
}

void RaylibTools::SetColor(Color color) // Set the default color
{
	colorCircleLine = color; // Set circle line color
	RaylibTools::colorLine = color; // Set line color
}

void RaylibTools::DrawLine(int startX, int startY, int endX, int endY, int size, Color color)
{
	colorLine = color; // Set line color
	sizeLine = size; // Set line size
	DrawLineEx(Vector2{ static_cast<float>(startX), static_cast<float>(startY) },
		Vector2{ static_cast<float>(endX), static_cast<float>(endY) }, static_cast<float>(size), color);
}

void RaylibTools::DrawLine(int startX, int startY, int endX, int endY, int size)
{
	RaylibTools::DrawLine(startX, startY, endX, endY, size, colorLine);
}

void RaylibTools::DrawLine(int startX, int startY, int endX, int endY)
{
	RaylibTools::DrawLine(startX, startY, endX, endY, sizeLine, colorLine);
}

void RaylibTools::DrawLineAngle(int startX, int startY, float angle, int length, int size, Color color)
{
	colorLine = color; // Set line color
	lengthLine = length; // Set line length
	sizeLine = size; // Set line size
	float endX = startX + length * cos(angle * PI / 180.0f);
	float endY = startY + length * sin(angle * PI / 180.0f);
	RaylibTools::DrawLine(startX, startY, static_cast<int>(endX), static_cast<int>(endY), size, color);
}

void RaylibTools::DrawLineAngle(int startX, int startY, float angle, int length, int size)
{
	RaylibTools::DrawLineAngle(startX, startY, angle, length, size, colorLine);
}

void RaylibTools::DrawLineAngle(int startX, int startY, float angle)
{
	RaylibTools::DrawLineAngle(startX, startY, angle, lengthLine, sizeLine, colorLine);
}

void RaylibTools::DrawCircleLine(int centerX, int centerY, float radius, int size, Color color)
{
	colorCircleLine = color; // Set circle line color
	DrawRing(Vector2{ static_cast<float>(centerX), static_cast<float>(centerY) },
		radius - size / 2.0f, radius + size / 2.0f, 0.0f, 360.0f, static_cast<int>(radius * 0.4f) + 4, color);
}

void RaylibTools::DrawCircleLine(int centerX, int centerY, float radius, int size)
{
	RaylibTools::DrawCircleLine(centerX, centerY, radius, size, colorCircleLine);
}

void RaylibTools::DrawTexture(Texture2D texture, float x, float y, float percent)
{
	float tw = static_cast<float>(texture.width) * percent; // now width of texture
	float th = static_cast<float>(texture.height) * percent; // now height of texture
	DrawTexturePro(texture, Rectangle{ 0, 0, tw, th }, Rectangle{ x, y, tw, th }, Vector2{ 0, 0 }, 0, WHITE);
}