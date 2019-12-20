#include "TuringMachine.h"
#include <iostream>
#include <iomanip>

TuringMachine::TuringMachine(TuringGraph& graph, std::vector<char> tape, int position) : graph(graph), tape(tape), pos(position)
{
}

bool TuringMachine::ExecuteProgram()
{
	int i = 0;
	while (true)
	{
		try
		{
			std::cout << "Step " << i++ << ": ";
			Move();
			system("pause");
		}
		catch (Finished & f)
		{
			return f.GetValid();
		}
	}
}

void TuringMachine::SetPos(int pos)
{
	this->pos = pos;
}

void TuringMachine::Move() 
{
	std::cout << *this << std::endl;
	char change;
	int move;
	
	graph.NextState(tape[pos], tape[pos], move);

	pos += move;
}

std::ostream& operator<<(std::ostream& os, const TuringMachine& tm)
{
	os << std::endl;
	for (unsigned i = 0; i < tm.tape.size() * 3; i++)
		os << '-';
	os << std::endl;
	for (unsigned i = 0; i < tm.tape.size(); i++)
		if (i == tm.pos)
			os << '|' << tm.tape[i] << '|';
		else
			os << ' ' << tm.tape[i] << ' ';
	os << std::endl;
	for (unsigned i = 0; i < tm.tape.size() * 3; i++)
		os << '-';

	return os;
}
