#pragma once
#include <string>
#include <vector>
#include "Project.h"
#include <fstream>
#include <iostream>

class Catalogue
{
public:
	Catalogue();
	~Catalogue();

	//Returns a vector of ids which match the search term
	std::vector<int> searchByText(std::vector<std::string> text, std::vector<int> projectID, std::string searchTerm);

	//Returns a vector of projects which match the search term
	std::vector<Project> searchByProjectTitle(std::vector<Project> projects, std::string searchTerm);

	//Returns a vector of projects contain the actor  **Make use of constainsCast**
	std::vector<Project> searchByActor(std::vector <Project> projects, std::string actorName);

	//Returns a vector of ids in order
	std::vector<int> sortByText(std::vector<std::string> text, std::vector<int> IDs);

	//Returns a vector of projects in alphabetical order
	std::vector<Project> sortByTitle(std::vector<Project> projects);

	//Returns a vector of ids in date order
	std::vector<int> sortByDate(std::vector<std::string> dates, std::vector<int> IDs);

	//Returns a vector of projects in date order
	std::vector<Project> sortByDate(std::vector<Project>);

	std::vector<Project> projects;

	void add(Project p);

	void write();

private:
	int binarySearch(std::vector<std::string> arr, int start, int end, std::string target);
	void quickSort(std::vector<std::string> &arr, int start, int end);
	void swap(std::string &x, std::string &y);
	int partition(std::vector<std::string> &arr, int start, int end);
};

