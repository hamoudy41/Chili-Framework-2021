/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
	void GameBox(int x, int y, int r, int g, int b);
	bool OverlapTest(int box0x, int box0y, int box1x, int box1y);
	int ClampScreenX(int x);
	int ClampScreenY(int y);

private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	/********************************/
	int x_mobile = 550;
	int y_mobile = 450;

	int x_fixed0 = 100;
	int y_fixed0 = 300;
	int x_fixed1 = 200;
	int y_fixed1 = 300;
	int x_fixed2 = 300;
	int y_fixed2 = 300;
	int x_fixed3 = 400;
	int y_fixed3 = 300;

	int r_mobile = 255;
	int g_mobile = 255;
	int b_mobile = 255;
	int vx = 0;
	int vy = 0;
	int displacement = 3;

	bool shapeIsChanged = false;
	bool inhibitUp = false;
	bool inhibitDown = false;
	bool inhibitRight = false;
	bool inhibitLeft = false;
	bool collided = false;

	bool colorIsChanged = false;
	bool leftIsPressed = false;
	bool rightIsPressed = false;
	bool upIsPressed = false;
	bool downIsPressed = false;

};