// TSPM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cGame.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include "Project.h"
#include "Catalogue.h"


cGame game;

int search() {
	int offset = 4;
	int selected = 0;
	int projectOffset = 0;
	std::vector<std::string> projects = { "Alpha","Beta","Gamma","Omega","Beta","Gamma","Omega","Beta","Gamma","Omega","Beta","Gamma","Omega","Beta","Jordan","Omega","Beta","Gamma","Omega","Beta","Gamma","Omega","Beta","Gamma","Omega","Beta","Gamma","Omega","Beta","Gamma","Omega","Beta","Gamma","Omega","Beta","Gamma","Omega","Beta","Gamma","Omega" };
	while (!GetAsyncKeyState(VK_ESCAPE)){
		game.blank_screen();
		game.border(2);
		if (game.input() != "") {
			game.stringBuffer += game.input();
			game.drawColor(3, offset + 2 + selected, projects.at(selected + projectOffset).size(), 15);
			selected = 0;
			projectOffset = 0;
		}
		game.print("Search Term: " + game.stringBuffer, 3, offset);
		game.drawColor(3, offset + 2 + selected, projects.at(selected + projectOffset).size(),240);
		for (int i = 0; i < 20; i++) {
			game.print(projects.at(i+projectOffset), 3, offset + i + 2);
		}
		game.print("More Below...", 3, 27);

		if (GetAsyncKeyState(VK_DOWN)) {
			game.drawColor(3, offset + 2 + selected, projects.at(selected+projectOffset).size(), 15);
			selected++;
			if (selected > 19) {
				selected = 19;
				projectOffset++;
			}
			
		}
		if (GetAsyncKeyState(VK_UP)) {
			game.drawColor(3, offset + 2 + selected, projects.at(selected + projectOffset).size(), 15);
			selected--;
			if (selected < 0) {
				selected = 0;
				projectOffset--;
				if (projectOffset < 0)
					projectOffset = 0;
			}
			
		}
		game.draw();
		Sleep(150);
		
	}
	return 5;
}

int menu() {
	int offset = 1;
	int choice = -1;
	game.print("1. Load File",3,3 + offset);
	game.print("2. Create New Project", 3, 4 + offset);
	game.print("3. Update Box Office Figures", 3, 5 + offset);
	game.print("4. Delete Project", 3, 6 + offset);
	game.print("5. Search", 3, 7 + offset);
	game.print("6. Maintenance", 3, 8 + offset);
	game.print("0. Exit", 3, 9 + offset);
	game.print("Please Enter Choice: " + game.stringBuffer, 3, 11 + offset);
	if (GetAsyncKeyState(VK_RETURN)) {
		int temp = std::stoi(game.stringBuffer);
		game.stringBuffer.clear();
		return temp;
	}
	return -1;
}

int main(){
	Project p1(0, "Dumbo", "Big elaphant and mum ded", "2019/04/26", 90, false, false);
	p1.addKeyword("Try not to cry");
	p1.addKeyword("another keyword");
	p1.addFilmingLocation("Home");
	p1.addFilmingLocation("not home");
	p1.addCrewMember("Dumbo", "actor");
	p1.addCrewMember("Dumbo's mum", "dead");
	p1.addGenre("sad");

	Project p2(0, "Dumbo2", "Big elaphant and mum ded 2", "2019/04/27", 90, false, false);
	p2.addKeyword("Try not to cry 2");
	p2.addKeyword("another keyword 2");
	p2.addFilmingLocation("Home 2");
	p2.addFilmingLocation("not home 2");
	p2.addCrewMember("Dumbo", "actor 2");
	p2.addCrewMember("Dumbo's mum 2", "dead 2");
	p2.addGenre("sad 2");

	Catalogue c1;

	c1.add(p1);
	c1.add(p2);

	int screen = 5;
	game.setup();
	game.blank_screen();
	while (true) {
		game.blank_screen();
		game.border(2);
		game.print("Welcome to TSPM",game.screenWidth/2-8,2);
		game.draw_pixel(0, 0, char(screen+48));
		game.stringBuffer += game.input();
		if (GetAsyncKeyState(VK_BACK) && game.stringBuffer.size()>0) {
			game.stringBuffer.pop_back();
		}
		switch (screen) {
		case -1:
			screen = menu();
			break;
		case 0:
			return 0;
		case 1:
			screen = -1;
			break;
		case 2:
			screen = -1;
			break;
		case 3:
			screen = -1;
			break;
		case 4:
			screen = -1;
			break;
		case 5:
			screen = search();
			break;
		case 6:
			screen = -1;
			break;
		default:
			screen = menu();
			game.print("Invalid Choice Please Try Again",3,13);
		}
		game.draw();
		Sleep(150);
	}
	
	
    return 0;
}

