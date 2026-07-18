#include "Audio.h"

void PlayAudioSwing()
{
	String asset = Format(U"swing", Random(1, 2));
	AudioAsset(asset).stopAllShots();
	AudioAsset(asset).playOneShot();
}

void PlayAudio(const String& asset)
{
	AudioAsset(asset).stopAllShots();
	AudioAsset(asset).playOneShot();
}

