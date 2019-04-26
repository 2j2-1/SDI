#include "stdafx.h"
#include "DVD.h"


DVD::DVD()
{
}


DVD::~DVD()
{
}

std::string DVD::save()
{
	std::string data = PhysicalMedium::save();

	for (std::string aTrack : AudioTracksDubs)
	{
		data += aTrack + "\n";
	}

	data += ",\n";

	for (std::string sTrack : SubtitleLanguages)
	{
		data += sTrack + "\n";
	}

	data += ",\n";

	return data;
}
