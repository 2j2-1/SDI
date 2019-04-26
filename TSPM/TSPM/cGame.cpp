#include "stdafx.h"
#include "cGame.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h> 
#include <stdio.h>
#include <Windows.h>
#include <string>


void cGame::draw_pixel(int x, int y, char c) {
	if (y >= 0 && y <= screenHeight && x >= 0 && x < screenWidth) {
		//Translate from 2d coordinates to 1d
		screen[y*screenWidth + x] = c;
	}
}

void cGame::blank_screen() {
	//Fill screen with blank pixels
	for (int y = 0; y < this->screenHeight; y++) {
		for (int x = 0; x < screenWidth; x++) {
			draw_pixel(x, y, 32);
		}
	}
}

void cGame::draw() {
	DWORD written;
	WriteConsoleOutputCharacterA(hConsole, screen, screenHeight*screenWidth, { 0,0 }, &written);
}

void cGame::setup() {
	SetConsoleActiveScreenBuffer(hConsole);
	srand(time(NULL));
}

void cGame::print(std::string s, int x, int y) {
	//Draws a string to the screen
	for (int i = 0; i < s.length(); i++)
	{
		draw_pixel(x + i, y, s[i]);
	}
}

std::string cGame::input() {
	std::string str;
	for (int i = 0; i < 26; i++) {
		if (GetAsyncKeyState(0x41 + i)) {
			if (GetAsyncKeyState(0xA0)|| GetAsyncKeyState(0xA1))
				str += 0x41 + i;
			else
				str += 0x61 + i;
		}
	if (GetAsyncKeyState(VK_SPACE)) {
			str += ' ';
		}
	}
	return str;
}

void cGame::border(int num) {
	for (int j = 0; j < num; j++) {
		for (int i = 0; i < screenWidth; i++) {
			draw_pixel(i, j, '#');
			draw_pixel(i, screenHeight - 1 - j, '#');
		}
		for (int i = 0; i < screenHeight; i++) {
			draw_pixel(j, i, '#');
			draw_pixel(screenWidth - 1 - j, i, '#');
		}
	}
}