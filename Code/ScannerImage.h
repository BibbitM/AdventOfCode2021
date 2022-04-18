#pragma once

class ScannerImage
{
public:
	ScannerImage() = default;
	ScannerImage(int width, int height)
		: m_width(width), m_height(height)
	{ }

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

private:
	int m_width{};
	int m_height{};
};
