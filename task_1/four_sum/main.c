#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../interfaces/dynamic_array/array.h"

typedef struct Pair
{
    int i, j;
    int sum;
} Pair;

Pair pair(int i, int j, int sum)
{
    Pair result;
    result.i = i;
    result.j = j;
    result.sum = sum;
    return result;
}

int check_indepedence(Pair p1, Pair p2)
{
    return (p1.i != p2.i)
        && (p1.i != p2.j)
        && (p1.j != p2.i)
        && (p1.j != p2.j);
}

int compare(const void *ptr1, const void *ptr2) 
{
    Pair first = *((Pair*) ptr1);
    Pair second = *((Pair*) ptr2);
    
    if (first.sum > second.sum) return  1;
    if (first.sum < second.sum) return -1;
    return 0;
}

int array_push_pair(int **result_array, int *input_array, Pair *pair_array, int i, int j)
{
    if (pair_array[i].i < pair_array[j].i) return -1;

    array_push(*result_array, input_array[pair_array[i].i]);
    array_push(*result_array, input_array[pair_array[i].j]);
    array_push(*result_array, input_array[pair_array[j].i]);
    array_push(*result_array, input_array[pair_array[j].j]);

    return 0;
}

int *four_sum(int *array, int sum)
{
    if (array == NULL) return NULL;
    int size = array_length(array);
    int pairs_size = size * (size - 1) / 2;

    Pair* temp_array = NULL;
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size; ++j)
            array_push(temp_array, pair(i, j, array[i] + array[j]));
    
    qsort(temp_array, pairs_size, sizeof(Pair), compare);

    int *result = NULL;
    int i = 0, j = pairs_size - 1;
    while (i < j)
    {
        int current_sum = temp_array[i].sum + temp_array[j].sum;
        if (current_sum > sum) { --j; continue; }
        if (current_sum < sum) { ++i; continue; }
        if (check_indepedence(temp_array[i], temp_array[j]))
            array_push_pair(&result, array, temp_array, i, j);
        if (check_indepedence(temp_array[i + 1], temp_array[j]))
            array_push_pair(&result, array, temp_array, i + 1, j);
        if (check_indepedence(temp_array[i], temp_array[j - 1]))
            array_push_pair(&result, array, temp_array, i, j - 1);
        ++i;
        --j;
    }

    array_free(temp_array);

    return result;
}

int main()
{
    // tests
    int input[] = {-2, -3, 4, -1, -2};
    int output[] = {-3, -1, -2, 4, -1, -2, -3, 4}; // two quadruplets, one includes the first -2, the other includes the second -2

    int *arr = NULL;
    for (int i = 0; i < 5; ++i) array_push(arr, input[i]);
    int *result = four_sum(arr, -2);

    assert(result != NULL);
    assert(array_length(result) == 8);
    for (int i = 0; i < 8; ++i)
        assert(result[i] == output[i]);

    array_free(arr);
    array_free(result);

    return EXIT_SUCCESS;
}
