#include <stdio.h>
#include "utils.h"
#include <stdlib.h>
#include <string.h>

void insertion_sort(int *arr, int len) {
    for (int i = 0; i < len; i++) {
        int min = i;

        for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
            swap(&arr[j], &arr[j - 1], sizeof(arr[j]));
    }
}