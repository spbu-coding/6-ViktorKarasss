//
// Created by mi on 18.11.2020.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "argvalidate.h"

#define SORT_NAMES_SIZE 5
#define COMPARER_NAMES_SIZE 2
#define ARGS_COUNT 6
#define ARG_SORT_NAME 4
#define ARG_COMPARER_NAME 5
#define ARG_STR_COUNT 1
#define ARG_INPUT_FILE 2
#define ARG_OUTPUT_FILE 3
#define MAX_INPUT_STRING_SIZE 1000

#define errprintf(x) fprintf(stderr, "%s", x)

static const char *SORT_NAMES[SORT_NAMES_SIZE] = {"bubble", "insertion", "radix", "quick", "merge"};
static const char *COMPARER_NAMES[COMPARER_NAMES_SIZE] = {"asc", "des"};

int is_in(char *name, const char **name_list, int list_size) {
    int flag = 0;
    for (int i = 0; i < list_size; i++) {
        if (strcmp(name, name_list[i]) == 0)
            flag = 1;
    }
    return flag;
}


int is_int(const char *str) {
    for (long unsigned int i = 0; i < strlen(str); i++) {
        if (str[i] > '9' || str[i] < '0')
            return 0;
    }
    return 1;
}

int count_str(FILE *file) {
    char *estr;
    char str[MAX_INPUT_STRING_SIZE + 1];
    int i = 0;
    while (1) {
        estr = fgets(str, sizeof(str), file);
        if (estr == NULL) {
            if (feof(file) != 0) {
                break;
            } else {
                printf("Read file error\n");
                exit(-1);
            }
        }
        i++;
    }
    return i;
}

int validate(int argc, char **argv) {
    if (argc != ARGS_COUNT) {
        errprintf("Incorrect count of argument");
        return -1;
    }
    if (!is_in(argv[ARG_SORT_NAME], SORT_NAMES, SORT_NAMES_SIZE)) {
        errprintf("Incorrect name of sort");
        return -1;
    }
    if (!is_in(argv[ARG_COMPARER_NAME], COMPARER_NAMES, COMPARER_NAMES_SIZE)){
        errprintf("Incorrect name of comparer");
        return -1;}
    if (!is_int(argv[ARG_STR_COUNT])){
        errprintf("Incorrect count of string");
        return -1;
    }

    FILE *file;
    file = fopen(argv[ARG_INPUT_FILE], "r");
    if (file == NULL){
        errprintf("Incorrect input file name or input file can not be open");
        return -1;}
    else {
        if (count_str(file) < strtol(argv[ARG_STR_COUNT], NULL, 10)){
            errprintf("Incorrect count of string");
            return -1;
        }
        fclose(file);
    }
    return 0;
}