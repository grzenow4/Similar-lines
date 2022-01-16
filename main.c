#include "definitions.h"
#include "line.h"
#include "group.h"
#include "functions.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char c;
	int current_line = 1;
	int saved_lines = 0;

	int groups_size = INIT_SIZE;
	group *groups = malloc(groups_size * sizeof(group));
	if (groups == NULL) exit(1);
	int number_of_groups = 0;

	char *buffer;
	int buffer_size;

	line *lines = malloc(0);
	if (lines == NULL) exit(1);

	bool skip_line = false;

	init_buffer(&buffer, &buffer_size);

	do {
		c = getchar();

		if (c == '\n' || c == EOF) {

			if ((int) strlen(buffer) == 0 || skip_line) {
				saved_lines++;

				lines = realloc(lines, saved_lines * sizeof(line));
				if (lines == NULL) exit(1);

				init_line(&lines[saved_lines - 1]);
				lines[saved_lines - 1].line_number = current_line;
			}
			else if (!skip_line) {
				saved_lines++;

				lines = realloc(lines, saved_lines * sizeof(line));
				if (lines == NULL) exit(1);

				init_line(&lines[saved_lines - 1]);
				lines[saved_lines - 1].line_number = current_line;

				convert_chain(lines, buffer, saved_lines);
			}

			free(buffer);
			init_buffer(&buffer, &buffer_size);
			current_line++;
			skip_line = false;
		}
		else if (skip_line) {
			continue;
		}
		else if (!(c >= LOWER_LIMIT && c <= UPPER_LIMIT) && !isspace(c)) {
			skip_line = true;
			fprintf(stderr, "ERROR %d\n", current_line);
		}
		else {
			int length = (int) strlen(buffer);

			if (length == 0 && c == '#') {
				skip_line = true;
				continue;
			}

			if (length == buffer_size - 1) {
				expand_buffer(&buffer, &buffer_size);
			}

			if (isspace(c)) {
				c = ' ';
			}

			buffer[length] = tolower(c);
			buffer[length + 1] = '\0';
		}
	} while (c != EOF);

	sort_lines_numbers(lines, saved_lines);
	sort_lines_words(lines, saved_lines);

	for (int i = 0; i < saved_lines; i++) {

		if (lines[i].word_count != 0 || lines[i].number_count != 0) {
			bool is_in_new_group = true;

			for (int j = 0; j < i; j++) {

				if (similar_lines(lines, i, j)) {
					is_in_new_group = false;
					int nofg = number_of_groups;
					int num = lines[j].line_number;
					int group_number = search_for_group(groups, nofg, num);

					int gsize = groups[group_number].size;
					int gcapacity = groups[group_number].capacity;
					if (gsize == gcapacity) {
						expand_group_array(&groups[group_number]);
					}

					groups[group_number].array[gsize] = lines[i].line_number;
					groups[group_number].size++;
					break;
				}

			}

			if (is_in_new_group) {
				number_of_groups++;
				int nofg = number_of_groups;
				int num_2 = lines[i].line_number;
				groups = realloc(groups, number_of_groups * sizeof(group));
				init_group_array(&groups[number_of_groups - 1]);
				groups[nofg - 1].array[groups[nofg - 1].size] = num_2;
				groups[nofg - 1].size++;
			}

		}

	}

	print_groups(groups, number_of_groups);
	remove_lines(lines, saved_lines);
	remove_groups(groups, number_of_groups);
	free(lines);
	free(buffer);

	return 0;
}