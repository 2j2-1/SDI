#include "stdafx.h"
#include "PhysicalMedium.h"


PhysicalMedium::PhysicalMedium()
{
}

PhysicalMedium::PhysicalMedium(int ID, std::string type, std::string title, std::string format, std::string frameAspect, std::string packaging)
{
	this->ID=ID;
	this->type=type;
	this->title=title;
	this->format=format;
	this->frameAspect=frameAspect;
	this->packaging=packaging;
}

PhysicalMedium::~PhysicalMedium()
{
}

std::string PhysicalMedium::save()
{
	std::string data;

	data = std::to_string(ID) + "\n";
	data += type + "\n";
	data += title + "\n";
	data += format + "\n";
	data += frameAspect + "\n";
	data += packaging + "\n";

	return data;
}
