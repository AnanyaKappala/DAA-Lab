/* Given an undirected weighted connected graph G(V, E) and starring
vertex ‘s’. Maintain a Min-Priority Queue ‘Q’ from the vertex set V and apply Prim’s algorithm
to
• Find the minimum spanning tree T(V, E’). Display the cost adjacency matrix of ‘T’.
• Display total cost of the minimum spanning tree T.
Note# Nodes will be numbered consecutively from 1 to n (user input), and edges will have
varying weight. The graph G can be read from an input file “inUnAdjMat.dat” that contains cost
adjacency matrix. The expected output could be displayed as the cost adjacency matrix of the
minimum spanning tree and total cost of the tree.

Content of the input file “inUnAdjMat.dat” could be
0 4 0 0 0 0 0 8 0
4 0 8 0 0 0 0 11 0
0 8 0 7 0 4 0 0 2
0 0 7 0 9 14 0 0 0
0 0 0 9 0 10 0 0 0
0 0 4 14 10 0 2 0 0
0 0 0 0 0 2 0 1 6
8 11 0 0 0 0 1 0 7
0 0 2 0 0 0 6 7 0
Input:
Enter the Number of Vertices: 9
Enter the Starting Vertex: 1
Output:
0 4 0 0 0 0 0 8 0
4 0 0 0 0 0 0 0 0
0 0 0 7 0 4 0 0 2
0 0 7 0 9 0 0 0 0
0 0 0 9 0 0 0 0 0
0 0 4 0 0 0 2 0 0
0 0 0 0 0 2 0 1 0
8 0 0 0 0 0 1 0 0
0 0 2 0 0 0 0 0 0
Total Weight of the Spanning Tree: 37*/
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

// Function to find the minimum vertex with the minimum key value
int findMinKeyVertex(int key[], bool inMST[], int V) {
    int minKey = INT_MAX;
    int minVertex;

    for (int v = 0; v < V; v++) {
        if (!inMST[v] && key[v] < minKey) {
            minKey = key[v];
            minVertex = v;
        }
    }

    return minVertex;
}

// Function to display the cost adjacency matrix
void displayMSTCostMatrix(int costMatrix[][MAX_VERTICES], int parent[], int V) {
    printf("Cost Adjacency Matrix of the Minimum Spanning Tree:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (parent[j] == i) {
                printf("%d ", costMatrix[i][j]);
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

int main() {
    int V;
    printf("Enter the Number of Vertices: ");
    scanf("%d", &V);

    int costMatrix[MAX_VERTICES][MAX_VERTICES];
    FILE *file = fopen("inUnAdjMat.dat", "r");
    
    if (file == NULL) {
        printf("Failed to open the input file.\n");
        return 1;
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            fscanf(file, "%d", &costMatrix[i][j]);
        }
    }

    fclose(file);

    int startVertex;
    printf("Enter the Starting Vertex: ");
    scanf("%d", &startVertex);

    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    bool inMST[MAX_VERTICES];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        inMST[i] = false;
    }

    key[startVertex - 1] = 0;
    parent[startVertex - 1] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = findMinKeyVertex(key, inMST, V);
        inMST[u] = true;

        for (int v = 0; v < V; v++) {
            if (costMatrix[u][v] && !inMST[v] && costMatrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = costMatrix[u][v];
            }
        }
    }

    displayMSTCostMatrix(costMatrix, parent, V);

    int totalWeight = 0;
    for (int i = 0; i < V; i++) {
        if (key[i] != INT_MAX) {
            totalWeight += key[i];
        }
    }

    printf("Total Weight of the Spanning Tree: %d\n", totalWeight);

    return 0;
}
