/* Write a menu driven program to sort a list of elements in ascending
order using Quick Sort technique. Each choice for the input data has its own disc file. A separate
output file can be used for sorted elements. After sorting display the content of the output file
along with number of comparisons. Based on the partitioning position for each recursive call,
conclude the input scenario is either best-case partitioning or worst-case partitioning.
Note#
• The worst-case behavior for quicksort occurs when the partitioning routine produces one
subproblem with n-1 elements and one with 0 elements. The best-case behaviour
occurred in most even possible split, PARTITION produces two subproblems, each of
size no more than n/2.
• Number of elements in each input file should vary from 300 to 500 entries.
• For ascending order: Read data from a file “inAsce.dat” having content 10 20 30 40.....,
Store the result in “outQuickAsce.dat”.
• For descending order: Read data from a file “inDesc.dat” having content 90 80 70 60....,
Store the result in “outQuickDesc.dat”.
• For random data: Read data from a file “inRand.dat” having content 55 66 33 11 44 ...,
Store the result in “outQuickRand.dat”
Sample Input from file:
MAIN MENU (QUICK SORT)
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
#include <stdlib.h>

long long comparisons = 0;

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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
    int choice, n, data[500];
    
    do {
        printf("MAIN MENU (QUICK SORT)\n");
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
        quickSort(data, 0, n - 1);

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

        long long bestCaseComparisons = n - 1;
        long long worstCaseComparisons = (n * (n - 1)) / 2; 
        if (comparisons == bestCaseComparisons) {
            printf("Scenario: Best-case partitioning\n");
        } else if (comparisons == worstCaseComparisons) {
            printf("Scenario: Worst-case partitioning\n");
        } else {
            printf("Scenario: Average-case partitioning\n");
        }

        switch (choice) {
            case 1:
                outputFile = fopen("outQuickAsce.dat", "w");
                break;
            case 2:
                outputFile = fopen("outQuickDesc.dat", "w");
                break;
            case 3:
                outputFile = fopen("outQuickRand.dat", "w");
                break;
        }

        if (outputFile == NULL) {
            printf("Error opening output file.\n");
            return 1;
        }

        for (int i = 0; i < n; i++) {
            fprintf(outputFile, "%d ", data[i]);
        }
        fclose(outputFile);

    } while (1);

    return 0;
}
