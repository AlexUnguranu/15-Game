#pragma once
#include <vector>
#include <string>
struct Node
{
public:
	std::vector<std::vector<int>> puzz;
	Node* p;
	std::string come_from;
	int cost;
	int depth=0;
public:
	Node(Node* p = nullptr, std::string dir="", std::vector<std::vector<int>> puzz = {}, int cost = NULL);
	int ConvertDirtoNumber();
};

