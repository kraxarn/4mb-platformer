#include "image.hpp"

ce::image::image(const cmrc::file &file)
	: Image(LoadImageFromMemory(".png",
	(const unsigned char *) file.cbegin(),
	static_cast<int>(file.size())))
{
}

ce::image::image(const Image &img)
	: Image(img)
{
}
