#include "definitions.h"
#include "functions.h"
#include "line.h"

void init_buffer(char **buffer, int *buffer_size) {
	*buffer_size = INIT_SIZE;
	*buffer = malloc(*buffer_size * sizeof(char));
	if (*buffer == NULL) exit(1);
	*buffer[0] = '\0';	
}

void expand_buffer(char **buffer, int *buffer_size) {
	*buffer_size *= FACTOR;
	*buffer = realloc(*buffer, *buffer_size * sizeof(char));
	if (*buffer == NULL) exit(1);
}

long double convert_to_number(char *word, bool *is_nan) {
	char *remainder;
	long double number;
	*is_nan = false;
	int length = (int) strlen(word);

	if (length == 2 && word[0] == '0' && word[1] == 'x') {
		return 0.0;
	}
	else if (length > 2 && word[2] == 'x') {
		*is_nan = true;
		return 0.0;
	}
	else if (length >= 2 && word[0] == '0' && word[1] != 'x' && word[1] != '.') {
		number = (long double) strtoull(word, &remainder, OCTAL);

		if (remainder[0] != '\0' || number == 0) {
			number = strtold(word, &remainder);
		}

	}
	else {
		number = strtold(word, &remainder);
	}

	if (remainder[0] != '\0' || number != number) {
		*is_nan = true;
	}

	return number;
}

// Funkcja konwertująca cały wiersz w liczby i nieliczby i wrzucająca je do odpowiednich tablic
void convert_chain(line *line, char *buffer, int saved_lines) {
	char *token = strtok(buffer, " ");

	while (token != NULL) {
		bool is_nan;
		long double number = convert_to_number(token, &is_nan);

		if (is_nan) {
			line_insert_word(&line[saved_lines - 1], token);
		}
		else {
			line_insert_number(&line[saved_lines - 1], number);
		}

		token = strtok(NULL, " ");
	}

}

int comparator_for_numbers(const void* a, const void* b) {
	long double x = *(long double*) a;
	long double y = *(long double*) b;

	if (x < y) {
		return -1;
	}
	else if (x == y) {
		return 0;
	}
	else {
		return 1;
	}

}

int comparator_for_words(const void* a, const void* b) {
	char *x = *(char**) a;
	char *y = *(char**) b;

	return strcmp(x, y);
}

void sort_lines_numbers(line *line, int lines_number) {

	for (int i = 0; i < lines_number; i++) {
		long double *array = line[i].numbers;
		int number = line[i].number_count;
		int size = sizeof(long double);
		qsort(array, number, size, comparator_for_numbers);
	}

}

void sort_lines_words(line *line, int lines_number) {

	for (int i = 0; i < lines_number; i++) {
		char **array = line[i].words;
		int number = line[i].word_count;
		int size = sizeof(char*);
		qsort(array, number, size, comparator_for_words);
	}

}