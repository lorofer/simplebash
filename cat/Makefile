CC = gcc
FLAGS = -c -g -Wall -Werror -Wextra -std=c11

s21_cat: cat_main.o string_processing.o cat_flags.o
	$(CC) -o s21_cat cat_main.o string_processing.o cat_flags.o

string_processing.o: string_processing.c
	$(CC) $(FLAGS) string_processing.c

cat_flags.o: cat_flags.c
	$(CC) $(FLAGS) cat_flags.c

cat_main.o: cat_main.c
	$(CC) $(FLAGS) cat_main.c

clean:
	rm -rf *.o *.out s21_cat