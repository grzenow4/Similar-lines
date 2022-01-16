#ifndef LINE_H
#define LINE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void init_line(line *line);

extern void expand_line_word_array(line *line);

extern void expand_line_number_array(line *line);

extern void line_insert_word(line *line, char *word);

extern void line_insert_number(line *line, long double number);

extern void remove_lines(line *line, int saved_lines);

extern bool similar_lines(line *line, int no1, int no2);

#endif /* LINE_H */