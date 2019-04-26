#pragma once

#include <string>
#include <vector> 
#include "CrewMember.h"

class Project
{
public:
	Project(int projectID, std::string title, std::string summary, std::string releaseDate, unsigned int runtime, bool playingInCinimam, bool unreleased);

	~Project();


	int projectID;

	std::string title;

	std::string summary;

	std::vector<std::string> genres;

	std::string releaseDate;

	std::vector<std::string> filmingLocations;

	unsigned int runtime;

	std::vector<std::string> keywords;

	std::vector<CrewMember> crewMembers;

	bool playingInCinima;

	bool unreleased;

	bool containsCast(std::string name, std::string role);

	void addKeyword(std::string keyword);

	void addCrewMember(std::string name, std::string role);

	void addFilmingLocation(std::string location);

	void addGenre(std::string genre);

	std::string save();


};

