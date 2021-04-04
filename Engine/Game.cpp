/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	shapeIsChanged = wnd.kbd.KeyIsPressed(VK_SHIFT);
	colorIsChanged = wnd.kbd.KeyIsPressed(VK_CONTROL); 
	leftIsPressed = wnd.kbd.KeyIsPressed(VK_LEFT);
	rightIsPressed = wnd.kbd.KeyIsPressed(VK_RIGHT);
	upIsPressed = wnd.kbd.KeyIsPressed(VK_UP);
	downIsPressed = wnd.kbd.KeyIsPressed(VK_DOWN);

	if (rightIsPressed)
	{
		if (!inhibitRight)
		{
			x_mobile = x_mobile + displacement;
			vx = vx + 1;
			inhibitRight = true;
		}
			
	}
	else
	{
		inhibitRight = false;
	}

	if (leftIsPressed)
	{
		if (!inhibitLeft)
		{
			x_mobile = x_mobile - displacement;
			vx = vx - 1;
			inhibitLeft = true;
		}

	}
	else
	{
		inhibitLeft = false;
	}

	if (downIsPressed)
	{
		if (!inhibitDown)
		{
			y_mobile = y_mobile + displacement;
			vy = vy + 1;
			inhibitDown = true;
		}

	}
	else
	{
		inhibitDown = false;
	}

	if (upIsPressed)
	{
		if (!inhibitUp)
		{
			y_mobile = y_mobile - displacement;
			vy = vy - 1;
			inhibitUp = true;
		}

	}
	else
	{
		inhibitUp = false;
	}


	x_mobile = ClampScreenX(x_mobile);
	y_mobile = ClampScreenY(y_mobile);

	collided =
		OverlapTest(x_fixed0, y_fixed0, x_mobile, y_mobile) ||
		OverlapTest(x_fixed1, y_fixed1, x_mobile, y_mobile) ||
		OverlapTest(x_fixed2, y_fixed2, x_mobile, y_mobile) ||
		OverlapTest(x_fixed3, y_fixed3, x_mobile, y_mobile);
}

void Game::ComposeFrame()
{
	GameBox(x_fixed0, y_fixed0, 0, 255, 0);
	GameBox(x_fixed1, y_fixed1, 0, 255, 0);
	GameBox(x_fixed2, y_fixed2, 0, 255, 0);
	GameBox(x_fixed3, y_fixed3, 0, 255, 0);

	if (collided)
	{
		GameBox(x_mobile, y_mobile, 255, 0, 0);
	}
	else
	{
		GameBox(x_mobile, y_mobile, 255, 255, 255);
	}
}

void Game::GameBox(int x, int y, int r, int g, int b)
{
	gfx.PutPixel(-5 + x, -5 + y, r, g, b);
	gfx.PutPixel(-5 + x, -4 + y, r, g, b);
	gfx.PutPixel(-5 + x, -3 + y, r, g, b);
	gfx.PutPixel(-4 + x, -5 + y, r, g, b);
	gfx.PutPixel(-3 + x, -5 + y, r, g, b);
	gfx.PutPixel(-5 + x, 5 + y, r, g, b);
	gfx.PutPixel(-5 + x, 4 + y, r, g, b);
	gfx.PutPixel(-5 + x, 3 + y, r, g, b);
	gfx.PutPixel(-4 + x, 5 + y, r, g, b);
	gfx.PutPixel(-3 + x, 5 + y, r, g, b);
	gfx.PutPixel(5 + x, -5 + y, r, g, b);
	gfx.PutPixel(5 + x, -4 + y, r, g, b);
	gfx.PutPixel(5 + x, -3 + y, r, g, b);
	gfx.PutPixel(4 + x, -5 + y, r, g, b);
	gfx.PutPixel(3 + x, -5 + y, r, g, b);
	gfx.PutPixel(5 + x, 5 + y, r, g, b);
	gfx.PutPixel(5 + x, 4 + y, r, g, b);
	gfx.PutPixel(5 + x, 3 + y, r, g, b);
	gfx.PutPixel(4 + x, 5 + y, r, g, b);
	gfx.PutPixel(3 + x, 5 + y, r, g, b);
}

bool Game::OverlapTest(int box0x, int box0y, int box1x, int box1y)
{
	const int left_mobile = box0x - 5;
	const int right_mobile = box0x + 5;
	const int top_mobile = box0y - 5;
	const int bottom_mobile = box0y + 5;

	const int left_fixed = box1x - 5;
	const int right_fixed = box1x + 5;
	const int top_fixed = box1y - 5;
	const int bottom_fixed = box1y + 5;

	return 
		(left_mobile <= right_fixed &&
		right_mobile >= left_fixed &&
		top_mobile <= bottom_fixed &&
		bottom_mobile >= top_fixed);
}

int Game::ClampScreenX(int x)
{
	const int left = x - 5;
	const int right = x + 5;

	if (right >= gfx.ScreenWidth)
	{
		return gfx.ScreenWidth - 6;
	}
	if (left < 0)
	{
		return 5;
	}
	else
	{
		return x;
	}
}

int Game::ClampScreenY(int y)
{
	const int top = y - 5;
	const int bottom = y + 5;

	if (bottom >= gfx.ScreenWidth)
	{
		return gfx.ScreenWidth - 6;
	}
	if (top < 0)
	{
		return 5;
	}
	else
	{
		return y;
	}
}
