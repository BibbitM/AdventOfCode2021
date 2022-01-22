#pragma once

#include <istream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

struct PolimerPair
{
	union
	{
		char chars[2];
		short value;
	};

	bool operator==(const PolimerPair& other) const { return value == other.value; }
	bool operator==(std::string_view str) const { return str[0] == chars[0] && str[1] == chars[1]; }

	PolimerPair(std::string_view str)
	{
		chars[0] = str[0];
		chars[1] = str[1];
	}
	PolimerPair(char first, char second)
	{
		chars[0] = first;
		chars[1] = second;
	}
};

template<>
struct std::hash<PolimerPair>
{
	std::size_t operator()(const PolimerPair& pair) const noexcept
	{
		return std::hash<short>{}(pair.value);
	}
};

class Polimer
{
public:
	Polimer() = default;
	Polimer(std::string_view polimer) { SetPolimer(polimer); }
	void SetPolimer(std::string_view polimer);

	void Grow(const std::vector<std::pair<PolimerPair, char>>& instructions);
	size_t CalculteMostSubLessQuantity() const;
	size_t GetLength() const;

private:
	std::unordered_map<PolimerPair, size_t> m_pairs;
	std::unordered_map<char, size_t> m_chars;
};

std::istream& operator>>(std::istream& in, Polimer& polimer);
std::istream& operator>>(std::istream& in, std::vector<std::pair<PolimerPair, char>>& instructions);
