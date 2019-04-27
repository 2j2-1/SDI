#pragma once
#include "PhysicalMedium.h"

#include <vector>

class DVD :
	public PhysicalMedium
{
public:
	DVD(int ID, std::string type, std::string title, std::string format, std::string frameAspect, std::string packaging);
	~DVD();

	std::vector<std::string> AudioTracksDubs;
	std::vector<std::string> SubtitleLanguages;
	std::vector<std::string> bonusFeatures;

	std::string save();
	void addAudioTrack(std::string track);
	void addSubtitleLanguage(std::string sub);
	void addBonusFeature(std::string feature);
};

