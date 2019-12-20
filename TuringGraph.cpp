#include "TuringGraph.h"

#include <vector>
#include <iostream>
#include <iomanip>

void TuringGraph::AddNode(int q)
{
	for (unsigned i = 0; i < nodes.size(); i++)
		if (q == nodes[i]->q)
			return;

	Node* temp = new Node(q);
	if (curr == nullptr)
		curr = temp;

	nodes.push_back(temp);
}

void TuringGraph::RemoveNode(int q)
{
	if (q > nodes.size() || q < 0)
		throw std::exception("Node does not exsist!");

	for (unsigned i = 0; i < nodes.size(); i++)
		RemoveEdge(i, q);

	delete nodes[q];
	nodes.erase(nodes.begin() + q);
}

void TuringGraph::AddEdge(int srcNode, char input, char destNode, char change, int move)
{
	if (move > 1 || move < -1)
		throw std::exception("Unvalid move of Turing machine!");

	if (destNode == '-')
		destNode = -1;
	else if (destNode == '+')
		destNode = -2;
	else
		destNode -= '0';

	int index = convert(input);

	nodes[srcNode]->edges[index] = Edge(destNode, change, move);
}

void TuringGraph::RemoveEdge(int srcNode, int destNode)
{
	for (unsigned i = 0; i < nodes[srcNode]->edges.size(); i++)
		if (nodes[srcNode]->edges[i].index == destNode)
			nodes[srcNode]->edges.erase(nodes[srcNode]->edges.begin() + i);
}

bool TuringGraph::AreConnected(int srcNode, int destNode) const
{
	for (unsigned i = 0; i < nodes[srcNode]->edges.size(); i++)
		if (nodes[srcNode]->edges[i].index == destNode)
			return true;
	return false;
}

void TuringGraph::NextState(char input, char& change, int& move)
{
	Edge& temp = curr->edges[convert(input)];
	move += temp.move;
	change = temp.change;

	if (temp.index == -1)
		throw Finished(true);
	if (temp.index == -2)
		throw Finished(false);

	curr = nodes[temp.index];
}

bool TuringGraph::IsValid() const
{
	int children = numberOfChildren(*nodes[0]);

	for (unsigned i = 1; i < nodes.size(); i++)
	{
		int currChildern = numberOfChildren(*nodes[i]);

		if (currChildern != children)
			return false;
	}

	return true;
}

void TuringGraph::Destroy()
{
	destroy();
}

void TuringGraph::Reset()
{
	curr = nodes[0];
}

TuringGraph::~TuringGraph()
{
	destroy();
}

int TuringGraph::numberOfChildren(const Node& node)
{
	int children = 0;
	for (unsigned i = 0; i < node.edges.size(); i++)
		if (node.edges[i].change != 'e')
			children++;

	return children;
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
		throw std::exception("This should not happen...");
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
	for (unsigned i = 0; i < tg.nodes.size(); i++)
		for (unsigned j = 0; j < tg.nodes[i]->edges.size(); j++)
		{
			char temp;
			if (tg.nodes[i]->edges[j].index == -2)
				temp = '-';
			else if (tg.nodes[i]->edges[j].index == -1)
				temp = '+';
			else
				temp = tg.nodes[i]->edges[j].index + '0';

			os << "f(q" << i << ',' << tg.convert((int)j) << ")=(q" 
				<< temp << ',' << tg.nodes[i]->edges[j].change 
				<< ',' << std::setw(2) << std::setfill('+') 
				<< tg.nodes[i]->edges[j].move << ')' << std::endl;
		}

	return os;
}
