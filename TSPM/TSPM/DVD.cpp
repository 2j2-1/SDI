#include "stdafx.h"
#include "DVD.h"


DVD::DVD(int ID, std::string type, std::string title, std::string format, std::string frameAspect, std::string packaging)
	: PhysicalMedium(ID, type, title, format, frameAspect, packaging)
{
	
}


DVD::~DVD()
{
}

std::string DVD::save()
{
	std::string data = PhysicalMedium::save();

	//Adds the vector of audio track languages to the file a comma represents the end of the audio track languages in the file
	for (std::string aTrack : AudioTracksDubs)
	{
		data += aTrack + "\n";
	}

	data += ",\n";

	//Adds the vector of Subtitle languages to the file a comma represents the end of the Subtitle languages in the file
	for (std::string sTrack : SubtitleLanguages)
	{
		data += sTrack + "\n";
	}

	data += ",\n";

	//Adds the vector of bonus features to the file a comma represents the end of the features in the file
	for (std::string feature : bonusFeatures)
	{
		data += feature + "\n";
	}
	
	data += ",\n";


	return data;
}

void DVD::addAudioTrack(std::string track)
{
	AudioTracksDubs.push_back(track);
}

void DVD::addSubtitleLanguage(std::string sub)
{
	SubtitleLanguages.push_back(sub);
}

void DVD::addBonusFeature(std::string feature)
{
	bonusFeatures.push_back(feature);
}
