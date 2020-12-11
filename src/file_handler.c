//
// Created by viktor on 22.11.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "file_handler.h"

#define MAX_INPUT_STRING_SIZE 1000

void read(FILE *file, char **array, int size) {
    char *str;
    int i = 0;
    while (1) {
        if (i >= size)
            break;
        str = fgets(array[i], sizeof(array[i]), file);
        if (str == NULL) {
            if (feof(file) != 0) {
                break;
            } else {
                printf("Read file error\n");
                exit(-1);
            }
        }
        i++;
    }
}

void write(FILE *file, char **array, int size) {
    for (int i = 0; i < size; i++) {
        fprintf(file, "%s", array[i]);
    }
}