#include "string_processing.h"

void string_processing(int argc, char *argv[], int file_index,
                       struct cat_flags flags) {
  int prev_str_number = 0;
  int curr_str_number = 1;

  char curr_ch;
  char prev_ch = 0;

  int prev_str_is_empty = 0;
  int it_is_a_first_str = 1;

  for (int i = file_index; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");

    if (file != NULL) {
      while ((curr_ch = fgetc(file)) != EOF) {
        if (!(flags.s && (curr_ch == '\n' && prev_str_is_empty))) {
          char_conversion(flags, curr_ch, &prev_ch, &prev_str_number,
                          &curr_str_number);
        }
        prev_str_is_empty =
            (curr_ch == '\n' && (prev_ch == '\n' || it_is_a_first_str));
        prev_ch = curr_ch;
        it_is_a_first_str = 0;
      }
      fclose(file);
    } else {
      fprintf(stderr, "s21_cat: %s: Нет такого файла или каталога\n", argv[i]);
    }
  }
}

void char_conversion(struct cat_flags flags, char curr_ch, const char *prev_ch,
                     int *prev_str_number, int *curr_str_number) {
  int char_has_been_output = 0;
  if (flags.n) {
    n_flag(curr_ch, prev_str_number, curr_str_number);
  }
  if (flags.b) {
    b_flag(curr_ch, *prev_ch, prev_str_number, curr_str_number);
  }
  if (flags.v) {
    char_has_been_output = v_flag(curr_ch) || char_has_been_output;
  }
  if (flags.e) {
    e_flag(curr_ch);
  }
  if (flags.t) {
    char_has_been_output = t_flag(curr_ch) || char_has_been_output;
  }

  if (!char_has_been_output) {
    putchar(curr_ch);
  }
}