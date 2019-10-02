#include "algorithms.h"

SolutionPath *DFS_Search(State problem, State solution)
{
	long stack_size = 0;
	long max_stack_size = 0;
	int state_cost = 0;
	int visited_node_count = 0;
	long visited_size = 0;
	int solution_length = -1;
	char heuristic[100] = "DFS";

	LinkedList *head_children = NULL;
	Stack *top_visited = NULL;
	Stack *top_stack = NULL;
	StateList *node = NULL;

	SolutionPath *pathHead = NULL;
    SolutionPath *newPathNode = NULL;

    // create first node which is the problem node
	node = createNode(problem, state_cost, NULL);

	// push first node to the stack
	top_stack = push(top_stack, node, &stack_size);

	while(1)
	{
		// if open stack is empty, return failure
		if(emptyStack(top_stack) == true)
		{
			printf("\nError: First node wasn't pushed to stack!\n");
			exit(-1);
		}

		// pop node from stack until it finds node that hasn't been visited
		do
		{
			node = pop(&top_stack, &stack_size);

		}while(stateInStack(top_visited, node->puzzle) == true);

		// if node puzzle matches the solution puzzle, return success
		if(matchBoards(node->puzzle, solution) == true)
		{
			printf("\nFound Solution!\n");
			break;
		}

		// push node into visited stack
		top_visited = push(top_visited, node, &visited_size);

		// increase visited node count
		visited_node_count++;

		// get list of all possible puzzles (children) from current node
		head_children = getChildren(node, solution, heuristic);

		// move children to the open stack
		top_stack = moveChildrenToStack(top_stack, head_children, &stack_size);

		// keep track of maximum size of open stack
		if(stack_size > max_stack_size)
		{
			max_stack_size = stack_size;
		}

		// erase children list
		head_children = clearLinkedList(head_children);
	}

	// if open stack is not empty, erase the entire stack
	if(emptyStack(top_stack) == false)
	{
		top_stack = clearStack(top_stack);
	}
	
	// if visited stack is not empty, erase the entire stack
	if(emptyStack(top_visited) == false)
	{
		top_visited = clearStack(top_visited);
	}	

	// create the solution path from the last node to the first using parental relationship
	while(node != NULL) 
	{
        newPathNode = malloc(sizeof(SolutionPath));
        newPathNode->action = node->puzzle.action;
        newPathNode->puzzle = node->puzzle;
        newPathNode->next = pathHead;
        pathHead = newPathNode;

        // increment solution length and move to parent node
        solution_length++;
        node = node->parent;
    }

    // print important variables
	printf("\nNumber of visited nodes: %d\nMaximum size of OPEN: %ld", visited_node_count, max_stack_size);

	// return solution path to be printed
	return pathHead;
}

SolutionPath *BFS_Search(State problem, State solution)
{
	long queue_size = 0;
	int state_cost = 0;
	long max_queue_size = 0;
	int visited_node_count = 0;
	int solution_length = -1;
	char heuristic[100] = "BFS";

	StateList *node = NULL;
	LinkedList *head_visited = NULL;
	LinkedList *head_children = NULL;

	Queue *first = NULL;
	Queue *last = NULL;

	SolutionPath *pathHead = NULL;
    SolutionPath *newPathNode = NULL;

	// create first node
	node = createNode(problem, state_cost, NULL);

	// push first node to the queue
	enqueue(&first, &last, node, &queue_size);

	while(1)
	{
		// if open queue is empty, return failure
		if(emptyQueue(first) == true)
		{
			printf("\nError: First node wasn't pushed to queue!\n");
			exit(-1);
		}

		// remove first node from queue until it finds node that hasn't been visited
		do
		{
			node = dequeue(&first, &last, &queue_size);

		}while(stateInList(head_visited, node->puzzle) == true);

		// if node puzzle matches the solution puzzle, return success
		if(matchBoards(node->puzzle, solution) == true)
		{
			printf("\nFound Solution!\n");
			break;
		}

		// add node into visited list
		head_visited = addNode(head_visited, node);

		// increase visited node count
		visited_node_count++;

		// get list of all possible puzzles (children) from current node
		head_children = getChildren(node, solution, heuristic);

		// move children to the open queue
		moveChildrenToQueue(&first, &last, head_children, &queue_size);

		// keep track of maximum size of open queue
		if(queue_size > max_queue_size)
		{
			max_queue_size = queue_size;
		}

		// erase children list
		head_children = clearLinkedList(head_children);
	}

	// if open queue is not empty, erase the entire queue
	if(emptyQueue(first) == false)
	{
		clearQueue(first, last);
	}
	
	// if visited list is not empty, erase the entire list
	if(emptyList(head_visited) == false)
	{
		clearLinkedList(head_visited);
	}	

	// create the solution path from the last node to the first using parental relationship
	while(node != NULL) 
	{
        newPathNode = malloc(sizeof(SolutionPath));
        newPathNode->action = node->puzzle.action;
        newPathNode->puzzle = node->puzzle;
        newPathNode->next = pathHead;
        pathHead = newPathNode;

        // increment solution length and move to parent node
        solution_length++;
        node = node->parent;
    }

    // print important variables
	printf("\nNumber of visited nodes: %d\nMaximum size of OPEN: %ld", visited_node_count, max_queue_size);

	// return solution path to be printed
    return pathHead;
}

SolutionPath *AStar_Search(State problem, State solution, char *heuristic)
{
	long pqueue_size = 0;
	long max_pqueue_size = 0;
	int closed_state_cost = 0;
	int max_cost = 0;
	int visited_node_count = 0;
	int solution_length = -1;

	StateList *node = NULL;
	LinkedList *head_closed = NULL;
	LinkedList *head_children = NULL;

    PQueue *first_open = NULL;
	PQueue *last_open = NULL;

	SolutionPath *pathHead = NULL;
    SolutionPath *newPathNode = NULL;
	
	// create first node with cost 0
	node = createNode(problem, 0, NULL);

	// push first node to the queue
	enPqueue(&first_open, &last_open, &pqueue_size, node, &max_cost);

	while(1)
	{
		// if open priority queue is empty, return failure
		if(emptyPQueue(first_open) == true)
		{
			printf("\nError: First node wasn't pushed to queue!\n");
			exit(-1);
		}

		while(1)
		{
			// remove node with highest priority from priority queue
			node = dePqueue(&first_open, &last_open, &pqueue_size);

			// check if current node puzzle has already been visited, save cost if it has
			if(stateInClosed(head_closed, node->puzzle, &closed_state_cost) == false)
			{
				break;
			}
			// check if current node cost is lower than cost in visited list
			else if(node->cost < closed_state_cost)
			{
				// remove node that was visited from the list
				removeNode(head_closed, node);
				visited_node_count--;
				break;
			}
		}
		
		// if node puzzle matches the solution puzzle, return success
		if(matchBoards(node->puzzle, solution) == true)
		{
			printf("\nFound Solution!\n");
			break;
		}

		// add node into visited list
		head_closed = addNode(head_closed, node);

		// increase visited node count
		visited_node_count++;

		// get list of all possible puzzles (children) from current node
		head_children = getChildren(node, solution, heuristic);

		// move children to the open priority queue
		moveChildrenToPQueue(&first_open, &last_open, head_children, &max_cost, &pqueue_size);

		// keep track of maximum size of open priority queue
		if(pqueue_size > max_pqueue_size)
		{
			max_pqueue_size = pqueue_size;
		}

		// erase children list
		head_children = clearLinkedList(head_children);
	}

	// if open priority queue is not empty, erase the entire queue
	if(emptyPQueue(first_open) == false)
	{
		clearPQueue(first_open, last_open);
	}
	
	// if visited list is not empty, erase the entire list
	if(emptyList(head_closed) == false)
	{
		clearLinkedList(head_closed);
	}

	// create the solution path from the last node to the first using parental relationship
	while(node != NULL) 
	{
        newPathNode = malloc(sizeof(SolutionPath));
        newPathNode->action = node->puzzle.action;
        newPathNode->puzzle = node->puzzle;
        newPathNode->next = pathHead;
        pathHead = newPathNode;

        // increment solution length and move to parent node
        solution_length++;
        node = node->parent;
    }

    // print important variables
	printf("\nNumber of visited nodes: %d\nMaximum size of OPEN: %ld", visited_node_count, max_pqueue_size);

	// return solution path to be printed
	return pathHead;
}