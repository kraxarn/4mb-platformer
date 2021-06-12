#pragma once

#include <cstddef>
#include <functional>

namespace ce
{
	template<typename T>
	class vector2
	{
	public:
		vector2()
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
		}

		vector2(T x, T y)
		{
			this->x = x;
			this->y = y;
		}

		auto operator==(const vector2<T> &vec) const -> bool
		{
			return vec.x == x && vec.y == y;
		}

		auto operator*(T value) const -> vector2<T>
		{
			return vector2<T>(x * value, y * value);
		}

		auto operator+(T value) const -> vector2<T>
		{
			return vector2<T>(x + value, y + value);
		}

		T x;
		T y;
	};

	using vector2f = ce::vector2<float>;
	using vector2i = ce::vector2<int>;
}

namespace std
{
	template<typename T>
	struct hash<ce::vector2<T>>
	{
		auto operator()(const ce::vector2<T> &key) const -> std::size_t
		{
			return std::hash<T>()(key.x) ^ (std::hash<T>()(key.y) << 1);
		}
	};
}
