#pragma once
#include "TuringGraph.h"
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>

class InvalidNameException
{
	friend std::ostream& operator<<(std::ostream& os, const InvalidNameException ex)
	{
		return os << "File with that name does not exsist!";
	}
};

class TuringParser
{
public:
	TuringGraph& Compile(const std::string& programFile);

	std::vector<char>& GetInput(const std::string& inputFile);

	int GetPosition(const std::string& inputFile);
private:
	TuringGraph program;
};
