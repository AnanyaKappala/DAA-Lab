/* Write a program to find out the Longest Common Subsequence of two
given strings. Calculate length of the LCS.
Input:

Enter the first string into an array: 10010101
Enter the second string into an array: 010110110

Output:
LCS: 100110
LCS Length: 6*/
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

void findLCS(char X[], char Y[], int m, int n, int LCS[MAX_LENGTH][MAX_LENGTH]) {
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                LCS[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                LCS[i][j] = LCS[i - 1][j - 1] + 1;
            else
                LCS[i][j] = max(LCS[i - 1][j], LCS[i][j - 1]);
        }
    }
}

void printLCS(char X[], char Y[], int m, int n, int LCS[MAX_LENGTH][MAX_LENGTH]) {
    int index = LCS[m][n];
    char lcs[MAX_LENGTH];
    lcs[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (LCS[i - 1][j] > LCS[i][j - 1])
            i--;
        else
            j--;
    }

    printf("LCS: %s\n", lcs);
    printf("LCS Length: %d\n", strlen(lcs));
}

int main() {
    char X[MAX_LENGTH], Y[MAX_LENGTH];

    printf("Enter the first string into an array: ");
    scanf("%s", X);
    printf("Enter the second string into an array: ");
    scanf("%s", Y);

    int m = strlen(X);
    int n = strlen(Y);
    int LCS[MAX_LENGTH][MAX_LENGTH];

    findLCS(X, Y, m, n, LCS);
    printLCS(X, Y, m, n, LCS);

    return 0;
}
