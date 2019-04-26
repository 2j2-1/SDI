#include "stdafx.h"
#include "PhysicalMedium.h"


PhysicalMedium::PhysicalMedium()
{
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
