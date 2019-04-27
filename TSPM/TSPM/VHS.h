#pragma once
#include "PhysicalMedium.h"
class VHS :
	public PhysicalMedium
{
public:
	//VHS(int ID, std::string type, std::string title, std::string format, std::string frameAspect, std::string packaging, std::string AudioTrackLanguage, std::string subtitlesLanguage);

	VHS(int ID, std::string type, std::string title, std::string format, std::string frameAspect, std::string packaging, std::string AudioTrackLanguage, std::string subtitlesLanguage);
	~VHS();

	/*int ID;
	std::string type;
	std::string title;
	std::string format;
	std::string frameAspect;
	std::string packaging;*/

	std::string AudioTrackLanguage;
	std::string subtitlesLanguage;

	std::string save();
};

