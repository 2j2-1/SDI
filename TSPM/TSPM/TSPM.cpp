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

int search() {
	int offsetY = 4;
	int offsetX = 20;
	int selected = 0;
	int projectOffset = 0;
	std::vector<Project> allProjects = c1.sortByTitle(c1.searchByProjectTitle(c1.projects, ""));
	std::vector<std::string> projects;
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
		game.print("Search Term: " + game.stringBuffer, 3, offsetY-1);
		game.drawColor(3, offsetY + 2 + selected, projects.at(selected + projectOffset).size(),240);
		for (int i = 0; i < min(20,projects.size()); i++) {
			game.print(projects.at(i+projectOffset), 3, offsetY + i + 2);
		}
		game.print("More Below...", 3, 27);

		Project current = c1.projects.at(selected+projectOffset);

		std::vector<std::string> metaData;
		metaData.push_back("Title: " + current.title);
		metaData.push_back("Summary: ");
		int lenOfSummary = 95;
		int nextline = 0;
		for (int i = 0; i < current.summary.size()/ lenOfSummary+1; i++){
			metaData.push_back(current.summary.substr(i*lenOfSummary,(i+1)*lenOfSummary));
		}
		metaData.push_back("Genre: " + current.genres[0]);
		for (int i = 1; i < current.genres.size(); i++) {
			metaData.push_back(current.genres[i]);
		}
		metaData.push_back("Release Date: " + current.releaseDate);
		metaData.push_back("Filming Locations: " + current.filmingLocations[0]);
		for (int i = 1; i < current.filmingLocations.size(); i++){
			metaData.push_back(current.filmingLocations[i]);
		}
		metaData.push_back("Runtime: " + std::to_string(current.runtime) + " Minutes");
		metaData.push_back("Keywords: " + current.keywords[0]);
		for (int i = 1; i < current.keywords.size(); i++) {
			metaData.push_back(current.keywords[i]);
		}
		
		metaData.push_back("Crew Members: ");
		for (int i = 0; i < current.crewMembers.size(); i++) {
			metaData.push_back(current.crewMembers[i].role + " " + current.crewMembers[i].name);
		}
		if (current.playingInCinima)
			metaData.push_back("Currently Playing In Cinemas");
		else if (current.unreleased)
			metaData.push_back("Currently Unrealeased");
		else 
			metaData.push_back("This Project Has Been Realeased");




		for (int i = 0; i < metaData.size(); i++){
			game.print(metaData[i], offsetX, offsetY + i);
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			game.drawColor(3, offsetY + 2 + selected, projects.at(selected + projectOffset).size(), 15);
			selected++;
			if (selected > min(19, projects.size()-1)) {
				selected = min(19, projects.size()-1);
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
			game.stringBuffer.pop_back();
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			allProjects = c1.sortByTitle(c1.searchByProjectTitle(c1.projects, game.stringBuffer));
			projects.clear();
			for (int i = 0; i < allProjects.size(); i++) {
				projects.push_back(allProjects[i].title);
			}
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

	Project p3(1, "Jumbo", "Big elaphant and mum ded 2", "2019/04/27", 90, false, false);
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

