#include "stdafx.h"
#include "Project.h"

#include <fstream>

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

void Project::addPhysicalMedium(PhysicalMedium m)
{
	physcicalMeduims.push_back(m);
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
	std::ofstream f;
	f.open(std::to_string(projectID) + ".txt");

	std::string data;

	data = title + "\n";
	data += summary + "\n";
	data += releaseDate + "\n";
	data += std::to_string(runtime) + "\n";
	data += (std::string)(playingInCinima ? "true" : "false") + "\n";
	data += (std::string)(unreleased ? "true" : "false") + "\n";

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


	f << data;

	return data;
}
