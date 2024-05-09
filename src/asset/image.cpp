#include "image.hpp"

asset::image::image(const std::vector<unsigned char> &data)
	: Image(LoadImageFromMemory(".png",
		data.data(), static_cast<int>(data.size())))
{
}

asset::image::image(const Image &img)
	: Image(img)
{
}
