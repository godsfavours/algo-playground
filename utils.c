#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void swap(void *a, void *b, size_t size) {
    void *temp = malloc(size);
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}

int *get_arr_copy(int *arr, int len) {
    int *copy = malloc(sizeof(int) * len);
    memcpy(copy, arr, sizeof(int) * len);
    return copy;
}

int *get_arr(int len) {
    int upper = len * 10;
    int lower = 0;

    int *arr = malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++) {
        // arr[i] = rand();
        arr[i] = (rand() % (upper - lower + 1)) + lower;
    }
    return arr;
}

int *get_sorted_arr(int len) {
    int *arr = malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++) {
        arr[i] = i;
    }
    return arr;
}

int *get_half_sorted_arr(int len) {
    int *arr = malloc(sizeof(int) * len);
    int i = 0;
    for (; i < len / 2; i++) {
        arr[i] = i;
    }

    int upper = len * 10;
    int lower = 0;

    for (; i < len; i++) {
        arr[i] = (rand() % (upper - lower + 1)) + lower;
    }

    return arr;
}

int *get_reverse_sorted_arr(int len) {
    int *arr = malloc(sizeof(int) * len);
    int v = len;
    for (int i = 0; i < len; i++) {
        arr[i] = v--;
    }
    return arr;
}

void print_arr(int *arr, int len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        printf(i != len - 1 ? "%d," : "%d", arr[i]);
    }
    printf("]\n");
}