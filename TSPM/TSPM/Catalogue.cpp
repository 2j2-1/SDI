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
	return std::vector<int>();
}

std::vector<Project> Catalogue::sortByTitle(std::vector<Project> projects)
{
	return std::vector<Project>();
}

std::vector<int> Catalogue::sortByDate(std::vector<std::string> dates, std::vector<int> IDs)
{
	return std::vector<int>();
}

std::vector<Project> Catalogue::sortByDate(std::vector<Project>)
{
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
}

void Catalogue::swap(std::string & x, std::string & y)
{
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

void Catalogue::add(Project p)
{
	projects.push_back(p);
}
