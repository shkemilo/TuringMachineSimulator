#include "TuringGraph.h"
#include <vector>
#include <iostream>
#include <iomanip>

void TuringGraph::AddNode(int q)
{
	for (int i = 0; i < nodes.size(); i++)
		if (q == nodes[i]->q)
			return;

	Node* temp = new Node(q);
	if (curr == nullptr)
		curr = temp;

	nodes.push_back(temp);
}

void TuringGraph::RemoveNode(int q)
{
	if (q > nodes.size())
		throw std::exception("Node does not exsist!");

	nodes.erase(nodes.begin() + q);
}

void TuringGraph::AddEdge(int srcNode, char input, char destNode, char change, int move)
{
	if (move > 1 || move < -1)
		throw std::exception("Unvalid move of Turing machine!");

	if (destNode == '+')
		destNode = -1;
	else if (destNode == '-')
		destNode = -2;
	else
		destNode -= '0';

	int index = convert(input);

	nodes[srcNode]->edges[index] = Edge(destNode, change, move);
}

void TuringGraph::RemoveEdge(int srcNode, int destNode)
{
	for (int i = 0; i < nodes[srcNode]->edges.size(); i++)
		if (nodes[srcNode]->edges[i].index == destNode)
			nodes[srcNode]->edges.erase(nodes[srcNode]->edges.begin() + i);
}

bool TuringGraph::AreConnected(int srcNode, int destNode) const
{
	for (int i = 0; i < nodes[srcNode]->edges.size(); i++)
		if (nodes[srcNode]->edges[i].index == destNode)
			return true;
	return false;
}

void TuringGraph::NextState(char input, char& change, int& move)
{
	Edge& temp = curr->edges[convert(input)];
	move = temp.move;
	change = temp.change;

	if (temp.index == -1)
		throw Finished(true);
	if (temp.index == -2)
		throw Finished(false);

	curr = nodes[temp.index];
}

bool TuringGraph::IsValid() const
{
	int children = 0;
	for (unsigned i = 0; i < nodes[0]->edges.size(); i++)
		if (nodes[0]->edges[i].change != 'e')
			children++;

	for (unsigned i = 1; i < nodes.size(); i++)
	{
		int currChildern = 0;
		for (unsigned j = 0; j < nodes[i]->edges.size(); j++)
			if (nodes[i]->edges[j].change != 'e')
				currChildern++;

		if (currChildern != children)
			return false;
	}

	return true;
}

void TuringGraph::Destroy()
{
	destroy();
}

TuringGraph::~TuringGraph()
{
	destroy();
}

int TuringGraph::convert(char c) const
{
	switch (c)
	{
	case 'b':
		return 0;
	case '0':
		return 1;
	case '1':
		return 2;
	case '+':
		return -1;
	case '-':
		return -2;
	default:
		throw std::exception("This should not happen!");
	}
}

char TuringGraph::convert(int i) const
{
	switch (i)
	{
	case 0:
		return 'b';
	case 1:
		return '0';
	case 2:
		return '1';
	default:
		throw std::exception("This should not happen...");
	}
}

void TuringGraph::destroy()
{
	while (!nodes.empty())
	{
		delete nodes.back();
		nodes.pop_back();
	}

	curr = nullptr;
}

std::ostream& operator<<(std::ostream& os, const TuringGraph& tg)
{
	for (int i = 0; i < tg.nodes.size(); i++)
		for (int j = 0; j < tg.nodes[i]->edges.size(); j++)
		{
			char temp;
			if (tg.nodes[i]->edges[j].index == -2)
				temp = '-';
			else if (tg.nodes[i]->edges[j].index == -1)
				temp = '+';
			else
				temp = tg.nodes[i]->edges[j].index + '0';

			os << "f(q" << i << ',' << tg.convert(j) << ")=(q" 
				<< temp << ',' << tg.nodes[i]->edges[j].change 
				<< ',' << std::setw(2) << std::setfill('+') << tg.nodes[i]->edges[j].move << ')' << std::endl;
		}

	return os;
}
