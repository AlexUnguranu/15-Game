#pragma once
#include "Header.h"

void FileRead(std::vector<std::vector<int>>& puzz)
{
	std::ifstream inp("Puzzle.in");
	if (inp.is_open())
	{
		puzz.reserve(9);
		while (!inp.eof())
		{
			std::vector<int>line_vect;
			std::string line;
			std::getline(inp, line);
			line.push_back(' ');
			while (!line.empty())
			{
				if (line[0] == ' ')
					line.erase(line.begin(), line.begin() + 1);
				else {
					std::string word;
					auto pos = line.find(' ');
					word = line.substr(0, pos);
					line.erase(line.begin(), line.begin() + pos);
					auto value = std::stoi(word);
					line_vect.push_back(value);
				}
			}
			puzz.push_back(line_vect);
		}
	}
	else {
		std::cout << "Input File is invalid , Required name :'Puzzle.in'";
		exit(2);
	}
}

void WritePuzz(std::vector<std::vector<int>> puzz)
{
	for (int i = 0; i < puzz.size(); i++)
	{
		std::cout << std::endl;
		for (int j = 0; j < puzz.size(); j++)
		{
			std::cout << puzz[i][j] << ' ';
		}
	}
	std::cout << std::endl;
}

bool CheckSolvability(std::vector<std::vector<int>> puzz)
{
	std::vector<int> line_vect = ConvertMatrixToVector(puzz);
	int inv = GetInversionsNumber(line_vect) % 2;
	bool ok = true;
	int grid_width = puzz.size() % 2;
	if (grid_width == 1 && inv == 0)
		return true;
	else if (grid_width == 0) {
		int pos = (puzz.size() - GetBlankPosition(puzz).first) % 2;
		if (pos == 0 && inv == 1)
			return true;
		if (pos == 1 && inv == 0)
			return true;

	}
	return false;
}

int GetInversionsNumber(std::vector<int> vect)
{
	int cnt = 0;
	for (int i = 0; i < vect.size() - 1; i++)
	{
		for (int j = i + 1; j < vect.size(); j++)
		{
			if (vect[i] > vect[j] && vect[j] != 0)
				cnt++;
		}
	}
	return cnt;
}

std::vector<int> ConvertMatrixToVector(std::vector<std::vector<int>> puzz)
{
	std::vector<int> new_vect;
	for (int i = 0; i < puzz.size(); i++)
	{
		for (int j = 0; j < puzz.size(); j++)
		{
			new_vect.push_back(puzz[i][j]);
		}
	}
	return new_vect;
}

std::pair<int, int> GetBlankPosition(std::vector<std::vector<int>> puzz)
{
	for (int i = 0; i < puzz.size(); i++)
	{
		for (int j = 0; j < puzz.size(); j++)
		{
			if (puzz[i][j] == 0)
				return { i,j };
		}
	}
}

int ManhattanCost(std::vector<std::vector<int>> puzz)
{
	int Manh_cost = 0;
	for (int i = 0; i < puzz.size(); i++)
	{
		for (int j = 0; j < puzz.size(); j++)
		{
			int  val = puzz[i][j];
			int v1 = (val - 1) / puzz.size();
			int v2 = (val - 1) % puzz.size();
			if (val == 0)
			{
				v1 = puzz.size() - 1;
				v2 = puzz.size() - 1;
			}

			Manh_cost += abs(v1 - i) + abs(v2 - j);
		}
	}
	return Manh_cost;
}

std::string MatrixElemAsContinuousString(std::vector<std::vector<int>> puzz)
{
	std::string Matr_ID;
	for (int i = 0; i < puzz.size(); i++)
	{
		for (int j = 0; j < puzz[i].size(); j++)
		{
			Matr_ID += std::to_string(puzz[i][j]);
			Matr_ID += " ";
		}
	}
	//std::cout << "\n\n" << Matr_ID << "\n";
	return Matr_ID;
}

void PuzzleSolve(std::vector<std::vector<int>> puzz)
{
	Node* Start = new Node;
	Start->puzz = puzz;
	Start->cost = ManhattanCost(puzz);
	std::unordered_map<std::string, int> map;
	map[MatrixElemAsContinuousString(puzz)] = ManhattanCost(puzz);
	//std::vector<Node*> vect = GenerateChildrens(Start, map);
	std::priority_queue<Node*, std::vector<Node*>, Comparer> prior_q;
	prior_q.push(Start);
	bool found = false;
	Node* fin = Start;
	std::cout << "Start \n=========================================================\n";
	int cnt = 0;
	while (true)
	{
		if (prior_q.empty())// unavailable case ?
		{
			break;
		}

		Node* top = prior_q.top();
		std::cout << top->cost /*- top->depth*/ << "  ";
		if (top->cost - top->depth == 0)
		{
			found = true;
			fin = top;
			break;
		}
		prior_q.pop();
		std::vector < Node* > vect = GenerateChildrens(top, map);
		cnt++;
		if (cnt > 10000)
			cnt = 0;
		for (int i = 0; i < vect.size(); i++)
		{
			prior_q.push(vect[i]);
		}
	}
	//if (fin != nullptr)
	//	WritePuzz(fin->puzz);
	//std::cout << ManhattanCost(fin->puzz);
	std::cout << "\n=========================================================\nFIN\n";
	ConstructFinalPath(fin);
}

void ConstructFinalPath(Node* nod)
{
	std::list<std::string> path;

	while (nod != nullptr)
	{
		path.push_front(nod->come_from);
		nod = nod->p;
	}
	for (auto it : path)
	{
		if (it == "U")
			std::cout << "D";
		else if (it == "D")
			std::cout << "U";
		else if (it == "R")
			std::cout << "L";
		else 
			std::cout << "R";
		std::cout << " ";
	}
}

std::vector<Node*> GenerateChildrens(Node* P, std::unordered_map < std::string, int >& map) // puzz_ca_str , cost
{
	std::vector<Node*> chids;
	chids.reserve(3);
	auto blank = GetBlankPosition(P->puzz);
	int blank_i = blank.first, blank_j = blank.second;
	if (blank_i > 0) // daca exista sus 
	{
		std::vector<std::vector<int>>puzz = P->puzz;
		std::swap(puzz[blank_i][blank_j], puzz[blank_i - 1][blank_j]);
		std::string Matr_ID = MatrixElemAsContinuousString(puzz);
		int cost = ManhattanCost(puzz);
		if (map.find(Matr_ID) == map.end())// cautam in map
		{
			Node* nod = new Node(P, "U", puzz, cost);
			map[Matr_ID] = cost;
			chids.push_back(nod);
		}
		else
		{
			if (P->cost > cost)
				map[Matr_ID] = cost;
		}
	}
	if (blank_i < P->puzz.size() - 1)// daca exista jos 
	{
		std::vector<std::vector<int>>puzz = P->puzz;
		std::swap(puzz[blank_i][blank_j], puzz[blank_i + 1][blank_j]);
		std::string Matr_ID = MatrixElemAsContinuousString(puzz);
		int cost = ManhattanCost(puzz);
		if (map.find(Matr_ID) == map.end())// cautam in map
		{
			Node* nod = new Node(P, "D", puzz, cost);
			map[Matr_ID] = cost;
			chids.push_back(nod);
		}
		else
		{
			if (P->cost > cost)
				map[Matr_ID] = cost;
		}
	}
	if (blank_j > 0) // daca exista stanga
	{
		std::vector<std::vector<int>>puzz = P->puzz;
		std::swap(puzz[blank_i][blank_j], puzz[blank_i][blank_j - 1]);
		std::string Matr_ID = MatrixElemAsContinuousString(puzz);
		int cost = ManhattanCost(puzz);
		if (map.find(Matr_ID) == map.end())// cautam in map
		{
			Node* nod = new Node(P, "L", puzz, cost);
			map[Matr_ID] = cost;
			chids.push_back(nod);
		}
		else
		{
			if (P->cost > cost)
				map[Matr_ID] = cost;
		}
	}
	if (blank_j < P->puzz.size() - 1) // daca exista dreapta
	{
		std::vector<std::vector<int>>puzz = P->puzz;
		std::swap(puzz[blank_i][blank_j], puzz[blank_i][blank_j + 1]);
		std::string Matr_ID = MatrixElemAsContinuousString(puzz);
		int cost = ManhattanCost(puzz);
		if (map.find(Matr_ID) == map.end())// cautam in map
		{
			Node* nod = new Node(P, "R", puzz, cost);
			map[Matr_ID] = cost;
			chids.push_back(nod);
		}
		else
		{
			if (P->cost > cost)
				map[Matr_ID] = cost;
		}
	}
	return chids;
}