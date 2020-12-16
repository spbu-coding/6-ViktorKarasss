//
// Created by viktor on 22.11.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "file_handler.h"

#define MAX_INPUT_STRING_SIZE 1000

void read(FILE *file, char **array, int size) {
    for(int i = 0; i < size; i++){
        fgets(array[i], MAX_INPUT_STRING_SIZE, file);
    }
}

void write(FILE *file, char **array, int size) {
    for(int i = 0; i < size; i++){
        fputs(array[i], file);
    }
    if(size == 0){
        fputs("\n", file);
    }
}