#include "definitions.h"
#include "line.h"

void init_line(line *line) {
	line->word_array_size = INIT_SIZE;
	line->words = malloc(line->word_array_size * sizeof(char*));
	if (line->words == NULL) exit(1);
	line->word_count = 0;

	line->number_array_size = INIT_SIZE;
	line->numbers = malloc(line->number_array_size * sizeof(long double));
	if (line->numbers == NULL) exit(1);
	line->number_count = 0;
}

void expand_line_word_array(line *line) {
	line->word_array_size *= FACTOR;
	line->words = realloc(line->words, line->word_array_size * sizeof(char*));
	if (line->words == NULL) exit(1);
}

void expand_line_number_array(line *line) {
	line->number_array_size *= FACTOR;
	int size = line->number_array_size;
	line->numbers = realloc(line->numbers, size * sizeof(long double));
	if (line->numbers == NULL) exit(1);
}

void line_insert_word(line *line, char *word) {

	if (line->word_count == line->word_array_size) {
		expand_line_word_array(line);
	}

	line->words[line->word_count] = malloc((strlen(word) + 1) * sizeof(char));
	if (line->words == NULL) exit(1);

	strcpy(line->words[line->word_count], word);
	line->word_count++; 
}

void line_insert_number(line *line, long double number) {

	if (line->number_count == line->number_array_size) {
		expand_line_number_array(line);
	}

	line->numbers[line->number_count] = number;
	line->number_count++;
}

void remove_lines(line *line, int saved_lines) {

	for (int i = 0; i < saved_lines; i++) {

		for (int w = 0; w < line[i].word_count; w++) {
			free(line[i].words[w]);
		}

		free(line[i].words);
		free(line[i].numbers);
	}

}

bool similar_lines(line *line, int no1, int no2) {
	int amnt_of_nums_1 = line[no1].number_count;
	int amnt_of_nums_2 = line[no2].number_count;
	int amnt_of_nans_1 = line[no1].word_count;
	int amnt_of_nans_2 = line[no2].word_count;

	if (amnt_of_nums_1 == amnt_of_nums_2 && amnt_of_nans_1 == amnt_of_nans_2) {

		for (int i = 0; i < amnt_of_nums_1; i++) {

			if (line[no1].numbers[i] != line[no2].numbers[i]) {
				return false;
			}

		}

		for (int i = 0; i < amnt_of_nans_1; i++) {

			if (strcmp(line[no1].words[i], line[no2].words[i]) != 0) {
				return false;
			}

		}

	}
	else {
		return false;
	}

	return true;
}