#pragma once

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

		T x;
		T y;
	};

	using vector2i = ce::vector2<int>;
	using vector2f = ce::vector2<float>;
}
