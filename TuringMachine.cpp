#include "TuringMachine.h"

#include <iostream>
#include <vector>

TuringMachine::TuringMachine(TuringGraph& graph, std::vector<char> tape, int position) : graph(graph), tape(tape), pos(position)
{
}

bool TuringMachine::ExecuteProgram(std::ostream& os)
{
	int i = 0;
	while (true)
	{
		try
		{
			os << "Step " << i++ << ": ";
			Move(os);
			system("pause");
		}
		catch (Finished & f)
		{
			os << "End state: " << *this << std::endl;
			graph.Reset();
			return f.GetValid();
		}
	}
}

void TuringMachine::Move(std::ostream& os) 
{
	os << *this << std::endl;
	
	graph.NextState(tape[pos], tape[pos], pos);
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
