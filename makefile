CC       = gcc
CPPFLAGS =
CFLAGS   = -Wall -Wextra -std=c11 -O2
LDFLAGS  =

.PHONY: all clean

OBJ =\
	line.o \
	group.o \
	functions.o \
	main.o

all: similar_lines

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

similar_lines: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o similar_lines

clean:
	rm -f *.o similar_lines
