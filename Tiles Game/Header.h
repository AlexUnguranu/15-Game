#pragma once

#include <stack>
#include <list>
#include <map>
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "Node.h"
#include <unordered_map>
struct Comparer // comparator priority queue
{
	bool operator ()(Node* pos, Node* pos2)
	{
		return pos->cost-pos->depth > pos2->cost-pos2->depth;
	}
};
void FileRead(std::vector<std::vector<int>>& puzz);
void WritePuzz(std::vector<std::vector<int>>puzz);
bool CheckSolvability(std::vector<std::vector<int>>puzz);
int GetInversionsNumber(std::vector<int> vect);
std::vector<int> ConvertMatrixToVector(std::vector<std::vector<int>>puzz);
std::pair<int, int> GetBlankPosition(std::vector<std::vector<int>>puzz);
std::vector<Node*> GenerateChildrens(Node* P, std::unordered_map < std::string, int >& map);// map parameters ? puzz_ca_str  , cost 
int ManhattanCost(std::vector<std::vector<int>>puzz);
std::string MatrixElemAsContinuousString(std::vector<std::vector<int>> puzz);
void PuzzleSolve(std::vector<std::vector<int>>puzz);
void ConstructFinalPath(Node* nod);