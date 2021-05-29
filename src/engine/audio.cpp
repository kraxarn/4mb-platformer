#include "audio.hpp"

ce::audio::audio()
{
	InitAudioDevice();
}

ce::audio::~audio()
{
	CloseAudioDevice();
}
