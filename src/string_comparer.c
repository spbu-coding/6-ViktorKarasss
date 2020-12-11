//
// Created by mi on 18.11.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "sortings.h"
#include "argvalidate.h"
#include "file_handler.h"

#define ARG_STR_COUNT 1
#define ARG_INPUT_FILE 2
#define ARG_OUTPUT_FILE 3
#define ARG_SORT_NAME 4
#define ARG_COMPARER_NAME 5

int main(int argc, char **argv) {
    int code = validate(argc, argv);
    if (code == -1)
        return code;

    char *sort_name = argv[ARG_SORT_NAME];
    char *comparer_name = argv[ARG_COMPARER_NAME];
    char *input_name = argv[ARG_INPUT_FILE];
    char *output_name = argv[ARG_OUTPUT_FILE];
    int str_count = strtol(argv[ARG_STR_COUNT], NULL, 10);

    FILE *input = fopen(input_name, "r");
    FILE *output = fopen(output_name, "w");

    char **array = malloc(sizeof(char *) * str_count);
    for (int i = 0; i < str_count; i++)
        array[i] = malloc(sizeof(char) * MAX_INPUT_STRING_SIZE);

    read(input, array, str_count);
    comparator_func_t comp = (strcmp(comparer_name, "des") == 0) ? comp_des : comp_asc;
    sort(array, str_count, comp, sort_name);
    write(output, array, str_count);

    for (int i = 0; i < str_count; i++) free(array[i]);
    free(array);

    fclose(input);
    fclose(output);

    return 0;
}
