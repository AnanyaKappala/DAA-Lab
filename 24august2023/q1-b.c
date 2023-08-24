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

struct person *heap;
int size = 0;
int capacity = 0;

void insert(struct person p);
void delete();
void heapify(int i);
void swap(int i, int j);
int parent(int i);
int left(int i);
int right(int i);
void display();
void displayWeight();

int main()
{
    printf("MAIN MENU (HEAP)\n");
    printf("1. Read Data\n");
    printf("2. Create a Min-heap based on the age\n");
    printf("3. Create a Max-heap based on the weight\n");
    printf("4. Display weight of the youngest person\n");
    printf("5. Insert a new person into the Min-heap\n");
    printf("6. Delete the oldest person\n");
    printf("7. Exit\n");

    int ch;
    printf("Enter option: ");
    scanf("%d", &ch);

    while (ch != 7)
    {
        switch (ch)
        {
        case 1:
        {
            FILE *file = fopen("data.txt", "r");
            if (file == NULL)
            {
                printf("Error opening file.\n");
                exit(1);
            }

            fscanf(file, "%d", &capacity);
            heap = (struct person *)malloc(capacity * sizeof(struct person));

            for (int i = 0; i < capacity; i++)
            {
                fscanf(file, "%d %s %d %d %d", &heap[i].id, heap[i].name, &heap[i].age, &heap[i].height, &heap[i].weight);
            }

            size = capacity;
            fclose(file);
            break;
        }
        case 2:
        {
            printf("Min-heap based on age:\n");
            display();
            break;
        }
        case 3:
        {
            printf("Max-heap based on weight:\n");
            for (int i = 0; i < size; i++)
            {
                heap[i].age = -heap[i].age;
            }
            for (int i = 0; i < size; i++)
            {
                heap[i].age = -heap[i].age;
            }
            display();
            break;
        }
        case 4:
        {
            displayWeight();
            break;
        }
        case 5:
        {
            printf("Enter id: ");
            int id;
            scanf("%d", &id);

            printf("Enter name: ");
            char name[100];
            scanf("%s", name);

            printf("Enter age: ");
            int age;
            scanf("%d", &age);

            printf("Enter height: ");
            int height;
            scanf("%d", &height);

            printf("Enter weight: ");
            int weight;
            scanf("%d", &weight);

            struct person p;
            p.id = id;
            p.name = strdup(name);
            p.age = age;
            p.height = height;
            p.weight = weight;

            insert(p);
            break;
        }
        case 6:
        {
            delete ();
            break;
        }
        default:
        {
            printf("Invalid choice\n");
            break;
        }
        }
        printf("Enter option: ");
        scanf("%d", &ch);
    }

    for (int i = 0; i < size; i++)
    {
        free(heap[i].name);
    }
    free(heap);

    return 0;
}

void insert(struct person p)
{
    if (size == capacity)
    {
        printf("Heap is full\n");
        return;
    }
    size++;
    int i = size - 1;
    heap[i] = p;
    while (i != 0 && heap[parent(i)].age > heap[i].age)
    {
        swap(i, parent(i));
        i = parent(i);
    }
}

void delete()
{
    if (size == 0)
    {
        printf("Heap is empty\n");
        return;
    }
    if (size == 1)
    {
        size--;
        return;
    }
    heap[0] = heap[size - 1];
    size--;
    heapify(0);
}

void heapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < size && heap[l].age < heap[i].age)
        smallest = l;
    if (r < size && heap[r].age < heap[smallest].age)
        smallest = r;
    if (smallest != i)
    {
        swap(i, smallest);
        heapify(smallest);
    }
}

void swap(int i, int j)
{
    struct person temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

int parent(int i)
{
    return (i - 1) / 2;
}

int left(int i)
{
    return 2 * i + 1;
}

int right(int i)
{
    return 2 * i + 2;
}

void display()
{
    for (int i = 0; i < size; i++)
        printf("%d %s %d %d %d\n", heap[i].id, heap[i].name, heap[i].age, heap[i].height, heap[i].weight);
}

void displayWeight()
{
    printf("Weight of youngest student: %d kg\n", heap[0].weight);
}