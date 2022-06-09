#include <stdio.h>
#include <stdlib.h>
#include "tcb.h"
// OScar Veloria Code

typedef struct myQueue {
  TCB_t* head;
  TCB_t* tail;
} myQueue;

// returns a newpointer of tcb_t item
struct TCB_t *myNewItem() {
    struct TCB_t *newItem = malloc(sizeof(struct TCB_t));
    return newItem;
}

myQueue* initializeQueue() {
  return (myQueue*) malloc(sizeof(myQueue));
}

void AddQ(myQueue* queue, TCB_t* item) {

  if (queue->head == NULL) {
    queue->head = item;
    queue->tail = item;
    return;
  } 

  if(queue->head == queue->tail){
    item->prev = queue->tail;
    item->next = NULL;
    queue->tail->next = item;
    queue->tail = item;
  } else {

    TCB_t* newItem = item;
    newItem->prev = queue->tail;
    newItem->next = NULL;
    queue->tail->next = newItem;
    queue->tail = newItem;
  }
}

TCB_t* DeleteQ(myQueue* thisQueue) {
  if (thisQueue->head!=NULL) {

      TCB_t* popElement = thisQueue->head;

      if (thisQueue->head == thisQueue->tail) {
        thisQueue->head = NULL;
        thisQueue->tail = NULL;

      } else {

        thisQueue->head = thisQueue->head->next;
        thisQueue->head->prev = NULL;
      }

      return popElement;
  } else {
    return thisQueue->head;
  }

}

void RotateQueue(myQueue* thisQueue) {
  if (thisQueue->head != NULL) {
    // we delete the head from thisQueue and pop it out using DeleteQ()
    TCB_t* elementPop = DeleteQ(thisQueue);
    // add the popped out element to thisQueue
    AddQ(thisQueue, elementPop);
  } else {
    int x = 0 + 1;
  }
}