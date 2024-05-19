#include "keymap.hpp"

keymap::keymap()
{
	add("left", chirp::keyboard_key::left);
	add("left", chirp::gamepad_button::left_face_left);

	add("right", chirp::keyboard_key::right);
	add("right", chirp::gamepad_button::left_face_right);

	add("up", chirp::keyboard_key::up);
	add("up", chirp::gamepad_button::left_face_up);

	add("down", chirp::keyboard_key::down);
	add("down", chirp::gamepad_button::left_face_down);

	add("enter", chirp::keyboard_key::enter);
	add("enter", chirp::gamepad_button::right_face_down);

	add("jump", chirp::keyboard_key::up);
	add("jump", chirp::gamepad_button::right_face_down);

	add("pause", chirp::keyboard_key::escape);
	add("pause", chirp::gamepad_button::middle_right);
}
