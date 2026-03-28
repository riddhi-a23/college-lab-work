#include <stdio.h>
#include <stdlib.h>

#define V_COUNT 6
#define E_COUNT 9

typedef struct Edge {
    int u, v, weight;
} Edge;

typedef struct subset {
    int parent;
    int rank;
} subset;

int find(subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int compareEdges(const void* a, const void* b) {
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight - b1->weight; 
}

void kruskalMST(Edge edges[]) {
    Edge result[V_COUNT]; 
    int e = 0; 
    int i = 0; 

    qsort(edges, E_COUNT, sizeof(edges[0]), compareEdges);

    subset* subsets = (subset*)malloc(V_COUNT * sizeof(subset));
    for (int v = 0; v < V_COUNT; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V_COUNT - 1 && i < E_COUNT) {
        Edge next_edge = edges[i++];
        int x = find(subsets, next_edge.u);
        int y = find(subsets, next_edge.v);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    int minimumCost = 0;
    printf("Edges included in the MST (listed in the order they were added):\n");
    for (i = 0; i < e; ++i) {
        printf("Step %d: Edge C%d - C%d \tCost: %d\n", i + 1, result[i].u + 1, result[i].v + 1, result[i].weight);
        minimumCost += result[i].weight;
    }
    
    printf("\nTotal Minimum Cost: %d lakhs\n", minimumCost);
    
    printf("Order of edges added: ");
    for (i = 0; i < e; ++i) {
        printf("(C%d, C%d) ", result[i].u + 1, result[i].v + 1);
    }
    printf("\n");
}

int main() {
    Edge edges[E_COUNT] = {
        {0, 1, 3}, {0, 2, 1}, {0, 3, 6},
        {1, 2, 5}, {1, 4, 3}, {2, 3, 5},
        {2, 5, 4}, {3, 5, 2}, {4, 5, 6}
    };

    kruskalMST(edges);
    return 0;
}