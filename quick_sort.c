#include "quick_sort.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static void partition(int *arr, int len) {
    int i = rand() % len;

    printf("i = %d\n", i);

}

void quick_sort(int *arr, int len) {
    if (len <= 1)
        return;
}