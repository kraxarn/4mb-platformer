#include "asset/sound.hpp"

asset::sound::sound(const std::vector<unsigned char> &data)
{
	r_wave = LoadWaveFromMemory(".wav",
		data.data(), static_cast<int>(data.size()));

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
