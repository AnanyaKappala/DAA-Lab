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
#include<string.h>
int insertionSort(int arr[], int size) {
    int comparisons = 0;

    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            comparisons++;
        }

        arr[j + 1] = key;
    }

    return comparisons;
}

void displayArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int option;
    do {
        printf("MAIN MENU (INSERTION SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. Exit\n");
        printf("Enter option: ");
        scanf("%d", &option);

        if (option >= 1 && option <= 3) {
            FILE *inputFile;
            FILE *outputFile;
            char inputFileName[20], outputFileName[20];
            int arr[500]; 

            switch (option) {
                case 1:
                    strcpy(inputFileName, "inAsce.dat");
                    strcpy(outputFileName, "outInsAsce.dat");
                    break;
                case 2:
                    strcpy(inputFileName, "inDesc.dat");
                    strcpy(outputFileName, "outInsDesc.dat");
                    break;
                case 3:
                    strcpy(inputFileName, "inRand.dat");
                    strcpy(outputFileName, "outInsRand.dat");
                    break;
            }

            inputFile = fopen(inputFileName, "r");
            if (inputFile == NULL) {
                printf("Error opening input file.\n");
                continue;
            }

            int size;
            fscanf(inputFile, "%d", &size);

            for (int i = 0; i < size; i++) {
                fscanf(inputFile, "%d", &arr[i]);
            }
            fclose(inputFile);

            int comparisons = insertionSort(arr, size);

            outputFile = fopen(outputFileName, "w");
            if (outputFile == NULL) {
                printf("Error opening output file.\n");
                continue;
            }

            for (int i = 0; i < size; i++) {
                fprintf(outputFile, "%d ", arr[i]);
            }
            fclose(outputFile);

            printf("Before Sorting: ");
            displayArray(arr, size);

            printf("After Sorting: ");
            displayArray(arr, size);

            printf("Number of Comparisons: %d\n", comparisons);
            if (comparisons == (size - 1) * size / 2) {
                printf("Scenario: Best-case\n");
            } else if (comparisons == (size - 1) * size) {
                printf("Scenario: Worst-case\n");
            } else {
                printf("Scenario: Average-case\n");
            }
        } else if (option != 4) {
            printf("Invalid option.\n");
        }
    } while (option != 4);

    return 0;
}
