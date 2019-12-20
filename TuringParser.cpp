#include "TuringParser.h"
#include <sstream>

TuringGraph& TuringParser::Compile(const std::string& programName)
{
	program.Destroy();

	std::ifstream programInput(programName);
	if (!programInput.is_open())
		throw InvalidNameException();

	std::string line;
	while (std::getline(programInput, line))
	{
		int q, move;
		char input, qNext, change;
		int result = sscanf(line.c_str(), "f(q %d, %c) = (q %c, %c, %d)", &q, &input, &qNext, &change, &move);
		if (result != 5)
			throw std::exception("Compile error: Invalid program format!");


		program.AddNode(q);
		program.AddEdge(q, input, qNext, change, move);
	}

	if (!program.IsValid())
		throw std::exception("Compile error: Not all inputs specified!");

	programInput.close();
	return program;
}

std::vector<char>& TuringParser::GetInput(const std::string& inputName)
{
	std::ifstream input(inputName);
	if (!input.is_open())
		throw InvalidNameException();

	std::string buffer;
	std::getline(input, buffer);

	std::vector<char> temp;
	std::istringstream iss(buffer);
	char c;
	while (iss >> c)
	{
		if (c != '0' && c != '1' && c != 'b')
			throw std::exception("Invalid input: Tape has invalid symbols!");
		temp.push_back(c);
	}

	if (temp.size() == 0)
		throw std::exception("Invalid input: Tape cant be empty!");
	if (temp.back() != 'b')
		throw std::exception("Invalid input: Tape must end with b character!");

	input.close();
	return *(new std::vector<char>(temp));
}

int TuringParser::GetPosition(const std::string& inputFile)
{
	std::ifstream input(inputFile);
	if (!input.is_open())
		throw InvalidNameException();

	std::string buffer;
	std::getline(input, buffer);

	int position = -1;
	input >> position;

	if (position == -1)
		throw std::exception("Invalid input: Initial position of head is not specified!");

	return position;
}
