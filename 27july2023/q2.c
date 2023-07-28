/* : Given an array arr[] of size N, find the prefix sum of the array. A prefix sum array is another array
prefixSum[] of the same size, such that the value of prefixSum[i] is arr[0] + arr[1] + arr[2] . . . arr[i].
Input Array: 3 4 5 1 2
Output Array: 3 7 12 13 15 */
#include <stdio.h>
int main()
{
    int arr[100];
    int n;
    printf("Enter the number of elements:");
    scanf("%d", &n);
    printf("Enter the elements:");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int prefix_sum[100];
    prefix_sum[0] = arr[0];
    for (int i = 1; i < n; i++)
    {
        prefix_sum[i] = prefix_sum[i - 1] + arr[i];
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", prefix_sum[i]);
    }
    printf("\n");
    return 0;
}