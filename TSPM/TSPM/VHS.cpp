#include "stdafx.h"
#include "VHS.h"


VHS::VHS()
{
}


VHS::~VHS()
{
}

std::string VHS::save()
{
	std::string data = PhysicalMedium::save();

	data += AudioTrackLanguage + "\n";
	data += subtitlesLanguage + "\n";

	return data;
}
