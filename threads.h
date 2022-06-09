#include "q.h"

myQueue* runQueue;
// creates a thread stack and its to the queue
void start_thread(void (*function)(int, int), int threadID) {
  void *stack = (void *)malloc(8192);    
  struct TCB_t* tcb = (TCB_t*) malloc(sizeof(TCB_t)); // allocate a TCB (via malloc)
  init_TCB(tcb, function, stack, 8192, threadID); // call init_TCB with appropriate arguments
  AddQ(runQueue, tcb); // call addQ to add this TCB into the “runQueue” which is a global header pointer
}

// runs first thread in queue
void run() {
  ucontext_t parent; // place to store the main context
  getcontext(&parent); // stores process' context in parent var
  swapcontext(&parent, &(runQueue->head->context)); // saves current context (state of stack pointer, function, etc.) and loads next context from thread queue then runs thread
}

// runs next thread in queue and moves current thread to back of queue
void yield() {
  ucontext_t* temp = &(runQueue->head->context);
  RotateQueue(runQueue); 
  // swap the context, from previous thread to new thread at head of queue
  swapcontext(temp, &(runQueue->head->context)); 
}