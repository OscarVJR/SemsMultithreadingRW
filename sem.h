#include "threads.h"

typedef struct Semaphore {
  int semVal;
  myQueue* semQueue; // queue for the blocked threads
} Semaphore;

void P(Semaphore* sema) {
  while (1) {
    if (sema->semVal <= 0) {
      TCB_t* element = DeleteQ(runQueue);
      AddQ(sema->semQueue, element);

      if (runQueue->head==NULL){
        return;
      }


      swapcontext(&(sema->semQueue->tail->context), &(runQueue->head->context));
    } else {

      sema->semVal--;
      return;
    }
  }
}

void V(Semaphore* sema) {

  if (sema->semQueue->head != NULL) {
    TCB_t* threadBlock = DeleteQ(sema->semQueue);
    AddQ(runQueue, threadBlock);
  }
  sema->semVal++;
}

Semaphore* InitializeSem(int val) {
  Semaphore* sem = (Semaphore*) malloc(sizeof(Semaphore));
  sem->semVal = val;
  sem->semQueue = initializeQueue();
  return sem;
}
