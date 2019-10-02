#ifndef GAME_H
#define GAME_H

#include "headers.h"
#include "list.h"

// Function that checks input parameters
void inputCheck(int argc, char **argv, int *puzzle, int *algorithm, char *heuristic);

// Function used to define all problem puzzles and other important information
void setProblems(State *p1, State *p2, State *p3, State *p4);

// Function used to define solution puzzle and other important information
void setSolution(State *solution);

// Function used to print puzzle board (mainly for debugging)
void printBoard(int board[][GRID_SIZE]);

// Function that compares 2 puzzle boards and returns true if they match
bool matchBoards(State state1, State state2);

// Function that returns the Manhattan distance between 2 puzzle boards
int manhattanDistance(State state1, State state2);

// Function that returns the number of misplaced tiles between 2 puzzle boards
int misplacedTiles(State puzzle, State solution);

// Function that returns a list of all allowed puzzles (children) originated from one puzzle (parent)
LinkedList *getChildren(StateList *node, State solution, char *procedure);

// Function that transfers list of children to a stack
Stack *moveChildrenToStack(Stack *top, LinkedList *head, long *stack_size);

// Function that transfers list of children to a queue
void moveChildrenToQueue(Queue **first, Queue **last, LinkedList *head, long *queue_size);

// Function that transfers list of children to a priority queue
void moveChildrenToPQueue(PQueue **first_open, PQueue **last_open, LinkedList *head_children, int *_max_cost, long *pqueue_size);

// Function that prints the solution path 
void printSolution(SolutionPath *path);

#endif
