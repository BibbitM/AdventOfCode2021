#include "pch.h"
#include "ScannerImage.h"

#include <cassert>
#include <string>

std::istream& operator>>(std::istream& in, ScannerImage& image)
{
	std::string line;
	while (std::getline(in, line))
	{
		if (image.m_width == 0 && image.m_height == 0)
			image.m_width = static_cast<int>(line.length());
		else
			assert(image.m_width == line.length());
		++image.m_height;

		AppendBoolVectorByString(image.m_pixels, line);
	}
	assert(image.m_pixels.size() == image.m_width * image.m_height);
	return in;
}

void AppendBoolVectorByString(std::vector<bool>& vec, std::string_view str)
{
	vec.reserve(vec.size() + str.length());
	for (char c : str)
		vec.push_back(c == '#');
}
