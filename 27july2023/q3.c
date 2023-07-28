/* Write a program to read ‘n’ integers from a disc file that must contain some duplicate values and store them into
an array. Perform the following operations on the array.
a) Find out the total number of duplicate elements.
b) Find out the most repeating element in the array.
Input: Enter how many numbers you want to read from file: 15
Output: The content of the array: 10 40 35 47 68 22 40 10 98 10 50 35 68 40 10
Total number of duplicate values = 4
The most repeating element in the array = 10 */
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n;
    int arr[100];
    int duplicate_elements = 0;
    int most_repeating_elements = 0;
    int count = 0;
    printf("Enter how many numbers you want to from file:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                duplicate_elements++;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        count = 0;
        for (int j = 0; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                count++;
            }
        }
        if (count > most_repeating_elements)
        {
            most_repeating_elements = count;
        }
    }
    printf("The content of the array:");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Total no of duplicate values: %d\n", duplicate_elements);
    printf("Most repeating elements in the array: %d\n", most_repeating_elements);
    return 0;
}