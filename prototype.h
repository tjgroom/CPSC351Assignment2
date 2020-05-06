#include "process.h"
#include "queue.h"
#include "memory.h"

// generate process list based on the contents of the filepath
PROCESS* assignProcList(const char* file_path);

char* getPrefix(int time); // returns a string or a tab depending on what has been announced on the clock tick
int getProcNum(FILE* file_ptr); // retrieves the number of processes
int main(); // main function

// prompts the user for the numeric input and validates it with the provided pointer
int numericInput(const char* output, int (*func)(int));
void assignMemory(int time); // assigns available memory to waiting processes
void clear_stdin(char* buf); // clears remaining chars from stdin
void terminateProc(int time); // removes completed processes from memory
void enqueueProcs(int time); // adds new processes to the input queue

// prompts the user to enter the input
void getInput(int* mem, int* page, char* file_path);
int isOneTwoOrThree(int t) // determines if the input ranges from 1 to 3
void mainLoop(); // main program loop
int isMultOfHundred(int t); // determines if the input is a multiple of 100
void printAvgTurnAround(); // displays the average turnaround time
void getFileName(char* res); // promts the user to enter a file name