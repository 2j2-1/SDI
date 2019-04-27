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
Catalogue c1;
Project selectedProject;
void printMetaData(Project current) {

}

void printSearch(std::vector<std::string> projects, int offsetY, int selected, int projectOffset) {
	game.print("Search Term: " + game.stringBuffer, 3, offsetY - 1);
	if (projects.size() > 0) {
		game.drawColor(3, offsetY + 2 + selected, projects.at(selected + projectOffset).size(), 240);
		for (int i = 0; i < min(20, projects.size()); i++) {
			game.print(projects.at(i + projectOffset), 3, offsetY + i + 2);
		}
		if (projects.size()>20)
			game.print("More Below...", 3, 27);
	}
	else
		game.drawColor(3, offsetY + 2 + selected, 20, 15);
}
int search() {
	int offsetY = 4;
	int offsetX = 20;
	int selected = 0;
	int projectOffset = 0;
	std::vector<Project> allProjects = c1.sortByTitle(c1.searchByProjectTitle(c1.projects, ""));
	std::vector<std::string> projects;
	int metaDataSize;
	for (int i = 0; i < allProjects.size(); i++){
		projects.push_back(allProjects[i].title);
	}
	while (!GetAsyncKeyState(VK_ESCAPE)){
		game.blank_screen();
		if (game.input() != "") {
			game.stringBuffer += game.input();
			game.drawColor(3, offsetY + 2 + selected, projects.at(selected + projectOffset).size(), 15);
			selected = 0;
			projectOffset = 0;
		}
		
		printSearch(projects, offsetY, selected, projectOffset);

		printSearch(projects, offsetY, selected, projectOffset);

		if (GetAsyncKeyState(VK_DOWN)) {
			game.drawColor(3, offsetY + 2 + selected, projects.at(selected + projectOffset).size(), 15);
			selected++;
			if (selected > min(19, projects.size() - 1)) {
				selected = min(19, projects.size() - 1);
				projectOffset++;
			}
		}
		if (GetAsyncKeyState(VK_UP)) {
			game.drawColor(3, offsetY + 2 + selected, projects.at(selected + projectOffset).size(), 15);
			selected--;
			if (selected < 0) {
				selected = 0;
				projectOffset--;
				if (projectOffset < 0)
					projectOffset = 0;
			}
		}
		if (GetAsyncKeyState(VK_BACK)) {
			if (game.stringBuffer.size()>0)
				game.stringBuffer.pop_back();
		}
		if (GetAsyncKeyState(VK_TAB)) {
			allProjects = c1.sortByTitle(c1.searchByProjectTitle(c1.projects, game.stringBuffer));
			projects.clear();
			for (int i = 0; i < allProjects.size(); i++) {
				projects.push_back(allProjects[i].title);
			}
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			selectedProject = allProjects.at(selected);
			break;
		}
		game.draw();
		Sleep(50);
		
	}
	game.drawColor(3, offsetY + 2 + selected, projects.at(selected + projectOffset).size(), 15);
	return -1;
}

int menu() {
	int offset = 1;
	int choice = -1;
	game.print("1. Load File",3,3 + offset);
	game.print("2. Create New Project", 3, 4 + offset);
	game.print("3. View/Update File", 3, 5 + offset);
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

int update() {
	int xoff = 3;
	int yoff = 3;
	int dataoff = 20;
	while (true) {
		yoff = 3;
		game.blank_screen();
		game.print("Title: ", xoff, yoff);
		game.print(selectedProject.title, xoff + dataoff, yoff);
		yoff++;

		game.print("Summary: ", xoff, yoff);
		game.print(selectedProject.summary, xoff + dataoff, yoff);
		yoff++;

		game.print("Release Date: ", xoff, yoff);
		game.print(selectedProject.releaseDate, xoff + dataoff, yoff);
		yoff++;

		game.print("Run Time: ", xoff, yoff);
		game.print(std::to_string(selectedProject.runtime), xoff + dataoff, yoff);
		yoff++;

		game.print("Playing In Cinima: ", xoff, yoff);
		if (selectedProject.playingInCinima)
			game.print("True", xoff + dataoff, yoff);
		else
			game.print("False", xoff + dataoff, yoff);
		yoff++;

		game.print("unreleased: ", xoff, yoff);
		if (selectedProject.unreleased)
			game.print("True", xoff + dataoff, yoff);
		else
			game.print("False", xoff + dataoff, yoff);
		yoff++;

		game.print("weeklySales: ", xoff, yoff);
		game.print(std::to_string(selectedProject.weeklySales), xoff + dataoff, yoff);
		yoff++;

		game.print("genres: ", xoff, yoff);
		for (int i = 0; i < selectedProject.genres.size(); i++){
			game.print(selectedProject.genres.at(i), xoff + dataoff, yoff);
			yoff++;
		}
		
		game.print("filmingLocations: ", xoff, yoff);
		for (int i = 0; i < selectedProject.filmingLocations.size(); i++) {
			game.print(selectedProject.filmingLocations.at(i), xoff + dataoff, yoff);
			yoff++;
		}

		game.print("keywords: ", xoff, yoff);
		for (int i = 0; i < selectedProject.keywords.size(); i++) {
			game.print(selectedProject.keywords.at(i), xoff + dataoff, yoff);
			yoff++;
		}

		game.print("crewMembers: ", xoff, yoff);
		for (int i = 0; i < selectedProject.crewMembers.size(); i++) {
			game.print(selectedProject.crewMembers.at(i).role + " - " + selectedProject.crewMembers.at(i).name, xoff + dataoff, yoff);
			yoff++;
		}

		game.print("physcicalMeduims: ", xoff, yoff);
		

		game.draw();
	}
	return -1;
}

int main(){
	/*Project p1(0, "Dumbo", "Ridiculed because of his enormous ears, a young circus elephant is assisted by a mouse to achieve his full potential.", "1942/01/02", 64, false, false);
	p1.addKeyword("Try not to cry");
	p1.addKeyword("another keyword");
	p1.addFilmingLocation("Home");
	p1.addFilmingLocation("not home");
	p1.addCrewMember("Dumbo", "actor");
	p1.addCrewMember("Dumbo", "producer");
	p1.addCrewMember("Dumbo", "director");
	p1.addCrewMember("Dumbo", "camera man");
	p1.addCrewMember("Dumbo", "writer");
	p1.addCrewMember("Dumbo's mum", "dead");
	p1.addGenre("sad");

	Project p2(1, "Jumbz", "Big elaphant and mum ded 2", "2019/04/27", 90, false, false);
	p2.addKeyword("Try not to cry 2");
	p2.addKeyword("another keyword 2");
	p2.addFilmingLocation("Home 2");
	p2.addFilmingLocation("not home 2");
	p2.addCrewMember("Dumbo", "actor 2");
	p2.addCrewMember("Dumbo's mum 2", "dead 2");
	p2.addGenre("sad 2");

	Project p3(2, "Jumbo", "Big elaphant and mum ded 2", "2019/04/27", 90, false, false);
	p3.addKeyword("Try not to cry 2");
	p3.addKeyword("another keyword 2");
	p3.addFilmingLocation("Home 2");
	p3.addFilmingLocation("not home 2");
	p3.addCrewMember("Dumbo", "actor 2");
	p3.addCrewMember("Dumbo's mum 2", "dead 2");
	p3.addGenre("sad 2");

	

	c1.add(p1);
	c1.add(p2);
	c1.add(p3);


	c1.write();*/
	c1.read();


	int screen = -1;
	game.setup();
	game.blank_screen();
	while (true) {
		game.blank_screen();
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
			//if (selectedProject.projectID != -1)
				screen = update();
			//else
				//screen = -1;
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
	}
	
	
    return 0;
}

