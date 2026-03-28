#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 6

typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

typedef struct MinHeapNode {
    int v;
    int key;
} MinHeapNode;

typedef struct MinHeap {
    int size;
    int capacity;
    int *pos;    
    MinHeapNode **array;
} MinHeap;

AdjListNode* newAdjListNode(int dest, int weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdge(AdjListNode* graph[], int src, int dest, int weight) {
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph[src];
    graph[src] = newNode;

    newNode = newAdjListNode(src, weight);
    newNode->next = graph[dest];
    graph[dest] = newNode;
}

MinHeapNode* newMinHeapNode(int v, int key) {
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->key = key;
    return minHeapNode;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key)
        smallest = right;

    if (smallest != idx) {
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

MinHeapNode* extractMin(MinHeap* minHeap) {
    if (minHeap->size == 0) return NULL;
    MinHeapNode* root = minHeap->array[0];
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;
    --minHeap->size;
    minHeapify(minHeap, 0);
    return root;
}

void decreaseKey(MinHeap* minHeap, int v, int key) {
    int i = minHeap->pos[v];
    minHeap->array[i]->key = key;
    while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key) {
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int isInMinHeap(MinHeap* minHeap, int v) {
    return minHeap->pos[v] < minHeap->size;
}

void primMST(AdjListNode* graph[]) {
    int parent[V]; 
    int key[V];      
    MinHeap* minHeap = createMinHeap(V);

    for (int v = 1; v < V; ++v) {
        parent[v] = -1;
        key[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, key[v]);
        minHeap->pos[v] = v;
    }
    
    key[0] = 0;
    minHeap->array[0] = newMinHeapNode(0, key[0]);
    minHeap->pos[0] = 0;
    minHeap->size = V;
    
    int add_order[V];
    int order_idx = 0;

    while (minHeap->size != 0) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; 
        add_order[order_idx++] = u;

        AdjListNode* pCrawl = graph[u];
        while (pCrawl != NULL) {
            int v = pCrawl->dest;
            if (isInMinHeap(minHeap, v) && pCrawl->weight < key[v]) {
                key[v] = pCrawl->weight;
                parent[v] = u;
                decreaseKey(minHeap, v, key[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    int total_cost = 0;
    printf("Edges in MST (Prim's):\n");
    for (int i = 1; i < V; ++i) {
        printf("C%d - C%d \tCost: %d\n", parent[i] + 1, i + 1, key[i]);
        total_cost += key[i];
    }
    printf("Total Minimum Cost: %d lakhs\n", total_cost);
    
    printf("Order of vertices added: ");
    for(int i = 0; i < V; i++) printf("C%d ", add_order[i] + 1);
    printf("\n");
}

int main() {
    AdjListNode* graph[V] = {NULL};

    addEdge(graph, 0, 1, 3); // C1-C2
    addEdge(graph, 0, 2, 1); // C1-C3
    addEdge(graph, 0, 3, 6); // C1-C4
    addEdge(graph, 1, 2, 5); // C2-C3
    addEdge(graph, 1, 4, 3); // C2-C5
    addEdge(graph, 2, 3, 5); // C3-C4
    addEdge(graph, 2, 5, 4); // C3-C6
    addEdge(graph, 3, 5, 2); // C4-C6
    addEdge(graph, 4, 5, 6); // C5-C6

    primMST(graph);
    return 0;
}