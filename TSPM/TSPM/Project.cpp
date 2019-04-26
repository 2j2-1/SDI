#include "stdafx.h"
#include "Project.h"


Project::Project(int projectID, std::string title, std::string summary, std::string genre, std::string releaseDate, unsigned int runtime, bool playingInCinimam, bool unreleased)
{
	this->projectID = projectID;

	this->title = title;

	this->summary = summary;

	this->genre = genre;

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
