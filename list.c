#include "list.h"

StateList *createNode(State puzzle, int cost, StateList *parent)
{
  // allocate memory for the new node
  StateList *newNode = malloc(sizeof(StateList));

  if(newNode == NULL)
  {
    printf("\nError: Unable to create pointer! Function: createNode (Not enough space)\n");
    exit(-1);
  }

  // story information of the new node
  newNode->puzzle = puzzle;
  newNode->cost = cost;
  newNode->parent = parent;
  newNode->children = NULL;

  // return new node
  return newNode;
}

/*
*
*
* Linked List Functions
*
*/

LinkedList *addNode(LinkedList *head, StateList *node)
{
  // list not empty, store node in new element of the list
  if(emptyList(head) == false)
  {
    LinkedList *newNode = malloc(sizeof(LinkedList));

    if(newNode == NULL)
    {
      printf("\nError: Unable to create pointer! Function: addNode #1 (Not enough space)\n");
      exit(-1);
    }

    LinkedList *aux = head;

    // search for the last element of the list
    while(aux->next != NULL)
    {
      aux = aux->next;
    }

    // store information on the new element
    aux->next = newNode;
    newNode->node = node;
    newNode->next = NULL;
    
  }
  // create head of the list and store the node
  else
  {
    head = (LinkedList *)malloc(sizeof(LinkedList));

    if(head == NULL)
    {
      printf("\nError: Unable to create pointer! Function: addNode #2 (Not enough space)\n");
      exit(-1);
    }

    // store information on the head element
    head->node = node;
    head->next = NULL;
  }

  return head;
}

bool emptyList(LinkedList *head)
{

  return((head == NULL) ? true : false);
}

LinkedList *clearLinkedList(LinkedList *head)
{
  LinkedList *tmp;

  // go through every element of the queue and free memory allocated 
  while(head != NULL)
  {
    tmp = head;
    head = head->next;
    free(tmp);
  }

  return head;
}

bool stateInList(LinkedList *head, State puzzle)
{
  LinkedList *tmp = head;

  // if the list is empty, puzzle is not in the list
  if(emptyList(head) == true)
  {
    return false;
  }

  // go through every element of the list
  while(tmp != NULL)
  {
    // compare each element with specific puzzle, return true if there's a match
    if(matchBoards(tmp->node->puzzle, puzzle) == true) 
    {
      return true;
    }

    tmp = tmp->next;
  }

  // return false if specific puzzle is not found
  return false;
}

void printList(LinkedList *head)
{
  LinkedList *tmp = head;

  // go through every element of the list
  while(tmp != NULL)
  {
    // print puzzle onto terminal
    printBoard(tmp->node->puzzle.board);
    tmp = tmp->next;
  }
}

LinkedList *removeNode(LinkedList *head, StateList *node)
{
  LinkedList *tmp = head;
  LinkedList *aux = NULL;

  // check if node to be removed is on the head of the list
  if(matchBoards(node->puzzle, head->node->puzzle) == true)
  {
    head = head->next;
    free(tmp);
  }
  else
  {
    // go through every element of the list
    while(tmp != NULL)
    {
      aux = tmp;
      tmp = tmp->next;

      // compare each element with specific puzzle, remove element if there's a match
      if(matchBoards(node->puzzle, tmp->node->puzzle) == true)
      {
        aux->next = tmp->next;
        tmp->next = NULL;
        free(tmp);
        break;
      }
      
    }
  }

  return head;
}

LinkedList *reverseList(LinkedList** head) 
{ 
    LinkedList* prev = NULL; 
    LinkedList* current = *head; 
    LinkedList* next = NULL; 

    while (current != NULL)
    { 
        // Store next element
        next = current->next; 
  
        // Reverse current node's pointer 
        current->next = prev; 
  
        // Move pointers one position ahead. 
        prev = current; 
        current = next; 
    } 

    *head = prev;

    return (*head);
} 

/*
*
*
* Stack Functions
*
*/

Stack *push(Stack *top, StateList *node, long *size)
{
  Stack *newNode;

  // stack not empty, store node in new element of the stack
  if(emptyStack(top) == false)
  {
    //allocating memory for new node
    newNode = malloc(sizeof(Stack));

    if(newNode == NULL)
    {
      printf("\nError: Unable to create pointer! Function: push #1 (Not enough space)\n");
      exit(-1);
    }

    // store information on the new element
    newNode->next = top;
    newNode->node = node;

    // update top of stack
    top = newNode;    
  }
  // create top of the stack and store the node
  else
  {
    top = malloc(sizeof(Stack));

    if(top == NULL)
    {
      printf("\nError: Unable to create pointer! Function: push #1 (Not enough space)\n");
      exit(-1);
    }

    top->next = NULL;
    top->node = node;
  }

  // save increase in stack size
  (*size)++;

  // return pointer to the top element of the stack
  return top;
}

StateList* pop(Stack **top, long *size)
{
  StateList *node; 
  Stack* tmp; 

  // check if stack is empty, exit program if it is (safety measure)
  if(emptyStack(*top) == true)
  {
    printf("\n Error : Trying to pop from empty stack\n");
    exit(-1);
  }

  // move top pointer to the element below it
  tmp = *top;
  node = (*top)->node;
  (*top) = (*top)->next;

  // save decrease in stack size
  (*size)--;

  // return node that was previously on the top of the stack
  return node;
}

bool emptyStack(Stack *top)
{

  return((top == NULL) ? true : false);
}

Stack *clearStack(Stack *top)
{
  Stack *tmp;

  // go through every element of the queue and free memory allocated 
  while(top != NULL)
  {
    tmp = top;
    top = top->next;
    free(tmp);
  }

  free(top);

  return top;
}

bool stateInStack(Stack *top, State puzzle)
{
  Stack *tmp = top;

  // if the stack is empty, puzzle is not in the stack
  if(emptyStack(top) == true)
  {
    return false;
  }

  // go through every element of the stack
  while(tmp != NULL)
  {
    // compare each element with specific puzzle, return true if there's a match
    if(matchBoards(tmp->node->puzzle, puzzle) == true) 
    {
      return true;
    }

    tmp = tmp->next;
  }

  // return false if specific puzzle is not found
  return false;
}

void printStack(Stack *top)
{
  Stack *tmp = top;

  // go through every element of the stack
  while(tmp != NULL)
  {
    // print puzzle onto terminal
    printBoard(tmp->node->puzzle.board);
    tmp = tmp->next;
  }
}

/*
*
*
* Queue Functions
*
*/

void enqueue(Queue **first, Queue **last, StateList *node, long *queue_size)
{

  // queue not empty, store node in new element of the queue
  if(emptyQueue(*first) == false)
  {
    Queue *tmp = (Queue *)malloc(sizeof(Queue));

    if(tmp == NULL)
    {
      printf("\nError: Unable to create pointer! Function: enqueue #1 (Not enough space)\n");
      exit(-1);
    }

    // store information on the new element and placed in the end of the queue
    (*last)->next = tmp;
    tmp->node = node;
    tmp->next = NULL;
 
    (*last) = tmp;
  }
  else
  {
    // allocate memory for the first node on the list
    *first = (Queue *)malloc(sizeof(Queue));

    if((*first) == NULL)
    {
      printf("\nError: Unable to create pointer! Function: enqueue #2 (Not enough space)\n");
      exit(-1);
    }

    // store information on the new element
    (*first)->next = NULL;
    (*first)->node = node;
    *last = *first;
  }

  // save increase in queue size
  (*queue_size)++;
}

StateList *dequeue(Queue **first, Queue **last, long *queue_size)
{
  Queue *tmp = *first;
  StateList *node;
 
  // check if queue is empty, exit program if it is (safety measure)
  if(emptyQueue(*first) == true)
  {
    printf("\n Error : Empty queue\n");
    exit(-1);
  }
  // check if there are more than one element on the queue
  else if(tmp->next != NULL)
  {
    node = tmp->node;
    (*first) = (*first)->next;
    free(tmp);
  }
  else
  {
    node = tmp->node;
    (*first) = NULL;
    (*last) = NULL;
  }

  // save decrease in queue size
  (*queue_size)--;

  // return first element of the queue
  return node;
}

bool emptyQueue(Queue *first)
{

  return( (first == NULL) ? true : false);
}

void clearQueue(Queue *first, Queue *last)
{
  Queue *tmp;

  // go through every element of the queue and free memory allocated 
  while(first != NULL)
  {
    tmp = first;
    first = first->next;
    free(tmp);
  }

  first = NULL;
  last = NULL;
}

/*
*
*
* Priority Queue Functions
*
*/

void enPqueue(PQueue **first, PQueue **last, long *pqueue_size, StateList *node, int *max_cost)
{

  // priority queue not empty, store node in new element of the queue
  if(emptyPQueue(*first) == false)
  {

    PQueue *tmp = (PQueue *)malloc(sizeof(PQueue));

    PQueue *aux = (*first);

    if(tmp == NULL)
    {
      printf("\nError: Unable to create pointer! Function: enPqueue #1 (Not enough space)\n");
      exit(-1);
    }

    // store information on the new element
    tmp->node = node;
    tmp->next = NULL;

    // check if new node's cost is lower or equal than the node in the first position
    if((*first)->node->cost >= node->cost)
    {
      tmp->next = *first;
      (*first) = tmp;
    }
    // check if new node's cost is higher or equal than the node in the last position
    else if((*last)->node->cost <= node->cost)
    {
      (*last)->next = tmp;
      (*max_cost) = node->cost;
      (*last) = tmp;
    }
    // go through the priority queue and place new node in the correct position
    else
    {
      while(aux->next != NULL && (aux->next)->node->cost <= node->cost)
      {
        aux = aux->next;
      }

      tmp->next = aux->next;
      aux->next = tmp;

      if(aux->next == NULL)
      {
        (*last) = aux;
      }
    }
  }
  // allocate memory for the first node on the priority queue
  else
  {
    PQueue *tmp = (PQueue *)malloc(sizeof(PQueue));

    tmp->node = node;
    tmp->next = NULL;

    (*first) = tmp;
    (*last) = tmp;
    (*max_cost) = node->cost;
  }  

  // save increment in priority queue size
  (*pqueue_size)++;
}

StateList *dePqueue(PQueue **first, PQueue **last, long *pqueue_size)
{
  PQueue *tmp = (*first);
  StateList *node;
 
  // check if queue is empty, exit program if it is (safety measure)
  if(emptyPQueue(*first) == true)
  {
    printf("\n Error : Empty priority queue\n");
    exit(-1);
  }
  // check if there are more than one element on the priority queue
  else if(tmp->next != NULL)
  {
    node = tmp->node;
    (*first) = (*first)->next;
    free(tmp);
  }
  else
  {
    node = (*first)->node;
    (*first) = NULL;
    (*last) = NULL;
  }

  // save decrease in queue size
  (*pqueue_size)--;

  // return highest priority element
  return node;
}

bool stateInClosed(LinkedList *head, State puzzle, int *cost)
{
  LinkedList *tmp = head;

  // if the priority queue is empty, puzzle is not in the priority queue
  if(emptyList(head) == true)
  {
    return false;
  }

  // go through every element of the priority queue
  while(tmp != NULL)
  {
    // compare each element with specific puzzle. If there's a match, save cost and return true
    if(matchBoards(tmp->node->puzzle, puzzle) == true) 
    {
      *cost = tmp->node->cost;
      return true;
    }

    tmp = tmp->next;
  }

  // return false if specific puzzle is not found
  return false;
}

bool emptyPQueue(PQueue *first)
{

  return( (first == NULL) ? true : false);
}

void clearPQueue(PQueue *first, PQueue *last)
{
  PQueue *tmp;

  // go through every element of the queue and free memory allocated 
  while(first != NULL)
  {
    tmp = first;
    first = first->next;
    free(tmp);
  }

  last = NULL;
}

void printPQueue(PQueue *first)
{
  PQueue *tmp = first;

  // go through every element of the priority queue
  while(tmp != NULL)
  {
    // print puzzle onto terminal
    printBoard(tmp->node->puzzle.board);
    tmp = tmp->next;
  }
}

int findMax(PQueue *first)
{
  PQueue *tmp = first;

  int max = -1;

  // go through every element of the priority queue
  while(tmp != NULL)
  {
    // update maximum value
    if(tmp->node->cost > max)
    {
      max = tmp->node->cost;
    }

    tmp = tmp->next;
  }

  // return maximum value
  return max;
}
