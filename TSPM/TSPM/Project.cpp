#include "stdafx.h"
#include "Project.h"


Project::Project()
{
}


Project::~Project()
{
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
