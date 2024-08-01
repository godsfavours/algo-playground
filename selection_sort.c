#include <stdio.h>
#include "utils.h"
#include <stdlib.h>
#include <string.h>

void selection_sort(int *arr, int len) {
    if (len < 1)
        return;

    for (int i = 0; i < len - 1; i++) {
        int min = i;

        for (int j = i + 1; j < len; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }

        if (arr[min] != arr[i])
            swap(&arr[i], &arr[min], sizeof(arr[i]));
    }
}