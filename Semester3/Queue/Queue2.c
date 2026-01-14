#include<stdio.h>

#include<stdlib.h>

#include<time.h>



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

    return *dp;

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

    int N,num;

    printf("Enter queue size:");

    scanf("%d",&N);

    N++;

    queue *myQueue = createIntegerQueue(N);

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

        current = (current+1)%N;

    }

    srand(time(NULL)); //Advancement

    // int rValue = 3;

    int rValue = (rand()%9)+1; //Advancement

    printf("\n\nrValue is %d.\n",rValue);

    while(!isIntegerQueueEmpty(myQueue)){

        int smth = dequeueInteger(myQueue,&num);

        int qElement = smth;

        qElement = qElement - rValue;

        if(qElement>0){

            enqueueInteger(myQueue,qElement);

            printf("Enqueued updated qelement %d back to the queue.\n", qElement);

        }

        else {

         printf("Dequeued element %d.\n", smth);

        }

    }

    printf("\nQueue is empty now.\n");

    freeIntegerQueue(myQueue);

    return 0;

}
