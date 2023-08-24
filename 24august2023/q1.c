/* Define a struct person as follows:
struct person
{
int id;
char *name;
int age;
int height;
int weight;
};
Write a menu driven program to read the data of ‘n’ students from a file and store them in a dynamically allocated
array of struct person. Implement the min-heap or max-heap and its operations based on the menu options.
Sample Input/Output:
MAIN MENU (HEAP)
1. Read Data
2. Create a Min-heap based on the age
3. Create a Max-heap based on the weight
4. Display weight of the youngest person
5. Insert a new person into the Min-heap
6. Delete the oldest person
7. Exit
Enter option: 1
Id Name Age Height Weight(pound)
0 Adarsh Hota 39 77 231
1 Levi Maier 56 77 129
2 Priya Kumari 63 78 240
3 Dorothy Helton 47 72 229
4 Florence Smith 24 75 171
5 Erica Anyan 38 73 102
6 Norma Webster 23 75 145
Enter option: 4
Weight of youngest student: 65.77 kg
Note#: Other menu choices are similarly verified.*/
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

typedef struct person Person;

// Function to swap two persons
void swapPersons(Person *a, Person *b)
{
    Person temp = *a;
    *a = *b;
    *b = temp;
}

// Min-heapify function based on age
void minHeapifyByAge(Person *arr, int size, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && arr[left].age < arr[smallest].age)
        smallest = left;

    if (right < size && arr[right].age < arr[smallest].age)
        smallest = right;

    if (smallest != i)
    {
        swapPersons(&arr[i], &arr[smallest]);
        minHeapifyByAge(arr, size, smallest);
    }
}

// Max-heapify function based on weight
void maxHeapifyByWeight(Person *arr, int size, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && arr[left].weight > arr[largest].weight)
        largest = left;

    if (right < size && arr[right].weight > arr[largest].weight)
        largest = right;

    if (largest != i)
    {
        swapPersons(&arr[i], &arr[largest]);
        maxHeapifyByWeight(arr, size, largest);
    }
}

// Build a min-heap based on age
void buildMinHeapByAge(Person *arr, int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
        minHeapifyByAge(arr, size, i);
}

// Build a max-heap based on weight
void buildMaxHeapByWeight(Person *arr, int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
        maxHeapifyByWeight(arr, size, i);
}

// Function to read data from a file and store in an array of persons
Person *readDataFromFile(const char *filename, int *numPersons)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    fscanf(file, "%d", numPersons);

    Person *persons = (Person *)malloc(sizeof(Person) * (*numPersons));
    for (int i = 0; i < *numPersons; i++)
    {
        persons[i].name = (char *)malloc(sizeof(char) * 50);
        fscanf(file, "%d %s %d %d %d", &persons[i].id, persons[i].name, &persons[i].age, &persons[i].height, &persons[i].weight);
    }

    fclose(file);
    return persons;
}

// Function to insert a new person into the min-heap based on age
void insertIntoMinHeapByAge(Person *arr, int *size, Person newPerson)
{
    (*size)++;
    int i = (*size) - 1;
    arr[i] = newPerson;

    while (i > 0 && arr[(i - 1) / 2].age > arr[i].age)
    {
        swapPersons(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to delete the oldest person from the min-heap based on age
void deleteFromMinHeapByAge(Person *arr, int *size)
{
    if (*size <= 0)
    {
        printf("Heap is empty.\n");
        return;
    }

    if (*size == 1)
    {
        (*size)--;
        return;
    }

    arr[0] = arr[*size - 1];
    (*size)--;
    minHeapifyByAge(arr, *size, 0);
}

int main()
{
    int option, numPersons;
    Person *persons = NULL;

    while (1)
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
            if (persons != NULL)
            {
                for (int i = 0; i < numPersons; i++)
                    free(persons[i].name);
                free(persons);
            }
            persons = readDataFromFile("data.txt", &numPersons);
            printf("Data read successfully.\n");
            break;

        case 2:
            if (persons == NULL)
            {
                printf("Please read data first.\n");
                break;
            }
            buildMinHeapByAge(persons, numPersons);
            printf("Min-heap based on age created.\n");
            break;

        case 3:
            if (persons == NULL)
            {
                printf("Please read data first.\n");
                break;
            }
            buildMaxHeapByWeight(persons, numPersons);
            printf("Max-heap based on weight created.\n");
            break;

        case 4:
            if (persons == NULL)
            {
                printf("Please read data first.\n");
                break;
            }
            printf("Weight of youngest student: %.2f kg\n", persons[0].weight * 0.45359237);
            break;

        case 5:
        {
            if (persons == NULL)
            {
                printf("Please read data first.\n");
                break;
            }

            Person newPerson;
            printf("Enter new person details (Id Name Age Height Weight): ");
            scanf("%d", &newPerson.id);

            // Allocate memory for the name field and read the name
            newPerson.name = (char *)malloc(sizeof(char) * 50);
            scanf("%s", newPerson.name);

            scanf("%d %d %d", &newPerson.age, &newPerson.height, &newPerson.weight);
            insertIntoMinHeapByAge(persons, &numPersons, newPerson);
            printf("New person inserted into the Min-heap.\n");
            break;
        }

        case 6:
        {
            if (persons == NULL)
            {
                printf("Please read data first.\n");
                break;
            }

            deleteFromMinHeapByAge(persons, &numPersons);
            printf("Oldest person deleted from the Min-heap.\n");
            break;
        }

        case 7:
            if (persons != NULL)
            {
                for (int i = 0; i < numPersons; i++)
                    free(persons[i].name);
                free(persons);
            }
            printf("Exiting...\n");
            exit(0);

        default:
            printf("Invalid option.\n");
            break;
        }
    }

    return 0;
}