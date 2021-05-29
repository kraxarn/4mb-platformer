#pragma once

namespace ce
{
	class scene
	{
	public:
		virtual scene() = default;
		virtual ~scene() = delete;

		virtual void create() = 0;
		virtual void render() = 0;
		virtual void destroy() = 0;
	};
}
