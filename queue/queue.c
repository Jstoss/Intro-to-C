#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

typedef struct Queue {
    unsigned int length;
    unsigned int capacity;
    int *storage;
} Queue;

/*
    Creates a queue by allocating the appropriate amount of memory for an
    instance of the Queue struct, and initializes all of the fields of the
    struct. Also allocates memory for the queue's storage structure.
*/
Queue *createQueue(unsigned capacity)
{
  Queue *newQ = malloc(sizeof(Queue));
  newQ->storage = malloc(capacity * sizeof(int));
  newQ->length = 0;
  newQ->capacity = capacity;
  return newQ;
}

/*
    Adds the given item to the end of the queue. If the queue does
    not have room, expand the queue's available storage so that it
    does have room for the additional item.
*/
void enqueue(Queue *q, int item)
{
  if(q->length == q->capacity)
  {
    int oldCap = q->capacity;
    int newCap = q->capacity * 2;
    q->storage = resize_memory(q->storage, oldCap, newCap);
    q->capacity = newCap;
  }
  q->storage[q->length] = item;
  q->length++;
}

/*
    Removes the item at the front of the queue. If the queue is empty,
    this function should return -1.
*/
int dequeue(Queue *q)
{
  if(q->length == 0)
  {
    return -1;
  }
  else
  {
    int returnItem = q->storage[0];
    for(unsigned int i = 0; i< q->length; i++)
    {
      q->storage[i] = q->storage[i + 1];
    }
    q->length--;
    return returnItem;
  }
}

/*
    Frees the memory used to hold the queue instance and its
    associated storage.
*/
void destroyQueue(Queue *q)
{
  free(q->storage);
  free(q);
}


#ifndef TESTING
int main(void)
{
    Queue *q = createQueue(4);

    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);
    enqueue(q, 6);

    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));

    destroyQueue(q);

    return 0;
}
#endif
