# SemaphoresRW
Implemented the Readers and Writers Problem using Semaphores and multithreading in C++. 
Readers read the scratchpad variable, prints out current value.
Writers write their thread ID's in the variable, then verify that the correct ID is written.
Input test case example: 
2,2
  1
  -1
  2
  -2
  
First line - number of Readers and Number of Writers respectively. Followed are R+W numbers showing the ready Queue,
Positive numbers -> readers, negative numbers -> writers. Beginning scratch pad variable i is set to 0.

Output test case exmaple: 
This is the 1 th reader reading value i = 0 for the first time

 This is the 1 th reader reading value i = 0 for the second time

 This is the 1 th writer writing value i = 1

 This is the 1 th writer verifying value i = 1

 This is the 2 th reader reading value i = 1 for the first time

 This is the 2 th reader reading value i = 1 for the second time

 This is the 2 th writer writing value i = 2

 This is the 2 th writer verifying value i = 2

