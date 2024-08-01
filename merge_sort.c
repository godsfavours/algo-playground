#include "merge_sort.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static void merge(int *arr, int len) {
    int *temp = malloc(sizeof(int) * len);
    int temp_i = 0;
    int i = 0;
    int j = len/2;

    while (!(j == len && i == (len/2))) {
        if (i == (len/2)) {
            temp[temp_i++] = arr[j++];
        } else if (j == len) {
            temp[temp_i++] = arr[i++];
        } else if (arr[i] < arr[j]) {
            temp[temp_i++] = arr[i++];
        } else if (arr[j] < arr[i]) {
            temp[temp_i++] = arr[j++];
        } else {
            assert(arr[i] == arr[j]);
            temp[temp_i++] = arr[j++];
            temp[temp_i++] = arr[i++];
        }
    }

    memcpy(arr, temp, sizeof(int) * len);
    free(temp);
}

void merge_sort(int *arr, int len) {
    if (len <= 1)
        return;

    merge_sort(&arr[0], len/2);
    merge_sort(&arr[len/2], len - (len/2));
    merge(arr, len);
}