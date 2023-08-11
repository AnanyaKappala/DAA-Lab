/* Write a menu driven program to sort a list of elements in ascending order using Insertion Sort technique. The 
nature of the input data is choice based and a distinct file is considered for each choice. The sorted elements can 
be stored in a separate output file. After sorting display the content of the output file along with number of 
comparisons. Based on the number of comparisons, conclude the input scenario is either best or worst case.
Note#
• Number of elements in each input file should vary from 300 to 500 entries.
• For ascending order: Read data from a file “inAsce.dat” having content 10 20 30 40 .....,
Store the result in “outInsAsce.dat”.
• For descending order: Read data from a file “inDesc.dat” having content 90 80 70 60....,
Store the result in “outInsDesc.dat”.
• For random data: Read data from a file “inRand.dat” having content 55 66 33 11 44 ...,
Store the result in “outInsRand.dat”
Sample Input from file:
MAIN MENU (INSERTION SORT)
1. Ascending Data
2. Descending Data
3. Random Data
4. ERROR (EXIT)
Output:
Enter option: 1
Before Sorting: Content of the input file
After Sorting: Content of the output file

Number of Comparisons: Actual
Scenario: Best or Worst-case*/
#include <stdio.h>

void insertionSort(int arr[], int n, long long *comparisons) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            (*comparisons)++;
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    FILE *inputFile, *outputFile;
    int choice, n, data[500], i;
    long long comparisons = 0;

    do {
        printf("MAIN MENU (INSERTION SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. Exit\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputFile = fopen("inAsce.dat", "r");
                break;
            case 2:
                inputFile = fopen("inDesc.dat", "r");
                break;
            case 3:
                inputFile = fopen("inRand.dat", "r");
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                continue;
        }

        if (inputFile == NULL) {
            printf("Error opening input file.\n");
            return 1;
        }

        n = 0;
        while (fscanf(inputFile, "%d", &data[n]) != EOF) {
            n++;
        }
        fclose(inputFile);

        comparisons = 0;
        insertionSort(data, n, &comparisons);

        switch (choice) {
            case 1:
                printf("Ascending Data:\n");
                break;
            case 2:
                printf("Descending Data:\n");
                break;
            case 3:
                printf("Random Data:\n");
                break;
        }
        printArray(data, n);
        printf("\nNumber of Comparisons: %lld\n", comparisons);

        long long bestCaseComparisons = (n - 1) * n / 2; 
        long long worstCaseComparisons = bestCaseComparisons + (n - 1); 
        if (comparisons == bestCaseComparisons) {
            printf("Scenario: Best-case\n");
        } else if (comparisons == worstCaseComparisons) {
            printf("Scenario: Worst-case\n");
        } else {
            printf("Scenario: Average-case\n");
        }

        switch (choice) {
            case 1:
                outputFile = fopen("outInsAsce.dat", "w");
                break;
            case 2:
                outputFile = fopen("outInsDesc.dat", "w");
                break;
            case 3:
                outputFile = fopen("outInsRand.dat", "w");
                break;
        }

        if (outputFile == NULL) {
            printf("Error opening output file.\n");
            return 1;
        }

        for (i = 0; i < n; i++) {
            fprintf(outputFile, "%d ", data[i]);
        }
        fclose(outputFile);

    } while (1);

    return 0;
}
