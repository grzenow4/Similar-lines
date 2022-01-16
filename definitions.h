#define INIT_SIZE 16

#define FACTOR 2

#define OCTAL 8

#define LOWER_LIMIT 33

#define UPPER_LIMIT 126

struct group {
	int *array;
	int size;
	int capacity;
};

typedef struct group group;

struct line {
	char **words;
	int word_array_size;
	int word_count;

	long double *numbers;
	int number_array_size;
	int number_count;

	int line_number;
};

typedef struct line line;