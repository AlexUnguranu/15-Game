#pragma once
#include "Header.h"


int main()
{
	std::vector<std::vector<int>> puzz;
	FileRead(puzz);
	MatrixElemAsContinuousString(puzz);
	WritePuzz(puzz);

	//std::swap(puzz[1][1], puzz[0][1]);
	//WritePuzz(puzz);
	//std::cout << GetBlankPosition(puzz);
	if (CheckSolvability(puzz))
		std::cout << "The configuration is solvable!"<<std::endl;
	else {
		std::cout << "The configuration is not solvable!";
		exit(2);
	}
	//std::cout << ManhattanCost(puzz);
	PuzzleSolve(puzz);

}

