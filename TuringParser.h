#ifndef  _TURING_PARSER_GUARD_
#define _TURING_PARSER_GUARD

#include "TuringGraph.h"

#include <string>
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
#endif
