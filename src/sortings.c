//
// Created by mi on 18.11.2020.
//
#include <stdlib.h>
#include <limits.h>
#include "sortings.h"


void sort(strings_array_t array, array_size_t size, comparator_func_t comparator, sort_name name) {
    if (strcmp(name, "bubble") == 0)
        bubble(array, size, comparator);
    else if (strcmp(name, "insertion") == 0)
        insertion(array, size, comparator);
    else if (strcmp(name, "merge") == 0)
        merge(array, size, comparator);
    else if (strcmp(name, "quick") == 0)
        quick(array, size, comparator);
    else if (strcmp(name, "radix") == 0)
        radix(array, size, comparator);
}

void bubble(strings_array_t array, array_size_t size, comparator_func_t comparator) {
    unsigned long no_swap;
    for (unsigned long i = size - 1; i >= 0; i--) {
        no_swap = 1;
        for (unsigned long j = 0; j < i; j++) {
            if (comparator(array[j], array[j + 1])) {
                char *tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
                no_swap = 0;
            }
        }
        if (no_swap == 1)
            break;
    }
}

void insertion(strings_array_t array, array_size_t size, comparator_func_t comparator) {
    unsigned long location;
    char *new_element;

    for (unsigned long i = 1; i < size; i++) {
        new_element = array[i];
        location = i - 1;
        while (location >= 0 && comparator(array[location], new_element)) {
            array[location + 1] = array[location];
            location = location - 1;
        }
        array[location + 1] = new_element;
    }
}

void merge(strings_array_t array, array_size_t size, comparator_func_t comparator) {
    unsigned long step = 1;
    char **temp = malloc(sizeof(char *) * size);

    while (step < size) {
        unsigned long index = 0;
        unsigned long l = 0;
        unsigned long m = l + step;
        unsigned long r = l + step * 2;
        do {
            m = m < size ? m : size;
            r = r < size ? r : size;
            unsigned long i1 = l, i2 = m;
            while (i1 < m && i2 < r) {
                if (comparator(array[i2], array[i1])) { temp[index++] = array[i1++]; }
                else { temp[index++] = array[i2++]; }
            }
            while (i1 < m) temp[index++] = array[i1++];
            while (i2 < r) temp[index++] = array[i2++];
            l += step * 2;
            m += step * 2;
            r += step * 2;
        } while (l < size);
        for (unsigned long i = 0; i < size; i++)
            array[i] = temp[i];
        step *= 2;
    }

    free(temp);
}


void reqursion_quick(strings_array_t array, unsigned long first, unsigned long last, comparator_func_t comparator) {
    if (first < last) {
        unsigned long left = first, right = last;
        char *middle = array[(left + right) / 2];
        do {
            while (comparator(middle, array[left])) left++; // <
            while (comparator(array[right], middle)) right--; // >
            if (left <= right) {
                char *tmp = array[left];
                array[left] = array[right];
                array[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        reqursion_quick(array, first, right, comparator);
        reqursion_quick(array, left, last, comparator);
    }
}

void quick(strings_array_t array, array_size_t size, comparator_func_t comparator) {
    unsigned long right = (unsigned long ) size - 1;
    reqursion_quick(array, 0, right, comparator);
}

static void swap_strings(const char **a, const char **b) {
    const char *temp;

    temp = *a;
    *a = *b;
    *b = temp;
}


static void reqursion_radix(unsigned long size, const char **array, unsigned long symbol) {
    unsigned long i;
    unsigned long count[UCHAR_MAX + 1];
    unsigned long mode;
    const char **bucket[UCHAR_MAX + 1];
    const char **top[UCHAR_MAX + 1];
    while (size > 1) {
        memset(count, 0, sizeof(unsigned long ) * (UCHAR_MAX + 1));
        for (i = 0; i < size; i++) {
            count[(unsigned char) array[i][symbol]]++;
        }
        mode = 1;
        for (i = 2; i < UCHAR_MAX + 1; i++) {
            if (count[i] > count[mode]) {
                mode = i;
            }
        }
        if (count[mode] < size) {
            bucket[0] = top[0] = array;
            for (i = 1; i < UCHAR_MAX + 1; i++) {
                top[i] = bucket[i] = bucket[i - 1] + count[i - 1];
            }
            for (i = 0; i < UCHAR_MAX + 1; i++) {
                while (top[i] < bucket[i] + count[i]) {
                    if ((unsigned char) top[i][0][symbol] == i) {
                        top[i]++;
                    } else {
                        swap_strings(top[i], top[(unsigned char) top[i][0][symbol]]++);
                    }
                }
            }
            for (i = 1; i < UCHAR_MAX + 1; i++) {
                if (i != mode) {
                    reqursion_radix(count[i], bucket[i], symbol + 1);
                }
            }
            size = count[mode];
            array = bucket[mode];
            symbol += 1;

        } else {
            symbol += 1;
        }
    }
}

void radix(strings_array_t array, array_size_t size, comparator_func_t comparator) {
    reqursion_radix(size, (const char **) array, 0);
    if (comparator("a", "b")) {
        for (unsigned long i = 0; i < size / 2; i++) {
            char *temp = array[i];
            array[i] = array[size - i - 1];
            array[size - i - 1] = temp;
        }
    }
}


int comp_asc(const char *a, const char *b) {
    const unsigned char *s1 = (const unsigned char *) a;
    const unsigned char *s2 = (const unsigned char *) b;
    unsigned char c1, c2;
    do {
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;
        if (c2 == '\0')
            return (c2 - c1) < 0;
    } while (c2 == c1);
    return (c2 - c1) < 0;
}

int comp_des(const char *a, const char *b) {
    const unsigned char *s1 = (const unsigned char *) a;
    const unsigned char *s2 = (const unsigned char *) b;
    unsigned char c1, c2;
    do {
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;
        if (c1 == '\0')
            return (c1 - c2) < 0;
    } while (c1 == c2);
    return (c1 - c2) < 0;
}