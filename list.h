#ifndef LIST_H
#define LIST_H

#include "headers.h"
#include "game.h"

// Function that creates a new node with all necessary information and connection to parent node
StateList *createNode(State puzzle, int cost, StateList *parent);

/*
*
*
* Linked List Functions
*
*/

// Function that adds new node to the list
LinkedList *addNode(LinkedList *head, StateList *node);

// Function that checks if the list is empty
bool emptyList(LinkedList *head);

// Function that erases the list
LinkedList *clearLinkedList(LinkedList *head);

// Function that looks for specific puzzle in the list
bool stateInList(LinkedList *head, State puzzle);

// Function used to print the list (mainly for debugging)
void printList(LinkedList *head);

// Function that removes a specific node from the list
LinkedList *removeNode(LinkedList *head, StateList *node);

// Function that reverses the order of the list (used for possible performance enhancement)
LinkedList *reverseList(LinkedList** head);

/*
*
*
* Stack Section
*
*/

// Function that pushes new node to the stack
Stack *push(Stack *top, StateList *node, long *size);

// Function that returns the top node from the stack
StateList* pop(Stack **top, long *size);

// Function that checks if the stack is empty
bool emptyStack(Stack *top);

// Function that erases the stack
Stack *clearStack(Stack *top);

// Function that looks for specific puzzle in the stack
bool stateInStack(Stack *top, State puzzle);

// Function used to print the stack (mainly for debugging)
void printStack(Stack *top);

/*
*
*
* Queue Section
*
*/

// Function that sends new node to the queue, placing it in last
void enqueue(Queue **first, Queue **last, StateList *node, long *queue_size);

// function that returns first node of the queue
StateList *dequeue(Queue **first, Queue **last, long *queue_size);

// Function that checks if the queue is empty
bool emptyQueue(Queue *first);

// Function that erases the queue
void clearQueue(Queue *first, Queue *last);

/*
*
*
* Priority Queue Section
*
*/

// Function that sends new node to the queue, placing it in the correct position based on it's priority (in this case cost)
void enPqueue(PQueue **first, PQueue **last, long *pqueue_size, StateList *node, int *max_cost);

// Function that returns the first node of the queue, which is the one with the lowest cost
StateList *dePqueue(PQueue **first, PQueue **last, long *pqueue_size);

// Function that looks for specific puzzle in the priority queue 
bool stateInClosed(LinkedList *head, State puzzle, int *cost);

// Function that checks if the priority queue is empty
bool emptyPQueue(PQueue *first);

// Function that erases the priority queue
void clearPQueue(PQueue *first, PQueue *last);

// Function used to print the priority queue (mainly for debugging)
void printPQueue(PQueue *first);

// Function used to get the maximum cost in the priority queue (mainly for debugging)
int findMax(PQueue *first);

#endif
