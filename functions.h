#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void init_buffer(char **buffer, int *buffer_size);

extern void expand_buffer(char **buffer, int *buffer_size);

extern long double convert_to_number(char *word, bool *is_nan);

extern void convert_chain(line *line, char *buffer, int saved_lines);

extern int comparator_for_numbers(const void* a, const void* b);

extern int comparator_for_words(const void* a, const void* b);

extern void sort_lines_numbers(line *line, int lines_number);

extern void sort_lines_words(line *line, int lines_number);

#endif /* FUNCTIONS_H */