/* Write a menu driven program to sort list of array elements using Merge Sort technique and calculate the execution
time only to sort the elements. Count the number of comparisons.
Note#
• To calculate execution time, assume that single program is under execution in the CPU.
• Number of elements in each input file should vary from 300 to 500 entries.
• For ascending order: Read data from a file “inAsce.dat” having content 10 20 30 40.....,
Store the result in “outMergeAsce.dat”.
• For descending order: Read data from a file “inDesc.dat” having content 90 80 70 60....,
Store the result in “outMergeDesc.dat”.
• For random data: Read data from a file “inRand.dat” having content 55 66 33 11 44 ...,
Store the result in “outMergeRand.dat”
Sample Input from file:
MAIN MENU (MERGE SORT)
1. Ascending Data
2. Descending Data
3. Random Data
4. ERROR (EXIT)
Output:
Enter option: 1
Before Sorting: Content of the input file
After Sorting: Content of the output file
Number of Comparisons: Actual
Execution Time: lapse time in nanosecond*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparisons = 0;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[100], R[100];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
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
    struct timespec start_time, end_time;

    do {
        printf("MAIN MENU (MERGE SORT)\n");
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
        clock_gettime(CLOCK_MONOTONIC, &start_time);
        mergeSort(data, 0, n - 1);
        clock_gettime(CLOCK_MONOTONIC, &end_time);

        long long elapsed_ns = (end_time.tv_sec - start_time.tv_sec) * 1000000000 + (end_time.tv_nsec - start_time.tv_nsec);

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
        printf("Execution Time: %lld nanoseconds\n", elapsed_ns);

        switch (choice) {
            case 1:
                outputFile = fopen("outMergeAsce.dat", "w");
                break;
            case 2:
                outputFile = fopen("outMergeDesc.dat", "w");
                break;
            case 3:
                outputFile = fopen("outMergeRand.dat", "w");
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
