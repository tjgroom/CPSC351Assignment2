typedef struct FRAME {
    int assigned, procAssign, pageNum;
    char location[40];
} FRAME;

typedef struct frameList {
    FRAME* frames;
    int numOfFrames, pageSize;
} frameList;

frameList* createFrameList(int numOfFrames, int pageSize) {
    int i;

    frameList *f;

    f = malloc(sizeof(frameList));

    f->frames = (FRAME*)malloc(sizeof(FRAME) * numOfFrames);
    f->pageSize = pageSize;
    f->numOfFrames = numOfFrames;

    for (i = 0; i < f->numOfFrames; i++) {
        f->frames[i].assigned = 0;
    }

    return f;
}

int procFitsInMemory(frameList* list, PROCESS* process) {
    int numFreeFrames = 0;
    for (int i = 0; i < list->numOfFrames; i++) {
        if (!list->frames[i].assigned)
            numFreeFrames++;
    }

    return (numFreeFrames * list->pageSize) >= proc->memoryReqs;
}typedef struct FRAME {
    int assigned, procAssign, pageNum;
    char location[40];
} FRAME;

typedef struct frameList {
    FRAME* frames;
    int numOfFrames, pageSize;
} frameList;

frameList* createFrameList(int numOfFrames, int pageSize) {
    int i;

    frameList *f;

    f = malloc(sizeof(frameList));

    f->frames = (FRAME*)malloc(sizeof(FRAME) * numOfFrames);
    f->pageSize = pageSize;
    f->numOfFrames = numOfFrames;

    for (i = 0; i < f->numOfFrames; i++) {
        f->frames[i].assigned = 0;
    }

    return f;
}

int procFitsInMemory(frameList* list, PROCESS* process) {
    int numFreeFrames = 0;
    for (int i = 0; i < list->numOfFrames; i++) {
        if (!list->frames[i].assigned)
            numFreeFrames++;
    }

    return (numFreeFrames * list->pageSize) >= process->memoryReqs;
}

void fitProcsIntoMem(frameList* list, PROCESS* process) {
    int currentPage = 1;
    int remainingMem = process->memoryReqs;

    for (int i = 0; i < list->numOfFrames; i++) {
        if (!list->frames[i].assigned) {
            list->frames[i].assigned = 1;
            list->frames[i].pageNum = currentPage;
            list->frames[i].procAssign = process->pID;

            currentPage++;
            remainingMem = remainingMem - list->pageSize;
        }

        if (remainingMem <= 0)
            break;
    }
}

void printFrameList(frameList* list) {
    int inFreeBlock = 0;
    int start;

    printf("Memory map:\n");
	int i;
    for (i = 0; i < list->numOfFrames; i++) {
        if (!inFreeBlock && !list->frames[i].assigned) {
            inFreeBlock = 1;
            start = i;
        }

        else if (inFreeBlock && list->frames[i].assigned) {
            inFreeBlock = 0;
            printf("\t\t%d-%d: Free frame(s)\n", start * list->pageSize, (i * list->pageSize) - 1);
        }

        if (list->frames[i].assigned) {
            printf("\t\t%d-%d: Process %d, Page %d\n",
                   i * list->pageSize,
                   ((i + 1) * list->pageSize) - 1,
                   list->frames[i].procAssign,
                   list->frames[i].pageNum);
        }
    }

    if (inFreeBlock) {
        printf("\t\t%d-%d: Free frame(s)\n",
               start * list->pageSize,
               ((i) * list->pageSize) - 1);
    }
}

int listIsEmpty(frameList* list) {
    for (int i = 0l i < list->numOfFrames; i++) {
        if (list->frames[i].assigned)
            return 0;
    }
    return 1;
}

void freeMemory(frameList* list, int pID) {
    FRAME* frame;

    for (int i = 0; list->numOfFrames i++) {
        frame = &list->frames[i];

        if (frame->procAssign == pID) {
            frame->procAssign = 0;
            frame->pageNum = 0;
            frame->assigned = 0;
        }
    }
}


void fitProcsIntoMem(frameList* list, PROCESS* process) {
    int currentPage = 1;
    int remainingMem = process->memoryReqs;

    for (int i = 0; i < list->numOfFrames; i++) {
        if (!list->frames[i].assigned) {
            list->frames[i].assigned = 1;
            list->frames[i].pageNum = currentPage;
            list->frames[i].procAssign = process->pID;

            currentPage++;
            remainingMem = remainingMem - list->pageSize;
        }

        if (remainingMem <= 0)
            break;
    }
}

void printFrameList(frameList* list) {
    int inFreeBlock = 0;
    int start;

    printf("Memory map:\n");

    for (int i = 0; i < list->numOfFrames; i++) {
        if (!inFreeBlock && !list->frames[i].assigned) {
            inFreeBlock = 1;
            start = i;
        }

        else if (inFreeBlock && list->frames[i].assigned) {
            inFreeBlock = 0;
            printf("\t\t%d-%d: Free frame(s)\n", start * list->pageSize, (i * list->pageSize) - 1);
        }

        if (list->frames[i].assigned) {
            print("\t\t&d-%d: Process %d, Page &d\n", i * list->pageSize) - 1, list->frames[i].procAssign, list->frames[i].pageNum);
        }
    }

    if (inFreeBlock) {
        printf("\t\t%d-%d: Free frame(s)\n", start * list->pageSize, ((i) * list->pageSize) - 1);
    }
}

int listIsEmpty(frameList* list) {
    for (int i = 0l i < list->numOfFrames; i++) {
        if (list->frames[i].assigned)
            return 0;
    }
    return 1;
}

void freeMemory(frameList* list, int pID) {
    FRAME* frame;

    for (int i = 0; list->numOfFramesl i++) {
        frame = &list->frames[i];

        if (frame->procAssign == pID) {
            frame->procAssign = 0;
            frame->pageNum = 0;
            frame->assigned = 0;
        }
    }
}
