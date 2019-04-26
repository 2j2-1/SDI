#pragma once

#include <string>
#include <vector> 
#include "CrewMember.h"

class Project
{
public:
	Project();
	~Project();


	int projectID;

	std::string title;

	std::string summary;

	std::string genre;

	std::string string;

	std::vector<std::string> filmingLocations;

	unsigned int runtime;

	std::vector<std::string> keywords;

	std::vector<CrewMember> crewMembers;

	bool playingInCinima;

	bool unreleased;
};

