/* Given a directed weighted graph G (V, E) where weight indicates
distance. Vertices will be numbered consecutively from 1 to n (user input), and edges will have
varying distances or lengths.

● Determine the length of the shortest path between every pair of vertices using Floyd-
Warshall’s algorithm.

● Display the intermediate vertices on the shortest-path from the given pair of vertices
(u,v).
Note# The graph G can be read from an input file “inDiAdjMat2.dat” that contains cost
adjacency matrix. The expected output could be a shorted-path weight matrix and the path
consisting of intermediate vertices.
Content of the input file “inDiAdjMat2.dat” could be
0 3 8 0 -4
0 0 0 1 7
0 4 0 0 0
2 0 -5 0 0
0 0 0 6 0

Input:
Number of Vertices: 5
Enter the source and destination vertex: 2 5
Output:
0 1 -3 2 -4
3 0 -4 1 -1
7 4 0 5 3
2 -1 -5 0 -2
8 5 1 6 0
Shortest Path from vertex 2 to vertex 5: 2-->4-->1-->5
Path weight: -1*/
#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

int graph[MAX_VERTICES][MAX_VERTICES];
int next[MAX_VERTICES][MAX_VERTICES];

void initialize(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                graph[i][j] = 0;
                next[i][j] = -1;
            } else if (graph[i][j] == 0) {
                graph[i][j] = INF;
                next[i][j] = -1;
            }
        }
    }
}

void floydWarshall(int n) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (graph[i][k] != INF && graph[k][j] != INF && graph[i][j] > graph[i][k] + graph[k][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    next[i][j] = k;
                }
            }
        }
    }
}

void printPath(int u, int v) {
    if (next[u][v] == -1) {
        return;
    }
    printPath(u, next[u][v]);
    printf("%d-->", next[u][v]);
    printPath(next[u][v], v);
}

int main() {
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    // Input the adjacency matrix from the file
    FILE *file = fopen("inDiAdjMat2.dat", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }
    fclose(file);

    initialize(n);
    floydWarshall(n);

    int src, dest;
    printf("Enter the source and destination vertices: ");
    scanf("%d %d", &src, &dest);

    printf("Shortest Path from vertex %d to vertex %d: %d-->", src, dest, src);
    printPath(src, dest);
    printf("%d\n", dest);

    printf("Path weight: %d\n", graph[src][dest]);

    return 0;
}
