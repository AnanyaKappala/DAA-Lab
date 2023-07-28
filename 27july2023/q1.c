/* Write a program to find out the second smallest and second largest element stored in an array of n integers.
Input: Size of the array is ‘n’ and read ‘n’ number of elements from a disc file.
Output: Second smallest, Second largest */
#include <stdio.h>
int main()
{
    int n, i, smallest, second_smallest, largest, second_largest;
    int arr[100];
    printf("Enter the size of array:");
    scanf("%d", &n);
    printf("Enter the elements of the array:");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    smallest = arr[0];
    second_smallest = arr[0];
    largest = arr[0];
    second_largest = arr[0];
    for (i = 0; i < n; i++)
    {
        if (arr[i] < smallest)
        {
            second_smallest = smallest;
            smallest = arr[i];
        }
        else if (arr[i] > smallest && arr[i] < second_smallest)
        {
            second_smallest = arr[i];
        }
        if (arr[i] > largest)
        {
            second_largest = largest;
            largest = arr[i];
        }
        else if (arr[i] < largest && arr[i] > second_largest)
        {
            second_largest = arr[i];
        }
    }
    printf("Second smallest: %d\n", second_smallest);
    printf("Second largest: %d\n", second_largest);
}