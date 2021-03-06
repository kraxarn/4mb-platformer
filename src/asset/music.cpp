#include "asset/music.hpp"

asset::music::music(const cmrc::file &file, const std::string &name)
	: file_name(std::string(name))
{
	r_music = LoadMusicStreamFromMemory(".xm",
		(unsigned char *) file.begin(),
		static_cast<int>(file.size()));

	r_music.looping = true;
}

asset::music::~music()
{
	if (is_playing())
	{
		stop();
	}

	UnloadMusicStream(r_music);
}

void asset::music::play() const
{
	PlayMusicStream(r_music);
}

auto asset::music::is_playing() const -> bool
{
	return IsMusicPlaying(r_music);
}

void asset::music::stop() const
{
	StopMusicStream(r_music);
}

void asset::music::pause() const
{
	PauseMusicStream(r_music);
}

void asset::music::resume() const
{
	ResumeMusicStream(r_music);
}

auto asset::music::length() const -> float
{
	return GetMusicTimeLength(r_music);
}

auto asset::music::played() const -> float
{
	return GetMusicTimePlayed(r_music);
}

void asset::music::update() const
{
	UpdateMusicStream(r_music);
}

auto asset::music::name() const -> std::string
{
	return file_name.substr(0, file_name.find('.'));
}
