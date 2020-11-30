//
// Created by mi on 18.11.2020.
//
#include <stdlib.h>
#include "sortings.h"

void sort(strings_array_t array, array_size_t size, comparator_func_t comparator, sort_name name){
    if(strcmp(name,"bubble") == 0)
        bubble(array,size,comparator);
    else if(strcmp(name,"insertion") == 0)
        insertion(array,size,comparator);
    else if(strcmp(name,"merge") == 0)
        merge(array,size,comparator);
    else if(strcmp(name,"quick") == 0)
        quick(array,size,comparator);
    else if(strcmp(name,"radix") == 0)
        radix(array,size,comparator);
}

void bubble(strings_array_t array, array_size_t size, comparator_func_t comparator){
    int no_swap;
    for (int i = size - 1; i >= 0; i--){
        no_swap = 1;
        for (int j = 0; j < i; j++){
            if (comparator(array[j],array[j + 1])){
                char* tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
                no_swap = 0;
            }
        }
        if (no_swap == 1)
            break;
    }
}

void insertion(strings_array_t array, array_size_t size, comparator_func_t comparator){
    int location;
    char* new_element;

    for (int i = 1; i < size; i++){
        new_element = array[i];
        location = i - 1;
        while(location >= 0 && comparator(array[location], new_element)){
            array[location+1] = array[location];
            location = location - 1;
        }
        array[location+1] = new_element;
    }
}

void merge(strings_array_t array, array_size_t size, comparator_func_t comparator){
    int step = 1;
    char** temp = malloc(sizeof(char*) * size);
    for(int i = 0; i < size; i++)
        temp[i] = malloc(sizeof(char) * (MAX_INPUT_STRING_SIZE + 1));
    while (step < size){
        int index = 0;
        int l = 0;
        int m = l + step;
        int r = l + step * 2;
        do{
            m = m < size ? m : size;
            r = r < size ? r : size;
            int i1 = l, i2 = m;
            while(i1 < m && i2 < r){
                if (comparator(array[i2],array[i1])) { temp[index++] = array[i1++]; }
                else { temp[index++] = array[i2++]; }
            }
            while (i1 < m) temp[index++] = array[i1++];
            while (i2 < r) temp[index++] = array[i2++];
            l += step * 2;
            m += step * 2;
            r += step * 2;
        } while (l < size);
        for (int i = 0; i < size; i++)
            array[i] = temp[i];
        step *= 2;
    }
}



void quick(strings_array_t array, array_size_t size, comparator_func_t comparator){
    long i = 0, j = size-1;
    char* temp;
    char* p;

    p = array[size>>1];

    do {
        while ( comparator(p, array[i]) ) i++;
        while ( comparator(array[j], p) ) j--;

        if (i <= j) {
            temp = array[i]; array[i] = array[j]; array[j] = temp;
            i++; j--;
        }
    } while ( i<=j );

    if ( j > 0 ) quick(array, j, comparator);
    if ( size > i ) quick(array+i, size-i, comparator);
}

void radix(strings_array_t array, array_size_t size, comparator_func_t comparator){

}


int comp_asc(const char* array, const char* b){
    const unsigned char *s1 = (const unsigned char *) array;
    const unsigned char *s2 = (const unsigned char *) b;
    unsigned char c1, c2;
    do{
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;
        if (c1 == '\0')
            return (c1 - c2) > 0;
    }
    while (c1 == c2);
    return (c1 - c2) > 0;
}

int comp_des(const char* array, const char* b){
    const unsigned char *s1 = (const unsigned char *) array;
    const unsigned char *s2 = (const unsigned char *) b;
    unsigned char c1, c2;
    do{
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;
        if (c1 == '\0')
            return (c1 - c2) < 0;
    }
    while (c1 == c2);
    return (c1 - c2) < 0;
}