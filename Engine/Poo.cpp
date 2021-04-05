#include "Poo.h"
#include "Graphics.h"

void Poo::Update()
{
	x += vx;
	y += vy;

	const int right = x + width;

	if (x < 0)
	{
		x = 0;
		vx = -vx;
	}
	else if (right >= Graphics::ScreenWidth)
	{
		x = Graphics::ScreenWidth - width - 1;
		vx = -vx;
	}

	const int bottom = y + height;

	if (y < 0)
	{
		y = 0;
		vy = -vy;
	}
	else if (bottom >= Graphics::ScreenHeight)
	{
		y = Graphics::ScreenHeight - height - 1;
		vy = -vy;
	}

}

void Poo::ProcessConsumption(int dudeX, int dudeY, int dudeWidth, int dudeHeight)
{
	const int dudeRight = dudeX + dudeWidth;
	const int pooRight = x + width;
	const int dudeBottom = dudeY + dudeHeight;
	const int pooBottom = y + height;

	if (dudeRight >= x &&
		dudeX <= pooRight &&
		dudeBottom >= y &&
		dudeY <= pooBottom)
	{
		isEaten = true;
	}
}
