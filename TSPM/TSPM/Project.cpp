#include "stdafx.h"
#include "Project.h"

#include <fstream>
#include "Catalogue.h"

Project::Project(int projectID, std::string title, std::string summary, std::string releaseDate, unsigned int runtime, bool playingInCinimam, bool unreleased, int weeklySales)
{
	setProjectID(projectID);

	setTitle(title);

	setSummary(summary);

	setReleaseDate(releaseDate);

	setRunTime(runtime);

	this->playingInCinima = playingInCinima;

	this->unreleased = unreleased;

	if (playingInCinima)
		this->weeklySales = weeklySales;
	else
		this->weeklySales = 0;
}

Project::~Project()
{
}
void Project::update(std::string title, std::string summary, std::string releaseDate, unsigned int runtime, bool playingInCinimam, bool unreleased, int weeklySales)
{
	this->title = title;

	this->summary = summary;

	this->releaseDate = releaseDate;

	this->runtime = runtime;

	this->playingInCinima = playingInCinima;

	this->unreleased = unreleased;

	if (playingInCinima)
		this->weeklySales = weeklySales;
	else
		this->weeklySales = 0;


}
Project::Project()
{
	this->projectID = -1;
}

void Project::addPhysicalMedium(PhysicalMedium * m)
{
	physcicalMeduims.push_back(m);
}

bool Project::containsCast(std::string name, std::string role)
{
	std::vector<std::string> names;
	for (CrewMember c : crewMembers)
	{
		names.push_back(c.name);
	}

	int index = binarySearch(names, 0, names.size() - 1, name);

	if (index == -1)
	{
		return false;
	}
	else
	{
		return true;
	}

	/*
	for (CrewMember c : crewMembers)
	{
		if (c.name == name && c.role == role)
		{
			return true;
		}
	}
	return false;
	*/
}

void Project::addKeyword(std::string keyword)
{
	keywords.push_back(keyword);
}

void Project::addCrewMember(std::string name, std::string role)
{
	std::vector<CrewMember> temp;
	bool added = false;

	for (int i = 0; i < crewMembers.size(); i++)
	{
		if (crewMembers[i].name > name && !added)
		{
			temp.push_back({ name, role });
			added = true;
		}
		temp.push_back(crewMembers[i]);
		

	}
	crewMembers = temp;

	if (crewMembers.size() == 0 || crewMembers.back().name < name)
	{
		crewMembers.push_back({ name, role });
	}
	std::cout <<  "";
}

void Project::addFilmingLocation(std::string location)
{
	filmingLocations.push_back(location);
}

void Project::addGenre(std::string genre)
{
	genres.push_back(genre);
}

int Project::getProjectID()
{
	return projectID;
}

std::string Project::getTitle()
{
	return title;
}

std::string Project::getSummary()
{
	return summary;
}

std::string Project::getReleaseDate()
{
	return releaseDate;
}

int Project::getRunTime()
{
	return runtime;
}

int Project::getWeeklySales()
{
	return weeklySales;
}

bool Project::getUnreleased()
{
	return unreleased;
}

bool Project::getPlayingInCinima()
{
	return playingInCinima;
}

std::vector<std::string> Project::getGenres()
{
	return genres;
}

std::vector<std::string> Project::getFilmingLocations()
{
	return filmingLocations;
}

std::vector<std::string> Project::getKeywords()
{
	return keywords;
}

std::vector<CrewMember> Project::getCrewMembers()
{
	return crewMembers;
}

std::vector<PhysicalMedium*> Project::getPhyicalMediums()
{
	return physcicalMeduims;
}

void Project::setProjectID(int id)
{
	if (id < 0)
	{
		throw std::invalid_argument("Project ID must be positive.");
	}

	this->projectID = id;
}

void Project::setTitle(std::string title)
{
	if (title == "")
	{
		throw std::invalid_argument("Must include a title");
	}

	this->title = title;
}

void Project::setSummary(std::string summary)
{
	if (summary == "")
	{
		throw std::invalid_argument("Must include a summary");
	}
	this->summary = summary;
}

void Project::setReleaseDate(std::string date)
{
	if (date == "")
	{
		throw std::invalid_argument("Must include a date");
	}
	this->releaseDate = date;
}

void Project::setRunTime(int runTime)
{
	if (runTime < 0)
	{
		throw std::invalid_argument("Runtime cannot be negitive");
	}

	this->runtime = runTime;
}

void Project::setWeeklySales(int sales)
{
	if (sales < 0)
	{
		throw std::invalid_argument("Weely ticket sales cannot be negitive");
	}
	this->weeklySales = sales;
}

void Project::setGenres(std::vector<std::string> genreVector)
{
	this->genres = genreVector;
}

void Project::setFilmingLocations(std::vector<std::string> locationVector)
{
	this->filmingLocations = locationVector;
}

void Project::setKeywords(std::vector<std::string> keywordVector)
{
	this->keywords = keywordVector;
}

void Project::setCrewMembers(std::vector<CrewMember> crewVector)
{
	this->crewMembers = crewVector;
}

void Project::setPhyicalMediums(std::vector<PhysicalMedium*> mediumVector)
{
	this->physcicalMeduims = mediumVector;
}

void Project::setUnreleased(bool unreleased)
{
	this->unreleased = unreleased;
}

void Project::setPlayingInCinima(bool playing)
{
	this->playingInCinima = playing;
}

std::string Project::save()
{
	std::ofstream f;
	f.open(std::to_string(projectID) + ".txt");

	std::string data;

	data = title + "\n";
	data += summary + "\n";
	data += releaseDate + "\n";
	data += std::to_string(runtime) + "\n";
	data += (std::string)(playingInCinima ? "true" : "false") + "\n";
	data += (std::string)(unreleased ? "true" : "false") + "\n";
	data += std::to_string(weeklySales) + "\n";

	for (std::string keyword : keywords)
	{
		data += keyword + "\n";
	}

	data += ",\n";

	for (CrewMember crewMember : crewMembers)
	{
		data += crewMember.name + "\n";
		data += crewMember.role + "\n";
	}

	data += ",\n";

	for (std::string location : filmingLocations)
	{
		data += location + "\n";
	}

	data += ",\n";

	for (std::string genre : genres)
	{
		data += genre + "\n";
	}

	data += ",\n";

	for (PhysicalMedium * physicalMedium : physcicalMeduims)
	{
		if (physicalMedium->type == "VHS")
		{
			data += ((VHS*)physicalMedium)->save();
		}
		else
		{
			data += ((DVD*)physicalMedium)->save();
		}
	}


	f << data;

	return data;
}

std::vector<std::string> Project::split(std::string text, char del)
{
	std::vector < std::string > ret;
	ret.push_back("");
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == del)
		{
			ret.push_back("");
		}
		else
		{
			ret.back() += text[i];
		}
	}

	return ret;
}

int Project::binarySearch(std::vector<std::string> arr, int start, int end, std::string target)
{
	if (end >= start) {
		int mid = start + (end - start) / 2;

		// If element in middle 
		if (arr[mid] == target)
			return mid;

		// If in left half
		if (arr[mid] > target)
			return binarySearch(arr, start, mid - 1, target);

		// Else in right half
		return binarySearch(arr, mid + 1, end, target);
	}

	// Not present
	return -1;
}
