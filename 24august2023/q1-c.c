#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

void swap(struct person *a, struct person *b)
{
    struct person temp = *a;
    *a = *b;
    *b = temp;
}

// Min-Heapify based on age
void minHeapify(struct person arr[], int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].age < arr[smallest].age)
        smallest = left;

    if (right < n && arr[right].age < arr[smallest].age)
        smallest = right;

    if (smallest != i)
    {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

// Max-Heapify based on weight
void maxHeapify(struct person arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].weight > arr[largest].weight)
        largest = left;

    if (right < n && arr[right].weight > arr[largest].weight)
        largest = right;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void buildMinHeap(struct person arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);
}

void buildMaxHeap(struct person arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

int main()
{
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct person *students = (struct person *)malloc(n * sizeof(struct person));

    FILE *file = fopen("data.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    printf("Id Name Age Height Weight(pound)\n");
    for (int i = 0; i < n; i++)
    {
        students[i].name = (char *)malloc(50 * sizeof(char)); // Assuming max name length of 50
        fscanf(file, "%d %s %d %d %d", &students[i].id, students[i].name, &students[i].age, &students[i].height, &students[i].weight);
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d %s %d %d %d\n", students[i].id, students[i].name, students[i].age, students[i].height, students[i].weight);
    }

    fclose(file);

    int option;
    do
    {
        printf("\nMAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch (option)
        {
            case 1:
                // Data is already read, move to other options
                break;

            case 2:
                buildMinHeap(students, n);
                printf("Min-heap based on age created.\n");
                break;

            case 3:
                buildMaxHeap(students, n);
                printf("Max-heap based on weight created.\n");
                break;

            case 4:
                if (n > 0)
                {
                    printf("Weight of youngest student: %.2f kg\n", students[0].weight * 0.453592);
                }
                else
                {
                    printf("No students available.\n");
                }
                break;

            case 5:
                n++;
                students = (struct person *)realloc(students, n * sizeof(struct person));
                students[n - 1].name = (char *)malloc(50 * sizeof(char)); // Assuming max name length of 50
                printf("Enter new student details: ");
                scanf("%d %s %d %d %d", &students[n - 1].id, students[n - 1].name, &students[n - 1].age, &students[n - 1].height, &students[n - 1].weight);
                buildMinHeap(students, n);
                printf("New student inserted into Min-heap.\n");
                break;

            case 6:
                if (n > 0)
                {
                    students[0] = students[n - 1];
                    n--;
                    students = (struct person *)realloc(students, n * sizeof(struct person));
                    buildMinHeap(students, n);
                    printf("Oldest student deleted.\n");
                }
                else
                {
                    printf("No students available.\n");
                }
                break;

            case 7:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid option.\n");
        }
    } while (option != 7);

    // Free dynamically allocated memory
    for (int i = 0; i < n; i++)
    {
        free(students[i].name);
    }
    free(students);

    return 0;
}
