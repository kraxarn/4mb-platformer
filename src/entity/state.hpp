#pragma once

namespace entity
{
	class state
	{
	public:
		state() = default;

		auto get_coins() const -> int;
		void add_coins(int amount);

		auto get_gems() const -> int;
		void set_gems(int value);
		void add_gems(int amount);

	private:
		/** Coins total */
		int coins = 0;

		/** Gems collected for current level */
		int gems = 0;
	};
}
