CC = gcc
FLAGS = -c -g -Wall -Werror -Wextra -std=c11

s21_grep: grep_main.o grep_flags.o files_processing.o
	$(CC) -o s21_grep grep_main.o grep_flags.o files_processing.o

grep_main.o: grep_main.c
	$(CC) $(FLAGS) grep_main.c

grep_flags.o: grep_flags.c
	$(CC) $(FLAGS) grep_flags.c

files_processing.o: files_processing.c
	$(CC) $(FLAGS) files_processing.c

clean:
	rm -rf *.o *.out s21_grep