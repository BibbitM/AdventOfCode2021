#pragma once

#include <istream>
#include <string>
#include <string_view>
#include <vector>

class Polimer
{
public:
	Polimer() = default;
	Polimer(std::string_view polimer) : m_polimer(polimer) {}

	void Grow(const std::vector<std::pair<std::string, char>>& instructions);
	int CalculteMostSubLessQuantity() const;

	const std::string& AsString() const { return m_polimer; }
	size_t GetLength() const { return m_polimer.length(); }

private:
	std::string m_polimer;

	friend std::istream& operator>>(std::istream& in, Polimer& polimer);
};

std::istream& operator>>(std::istream& in, Polimer& polimer);
std::istream& operator>>(std::istream& in, std::vector<std::pair<std::string, char>>& instructions);
