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
int printMetaData(Project current, int offsetY, int selected, int projectOffset, int offsetX,int mode) {


	std::vector<std::vector<std::string>> metaData;
	std::vector<std::string> tempMetaData;
	int lenOfSummary = 110;

	std::vector<std::string> titleMetaData;
	titleMetaData.push_back("Title: ");
	titleMetaData.push_back(current.title);
	metaData.push_back(titleMetaData);

	std::vector<std::string> summaryMetaData;
	summaryMetaData.push_back("Summary: ");
	for (int i = 0; i < current.summary.size() / lenOfSummary + 1; i++) {
		summaryMetaData.push_back(current.summary.substr(i*lenOfSummary, (i + 1)*lenOfSummary));
	}
	metaData.push_back(summaryMetaData);

	std::vector<std::string> genreMetaData;
	genreMetaData.push_back("Genre: ");
	for (int i = 0; i < current.genres.size(); i++) {
		genreMetaData.push_back(current.genres[i]);
	}
	metaData.push_back(genreMetaData);
	

	std::vector<std::string> rdMetaData;
	rdMetaData.push_back("Release Date: ");
	rdMetaData.push_back(current.releaseDate);
	metaData.push_back(rdMetaData);
	

	std::vector<std::string> flMetaData;
	flMetaData.push_back("Filming Locations: ");
	for (int i = 0; i < current.filmingLocations.size(); i++) {
		flMetaData.push_back(current.filmingLocations[i]);
	}
	metaData.push_back(flMetaData);
	

	std::vector<std::string> runtimeMetaData;
	runtimeMetaData.push_back("Runtime: ");
	runtimeMetaData.push_back(std::to_string(current.runtime) + " Minutes");
	metaData.push_back(runtimeMetaData);
	

	std::vector<std::string> keywordsMetaData;
	keywordsMetaData.push_back("Keywords: ");
	for (int i = 0; i < current.keywords.size(); i++) {
		keywordsMetaData.push_back(current.keywords[i]);
	}
	metaData.push_back(keywordsMetaData);
	

	std::vector<std::string> cmMetaData;
	cmMetaData.push_back("Crew Members: ");
	for (int i = 0; i < current.crewMembers.size(); i++) {
		cmMetaData.push_back(current.crewMembers[i].role + " " + current.crewMembers[i].name);
	}
	metaData.push_back(cmMetaData);
	

	std::vector<std::string> rsMetaData;
	if (current.playingInCinima)
		rsMetaData.push_back("Currently Playing In Cinemas  ");
	else if (current.unreleased)
		rsMetaData.push_back("Currently Unrealeased  ");
	else
		rsMetaData.push_back("This Project Has Been Realeased  ");
	metaData.push_back(rsMetaData);
	

	
	int lineCount = 0;
	for (int i = selected; i < metaData.size(); i++) {
		if(i==selected && mode != 0)
			game.drawColor(3, offsetY  + lineCount, metaData.at(selected + projectOffset)[0].size() - 2, 240);
		game.print(metaData[i][0], offsetX, offsetY + i + lineCount - selected);
		if (metaData[i].size() == 2) {
			game.print(metaData[i][1], offsetX + metaData[i][0].size(), offsetY + i + lineCount - selected);
		}
		else {
			for (int j = 1; j < metaData[i].size(); j++){
				lineCount++;
				game.print(metaData[i][j], offsetX, offsetY + i + lineCount - selected);
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
			printMetaData(current, offsetY, selected, projectOffset, offsetX,mode);
		}
		else {
			metaDataSize = printMetaData(current, offsetY-2, selected, projectOffset, 3,mode);
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
		if (GetAsyncKeyState(VK_TAB)) {
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

	//c1.write();
	c1.read();


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

