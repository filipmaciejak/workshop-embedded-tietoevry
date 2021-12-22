#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../interfaces/dynamic_array/array.h"

int compare(const void *ptr1, const void *ptr2) 
{
    int first = *((int*) ptr1);
    int second = *((int*) ptr2);
    
    if (first > second) return  1;
    if (first < second) return -1;
    return 0;
}

int *three_sum(int *array, int sum)
{
    if (array == NULL) return NULL;
    int size = array_length(array);

    int *temp_array = malloc(sizeof(int) * size);
    if (temp_array == NULL) return NULL;
    for (int i = 0; i < size; ++i)
        temp_array[i] = array[i];
    qsort(temp_array, size, sizeof(int), compare);

    int *result = NULL;
    int index = 0;
    while (index < size - 2)
    {
        int i = index + 1, j = size - 1;
        while (i < j)
        {
            int current_sum = temp_array[index] + temp_array[i] + temp_array[j];
            if (current_sum > sum) { --j; continue; }
            if (current_sum < sum) { ++i; continue; }
            array_push(result, temp_array[index]);
            array_push(result, temp_array[i]); ++i;
            array_push(result, temp_array[j]); --j;
        }
        ++index;
    }

    return result;
}

int main()
{
    // tests
    int input[] = {2, 7, 4, 0, 9, 5, 1, 3};
    int output[] = {4, 7, 9};
    int *arr = NULL;
    for (int i = 0; i < 8; ++i) array_push(arr, input[i]);
    int *result = three_sum(arr, 20);

    assert(result != NULL);
    assert(array_length(result) == 3);
    for (int i = 0; i < 3; ++i)
        assert(result[i] == output[i]);

    array_free(arr);
    array_free(result);

    return EXIT_SUCCESS;
}
