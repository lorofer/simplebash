#ifndef files_processing_h
#define files_processing_h

#define _GNU_SOURCE

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grep_flags.h"

int files_processing(int, char **, struct grep_flags, char *, int);
void regex_compilation(struct grep_flags, regex_t *, char *);
void string_processing(char **, int, FILE *, int, regex_t, struct grep_flags);
void print_file_name(int, char *);
void string_output(char *);

#endif