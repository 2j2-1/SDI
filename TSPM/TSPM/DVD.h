#pragma once
#include "PhysicalMedium.h"

#include <vector>

class DVD :
	public PhysicalMedium
{
public:
	DVD();
	~DVD();

	std::vector<std::string> AudioTracksDubs;
	std::vector<std::string> SubtitleLanguages;
	std::vector<std::string> bonusFeatures;

	std::string save();
};

