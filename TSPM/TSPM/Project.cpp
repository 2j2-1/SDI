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
	/*When talking about the algorythms used for searches talk about how linear search was used because there does not tend to be a large number of crew memmbers */

	for (CrewMember c : crewMembers)
	{
		if (c.name == name && c.role == role)
		{
			return true;
		}
	}
	return false;
}
