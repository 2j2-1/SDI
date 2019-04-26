// TSPM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cGame.h"
#include <iostream>
#include <Windows.h>
#include <string>

cGame game;



void menu(std::string str) {
	
}

int main(){
	std::string str;
	game.setup();
	game.blank_screen();
	while (true) {
		game.blank_screen();
		game.border(2);
		str += game.input();
		if (GetAsyncKeyState(VK_BACK) && str.size()>0) {
			str.pop_back();
		}
		menu(str);
		
		game.draw();
		Sleep(150);
	}
	
	
    return 0;
}

