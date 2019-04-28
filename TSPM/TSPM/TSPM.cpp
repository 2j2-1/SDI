// TSPM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cGame.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include "Project.h"
#include "Catalogue.h"
#include <sstream>
#include "Stack.h"
#include <fstream>
#include <ctime>

const int _weeklySalesThreshold = 1000;


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
}
int search(int searchMode) {
	int offsetY = 4;
	int offsetX = 20;
	int selected = 0;
	int projectOffset = 0;
	std::vector<Project> allProjects = c1.sortByTitle(c1.projects);
	std::vector<std::string> projects;
	int metaDataSize;
	for (int i = 0; i < allProjects.size(); i++){
		projects.push_back(allProjects[i].getTitle());
	}
	while (!GetAsyncKeyState(VK_ESCAPE)){
		game.blank_screen();
		if (game.input() != "") {
			game.stringBuffer += game.input();
			selected = 0;
			projectOffset = 0;
		}
		
		printSearch(projects, offsetY, selected, projectOffset);

		//printSearch(projects, offsetY, selected, projectOffset);

		if (GetAsyncKeyState(VK_DOWN)) {
			selected++;
			if (selected > min(19, projects.size() - 1)) {
				selected = min(19, projects.size() - 1);
				projectOffset++;
			}
		}
		if (GetAsyncKeyState(VK_UP)) {
			selected--;
			if (selected < 0) {
				selected = 0;
				projectOffset--;
				if (projectOffset < 0)
					projectOffset = 0;
			}
			
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			Stack reverse;
			if (searchMode = 0)
				allProjects = c1.sortByTitle(c1.searchByActor(c1.projects, game.stringBuffer));
			else
				allProjects = c1.sortByTitle(c1.searchByProjectTitle(c1.projects, game.stringBuffer));
			projects.clear();

			for (Project proj : allProjects)
			{
				reverse.push(proj);
			}

			std::vector<Project> reversed;
			while (!reverse.isEmpty())
			{
				reversed.push_back(reverse.pop());
			}
			allProjects = reversed;
			
			for (int i = 0; i < allProjects.size(); i++) {
				projects.push_back(allProjects[i].getTitle());
			}
		}
		if (GetAsyncKeyState(VK_TAB)) {
			if (searchMode=0)
				allProjects = c1.sortByTitle(c1.searchByActor(c1.projects, game.stringBuffer));
			else
				allProjects = c1.sortByTitle(c1.searchByProjectTitle(c1.projects, game.stringBuffer));
			projects.clear();
			for (int i = 0; i < allProjects.size(); i++) {
				projects.push_back(allProjects[i].getTitle());
			}
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			if (projects.size()>0)
				selectedProject = allProjects.at(selected);
			break;
		}
		game.draw();
		Sleep(50);
		
	}
	return -1;
}

int menu() {
	int offset = 1;
	int choice = -1;
	game.print("1. Load File",3,3 + offset);
	game.print("2. Create New Project", 3, 4 + offset);
	game.print("3. Update Project", 3, 5 + offset);
	game.print("4. Delete Project", 3, 6 + offset);
	game.print("5. Search by Actor", 3, 7 + offset);
	game.print("6. Search By Title", 3, 8 + offset);
	game.print("7. Add Physical Media ", 3, 9 + offset);
	game.print("8. View Project ", 3, 10 + offset);
	game.print("0. Exit", 3, 11 + offset);
	game.print("Please Enter Choice: " + game.stringBuffer, 3, 13 + offset);
	if (GetAsyncKeyState(VK_RETURN)) {
		try
		{
			int temp = std::stoi(game.stringBuffer);
			game.stringBuffer.clear();
			return temp;
		}
		catch (std::invalid_argument ex)
		{
			game.stringBuffer.clear();
		}
		
		
	}
	return -1;
}

int addPhysicalMedia(){
	int xoff = 3;
	int yoff = 3;
	int dataoff = 20;
	std::vector<std::string> para;
	std::vector<std::string> words = { "ID","Type","Title","Format","Frame Aspect","Packing","Audio Track Language","Subtitle Language","Bonus Feature" };
	while (!GetAsyncKeyState(VK_ESCAPE)) {
		game.stringBuffer += game.input();
		yoff = 3;
		game.blank_screen();
		for (int i = 0; i < words.size(); i++) {
			if (para.size() == i)
				game.print(words.at(i) + ": " + game.stringBuffer, xoff, yoff);
			else if (para.size() > i)
				game.print(words.at(i) + ": " + para.at(i), xoff, yoff);
			else
				game.print(words.at(i) + ": ", xoff, yoff);
			yoff++;
		}
		game.print("physcicalMeduims: ", xoff, yoff);
		yoff++;
		if (GetAsyncKeyState(VK_RETURN) && para.size() <= words.size()) {
			para.push_back(game.stringBuffer);
			if (para.size() == words.size()) {
				if (para.at(2) == "VHS") {
					VHS * temp= new VHS(1, "VHS", para.at(2), para.at(3), para.at(4), para.at(5), para.at(6), para.at(7));
					selectedProject.addPhysicalMedium(temp);
				}
				else {
					DVD * temp = new DVD(1, para.at(1), para.at(2), para.at(3), para.at(4), para.at(5));
					for (int i = 0; i < Project::split(para.at(6), ',').size(); i++) {
						temp->addAudioTrack(Project::split(para.at(6), ',').at(i));
					}
					for (int i = 0; i < Project::split(para.at(7), ',').size(); i++) {
						temp->addSubtitleLanguage(Project::split(para.at(7), ',').at(i));
					}
					for (int i = 0; i < Project::split(para.at(8), ',').size(); i++) {
						temp->addBonusFeature(Project::split(para.at(8), ',').at(i));
					}
					selectedProject.addPhysicalMedium(temp);
				}
				selectedProject.save();
				
				return -1;
			}

			game.stringBuffer.clear();
		}

		game.draw();
	}
	return -1;
}

int update() {
	int xoff = 3;
	int yoff = 3;
	int dataoff = 20;
	int data = 0;
	std::vector<std::string> para = { selectedProject.getTitle(), selectedProject.getSummary(), selectedProject.getReleaseDate(), std::to_string(selectedProject.getRunTime()),std::to_string(selectedProject.getPlayingInCinima()),std::to_string(selectedProject.getUnreleased())};
	std::vector<std::string> words = { "Title","Summary","Release Date","Run Time","Playing In Cinima","unreleased","genres","filmingLocations","keywords","crewMembers" };
	game.stringBuffer = para.at(data);
	std::string temp;
	for (int i = 0; i < selectedProject.genres.size(); i++) {
		temp += selectedProject.genres.at(i) + ",";
	}
	if (temp.size() > 0) {
		temp.pop_back();
		para.push_back(temp);
	}
	temp.clear();
	for (int i = 0; i < selectedProject.filmingLocations.size(); i++) {
		temp += selectedProject.filmingLocations.at(i) + ",";
	}
	if (temp.size() > 0) {
		temp.pop_back();
		para.push_back(temp);
	}
	temp.clear();
	for (int i = 0; i < selectedProject.keywords.size(); i++) {
		temp += selectedProject.keywords.at(i) + ",";
	}
	if (temp.size() > 0) {
		temp.pop_back();
		para.push_back(temp);
	}
	temp.clear();
	for (int i = 0; i < selectedProject.crewMembers.size(); i++) {
		temp += selectedProject.crewMembers.at(i).name + "," + selectedProject.crewMembers.at(i).role + ",";
	}
	if (temp.size() > 0) {
		temp.pop_back();
		para.push_back(temp);
	}
	if (selectedProject.getPlayingInCinima()) {
		words.push_back("Box Office Sales");
		para.push_back(std::to_string(selectedProject.getWeeklySales()));
	}
		

	while(!GetAsyncKeyState(VK_ESCAPE)) {
		game.stringBuffer += game.input();
		yoff = 3;
		game.blank_screen();
		for (int i = 0; i < para.size(); i++) {
			if (data == i)
				game.print(words.at(i) + ": " + game.stringBuffer, xoff, yoff);
			else if (data < para.size())
				game.print(words.at(i) + ": " + para.at(i), xoff, yoff);
			else
				game.print(words.at(i) + ": ", xoff, yoff);
			yoff++;
		}
		game.print("Physcial Meduims: ", xoff, yoff);
		yoff++;
		for (int i = 0; i < selectedProject.physcicalMeduims.size(); i++){
			game.print(selectedProject.physcicalMeduims.at(i)->type, xoff, yoff);
			yoff++;
		}
		
		if (GetAsyncKeyState(VK_RETURN) && para.size() <= words.size()) {
			
			if (para.size() > data)
				para.at(data) = game.stringBuffer;
			else 
				para.push_back(game.stringBuffer);
			data++;
			
			if (data == words.size()) {
				try {
					bool a;
					std::istringstream(para.at(4)) >> std::boolalpha >> a;
					bool b;
					std::istringstream(para.at(5)) >> std::boolalpha >> b;
					Project temp(selectedProject.getProjectID(), para.at(0), para.at(1), para.at(2), std::stoi(para.at(3)), a, b);
					for (int i = 0; i < temp.split(para.at(6), ',').size(); i++) {
						temp.addGenre(temp.split(para.at(6), ',').at(i));
					}
					for (int i = 0; i < temp.split(para.at(7), ',').size(); i++) {
						temp.addFilmingLocation(temp.split(para.at(7), ',').at(i));
					}
					for (int i = 0; i < temp.split(para.at(8), ',').size(); i++) {
						temp.addKeyword(temp.split(para.at(8), ',').at(i));
					}
					for (int i = 0; i < temp.split(para.at(9), ',').size(); i += 2) {
						temp.addCrewMember(temp.split(para.at(9), ',').at(i), temp.split(para.at(9), ',').at(i + 1));
					}
					temp.setWeeklySales(std::stoi(para.at(10)));
					c1.deleteProject(selectedProject.getProjectID());
					c1.add(temp);
					selectedProject = temp;
					temp.save();
				}
				catch (std::invalid_argument ex){}

				return -1;
			} else
				game.stringBuffer = para.at(data);

		}

		game.draw();
	}
	return -1;
}

int create() {
	int xoff = 3;
	int yoff = 3;
	int dataoff = 20;
	std::vector<std::string> para;
	std::vector<std::string> words = {"Title","Summary","Release Date","Run Time","Playing In Cinima","unreleased","genres","filmingLocations","keywords","crewMembers","Box Office Sales" };
	while(!GetAsyncKeyState(VK_ESCAPE)) {
		game.stringBuffer += game.input();
		yoff = 3;
		game.blank_screen();
		for (int i = 0; i < words.size(); i++){
			if (para.size() == i)
				game.print(words.at(i) + ": " + game.stringBuffer, xoff, yoff);
			else if(para.size() > i)
				game.print(words.at(i) + ": " + para.at(i), xoff, yoff);
			else
				game.print(words.at(i) + ": ", xoff, yoff);
			yoff++;
		}
		if (GetAsyncKeyState(VK_RETURN) && para.size() <= words.size()) {
			para.push_back(game.stringBuffer);
			if (para.size() == words.size()) {
				try {
					bool a;
					std::istringstream(para.at(4)) >> std::boolalpha >> a;
					bool b;
					std::istringstream(para.at(5)) >> std::boolalpha >> b;
					Project temp(c1.projects.back().getProjectID()+1, para.at(0), para.at(1), para.at(2), std::stoi(para.at(3)), a, b);
					for (int i = 0; i < temp.split(para.at(6), ',').size(); i++) {
						temp.addGenre(temp.split(para.at(6), ',').at(i));
					}
					for (int i = 0; i < temp.split(para.at(7), ',').size(); i++) {
						temp.addFilmingLocation(temp.split(para.at(7), ',').at(i));
					}
					for (int i = 0; i < temp.split(para.at(8), ',').size(); i++) {
						temp.addKeyword(temp.split(para.at(8), ',').at(i));
					}
					for (int i = 0; i < temp.split(para.at(9), ',').size(); i += 2) {
						temp.addCrewMember(temp.split(para.at(9), ',').at(i), temp.split(para.at(9), ',').at(i + 1));
					}
					if (a) {
						temp.setWeeklySales(std::stoi(para.at(10)));
					}


					c1.add(temp);
					temp.save();
				}
				catch (std::invalid_argument ex){}
				catch(std::out_of_range){}
				return -1;
			}
			
			game.stringBuffer.clear();
		}
		
		game.draw();
	}
	return -1;
}

int view() {
	int xoff = 3;
	int yoff = 3;
	int dataoff = 20;
	int mode = -1;
	while (!GetAsyncKeyState(VK_ESCAPE)) {
		if (GetAsyncKeyState(VK_RIGHT)) {
			mode++;
			mode = min(mode, selectedProject.physcicalMeduims.size() - 1);
		}
		if (GetAsyncKeyState(VK_LEFT)) {
			mode--;
			mode = max(mode, -1);
		}
		yoff = 3;
		game.blank_screen();
		if (mode == -1) {
			game.print("Title: ", xoff, yoff);
			game.print(selectedProject.getTitle(), xoff + dataoff, yoff);
			yoff++;

			game.print("Summary: ", xoff, yoff);
			game.print(selectedProject.getSummary(), xoff + dataoff, yoff);
			yoff++;

			game.print("Release Date: ", xoff, yoff);
			game.print(selectedProject.getReleaseDate(), xoff + dataoff, yoff);
			yoff++;

			game.print("Run Time: ", xoff, yoff);
			game.print(std::to_string(selectedProject.getRunTime()), xoff + dataoff, yoff);
			yoff++;

			game.print("Playing In Cinima: ", xoff, yoff);
			if (selectedProject.getPlayingInCinima())
				game.print("True", xoff + dataoff, yoff);
			else
				game.print("False", xoff + dataoff, yoff);
			yoff++;

			game.print("unreleased: ", xoff, yoff);
			if (selectedProject.getUnreleased())
				game.print("True", xoff + dataoff, yoff);
			else
				game.print("False", xoff + dataoff, yoff);
			yoff++;

			game.print("weeklySales: ", xoff, yoff);
			game.print(std::to_string(selectedProject.getWeeklySales()), xoff + dataoff, yoff);
			yoff++;

			game.print("genres: ", xoff, yoff);
			for (int i = 0; i < selectedProject.genres.size(); i++) {
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
			for (int i = 0; i < selectedProject.physcicalMeduims.size(); i++) {
				game.print(selectedProject.physcicalMeduims.at(i)->type, xoff + dataoff, yoff);
				yoff++;
			}
		}
		else if (selectedProject.physcicalMeduims.size() > 0) {
			game.print("ID: ", xoff, yoff);
			game.print(std::to_string(selectedProject.physcicalMeduims.at(mode)->ID), xoff + dataoff, yoff);
			yoff++;
			game.print("type: ", xoff, yoff);
			game.print(selectedProject.physcicalMeduims.at(mode)->type, xoff + dataoff, yoff);
			yoff++;
			game.print("title: ", xoff, yoff);
			game.print(selectedProject.physcicalMeduims.at(mode)->title, xoff + dataoff, yoff);
			yoff++;
			game.print("format: ", xoff, yoff);
			game.print(selectedProject.physcicalMeduims.at(mode)->format, xoff + dataoff, yoff);
			yoff++;
			game.print("frameAspect: ", xoff, yoff);
			game.print(selectedProject.physcicalMeduims.at(mode)->frameAspect, xoff + dataoff, yoff);
			yoff++;
			game.print("packaging: ", xoff, yoff);
			game.print(selectedProject.physcicalMeduims.at(mode)->packaging, xoff + dataoff, yoff);
			yoff++;
			if (selectedProject.physcicalMeduims.at(mode)->type == "VHS") {
				game.print("AudioTrackLanguage: ", xoff, yoff);
				game.print(((VHS*)selectedProject.physcicalMeduims.at(mode))->AudioTrackLanguage, xoff + dataoff, yoff);
				yoff++;
				game.print("subtitlesLanguage: ", xoff, yoff);
				game.print(((VHS*)selectedProject.physcicalMeduims.at(mode))->subtitlesLanguage, xoff + dataoff, yoff);
				yoff++;
			}
			else {
				game.print("AudioTracksDubs: ", xoff, yoff);
				for (int i = 0; i < ((DVD*)selectedProject.physcicalMeduims.at(mode))->AudioTracksDubs.size(); i++) {
					game.print(((DVD*)selectedProject.physcicalMeduims.at(mode))->AudioTracksDubs.at(i), xoff + dataoff, yoff);
					yoff++;
				}
				game.print("SubtitleLanguages: ", xoff, yoff);
				for (int i = 0; i < ((DVD*)selectedProject.physcicalMeduims.at(mode))->SubtitleLanguages.size(); i++) {
					game.print(((DVD*)selectedProject.physcicalMeduims.at(mode))->SubtitleLanguages.at(i), xoff + dataoff, yoff);
					yoff++;
				}
				game.print("AudioTracksDubs: ", xoff, yoff);
				for (int i = 0; i < ((DVD*)selectedProject.physcicalMeduims.at(mode))->bonusFeatures.size(); i++) {
					game.print(((DVD*)selectedProject.physcicalMeduims.at(mode))->bonusFeatures.at(i), xoff + dataoff, yoff);
					yoff++;
				}
			}
		}

		game.draw();
	}
	return -1;
}

std::string getCurrentDate(){
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	return std::to_string(1900 + now->tm_year) + "-" + std::to_string(now->tm_mon + 1) + "-" + std::to_string(now->tm_mday);
}

void logCreation(Project p)
{
	std::ofstream outfile;

	outfile.open(getCurrentDate() + ".txt", std::ios_base::app);
	outfile << "Created project: " << p.getTitle() << "\n";
	outfile.close();
}

void logWeeklySales(Project p)
{
	std::ofstream outfile;

	outfile.open(getCurrentDate() + ".txt", std::ios_base::app);
	outfile << p.getTitle() << "'s weekly ticket sales: " << p.getWeeklySales();
	outfile.close();
}

int main(){
	Project p1(0, "Dumbo", "Ridiculed because of his enormous ears, a young circus elephant is assisted by a mouse to achieve his full potential.", "1942/01/02", 64, false, false);
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
	p1.addPhysicalMedium(new VHS(0,"VHS","Dumbo", "MP4", "MP4", "MP4", "MP4", "MP4"));

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

	p3.addPhysicalMedium(new VHS(5, "VHS", "Dumbo on vhs", "MP4", "Standard", "Card", "English", "English"));
	p3.addPhysicalMedium(new VHS(6, "VHS", "Dumbo on vhs", "MP4", "Standard", "Card", "English", "English"));
	p3.addPhysicalMedium(new VHS(7, "VHS", "Dumbo on vhs", "MP4", "Standard", "Card", "English", "English"));

	DVD * dvd1 = new DVD(8, "Blue ray", "Dumbo on blue ray", "MP4", "Wide sceen", "Plastic");
	DVD * dvd2 = new DVD(9, "Blue ray", "Dumbo on blue ray remastered", "MP4", "Wide sceen", "Plastic");

	dvd1->addAudioTrack("English");
	dvd1->addAudioTrack("Spanish");
	dvd1->addAudioTrack("French");

	dvd1->addSubtitleLanguage("English");
	dvd1->addSubtitleLanguage("Spanish");
	dvd1->addSubtitleLanguage("French");

	dvd1->addBonusFeature("English");
	dvd1->addBonusFeature("Spanish");
	dvd1->addBonusFeature("French");


	dvd2->addAudioTrack("English");
	dvd2->addAudioTrack("Spanish");
	dvd2->addAudioTrack("French");

	dvd2->addSubtitleLanguage("English");
	dvd2->addSubtitleLanguage("Spanish");
	dvd2->addSubtitleLanguage("French");

	dvd2->addBonusFeature("English");
	dvd2->addBonusFeature("Spanish");
	dvd2->addBonusFeature("French");

	p3.addPhysicalMedium(dvd1);
	p3.addPhysicalMedium(dvd2);

	//c1.add(p1);
	//c1.add(p2);
	//c1.add(p3);

	Stack stack;

	stack.push(p1);
	stack.push(p2);
	stack.push(p3);

	std::vector<Project> vect;
	
	while (!stack.isEmpty())
	{
		vect.push_back(stack.pop());
	}

	//c1.write();
	


	int screen = -1;
	game.setup();
	game.blank_screen();
	while(true) {
		game.blank_screen();
		game.print("Welcome to TSPM",game.screenWidth/2-8,2);
		game.draw_pixel(0, 0, char(screen+48));
		game.stringBuffer += game.input();
		
		switch (screen) {
		case -1:
			screen = menu();
			break;
		case 0:
			return 0;
		case 1:
			c1.projects.clear();
			c1.read();
			game.stringBuffer.clear();
			screen = -1;
			break;
		case 2:
			screen = create();
			logCreation(selectedProject);
			game.stringBuffer.clear();
			break;
		case 3:
			if (selectedProject.getProjectID() != -1) {
				screen = update();
				if (_weeklySalesThreshold)
					logWeeklySales(selectedProject);
			}
			game.stringBuffer.clear();
			screen = -1;
			break;
		case 4:
			screen = -1;
			if (selectedProject.getProjectID() != -1) {
				c1.deleteProjectFile(selectedProject.getProjectID());
				c1.deleteProject(selectedProject.getProjectID());
				selectedProject = Project();
			}
			game.stringBuffer.clear();
			break;
		case 5:
			if (c1.projects.size() != 0)
				screen = search(0);
			game.stringBuffer.clear();
			break;
		case 6:
			if (c1.projects.size() != 0)
				screen = search(1);
			game.stringBuffer.clear();
			break;
		case 7:
			if (selectedProject.getProjectID() != -1 && !selectedProject.getPlayingInCinima() && !selectedProject.getUnreleased()) {
				addPhysicalMedia();
			}
			game.stringBuffer.clear();
			screen = -1;
			break;
		case 8:
			if (selectedProject.getProjectID() != -1) {
				view();
			}
			game.stringBuffer.clear();
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

