#pragma once

#include "raylib.h"

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

		explicit vector2(Vector2 r_vec)
		{
			x = r_vec.x;
			y = r_vec.y;
		}

		template<typename R>
		auto to() const -> vector2<R>
		{
			return {
				static_cast<R>(x),
				static_cast<R>(y)
			};
		}

		auto to_r_vec() const -> Vector2
		{
			auto v = to<float>();
			return {
				v.x,
				v.y,
			};
		}

		auto operator*(T value) const -> vector2<T>
		{
			return vector2<T>(x * value, y * value);
		}

		auto operator/(T value) const -> vector2<T>
		{
			return vector2<T>(x / value, y / value);
		}

		auto operator+(const vector2<T> &value) const -> vector2<T>
		{
			return vector2<T>(x + value.x, y + value.y);
		}

		auto operator+(T value) const -> vector2<T>
		{
			return vector2<T>(x + value, y + value);
		}

		auto operator-(T value) const -> vector2<T>
		{
			return vector2<T>(x - value, y - value);
		}

		T x;
		T y;
	};

	using vector2f = ce::vector2<float>;
	using vector2i = ce::vector2<int>;
}
