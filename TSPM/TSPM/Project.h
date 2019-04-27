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

	// get functions
	int getProjectID();

	std::string getTitle();

	std::string getSummary();

	std::string getReleaseDate();

	int getRunTime();

	int getWeeklySales();

	std::vector<std::string> getGenres();

	std::vector<std::string> getFilmingLocations();

	std::vector<std::string> getKeywords();

	std::vector<CrewMember> getCrewMembers();

	std::vector<PhysicalMedium*> getPhyicalMediums();


	// set functions
	void setProjectID(int id);

	void setTitle(std::string title);

	void setSummary(std::string summary);

	void setReleaseDate(std::string date);

	void setRunTime(int runTime);

	void setWeeklySales(int sales);

	void setGenres(std::vector<std::string> genreVector);

	void setFilmingLocations(std::vector<std::string> locationVector);

	void setKeywords(std::vector<std::string> keywordVector);

	void setCrewMembers(std::vector<CrewMember> crewVector);

	void setPhyicalMediums(std::vector<PhysicalMedium*> mediumVector);


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

