#include "stdafx.h"
#include "Project.h"


Project::Project(int projectID, std::string title, std::string summary, std::string releaseDate, unsigned int runtime, bool playingInCinimam, bool unreleased)
{
	this->projectID = projectID;

	this->title = title;

	this->summary = summary;

	this->releaseDate = releaseDate;

	this->runtime = runtime;

	this->playingInCinima = playingInCinima;

	this->unreleased = unreleased;
}

Project::~Project()
{
}

bool Project::containsCast(std::string name, std::string role)
{

	for (CrewMember c : crewMembers)
	{
		if (c.name == name && c.role == role)
		{
			return true;
		}
	}
	return false;
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

std::string Project::save()
{
	std::string data;

	data = title + "\n";
	data += summary + "\n";
	data += releaseDate + "\n";
	data += runtime + "\n";
	data += playingInCinima + "\n";
	data += unreleased + "\n";

	for (std::string keyword : keywords)
	{

	}

	return data;
}
