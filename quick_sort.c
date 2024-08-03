#include "quick_sort.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static int partition(int *arr, int len) {
    swap(&arr[rand() % len], &arr[0], sizeof(int));
    int v = arr[0];
    int i = 0;
    int j = len;
    
    while (1) {
        while (arr[++i] < v) {
            if (i + 1 >= len)
                break;
        }

        while (arr[--j] > v) 
            continue;

        if (i >= j) {
            swap(&arr[0], &arr[j], sizeof(int));
            return j;
        }
        swap(&arr[i], &arr[j], sizeof(int));
    }

    swap(&arr[i], &arr[0], sizeof(int));
}

void quick_sort(int *arr, int len) {
    if (len <= 1)
        return;

   int p = partition(arr, len);
   quick_sort(&arr[0], p);
   quick_sort(&arr[p + 1], len - p - 1);
}