// utils.h

#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

int *get_arr_copy(int *arr, int len);
int *get_arr(int len);
int *get_sorted_arr(int len);
int *get_reverse_sorted_arr(int len);
int *get_half_sorted_arr(int len);
void print_arr(int *arr, int len);
void swap(void *a, void *b, size_t size);

#endif