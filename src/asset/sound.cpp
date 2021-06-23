#include "asset/sound.hpp"

asset::sound::sound(const cmrc::file &file)
{
	r_wave = LoadWaveFromMemory(".wav",
		(unsigned char *) file.begin(),
		static_cast<int>(file.size()));

	r_sound = LoadSoundFromWave(r_wave);
}

asset::sound::~sound()
{
	UnloadWave(r_wave);
	UnloadSound(r_sound);
}

void asset::sound::play()
{
	PlaySound(r_sound);
}
