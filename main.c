#include "splay.h"
#include "utils.h"
#include "selection_sort.h"
#include "insertion_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <limits.h>


const int DEFAULT_ARR_LEN = 100000;
const int MAX_PRINT_LEN = 20;

void test_splay() {
    SplayTree *t = SplayTree_create();
    SplayTree_insert(t, 5);
    SplayTree_print(t);
    SplayTree_insert(t, 10);
    SplayTree_print(t);
    SplayTree_insert(t, 2);
    SplayTree_print(t);
    SplayTree_insert(t, 1);
    SplayTree_print(t);

    // SplayTree_destroy(t);
    // SplayTree_destroy_nodes(t->root);
    printf("%d\n", SplayTree_search(t, 6) != NULL);
}

void test_selection_sort(int *arr, int len) {
    printf("\n==============\n");
    printf("selection_sort\n");
    printf("==============\n");

    int *arr_cpy = get_arr_copy(arr, len);
    if (len <= MAX_PRINT_LEN) {
        printf("\nsorting: ");
        print_arr(arr_cpy, len);
    }

    clock_t start_time = clock();
    selection_sort(arr_cpy, len);
    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    if (len <= MAX_PRINT_LEN) {
        printf("\nresult: ");
        print_arr(arr_cpy, len);
    }
    printf("completion time: %f seconds\n", time_taken);

    free(arr_cpy);
}

void test_insertion_sort(int *arr, int len) {
    printf("\n==============\n");
    printf("insertion_sort\n");
    printf("==============\n");
    

    int *arr_cpy = get_arr_copy(arr, len);
    if (len <= MAX_PRINT_LEN) {
        printf("\nsorting: ");
        print_arr(arr_cpy, len);
    }

    clock_t start_time = clock();
    insertion_sort(arr_cpy, len);
    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    if (len <= MAX_PRINT_LEN) {
        printf("\nresult: ");
        print_arr(arr_cpy, len);
    }
    printf("completion time: %f seconds\n", time_taken);

    free(arr_cpy);
}

void test_sort_helper(int *arr, int len) {
    test_selection_sort(arr, len);
    test_insertion_sort(arr, len);

    free(arr);
}

void test_sort_random(int len) {
    printf("\n\ntesting sorting functions with random array of len = %d\n", len);

    test_sort_helper(get_arr(len), len);
}

void test_sort_sorted(int len) {
    printf("\n\ntesting sorting functions with sorted array of len = %d\n", len);

    test_sort_helper(get_sorted_arr(len), len);
}

void test_sort_reverse_sorted(int len) {
    printf("\n\ntesting sorting functions with reverse sorted array of len = %d\n", len);

    test_sort_helper(get_reverse_sorted_arr(len), len);
}

void test_sort_half_sorted(int len) {
    printf("\n\ntesting sorting functions with half sorted array of len = %d\n", len);

    test_sort_helper(get_half_sorted_arr(len), len);
}

void test_sorts(int len) {
    test_sort_random(len);
    test_sort_sorted(len);
    test_sort_reverse_sorted(len);    
    test_sort_half_sorted(len);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    long len = DEFAULT_ARR_LEN;
    if (argc > 1) {
        char *p;
        int num;

        errno = 0;
        long conv = strtol(argv[1], &p, 10);
        if (errno != 0 || *p != '\0' || conv > INT_MAX || conv < INT_MIN) {
            fprintf(stderr, "Invalid number: %s\n", argv[1]);
            return 1;
        } else {
            len = conv;
        }
    }

    test_sorts(len);

    return 0;
}