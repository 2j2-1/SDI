#include "stdafx.h"
#include "VHS.h"





VHS::VHS(int ID, std::string type, std::string title, std::string format, std::string frameAspect, std::string packaging, std::string AudioTrackLanguage, std::string subtitlesLanguage)
{
	PhysicalMedium::PhysicalMedium(ID, type, title, format, frameAspect, packaging);

	this->AudioTrackLanguage = AudioTrackLanguage;
	this->subtitlesLanguage = subtitlesLanguage;

}

VHS::~VHS()
{
}

std::string VHS::save()
{
	std::string data = PhysicalMedium::save();

	data += AudioTrackLanguage + "\n";
	data += subtitlesLanguage + "\n";
	data += ",\n";
	return data;
}
