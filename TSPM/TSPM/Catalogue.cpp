#include "stdafx.h"
#include "Catalogue.h"
#include <fstream>
#include <sstream>


Catalogue::Catalogue()
{
}


Catalogue::~Catalogue()
{
}

std::vector<int> Catalogue::searchByText(std::vector<std::string> text, std::string searchTerm)
{
	//Creates a vector to store the indexes of items which contain the search term
	std::vector<int> indexes;

	//Loops through each elements
	for (int i = 0; i < text.size(); i++)
	{
		//If the current element contain the search term the index is added to the vector 
		if (text[i].find(searchTerm) != std::string::npos)
		{
			indexes.push_back(i);
		}
	}

	return indexes;
}

std::vector<Project> Catalogue::searchByProjectTitle(std::vector<Project> projects, std::string searchTerm)
{
	//Stores titles in a vector of strings to be used for the search
	std::vector<std::string> titles;
	for (int i = 0; i < projects.size(); i++)
	{
		titles.push_back(projects[i].getTitle());
	}

	std::vector<int> indexes = searchByText(titles, searchTerm);

	std::vector<Project> ret;

	//Adds items which match the search term to a vector 
	for (int i : indexes)
	{
		ret.push_back(projects[i]);
	}

	//Returns project
	return ret;
}

std::vector<Project> Catalogue::searchByActor(std::vector<Project> projects, std::string actorName)
{
	std::vector<Project> ret;
	//Finds Projects which contain the actor
	for (Project p : projects)
	{
		if (p.containsCast(actorName, "actor"))
		{
			ret.push_back(p);
		}
	}

	return ret;
}

std::vector<int> Catalogue::sortByText(std::vector<std::string> text, std::vector<int> IDs)
{
	std::vector<std::pair<int, std::string>> oldIndexes;
	std::vector<std::pair<int, std::string>> newIndexes;

	for (int i = 0; i < IDs.size(); i++)
	{
		oldIndexes.push_back(std::make_pair(IDs[i], text[i]));
	}

	int start = 0;
	int end = text.size() - 1;
	quickSort(text, start, end);

	for (int i = 0; i < text.size(); i++)
	{
		newIndexes.push_back(std::make_pair(i, text[i]));
	}

	int count = 0;
	std::vector<int> ret;
	while (count != newIndexes.size()){
		for (int i = 0; i < newIndexes.size(); i++){
			if (newIndexes[count].second == oldIndexes[i].second){
				ret.push_back(oldIndexes[i].first);
				count += 1;
				if (count == newIndexes.size())
					break;
			}
		}
		
	}


	return ret;
}

std::vector<Project> Catalogue::sortByTitle(std::vector<Project> projects)
{
	std::vector<std::string> titles;
	std::vector<int> indexes;
	
	//Constructs a vector of strings from the projects titles for the sort function
	for (int i = 0; i < projects.size(); i++)
	{
		titles.push_back(projects[i].getTitle());
		indexes.push_back(i);
	}

	std::vector<int> newIndexes = sortByText(titles, indexes);

	std::vector<Project> ret;

	//Constructs the sorted vector of projects
	for (int i : newIndexes)
	{
		ret.push_back(projects[i]);
	}

	return ret;
}

std::vector<int> Catalogue::sortByDate(std::vector<std::string> dates, std::vector<int> IDs)
{
	std::vector<std::pair<int, std::string>> oldIndexes;
	std::vector<std::pair<int, std::string>> newIndexes;

	for (int i = 0; i < IDs.size(); i++)
	{
		oldIndexes.push_back(std::make_pair(IDs[i], dates[i]));
	}

	int start = 0;
	int end = dates.size() - 1;
	quickSort(dates, start, end);

	for (int i = 0; i < dates.size(); i++)
	{
		newIndexes.push_back(std::make_pair(i, dates[i]));
	}

	int count = 0;
	std::vector<int> ret;
	bool complete = false;
	while (!complete)
	{
		for (int i = 0; i < newIndexes.size(); i++)
		{
			if (newIndexes[count].second == oldIndexes[i].second)
			{
				ret.push_back(oldIndexes[i].first);
				count += 1;
			}
		}
		if (count == newIndexes.size())
		{
			complete = true;
		}
	}


	return ret;
}

std::vector<Project> Catalogue::sortByDate(std::vector<Project> projects)
{
	std::vector<std::string> dates;
	std::vector<int> indexes;
	//Creates vector of date strings for the sort function
	for (int i = 0; i < projects.size(); i++)
	{
		dates.push_back(projects[i].getReleaseDate());
		indexes.push_back(i);
	}

	std::vector<int> newIndexes = sortByDate(dates, indexes);

	std::vector<Project> ret;

	//Constructs sorted vector of projects 
	for (int i : newIndexes)
	{
		ret.push_back(projects[i]);
	}

	return ret;
}

void Catalogue::quickSort(std::vector<std::string>& arr, int start, int end)
{
	if (start < end) {
		int p = 0;
		p = partition(arr, start, end);
		//Quick sorts each partition recursively
		quickSort(arr, start, p - 1);
		quickSort(arr, p + 1, end);
	}
}

void Catalogue::swap(std::string & x, std::string & y)
{
	std::string temp = x;
	x = y;
	y = temp;
}

int Catalogue::partition(std::vector<std::string>& arr, int start, int end)
{
	//Creates pivot in the centre of the partition
	int pivot = start + ((end - start) / 2);
	std::string pivotVal = arr[pivot];
	
	swap(arr[pivot], arr[end]);
	int store = start;

	//Places pivot in correct position
	for (int i = start; i < end; i++) {
		if (arr[i] < pivotVal) {
			swap(arr[i], arr[store]);
			store += 1;
		}
	}

	swap(arr[store], arr[end]);

	return store;
}

void Catalogue::add(Project p)
{
	//Projects are added in order of project id so available IDs can be retrieved by viewing the project ID at the end of the vector

	//If the current project should be the last elemement 
	if (projects.size() == 0 || p.getProjectID() == projects.back().getProjectID() + 1)
		//push the project the end of the vector
	projects.push_back(p);
	else
	{
		//inserts the project into the correct place using the projects id as an index
		projects.insert(projects.begin() + p.getProjectID(), p);
	}

	//Updates directories file to include the new project
	updateDirectories();
}

void Catalogue::update(Project p)
{
	projects[p.getProjectID()] = p;
	p.save();
}



void Catalogue::read()
{
	//Opens directories file which contains the names of the files for all the saved projects
	std::ifstream infile("directories.txt");

	//Loops through each directory
	std::string line;
	while (std::getline(infile, line))
	{
		
		std::ifstream f((line + ".txt").c_str());
		//Checks that the file exsists
		if (f.good())
		{
			f.close();
			//Adds the project from the file
			add(parse(line + ".txt", std::stoi(line)));
		}
		else
		{
			f.close();
		}
		
	}

	infile.close();
	
}

void Catalogue::write()
{
	std::ofstream f;
	f.open("directories.txt");

	//Writes all active projects to a file
	for (Project p : projects)
	{
		p.save();

		f << std::to_string(p.getProjectID()) << "\n";
	}
	f.close();
}

void Catalogue::updateDirectories()
{
	std::ofstream f;
	f.open("directories.txt");
	//Adds all active projects to directories list
	for (Project p : projects)
	{
		f << std::to_string(p.getProjectID()) << "\n";
	}
	f.close();
}

void Catalogue::deleteProject(int projectID)
{
	//Deletes the file of the project
	deleteProjectFile(projectID);

	//Removes project from the vector
	projects.erase(projects.begin() + projectID);

	//Updates the IDs of all active projects to fill the gap left by the deleted project
	for (int i = projectID; i < projects.size(); i++)
	{
		projects[i].setProjectID(projects[i].getProjectID() - 1);
		projects[i].save();
	}

	//Removes the final file as it will not get overwritten
	deleteProjectFile(projects.size());
}

void Catalogue::deleteProjectFile(int projectID)
{
	//Deletes file for a project
	remove((std::to_string(projectID) + ".txt").c_str());
}

Project Catalogue::parse(std::string filePath, int projectID)
{
	//Opens file containing project data
	std::ifstream infile(filePath);

	std::string line;

	//Stores attributes needed for contructor from the file 
	std::getline(infile, line);

	std::string title = line;

	std::getline(infile, line);

	std::string summary = line;

	std::getline(infile, line);

	std::string releaseDate = line;

	std::getline(infile, line);

	unsigned int runtime = std::stoi(line);

	std::getline(infile, line);

	bool playingInCinimam = (line == "true");

	std::getline(infile, line);

	bool unreleased = (line == "true");

	std::getline(infile, line);

	int weeklySales = std::stoi(line);

	//Constructs project from read data
	Project p(projectID, title, summary,  releaseDate,  runtime,  playingInCinimam,  unreleased, weeklySales);



	//Adds keywords for project
	while (std::getline(infile, line))
	{
		if (line == ",")
		{
			break;
		}
		p.addKeyword(line);

	}

	//Adds crew for project
	while (std::getline(infile, line))
	{
		if (line == ",")
		{
			break;
		}
		std::string name = line;

		std::getline(infile, line);

		std::string role = line;

		p.addCrewMember(name, role);
	}


	//Adds locations for project
	while (std::getline(infile, line))
	{
		if (line == ",")
		{
			break;
		}
		p.addFilmingLocation(line);

	}

	//Adds genre for project
	while (std::getline(infile, line))
	{
		if (line == ",")
		{
			break;
		}
		p.addGenre(line);
	}

	//Adds metarials for project
	while (std::getline(infile, line))
	{
		if (line == ",")
		{
			break;
		}
		int ID = std::stoi(line);
		std::getline(infile, line);
		std::string type = line;
		std::getline(infile, line);
		std::string title = line;
		std::getline(infile, line);
		std::string format = line;
		std::getline(infile, line);
		std::string frameAspect = line;
		std::getline(infile, line);
		std::string packaging = line;


		if (type == "VHS")
		{
			std::getline(infile, line);
			std::string AudioTrackLang = line;
			std::getline(infile, line);
			std::string subtitlesLang = line;
			p.addPhysicalMedium(new VHS(ID, type, title, format, frameAspect, packaging, AudioTrackLang, subtitlesLang));
		}
		else
		{
			DVD * dvd = new DVD(ID, type, title, format, frameAspect, packaging);

			while (std::getline(infile, line))
			{
				if (line == ",")
				{
					break;
				}

				dvd->addAudioTrack(line);
			}

			while (std::getline(infile, line))
			{
				if (line == ",")
				{
					break;
				}

				dvd->addSubtitleLanguage(line);
			}

			while (std::getline(infile, line))
			{
				if (line == ",")
				{
					break;
				}

				dvd->addBonusFeature(line);
			}

			p.addPhysicalMedium(dvd);
		}

		
	}


	//Returns project
	return p;
}

