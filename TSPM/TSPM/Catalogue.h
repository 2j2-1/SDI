#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Project.h"
#include "VHS.h"
#include "DVD.h"


class Catalogue
{
public:
	Catalogue();
	~Catalogue();

	//Returns a vector of ids which match the search term
	std::vector<int> searchByText(std::vector<std::string> text, std::string searchTerm);

	//Returns a vector of projects which match the search term
	std::vector<Project> searchByProjectTitle(std::vector<Project> projects, std::string searchTerm);

	//Returns a vector of projects that contain the actor  **Make use of constainsCast**
	std::vector<Project> searchByActor(std::vector <Project> projects, std::string actorName);

	//Returns a vector of ids in alphabetical order
	std::vector<int> sortByText(std::vector<std::string> text, std::vector<int> IDs);

	//Returns a vector of projects in alphabetical order
	std::vector<Project> sortByTitle(std::vector<Project> projects);

	//Returns a vector of ids in date order
	std::vector<int> sortByDate(std::vector<std::string> dates, std::vector<int> IDs);

	//Returns a vector of projects in date order
	std::vector<Project> sortByDate(std::vector<Project> projects);

	void add(Project p);

	void update(Project p);

	std::vector<Project> projects;

	void read();

	void write();

	void updateDirectories();

	void deleteProject(int projectID);
	void deleteProjectFile(int projectID);

	Project parse(std::string filePath, int projectID);

private:
	static void quickSort(std::vector<std::string> &arr, int start, int end);
	static void swap(std::string &x, std::string &y);
	static int partition(std::vector<std::string> &arr, int start, int end);
};

