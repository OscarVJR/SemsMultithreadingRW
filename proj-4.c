
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"

int wwc; //waiting Writers
int wc;  //Writers in Scratchpad
int globalVar = 0;
int numReaders; 
int numWriters;
Semaphore* readerSem;
Semaphore* writerSem;
//waiting Readers
int wrc; 
//readers in Scratch pad
int rc; 

// he gave us the exact pseudocode in Module 3 video
void writerFunc(int writerNumber) {
  if (wrc > 0 || wwc > 0 || rc > 0 || wc > 0 ) {

    wwc++;
    P(writerSem);
    wwc--;
  }
  wc++;

  globalVar++;
  printf("\n This is the %d th writer writing value i = %d \n", writerNumber, globalVar );
  yield();

  printf("\n This is the %d th writer verifying value i = %d \n", writerNumber, globalVar );

  wc--;
  if (wrc > 0) {
    for (int j = 0; j < wrc; j++) V(readerSem);
  } else if (wwc > 0) {
    V(writerSem);
  }

  TCB_t* item = DeleteQ(runQueue);
  if (runQueue->head != NULL) {
    swapcontext(&(item->context), &(runQueue->head->context));
  }
}

// he gave us the exact pseudocode in Module 3 video
void readerFunc(int readerID) {

  if (wwc > 0 || wc > 0) {
    wrc++;
    P(readerSem);
    wrc--;
  }
  //increment reader count for scratchpad
  rc++;
  printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, globalVar);

  yield();

  printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, globalVar);
  //decrement reader count from scratchpad
  rc--;
  if ( wwc > 0 && rc == 0 ) {
    V(writerSem);
  }

  TCB_t* item = DeleteQ(runQueue);

  if (runQueue->head != NULL) {
    swapcontext(&(item->context), &(runQueue->head->context));
  }
}


int main() {

  int readerSemValue = 0;
  int writerSemValue = 0;

  readerSem = InitializeSem(readerSemValue);
  writerSem = InitializeSem(writerSemValue);

  runQueue = initializeQueue();
  int total = 0;

  scanf("%d, %d",&numReaders, &numWriters);

  total = numReaders + numWriters + 0;


  for (int i = 1; i <= total; i++) {

    int thread_ID;

    scanf("%d", &thread_ID);

    void* fxn = thread_ID > 0 ? readerFunc : writerFunc;

    if (thread_ID < 0) {
      thread_ID *= -1;
    }

    start_thread(fxn, thread_ID);
  }

  run();

  return 0;
}
