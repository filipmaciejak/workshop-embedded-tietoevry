#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../interfaces/dynamic_array/array.h"

int compare(const void *element1, const void *element2) 
{
    int f = *((int*) element1);
    int s = *((int*) element2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int *twoSum(int *array, int sum)
{
    int size = array_length(array);

    int *temp_array = malloc(sizeof(int) * size);
    if (temp_array == NULL) return NULL;
    for (int i = 0; i < size; ++i)
        temp_array[i] = array[i];
    qsort(temp_array, size, sizeof(int), compare);

    int *result = NULL;
    int i = 0, j = size - 1;
    while (i < j)
    {
        int current_sum = temp_array[i] + temp_array[j];
        if (current_sum > sum) { --j; continue; }
        if (current_sum < sum) { ++i; continue; }
        array_push(result, temp_array[i]); ++i;
        array_push(result, temp_array[j]); --j;
    }

    return result;
}

int main()
{
    // tests
    int input[] = {3, 5, 2, -4, 8, 11};
    int output[] = {-4, 11, 2, 5};
    int *arr = NULL;
    for (int i = 0; i < 6; ++i) array_push(arr, input[i]);
    int *result = twoSum(arr, 7);

    assert(array_length(result) == 4);
    for (int i = 0; i < 4; ++i)
        assert(result[i] == output[i]);

    array_free(arr);
    array_free(result);

    return EXIT_SUCCESS;
}
