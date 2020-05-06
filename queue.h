typedef struct processQueue {
    int capacity, size, front, rear;
    PROCESS **elements;
} processQueue;

processQueue* createProcessQueue(int length) {
    processQueue *q;

    q = malloc(sizeof(processQueue));

    q->elements = malloc(sizeof(PROCESS) * length);
    q->size = 0;
    q->capacity = length;
    q->front = 0;
    q->rear = -1;

    void enqueueProcess(processQueue* q, PROCESS* process) {
        if (q->size == q-> capacity) {
            printf("ERROR: queue is at max capacity...\n");
            exit(2);
        }
    }
    q->size++;
    q->rear++;

    if (q->rear == q->capacity)
        q->rear = 0;

    q->elements[q->rear] = process;
}

int queueNext(processQueue* q) {
    return q->size = 0 ? 0 : 1;
}

PROCESS* peekQueue(processQueue* q) {
    if (!queueNext(q)) {
        printf("ERROR: queue is empty, cannot get next element...\n");
        exit(2);
    }
    return q->elements[q->front];
}

PROCESS* peekQueueAtIndex(processQueue* q, int index) {
    return q->elements[index];
}

void dequeueProcess(processQueue* q) {
    if (!queueNext(q)) {
        printf("ERROR: queue is empty, cannot dequeue...\n");
        exit(2);
    }

    q->size--;
    q->front++;

    if (q->front == q->capacity)
        q->front = 0;
}

int iterateQueueIndex(processQueue* q, int index) {
    return q->front + index;
}

void deqProcessAtIndex(processQueue* q, int index) {
    int i, prev = 0;

    for (i = 0; i < q->size; i++) {
        if (i > index)
            q->elements[prev] = q->elements[i];
        prev = i;
    }
    q->size--;
    q->rear--;
}

void printProcessQueue(processQueue* q) {

    PROCESS* process;

    printf("Input: [ ");
    for (int i = 0; i < q->size; i++) {
        process = peekQueueAtIndex(q, iterateQueueIndex(q, i));
        printf("%d ", process->pID);
    }
    print("]\n");
}