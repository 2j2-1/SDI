#include "stdafx.h"
#include "VHS.h"





/*VHS::VHS(int ID, std::string type, std::string title, std::string format, std::string frameAspect, std::string packaging, std::string AudioTrackLanguage, std::string subtitlesLanguage)
{
	/*this->ID;
	this->type;
	this->title;
	this->format;
	this->frameAspect;
	this->packaging;

	this->AudioTrackLanguage = AudioTrackLanguage;
	this->subtitlesLanguage = subtitlesLanguage;

}*/

VHS::VHS(int ID, std::string type, std::string title, std::string format, std::string frameAspect, std::string packaging, std::string AudioTrackLanguage, std::string subtitlesLanguage)
	: PhysicalMedium(ID, type, title, format, frameAspect, packaging)
{
	/*this->ID;
	this->type;
	this->title;
	this->format;
	this->frameAspect;
	this->packaging;*/

	this->AudioTrackLanguage = AudioTrackLanguage;
	this->subtitlesLanguage = subtitlesLanguage;

}


VHS::~VHS()
{
}

std::string VHS::save()
{
	//std::string data = PhysicalMedium::save();
	std::string data = "";
	data = std::to_string(ID) + "\n";
	data += type + "\n";
	data += title + "\n";
	data += format + "\n";
	data += frameAspect + "\n";
	data += packaging + "\n";

	data += AudioTrackLanguage + "\n";
	data += subtitlesLanguage + "\n";
	data += ",\n";
	return data;
}
