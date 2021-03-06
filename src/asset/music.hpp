#pragma once

#include "raylib.h"
#include "res.hpp"

namespace asset
{
	class music
	{
	public:
		explicit music(const cmrc::file &file, const std::string &name);
		~music();

		void play() const;
		auto is_playing() const -> bool;
		void stop() const;
		void pause() const;
		void resume() const;
		auto length() const -> float;
		auto played() const -> float;

		void update() const;

		auto name() const -> std::string;

	private:
		Music r_music = {};
		std::string file_name;
	};
}
