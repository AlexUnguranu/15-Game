#include "Node.h"

Node::Node(Node* p, std::string dir, std::vector<std::vector<int>> puzz, int cost)
{
	this->p = p;
	this->come_from = dir;
	this->puzz = puzz;
	if (p != nullptr)
		depth = p->depth + 1;
	this->cost = cost+depth;

}

int Node::ConvertDirtoNumber()
{
	if (this->come_from == "U")
		return 1;
	if (this->come_from == "R")
		return 2;
	if (this->come_from == "D")
		return 3;
	if (this->come_from == "L")
		return 4;
	return 0;
}
