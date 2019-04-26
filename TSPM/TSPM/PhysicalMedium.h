#pragma once
#include <string>
class PhysicalMedium
{
public:
	PhysicalMedium();
	~PhysicalMedium();

	int ID;
	std::string type;
	std::string title;
	std::string format;
	std::string frameAspect;
	std::string packaging;
};

