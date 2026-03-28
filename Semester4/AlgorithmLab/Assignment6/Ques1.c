#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100
#define E_SPARSE 120
#define E_DENSE 4500

typedef struct Node {
    int dest;
    int weight;
    struct Node* next;
} Node;

int sparse_edges[N][N] = {0};
int dense_edges[N][N] = {0};

Node* sparse_adj_list_unweighted[N] = {NULL};
Node* sparse_adj_list_weighted[N] = {NULL};

int dense_adj_matrix_unweighted[N][N] = {0};
int dense_adj_matrix_weighted[N][N] = {0};

void addEdgeList(Node* adj_list[], int src, int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = adj_list[src];
    adj_list[src] = newNode;
    
    newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = src;
    newNode->weight = weight;
    newNode->next = adj_list[dest];
    adj_list[dest] = newNode;
}

int main() {
    srand(time(NULL));
    int u, v, w, count;

    count = 0;
    while (count < E_SPARSE) {
        u = rand() % N;
        v = rand() % N;
        if (u != v && !sparse_edges[u][v]) {
            w = (rand() % 50) + 1; 
            sparse_edges[u][v] = 1;
            sparse_edges[v][u] = 1;
            addEdgeList(sparse_adj_list_unweighted, u, v, 1);
            addEdgeList(sparse_adj_list_weighted, u, v, w);
            count++;
        }
    }

    count = 0;
    while (count < E_DENSE) {
        u = rand() % N;
        v = rand() % N;
        if (u != v && !dense_edges[u][v]) {
            w = (rand() % 50) + 1;
            dense_edges[u][v] = 1;
            dense_edges[v][u] = 1;
            
            dense_adj_matrix_unweighted[u][v] = 1;
            dense_adj_matrix_unweighted[v][u] = 1;
            
            dense_adj_matrix_weighted[u][v] = w;
            dense_adj_matrix_weighted[v][u] = w;
            count++;
        }
    }

    printf("Graphs Generated Successfully.\n");
    printf("\nSparse Graph Adjacency List (Weighted) - First 5 Vertices:\n");
    for (int i = 0; i < 5; i++) {
        printf("Vertex %d: ", i);
        Node* temp = sparse_adj_list_weighted[i];
        while (temp) {
            printf("-> %d(w:%d) ", temp->dest, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }

    return 0;
}