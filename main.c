#include "game.h"
#include "list.h"
#include "algorithms.h"
#include <time.h>

int main(int argc, char **argv)
{
	int puzzle;
	int algorithm;
	char heuristic[100] = "";
	char *solving_algorithm[3] = {"DFS", "BFS", "AStar"};

	State p1;
	State p2;
	State p3;
	State p4;
	State solution;

	SolutionPath *AStar = NULL;
	SolutionPath *BFS = NULL;
	SolutionPath *DFS = NULL;

	// input parameter check
	inputCheck(argc, argv, &puzzle, &algorithm, heuristic);

	// define all problem puzzles and solution puzzle and other important information
	setProblems(&p1, &p2, &p3, &p4);
	setSolution(&solution);

	State problem[4] = {p1, p2, p3, p4};

	// display problem board, algorithm and heuristic to be used
	if(strcmp(heuristic, "H1") == 0 || strcmp(heuristic, "H2") == 0)
	{
		printf("\nPuzzle: P%d, Algorithm: %s, Heuristic: %s\n", puzzle, solving_algorithm[algorithm-1], heuristic);
		printBoard(problem[puzzle-1].board);
	}
	else
	{
		printf("\nPuzzle: P%d, Algorithm: %s, Heuristic: NON APPLICABLE\n", puzzle, solving_algorithm[algorithm-1]);
		printBoard(problem[puzzle-1].board);
	}
	
	// all possible programs to be ran, organized by problem and solving algorithm, followed by solution printed onto terminal
	switch(puzzle)
	{
		case 1:
			switch(algorithm)
			{
				case 1:
					// Run DFS
					DFS = DFS_Search(p1, solution);
					printSolution(DFS);
					break;
				case 2:
					// Run BFS
					BFS = BFS_Search(p1, solution);
					printSolution(BFS);
					break;
				case 3:
					// Run A*
					AStar = AStar_Search(p1, solution, heuristic);
					printSolution(AStar);
					break;
				default:
					exit(-1);
			}
			break;
		case 2:
			switch(algorithm)
			{
				case 1:
					// Run DFS
					DFS = DFS_Search(p2, solution);
					printSolution(DFS);
					break;
				case 2:
					// Run BFS
					BFS = BFS_Search(p2, solution);
					printSolution(BFS);
					break;
				case 3:
					// Run A*
					AStar = AStar_Search(p2, solution, heuristic);
					printSolution(AStar);
					break;
				default:
					exit(-1);
			}
			break;
		case 3:
			switch(algorithm)
			{
				case 1:
					// Run DFS
					DFS = DFS_Search(p3, solution);
					printSolution(DFS);
					break;
				case 2:
					// Run BFS
					BFS = BFS_Search(p3, solution);
					printSolution(BFS);
					break;
				case 3:
					// Run A*
					AStar = AStar_Search(p3, solution, heuristic);
					printSolution(AStar);
					break;
				default:
					exit(-1);
			}
			break;
		case 4:
			switch(algorithm)
			{
				case 1:
					// Run DFS
					DFS = DFS_Search(p4, solution);
					printSolution(DFS);
					break;
				case 2:
					// Run BFS
					BFS = BFS_Search(p4, solution);
					printSolution(BFS);
					break;
				case 3:
					// Run A*
					AStar = AStar_Search(p4, solution, heuristic);
					printSolution(AStar);
					break;
				default:
					exit(-1);
			}
			break;
	}	

	return 0;
}