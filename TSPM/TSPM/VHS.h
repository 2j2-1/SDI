#pragma once
#include "PhysicalMedium.h"
class VHS :
	public PhysicalMedium
{
public:
	VHS();
	~VHS();

	std::string AudioTrackLanguage;
	std::string subtitlesLanguage;
};

