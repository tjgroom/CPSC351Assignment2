#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "prototype.h"

// global constants
const int MAX_TIME = 100000;

int n = 0;
int last_announcement = -1;
PROCESS* processList;
processQueue* queue;
frameList* frList;

void mainLoop() {
    long time = 0;

    while (1) {
        enqueueProcs(time); // queue the new processes
        terminateProc(time); // terminates the completed processes
        assignMemory(time); // assigns available memory to a process if necessary

        time++;
        
        if (time > MAX_TIME) {
            printf("DEADLOCK: reached maximum time\n")
            break;
        }

        if (queue->size == 0 && listIsEmpty(frList))
            break;
    }

    printAvgTurnAround();
}

int main() {
    int pageSize = 0;
    int memSize = 0;
    char* filePath = malloc(100 * sizeof(char));

    getInput(&memSize, &pageSize, filePath);

    queue = createProcessQueue(n)

    frList = createFrameList(memSize / pageSize, pageSize);
    mainLoop();

    return 0;
}

void enqueueProcs(int time) {
    PROCESS* process;

    for (int i = 0; i < n; i++) {
        process = &processList[i];

        if (process->arrivalTime == time) {
            printf("%sProcess %d arrives\n", getPrefix(time), process->pID);

            enqueueProcess(queue, process);

            printProcessQueue(queue);
            printFrameList(frList);
        }
    }
}

void terminateProc(int time) {
    int timeInMem;
    PROCESS* process;

    for (int i = 0; i < n; i++) {
        process = &processList[i];
        timeInMem = time - process->timeAdded;

        if (process->isActive && (timeInMem >= process->lifeTime)) {
            printf("%sProcess %d completes\n", getPrefix(time), process->pID);

            process->isActive = 0;
            process->timeFinished = time;

            freeMemory(frList, process->pID);
            printFrameList(frList);
        }
    }
}

void assignMemory(int time) {
    int index, limit;
    limit = queue->size;

    for (int i = 0; i < limit; i++) {
        index = iterateQueueIndex(queue, i);
        process = queue->elements[index];

        if (procFitsInMemory(frList, process)) {
            printf("%sMM moves Process %d to memory\n", getPrefix(time), process->pID);

            fitProcsIntoMem(frList, process);

            process->isActive = 1;
            process->timeAdded = time;

            deqProcessAtIndex(queue, i);
            printProcessQueue(queue);
            printFrameList(frList);
        }
    }
}

char* getPrefix(int time) {
    char* result;

    result = malloc(20 * sizeof(char));

    if (last_announcement == time)
        sprintf(result, "\t");
    else
        sprintf(result, "t = %d: ", time);
    last_announcement = time;

    return result;
}

void printAvgTurnAround() {
    float total = 0;

    for (int i = 0; i < n; i++)
        total += processList[i].timeFinished - processList[i].arrivalTime;
    
    printf("Average Turnaround Time: %2.2f\n", total / n);
}

void isMultOfHundred(int t) {
    return (t % 100) == 0 ? 1 : 0;
}

void isOneTwoOrThree(int t) {
    return (t >- 1 && t <= 3) ? 1 : 0;
}

void clear_stdin(char* buf) {
    if (buf[strlen(buf) - 1] != '\n') {
        int ch;
        while (((ch = getchar()) != '\n') && (ch != EOF));
    }
}

int numericInput(const char* output, int (*func)(int)) {
    char buf[10];
    int success = 0;
    int res = 0;

    while (!success) {
        printf("%s: ", output);

        if (fgets(buf, 10, stdin) == NULL) {
            clear_stdin(buf);
            printf("ERROR: No data entered...\n");

            continue;
        }

        if (sscanf(buf, "%d", &res) <= 0) {
            clear_stdin(buf);
            printf("ERROR: No number entered...\n");

            continue;
        }

        if (!(success = (*func)(res))) {
            clear_stdin(buf);
            printf("ERROR: Invalid number entry...\n");
        }
    }
    return res;
}

void getFileName(char* res) {
    char buf[100];
    FILE* fp;

    while (1) {
        printf("Input file: ");

        if (fgets(buf, 100, stdin) == NULL) {
            clear_stdin(buf);
            printf("ERROR: No data entered...\n");

            continue;
        }

        if (sscanf(buf, "%s", res) <= 0) {
            clear_stdin(buf);
            printf("ERROR: No string entered...\n");

            continue;            
        }

        if (!(fp = fopen(res, "r")))
            perror("ERROR: Failed to open file!\n");
        else
            break;
    }
}

void getInput(int* mem, int* page, char* file_path) {
    while (1) {
        *mem = numericInput("Memory size", isMultOfHundred);
        *page = numericInput("Page size (1: 100, 2: 200, 3: 400)", isOneTwoOrThree);

        switch (*page) {
            case 1: *page = 100; break;
            case 2: *page = 200; break;
            case 3: *page = 400; break;
        }

        if ((*mem) % (*page) == 0) 
            break;
        
        printf("ERROR: %d is not a multiple of %d...\n", *mem, *page);
    }
    getFileName(file_path);
}

int getProcNum(FILE* file_ptr) {
    int num = 0;

    fscanf(file_ptr, "%d", &num);
    return num;
}

PROCESS* assignProcList(const char* file_path) {
    int numSpace, tmp, counter, total_space;
    counter = total_space = 0;
    FILE* file_ptr = fopen(file_path, "r");

    n = getProcNum(file_ptr);

    PROCESS* processList = malloc(n * sizeof(PROCESS));

    if (!file_ptr) {
        printf("ERROR: failed to open file...\n");
        exit(1);
    }

    while (!eof(file_ptr) && counter < n) {
        fscanf(file_ptr, "%d %d %d %d", &(processList[counter].pID), &(processList[counter].arrivalTime), &(processList[counter].lifeTime), &numSpace);

        total_space = 0;
        for (int i = 0; i < numSpace; i++) {
            fscanf(file_ptr, "%d", &tmp);
            total_space = total_space + tmp;
        }
        processList[counter].memoryReqs = total_space;
        
        processList[counter].isActive = 0;
        processList[counter].timeAdded = -1;
        processList[counter].timeFinished = -1;

        counter++;
    }

    fclose(file_ptr);
    return processList;
}


