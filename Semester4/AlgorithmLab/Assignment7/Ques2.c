#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 10
#define INF INT_MAX

struct Node {
    int v, dist;
};

void dijkstra(int graph[V][V], int src) {
    int dist[V];
    int visited[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int min = INF, u = -1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] != 0 && dist[u] != INF 
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\n--- Dijkstra's Results (Source: %d) ---\n", src);
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF)
            printf("%d \t INF\n", i);
        else
            printf("%d \t %d\n", i, dist[i]);
    }
}

int main() {
    int graph[V][V] = {0};
    int edges, u, v, w, src;

    printf("--- Dijkstra Limitation Experiment ---\n");
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges in format (u v w). \nNote: Use negative weights to create a negative cycle.\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d %d", &u, &v, &w);
        if (u < V && v < V) {
            graph[u][v] = w;
        }
    }

    printf("Enter source vertex (0-9): ");
    scanf("%d", &src);

    dijkstra(graph, src);

    printf("\nObservation: If you included a negative cycle, note that Dijkstra \n");
    printf("cannot find the true shortest path because it never revisits 'visited' nodes.\n");

    return 0;
}