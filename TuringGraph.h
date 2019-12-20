#pragma once
#include <vector>
#include <iostream>

class Finished
{
public:
	Finished(bool valid) : valid(valid) { }

	bool GetValid() { return valid; }

private:
	bool valid;
};

class TuringGraph
{
public:
	TuringGraph() = default;
	TuringGraph(const TuringGraph&) = delete;
	TuringGraph(TuringGraph&&) = delete;

	TuringGraph& operator=(const TuringGraph&) = delete;
	TuringGraph& operator=(TuringGraph&&) = delete;

	void AddNode(int q);

	void RemoveNode(int q);

	void AddEdge(int srcNode, char input, char destNode, char change, int move);

	void RemoveEdge(int srcNode, int destNode);

	bool AreConnected(int srcNode, int destNode) const;

	void NextState(char input, char& change, int& move);

	bool IsValid() const;

	void Destroy();

	~TuringGraph();

	friend std::ostream& operator<<(std::ostream& os, const TuringGraph& tg);

private:
	int convert(char c) const;
	char convert(int i) const;
	void destroy();

	struct Edge
	{
		Edge() { *this = { -1, 'e', 0 }; }
		Edge(int index, char change, int move) : index(index), change(change), move(move) { }

		int index;
		char change;
		int move;
	};

	struct Node
	{
		Node(int q) : q(q) { edges.resize(3); }

		int q;
		std::vector<Edge> edges;

	};

	Node posExit{ -1 };
	Node negExit{ -2 };
	std::vector<Node*> nodes;
	Node* curr = nullptr;
};

