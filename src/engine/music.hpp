#pragma once

#include "raylib.h"
#include "res.hpp"

namespace ce
{
	class music
	{
	public:
		explicit music(const cmrc::file &file);
		~music();

		void play() const;
		auto is_playing() const -> bool;
		void stop() const;
		void pause() const;
		void resume() const;
		auto length() const -> float;
		auto played() const -> float;

		void update() const;

	private:
		Music r_music = {};
	};
}
