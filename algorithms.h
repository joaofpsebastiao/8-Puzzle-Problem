#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "headers.h"
#include "game.h"
#include "list.h"

// Function that performs Depth First Search algorithm and returns solution path if it exists
SolutionPath *DFS_Search(State problem, State solution);

// Function that performs Breadth First Search algorithm and returns solution path if it exists
SolutionPath *BFS_Search(State problem, State solution);

// Function that performs A* Search algorithm with chosen heuristic function and returns solution path if it exists
SolutionPath *AStar_Search(State problem, State solution, char *heuristic);

#endif