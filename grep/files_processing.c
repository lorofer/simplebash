#include "files_processing.h"

int files_processing(int argc, char *argv[], struct grep_flags flags,
                     char *regex_pattern, int files_index) {
  int error = 0;

  regex_t regex;
  regex_compilation(flags, &regex, regex_pattern);

  int file_names_visible = !(files_index == argc - 1) && !flags.h;
  for (int i = files_index; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");
    if (file == NULL) {
      if (!flags.s) {
        fprintf(stderr, "s21_grep: %s: Нет такого файла или каталога\n",
                argv[files_index]);
      }
      error = 1;
    } else {
      string_processing(argv, i, file, file_names_visible, regex, flags);
      fclose(file);
    }
  }

  regfree(&regex);
  return error;
}

void regex_compilation(struct grep_flags flags, regex_t *regex,
                       char *regex_pattern) {
  int reg_flags = 0;
  if (flags.i) {
    reg_flags = REG_ICASE;
  }
  regcomp(regex, regex_pattern, reg_flags);
}

void string_processing(char *argv[], int curr_file_index, FILE *file,
                       int file_name_visible, regex_t regex,
                       struct grep_flags flags) {
  int str_counter = 0;
  int match_counter = 0;

  int file_matches = 0;

  char *string = NULL;
  size_t size = 0;
  while (getline(&string, &size, file) != -1) {
    str_counter++;

    regmatch_t match;
    int match_found = (regexec(&regex, string, 1, &match, 0) == 0) ^ flags.v;

    if (match_found) {
      if (flags.l) {
        file_matches = 1;
      } else if (flags.c) {
        match_counter++;
      } else if (flags.o) {
        char *string_cpy = calloc(strlen(string) + 1, sizeof(char));
        char *string_cpy_ptr = string_cpy;
        strcpy(string_cpy, string);

        while (regexec(&regex, string_cpy, 1, &match, 0) == 0) {
          print_file_name(file_name_visible, argv[curr_file_index]);
          if (flags.n) {
            printf("%d:", str_counter);
          }
          printf("%.*s\n", (int)(match.rm_eo - match.rm_so),
                 string_cpy + match.rm_so);
          string_cpy += (int)match.rm_eo;
        }

        free(string_cpy_ptr);
      } else {
        print_file_name(file_name_visible, argv[curr_file_index]);
        if (flags.n) {
          printf("%d:", str_counter);
        }
        string_output(string);
      }
    }
  }
  free(string);

  if (flags.l) {
    if (file_matches) {
      printf("%s\n", argv[curr_file_index]);
    }
  } else if (flags.c) {
    print_file_name(file_name_visible, argv[curr_file_index]);
    printf("%d\n", match_counter);
  }
}

void print_file_name(int file_name_visible, char *file_name) {
  if (file_name_visible) {
    printf("%s:", file_name);
  }
}

void string_output(char *string) {
  printf("%s", string);
  if (string[strlen(string) - 1] != '\n') {
    putchar('\n');
  }
}