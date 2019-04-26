#include "stdafx.h"
#include "Catalogue.h"



Catalogue::Catalogue()
{
}


Catalogue::~Catalogue()
{
}

std::vector<int> Catalogue::searchByText(std::vector<std::string> text, std::vector<int> projectID, std::string searchTerm)
{
	return std::vector<int>();
}

std::vector<Project> Catalogue::searchByProjectTitle(std::vector<Project> projects, std::string searchTerm)
{
	return std::vector<Project>();
}

std::vector<Project> Catalogue::searchByActor(std::vector<Project> projects, std::string actorName)
{
	return std::vector<Project>();
}

std::vector<int> Catalogue::sortByText(std::vector<std::string> text, std::vector<int> IDs)
{
	std::vector<std::pair<int, std::string>> oldIndexes;
	std::vector<std::pair<int, std::string>> newIndexes;

	for (int i = 0; i < IDs.size(); i++)
	{
		oldIndexes.push_back(std::make_pair(IDs[i], text[i]));
	}

	int start = 0;
	int end = text.size() - 1;
	quickSort(text, start, end);

	for (int i = 0; i < text.size(); i++)
	{
		newIndexes.push_back(std::make_pair(i, text[i]));
	}

	int count = 0;
	std::vector<int> ret;
	bool complete = false;
	while (!complete)
	{
		for (int i = 0; i < newIndexes.size(); i++)
		{
			if (newIndexes[count].second == oldIndexes[i].second)
			{
				ret.push_back(oldIndexes[i].first);
				count += 1;
			}
		}
		if (count == newIndexes.size())
		{
			complete = true;
		}
	}


	return ret;
}

std::vector<Project> Catalogue::sortByTitle(std::vector<Project> projects)
{
	std::vector<std::string> titles;
	std::vector<int> indexes;
	for (int i = 0; i < projects.size(); i++)
	{
		titles.push_back(projects[i].title);	// list of all project titles
		indexes.push_back(i);					// list with number of projects
	}

	std::vector<int> newIndexes = sortByText(titles, indexes);

	std::vector<Project> ret;

	for (int i : newIndexes)
	{
		ret.push_back(projects[i]);
	}

	return std::vector<Project>();
}

std::vector<int> Catalogue::sortByDate(std::vector<std::string> dates, std::vector<int> IDs)
{
	return std::vector<int>();
}

std::vector<Project> Catalogue::sortByDate(std::vector<Project> projects)
{
	std::vector<std::string> dates;
	std::vector<int> indexes;
	for (int i = 0; i < projects.size(); i++)
	{
		//dates.push_back(projects[i].releaseDate)
	}

	return std::vector<Project>();
}

int Catalogue::binarySearch(std::vector<std::string> arr, int start, int end, std::string target)
{
	if (end >= start) {
		int mid = start + (end - start) / 2;

		// If element in middle 
		if (arr[mid] == target)
			return mid;

		// If in left half
		if (arr[mid] > target)
			return binarySearch(arr, start, mid - 1, target);

		// Else in right half
		return binarySearch(arr, mid + 1, end, target);
	}

	// Not present
	return -1;
}

void Catalogue::quickSort(std::vector<std::string>& arr, int start, int end)
{
	if (start < end) {
		int p = 0;
		p = partition(arr, start, end);
		//Quick sorts each partition recursively
		quickSort(arr, start, p - 1);
		quickSort(arr, p + 1, end);
	}
}

void Catalogue::swap(std::string & x, std::string & y)
{
	std::string temp = x;
	x = y;
	y = temp;
}

int Catalogue::partition(std::vector<std::string>& arr, int start, int end)
{
	int pivot = start + ((end - start) / 2);
	std::string pivotVal = arr[pivot];
	swap(arr[pivot], arr[end]);
	int store = start;

	for (int i = start; i < end; i++) {
		if (arr[i] < pivotVal) {
			swap(arr[i], arr[store]);
			store += 1;
		}
	}

	swap(arr[store], arr[end]);

	return store;
}
