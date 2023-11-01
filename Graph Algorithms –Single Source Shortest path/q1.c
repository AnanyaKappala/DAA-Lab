/* Given a directed graph G (V, E) and a starting vertex ‘s’.
● Determine the lengths of the shortest paths from the starting vertex ‘s’ to all other
vertices in the graph G using Dijkstra’s Algorithm.
● Display the shortest path from the given source ‘s’ to all other vertices.
Note# Nodes will be numbered consecutively from 1 to n (user input), and edges will have
varying distances or lengths. The graph G can be read from an input file “inDiAdjMat1.dat” that
contains non-negative cost adjacency matrix. The expected output could be as per the sample
format.
Content of the input file “inDiAdjMat1.dat” could be
0 10 0 5 0
0 0 1 2 0
0 0 0 0 4
3 0 9 0 2
7 0 6 0 0

Input:
Enter the Number of Vertices: 5
Enter the Source Vertex: 1
Output:
Source Destination Cost Path
1 1 0 -
1 2 8 1->4->2
1 3 9 1->4->2->3
1 4 5 1->4
1 5 7 1->4->5*/
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

// Function to find the vertex with the minimum distance
int minDistance(int dist[], bool sptSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 1; v <= V; v++) {
        if (!sptSet[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the shortest path from source to vertex v
void printPath(int parent[], int v) {
    if (v == 0) {
        return;
    }
    printPath(parent, parent[v]);
    printf("%d->", v);
}

// Function to display the shortest paths and their lengths
void printShortestPaths(int dist[], int parent[], int V, int source) {
    printf("Source Destination Cost Path\n");
    for (int v = 1; v <= V; v++) {
        if (v != source) {
            printf("%d %d %d %d->", source, v, dist[v], source);
            printPath(parent, v);
            printf("\b\b\n");
        }
    }
}

// Function to perform Dijkstra's algorithm
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int V, int source) {
    int dist[MAX_VERTICES];
    bool sptSet[MAX_VERTICES];
    int parent[MAX_VERTICES];

    for (int v = 1; v <= V; v++) {
        dist[v] = INT_MAX;
        sptSet[v] = false;
    }

    dist[source] = 0;
    parent[source] = 0;

    for (int count = 1; count < V; count++) {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = true;

        for (int v = 1; v <= V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && (dist[u] + graph[u][v] < dist[v])) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printShortestPaths(dist, parent, V, source);
}

int main() {
    int V;
    printf("Enter the Number of Vertices: ");
    scanf("%d", &V);

    int source;
    printf("Enter the Source Vertex: ");
    scanf("%d", &source);

    int graph[MAX_VERTICES][MAX_VERTICES];

    FILE *file = fopen("inDiAdjMat1.dat", "r");
    if (file == NULL) {
        printf("Failed to open the input file.\n");
        return 1;
    }

    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    fclose(file);

    dijkstra(graph, V, source);

    return 0;
}
