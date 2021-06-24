#include "input.hpp"

ce::input::input()
{
	keyboard = {
		{ce::key::left, KEY_LEFT},
		{ce::key::right, KEY_RIGHT},
		{ce::key::up, KEY_UP},
		{ce::key::down, KEY_DOWN},
		{ce::key::enter, KEY_ENTER},
		{ce::key::jump, KEY_UP},
		{ce::key::pause, KEY_ESCAPE},
	};

	if (IsGamepadAvailable(0))
	{
		std::cout << "Gamepad connected: "
			<< get_gamepad_name() << std::endl;
		gamepad_index = 0;

		gamepad = {
			{ce::key::left, GAMEPAD_BUTTON_LEFT_FACE_LEFT},
			{ce::key::right, GAMEPAD_BUTTON_LEFT_FACE_RIGHT},
			{ce::key::up, GAMEPAD_BUTTON_LEFT_FACE_UP},
			{ce::key::down, GAMEPAD_BUTTON_LEFT_FACE_DOWN},
			{ce::key::enter, GAMEPAD_BUTTON_RIGHT_FACE_DOWN},
			{ce::key::jump, GAMEPAD_BUTTON_RIGHT_FACE_DOWN},
			{ce::key::pause, GAMEPAD_BUTTON_MIDDLE_RIGHT},
		};
	}
}

auto ce::input::is_pressed(ce::key key) const -> bool
{
	return IsKeyPressed(keyboard.at(key))
		|| (gamepad_index >= 0
			&& IsGamepadButtonPressed(gamepad_index, gamepad.at(key)));
}

auto ce::input::is_down(ce::key key) const -> bool
{
	return IsKeyDown(keyboard.at(key))
		|| (gamepad_index >= 0
			&& IsGamepadButtonDown(gamepad_index, gamepad.at(key)));
}

auto ce::input::get_gamepad_name() -> std::string
{
	const char *name = nullptr;
	return IsGamepadName(0, name)
		? std::string(name)
		: std::string();
}
