#include "definitions.h"
#include "group.h"

void init_group_array(group *group) {
	group->capacity = INIT_SIZE;
	group->array = malloc(group->capacity * sizeof(int));
	if (group->array == NULL) exit(1);
	group->size = 0;
}

void expand_group_array(group *group) {
	group->capacity *= FACTOR;
	group->array = realloc(group->array, group->capacity * sizeof(int));
	if (group->array == NULL) exit(1);
}

void expand_groups(group **group, int *size) {
	*size *= FACTOR;
	*group = realloc(*group, *size * sizeof(group));
	if (*group == NULL) exit(1);
}

void remove_groups(group *group, int number_of_groups) {

	for (int i = 0; i < number_of_groups; i++) {
		free(group[i].array);
	}

	free(group);
}

// zwraca numer grupy, w której znajduje się number
int search_for_group(group *group, int number_of_groups, int number) {

	for (int i = 0; i < number_of_groups; i++) {

		for (int j = 0; j < group[i].size; j++) {

			if (group[i].array[j] == number) {
				return i;
			}

		}

	}

	return -1;
}

void print_groups(group *group, int number_of_groups) {

	for (int i = 0; i < number_of_groups; i++) {
		printf("%d", group[i].array[0]);

		for (int j = 1; j < group[i].size; j++) {
			printf(" %d", group[i].array[j]);
		}

		putchar('\n');
	}
}