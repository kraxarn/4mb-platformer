#include "music.hpp"

ce::music::music(const cmrc::file &file)
{
	r_music = LoadMusicStreamFromMemory(".xm",
		(unsigned char *) file.begin(),
		static_cast<int>(file.size()));
	r_music.looping = true;
}

ce::music::~music()
{
	if (is_playing())
	{
		stop();
	}

	UnloadMusicStream(r_music);
}

void ce::music::play() const
{
	PlayMusicStream(r_music);
}

auto ce::music::is_playing() const -> bool
{
	return IsMusicPlaying(r_music);
}

void ce::music::stop() const
{
	StopMusicStream(r_music);
}

void ce::music::pause() const
{
	PauseMusicStream(r_music);
}

void ce::music::resume() const
{
	ResumeMusicStream(r_music);
}

auto ce::music::length() const -> float
{
	return GetMusicTimeLength(r_music);
}

auto ce::music::played() const -> float
{
	return GetMusicTimePlayed(r_music);
}

void ce::music::update() const
{
	UpdateMusicStream(r_music);
	SetMusicPitch(r_music, 1.F);
}
