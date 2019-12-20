#pragma once
#include "TuringGraph.h"

#include <vector>
#include <iostream>

class TuringMachine
{
public:
	TuringMachine(TuringGraph& graph, std::vector<char> tape, int position = 2);

	bool ExecuteProgram(std::ostream& os = std::cout);

	void Move(std::ostream& os = std::cout);

	friend std::ostream& operator<<(std::ostream& os, const TuringMachine& tm);

private:
	TuringGraph& graph;

	std::vector<char> tape;
	int pos = 0;
};

