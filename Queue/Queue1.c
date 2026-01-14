#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int *arr;
    int front;
    int rear;
    int size;
}queue;

queue* createIntegerQueue(int queueSize){
    queue *q = (queue *)malloc(sizeof(queue));
    if(q == NULL){
        return NULL;
    }
    q->front = 0;
    q->rear = 0;
    q->size = queueSize;
    q->arr = (int *)malloc(queueSize * sizeof(int));
    return q;
}

int isIntegerQueueFull(queue *q){
    if(q == NULL){
        return 0;
    }
    if(q->arr == NULL){
        return 0;
    }
    if((q->rear+1)%q->size == q->front){
        return 1;
    }
    return 0;
}

int isIntegerQueueEmpty(queue *q){
    if(q == NULL){
        return 0;
    }
    if(q->arr == NULL){
        return 0;
    }
    if(q->rear == q->front){
        return 1;

    }
    return 0;
}

int enqueueInteger(queue *q, int d){
    if(isIntegerQueueFull(q) || q == NULL){
        return 0;
    }
    q->arr[q->rear] = d;
    q->rear = (q->rear + 1) % q->size;

    return 1;

}



int dequeueInteger(queue *q, int *dp){

    if(isIntegerQueueEmpty(q) || q == NULL){

        return 0;

    }

    *dp = q->arr[q->front];

    q->arr[q->front] = 0;

    q->front = (q->front + 1) % q->size;

    return 1;

}



int freeIntegerQueue(queue *q){

    if(q == NULL){

        return 0;

    }

    free(q->arr);

    free(q);

    return 1;

}



int main() {

    int size,num;

    printf("Enter queue size:");

    scanf("%d",&size);

    size++;

    queue *myQueue = createIntegerQueue(size);

    while(!isIntegerQueueFull(myQueue)){

        printf("Enter element to enqueue at the end of the queue: ");

        scanf("%d",&num);

        enqueueInteger(myQueue,num);

        printf("Enqueued element %d.\n", num);

    }

    printf("\nQueue is full! Cannot enqueue.\n");

    printf("\nQueue elements: ");

    int current = myQueue->front;

    while(current!=myQueue->rear) {

        printf("%d ",myQueue->arr[current]);

        current = (current+1)%size;

    }

    printf("\n\nDequeueing elements...\n\n");

    while(!isIntegerQueueEmpty(myQueue)){

        dequeueInteger(myQueue,&num);

        printf("Dequeued element %d.\n", num);

    }

    printf("\nQueue is empty now.\n");

    freeIntegerQueue(myQueue);

    return 0;

}
