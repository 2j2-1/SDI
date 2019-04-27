#pragma once

#include <string>
#include <vector> 
#include "CrewMember.h"
#include "PhysicalMedium.h"

class Project
{
public:
	Project(int projectID, std::string title, std::string summary, std::string releaseDate, unsigned int runtime, bool playingInCinimam, bool unreleased);

	~Project();

	void addPhysicalMedium(PhysicalMedium m);

	bool playingInCinima;

	bool unreleased;

	bool containsCast(std::string name, std::string role);

	void addKeyword(std::string keyword);

	void addCrewMember(std::string name, std::string role);

	void addFilmingLocation(std::string location);

	void addGenre(std::string genre);

	std::string save();


	int projectID;

	std::string title;

	std::string summary;

	std::vector<std::string> genres;

	std::string releaseDate;

	std::vector<std::string> filmingLocations;

	unsigned int runtime;

	std::vector<std::string> keywords;

	std::vector<CrewMember> crewMembers;

	std::vector<PhysicalMedium> physcicalMeduims;

	
private:
	static int binarySearch(std::vector<std::string> arr, int start, int end, std::string target);

};

