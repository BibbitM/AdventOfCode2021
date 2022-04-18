#include "pch.h"
#include "ScannerImage.h"

#include <cassert>
#include <numeric>
#include <string>

size_t ScannerImage::GetEnhanced(int centerX, int centerY) const
{
	size_t enhanced = 0;
	for (int y = centerY - 1; y <= centerY + 1; ++y)
		for (int x = centerX - 1; x <= centerX + 1; ++x)
			enhanced = (enhanced << 1) | static_cast<size_t>(Get(x, y));
	return enhanced;
}

size_t ScannerImage::CountLitPixels() const
{
	size_t count = 0;
	return std::accumulate(m_pixels.begin(), m_pixels.end(), count);
}

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
