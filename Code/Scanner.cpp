#include "pch.h"
#include "Scanner.h"

#include <sstream>
#include <string>

std::istream& operator>>(std::istream& in, Scanner& scanner)
{
	std::string line;
	std::getline(in, line); //< Skip header "--- scanner 0 ---".
	while (std::getline(in, line) && !line.empty())
	{
		std::istringstream inLine(line);
		inLine >> scanner.m_beacons.emplace_back();
	}

	return in;
}
