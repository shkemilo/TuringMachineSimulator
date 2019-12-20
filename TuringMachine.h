#pragma once
#include "TuringGraph.h"
#include <iostream>

class TuringMachine
{
public:
	TuringMachine(TuringGraph& graph, std::vector<char> tape, int position = 2);

	bool ExecuteProgram();

	void SetPos(int pos);

	void Move();

	friend std::ostream& operator<<(std::ostream& os, const TuringMachine& tm);

private:
	TuringGraph& graph;

	std::vector<char> tape;
	int pos = 0;
};

