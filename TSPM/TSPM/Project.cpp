#include "stdafx.h"
#include "Project.h"

#include <fstream>

Project::Project(int projectID, std::string title, std::string summary, std::string releaseDate, unsigned int runtime, bool playingInCinimam, bool unreleased, int weeklySales)
{
	this->projectID = projectID;

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

Project::~Project()
{
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
	crewMembers.push_back({ name, role });
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
	this->projectID = id;
}

void Project::setTitle(std::string title)
{
	this->title = title;
}

void Project::setSummary(std::string summary)
{
	this->summary = summary;
}

void Project::setReleaseDate(std::string date)
{
	this->releaseDate = date;
}

void Project::setRunTime(int runTime)
{
	this->runtime = runTime;
}

void Project::setWeeklySales(int sales)
{
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
