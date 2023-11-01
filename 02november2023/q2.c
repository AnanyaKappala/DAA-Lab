/* Given an undirected weighted connected graph G(V, E). Apply
Krushkal’s algorithm to
● Find the minimum spanning tree T(V, E’) and Display the selected edges of G.
● Display total cost of the minimum spanning tree T.
Note# Nodes will be numbered consecutively from 1 to n (user input), and edges will have
varying weight. The weight matrix of the graph can be represented from the user’s input in the
given format. The expected output could be the selected edge and the corresponding cost of the
edge as per the sample output.
Input Format:
● The first line contains two space-separated integers ‘n’ and ‘m’, the number of nodes
and edges in the graph.
● Each line ‘i’ of the ‘m’ subsequent lines contains three space-separated integers ‘u’, ‘v’
and ‘w’, that describe an edge (u, v) and weight ‘w’.

Input:
9 14
1 2 4
1 8 8
2 3 8
2 8 11
3 4 7
3 6 4
3 9 2
4 5 9
4 6 14
5 6 10
6 7 2
7 8 1
7 9 6
8 9 7
Output:
Edge Cost
8--7 1
7--6 2
3--9 2
1--2 4
3--6 4
3--4 7
1--8 8
4--5 9
Total Weight of the Spanning Tree: 37*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_EDGES 100

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a disjoint-set
struct DisjointSet {
    int parent[MAX_VERTICES];
};

// Function to initialize a disjoint-set
void makeSet(struct DisjointSet* ds, int V) {
    for (int i = 0; i < V; i++) {
        ds->parent[i] = i;
    }
}

// Function to find the parent of a vertex in a disjoint-set
int find(struct DisjointSet* ds, int vertex) {
    if (ds->parent[vertex] != vertex) {
        ds->parent[vertex] = find(ds, ds->parent[vertex]);
    }
    return ds->parent[vertex];
}

// Function to perform union of two sets
void unionSets(struct DisjointSet* ds, int src, int dest) {
    int srcParent = find(ds, src);
    int destParent = find(ds, dest);
    ds->parent[srcParent] = destParent;
}

// Function to compare two edges based on their weight
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Function to find the minimum spanning tree using Kruskal's algorithm
void kruskalMST(struct Edge edges[], int V, int E) {
    struct Edge resultMST[MAX_EDGES];
    int mstSize = 0;
    int mstWeight = 0;

    struct DisjointSet ds;
    makeSet(&ds, V);

    // Sort the edges in ascending order of weight
    qsort(edges, E, sizeof(struct Edge), compareEdges);

    // Iterate through the sorted edges and add them to the MST if they don't form a cycle
    for (int i = 0; i < E && mstSize < V - 1; i++) {
        int src = edges[i].src;
        int dest = edges[i].dest;
        int srcParent = find(&ds, src);
        int destParent = find(&ds, dest);

        if (srcParent != destParent) {
            resultMST[mstSize++] = edges[i];
            mstWeight += edges[i].weight;
            unionSets(&ds, srcParent, destParent);
        }
    }

    // Display the selected edges and their costs
    printf("Edge Cost\n");
    for (int i = 0; i < mstSize; i++) {
        printf("%d--%d %d\n", resultMST[i].src, resultMST[i].dest, resultMST[i].weight);
    }

    printf("Total Weight of the Spanning Tree: %d\n", mstWeight);
}

int main() {
    int V, E;
    printf("Enter the number of nodes and edges: ");
    scanf("%d %d", &V, &E);

    struct Edge edges[MAX_EDGES];
    printf("Enter the edges and their weights:\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    kruskalMST(edges, V, E);

    return 0;
}
