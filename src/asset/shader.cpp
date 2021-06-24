#include "shader.hpp"

asset::shader::shader(const cmrc::file &file)
{
	r_shader = LoadShaderFromMemory(nullptr, (const char *) file.begin());
}

asset::shader::~shader()
{
	UnloadShader(r_shader);
}

void asset::shader::begin()
{
	BeginShaderMode(r_shader);
}

void asset::shader::end()
{
	EndShaderMode();
}
