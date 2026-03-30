#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

void BellmanFord(struct Graph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    int dist[V];

    for (int i = 0; i < V; i++)
        dist[i] = INF;
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INF && dist[u] + weight < dist[v]) 
                dist[v] = dist[u] + weight;
        }
    }

    int hasNegativeCycle = 0;
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            hasNegativeCycle = 1;
            break;
        }
    }

    if (hasNegativeCycle) {
        printf("\nGraph contains a negative weight cycle!\n");
        printf("Shortest path values are undefined as they can decrease indefinitely.\n");
    } else {
        printf("\nVertex   Distance from Source %d\n", src);
        for (int i = 0; i < V; i++) {
            if (dist[i] == INF)
                printf("%d \t\t INF\n", i);
            else
                printf("%d \t\t %d\n", i, dist[i]);
        }
    }
}

int main() {
    int v_count, e_count, source;

    printf("Enter number of vertices: ");
    scanf("%d", &v_count);
    printf("Enter number of edges: ");
    scanf("%d", &e_count);

    struct Graph* graph = createGraph(v_count, e_count);

    for (int i = 0; i < e_count; i++) {
        printf("Enter edge %d (src dest weight): ", i + 1);
        scanf("%d %d %d", &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight);
    }

    printf("Enter source vertex: ");
    scanf("%d", &source);

    BellmanFord(graph, source);

    return 0;
}