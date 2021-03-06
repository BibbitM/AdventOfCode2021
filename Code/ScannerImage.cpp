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
	if (m_outPixel)
		return std::numeric_limits<size_t>::max();

	size_t count = 0;
	return std::accumulate(m_pixels.begin(), m_pixels.end(), count);
}

ScannerImage ScannerImage::Enhance(const std::vector<bool>& enhacementAlgorithm) const
{
	ScannerImage enhancedImage{ m_width + 4, m_height + 4 };

	enhancedImage.SetOutPixel(enhacementAlgorithm[m_outPixel ? 511 : 0]);

	for (int x = 0; x < enhancedImage.m_width; ++x)
	{
		for (int y = 0; y < enhancedImage.m_height; ++y)
		{
			bool enhancedPixel = enhacementAlgorithm[GetEnhanced(x - 2, y - 2)];
			enhancedImage.Set(x, y, enhancedPixel);
		}
	}

	return enhancedImage;
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

std::ostream& operator<<(std::ostream& out, const ScannerImage& image)
{
	std::string line;
	line.resize(image.GetWidth());

	for (int y = 0; y < image.GetHeight(); ++y)
	{
		for (int x = 0; x < image.GetWidth(); ++x)
		{
			line[x] = image.Get(x, y) ? '#' : '.';
		}
		out << line << '\n';
	}

	return out;

}

void AppendBoolVectorByString(std::vector<bool>& vec, std::string_view str)
{
	vec.reserve(vec.size() + str.length());
	for (char c : str)
		vec.push_back(c == '#');
}
