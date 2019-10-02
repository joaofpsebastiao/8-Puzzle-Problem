#include "game.h"

void inputCheck(int argc, char **argv, int *puzzle, int *algorithm, char *heuristic)
{
	// check if number of input arguments is valid
	if(argc < 3 || argc > 4)
	{
		printf("\nError: Invalid number of inputs!\nCorrect input: ./homework1 puzzle algorithm heuristic, \nwhere puzzle = P1/P2/P3/P4, algorithm = DFS/BFS/AStar and heuristic = H1/H2 (if AStar is chosen).\n\n");
		exit(-1);
	}
	// check if first input argument is valid
	else if((strcmp(argv[1], "P1") != 0) && (strcmp(argv[1], "P2") != 0) && (strcmp(argv[1], "P3") != 0) && (strcmp(argv[1], "P4") != 0))
	{
		printf("\nError: Invalid 2nd input!\nCorrect input: ./homework1 puzzle algorithm heuristic, \nwhere puzzle = P1/P2/P3/P4, algorithm = DFS/BFS/AStar and heuristic = H1/H2 (if AStar is chosen).\n\n");
		exit(-1);
	}
	// check if second input argument is valid
	else if((strcmp(argv[2], "DFS") != 0) && (strcmp(argv[2], "BFS") != 0) && (strcmp(argv[2], "AStar") != 0))
	{
		printf("\nError: Invalid 3rd input!\nCorrect input: ./homework1 puzzle algorithm heuristic, \nwhere puzzle = P1/P2/P3/P4, algorithm = DFS/BFS/AStar and heuristic = H1/H2 (if AStar is chosen).\n\n");
		exit(-1);
	}
	// check which problem has been chosen
	else
	{
		if(strcmp(argv[1], "P1") == 0)
		{
			*puzzle = 1;
		}
		else if(strcmp(argv[1], "P2") == 0)
		{
			*puzzle = 2;
		}
		else if(strcmp(argv[1], "P3") == 0)
		{
			*puzzle = 3;
		}
		else
		{
			*puzzle = 4;
		}

		// check which solving algorithm has been chosen
		if((strcmp(argv[2], "DFS") == 0))
		{
			*algorithm = 1;
		}
		else if((strcmp(argv[2], "BFS") == 0))
		{
			*algorithm = 2;
		}
		// check which A* heuristic has been chosen
		else
		{
			*algorithm = 3;
			if((strcmp(argv[3], "H1") == 0))
			{
				strcpy(heuristic, "H1");
			}
			else if((strcmp(argv[3], "H2") == 0))
			{
				strcpy(heuristic, "H2");
			}
			else
			{
				printf("\nError: Invalid 4rd input!\nCorrect input: ./homework1 puzzle algorithm heuristic, \nwhere puzzle = P1/P2/P3/P4, algorithm = DFS/BFS/AStar and heuristic = H1/H2 (if AStar is chosen).\n\n");
				exit(-1);
			}
		}
		return;
	}
}

void setProblems(State *p1, State *p2, State *p3, State *p4)
{

	// set valid flag to true, no action and predefined board for problem 1
	p1->valid = true;
	p1->action = NOT_APPLICABLE;
	p1->board[0][0] = 4;
	p1->board[0][1] = 1;
	p1->board[0][2] = 0;
	p1->board[1][0] = 6;
	p1->board[1][1] = 3;
	p1->board[1][2] = 2;
	p1->board[2][0] = 7;
	p1->board[2][1] = 5;
	p1->board[2][2] = 8;
	
	// set valid flag to true, no action and predefined board for problem 2
	p2->valid = true;
	p2->action = NOT_APPLICABLE;
	p2->board[0][0] = 4;
	p2->board[0][1] = 3;
	p2->board[0][2] = 1;
	p2->board[1][0] = 6;
	p2->board[1][1] = 5;
	p2->board[1][2] = 2;
	p2->board[2][0] = 0;
	p2->board[2][1] = 7;
	p2->board[2][2] = 8;
	
	// set valid flag to true, no action and predefined board for problem 3
	p3->valid = true;
	p3->action = NOT_APPLICABLE;
	p3->board[0][0] = 3;
	p3->board[0][1] = 1;
	p3->board[0][2] = 0;
	p3->board[1][0] = 4;
	p3->board[1][1] = 5;
	p3->board[1][2] = 2;
	p3->board[2][0] = 6;
	p3->board[2][1] = 7;
	p3->board[2][2] = 8;
	
	// set valid flag to true, no action and predefined board for problem 4
	p4->valid = true;
	p4->action = NOT_APPLICABLE;
	p4->board[0][0] = 0;
	p4->board[0][1] = 1;
	p4->board[0][2] = 2;
	p4->board[1][0] = 3;
	p4->board[1][1] = 4;
	p4->board[1][2] = 5;
	p4->board[2][0] = 6;
	p4->board[2][1] = 7;
	p4->board[2][2] = 8;
}

void setSolution(State *solution)
{
	// set valid flag to true, no action and predefined board for the solution
	solution->valid = true;
	solution->action = NOT_APPLICABLE;	
	solution->board[0][0] = 1;
	solution->board[0][1] = 2;
	solution->board[0][2] = 3;
	solution->board[1][0] = 4;
	solution->board[1][1] = 5;
	solution->board[1][2] = 6;
	solution->board[2][0] = 7;
	solution->board[2][1] = 8;
	solution->board[2][2] = 0;
}

void printBoard(int board[][GRID_SIZE])
{
    int row, col;

    // go through every cell and print the number 
    for(row = 0; row < 3; row++)
    {
        printf("+---+---+---+\n");

        for(col = 0; col < 3; col++)
        {
            printf("| %d ", board[row][col]);
        }
        printf("|\n");
    }
    printf("+---+---+---+\n");
}

bool matchBoards(State state1, State state2)
{
	//go through every cell, check if every cell has the same number
	for(int i = 0; i < GRID_SIZE; i++)
	{
		for(int j = 0; j < GRID_SIZE; j++)
		{
			// if cell has a different number, return false
			if(state1.board[i][j] != state2.board[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

int manhattanDistance(State state1, State state2)
{
	int line0, line1, col0, col1, diffx, diffy, distance = 0;

	// go through every line and column on puzzle 1
	for(line0 = 0; line0 < GRID_SIZE; line0++)
	{
		for(col0 = 0; col0 < GRID_SIZE; col0++)
		{
			// go through every line and column on puzzle 2
			for(line1 = 0; line1 < GRID_SIZE; line1++)
			{
				for(col1 = 0; col1 < GRID_SIZE; col1++)
				{
					diffx = diffy = 0;

					// if a match is found
					if(state1.board[line0][col0] == state2.board[line1][col1])
					{
						// compute distance in x and y direction
						diffx = (line0 - line1 < 0) ? line1 - line0 : line0 - line1;
                        diffy = (col0 - col1 < 0) ? col1 - col0 : col0 - col1;

                        // sum distances
                        distance += diffx + diffy;
					}
				}
			}
		}
	}

	// return Manhattan distance
	return distance;
}

int misplacedTiles(State puzzle, State solution)
{
	int tiles = 0;

	// go though every line
	for(int line = 0; line < GRID_SIZE; line++)
	{
		// go through every column
		for(int col = 0; col < GRID_SIZE; col++)
		{
			// if cell's number doesn't match, increment counter
			if(puzzle.board[line][col] != solution.board[line][col])
			{
				tiles++;
			}
		}
	}

	// return number of misplaced tiles
	return tiles;
}

State createState(State puzzle, Move action)
{
	int row, col;
	State newState;

	// go through the puzzle to find the blank character
	for(int i = 0; i < GRID_SIZE; i++)
	{
		for(int j = 0; j < GRID_SIZE; j++)
		{	
			// Save line and column of the blank character's location
			if(puzzle.board[i][j] == 0)
			{
				row = i;
				col = j;
			}

			// copy original board to new board
			newState.board[i][j] = puzzle.board[i][j];
		}
	}

	// Check if it's possible to move blank character upwards
	if(action == UP && row - 1 >= 0) 
	{
		// swap elements
		int tmp = newState.board[row-1][col];
		newState.board[row-1][col] = newState.board[row][col];
		newState.board[row][col] = tmp;

		// set valid flag and save movement
		newState.valid = true;
		newState.action = UP;
	}
	// Check if it's possible to move blank character downwards
	else if(action == DOWN && row + 1 < GRID_SIZE) 
	{
		// swap elements
		int tmp = newState.board[row+1][col];
		newState.board[row+1][col] = newState.board[row][col];
		newState.board[row][col] = tmp;

		// set valid flag and save movement
		newState.valid = true;
		newState.action = DOWN;
	}
	// Check if it's possible to move blank character leftwards
	else if(action == LEFT && col - 1 >= 0) 
	{
		// swap elements
		int tmp = newState.board[row][col-1];
		newState.board[row][col-1] = newState.board[row][col];
		newState.board[row][col] = tmp;

		// set valid flag and save movement
		newState.valid = true;
		newState.action = LEFT;
	}
	// Check if it's possible to move blank character rightwards
	else if(action == RIGHT && col + 1 < GRID_SIZE) 
	{
		// swap elements
		int tmp = newState.board[row][col+1];
		newState.board[row][col+1] = newState.board[row][col];
		newState.board[row][col] = tmp;

		// set valid flag and save movement
		newState.valid = true;
		newState.action = RIGHT;
	}
	else
	{
		// Can't make any move without falling off the board
		newState.valid = false;
	}

	// return new state
	return newState;
}

LinkedList *getChildren(StateList *parent, State solution, char *procedure)
{
	State testState;
	int distance = 0;

	StateList *child = NULL;

	// check if moving up creates a valid state and if the previous movement wasn't downwards (to avoid repetition)
	if(parent->puzzle.action != DOWN && (testState = createState(parent->puzzle, UP)).valid == true)
	{
		// check what cost to assign based on solving algorithm and heuristic
		if(strcmp(procedure, "H1") == 0)
		{
			distance = parent->cost + misplacedTiles(testState, solution);
		}
		else if(strcmp(procedure, "H2") == 0)
		{
			distance = parent->cost + manhattanDistance(testState, solution);
		}
		else if(strcmp(procedure, "DFS") == 0 || strcmp(procedure, "BFS") == 0)
		{
			distance = parent->cost + 1;
		}
		// invalid heuristic
		else
		{
			printf("\nError: getAStarChildren\n");
			exit(-1);
		}

		// create child node with state, distance and parent connection
		child = createNode(testState, distance, parent);

		// add child to parent's children list
		parent->children = addNode(parent->children, child);
	}

	// check if moving down creates a valid state and if the previous movement wasn't upwards (to avoid repetition)
	if(parent->puzzle.action != UP && (testState = createState(parent->puzzle, DOWN)).valid == true)
	{
		// check what cost to assign based on solving algorithm and heuristic
		if(strcmp(procedure, "H1") == 0)
		{
			distance = parent->cost + misplacedTiles(testState, solution);
		}
		else if(strcmp(procedure, "H2") == 0)
		{
			distance = parent->cost + manhattanDistance(testState, solution);
		}
		else if(strcmp(procedure, "DFS") == 0 || strcmp(procedure, "BFS") == 0)
		{
			distance = parent->cost + 1;
		}
		// invalid heuristic
		else
		{
			printf("\nError: getAStarChildren\n");
			exit(-1);
		}

		// create child node with state, distance and parent connection
		child = createNode(testState, distance, parent);

		// add child to parent's children list
		parent->children = addNode(parent->children, child);
	}

	// check if moving left creates a valid state and if the previous movement wasn't rightwards (to avoid repetition)
	if(parent->puzzle.action != RIGHT && (testState = createState(parent->puzzle, LEFT)).valid == true)
	{
		// check what cost to assign based on solving algorithm and heuristic
		if(strcmp(procedure, "H1") == 0)
		{
			distance = parent->cost + misplacedTiles(testState, solution);
		}
		else if(strcmp(procedure, "H2") == 0)
		{
			distance = parent->cost + manhattanDistance(testState, solution);
		}
		else if(strcmp(procedure, "DFS") == 0 || strcmp(procedure, "BFS") == 0)
		{
			distance = parent->cost + 1;
		}
		// invalid heuristic
		else
		{
			printf("\nError: getAStarChildren\n");
			exit(-1);
		}

		// create child node with state, distance and parent connection
		child = createNode(testState, distance, parent);

		// add child to parent's children list
		parent->children = addNode(parent->children, child);
	}

	// check if moving right creates a valid state and if the previous movement wasn't leftwards (to avoid repetition)
	if(parent->puzzle.action != LEFT && (testState = createState(parent->puzzle, RIGHT)).valid == true)
	{
		// check what cost to assign based on solving algorithm and heuristic
		if(strcmp(procedure, "H1") == 0)
		{
			distance = parent->cost + misplacedTiles(testState, solution);
		}
		else if(strcmp(procedure, "H2") == 0)
		{
			distance = parent->cost + manhattanDistance(testState, solution);
		}
		else if(strcmp(procedure, "DFS") == 0 || strcmp(procedure, "BFS") == 0)
		{
			distance = parent->cost + 1;
		}
		// invalid heuristic
		else
		{
			printf("\nError: getAStarChildren\n");
			exit(-1);
		}

		// create child node with state, distance and parent connection
		child = createNode(testState, distance, parent);

		// add child to parent's children list
		parent->children = addNode(parent->children, child);
	}

	// return children list 
	return parent->children;
}

Stack *moveChildrenToStack(Stack *top, LinkedList *head, long *stack_size)
{
	LinkedList *tmp = head;

	long size = *stack_size;

	// go through every element of the children list
	while(tmp != NULL)
	{
		// send children node to the stack
		top = push(top, tmp->node, &size);
		tmp = tmp->next;
	}

	// update stack information
	*stack_size = size;

	return top;	
}

void moveChildrenToQueue(Queue **first, Queue **last, LinkedList *head, long *queue_size)
{
	LinkedList *tmp = head;

	Queue *top = (*first);
	Queue *bottom = (*last);

	long q_size = *queue_size;

	// go through every element of the children list
	while(tmp != NULL)
	{
		// send children node to the queue
		enqueue(&top, &bottom, tmp->node, &q_size);
		tmp = tmp->next;
	}

	// update queue information
	(*first) = top;
	(*last) = bottom;
	(*queue_size) = q_size;
}

void moveChildrenToPQueue(PQueue **first_open, PQueue **last_open, LinkedList *head_children, int *max_cost, long *pqueue_size)
{

	LinkedList *tmp = head_children;

	PQueue *top = (*first_open);
	PQueue *bottom = (*last_open);

	int max = *max_cost;
	long pq_size = *pqueue_size;	

	// go through every element of the children list
	while(tmp != NULL)
	{
		// send children node to the priority queue
		enPqueue(&top, &bottom, &pq_size, tmp->node, &max);
		tmp = tmp->next;
	}

	// update priority queue information
	(*first_open) = top;
	(*last_open) = bottom;
	(*max_cost) = max;
	(*pqueue_size) = pq_size;
}

void printSolution(SolutionPath *path) 
{
	//check if solution exists
    if(path == NULL) 
    {
        printf("\nNo solution found.\n");
        exit(-1);
    }

    printf("\n\nSOLUTION: (Relative to the space character)\n");

    char *move[4] = {"UP", "DOWN", "LEFT", "RIGHT"};
    int counter = 1;

    // skip first iteration equal to the problem state, print iteration and respective movement
    for(path = path->next; path; path = path->next, ++counter)
    {
        printf("%d. Move %s\n", counter, move[path->action]);
    }
}


