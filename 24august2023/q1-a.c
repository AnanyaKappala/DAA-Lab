#include <stdio.h>
#include <stdlib.h>

struct person {
  int id;
  char *name;
  int age;
  int height;
  int weight;
};

void read_data(struct person *array, int n) {
  // Open the file.
  FILE *fp = fopen("data.txt", "r");
  if (fp == NULL) {
    printf("Error opening file.\n");
    exit(1);
  }

  // Read the data from the file.
  for (int i = 0; i < n; i++) {
    fscanf(fp, "%d %s %d %d %d", &array[i].id, array[i].name, &array[i].age, &array[i].height, &array[i].weight);
  }

  // Close the file.
  fclose(fp);
}

void create_min_heap(struct person *array, int n) {
  // Initialize the heap.
  for (int i = n / 2 - 1; i >= 0; i--) {
    min_heapify(array, i, n);
  }
}

void create_max_heap(struct person *array, int n) {
  // Initialize the heap.
  for (int i = n / 2 - 1; i >= 0; i--) {
    max_heapify(array, i, n);
  }
}

void display_weight_of_youngest_person(struct person *array, int n) {
  // Find the minimum weight.
  int min_weight = array[0].weight;
  int min_index = 0;
  for (int i = 1; i < n; i++) {
    if (array[i].weight < min_weight) {
      min_weight = array[i].weight;
      min_index = i;
    }
  }

  // Print the weight of the youngest person.
  printf("Weight of youngest student: %.2f kg\n", min_weight * 0.45359237);
}

void insert_into_min_heap(struct person *array, int *n, struct person person) {
  // Increase the size of the heap.
  (*n)++;

  // Insert the person into the heap.
  array[*n - 1] = person;
  min_heapify(array, *n - 1, *n);
}

void delete_from_min_heap(struct person *array, int *n) {
  // Remove the minimum element from the heap.
  array[0] = array[*n - 1];
  (*n)--;

  // Heapify the heap.
  min_heapify(array, 0, *n);
}

void min_heapify(struct person *array, int i, int n) {
  // Find the minimum child of the node.
  int min_index = i;
  int left_child = 2 * i + 1;
  int right_child = 2 * i + 2;

  if (left_child < n && array[left_child].age < array[min_index].age) {
    min_index = left_child;
  }

  if (right_child < n && array[right_child].age < array[min_index].age) {
    min_index = right_child;
  }

  // If the minimum child is smaller than the node, swap them.
  if (min_index != i) {
    struct person temp = array[i];
    array[i] = array[min_index];
    array[min_index] = temp;

    min_heapify(array, min_index, n);
  }
}

int main() {
  // Initialize variables.
  int n;
  struct person *array;

  // Read the number of students.
  printf("Enter the number of students: ");
  scanf("%d", &n);

  // Allocate memory for the array.
array = (struct person *)malloc(n * sizeof(struct person));
if (array == NULL) {
  printf("Error allocating memory.\n");
  exit(1);
}
   // Read the data from the file.
  read_data(array, n);

  // Create the min-heap.
  create_min_heap(array, n);

  // Print the weight of the youngest person.
  display_weight_of_youngest_person(array, n);

  // Menu driven program.
  int option;
  do {
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

    switch (option) {
      case 1:
        read_data(array, n);
        break;
      case 2:
        create_min_heap(array, n);
        break;
      case 3:
        create_max_heap(array, n);
        break;
      case 4:
        display_weight_of_youngest_person(array, n);
        break;
      case 5: {
        struct person person;
        printf("Enter the id, name, age, height and weight of the person: ");
        scanf("%d %s %d %d %d", &person.id, person.name, &person.age, &person.height, &person.weight);
        insert_into_min_heap(array, &n, person);
        break;
      }
      case 6:
        delete_from_min_heap(array, &n);
        break;
      case 7:
        printf("Exiting...\n");
        break;
      default:
        printf("Invalid option.\n");
        break;
    }
  } while (option != 7);

  // Free the memory.
  free(array);

  return 0;
}