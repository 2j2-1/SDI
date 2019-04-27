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
	std::vector<int> indexes;

	for (int i = 0; i < text.size(); i++)
	{
		if (text[i].find(searchTerm) != std::string::npos)
		{
			indexes.push_back(i);
		}
	}

	return indexes;
}

std::vector<Project> Catalogue::searchByProjectTitle(std::vector<Project> projects, std::string searchTerm)
{
	std::vector<std::string> titles;
	for (int i = 0; i < projects.size(); i++)
	{
		titles.push_back(projects[i].title);
	}

	std::vector<int> indexes = searchByText(titles, searchTerm);

	std::vector<Project> ret;

	for (int i : indexes)
	{
		ret.push_back(projects[i]);
	}

	return ret;
}

std::vector<Project> Catalogue::searchByActor(std::vector<Project> projects, std::string actorName)
{
	std::vector<Project> ret;
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
	for (int i = 0; i < projects.size(); i++)
	{
		titles.push_back(projects[i].title);
		indexes.push_back(i);
	}

	std::vector<int> newIndexes = sortByText(titles, indexes);

	std::vector<Project> ret;

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
	for (int i = 0; i < projects.size(); i++)
	{
		dates.push_back(projects[i].releaseDate);
		indexes.push_back(i);
	}

	std::vector<int> newIndexes = sortByDate(dates, indexes);

	std::vector<Project> ret;

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
	int pivot = start + ((end - start) / 2);
	std::string pivotVal = arr[pivot];
	swap(arr[pivot], arr[end]);
	int store = start;

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
	if (projects.size() == 0 || p.projectID == projects.back().projectID + 1)
	projects.push_back(p);
	else
	{
		projects.insert(projects.begin() + p.projectID, p);
	}
}



void Catalogue::read()
{
	std::ifstream infile("directories.txt");

	std::string line;
	while (std::getline(infile, line))
	{
		add(parse(line + ".txt", std::stoi(line)));
	}

	infile.close();
	
}

void Catalogue::write()
{
	std::ofstream f;
	f.open("directories.txt");
	for (Project p : projects)
	{
		p.save();

		f << std::to_string(p.projectID) << "\n";
	}
	f.close();
}

void Catalogue::updateDirectories()
{
	std::ofstream f;
	f.open("directories.txt");
	for (Project p : projects)
	{
		f << std::to_string(p.projectID) << "\n";
	}
	f.close();
}

void Catalogue::deleteProject(int projectID)
{
	projects.erase(projects.begin() + projectID, projects.begin() + projectID);

	for (int i = projectID; i < projects.size(); i++)
	{
		projects[i].projectID -= 1;
	}
}

Project Catalogue::parse(std::string filePath, int projectID)
{
	std::ifstream infile(filePath);

	std::string line;

	
	std::getline(infile, line);

	//int projectID = std::stoi(line);

	//std::getline(infile, line);

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

	Project p(projectID, title, summary,  releaseDate,  runtime,  playingInCinimam,  unreleased);




	while (std::getline(infile, line))
	{
		if (line == ",")
		{
			break;
		}
		p.addKeyword(line);

	}

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

	while (std::getline(infile, line))
	{
		if (line == ",")
		{
			break;
		}
		p.addFilmingLocation(line);

	}

	while (std::getline(infile, line))
	{
		if (line == ",")
		{
			break;
		}
		p.addGenre(line);
	}

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



	return p;
}

