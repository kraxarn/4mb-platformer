#include "clf/clfv2.hpp"
#include "clf/clfv3.hpp"

#include <iostream>
#include <filesystem>

auto main(int argc, char **argv) -> int
{
	std::filesystem::path out("assets/level/v3");
	for (const auto &dir : std::filesystem::directory_iterator("assets/level/v2"))
	{
		const auto &path = dir.path();
		auto level = clf_v2::parse(path);
		std::cout << path << " => ";

		std::filesystem::path out_path = out / path.stem();
		clf_v3::save(level, out_path);
		std::cout << out_path << std::endl;
	}

	return 0;
}
