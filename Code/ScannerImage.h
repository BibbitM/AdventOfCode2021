#pragma once

#include <istream>
#include <cassert>
#include <string_view>
#include <vector>

class ScannerImage
{
public:
	ScannerImage() = default;
	ScannerImage(int width, int height)
		: m_width(width), m_height(height)
	{
		m_pixels.resize(m_width * m_height);
	}

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
	bool Get(int x, int y) const { return IsValid(x, y) ? m_pixels[GetIndex(x, y)] : false; }
	void Set(int x, int y, bool value) { assert(IsValid(x, y)); m_pixels[GetIndex(x, y)] = value; }
	size_t GetEnhanced(int x, int y) const;
	size_t CountLitPixels() const;

	friend std::istream& operator>>(std::istream& in, ScannerImage& image);

private:
	bool IsValid(int x, int y) const
	{
		return x >= 0 && x < m_width&& y >= 0 && y < m_height;
	}
	size_t GetIndex(int x, int y) const
	{
		return static_cast<size_t>(x) + static_cast<size_t>(y) * static_cast<size_t>(m_width);
	}

	std::vector<bool> m_pixels;
	int m_width{};
	int m_height{};
};

std::istream& operator>>(std::istream& in, ScannerImage& image);

void AppendBoolVectorByString(std::vector<bool>& vec, std::string_view str);
