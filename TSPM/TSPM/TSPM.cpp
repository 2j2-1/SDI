// TSPM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cGame.h"
#include <iostream>
#include <Windows.h>
#include <string>

cGame game;

int search() {
	if (GetAsyncKeyState(VK_BACK)) {
		return -1;
	}
	return 5;
}

int menu(std::string str) {
	int offset = 1;
	int choice = -1;
	game.print("1. Load File",3,3 + offset);
	game.print("2. Create New Project", 3, 4 + offset);
	game.print("3. Update Box Office Figures", 3, 5 + offset);
	game.print("4. Delete Project", 3, 6 + offset);
	game.print("5. Search", 3, 7 + offset);
	game.print("6. Maintenance", 3, 8 + offset);
	game.print("0. Exit", 3, 9 + offset);
	game.print("Please Enter Choice: " + str, 3, 11 + offset);
	if (GetAsyncKeyState(VK_RETURN)) {
		return std::stoi(str);
	}
	return -1;
}

int main(){
	int screen = -1;
	std::string str;
	game.setup();
	game.blank_screen();
	while (true) {
		game.blank_screen();
		game.border(2);
		game.print("Welcome to TSPM",game.screenWidth/2-8,2);
		game.draw_pixel(0, 0, char(screen+48));
		str += game.input();
		if (GetAsyncKeyState(VK_BACK) && str.size()>0) {
			str.pop_back();
		}
		switch (screen) {
		case -1:
			screen = menu(str);
			break;
		case 0:
			return 0;
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:
			screen = search();
			break;
		case 6:

			break;
		default:
			screen = menu(str);
			game.print("Invalid Choice Please Try Agan",3,13);
		}
		game.draw();
		Sleep(150);
	}
	
	
    return 0;
}

