/* Write a program to find the maximum profit nearest to but not
exceeding the given knapsack capacity using the Fractional Knapsack algorithm.
Notes# Declare a structure ITEM having data members item_id, item_profit, item_weight and
profit_weight_ratio. Apply heap sort technique to sort the items in non-increasing order,
according to their profit /weight.
Input:

Enter the number of items: 3
Enter the profit and weight of item no 1: 27 16
Enter the profit and weight of item no 2: 14 12
Enter the profit and weight of item no 3: 26 13
Enter the capacity of knapsack:18

Output:

Item No Profit Weight Amount to be taken
3 26.000000 13.000000 1.000000
1 27.000000 16.000000 0.312500
2 14.000000 12.000000 0.000000
Maximum profit: 34.437500*/
#include <stdio.h>
#include <stdlib.h>

struct ITEM {
    int item_id;
    int item_profit;
    int item_weight;
    float profit_weight_ratio;
};

void swap(struct ITEM* a, struct ITEM* b) {
    struct ITEM temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(struct ITEM arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = left;

    if (right < n && arr[right].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(struct ITEM arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

float fractionalKnapsack(int capacity, struct ITEM items[], int numItems) {
    heapSort(items, numItems);

    float totalProfit = 0.0;
    int currentWeight = 0;

    for (int i = 0; i < numItems; i++) {
        if (currentWeight + items[i].item_weight <= capacity) {
            totalProfit += items[i].item_profit;
            currentWeight += items[i].item_weight;
            printf("Amount to be taken %.6f\n", 1.0);
        } else {
            float fraction = (float)(capacity - currentWeight) / items[i].item_weight;
            totalProfit += fraction * items[i].item_profit;
            printf("%.6f\n", fraction);
        }
        printf("Item No %d\nProfit %.6f\nWeight %.6f\n", items[i].item_id, (float)items[i].item_profit, (float)items[i].item_weight);
    }

    return totalProfit;
}

int main() {
    int numItems, capacity;
    printf("Enter the number of items: ");
    scanf("%d", &numItems);

    struct ITEM items[numItems];

    for (int i = 0; i < numItems; i++) {
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%d %d", &items[i].item_profit, &items[i].item_weight);
        items[i].item_id = i + 1;
        items[i].profit_weight_ratio = (float)items[i].item_profit / items[i].item_weight;
    }

    printf("Enter the capacity of knapsack: ");
    scanf("%d", &capacity);

    float maxProfit = fractionalKnapsack(capacity, items, numItems);

    printf("Maximum profit: %.6f\n", maxProfit);

    return 0;
}
