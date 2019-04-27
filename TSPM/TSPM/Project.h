#pragma once

#include <string>
#include <vector> 
#include "CrewMember.h"
#include "PhysicalMedium.h"

#include "VHS.h"
#include "DVD.h"

class Project
{
public:
	Project();

	Project(int projectID, std::string title, std::string summary, std::string releaseDate, unsigned int runtime, bool playingInCinimam, bool unreleased, int weeklySales = 0);

	~Project();

	void addPhysicalMedium(PhysicalMedium * m);

	bool playingInCinima;

	bool unreleased;

	bool containsCast(std::string name, std::string role);

	void addKeyword(std::string keyword);

	void addCrewMember(std::string name, std::string role);

	void addFilmingLocation(std::string location);

	void addGenre(std::string genre);


	std::string save();

	static std::vector<std::string> split(std::string text, char = ',');


	int projectID;

	std::string title;

	std::string summary;

	std::string releaseDate;

	unsigned int runtime;

	int weeklySales;

	std::vector<std::string> genres;

	std::vector<std::string> filmingLocations;

	std::vector<std::string> keywords;

	std::vector<CrewMember> crewMembers;

	std::vector<PhysicalMedium*> physcicalMeduims;

	
private:
	static int binarySearch(std::vector<std::string> arr, int start, int end, std::string target);

};

