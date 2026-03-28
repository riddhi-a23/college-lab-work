#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Edge { int u, v, weight; } Edge;
typedef struct subset { int parent; int rank; } subset;

int find(subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank) subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank) subsets[yroot].parent = xroot;
    else { subsets[yroot].parent = xroot; subsets[xroot].rank++; }
}

int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

int kruskalMST(Edge edges[], int V, int E) {
    qsort(edges, E, sizeof(edges[0]), compareEdges);
    subset* subsets = (subset*)malloc(V * sizeof(subset));
    for (int v = 0; v < V; ++v) { subsets[v].parent = v; subsets[v].rank = 0; }

    int mst_cost = 0;
    int e = 0, i = 0;
    printf("\n--- G1 MST Edges (Kruskal) ---\n");
    while (e < V - 1 && i < E) {
        Edge next_edge = edges[i++];
        int x = find(subsets, next_edge.u);
        int y = find(subsets, next_edge.v);
        if (x != y) {
            printf("%d - %d \tCost: %d\n", next_edge.u, next_edge.v, next_edge.weight);
            mst_cost += next_edge.weight;
            Union(subsets, x, y);
            e++;
        }
    }
    return mst_cost;
}

int minKey(int key[], int mstSet[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

int primMST(int** graph, int V) {
    int* parent = (int*)malloc(V * sizeof(int));
    int* key = (int*)malloc(V * sizeof(int));
    int* mstSet = (int*)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) { key[i] = INT_MAX; mstSet[i] = 0; }
    key[0] = 0; parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = 1;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u; key[v] = graph[u][v];
            }
    }

    int mst_cost = 0;
    printf("\n--- G2 MST Edges (Prim) ---\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d \tCost: %d\n", parent[i], i, graph[i][parent[i]]);
        mst_cost += graph[i][parent[i]];
    }
    return mst_cost;
}

int main() {
    int V1, E1, V2, E2;

    printf("Enter number of vertices and edges for G1: ");
    scanf("%d %d", &V1, &E1);
    Edge* edges1 = (Edge*)malloc(E1 * sizeof(Edge));
    printf("Enter edge list for G1 (u v weight):\n");
    for (int i = 0; i < E1; i++) {
        scanf("%d %d %d", &edges1[i].u, &edges1[i].v, &edges1[i].weight);
    }

    printf("Enter number of vertices and edges for G2: ");
    scanf("%d %d", &V2, &E2);
    int** graph2 = (int**)malloc(V2 * sizeof(int*));
    for (int i = 0; i < V2; i++) graph2[i] = (int*)calloc(V2, sizeof(int));
    
    printf("Enter edge list for G2 (u v weight):\n");
    for (int i = 0; i < E2; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph2[u][v] = w;
        graph2[v][u] = w; 
    }

    int c_u, c_v, c_w;
    printf("Enter the high-capacity transmission edge connecting G1 and G2 (u in G1, v in G2, weight): ");
    scanf("%d %d %d", &c_u, &c_v, &c_w);

    int cost1 = kruskalMST(edges1, V1, E1);
    int cost2 = primMST(graph2, V2);

    printf("\n--- Global Network MST ---\n");
    printf("Connecting Edge: G1(%d) - G2(%d) \tCost: %d\n", c_u, c_v, c_w);
    int total_global_cost = cost1 + cost2 + c_w;
    printf("\nTotal Cost of Global Spanning Tree: %d\n", total_global_cost);

    return 0;
}