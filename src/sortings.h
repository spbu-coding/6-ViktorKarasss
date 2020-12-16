//
// Created by mi on 18.11.2020.
//

#ifndef HOMEWORK6_SORTINGS_H
#define HOMEWORK6_SORTINGS_H

#include <string.h>

#define  MAX_INPUT_STRING_SIZE 1000

typedef int (*comparator_func_t)(const char*, const char*);
typedef char** strings_array_t;
typedef char* sort_name;
typedef size_t array_size_t;


void sort(strings_array_t, array_size_t, comparator_func_t, sort_name);

void bubble(strings_array_t, array_size_t, comparator_func_t);

void insertion(strings_array_t, array_size_t, comparator_func_t);

void merge(strings_array_t, array_size_t, comparator_func_t);

void quick(strings_array_t, array_size_t, comparator_func_t);

void radix(strings_array_t, array_size_t, comparator_func_t);

int comp_asc(const char* a, const char* b);

int comp_des(const char* a, const char* b);

#endif //HOMEWORK6_SORTINGS_H