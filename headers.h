#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define GRID_SIZE 3

// Enumerate used to identify movements between consecutive puzzles
typedef enum Move
{
    UP, DOWN, LEFT, RIGHT, // values for moving up, down, left, right, respectively
    NOT_APPLICABLE         // value assigned for problem and solution state
} Move;

// Structure containing the puzzle board, the action that originated it and validation flag
typedef struct State
{
	bool valid;				
    Move action;            
    int board[3][3];        
} State;

// Structure containing the state, cost to reach it, a connection to the parent state and a pointer to the list of its children
typedef struct StateList
{
	int cost;
	State puzzle;
	struct StateList *parent;
	struct LinkedList *children;
} StateList;

// Linked List of nodes
typedef struct LinkedList
{
	StateList *node;
	struct LinkedList *next; 
} LinkedList;

// Stack of nodes
typedef struct Stack
{
	StateList *node;
	struct Stack *next; 
} Stack;

// Queue of nodes
typedef struct Queue
{
	StateList *node;
	struct Queue *next;
} Queue;

// Priority Queue of nodes
typedef struct PQueue
{
	StateList *node;
	struct PQueue *next; 
} PQueue;

// Structure of the solution path containing the move and puzzle and a link to the next puzzle on the path
typedef struct SolutionPath
{
    Move action;
    State puzzle;
    struct SolutionPath *next;
} SolutionPath;

#endif
