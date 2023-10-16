/* Write a program to implement the matrix chain multiplication problem
using M-table & S-table to find optimal parenthesization of a matrix-chain product. Print the
number of scalar multiplications required for the given input.
Note# Dimensions of the matrices can be inputted as row and column values. Validate the
dimension compatibility.
Input:
Enter number of matrices: 4
Enter row and col size of A1: 30 35
Enter row and col size of A2: 35 15
Enter row and col size of A3: 15 5
Enter row and col size of A4: 5 10
Output:
M Table:
0 15750 7875 9375
0 0 2625 4375
0 0 0 750
0 0 0 0
S Table:
0 1 1 3
0 0 2 3
0 0 0 3
0 0 0 0
Optimal parenthesization: ( ( A1 (A2 A3)) A4)
The optimal ordering of the given matrices requires 9375 scalar multiplications.*/
#include <stdio.h>
#include <limits.h>

#define MAX_MATRICES 10

void matrixChainOrder(int p[], int n, int M[MAX_MATRICES][MAX_MATRICES], int S[MAX_MATRICES][MAX_MATRICES]) {
    int i, j, k, L, q;
    for (i = 1; i <= n; i++) {
        M[i][i] = 0;
    }
    
    for (L = 2; L <= n; L++) {
        for (i = 1; i <= n - L + 1; i++) {
            j = i + L - 1;
            M[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++) {
                q = M[i][k] + M[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < M[i][j]) {
                    M[i][j] = q;
                    S[i][j] = k;
                }
            }
        }
    }
}

void printOptimalParenthesis(int S[MAX_MATRICES][MAX_MATRICES], int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalParenthesis(S, i, S[i][j]);
        printOptimalParenthesis(S, S[i][j] + 1, j);
        printf(")");
    }
}

int main() {
    int n;
    printf("Enter number of matrices: ");
    scanf("%d", &n);
    
    int p[MAX_MATRICES]; // Array to store dimensions of matrices
    printf("Enter row and col size of A1: ");
    scanf("%d %d", &p[0], &p[1]);
    
    for (int i = 2; i <= n; i++) {
        int rows, cols;
        printf("Enter row and col size of A%d: ", i);
        scanf("%d %d", &rows, &cols);
        
        if (p[i - 1] != rows) {
            printf("Invalid matrix dimensions. Incompatible for multiplication.\n");
            return 1;
        }
        
        p[i] = cols;
    }
    
    int M[MAX_MATRICES][MAX_MATRICES];
    int S[MAX_MATRICES][MAX_MATRICES];
    
    matrixChainOrder(p, n, M, S);
    
    printf("M Table:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
    
    printf("S Table:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", S[i][j]);
        }
        printf("\n");
    }
    
    printf("Optimal parenthesization: ");
    printOptimalParenthesis(S, 1, n);
    
    printf("\nThe optimal ordering of the given matrices requires %d scalar multiplications.\n", M[1][n]);
    
    return 0;
}
