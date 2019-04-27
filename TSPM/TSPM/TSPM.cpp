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
int printMetaData(Project current, int offsetY, int selected, int projectOffset, int offsetX,int materialOffset,int mode) {


	std::vector<std::vector<std::string>> metaData;
	std::vector<std::string> tempMetaData;
	int lenOfSummary = 110;

	tempMetaData.push_back("Title: ");
	tempMetaData.push_back(current.title);
	metaData.push_back(tempMetaData);
	tempMetaData.clear();

	tempMetaData.push_back("Summary: ");
	for (int i = 0; i < current.summary.size() / lenOfSummary + 1; i++) {
		tempMetaData.push_back(current.summary.substr(i*lenOfSummary, (i + 1)*lenOfSummary));
	}
	metaData.push_back(tempMetaData);
	tempMetaData.clear();

	tempMetaData.push_back("Genre: ");
	for (int i = 0; i < current.genres.size(); i++) {
		tempMetaData.push_back(current.genres[i]);
	}
	metaData.push_back(tempMetaData);
	tempMetaData.clear();

	tempMetaData.push_back("Release Date: ");
	tempMetaData.push_back(current.releaseDate);
	metaData.push_back(tempMetaData);
	tempMetaData.clear();

	tempMetaData.push_back("Filming Locations: ");
	for (int i = 0; i < current.filmingLocations.size(); i++) {
		tempMetaData.push_back(current.filmingLocations[i]);
	}
	metaData.push_back(tempMetaData);
	tempMetaData.clear();

	tempMetaData.push_back("Runtime: ");
	tempMetaData.push_back(std::to_string(current.runtime) + " Minutes");
	metaData.push_back(tempMetaData);
	tempMetaData.clear();

	tempMetaData.push_back("Keywords: ");
	for (int i = 0; i < current.keywords.size(); i++) {
		tempMetaData.push_back(current.keywords[i]);
	}
	metaData.push_back(tempMetaData);
	tempMetaData.clear();

	tempMetaData.push_back("Crew Members: ");
	for (int i = 0; i < current.crewMembers.size(); i++) {
		tempMetaData.push_back(current.crewMembers[i].role + " " + current.crewMembers[i].name);
	}
	metaData.push_back(tempMetaData);
	tempMetaData.clear();

	if (current.playingInCinima)
		tempMetaData.push_back("Currently Playing In Cinemas  ");
	else if (current.unreleased)
		tempMetaData.push_back("Currently Unrealeased  ");
	else
		tempMetaData.push_back("This Project Has Been Realeased  ");
	metaData.push_back(tempMetaData);
	tempMetaData.clear();

	
	int lineCount = 0;
	for (int i = materialOffset; i < metaData.size(); i++) {
		if(i==selected && mode != 0)
			game.drawColor(3, offsetY + selected + lineCount, metaData.at(selected + projectOffset)[0].size() - 2, 240);

		game.print(metaData[i][0], offsetX, offsetY + i +lineCount - materialOffset);
		
		if (metaData[i].size() == 2) {
			game.print(metaData[i][1], offsetX + metaData[i][0].size(), offsetY + i + lineCount - materialOffset);
		}
		else {
			
			for (int j = 1; j < metaData[i].size(); j++){
				lineCount++;
				game.print(metaData[i][j], offsetX, offsetY + i + lineCount - materialOffset);
				
			}
		}
		lineCount++;
		
	}
		

	return metaData.size();
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
	int mode = 0;
	int materialOffset = 0;
	std::vector<Project> allProjects = c1.sortByTitle(c1.searchByProjectTitle(c1.projects, ""));
	std::vector<std::string> projects;
	Project current = c1.projects.at(selected + projectOffset);
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
		
		if (mode == 0) {
			printSearch(projects, offsetY, selected, projectOffset);
			current = c1.projects.at(selected + projectOffset);
			printMetaData(current, offsetY, selected, projectOffset, offsetX, 0,mode);
		}
		else {
			metaDataSize = printMetaData(current, offsetY-2, selected, projectOffset, 3, materialOffset,mode);
		}

		

		if (GetAsyncKeyState(VK_DOWN)) {
			if (mode == 0) {
				game.drawColor(3, offsetY + 2 + selected, projects.at(selected + projectOffset).size(), 15);
				selected++;
				if (selected > min(19, projects.size() - 1)) {
					selected = min(19, projects.size() - 1);
					projectOffset++;
				}
			}
			else {
				if (selected>20)
					materialOffset++;
				selected++;
				selected = min(selected, metaDataSize-1);
			}
		}
		if (GetAsyncKeyState(VK_UP)) {
			if (mode == 0) {
				game.drawColor(3, offsetY + 2 + selected, projects.at(selected + projectOffset).size(), 15);
				selected--;
				if (selected < 0) {
					selected = 0;
					projectOffset--;
					if (projectOffset < 0)
						projectOffset = 0;
				}
			} else {
				materialOffset--;
				materialOffset = max(materialOffset, 0);
				selected--;
				selected = max(selected, 0);
			}
			
			
		}
		if (GetAsyncKeyState(VK_BACK)) {
			if (game.stringBuffer.size()>0)
				game.stringBuffer.pop_back();
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			allProjects = c1.sortByTitle(c1.searchByProjectTitle(c1.projects, game.stringBuffer));
			projects.clear();
			for (int i = 0; i < allProjects.size(); i++) {
				projects.push_back(allProjects[i].title);
			}
		}
		if (GetAsyncKeyState(0x53)) {
			game.stringBuffer.pop_back();
			mode = 1;
			game.drawColor(3, offsetY + 2 + selected, projects.at(selected + projectOffset).size(), 15);
		}
		game.draw();
		Sleep(150);
		
	}
	game.drawColor(3, offsetY + 2 + selected, projects.at(selected + projectOffset).size(), 15);
	return -1;
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
	Project p1(0, "Dumbo", "Ridiculed because of his enormous ears, a young circus elephant is assisted by a mouse to achieve his full potential.", "1942/01/02", 64, false, false);
	p1.addKeyword("Try not to cry");
	p1.addKeyword("another keyword");
	p1.addFilmingLocation("Home");
	p1.addFilmingLocation("not home");
	p1.addCrewMember("Dumbo", "actor");
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

	c1.write();
	//c1.read();


	int screen = 5;
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

