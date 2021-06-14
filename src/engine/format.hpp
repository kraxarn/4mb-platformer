#pragma once

#include "engine/vector2.hpp"

#include <string>

namespace ce
{
	class fmt
	{
	public:
		template<typename Format>
		static auto format(const Format &fmt) -> std::string
		{
			return fmt;
		}

		template<typename Format, typename Arg, typename... Args>
		static auto format(const Format &fmt, const Arg &arg, Args &&... args) -> std::string
		{
			return format(collect(fmt, arg), args...);
		}

	private:
		template<typename Format>
		static auto collect(const Format &fmt, const std::string &arg) -> std::string
		{
			auto str = std::string(fmt);
			auto index = str.find("{}");
			if (index == std::string::npos)
			{
				return str;
			}
			return str.replace(index, 2, arg);
		}

		template<typename Format, typename Arg>
		static auto collect(const Format &fmt, const Arg &arg) -> std::string
		{
			return collect(fmt, std::to_string(arg));
		}

		template<typename Format>
		static auto collect(const Format &fmt, const char *arg) -> std::string
		{
			return collect(fmt, std::string(arg));
		}

		template<typename Format, typename VT>
		static auto collect(const Format &fmt, const ce::vector2<VT> &arg) -> std::string
		{
			return collect(fmt, format("{} {}", arg.x, arg.y));
		}
	};
}
